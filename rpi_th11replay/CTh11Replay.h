#pragma once

#include <memory>
#include "IReplay.h"

#define USER_DATA_TYPE_INFO		0
#define USER_DATA_TYPE_COMMENT	1

class CTh11Replay : public IReplay
{
public:
	class Info
	{
	public:
		Info(const char *pSrc, size_t nSize);
		~Info();

	private:
		Info(const Info &);
		Info& operator=(const Info &);

	public:
		const char *pszVersion;
		const char *pszName;
		const char *pszDate;
		const char *pszChara;
		const char *pszRank;
		const char *pszStage;
		const char *pszScore;
		const char *pszSlowRate;

	private:
		char *pData;
	};

public:
	bool IsSupported(const char *pSrc, size_t nSrcSize);
	int GetInfo(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize);
	Info *GetInfo(const char *pSrc, size_t nSrcSize);
	int GetComment(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize);
	int ReadComment(const char *pFilename, const char **ppDst, size_t *pDstSize);
	int WriteComment(const char *pFilename, const char *pSrc, size_t nSrcSize);
	int GetNumber(const char *pFilename, int *pNumType, char *pNum, size_t nNumSize);

private:
	int GetUserData(int nType, const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize);
};
