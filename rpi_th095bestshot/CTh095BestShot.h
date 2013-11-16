#pragma once

#include <cstdint>
#include "..\rpi_threplay\IImage.h"

class CTh095BestShot : public IImage
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
		static const size_t Size = 0x68;

	public:
		uint16_t unknown1;			// always 0x0302?
		int16_t level;				// 1-origin
		int16_t scene;				// 1-origin
		uint16_t unknown2;			// 0x0102 ... Version?
		int16_t width;
		int16_t height;
		int32_t score;
		float slowRate;
		uint8_t cardName[0x50];
	};

public:
	bool IsSupported(const char *pSrc, size_t nSrcSize);
	int GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pDstSize);
	Info *GetInfo(const char *pSrc, size_t nSrcSize);
	int GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo);
};
