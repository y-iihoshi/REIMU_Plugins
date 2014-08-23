#pragma once

#include <map>
#include <cstdint>
#include "..\rpi_threplay\IReplay.h"
#include "Mode.h"
#include "Chara.h"

class CTh105Replay
{
public:
	class Deck
	{
	public:
		typedef std::map<uint16_t, int32_t> CardMap;

	public:
		explicit Deck(const char *pSrc);
		~Deck();

	private:
		Deck(const Deck &);
		Deck& operator=(const Deck &);

	public:
		static const size_t Size = 0x2E;

	public:
		Th105::Chara chara;
		uint8_t color;
		uint32_t numCards;	// always 20?
		CardMap cards;
	};

	class Info
	{
	public:
		Info(const char *pSrc, size_t nSize);
		~Info();

	private:
		Info(const Info &);
		Info& operator=(const Info &);

	public:
		static const size_t Size = 0x7C;

	public:
		uint16_t versionId;
		Th105::Mode mode;
		Deck *pDeck1;
		Deck *pDeck2;
		uint8_t stageId;
		uint8_t bgmId;
		int32_t frames;
	};

public:
	bool IsSupported(const char *pSrc, size_t nSrcSize);
	int GetPlayerInfo(int player, const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pDstSize);
	Info *GetInfo(const char *pSrc, size_t nSrcSize);
};
