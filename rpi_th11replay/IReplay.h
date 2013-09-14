#pragma once

#define RET_OK			0
#define RET_ERR_PARAM	1
#define RET_ERR_READ	2
#define RET_ERR_WRITE	3
#define RET_ERR_NOMEM	4

class IReplay
{
public:
	enum NumberType
	{
		NUM_TYPE_BASIC,
		NUM_TYPE_USER,
		NUM_TYPE_INVALID
	};

public:
	virtual ~IReplay() = 0;
	virtual bool IsSupported(const char *pSrc, size_t nSrcSize) = 0;
	virtual int GetInfo(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize) = 0;
	virtual int GetComment(const char *pSrc, size_t nSrcSize, const char **ppDst, size_t *pDstSize) = 0;
	virtual int GetNumber(const char *pFilename, int *pNumType, char *pNum, size_t nNumSize) = 0;
};
