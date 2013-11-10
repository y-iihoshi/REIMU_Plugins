#pragma once

class BitReader
{
private:
	const char *pSrc;
	size_t nSrcIndex;
	size_t nSrcSize;
	bool disposed;
	int current;
	unsigned char mask;

public:
	BitReader(const char *pSrc, size_t nSrcSize);
	~BitReader();

	void Dispose();
	int ReadBits(int num);

protected:
	virtual void Dispose(bool disposing);
};
