#include <cstring>
#include "ThCrypt.h"

void ThCrypt::Decrypt(const char *pSrc, size_t nSrcSize, char *pDst, size_t nDstSize,
					  int size, int key, int step, int block, int limit)
{
    char *pInBlock = new char[block];
    char *pOutBlock = new char[block];
    int addup;
	size_t nSrcIndex = 0;
	size_t nDstIndex = 0;
	errno_t err;

	if ((unsigned)size > nSrcSize)
		return;

    addup = size % block;
    if (addup >= block / 4)
        addup = 0;
    addup += size % 2;
    size -= addup;

    while ((size > 0) && (limit > 0))
    {
        if (size < block)
            block = size;

		err = ::memcpy_s(pInBlock, block, &pSrc[nSrcIndex], block);
		nSrcIndex += block;
		if ((err != 0) || (nSrcIndex > nSrcSize))
			return;

        int inIndex = 0;
        for (int j = 0; j < 2; ++j)
        {
            int outIndex = block - j - 1;
            for (int i = 0; i < (block - j + 1) / 2; ++i)
            {
                pOutBlock[outIndex] = (char)(pInBlock[inIndex] ^ key);
                inIndex++;
                outIndex -= 2;
                key += step;
            }
        }

		err = ::memcpy_s(&pDst[nDstIndex], block, pOutBlock, block);
		nDstIndex += block;
		if ((err != 0) || (nDstIndex > nDstSize))
			return;
        limit -= block;
        size -= block;
    }

    size += addup;
    if (size > 0)
    {
		err = ::memcpy_s(&pDst[nDstIndex], size, &pSrc[nSrcIndex], size);
		nSrcIndex += size;
		nDstIndex += size;
		if ((err != 0) || (nSrcIndex > nSrcSize) || (nDstIndex > nDstSize))
			return;
    }
}
