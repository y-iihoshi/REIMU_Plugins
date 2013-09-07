// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.1)
#include "rpi_default.h"


// extern
HINSTANCE hInstance;


////////////////////////
//		�J�������
////////////////////////
enum{
	CL_FILENAME,
	CL_FILESIZE,
	CL_TIME_CREATE,
	CL_LAST_ACCESS,
	CL_LAST_WRITE,
	CL_EXT,
	CL_FILEPATH,
	CL_DIRECTORY,

	MAX_COLUMN,
};
#define MAX_COLUMN		8
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN+1] = {
	{"�t�@�C����"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TITLE},
	{"�t�@�C���T�C�Y"	, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_FILESIZE},
	{"�쐬����"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_CREATE},
	{"�A�N�Z�X����"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTACCESS},
	{"�X�V����"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTWRITE},
	{"�g���q"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_EXT},
	{"�t�@�C���p�X"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_PATH},
	{"�f�B���N�g��"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_DIRECTORY},
//	{"", LVCFMT_, SORT_, CLSYS_},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	2		// �ő���(2+2*n)

// �v���O�C���̏����擾����
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	const char* szInfo[MAX_INFO] = {
		"REIMU Default Plug-in Ver1.00 (C)sue445, 2005",
		"�f�t�H���g",
//		"*.*",
//		"�S�Ẵt�@�C��(*.*)",
	};

	if(nInfoNo>=0 && nInfoNo<MAX_INFO){
		if(szDst==NULL){
			return strlen(szInfo[nInfoNo]);
		}
		else if(dwDstLength > strlen(szInfo[nInfoNo])){
			strcpy(szDst, szInfo[nInfoNo]);
			return strlen(szInfo[nInfoNo]);
		}
	}

	return 0;
}

// �J�������̎擾
int GetColumnInfoEx(ColumnInfo** lpInfo)
{
	// �������m��
	*lpInfo = (ColumnInfo*)LocalAlloc(LPTR, sizeof(ColumnInfo) * (MAX_COLUMN+1));
	if(*lpInfo==NULL)	return RPI_NO_MEMORY;		// �������m�ۂł��Ȃ�

	memcpy(*lpInfo, Column, sizeof(ColumnInfo) * (MAX_COLUMN+1));

	return RPI_ALL_RIGHT;
}

// �Ή����Ă��邩�ǂ���(�Ή����Ă���Δ�0��Ԃ�)
// �t�@�C�����Ŕ��肷�邱�Ƃ����邩������Ȃ��̂Ńt�@�C�������ꉞ�����Ƃ�
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile)
{
	if(dwSize<HEADER_SIZE)							return 0;	// �o�b�t�@�T�C�Y��������
//	else if(strlen(szFile)>0 && !ExtCheck(szFile))	return 0;	// �g���q��v���Ȃ�
//	else if(memcmp(pSrc, "T8RP", HEADER_SIZE)!=0)	return 0;	// �w�b�_��v���Ȃ�

	return 1;
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	// �������m��
	*lpInfo = (FileInfo*)LocalAlloc(LPTR, sizeof(FileInfo) * (MAX_COLUMN));
	if(*lpInfo==NULL)			return RPI_NO_MEMORY;		// �������m�ۂł��Ȃ�

	ZeroMemory(*lpInfo, sizeof(FileInfo) * (MAX_COLUMN));


// ���̃v���O�C���ł͏��̎擾�͂���܂��񂪁A�ʏ�͉��̂悤�ɂ��Ƃ�����������܂���
//	FileInfo *pinfo = (FileInfo*)*lpInfo;
//	strcpy(pinfo[CL_INFO].szText, "Hoge");

	return RPI_ALL_RIGHT;
}


////////////////////////
//		�C�ӊ֐�
////////////////////////
// �����E�E���̏��(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	/*
	//	RPI_USE_GETFILEINFOTEXTT1��RPI_USE_GETFILEINFOTEXTT2�������Ȃ���
	//	switch���̒���default�����ɂȂ��Ă��܂��Ă������ɂ܂����̂ŃR�����g�A�E�g���Ă�����

	switch(nType){

#ifdef RPI_USE_GETFILEINFOTEXTT1
	case 1:		// ����
		break;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXTT1

#ifdef RPI_USE_GETFILEINFOTEXTT2
	case 2:		// �E��
		break;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXTT2

	default:
		return RPI_NO_FUNCTION;
	}
	*/
	return RPI_NO_FUNCTION;

	return RPI_ALL_RIGHT;
}

#ifdef RPI_USE_EDITDIALOG
// �ҏW�_�C�A���O
// (�t�@�C�����̓I�����[)
int EditDialogEx(HWND hWnd, const char* szFile)
{
	return 0;
}
#endif

#ifdef RPI_USE_CONFIGDIALOG
// �ݒ�_�C�A���O
int ConfigDialogEx(HWND hWnd)
{
	return OpenConfigDialog(hWnd);
}
#endif


//////////////////////////////////
//		���̑��̓����g�p�֐�
//////////////////////////////////
// �v���O�C�������[�h���ꂽ���Ɉ�x�������s�����֐�(�����Őݒ��ǂݍ��񂾂肷��)
void LoadPlugin(HINSTANCE hInst)
{
	// �R���t�B�O�_�C�A���O�p�ɃC���X�^���X���擾
	hInstance = hInst;
}
