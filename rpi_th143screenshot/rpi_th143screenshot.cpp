// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#include <memory>
#include <cstring>
#include <ctime>
#include "rpi_th143screenshot.h"
#include "CTh143ScreenShot.h"
#ifdef RPI_USE_CONFIGDIALOG
# include "CTh12Config.h"
# include "CConfigDialog.h"
#endif


// extern
HINSTANCE hInstance;

#ifdef RPI_USE_CONFIGDIALOG
static CTh12Config config;
#endif


////////////////////////
//		�J�������
////////////////////////
enum
{
	CL_FILENAME,
	CL_LAST_WRITE,
	CL_DAY,
	CL_SCENE,
	CL_DAY_SCENE,
	CL_WIDTH,
	CL_HEIGHT,
	CL_DATE_TIME,
	CL_SLOW_RATE,
	CL_FILESIZE,
	CL_DIRECTORY,

	MAX_COLUMN
};
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"�t�@�C����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"�X�V����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"���t",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�V�[��",			LVCFMT_LEFT,	SORT_NUMBER,	CLSYS_STRING},
	{"���t-�V�[��",		LVCFMT_LEFT,	SORT_NUMBER,	CLSYS_STRING},
	{"��",				LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"����",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"����",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"����������",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"�t�@�C���T�C�Y",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"�f�B���N�g��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	4		// �ő���(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For �e���A�}�m�W���N �X�N���[���V���b�g Ver1.00 (C) IIHOSHI Yoshinori, 2014",
	"�e���A�}�m�W���N �X�N���[���V���b�g",
	"sc*.dat",
	"�e���A�}�m�W���N �X�N���[���t�@�C��(sc*.dat)"
};

// �v���O�C���̏����擾����
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	if ((0 <= nInfoNo) && (nInfoNo < MAX_INFO))
	{
		size_t length = std::strlen(szPluginInfo[nInfoNo]);
		if (szDst == NULL)
			return length;
		else
			if (dwDstLength > length)
				return (::strcpy_s(szDst, dwDstLength, szPluginInfo[nInfoNo]) == 0) ? length : 0;
	}

	return 0;
}

// �J�������̎擾
int GetColumnInfoEx(ColumnInfo** lpInfo)
{
	if (lpInfo == NULL)
		return RPI_UNKNOWN_ERROR;

	size_t size = sizeof(ColumnInfo) * (MAX_COLUMN + 1);

	*lpInfo = (ColumnInfo *)::LocalAlloc(LPTR, size);
	if (*lpInfo == NULL)
		return RPI_NO_MEMORY;

	return (::memcpy_s(*lpInfo, size, Column, size) == 0) ? RPI_ALL_RIGHT : RPI_UNKNOWN_ERROR;
}

// �Ή����Ă��邩�ǂ���(�Ή����Ă���Δ�0��Ԃ�)
// �t�@�C�����Ŕ��肷�邱�Ƃ����邩������Ȃ��̂Ńt�@�C�������ꉞ�����Ƃ�
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile)
{
	return CTh143ScreenShot().IsSupported(pSrc, dwSize);
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	if ((pSrc == NULL) || (lpInfo == NULL))
		return RPI_UNKNOWN_ERROR;

	CTh143ScreenShot screenshot;

	if (!screenshot.IsSupported(pSrc, dwSize))
		return RPI_NOT_SUPPORT;

	*lpInfo = (FileInfo *)::LocalAlloc(LPTR, sizeof(FileInfo) * MAX_COLUMN);
	if (*lpInfo == NULL)
		return RPI_NO_MEMORY;

	std::unique_ptr<CTh143ScreenShot::Info> info(screenshot.GetInfo(pSrc, dwSize));
	if (info.get() == NULL)
		return RPI_FILE_READ_ERROR;

	const char *szDays[] = {
		"�����", "�����", "�O����", "�l����", "�ܓ���", "�Z����", "������", "������", "�����", "�ŏI��"
	};

	FileInfo *pInfo = *lpInfo;
	::sprintf_s(pInfo[CL_DAY].szText, "%s", szDays[info->day]);
	::sprintf_s(pInfo[CL_SCENE].szText, "%d", info->scene + 1);
	::sprintf_s(pInfo[CL_DAY_SCENE].szText, "%d-%d", info->day + 1, info->scene + 1);
	::sprintf_s(pInfo[CL_WIDTH].szText, "%d", info->width);
	::sprintf_s(pInfo[CL_HEIGHT].szText, "%d", info->height);
	time_t time = (time_t)info->dateTime;
	tm ts;
	::localtime_s(&ts, &time);
	std::strftime(pInfo[CL_DATE_TIME].szText, sizeof(pInfo[CL_DATE_TIME].szText), "%Y/%m/%d %H:%M:%S", &ts);
	::sprintf_s(pInfo[CL_SLOW_RATE].szText, "%.6f", info->slowRate);

	return RPI_ALL_RIGHT;
}


////////////////////////
//		�C�ӊ֐�
////////////////////////
#if defined(RPI_USE_GETFILEINFOTEXT1) || defined(RPI_USE_GETFILEINFOTEXT2)
// �����E�E���̃e�L�X�g���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	CTh143ScreenShot screenshot;
	size_t nDstSize;
	int retval;

	switch (nType)
	{
#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:
		retval = screenshot.GetInfo(pSrc, dwSize, pDst, &nDstSize);
		switch (retval)
		{
		case RET_OK:
			return RPI_ALL_RIGHT;
		case RET_ERR_NOMEM:
			return RPI_NO_MEMORY;
		case RET_ERR_READ:
			return RPI_FILE_READ_ERROR;
		default:
			return RPI_UNKNOWN_ERROR;
		}
#endif
#ifdef RPI_USE_GETFILEINFOTEXT2
	case 2:
		return RPI_NO_FUNCTION;
#endif
	default:
		return RPI_NO_FUNCTION;
	}
}
#endif

// �����E�E���̉摜���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile)
{
	CTh143ScreenShot screenshot;
	int retval;

	switch(nType){

#ifdef RPI_USE_GETFILEINFOIMAGE1
	case 1:		// ����
		return RPI_NO_FUNCTION;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE1

#ifdef RPI_USE_GETFILEINFOIMAGE2
	case 2:		// �E��
		retval = screenshot.GetPicture(pSrc, dwSize, pDst, pInfo);
		switch (retval)
		{
		case RET_OK:
			return RPI_ALL_RIGHT;
		case RET_ERR_NOMEM:
			return RPI_NO_MEMORY;
		case RET_ERR_READ:
			return RPI_FILE_READ_ERROR;
		default:
			return RPI_UNKNOWN_ERROR;
		}
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE2
	default:
		return RPI_NO_FUNCTION;
	}
}

#ifdef RPI_USE_EDITDIALOG
// �ҏW�_�C�A���O
// (�t�@�C�����̓I�����[)

int EditDialogEx(HWND hWnd, const char* szFile)
{
	return (CEditDialog(szFile).Show(hInstance, hWnd) == IDOK) ? 0 : 1;
}
#endif

#ifdef RPI_USE_CONFIGDIALOG
// �ݒ�_�C�A���O
int ConfigDialogEx(HWND hWnd)
{
	return (CConfigDialog(&config).Show(hInstance, hWnd) == IDOK) ? 0 : 1;
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

#ifdef RPI_USE_CONFIGDIALOG
	// �ݒ��ǂݍ���
	config.Load(hInstance);
#endif
}

