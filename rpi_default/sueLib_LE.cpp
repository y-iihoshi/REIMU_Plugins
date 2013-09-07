#include "sueLib_LE.h"


//=============================================================================
//		�t�@�C���T�C�Y���擾����
//=============================================================================
// input
//		szFile	: �t�@�C����
//
// return
//		�t�@�C���T�C�Y(���݂��Ȃ��ꍇ��0��Ԃ�)
//
//=============================================================================
DWORD fsize(const char* szFile)
{
	HANDLE	hf;
	DWORD	filesize;

	DWORD	ret = GetFileAttributes(szFile);
	if(ret==0xFFFFFFFF)								return 0;	// �G���[(�p�X��������Ȃ�)
	else if((ret & FILE_ATTRIBUTE_DIRECTORY) != 0)	return 0;	// �f�B���N�g��

	hf = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hf == INVALID_HANDLE_VALUE) return 0;

	filesize = GetFileSize(hf,NULL);
	CloseHandle(hf);

	if(filesize==0xFFFFFFFF)		return 0;	// GetFileSize�̃G���[

	return filesize;
}

//=============================================================================
//		�t�@�C�����烁�����ւ̊ȈՓǂݍ���
//=============================================================================
// input
//		szFile	: �t�@�C����
//		saDest	: �o�͐�
//		dwSize	: �ǂݍ��ރT�C�Y�B�t�@�C���T�C�Y������ɖ����Ȃ���΃G���[
//				  0(�ȗ���)�̎��͂Ƃ肠�����S���ǂݍ���ł���
//		bError	: �t�@�C���T�C�Y��dwSize�ɑ���Ȃ����̋���
//				  true:�G���[��Ԃ�  false:���̕������ǂݍ���(�G���[�ɂ��Ȃ�)
//
// return
//		�ǂݍ��ݐ����������ǂ���
//
//=============================================================================
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize, bool bError)
{
	DWORD filesize = fsize(szFile);
	if(filesize==0)								return false;	// �t�@�C���T�C�Y�擾���s
	else if(dwSize>0 && filesize<dwSize){
		if(bError)	return false;		// �t�@�C���T�C�Y����������
		else		dwSize = filesize;
	}
	else if(dwSize==0 || dwSize>filesize)	dwSize = filesize;	// �����ȗ����Ƃ��̓t�@�C����S���ǂݍ���

	FILE* fp = fopen(szFile, "rb");
	if(!fp)				return false;	// �t�@�C���J���Ȃ�

	saDest.Reset(new char[dwSize], dwSize);

	// �t�@�C���ǂݍ���
	fread(saDest.GetPtr(), saDest.GetSize(), 1, fp);

	fclose(fp);

	return true;
}

/*
//=============================================================================
//		�^�C���X�^���v���擾����
//=============================================================================
// input
//		szFile	: �t�@�C����
//		szDest	: �o�͐�o�b�t�@
//		nType	: �擾������(0:�쐬���� 1:�ŏI�A�N�Z�X���� 2:�X�V����)
//		bDay	: ���t�������o�����ǂ���
//		bTime	: �����������o�����ǂ���
//
// return
//
//=============================================================================
void GetTimeStamp(char* szDest, const char* szFile, int nType, bool bDay, bool bTime)
{
	HANDLE		hf = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	FILETIME	ft[3];
	SYSTEMTIME	st;
	char		time[200], day[200];

	ZeroMemory(time, sizeof(time));
	ZeroMemory(day , sizeof(day));

	if(nType<0 || nType>2)	nType = 2;

	// �t�@�C���̍X�V���Ԃ𒲂ׂ܂�
	if (hf != INVALID_HANDLE_VALUE){
		GetFileTime(hf, &ft[0], &ft[1], &ft[2]);
		CloseHandle(hf);
		FileTimeToSystemTime(&ft[nType], &st);
		sprintf(day , "%04d/%02d/%02d",	st.wYear       , st.wMonth , st.wDay);
		sprintf(time, "%02d:%02d:%02d",	(st.wHour+9)%24, st.wMinute, st.wSecond);
		if(bDay && bTime)	sprintf(szDest, "%s %s", day, time);
		else if(bDay)		strcpy( szDest, day);
		else if(bTime)		strcpy( szDest, time);
		else				strcpy( szDest, "");
	}
	else{
		strcpy(szDest, "");
	}
}

//=============================================================================
//		�t�@�C�������擾(szFile����Q��)
//=============================================================================
// input
//		szFile		: �t�@�C���p�X
//
// return
//		�t�@�C����
//
//=============================================================================
const char* GetFileName(const char* szFile)
{
	char* str = (char*)szFile;	// �߂�l�p
	char* p   = str;	// �J�E���^

	while(*p!='\0'){
		if(*p=='\\' || *p=='/')		str = p + 1;
		p = JmsNext(p);
	}

	return str;
}

//=============================================================================
//		�g���q���擾����(szFile����Q��)
//=============================================================================
// input
//		szFile		: �t�@�C���p�X
//
// return
//		�g���q(���݂��Ȃ��ꍇ�͏I�[��'\0'���Ԃ�)
//
//=============================================================================
const char* GetFileExt(const char* szFile)
{
	char* str  = (char*)GetFileName(szFile);	// �߂�l�p
	char* str1 = str;	// str�̏����l(��r�p)
	char* p    = str;	// �J�E���^

	while(*p!='\0'){
		if(*p=='.')			str = p + 1;
		p = JmsNext(p);
	}

	if(str==str1)		return p;	// �g���q�����݂��Ȃ��ꍇ��'\0'��Ԃ�
	return str;
}

//=============================================================================
//		�t�@�C���̃J�����g�f�B���N�g�����擾
//		("c:\temp\hoge.tmp"�̏ꍇ����"c:\temp")
//=============================================================================
// input
//		szDir		: �f�B���N�g�����i�[�����ꏊ
//		szFile		: �t�@�C���p�X
//
// return
//
//=============================================================================
void GetCurDir(char* szDir, const char* szFile)
{
	// �t�@�C�������Ȃ���szFile�̓f�B���N�g��
	const char* title = GetFileName(szFile);
	if(strlen(title)==0){
		strcpy(szDir, szFile);
		char* p = szDir + strlen(szDir) - 1;	// �Ō��1�o�C�g
		if(IsJms(szDir, p-szDir)==0 && (*p=='\\' || *p=='/')){
			*p = '\0';
			return;
		}
	}
	else{
		int length = strlen(szFile)-strlen(title)-1;
		strncpy(szDir, szFile, length);
		szDir[ length ] = '\0';
		return;
	}

	szDir[0] = '\0';
}

//=============================================================================
//		strcat�̏�����(�ӊO�ɕ֗�(��))
//=============================================================================
// input
//		str1		: ������o�b�t�@
//		format		: ����������
//
// return
//
//=============================================================================
void strcatf(char* str1, const char* format, ...)
{
	char buf[1024*10];

	if(!format){
		format = "Program aborted.";
	}
	ZeroMemory(buf, sizeof(buf));
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	if(str1[0]!='\0')	strcat(str1, buf);
	else				strcpy(str1, buf);
}
void strcatf(char* str1, char* str2)
{
	if(str1[0]!='\0')	strcat(str1, str2);
	else				strcpy(str1, str2);
}

//=============================================================================
//		�ėp�X�v���b�g�֐�
//=============================================================================
// input
//		szSrc		: ���̕�����
//		vecDest		: �o�͐�
//		cSplit		: ��؂蕶��(���p�����̂�)
//		szCmtOut	: �R�����g�A�E�g����(NULL��""�w��Ŗ���)
//
// return
//
//=============================================================================
void Split(const char* szSrc, vector< smart_array<char> > &vecDest, char cSplit, char* szCmtOut)
{
	char* p;	// �J�E���^
	char* str;	// �擪������
	smart_array<char> a;

	p = str = (char*)szSrc;
	vecDest.clear();

	while(*p){
		if(*p==cSplit){
			if(p>str){
				StringCopy(a, str, p-str);
				vecDest.push_back(a);
			}
		//	str =JmsNext(p);	// 1����J�n�ʒu�ɐݒ�
			str = p + 1;
		}
		// �R�����g�A�E�g
		else if(szCmtOut && strlen(szCmtOut)>0 && strlen(p)>=strlen(szCmtOut) &&
			strncmp(p,szCmtOut,strlen(szCmtOut))==0)
		{
			break;
		}

		p = JmsNext(p);
	}

	// �I�[����
	if(p>str){
		StringCopy(a, str, p-str);
		vecDest.push_back(a);
	}
}

//=============================================================================
//		smart_array<char> �ɕ�������R�s�[����
//=============================================================================
// input
//		sa		: �R�s�[��
//		szStr	: ������
//		nLength	: �R�s�[���钷��(0�̎�(�ȗ���)�͑S��)
//
// return
//
//=============================================================================
void StringCopy(smart_array<char>& sa, const char* szStr, int nLength)
{
	if(nLength<=0)	nLength = strlen(szStr);

	sa.Reset(new char[nLength+1], nLength+1);
	strncpy(sa.GetPtr(), szStr, nLength);
	*(sa.GetPtr()+nLength) = '\0';
}

//=============================================================================
//		�{�^���E�`�F�b�N�{�b�N�X�E���W�I�{�^���̏�Ԃ��擾
//=============================================================================
// input
//		hWnd		: �E�B���h�E�n���h��
//
// return
//		�`�F�b�N����Ă��� true �^ �`�F�b�N����ĂȂ� false
//
//=============================================================================
bool BtnGetCheck(HWND hWnd)
{
	if(SendMessage(hWnd, BM_GETCHECK, 0, 0)==BST_CHECKED)	return true;
	return false;
}

//=============================================================================
//		�{�^���E�`�F�b�N�{�b�N�X�E���W�I�{�^�����`�F�b�N����
//=============================================================================
// input
//		hWnd		: �E�B���h�E�n���h��
//		bCheck		: �`�F�b�N���邩���Ȃ���
//
// return
//
//=============================================================================
void BtnSetCheck(HWND hWnd, bool bCheck)
{
	WPARAM wParam = (bCheck) ? BST_CHECKED : BST_UNCHECKED;
//	WPARAM wParam;

//	if(bCheck)	wParam = BST_CHECKED;
//	else		wParam = BST_UNCHECKED;

	SendMessage(hWnd, BM_SETCHECK, wParam, NULL);
}
*/
