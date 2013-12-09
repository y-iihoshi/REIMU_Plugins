#include <regex>
#include <cstring>
#include "CTh128Replay.h"
#include "..\rpi_threplay\smart_array.h"
#include "..\rpi_threplay\sueLib_LE.h"

CTh128Replay::Info::Info(const char *pSrc, size_t nSize)
	: pData(new char[nSize])
{
	::memcpy_s(this->pData, nSize, pSrc, nSize);

	this->pszVersion = std::strstr(this->pData, "Version ") + std::strlen("Version ");
	this->pszName = std::strstr(this->pData, "Name ") + std::strlen("Name ");
	this->pszDate = std::strstr(this->pData, "Date ") + std::strlen("Date ");
	this->pszRoute = std::strstr(this->pData, "Route ") + std::strlen("Route ");
	this->pszLevel = std::strstr(this->pData, "Rank ") + std::strlen("Rank ");
	this->pszStage = std::strstr(this->pData, "Stage ") + std::strlen("Stage ");
	this->pszScore = std::strstr(this->pData, "Score ") + std::strlen("Score ");
	this->pszSlowRate = std::strstr(this->pData, "Slow Rate ") + std::strlen("Slow Rate ");

	for (size_t i = 0; i < nSize; i++)
		if ((this->pData[i] == 0x0D) || (this->pData[i] == 0x0A))
			this->pData[i] = 0x00;
}

CTh128Replay::Info::~Info()
{
	delete [] this->pData;
}

/*
	Structure of TH128 replay file:
		replay
			0x24 bytes:	replayHeader
				0x04 bytes:	replaySignature ("128r")
				0x08 bytes:	(unknown)
				0x04 bytes:	size of `replay'
				0x0C bytes:	(unknown)
				0x04 bytes:	size of `replayData'
				0x04 bytes:	(unknown)
			**** bytes:	replayData
		user<N>
			0x0C bytes: user<N>Header
				0x04 bytes: user<N>Signature ("USER")
				0x04 bytes: size of `user<N>'
				0x04 bytes: userDataType (0: info except comment, 1: comment)
			**** bytes:	user<N>Data
*/
#pragma pack(push)
#pragma pack(1)
struct UserHeader
{
	char szSignature[4];
	unsigned int nSize;
	unsigned int nType;
};
#pragma pack(pop)

static const unsigned int replaySizeOffset = 0x0C;
static const unsigned int userHeaderSize = 0x0C;

bool CTh128Replay::IsSupported(const char *pSrc, size_t nSize)
{
	return (nSize >= 4) && (std::strncmp(pSrc, "128r", 4) == 0);
}

int CTh128Replay::GetInfo(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize)
{
	return this->GetUserData(USER_DATA_TYPE_INFO, pSrc, nSrcSize, ppDst, pDstSize);
}

CTh128Replay::Info *CTh128Replay::GetInfo(const char *pSrc, size_t nSrcSize)
{
	const char *pDest;
	size_t nDestSize;

	return (this->GetInfo(pSrc, nSrcSize, &pDest, &nDestSize) == RET_OK)
		? new CTh128Replay::Info(pDest, nDestSize) : NULL;
}

int CTh128Replay::GetComment(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize)
{
	return this->GetUserData(USER_DATA_TYPE_COMMENT, pSrc, nSrcSize, ppDst, pDstSize);
}

int CTh128Replay::ReadComment(const char *pFilename, const char **ppDst, size_t *pDstSize)
{
	smart_array<char> buf;
	return File2Memory(pFilename, buf)
		? this->GetComment(buf.GetPtr(), buf.GetSize(), ppDst, pDstSize) : RET_ERR_READ;
}

int CTh128Replay::WriteComment(const char *pFilename, const char *pSrc, size_t nSrcSize)
{
	smart_array<char> buf;
	if (!File2Memory(pFilename, buf))
		return RET_ERR_READ;
	if (!this->IsSupported(buf.GetPtr(), buf.GetSize()))
		return RET_ERR_READ;

	FILE *fp;
	errno_t retval = ::fopen_s(&fp, pFilename, "wb");
	if (retval != 0)
		return RET_ERR_WRITE;

	unsigned int user1Offset, user2Offset;
	UserHeader user1Header, user2Header;
	size_t wroteCount;

	// Write `replay' section
	::memcpy_s(&user1Offset, sizeof(unsigned int), buf.GetPtr() + replaySizeOffset, sizeof(unsigned int));
	wroteCount = std::fwrite(buf.GetPtr(), sizeof(char), user1Offset, fp);
	if (wroteCount != user1Offset)
	{
		std::fclose(fp);
		return RET_ERR_WRITE;
	}

	// Read `user<N>' section headers
	::memcpy_s(&user1Header, sizeof(UserHeader), buf.GetPtr() + user1Offset, sizeof(UserHeader));
	user2Offset = user1Offset + user1Header.nSize;
	::memcpy_s(&user2Header, sizeof(UserHeader), buf.GetPtr() + user2Offset, sizeof(UserHeader));
	if (user1Header.nType != USER_DATA_TYPE_INFO)
	{
		std::swap(user1Offset, user2Offset);
		std::swap(user1Header, user2Header);
	}

	// Write `user1' (= info) section
	wroteCount = std::fwrite(buf.GetPtr() + user1Offset, sizeof(char), user1Header.nSize, fp);
	if (wroteCount != user1Header.nSize)
	{
		std::fclose(fp);
		return RET_ERR_WRITE;
	}

	// Write `user2' (= comment) section
	user2Header.nSize = userHeaderSize + nSrcSize;
	wroteCount = std::fwrite(&user2Header, sizeof(UserHeader), 1, fp);
	if (wroteCount != 1)
	{
		std::fclose(fp);
		return RET_ERR_WRITE;
	}
	wroteCount = std::fwrite(pSrc, sizeof(char), nSrcSize, fp);
	if (wroteCount != user2Header.nSize)
	{
		std::fclose(fp);
		return RET_ERR_WRITE;
	}

	std::fflush(fp);
	std::fclose(fp);
	return RET_OK;
}

int CTh128Replay::GetNumber(const char *pFilename, int *pNumType, char *pNum, size_t nNumSize)
{
	if ((pFilename == NULL) || (pNumType == NULL) || (pNum == NULL))
		return RET_ERR_PARAM;

	const char *pName = std::strrchr(pFilename, '\\');
	pName = (pName != NULL) ? (pName + 1) : pFilename;

	std::regex reBasic("th128_([[:digit:]]{2}).rpy", (std::regex::ECMAScript | std::regex::icase));
	std::regex reUser("th128_ud(.{0,4}).rpy", (std::regex::ECMAScript | std::regex::icase));
	std::cmatch results;

	*pNumType = NUM_TYPE_INVALID;
	if (std::regex_match(pName, results, reBasic))
	{
		int num = std::strtol(results[1].str().c_str(), NULL, 10);
		if ((0 < num) && (num <= 25))
			if (::strcpy_s(pNum, nNumSize, results[1].str().c_str()) == 0)
				*pNumType = NUM_TYPE_BASIC;
	}
	else if (std::regex_match(pName, results, reUser))
		if (::strcpy_s(pNum, nNumSize, results[1].str().c_str()) == 0)
			*pNumType = NUM_TYPE_USER;

	return RET_OK;
}

int CTh128Replay::GetUserData(int nType, const char *pSrc, size_t nSize, const char **ppDst, size_t *pDstSize)
{
	if ((nType != USER_DATA_TYPE_INFO) && (nType != USER_DATA_TYPE_COMMENT))
		return RET_ERR_PARAM;
	if ((pSrc == NULL) || (ppDst == NULL) || (pDstSize == NULL))
		return RET_ERR_PARAM;

	unsigned int userOffset;
	UserHeader userHeader;

	::memcpy_s(&userOffset, sizeof(unsigned int), pSrc + replaySizeOffset, sizeof(unsigned int));
	::memcpy_s(&userHeader, sizeof(UserHeader), pSrc + userOffset, sizeof(UserHeader));
	if (userHeader.nType != nType)
	{
		userOffset += userHeader.nSize;
		::memcpy_s(&userHeader, sizeof(UserHeader), pSrc + userOffset, sizeof(UserHeader));
	}

	if (std::strncmp(userHeader.szSignature, "USER", 4) != 0)
		return RET_ERR_READ;
	if (nSize < userOffset + userHeader.nSize)
		return RET_ERR_READ;
	if (userHeader.nType != nType)
		return RET_ERR_READ;

	*ppDst = pSrc + userOffset + userHeaderSize;
	*pDstSize = userHeader.nSize - userHeaderSize;

	return RET_OK;
}
