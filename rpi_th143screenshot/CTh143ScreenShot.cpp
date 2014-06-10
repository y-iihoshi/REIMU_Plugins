#include <cstring>
#include <cstdarg>
#include "CTh143ScreenShot.h"
#include "..\rpi_threplay\Lzss.h"
#include "..\rpi_threplay\smart_array.h"
#include "..\rpi_threplay\sueLib_LE.h"

static void print(char **ppszDst, size_t *pnDstSize, const char *pszFormat, ...)
{
	if ((ppszDst != NULL) && (pnDstSize != NULL) && (pszFormat != NULL))
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

CTh143ScreenShot::Info::Info(const char *pSrc, size_t nSize)
{
	if ((pSrc != NULL) && (nSize >= this->Size))
	{
		this->unknown1	= *((uint16_t *)(pSrc + 0x04));
		this->day		= *((int16_t  *)(pSrc + 0x06));
		this->scene		= *((int16_t  *)(pSrc + 0x08));
		this->unknown2	= *((uint16_t *)(pSrc + 0x0A));
		this->width		= *((int16_t  *)(pSrc + 0x0C));
		this->height	= *((int16_t  *)(pSrc + 0x0E));
		this->unknown3	= *((uint32_t *)(pSrc + 0x10));
		this->dateTime	= *((uint32_t *)(pSrc + 0x14));
		this->slowRate	= *((float    *)(pSrc + 0x18));
		::memcpy_s(this->unknown4, 0x58, pSrc + 0x1C, 0x58);
	}
}

CTh143ScreenShot::Info::~Info()
{
}

bool CTh143ScreenShot::IsSupported(const char *pSrc, size_t nSize)
{
	return (nSize >= 4) && (std::strncmp(pSrc, "BST3", 4) == 0);
}

int CTh143ScreenShot::GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pnDstSize)
{
	if ((pSrc == NULL) || (ppDst == NULL) || (pnDstSize == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh143ScreenShot::Info info(pSrc, nSrcSize);

	*ppDst = (char *)::LocalAlloc(LPTR, 1024);
	if (*ppDst == NULL)
		return RET_ERR_NOMEM;

	// FIXME

	*pnDstSize = std::strlen(*ppDst);

	return RET_OK;
}

CTh143ScreenShot::Info *CTh143ScreenShot::GetInfo(const char *pSrc, size_t nSrcSize)
{
	return new CTh143ScreenShot::Info(pSrc, nSrcSize);
}

int CTh143ScreenShot::GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo)
{
	if ((pSrc == NULL) || (ppDst == NULL) || (ppInfo == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh143ScreenShot::Info info(pSrc, nSrcSize);

	size_t nDstSize = 4 * info.width * info.height;
	*ppDst = (char *)::LocalAlloc(LPTR, nDstSize);
	if (*ppDst == NULL)
		return RET_ERR_NOMEM;
	*ppInfo = (BITMAPINFO *)::LocalAlloc(LPTR, sizeof(BITMAPINFO));
	if (*ppInfo == NULL)
	{
		LocalFree(*ppDst);
		return RET_ERR_NOMEM;
	}

	Lzss::Extract(pSrc + info.Size, nSrcSize - info.Size, *ppDst, nDstSize);

	size_t nStride = 4 * info.width;
	char *pScanline = new char[nStride];
	char *pTop = *ppDst;
	char *pBottom = *ppDst + nDstSize - nStride;
	for (int i = 0; i < info.height / 2; i++)
	{
		::memcpy_s(pScanline, nStride, pTop, nStride);
		::memcpy_s(pTop, nStride, pBottom, nStride);
		::memcpy_s(pBottom, nStride, pScanline, nStride);
		pTop += nStride;
		pBottom -= nStride;
	}
	delete [] pScanline;

	BITMAPINFOHEADER *pHeader = &((*ppInfo)->bmiHeader);
	pHeader->biSize = sizeof(BITMAPINFOHEADER);
	pHeader->biWidth = info.width;
	pHeader->biHeight = info.height;
	pHeader->biPlanes = 1;
	pHeader->biBitCount = 32;
	pHeader->biCompression = BI_RGB;
	pHeader->biSizeImage = 0;
	pHeader->biXPelsPerMeter = 0;
	pHeader->biYPelsPerMeter = 0;
	pHeader->biClrUsed = 0;
	pHeader->biClrImportant = 0;

	return RET_OK;
}
