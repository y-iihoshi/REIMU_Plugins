#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdarg>
#include "CTh123Replay.h"
#include "StringMaps.h"
#include "..\rpi_threplay\smart_array.h"
#include "..\rpi_threplay\sueLib_LE.h"

using namespace Th123;

namespace
{
	void print(char **ppszDst, size_t *pnDstSize, const char *pszFormat, ...)
	{
		if ((ppszDst != nullptr) && (pnDstSize != nullptr) && (pszFormat != nullptr))
		{
			va_list list;
			int nWroteBytes;

			va_start(list, pszFormat);
			nWroteBytes = ::vsprintf_s(*ppszDst, *pnDstSize, pszFormat, list);
			*ppszDst += nWroteBytes;
			*pnDstSize -= nWroteBytes;
			va_end(list);
		}
	}
}

CTh123Replay::Deck::Deck(const char *pSrc)
{
	if (pSrc != nullptr)
	{
		this->chara    = *(reinterpret_cast<const Chara    *>(pSrc));
		this->color    = *(reinterpret_cast<const uint8_t  *>(pSrc + 0x01));
		this->numCards = *(reinterpret_cast<const uint32_t *>(pSrc + 0x02));

		const uint16_t *pCardId = reinterpret_cast<const uint16_t *>(pSrc + 0x06);
		for (uint32_t count = 0; count < this->numCards; count++)
		{
			if (this->cards.find(*pCardId) != this->cards.end())
				this->cards[*pCardId]++;
			else
				this->cards[*pCardId] = 1;
			pCardId++;
		}
	}
}

CTh123Replay::Deck::~Deck()
{
}

CTh123Replay::Info::Info(const char *pSrc, size_t nSize)
	: pDeck1(nullptr), pDeck2(nullptr)
{
	if ((pSrc != nullptr) && (nSize >= this->Size))
	{
		this->versionId = *(reinterpret_cast<const int16_t *>(pSrc));
		this->mode      = *(reinterpret_cast<const Mode    *>(pSrc + 0x08));
		this->pDeck1 = new Deck(pSrc + 0x0E);
		if (this->mode == Mode::Story)
		{
			this->stageId = -1;
			this->bgmId   = -1;
			this->frames  = -1;
		}
		else
		{
			this->pDeck2  = new Deck(pSrc + 0x3F);
			this->stageId = *(reinterpret_cast<const int8_t *>(pSrc + 0x71));
			this->bgmId   = *(reinterpret_cast<const int8_t *>(pSrc + 0x72));
			this->frames  = (nSize - 0x79) / ((this->mode == Mode::VsCom) ? 4 : 2);		// really...?
		}
	}
}

CTh123Replay::Info::~Info()
{
	delete pDeck1;
	delete pDeck2;
}

bool CTh123Replay::IsSupported(const char *pSrc, size_t nSize)
{
	bool isSupported = false;

	if (nSize >= 2)
	{
		int16_t versionId = *(reinterpret_cast<const int16_t *>(pSrc));
		isSupported = (Th123::Versions.find(versionId) != Th123::Versions.cend());
	}

	return isSupported;
}

int CTh123Replay::GetPlayerInfo(
	int player, const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pDstSize)
{
	if ((player != 1) && (player != 2))
		return RET_ERR_PARAM;

	if ((pSrc == nullptr) || (ppDst == nullptr) || (pDstSize == nullptr))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh123Replay::Info info(pSrc, nSrcSize);

	*ppDst = (char *)::LocalAlloc(LPTR, 2048);
	if (*ppDst == nullptr)
		return RET_ERR_NOMEM;

	Deck *pDeck = (player == 1) ? info.pDeck1 : info.pDeck2;
	char *pDst = *ppDst;
	size_t nRemainSize = 2048;

	if ((info.mode == Mode::Story) && (player == 2))
	{
		::strcpy_s(pDst, nRemainSize, "");
		*pDstSize = sizeof(char);	// for null terminator
		return RET_OK;
	}

	::print(&pDst, &nRemainSize, "Player %d\r\n", player);
	::print(&pDst, &nRemainSize, "Character: %s\r\n",
		Th123::GetString(Th123::Characters, pDeck->chara).c_str());
	::print(&pDst, &nRemainSize, "Color: %d\r\n", pDeck->color);
	std::for_each(pDeck->cards.cbegin(), pDeck->cards.cend(),
		[&](const Deck::CardMap::value_type &value)
		{
			const auto &cards = (value.first < 100) ? Th123::SystemCards : Th123::Cards.at(pDeck->chara);
			return ::print(&pDst, &nRemainSize, "%s * %d\r\n",
				Th123::GetString(cards, value.first).c_str(), value.second);
		});

	*pDstSize = 2048 - nRemainSize + sizeof(char);	// for null terminator

	return RET_OK;
}

CTh123Replay::Info *CTh123Replay::GetInfo(const char *pSrc, size_t nSrcSize)
{
	return new CTh123Replay::Info(pSrc, nSrcSize);
}
