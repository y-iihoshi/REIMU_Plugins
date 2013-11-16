// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#include <memory>
#include <cstring>
#include "rpi_th11replay.h"
#include "CTh11Replay.h"
#include "CEditDialog.h"
#ifdef RPI_USE_CONFIGDIALOG
# include "CTh11Config.h"
# include "CConfigDialog.h"
#endif


// extern
HINSTANCE hInstance;

#ifdef RPI_USE_CONFIGDIALOG
static CTh11Config config;
#endif


////////////////////////
//		�J�������
////////////////////////
enum
{
	CL_FILENAME,
	CL_LAST_WRITE,
	CL_NUMBER,
	CL_PLAYER,
	CL_PLAY_TIME,
	CL_CHARACTER,
	CL_LEVEL,
	CL_STAGE,
	CL_SCORE,
	CL_SLOW_RATE,
	CL_VERSION,
	CL_COMMENT,
	CL_FILESIZE,
	CL_DIRECTORY,

	MAX_COLUMN
};
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"�t�@�C����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"�X�V����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"No.",				LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�v���C���[��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�v���C����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�g�p�L����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"��Փx",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�X�e�[�W",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�X�R�A",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"����������",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"�o�[�W����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�R�����g",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�t�@�C���T�C�Y",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"�f�B���N�g��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	4		// �ő���(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For �����n��a Ver0.01 (C) IIHOSHI Yoshinori, 2013",
	"�����n��a_Test",
	"th11_*.rpy",
	"�����n��a ���v���C�t�@�C��(th11_*.rpy)"
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
	return CTh11Replay().IsSupported(pSrc, dwSize);
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	if ((pSrc == NULL) || (lpInfo == NULL))
		return RPI_UNKNOWN_ERROR;

	CTh11Replay replay;

	if (!replay.IsSupported(pSrc, dwSize))
		return RPI_NOT_SUPPORT;

	*lpInfo = (FileInfo *)::LocalAlloc(LPTR, sizeof(FileInfo) * MAX_COLUMN);
	if (*lpInfo == NULL)
		return RPI_NO_MEMORY;

	std::unique_ptr<CTh11Replay::Info> info(replay.GetInfo(pSrc, dwSize));
	const char *pComment = NULL;
	size_t nCommentSize = 0;
	int retval = (info.get() != NULL)
		? replay.GetComment(pSrc, dwSize, &pComment, &nCommentSize) : RET_ERR_READ;

	switch (retval)
	{
	case RET_OK:
		{
			FileInfo *pInfo = (FileInfo *)*lpInfo;
			int numType;
			char number[5];
			if (replay.GetNumber(szFile, &numType, number, sizeof(number)) == RET_OK)
				switch (numType)
				{
				case CTh11Replay::NUM_TYPE_BASIC:
					::sprintf_s(pInfo[CL_NUMBER].szText, "No.%2s", number);
					break;
				case CTh11Replay::NUM_TYPE_USER:
					::sprintf_s(pInfo[CL_NUMBER].szText, "User");
					break;
				default:
					::sprintf_s(pInfo[CL_NUMBER].szText, "----");
					break;
				}
			::sprintf_s(pInfo[CL_PLAYER].szText, "%s", info->pszName);
			::sprintf_s(pInfo[CL_PLAY_TIME].szText, "%s", info->pszDate);
			::sprintf_s(pInfo[CL_CHARACTER].szText, "%s", info->pszChara);
			::sprintf_s(pInfo[CL_LEVEL].szText, "%s", info->pszRank);
			::sprintf_s(pInfo[CL_STAGE].szText, "%s", info->pszStage);
			::sprintf_s(pInfo[CL_SCORE].szText, "%s", info->pszScore);
			::sprintf_s(pInfo[CL_SLOW_RATE].szText, "%s", info->pszSlowRate);
			::sprintf_s(pInfo[CL_VERSION].szText, "%s", info->pszVersion);
			::sprintf_s(pInfo[CL_COMMENT].szText, "%s", pComment);
		}
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


////////////////////////
//		�C�ӊ֐�
////////////////////////
// �����E�E���̃e�L�X�g���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	CTh11Replay replay;
	const char *pConstDst;
	size_t nDstSize;
	int retval;

	switch (nType)
	{
#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:
		retval = replay.GetInfo(pSrc, dwSize, &pConstDst, &nDstSize);
		break;
#endif
#ifdef RPI_USE_GETFILEINFOTEXT2
	case 2:
		retval = replay.GetComment(pSrc, dwSize, &pConstDst, &nDstSize);
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
		::memcpy_s(*pDst, nDstSize, pConstDst, nDstSize);
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

