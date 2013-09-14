/*
自分用のライブラリ"sueLib"からREIMUプラグイン用に必要な部分だけ切り出してきたやつ
(sueLib_File.cppとかsueLib_String.cppとかで分割してはいるんですがそれでも多すぎるのでｗ)
*/
#ifndef _INC_SUELIB_LE
#define _INC_SUELIB_LE

#include <windows.h>
#include <stdio.h>
#include "smart_array.h"

DWORD fsize(const char* szFile);
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize=0, bool bError=true);

#endif
