#pragma once

#include <cstdint>
#include "..\rpi_threplay\IImage.h"

class CTh143ScreenShot : public IImage
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
		static const size_t Size = 0x74;

	public:
		uint16_t unknown1;
		int16_t day;				// 0-origin
		int16_t scene;				// 0-origin
		uint16_t unknown2;			// 0x0100 ... Version?
		int16_t width;
		int16_t height;
		uint32_t unknown3;			// always 0x0005E800?
		uint32_t dateTime;
		float slowRate;
		uint8_t unknown4[0x58];
	};

public:
	bool IsSupported(const char *pSrc, size_t nSrcSize);
	int GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pDstSize);
	Info *GetInfo(const char *pSrc, size_t nSrcSize);
	int GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo);
};
