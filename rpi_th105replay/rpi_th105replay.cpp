// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#include <memory>
#include <cstring>
#include "rpi_th105replay.h"
#include "CTh105Replay.h"
#include "StringMaps.h"
#ifdef RPI_USE_EDITDIALOG
#include "CEditDialog.h"
#endif
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
	CL_VERSION,
	CL_MODE,
	CL_PLAYER1,
	CL_COLOR1,
	CL_PLAYER2,
	CL_COLOR2,
	CL_STAGE,
	CL_BGM,
	CL_FILESIZE,
	CL_DIRECTORY,

	MAX_COLUMN
};
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"�t�@�C����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"�X�V����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"�o�[�W����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"���[�h",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�v���C���[ 1",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�F 1",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"�v���C���[ 2",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�F 2",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"�X�e�[�W",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"BGM",				LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�t�@�C���T�C�Y",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"�f�B���N�g��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	4		// �ő���(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For ������z�V Ver1.00 (C) IIHOSHI Yoshinori, 2014",
	"������z�V",
	"*.rep",
	"������z�V ���v���C�t�@�C��(*.rep)"
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
	return CTh105Replay().IsSupported(pSrc, dwSize);
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	if ((pSrc == NULL) || (lpInfo == NULL))
		return RPI_UNKNOWN_ERROR;

	CTh105Replay replay;

	if (!replay.IsSupported(pSrc, dwSize))
		return RPI_NOT_SUPPORT;

	*lpInfo = (FileInfo *)::LocalAlloc(LPTR, sizeof(FileInfo) * MAX_COLUMN);
	if (*lpInfo == NULL)
		return RPI_NO_MEMORY;

	std::unique_ptr<CTh105Replay::Info> info(replay.GetInfo(pSrc, dwSize));
	if (info.get() == NULL)
		return RPI_FILE_READ_ERROR;

	FileInfo *pInfo = (FileInfo *)*lpInfo;
	::sprintf_s(pInfo[CL_VERSION].szText, "%s", Th105::GetString(Th105::Versions, info->versionId).c_str());
	::sprintf_s(pInfo[CL_MODE   ].szText, "%s", Th105::GetString(Th105::Modes, info->mode).c_str());
	::sprintf_s(pInfo[CL_PLAYER1].szText, "%s",
		Th105::GetString(Th105::Characters, info->pDeck1->chara).c_str());
	::sprintf_s(pInfo[CL_COLOR1 ].szText, "%hhd", info->pDeck1->color);
	if (info->mode != Th105::Mode::Story)
	{
		::sprintf_s(pInfo[CL_PLAYER2].szText, "%s",
			Th105::GetString(Th105::Characters, info->pDeck2->chara).c_str());
		::sprintf_s(pInfo[CL_COLOR2 ].szText, "%hhd", info->pDeck2->color);
		::sprintf_s(pInfo[CL_STAGE  ].szText, "%s", Th105::GetString(Th105::Stages, info->stageId).c_str());
		::sprintf_s(pInfo[CL_BGM    ].szText, "%s", Th105::GetString(Th105::Bgms, info->bgmId).c_str());
	}
	else
	{
		::sprintf_s(pInfo[CL_PLAYER2].szText, "-");
		::sprintf_s(pInfo[CL_COLOR2 ].szText, "-");
		::sprintf_s(pInfo[CL_STAGE  ].szText, "-");
		::sprintf_s(pInfo[CL_BGM    ].szText, "-");
	}

	return RPI_ALL_RIGHT;
}


////////////////////////
//		�C�ӊ֐�
////////////////////////
// �����E�E���̃e�L�X�g���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	CTh105Replay replay;
	char *pDst2;
	size_t nDstSize;
	int retval;

	switch (nType)
	{
#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:
		retval = replay.GetPlayerInfo(1, pSrc, dwSize, &pDst2, &nDstSize);
		break;
#endif
#ifdef RPI_USE_GETFILEINFOTEXT2
	case 2:
		retval = replay.GetPlayerInfo(2, pSrc, dwSize, &pDst2, &nDstSize);
		break;
#endif
	default:
		return RPI_NO_FUNCTION;
	}

	switch (retval)
	{
	case RET_OK:
		*pDst = (char *)::LocalAlloc(LPTR, nDstSize);
		if (*pDst == NULL)
			return RPI_NO_MEMORY;
		::memcpy_s(*pDst, nDstSize, pDst2, nDstSize);
		if (nType == 1)
			::LocalFree(pDst2);
		return RPI_ALL_RIGHT;
	case RET_ERR_PARAM:
	case RET_ERR_READ:
		return RPI_FILE_READ_ERROR;
	case RET_ERR_NOMEM:
		return RPI_NO_MEMORY;
	default:
		return RPI_UNKNOWN_ERROR;
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

