#include <cstdio>
#include "BitReader.h"

BitReader::BitReader(const char *pSrc, size_t nSrcSize)
	: pSrc(pSrc), nSrcSize(nSrcSize)
{
	this->nSrcIndex = 0;
	this->disposed = ((pSrc == NULL) || (nSrcSize == 0));
	this->current = 0;
	this->mask = 0x80;
}

BitReader::~BitReader()
{
	this->Dispose(false);
}

void BitReader::Dispose()
{
	this->Dispose(true);
}

void BitReader::Dispose(bool disposing)
{
	if (!this->disposed)
	{
		if (disposing)
		{
			this->pSrc = NULL;
			this->nSrcSize = 0;
		}
		this->disposed = true;
	}
}

int BitReader::ReadBits(int num)
{
	if (!this->disposed)
	{
		int value = 0;
		for (int i = 0; i < num; i++)
		{
			if (this->mask == 0x80)
			{
				this->current = this->pSrc[this->nSrcIndex++];
				if (this->nSrcIndex >= this->nSrcSize)
					this->current = 0;
			}
			value <<= 1;
			if (((unsigned char)this->current & this->mask) != 0)
				value |= 1;
			this->mask >>= 1;
			if (this->mask == 0)
				this->mask = 0x80;
		}
		return value;
	}
	else
	{
		return -1;
	}
}
