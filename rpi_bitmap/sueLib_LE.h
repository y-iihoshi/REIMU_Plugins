/*
�����p�̃��C�u����"sueLib"����REIMU�v���O�C���p�ɕK�v�ȕ��������؂�o���Ă������
(sueLib_File.cpp�Ƃ�sueLib_String.cpp�Ƃ��ŕ������Ă͂����ł�������ł���������̂ł�)
*/
#ifndef _INC_SUELIB_LE
#define _INC_SUELIB_LE

#include <windows.h>
#include <stdio.h>
#include "smart_array.h"

DWORD fsize(const char* szFile);
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize=0, bool bError=true);

#endif
