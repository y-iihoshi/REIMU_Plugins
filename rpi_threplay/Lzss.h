#pragma once

class Lzss
{
public:
	static const int DicSize = 0x2000;

	static void Extract(const char *pSrc, size_t nSrcSize, char *pDst, size_t nDstSize);

private:
	Lzss();
	Lzss(const Lzss&);
	Lzss& operator=(const Lzss&);
};
