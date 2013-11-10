#pragma once

#include <cstdint>
#include "..\rpi_threplay\IImage.h"

class CTh125BestShot : public IImage
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
		static const size_t Size = 0xE4;

	public:
		uint16_t unknown1;			// always 0x0405?
		int16_t level;				// 1-origin
		int16_t scene;				// 1-origin
		uint16_t unknown2;			// 0x0100 ... Version?
		int16_t width;
		int16_t height;
		uint32_t unknown3;			// always 0x00000000?
		int16_t width2;
		int16_t height2;
		int16_t halfWidth;
		int16_t halfHeight;
		uint32_t dateTime;
		uint32_t unknown4;			// always 0x00000000?
		float slowRate;
		union
		{
			struct
			{
				uint32_t bit00 : 1;		// always 1?
				uint32_t bit01 : 1;		// always 0?
				uint32_t twoShot : 1;
				uint32_t niceShot : 1;
				uint32_t riskBonus : 1;
				uint32_t bit05 : 1;		// always 0?
				uint32_t redShot : 1;
				uint32_t purpleShot : 1;

				uint32_t blueShot : 1;
				uint32_t cyanShot : 1;
				uint32_t greenShot : 1;
				uint32_t yellowShot : 1;
				uint32_t orangeShot : 1;
				uint32_t colorfulShot : 1;
				uint32_t rainbowShot : 1;
				uint32_t bit15 : 1;		// always 0?

				uint32_t soloShot : 1;
				uint32_t bit17 : 1;		// always 0?
				uint32_t bit18 : 1;		// always 0?
				uint32_t bit19 : 1;		// always 0?
				uint32_t bit20 : 1;		// always 1?
				uint32_t bit21 : 1;		// always 1?
				uint32_t macroBonus : 1;
				uint32_t bit23 : 1;		// always 1?

				uint32_t frontShot : 1;
				uint32_t backShot : 1;
				uint32_t sideShot : 1;
				uint32_t clearShot : 1;
				uint32_t catBonus : 1;
				uint32_t bit29 : 1;		// always 0?
				uint32_t bit30 : 1;		// always 0?
				uint32_t bit31 : 1;		// always 0?
			} fields;
			uint32_t value;
		} bonusFields;
		int32_t resultScore;
		int32_t basePoint;
		uint32_t unknown7[2];
		int32_t riskBonus;
		float bossShot;
		float niceShot;
		float angleBonus;
		int32_t macroBonus;
		int32_t frontSideBackShot;
		int32_t clearShot;
		uint8_t unknown10[0x30];	// always all 0x00?
		float angle;
		int32_t resultScore2;
		uint32_t unknown12;			// checksum?
		uint8_t cardName[0x50];
	};

public:
	bool IsSupported(const char *pSrc, size_t nSrcSize);
	int GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pDstSize);
	Info *GetInfo(const char *pSrc, size_t nSrcSize);
	int GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo);
};
