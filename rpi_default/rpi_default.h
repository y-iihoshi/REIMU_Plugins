// プラグインごとの独自の処理をする部分(Rev.1)
#ifndef _INC_RPI_DEFAULT
#define _INC_RPI_DEFAULT

#include "reimu_plugin.h"
#include "sueLib_LE.h"


// プラグインごとの独自の処理をする関数

// 必須関数
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength);
int GetColumnInfoEx(ColumnInfo** lpInfo);
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile="");
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile="");

// 任意関数
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile="");
#ifdef RPI_USE_EDITDIALOG
int EditDialogEx(HWND hWnd, const char* szFile);
#endif
#ifdef RPI_USE_CONFIGDIALOG
int ConfigDialogEx(HWND hWnd);
#endif

// その他の内部使用関数
void LoadPlugin(HINSTANCE hInst);

// extern
extern	HINSTANCE hInstance;


// ファイル識別用に最低限必要なバイト数
#define HEADER_SIZE		1

#endif
