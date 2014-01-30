#include <cstring>
#include "Lzss.h"
#include "BitReader.h"

void Lzss::Extract(const char *pSrc, size_t nSrcSize, char *pDst, size_t nDstSize)
{
	BitReader reader(pSrc, nSrcSize);
	unsigned char dictionary[DicSize];
	int dicIndex = 1;
	size_t dstIndex = 0;

	std::memset(dictionary, 0, sizeof(dictionary));

	while (dicIndex < DicSize)
	{
		int flag = reader.ReadBits(1);
		if (flag != 0)
		{
			unsigned char ch = (unsigned char)reader.ReadBits(8);
			pDst[dstIndex++] = ch;
			if (dstIndex >= nDstSize)
				break;
			dictionary[dicIndex] = ch;
			dicIndex = (dicIndex + 1) & 0x1FFF;
		}
		else
		{
			int offset = reader.ReadBits(13);
			if (offset == 0)
				break;
			else
			{
				int length = reader.ReadBits(4) + 3;
				for (int i = 0; i < length; i++)
				{
					unsigned char ch = dictionary[(offset + i) & 0x1FFF];
					pDst[dstIndex++] = ch;
					if (dstIndex >= nDstSize)
						break;
					dictionary[dicIndex] = ch;
					dicIndex = (dicIndex + 1) & 0x1FFF;
				}
			}
		}
	}
}
