#include "CImage.h"


// 対応しているかどうか
int CBmp::IsSupported(const char* pSrc, DWORD dwSize, const char* szFile)
{
	const char*				pHeader = pSrc;
	const BITMAPINFOHEADER*	pInfo   = (BITMAPINFOHEADER*)(pSrc + sizeof(BITMAPFILEHEADER));
	const BITMAPCOREHEADER*	pCore   = (BITMAPCOREHEADER*)(pSrc + sizeof(BITMAPFILEHEADER));

	if(pHeader[0]=='B' && pHeader[1]=='M'){
		// WIN
		if(pInfo->biSize==sizeof(BITMAPINFOHEADER)){
			switch(pInfo->biBitCount){
			case 8: case 16: case 24: case 32:
				return 1;
			}
		}
		// OS/2
		else if(pInfo->biSize==sizeof(BITMAPCOREHEADER)){
			switch(pCore->bcBitCount){
			case 8: case 24:
				return 2;
			}
		}
	}

	return 0;
}

// 画像情報の取得
bool CBmp::GetPictureInfo(const char* pSrc, DWORD dwSize, BITMAPINFOHEADER* pHeader)
{
	const BITMAPINFOHEADER*	pInfo   = (BITMAPINFOHEADER*)(pSrc + sizeof(BITMAPFILEHEADER));
	const BITMAPCOREHEADER*	pCore   = (BITMAPCOREHEADER*)(pSrc + sizeof(BITMAPFILEHEADER));


	switch(IsSupported(pSrc, dwSize)){
	case 1:		// WIN
		memcpy(pHeader, pInfo, sizeof(BITMAPINFOHEADER));
		break;
	case 2:		// OS/2
		ZeroMemory(pHeader, sizeof(BITMAPINFOHEADER));
		pHeader->biSize				= sizeof(BITMAPINFOHEADER);
		pHeader->biWidth			= pCore->bcWidth;
		pHeader->biHeight			= pCore->bcHeight;
		pHeader->biPlanes			= 1;
		pHeader->biBitCount			= pCore->bcBitCount;
		pHeader->biCompression		= BI_RGB;
		pHeader->biSizeImage		= 0;
		pHeader->biXPelsPerMeter	= 0;
		pHeader->biYPelsPerMeter	= 0;
		if(pHeader->biBitCount <= 8)	pHeader->biClrUsed = (2 << pHeader->biBitCount);
		else							pHeader->biClrUsed = 0;
		pHeader->biClrImportant = 0;
		break;
	default:
		return false;
	}

	return true;
}

// 画像本体の読み込み
bool CBmp::GetPicture(const char* pSrc, DWORD dwSize, char** pDst, BITMAPINFO** pInfo)
{
	int i;
	DWORD dwInfoSize, dwImgSize, dwLineSize, dwPalNum;
	BITMAPINFOHEADER	bmiHeader;

	const BITMAPFILEHEADER* pHeader = (BITMAPFILEHEADER*)pSrc;

	if(!GetPictureInfo(pSrc, dwSize, &bmiHeader))	return false;

	dwInfoSize = sizeof(BITMAPINFOHEADER);
	if(bmiHeader.biBitCount<=8){
		dwPalNum = 2<<bmiHeader.biBitCount;
		dwInfoSize += sizeof(RGBQUAD) * dwPalNum;
	}
	else{
		dwPalNum = 0;
	}
	dwLineSize = (bmiHeader.biWidth * (bmiHeader.biBitCount / 8) +3) & ~3; /*4byte境界*/
	dwImgSize  = dwLineSize * abs(bmiHeader.biHeight);
	if(dwSize < pHeader->bfOffBits + dwImgSize)		return false;	// 画像ファイル小さすぎ

	*pInfo = (BITMAPINFO*)LocalAlloc(LPTR, dwInfoSize);
	*pDst  = (char*)      LocalAlloc(LPTR, dwImgSize);

	memcpy(*pInfo, &bmiHeader, sizeof(BITMAPINFOHEADER));

	switch(IsSupported(pSrc, dwSize)){
	case 1:		// WIN
		{
			RGBQUAD		*p1, *p2;
			p1 = (RGBQUAD*)(pSrc+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));	// 入力
			p2 = (RGBQUAD*)((char*)*pInfo+sizeof(BITMAPINFOHEADER));							// 出力
			for(i = 0; i < (int)dwPalNum; i++){
				memcpy(p2++, p1++, sizeof(RGBQUAD));
			}
		}
		break;
	case 2:		// OS/2
		{
			RGBTRIPLE	*p1;
			RGBQUAD		*p2;
			p1 = (RGBTRIPLE*)(pSrc+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPCOREHEADER));	// 入力
			p2 = (RGBQUAD*)(*pInfo+sizeof(BITMAPINFOHEADER));							// 出力
			for(i = 0; i < (int)dwPalNum; i++){
				memcpy(p2++, p1++, sizeof(RGBTRIPLE));
			}
		}
		break;
	}

	memcpy(*pDst, pSrc+pHeader->bfOffBits, dwImgSize);

	return true;
}
