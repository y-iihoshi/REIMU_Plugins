// �v���O�C�����Ƃ̓Ǝ��̏��������镔��(Rev.2)
#include <memory>
#include <cstring>
#include <ctime>
#include "rpi_th125bestshot.h"
#include "CTh125BestShot.h"
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
	CL_LEVEL_SCENE,
	CL_CARD_NAME,
	CL_WIDTH,
	CL_HEIGHT,
	//CL_WIDTH2,
	//CL_HEIGHT2,
	//CL_HALF_WIDTH,
	//CL_HALF_HEIGHT,
	CL_DATE_TIME,
	CL_SLOW_RATE,
	//CL_BONUS_FIELDS,
	CL_RESULT_SCORE,
	//CL_RESULT_SCORE2,
	CL_BASE_POINT,
	CL_CLEAR_SHOT,
	CL_SOLO_SHOT,
	CL_RED_SHOT,
	CL_PURPLE_SHOT,
	CL_BLUE_SHOT,
	CL_CYAN_SHOT,
	CL_GREEN_SHOT,
	CL_YELLOW_SHOT,
	CL_ORANGE_SHOT,
	CL_COLORFUL_SHOT,
	CL_RAINBOW_SHOT,
	CL_RISK_BONUS,
	CL_MACRO_BONUS,
	CL_FRONT_SHOT,
	CL_SIDE_SHOT,
	CL_BACK_SHOT,
	CL_CAT_BONUS,
	CL_BOSS_SHOT,
	CL_TWO_SHOT,
	CL_NICE_SHOT,
	CL_ANGLE_BONUS,
	CL_ANGLE,
	//CL_UNKNOWN7,
	//CL_UNKNOWN12,
	CL_FILESIZE,
	CL_DIRECTORY,

	MAX_COLUMN
};
// ��L��CL�`�ƑΉ����Ă���K�v������
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"�t�@�C����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"�X�V����",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"�V�[��",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�X�y���J�[�h��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"��",				LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"����",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	//{"��2",				LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	//{"����2",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	//{"��/2",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	//{"����/2",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"����",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"����������",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	//{"Bonus fields",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"Result Score",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	//{"Result Score2",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Base Point",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Clear Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Solo Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Red Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Purple Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Blue Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Cyan Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Green Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Yellow Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Orange Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Colorful Shot",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Rainbow Shot",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Risk Bonus",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Macro Bonus",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Front Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Side Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Back Shot",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Cat Bonus",		LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"Boss Shot",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"Two Shot",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"Nice Shot",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"Angle Bonus",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"Angle",			LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	//{"Unknown7",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	//{"Unknown12",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"�t�@�C���T�C�Y",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"�f�B���N�g��",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// �I�[(�K�{)
};


////////////////////////
//		�K�{�֐�
////////////////////////
#define MAX_INFO	4		// �ő���(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For �_�u���X�|�C���[ �x�X�g�V���b�g Ver1.01 (C) IIHOSHI Yoshinori, 2013",
	"�_�u���X�|�C���[ �x�X�g�V���b�g",
	"bs*.dat",
	"�_�u���X�|�C���[ �x�X�g�V���b�g�t�@�C��(bs*.dat)"
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
	return CTh125BestShot().IsSupported(pSrc, dwSize);
}

// ���X�g�r���[�ŕ\���������擾
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	if ((pSrc == NULL) || (lpInfo == NULL))
		return RPI_UNKNOWN_ERROR;

	CTh125BestShot bestshot;

	if (!bestshot.IsSupported(pSrc, dwSize))
		return RPI_NOT_SUPPORT;

	*lpInfo = (FileInfo *)::LocalAlloc(LPTR, sizeof(FileInfo) * MAX_COLUMN);
	if (*lpInfo == NULL)
		return RPI_NO_MEMORY;

	std::unique_ptr<CTh125BestShot::Info> info(bestshot.GetInfo(pSrc, dwSize));
	if (info.get() == NULL)
		return RPI_FILE_READ_ERROR;

	const char *szLevels[] = {
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "EX", "SP"
	};

	FileInfo *pInfo = *lpInfo;
	::sprintf_s(pInfo[CL_LEVEL_SCENE].szText, "%s-%d", szLevels[info->level - 1], info->scene);
	::memcpy_s(
		pInfo[CL_CARD_NAME].szText, sizeof(pInfo[CL_CARD_NAME].szText),
		info->cardName, sizeof(info->cardName));
	::sprintf_s(pInfo[CL_WIDTH].szText, "%d", info->width);
	::sprintf_s(pInfo[CL_HEIGHT].szText, "%d", info->height);
	//::sprintf_s(pInfo[CL_WIDTH2].szText, "%d", info->width2);
	//::sprintf_s(pInfo[CL_HEIGHT2].szText, "%d", info->height2);
	//::sprintf_s(pInfo[CL_HALF_WIDTH].szText, "%d", info->halfWidth);
	//::sprintf_s(pInfo[CL_HALF_HEIGHT].szText, "%d", info->halfHeight);
	time_t time = (time_t)info->dateTime;
	tm ts;
	::localtime_s(&ts, &time);
	std::strftime(pInfo[CL_DATE_TIME].szText, sizeof(pInfo[CL_DATE_TIME].szText), "%Y/%m/%d %H:%M:%S", &ts);
	::sprintf_s(pInfo[CL_SLOW_RATE].szText, "%.6f", info->slowRate);
	//for (int i = 0, j = 0; i < 32; i++)
	//{
	//	pInfo[CL_BONUS_FIELDS].szText[j++] = (info->bonusFields.value & (1 << (31 - i))) ? '1' : '0';
	//	if (i % 8 == 7)
	//		pInfo[CL_BONUS_FIELDS].szText[j++] = ' ';
	//	if (i == 31)
	//		pInfo[CL_BONUS_FIELDS].szText[j] = '\0';
	//}
	::sprintf_s(pInfo[CL_RESULT_SCORE].szText, "%d", info->resultScore);
	//::sprintf_s(pInfo[CL_RESULT_SCORE2].szText, "%d", info->resultScore2);
	::sprintf_s(pInfo[CL_BASE_POINT].szText, "%d", info->basePoint);
	::sprintf_s(pInfo[CL_CLEAR_SHOT].szText, "%d",
		info->bonusFields.fields.clearShot ? info->clearShot : 0);
	::sprintf_s(pInfo[CL_SOLO_SHOT].szText, "%d",
		info->bonusFields.fields.soloShot ? 100 : 0);
	::sprintf_s(pInfo[CL_RED_SHOT].szText, "%d",
		info->bonusFields.fields.redShot ? 300 : 0);
	::sprintf_s(pInfo[CL_PURPLE_SHOT].szText, "%d",
		info->bonusFields.fields.purpleShot ? 300 : 0);
	::sprintf_s(pInfo[CL_BLUE_SHOT].szText, "%d",
		info->bonusFields.fields.blueShot ? 300 : 0);
	::sprintf_s(pInfo[CL_CYAN_SHOT].szText, "%d",
		info->bonusFields.fields.cyanShot ? 300 : 0);
	::sprintf_s(pInfo[CL_GREEN_SHOT].szText, "%d",
		info->bonusFields.fields.greenShot ? 300 : 0);
	::sprintf_s(pInfo[CL_YELLOW_SHOT].szText, "%d",
		info->bonusFields.fields.yellowShot ? 300 : 0);
	::sprintf_s(pInfo[CL_ORANGE_SHOT].szText, "%d",
		info->bonusFields.fields.orangeShot ? 300 : 0);
	::sprintf_s(pInfo[CL_COLORFUL_SHOT].szText, "%d",
		info->bonusFields.fields.colorfulShot ? 900 : 0);
	::sprintf_s(pInfo[CL_RAINBOW_SHOT].szText, "%d",
		info->bonusFields.fields.rainbowShot ? 2100 : 0);
	::sprintf_s(pInfo[CL_RISK_BONUS].szText, "%d",
		info->bonusFields.fields.riskBonus ? info->riskBonus : 0);
	::sprintf_s(pInfo[CL_MACRO_BONUS].szText, "%d",
		info->bonusFields.fields.macroBonus ? info->macroBonus : 0);
	::sprintf_s(pInfo[CL_FRONT_SHOT].szText, "%d",
		info->bonusFields.fields.frontShot ? info->frontSideBackShot : 0);
	::sprintf_s(pInfo[CL_SIDE_SHOT].szText, "%d",
		info->bonusFields.fields.sideShot ? info->frontSideBackShot : 0);
	::sprintf_s(pInfo[CL_BACK_SHOT].szText, "%d",
		info->bonusFields.fields.backShot ? info->frontSideBackShot : 0);
	::sprintf_s(pInfo[CL_CAT_BONUS].szText, "%d",
		info->bonusFields.fields.catBonus ? 666 : 0);
	::sprintf_s(pInfo[CL_BOSS_SHOT].szText, "%.2f", info->bossShot);
	::sprintf_s(pInfo[CL_TWO_SHOT].szText, "%.2f",
		info->bonusFields.fields.twoShot ? 1.50 : 1.00);
	::sprintf_s(pInfo[CL_NICE_SHOT].szText, "%.2f",
		info->bonusFields.fields.niceShot ? info->niceShot : 1.00);
	::sprintf_s(pInfo[CL_ANGLE_BONUS].szText, "%.2f", info->angleBonus);
	::sprintf_s(pInfo[CL_ANGLE].szText, "%.6f", info->angle);
	//::sprintf_s(pInfo[CL_UNKNOWN7].szText, "%08X", info->unknown7[0]);
	//::sprintf_s(
	//	pInfo[CL_UNKNOWN7].szText + 8, sizeof(pInfo[CL_UNKNOWN7].szText) - 8,
	//	" %08X", info->unknown7[1]);
	//::sprintf_s(pInfo[CL_UNKNOWN12].szText, "%08X", info->unknown12);

	return RPI_ALL_RIGHT;
}


////////////////////////
//		�C�ӊ֐�
////////////////////////
// �����E�E���̃e�L�X�g���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	CTh125BestShot bestshot;
	size_t nDstSize;
	int retval;

	switch (nType)
	{
#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:
		retval = bestshot.GetInfo(pSrc, dwSize, pDst, &nDstSize);
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

// �����E�E���̉摜���(nType 1:���� 2:�E��)
// (���������̓I�����[)
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile)
{
	CTh125BestShot bestshot;
	int retval;

	switch(nType){

#ifdef RPI_USE_GETFILEINFOIMAGE1
	case 1:		// ����
		return RPI_NO_FUNCTION;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE1

#ifdef RPI_USE_GETFILEINFOIMAGE2
	case 2:		// �E��
		retval = bestshot.GetPicture(pSrc, dwSize, pDst, pInfo);
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

