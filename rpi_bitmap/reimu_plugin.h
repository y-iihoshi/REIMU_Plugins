// プラグインごとのきまりきった処理をする部分(Rev.2)
#ifndef _INC_REIMU_PLUGIN
#define _INC_REIMU_PLUGIN

#include <windows.h>
#include <stdio.h>


// 任意関数を使用するかどうかを定義
// 使用しない場合はコメントアウトしてください
// (exports.defのコメントアウトもお忘れなくｗ)
//#define RPI_USE_GETFILEINFOTEXT1	// GetFileInfoText1
//#define RPI_USE_GETFILEINFOTEXT2	// GetFileInfoText2
#define RPI_USE_GETFILEINFOIMAGE1	// GetFileInfoImage1
//#define RPI_USE_GETFILEINFOIMAGE2	// GetFileInfoImage2
//#define RPI_USE_EDITDIALOG			// EditDialog
//#define RPI_USE_CONFIGDIALOG		// ConfigDialog


#ifndef DLLEXPORT
# define DLLEXPORT	__declspec(dllexport)
#endif
#ifndef STDCALL
# define STDCALL	__stdcall
#endif

// エラーコード
#define RPI_NO_FUNCTION			-1	// 未実装の関数
#define RPI_ALL_RIGHT			0	// 正常終了
#define RPI_NOT_SUPPORT			1	// 未対応の形式
#define RPI_FILE_READ_ERROR		2	// ファイル読み込みエラー
#define	RPI_FILE_WRITE_ERROR	3	// ファイル書き出しエラー
#define RPI_NO_MEMORY			4	// メモリーが確保出来ない
#define RPI_UNKNOWN_ERROR		5	// 未知のエラー
#define RPI_DIALOG_CANCELED		6	// EditDialogやConfigDialogでキャンセルされた


// ColumnInfo::nAlignで使うやつ
// これだけのためにcommctrl.hをインクルードしたくないので(ぉ
#ifndef LVCFMT_LEFT
# define LVCFMT_LEFT	0x0000
# define LVCFMT_RIGHT	0x0001
# define LVCFMT_CENTER	0x0002
#endif

// ColumnInfo::nSortTypeで使うやつ
#ifndef SORT_STRING
# define SORT_STRING	0	//	0:文字列ソート(項目の中身をそのままの文字列として辞書式にソートする)
# define SORT_NUMBER	1	//	1:整数ソート(項目の中身を整数とみなしてソートする
							//    atoi準拠だが、3桁区切りのカンマは無視される)
# define SORT_FLOAT		2	//	2:小数ソート(項目の中身を小数とみなしてソートする(atof変換))
# define SORT_HEX		3	//  3:16進数ソート(項目の中身を16進数とみなしてソートする)
#endif

// ColumnInfo::nSystemで使うやつ
#define CLSYS_STRING			0	//	0:無効(GetFileInfoListで取得した文字列をそのまま表示)
#define CLSYS_PATH				1	//	1:ファイルパス
#define CLSYS_DIRECTORY			2	//	2:ファイルのある場所(ディレクトリ)
#define CLSYS_TITLE				3	//	3:ファイルタイトル
#define CLSYS_EXT				4	//	4:ファイルの拡張子
#define CLSYS_TIME_CREATE		5	//	5:作成日時
#define CLSYS_TIME_LASTACCESS	6	//	6:アクセス日時
#define CLSYS_TIME_LASTWRITE	7	//	7:更新日時
#define CLSYS_FILESIZE			8	//	8:ファイルサイズ


#pragma pack(push)
#pragma pack(1) // 構造体のメンバ境界を1バイトにする

// カラム情報構造体
struct ColumnInfo{	// sizeof(ColumnInfo) = 128
	char szTitle[116];	// カラムに表示するタイトル
	int nAlign; 		// テキストの配置方法
						//	0:左寄せ
						//	1:右寄せ
						//	2:センタリング
						// (commctrl.hで定義されているLVCFMT_LEFT,LVCFMT_RIGHT,
						//	LVCFMT_CENTERと同一のものです)
	int nSortType;		// カラムをクリックした時のその列のソート方法
						//	0:文字列ソート(項目の中身をそのままの文字列として辞書式にソートする)
						//	1:整数ソート(項目の中身を整数とみなしてソートする
						//	  atoi準拠だが、3桁区切りのカンマは無視される)
						//	2:小数ソート(項目の中身を小数とみなしてソートする(atof変換))
						//	3:16進数ソート(項目の中身を16進数とみなしてソートする)
	int nSystem;		// リストビューにシステム情報を表示するかどうか
						//	0:無効(GetFileInfoListで取得した文字列をそのまま表示)
						//	1:ファイルパス
						//	2:ファイルのある場所(ディレクトリ)
						//	3:ファイルタイトル
						//	4:ファイルの拡張子
						//	5:作成日時
						//	6:アクセス日時
						//	7:更新日時
						//  8:ファイルサイズ
};

// リスト情報構造体
struct FileInfo{  // sizeof(FileInfo) = 512
	char szText[512];	// リストに表示する文字列(ColumnInfoのnSystemが0の時のみ有効)
};

#pragma pack(pop)

// RPI関数
extern "C" {
	// 必須関数
	int DLLEXPORT STDCALL GetPluginRevision();
	unsigned int DLLEXPORT STDCALL GetPluginInfo(int nInfoNo, char* szDst, int nDstLength);
	int DLLEXPORT STDCALL GetColumnInfo(ColumnInfo** lpInfo);
	unsigned int DLLEXPORT STDCALL IsSupported(const char* pSrc, unsigned int dwSize);
	int DLLEXPORT STDCALL GetFileInfoList(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo);

	// 任意関数
#ifdef RPI_USE_GETFILEINFOTEXT1
	int DLLEXPORT STDCALL GetFileInfoText1(const char* pSrc, unsigned int dwSize, char** pDst);
#endif
#ifdef RPI_USE_GETFILEINFOTEXT2
	int DLLEXPORT STDCALL GetFileInfoText2(const char* pSrc, unsigned int dwSize, char** pDst);
#endif
#ifdef RPI_USE_GETFILEINFOIMAGE1
	int DLLEXPORT STDCALL GetFileInfoImage1(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
#endif
#ifdef RPI_USE_GETFILEINFOIMAGE2
	int DLLEXPORT STDCALL GetFileInfoImage2(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
#endif
#ifdef RPI_USE_EDITDIALOG
	int DLLEXPORT STDCALL EditDialog(HWND hWnd, const char* szFile);
#endif
#ifdef RPI_USE_CONFIGDIALOG
	int DLLEXPORT STDCALL ConfigDialog(HWND hWnd);
#endif

}

// GetProcAddressする時に便利なtypedef宣言
typedef int (WINAPI *LPGETPLUGINREVISION)();
typedef unsigned int (WINAPI *LPGETPLUGININFO)(int nInfoNo, char* szDst, unsigned int dwDstLength);
typedef int (WINAPI *LPGETCOLUMNINFO)(ColumnInfo** lpInfo);
typedef unsigned int (WINAPI *LPISSUPPORTED)(const char* pSrc, unsigned int dwSize);
typedef int (WINAPI *LPGETFILEINFOLIST)(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo);
typedef int (WINAPI *LPGETFILEINFOTEXT1)(const char* pSrc, unsigned int dwSize, char** pDst);
typedef int (WINAPI *LPGETFILEINFOTEXT2)(const char* pSrc, unsigned int dwSize, char** pDst);
typedef int (WINAPI *LPGETFILEINFOIMAGE1)(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
typedef int (WINAPI *LPGETFILEINFOIMAGE2)(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
typedef int (WINAPI *LPEDITDIALOG)(HWND hWnd, const char* szFile);
typedef int (WINAPI *LPCONFIGDIALOG)(HWND hWnd);

#endif
