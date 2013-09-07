// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#ifndef _INC_RPI_DEFAULT
#define _INC_RPI_DEFAULT

#include "reimu_plugin.h"
#include "sueLib_LE.h"
#include "CImage.h"


// �v���O�C�����Ƃ̓Ǝ��̏���������֐�

// �K�{�֐�
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength);
int GetColumnInfoEx(ColumnInfo** lpInfo);
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile="");
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile="");

// �C�ӊ֐�
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile="");
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile="");
#ifdef RPI_USE_EDITDIALOG
int EditDialogEx(HWND hWnd, const char* szFile);
#endif
#ifdef RPI_USE_CONFIGDIALOG
int ConfigDialogEx(HWND hWnd);
#endif

// ���̑��̓����g�p�֐�
void LoadPlugin(HINSTANCE hInst);

// extern
extern	HINSTANCE hInstance;


// �t�@�C�����ʗp�ɍŒ���K�v�ȃo�C�g��
#define HEADER_SIZE		(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER))

#endif
