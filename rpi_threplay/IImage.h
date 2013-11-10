#pragma once

#include <Windows.h>

#define RET_OK			0
#define RET_ERR_PARAM	1
#define RET_ERR_READ	2
#define RET_ERR_WRITE	3
#define RET_ERR_NOMEM	4

class IImage
{
public:
	virtual ~IImage() = 0;

	virtual bool IsSupported(const char *pSrc, size_t nSrcSize) = 0;
	virtual int GetPicture(const char *pSrc, size_t nSrcSize, char **pDst, BITMAPINFO **lpInfo) = 0;
};
