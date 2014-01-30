#pragma once

class ThCrypt
{
public:
	static void Decrypt(
		const char *pSrc, size_t nSrcSize, char *pDst, size_t nDstSize,
		int size, int key, int step, int block, int limit);
};
