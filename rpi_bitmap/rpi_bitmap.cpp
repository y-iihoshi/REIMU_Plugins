// プラグインごとの独自の処理をする部分(Rev.2)
#include "rpi_bitmap.h"


// extern
HINSTANCE hInstance;


////////////////////////
//		カラム情報
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
// 上記のCL～と対応している必要がある
static const ColumnInfo Column[MAX_COLUMN+1] = {
	{"ファイル名"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TITLE},
	{"幅"				, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"高さ"				, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"ビット数"			, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_STRING},
	{"ファイルサイズ"	, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_FILESIZE},
	{"更新日時"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTWRITE},
	{"ディレクトリ"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_DIRECTORY},
//	{"", LVCFMT_, SORT_, CLSYS_},

	{""}	// 終端(必須)
};


////////////////////////
//		必須関数
////////////////////////
#define MAX_INFO	4		// 最大情報数(2+2*n)

// プラグインの情報を取得する
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	const char* szInfo[MAX_INFO] = {
		"REIMU Image Plug-in Ver1.00 (C)sue445, 2005",
		"ビットマップ",
		"*.bmp",
		"ビットマップファイル(*.bmp)",
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

// カラム情報の取得
int GetColumnInfoEx(ColumnInfo** lpInfo)
{
	// メモリ確保
	*lpInfo = (ColumnInfo*)LocalAlloc(LPTR, sizeof(ColumnInfo) * (MAX_COLUMN+1));
	if(*lpInfo==NULL)	return RPI_NO_MEMORY;		// メモリ確保できない

	memcpy(*lpInfo, Column, sizeof(ColumnInfo) * (MAX_COLUMN+1));

	return RPI_ALL_RIGHT;
}

// 対応しているかどうか(対応していれば非0を返す)
// ファイル名で判定することもあるかもしれないのでファイル名も一応送っとく
unsigned int IsSupportedEx(const char* pSrc, unsigned int dwSize, const char* szFile)
{
	if(dwSize<HEADER_SIZE)		return 0;	// バッファサイズ小さすぎ

	CBmp bmp;
	return bmp.IsSupported(pSrc, dwSize);
}

// リストビューで表示するやつを取得
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	CBmp bmp;
	BITMAPINFOHEADER	bmiHeader;

	if(!bmp.GetPictureInfo(pSrc, dwSize, &bmiHeader))	return RPI_NOT_SUPPORT;

	// メモリ確保
	*lpInfo = (FileInfo*)LocalAlloc(LPTR, sizeof(FileInfo) * (MAX_COLUMN));
	if(*lpInfo==NULL)			return RPI_NO_MEMORY;		// メモリ確保できない

	ZeroMemory(*lpInfo, sizeof(FileInfo) * (MAX_COLUMN));


	FileInfo *pinfo = (FileInfo*)*lpInfo;
	sprintf(pinfo[CL_WIDTH].szText		, "%u", bmiHeader.biWidth);
	sprintf(pinfo[CL_HEIGHT].szText		, "%u", bmiHeader.biHeight);
	sprintf(pinfo[CL_BITCOUNT].szText	, "%u", bmiHeader.biBitCount);

	return RPI_ALL_RIGHT;
}


////////////////////////
//		任意関数
////////////////////////
// 左下・右下のテキスト情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	switch(nType){

#ifdef RPI_USE_GETFILEINFOTEXT1
	case 1:		// 左下
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOTEXT2
	case 2:		// 右下
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2

	// RPI_USE_GETFILEINFOTEXT1とRPI_USE_GETFILEINFOTEXT2が
	// 両方定義されてない時のためにダミーで入れておく(^^;
	case 0:
		break;
	}

	return RPI_NO_FUNCTION;
}

// 左下・右下の画像情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
int GetFileInfoImageEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo, const char* szFile)
{
	CBmp bmp;

	switch(nType){

#ifdef RPI_USE_GETFILEINFOIMAGE1
	case 1:		// 左下
		if(!bmp.GetPicture(pSrc, dwSize, pDst, pInfo))	return RPI_NOT_SUPPORT;

		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE1

#ifdef RPI_USE_GETFILEINFOIMAGE2
	case 2:		// 右下
		return RPI_ALL_RIGHT;
#endif		// #ifdef RPI_USE_GETFILEINFOIMAGE2

	// RPI_USE_GETFILEINFOIMAGE1とRPI_USE_GETFILEINFOIMAGE2が
	// 両方定義されてない時のためにダミーで入れておく(^^;
	case 0:
		break;
	}

	return RPI_NO_FUNCTION;
}

#ifdef RPI_USE_EDITDIALOG
// 編集ダイアログ
// (ファイル入力オンリー)
int EditDialogEx(HWND hWnd, const char* szFile)
{
	return 0;
}
#endif

#ifdef RPI_USE_CONFIGDIALOG
// 設定ダイアログ
int ConfigDialogEx(HWND hWnd)
{
	return OpenConfigDialog(hWnd);
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

	// 設定を読み込む
//	LoadConfig();
}

