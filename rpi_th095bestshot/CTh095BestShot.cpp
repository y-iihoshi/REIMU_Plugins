#include <cstring>
#include "CTh095BestShot.h"
#include "..\rpi_threplay\Lzss.h"
#include "..\rpi_threplay\smart_array.h"
#include "..\rpi_threplay\sueLib_LE.h"

CTh095BestShot::Info::Info(const char *pSrc, size_t nSize)
{
	if ((pSrc != NULL) && (nSize >= this->Size))
	{
		this->unknown1	= *((uint16_t *)(pSrc + 0x04));
		this->level		= *((int16_t  *)(pSrc + 0x06));
		this->scene		= *((int16_t  *)(pSrc + 0x08));
		this->unknown2	= *((uint16_t *)(pSrc + 0x0A));
		this->width		= *((int16_t  *)(pSrc + 0x0C));
		this->height	= *((int16_t  *)(pSrc + 0x0E));
		this->score		= *((int32_t  *)(pSrc + 0x10));
		this->slowRate	= *((float    *)(pSrc + 0x14));
		::memcpy_s(this->cardName, 0x50, pSrc + 0x18, 0x50);
	}
}

CTh095BestShot::Info::~Info()
{
}

bool CTh095BestShot::IsSupported(const char *pSrc, size_t nSize)
{
	return (nSize >= 4) && (std::strncmp(pSrc, "BSTS", 4) == 0);
}

int CTh095BestShot::GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pnDstSize)
{
	if ((pSrc == NULL) || (ppDst == NULL) && (pnDstSize == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh095BestShot::Info info(pSrc, nSrcSize);

	*ppDst = (char *)::LocalAlloc(LPTR, 1024);
	if (*ppDst == NULL)
		return RET_ERR_NOMEM;

	// FIXME

	*pnDstSize = std::strlen(*ppDst);

	return RET_OK;
}

CTh095BestShot::Info *CTh095BestShot::GetInfo(const char *pSrc, size_t nSrcSize)
{
	return new CTh095BestShot::Info(pSrc, nSrcSize);
}

int CTh095BestShot::GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo)
{
	if ((pSrc == NULL) || (ppDst == NULL) || (ppInfo == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh095BestShot::Info info(pSrc, nSrcSize);

	size_t nSrcStride = 3 * info.width;
	size_t nDecodedSrcSize = nSrcStride * info.height;
	char *pDecodedSrc = (char *)::LocalAlloc(LPTR, nDecodedSrcSize);
	if (pDecodedSrc == NULL)
		return RET_ERR_NOMEM;

	size_t nDstStride = 3 * info.width;
	size_t nRemain = nDstStride % 4;
	if (nRemain)
		nDstStride += 4 - nRemain;
	size_t nDstSize = nDstStride * info.height;
	*ppDst = (char *)::LocalAlloc(LPTR, nDstSize);
	if (*ppDst == NULL)
	{
		::LocalFree(pDecodedSrc);
		return RET_ERR_NOMEM;
	}
	*ppInfo = (BITMAPINFO *)::LocalAlloc(LPTR, sizeof(BITMAPINFO));
	if (*ppInfo == NULL)
	{
		::LocalFree(pDecodedSrc);
		::LocalFree(*ppDst);
		return RET_ERR_NOMEM;
	}

	Lzss::Extract(pSrc + info.Size, nSrcSize - info.Size, pDecodedSrc, nDecodedSrcSize);

	char *pDstTop = *ppDst;
	char *pSrcBottom = pDecodedSrc + nDecodedSrcSize - nSrcStride;
	for (int i = 0; i < info.height; i++)
	{
		::memcpy_s(pDstTop, nDstStride, pSrcBottom, nSrcStride);
		pDstTop += nDstStride;
		pSrcBottom -= nSrcStride;
	}

	::LocalFree(pDecodedSrc);

	BITMAPINFOHEADER *pHeader = &((*ppInfo)->bmiHeader);
	pHeader->biSize = sizeof(BITMAPINFOHEADER);
	pHeader->biWidth = info.width;
	pHeader->biHeight = info.height;
	pHeader->biPlanes = 1;
	pHeader->biBitCount = 24;
	pHeader->biCompression = BI_RGB;
	pHeader->biSizeImage = 0;
	pHeader->biXPelsPerMeter = 0;
	pHeader->biYPelsPerMeter = 0;
	pHeader->biClrUsed = 0;
	pHeader->biClrImportant = 0;

	return RET_OK;
}
