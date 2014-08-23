#pragma once

#include "reimu_plugin.h"

// �v���O�C�����Ƃ̓Ǝ��̏���������֐�

// �K�{�֐�
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength);
int GetColumnInfoEx(ColumnInfo** lpInfo);
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile="");
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile="");

// �C�ӊ֐�
#if defined(RPI_USE_GETFILEINFOTEXT1) || defined(RPI_USE_GETFILEINFOTEXT2)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile="");
#endif
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
#define HEADER_SIZE		2
