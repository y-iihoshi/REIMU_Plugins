// プラグインごとの独自の処理をする部分(Rev.2)
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
//		カラム情報
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
// 上記のCL～と対応している必要がある
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"ファイル名",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"更新日時",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"No.",				LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"プレイヤー名",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"プレイ時刻",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"使用キャラ",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"難易度",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"ステージ",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"スコア",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"処理落ち率",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"バージョン",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"コメント",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"ファイルサイズ",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"ディレクトリ",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// 終端(必須)
};


////////////////////////
//		必須関数
////////////////////////
#define MAX_INFO	4		// 最大情報数(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For 東方地霊殿 Ver0.01 (C) IIHOSHI Yoshinori, 2013",
	"東方地霊殿_Test",
	"th11_*.rpy",
	"東方地霊殿 リプレイファイル(th11_*.rpy)"
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
	return CTh11Replay().IsSupported(pSrc, dwSize);
}

// リストビューで表示するやつを取得
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
//		任意関数
////////////////////////
// 左下・右下のテキスト情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
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

