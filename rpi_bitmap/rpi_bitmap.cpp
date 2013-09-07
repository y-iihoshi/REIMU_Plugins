// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#include "rpi_bitmap.h"


// extern
HINSTANCE hInstance;


////////////////////////
//		�J�������
////////////////////////
enum{
	CL_FILENAME,
	CL_WIDTH,
	CL_HEIGHT,
	CL_BITCOUNT,
	CL_FILESIZE,
	CL_LAST_WRITE,
	CL_DIRECTORY,

	MAX_COLUMN,
};
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN+1] = {
	{"�t�@�C����"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TITLE},
	{"��"				, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"����"				, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"�r�b�g��"			, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"�t�@�C���T�C�Y"	, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_FILESIZE},
	{"�X�V����"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTWRITE},
	{"�f�B���N�g��"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_DIRECTORY},
//	{"", LVCFMT_, SORT_, CLSYS_},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	4		// �ő���(2+2*n)

// �v���O�C���̏����擾����
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	const char* szInfo[MAX_INFO] = {
		"REIMU Image Plug-in Ver1.00 (C)sue445, 2005",
		"�r�b�g�}�b�v",
		"*.bmp",
		"�r�b�g�}�b�v�t�@�C��(*.bmp)",
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
	if(dwSize<HEADER_SIZE)		return 0;	// �o�b�t�@�T�C�Y��������

	CBmp bmp;
	return bmp.IsSupported(pSrc, dwSize);
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	CBmp bmp;
	BITMAPINFOHEADER	bmiHeader;

	if(!bmp.GetPictureInfo(pSrc, dwSize, &bmiHeader))	return RPI_NOT_SUPPORT;

	// �������m��
	*lpInfo = (FileInfo*)LocalAlloc(LPTR, sizeof(FileInfo) * (MAX_COLUMN));
	if(*lpInfo==NULL)			return RPI_NO_MEMORY;		// �������m�ۂł��Ȃ�

	ZeroMemory(*lpInfo, sizeof(FileInfo) * (MAX_COLUMN));


	FileInfo *pinfo = (FileInfo*)*lpInfo;
	sprintf(pinfo[CL_WIDTH].szText		, "%u", bmiHeader.biWidth);
	sprintf(pinfo[CL_HEIGHT].szText		, "%u", bmiHeader.biHeight);
	sprintf(pinfo[CL_BITCOUNT].szText	, "%u", bmiHeader.biBitCount);

	return RPI_ALL_RIGHT;
}


////////////////////////
//		�C�ӊ֐�
////////////////////////
// �����E�E���̃e�L�X�g���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	switch(nType){

#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:		// ����
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOTEXT2
	case 2:		// �E��
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2

	// RPI_USE_GETFILEINFOTEXT1��RPI_USE_GETFILEINFOTEXT2��
	// ������`����ĂȂ����̂��߂Ƀ_�~�[�œ���Ă���(^^;
	case 0:
		break;
	}

	return RPI_NO_FUNCTION;
}

// �����E�E���̉摜���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile)
{
	CBmp bmp;

	switch(nType){

#ifdef RPI_USE_GETFILEINFOIMAGE1
	case 1:		// ����
		if(!bmp.GetPicture(pSrc, dwSize, pDst, pInfo))	return RPI_NOT_SUPPORT;

		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE1

#ifdef RPI_USE_GETFILEINFOIMAGE2
	case 2:		// �E��
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE2

	// RPI_USE_GETFILEINFOIMAGE1��RPI_USE_GETFILEINFOIMAGE2��
	// ������`����ĂȂ����̂��߂Ƀ_�~�[�œ���Ă���(^^;
	case 0:
		break;
	}

	return RPI_NO_FUNCTION;
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

	// �ݒ��ǂݍ���
//	LoadConfig();
}

