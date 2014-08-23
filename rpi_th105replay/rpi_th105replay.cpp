// プラグインごとの独自の処理をする部分(Rev.2)
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
//		カラム情報
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
// 上記のCL～と対応している必要がある
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"ファイル名",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"更新日時",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"バージョン",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"モード",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"プレイヤー 1",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"色 1",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"プレイヤー 2",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"色 2",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"ステージ",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"BGM",				LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"ファイルサイズ",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"ディレクトリ",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// 終端(必須)
};


////////////////////////
//		必須関数
////////////////////////
#define MAX_INFO	4		// 最大情報数(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For 東方緋想天 Ver1.00 (C) IIHOSHI Yoshinori, 2014",
	"東方緋想天",
	"*.rep",
	"東方緋想天 リプレイファイル(*.rep)"
};

// プラグインの情報を取得する
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

// カラム情報の取得
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

// 対応しているかどうか(対応していれば非0を返す)
// ファイル名で判定することもあるかもしれないのでファイル名も一応送っとく
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile)
{
	return CTh105Replay().IsSupported(pSrc, dwSize);
}

// リストビューで表示するやつを取得
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
//		任意関数
////////////////////////
// 左下・右下のテキスト情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
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
// 編集ダイアログ
// (ファイル入力オンリー)

int EditDialogEx(HWND hWnd, const char* szFile)
{
	return (CEditDialog(szFile).Show(hInstance, hWnd) == IDOK) ? 0 : 1;
}
#endif

#ifdef RPI_USE_CONFIGDIALOG
// 設定ダイアログ
int ConfigDialogEx(HWND hWnd)
{
	return (CConfigDialog(&config).Show(hInstance, hWnd) == IDOK) ? 0 : 1;
}
#endif


//////////////////////////////////
//		その他の内部使用関数
//////////////////////////////////
// プラグインがロードされた時に一度だけ実行される関数(ここで設定を読み込んだりする)
void LoadPlugin(HINSTANCE hInst)
{
	// コンフィグダイアログ用にインスタンスを取得
	hInstance = hInst;

#ifdef RPI_USE_CONFIGDIALOG
	// 設定を読み込む
	config.Load(hInstance);
#endif
}

