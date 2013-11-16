#include <cstring>
#include <cstdarg>
#include "CTh125BestShot.h"
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

CTh125BestShot::Info::Info(const char *pSrc, size_t nSize)
{
	if ((pSrc != NULL) && (nSize >= this->Size))
	{
		this->unknown1			= *((uint16_t *)(pSrc + 0x04));
		this->level				= *((int16_t  *)(pSrc + 0x06));
		this->scene				= *((int16_t  *)(pSrc + 0x08));
		this->unknown2			= *((uint16_t *)(pSrc + 0x0A));
		this->width				= *((int16_t  *)(pSrc + 0x0C));
		this->height			= *((int16_t  *)(pSrc + 0x0E));
		this->unknown3			= *((uint32_t *)(pSrc + 0x10));
		this->width2			= *((int16_t  *)(pSrc + 0x14));
		this->height2			= *((int16_t  *)(pSrc + 0x16));
		this->halfWidth			= *((int16_t  *)(pSrc + 0x18));
		this->halfHeight		= *((int16_t  *)(pSrc + 0x1A));
		this->dateTime			= *((uint32_t *)(pSrc + 0x1C));
		this->unknown4			= *((uint32_t *)(pSrc + 0x20));
		this->slowRate			= *((float    *)(pSrc + 0x24));
		this->bonusFields.value	= *((uint32_t *)(pSrc + 0x28));
		this->resultScore		= *((int32_t  *)(pSrc + 0x2C));
		this->basePoint			= *((int32_t  *)(pSrc + 0x30));
		this->unknown7[0]		= *((uint32_t *)(pSrc + 0x34));
		this->unknown7[1]		= *((uint32_t *)(pSrc + 0x38));
		this->riskBonus			= *((int32_t  *)(pSrc + 0x3C));
		this->bossShot			= *((float    *)(pSrc + 0x40));
		this->niceShot			= *((float    *)(pSrc + 0x44));
		this->angleBonus		= *((float    *)(pSrc + 0x48));
		this->macroBonus		= *((int32_t  *)(pSrc + 0x4C));
		this->frontSideBackShot = *((int32_t  *)(pSrc + 0x50));
		this->clearShot			= *((int32_t  *)(pSrc + 0x54));
		::memcpy_s(this->unknown10, 0x30, pSrc + 0x58, 0x30);
		this->angle				= *((float    *)(pSrc + 0x88));
		this->resultScore2		= *((int32_t  *)(pSrc + 0x8C));
		this->unknown12			= *((uint32_t *)(pSrc + 0x90));
		::memcpy_s(this->cardName, 0x50, pSrc + 0x94, 0x50);
	}
}

CTh125BestShot::Info::~Info()
{
}

bool CTh125BestShot::IsSupported(const char *pSrc, size_t nSize)
{
	return (nSize >= 4) && (std::strncmp(pSrc, "BST2", 4) == 0);
}

int CTh125BestShot::GetInfo(const char *pSrc, size_t nSrcSize, char **ppDst, size_t *pnDstSize)
{
	if ((pSrc == NULL) || (ppDst == NULL) && (pnDstSize == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh125BestShot::Info info(pSrc, nSrcSize);

	*ppDst = (char *)::LocalAlloc(LPTR, 1024);
	if (*ppDst == NULL)
		return RET_ERR_NOMEM;

	char *pDst = *ppDst;
	size_t nRemainSize = 1024;

	print(&pDst, &nRemainSize, "Base Point  %d\r\n", info.basePoint);
	if (info.bonusFields.fields.clearShot)
		print(&pDst, &nRemainSize, "Clear Shot!  + %d\r\n", info.clearShot);
	if (info.bonusFields.fields.soloShot)
		print(&pDst, &nRemainSize, "Solo Shot  + 100\r\n");
	if (info.bonusFields.fields.redShot)
		print(&pDst, &nRemainSize, "Red Shot  + 300\r\n");
	if (info.bonusFields.fields.purpleShot)
		print(&pDst, &nRemainSize, "Purple Shot  + 300\r\n");
	if (info.bonusFields.fields.blueShot)
		print(&pDst, &nRemainSize, "Blue Shot  + 300\r\n");
	if (info.bonusFields.fields.cyanShot)
		print(&pDst, &nRemainSize, "Cyan Shot  + 300\r\n");
	if (info.bonusFields.fields.greenShot)
		print(&pDst, &nRemainSize, "Green Shot  + 300\r\n");
	if (info.bonusFields.fields.yellowShot)
		print(&pDst, &nRemainSize, "Yellow Shot  + 300\r\n");
	if (info.bonusFields.fields.orangeShot)
		print(&pDst, &nRemainSize, "Orange Shot  + 300\r\n");
	if (info.bonusFields.fields.colorfulShot)
		print(&pDst, &nRemainSize, "Colorful Shot  + 900\r\n");
	if (info.bonusFields.fields.rainbowShot)
		print(&pDst, &nRemainSize, "Rainbow Shot  + 2100\r\n");
	if (info.bonusFields.fields.riskBonus)
		print(&pDst, &nRemainSize, "Risk Bonus  + %d\r\n", info.riskBonus);
	if (info.bonusFields.fields.macroBonus)
		print(&pDst, &nRemainSize, "Macro Bonus  + %d\r\n", info.macroBonus);
	if (info.bonusFields.fields.frontShot)
		print(&pDst, &nRemainSize, "Front Shot  + %d\r\n", info.frontSideBackShot);
	if (info.bonusFields.fields.sideShot)
		print(&pDst, &nRemainSize, "Side Shot  + %d\r\n", info.frontSideBackShot);
	if (info.bonusFields.fields.backShot)
		print(&pDst, &nRemainSize, "Back Shot  + %d\r\n", info.frontSideBackShot);
	if (info.bonusFields.fields.catBonus)
		print(&pDst, &nRemainSize, "Cat Bonus  + 666\r\n");
	print(&pDst, &nRemainSize, "\r\n");

	print(&pDst, &nRemainSize, "Boss Shot!  * %.2f\r\n", info.bossShot);
	if (info.bonusFields.fields.twoShot)
		print(&pDst, &nRemainSize, "Two Shot!  * 1.50\r\n");
	if (info.bonusFields.fields.niceShot)
		print(&pDst, &nRemainSize, "Nice Shot!  * %.2f\r\n", info.niceShot);
	print(&pDst, &nRemainSize, "Angle Bonus  * %.2f\r\n", info.angleBonus);
	print(&pDst, &nRemainSize, "\r\n");

	print(&pDst, &nRemainSize, "Result Score  %d\r\n", info.resultScore);

	*pnDstSize = std::strlen(*ppDst);

	return RET_OK;
}

CTh125BestShot::Info *CTh125BestShot::GetInfo(const char *pSrc, size_t nSrcSize)
{
	return new CTh125BestShot::Info(pSrc, nSrcSize);
}

int CTh125BestShot::GetPicture(const char *pSrc, size_t nSrcSize, char **ppDst, BITMAPINFO **ppInfo)
{
	if ((pSrc == NULL) || (ppDst == NULL) || (ppInfo == NULL))
		return RET_ERR_PARAM;

	if (!this->IsSupported(pSrc, nSrcSize))
		return RET_ERR_READ;

	CTh125BestShot::Info info(pSrc, nSrcSize);

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
