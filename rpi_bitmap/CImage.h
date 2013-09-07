// �摜�ǂݍ��݌n
#ifndef _INC_CIMAGE
#define _INC_CIMAGE


#include <windows.h>

// �C���^�[�t�F�[�X����
class IImage{
public:
	IImage(){}
	~IImage(){}

	virtual int IsSupported(const char* pSrc, DWORD dwSize, const char* szFile)
	{
		return 0;
	}
	virtual bool GetPictureInfo(const char* pSrc, DWORD dwSize, BITMAPINFOHEADER* lpHeader)
	{
		return false;
	}
	virtual bool GetPicture(const char* pSrc, DWORD dwSize, char** pDst, BITMAPINFO** lpInfo)
	{
		return false;
	}
};

// �r�b�g�}�b�v
class CBmp : private IImage{
public:
	CBmp(){}
	~CBmp(){}

	int  IsSupported(const char* pSrc, DWORD dwSize, const char* szFile="");
	bool GetPictureInfo(const char* pSrc, DWORD dwSize, BITMAPINFOHEADER* pHeader);
	bool GetPicture(const char* pSrc, DWORD dwSize, char** pDst, BITMAPINFO** pInfo);
};

#endif
