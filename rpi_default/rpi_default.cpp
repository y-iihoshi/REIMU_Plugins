// プラグインごとの独自の処理をする部分(Rev.1)
#include "rpi_default.h"


// extern
HINSTANCE hInstance;


////////////////////////
//		カラム情報
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
// 上記のCL～と対応している必要がある
static const ColumnInfo Column[MAX_COLUMN+1] = {
	{"ファイル名"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TITLE},
	{"ファイルサイズ"	, LVCFMT_RIGHT	, SORT_NUMBER	, CLSYS_FILESIZE},
	{"作成日時"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_CREATE},
	{"アクセス日時"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTACCESS},
	{"更新日時"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_TIME_LASTWRITE},
	{"拡張子"			, LVCFMT_LEFT	, SORT_STRING	, CLSYS_EXT},
	{"ファイルパス"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_PATH},
	{"ディレクトリ"		, LVCFMT_LEFT	, SORT_STRING	, CLSYS_DIRECTORY},
//	{"", LVCFMT_, SORT_, CLSYS_},

	{""}	// 終端(必須)
};


////////////////////////
//		必須関数
////////////////////////
#define MAX_INFO	2		// 最大情報数(2+2*n)

// プラグインの情報を取得する
unsigned int GetPluginInfoEx(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	const char* szInfo[MAX_INFO] = {
		"REIMU Default Plug-in Ver1.00 (C)sue445, 2005",
		"デフォルト",
//		"*.*",
//		"全てのファイル(*.*)",
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
	if(dwSize<HEADER_SIZE)							return 0;	// バッファサイズ小さすぎ
//	else if(strlen(szFile)>0 && !ExtCheck(szFile))	return 0;	// 拡張子一致しない
//	else if(memcmp(pSrc, "T8RP", HEADER_SIZE)!=0)	return 0;	// ヘッダ一致しない

	return 1;
}

// リストビューで表示するやつを取得
int GetFileInfoListEx(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo, const char* szFile)
{
	// メモリ確保
	*lpInfo = (FileInfo*)LocalAlloc(LPTR, sizeof(FileInfo) * (MAX_COLUMN));
	if(*lpInfo==NULL)			return RPI_NO_MEMORY;		// メモリ確保できない

	ZeroMemory(*lpInfo, sizeof(FileInfo) * (MAX_COLUMN));


// このプラグインでは情報の取得はありませんが、通常は下のようにやるといいかもしれません
//	FileInfo *pinfo = (FileInfo*)*lpInfo;
//	strcpy(pinfo[CL_INFO].szText, "Hoge");

	return RPI_ALL_RIGHT;
}


////////////////////////
//		任意関数
////////////////////////
// 左下・右下の情報(nType 1:左下 2:右下)
// (メモリ入力オンリー)
int GetFileInfoTextEx(int nType, const char* pSrc, unsigned int dwSize, char** pDst, const char* szFile)
{
	/*
	//	RPI_USE_GETFILEINFOTEXTT1とRPI_USE_GETFILEINFOTEXTT2が両方ないと
	//	switch文の中がdefaultだけになってしまってさすがにまずいのでコメントアウトしておくｗ

	switch(nType){

#ifdef RPI_USE_GETFILEINFOTEXTT1
	case 1:		// 左下
		break;
#endif		// #ifdef RPI_USE_GETFILEINFOTEXTT1

#ifdef RPI_USE_GETFILEINFOTEXTT2
	case 2:		// 右下
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
}
