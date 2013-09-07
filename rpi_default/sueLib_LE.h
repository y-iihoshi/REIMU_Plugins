/*
自分用のライブラリ"sueLib"からREIMUプラグイン用に必要な部分だけ切り出してきたやつ
(sueLib_File.cppとかsueLib_String.cppとかで分割してはいるんですがそれでも多すぎるのでｗ)
*/
#ifndef _INC_SUELIB_LE
#define _INC_SUELIB_LE

#include <windows.h>
#include <stdio.h>
#include "smart_array.h"
/*
#include <vector>

#include "sueLib_base.h"

using std::vector;
*/

DWORD fsize(const char* szFile);
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize=0, bool bError=true);
/*
void GetTimeStamp(char* szDest, const char* szFile, int nType=2, bool bDay=true, bool bTime=true);
const char* GetFileName(const char* szFile);
const char* GetFileExt( const char* szFile);
void GetCurDir(char* szDir, const char* szFile);
void strcatf(char* str1, const char* format, ...);
void strcatf(char* str1, char* str2);
void Split(const char* szSrc, vector< smart_array<char> > &vecDest, char cSplit, char* szCmtOut=NULL);
void StringCopy(smart_array<char>& sa, const char* szStr, int nLength=0);
bool BtnGetCheck(HWND hWnd);
void BtnSetCheck(HWND hWnd, bool bCheck);
*/

#endif
