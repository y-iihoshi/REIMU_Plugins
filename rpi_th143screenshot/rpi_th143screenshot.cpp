// プラグインごとの独自の処理をする部分(Rev.2)
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
//		カラム情報
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
// 上記のCL～と対応している必要がある
static const ColumnInfo Column[MAX_COLUMN + 1] = {
	{"ファイル名",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TITLE},
	{"更新日時",		LVCFMT_LEFT,	SORT_STRING,	CLSYS_TIME_LASTWRITE},
	{"日付",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"シーン",			LVCFMT_LEFT,	SORT_NUMBER,	CLSYS_STRING},
	{"日付-シーン",		LVCFMT_LEFT,	SORT_NUMBER,	CLSYS_STRING},
	{"幅",				LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"高さ",			LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_STRING},
	{"日時",			LVCFMT_LEFT,	SORT_STRING,	CLSYS_STRING},
	{"処理落ち率",		LVCFMT_RIGHT,	SORT_FLOAT,		CLSYS_STRING},
	{"ファイルサイズ",	LVCFMT_RIGHT,	SORT_NUMBER,	CLSYS_FILESIZE},
	{"ディレクトリ",	LVCFMT_LEFT,	SORT_STRING,	CLSYS_DIRECTORY},

	{""}	// 終端(必須)
};


////////////////////////
//		必須関数
////////////////////////
#define MAX_INFO	4		// 最大情報数(2+2*n)

static const char* szPluginInfo[MAX_INFO] = {
	"REIMU Plug-in For 弾幕アマノジャク スクリーンショット Ver1.00 (C) IIHOSHI Yoshinori, 2014",
	"弾幕アマノジャク スクリーンショット",
	"sc*.dat",
	"弾幕アマノジャク スクリーンファイル(sc*.dat)"
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
	return CTh143ScreenShot().IsSupported(pSrc, dwSize);
}

// リストビューで表示するやつを取得
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
		"一日目", "二日目", "三日目", "四日目", "五日目", "六日目", "七日目", "八日目", "九日目", "最終日"
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
//		任意関数
////////////////////////
#if defined(RPI_USE_GETFILEINFOTEXT1) || defined(RPI_USE_GETFILEINFOTEXT2)
// 左下・右下のテキスト情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
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

// 左下・右下の画像情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile)
{
	CTh143ScreenShot screenshot;
	int retval;

	switch(nType){

#ifdef RPI_USE_GETFILEINFOIMAGE1
	case 1:		// 左下
		return RPI_NO_FUNCTION;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE1

#ifdef RPI_USE_GETFILEINFOIMAGE2
	case 2:		// 右下
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

