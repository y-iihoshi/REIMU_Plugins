// プラグインごとのきまりきった処理をする部分(Rev.2)
#include "reimu_plugin.h"
#include "..\rpi_threplay\sueLib_LE.h"
#include "rpi_th123replay.h"


// エントリポイント
BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		LoadPlugin(hModule);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

////////////////////////
//		必須関数
////////////////////////
// プラグインのリビジョン(仕様番号)を取得する
int STDCALL GetPluginRevision()
{
	return 2;
}

// プラグインの情報を取得する
unsigned int STDCALL GetPluginInfo(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	return GetPluginInfoEx(nInfoNo, szDst, dwDstLength);
}

// カラム情報の取得
int STDCALL GetColumnInfo(ColumnInfo** lpInfo)
{
	return GetColumnInfoEx(lpInfo);
}

// 対応しているかどうか(対応していれば非0を返す)
unsigned int STDCALL IsSupported(const char* pSrc, unsigned int dwSize)
{
	// 識別用に最低限必要なバイト数を返す
	if(pSrc==NULL){
		return HEADER_SIZE;
	}
	// メモリ入力
	else if(dwSize){
		return IsSupportedEx(pSrc, dwSize);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf, HEADER_SIZE)){
			return IsSupportedEx(buf.GetPtr(), buf.GetSize(), pSrc);
		}
		return 0;
	}
}

// リストビューで表示するやつを取得
int STDCALL GetFileInfoList(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo)
{
	// サイズの大きいファイルを無駄に読み込むのは動作速度が遅くなるので、
	// ここでIsSupportedしておく
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// メモリ入力
	if(dwSize){
		return GetFileInfoListEx(pSrc, dwSize, lpInfo);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoListEx(buf.GetPtr(), buf.GetSize(), lpInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}

////////////////////////
//		任意関数
////////////////////////
#ifdef RPI_USE_GETFILEINFOTEXT1
// 左下のテキスト情報
int STDCALL GetFileInfoText1(const char* pSrc, unsigned int dwSize, char** pDst)
{
	// サイズの大きいファイルを無駄に読み込むのは動作速度が遅くなるので、
	// ここでIsSupportedしておく
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// メモリ入力
	if(dwSize){
		return GetFileInfoTextEx(1, pSrc, dwSize, pDst);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoTextEx(1, buf.GetPtr(), buf.GetSize(), pDst, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOTEXT2
// 右下のテキスト情報
int STDCALL GetFileInfoText2(const char* pSrc, unsigned int dwSize, char** pDst)
{
	// サイズの大きいファイルを無駄に読み込むのは動作速度が遅くなるので、
	// ここでIsSupportedしておく
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// メモリ入力
	if(dwSize){
		return GetFileInfoTextEx(2, pSrc, dwSize, pDst);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoTextEx(2, buf.GetPtr(), buf.GetSize(), pDst, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2


#ifdef RPI_USE_GETFILEINFOIMAGE1
// 左下の画像情報
int STDCALL GetFileInfoImage1(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo)
{
	// サイズの大きいファイルを無駄に読み込むのは動作速度が遅くなるので、
	// ここでIsSupportedしておく
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// メモリ入力
	if(dwSize){
		return GetFileInfoImageEx(1, pSrc, dwSize, pDst, pInfo);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoImageEx(1, buf.GetPtr(), buf.GetSize(), pDst, pInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOIMAGE2
// 右下の画像情報
int STDCALL GetFileInfoImage2(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo)
{
	// サイズの大きいファイルを無駄に読み込むのは動作速度が遅くなるので、
	// ここでIsSupportedしておく
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// メモリ入力
	if(dwSize){
		return GetFileInfoImageEx(2, pSrc, dwSize, pDst, pInfo);
	}
	// ファイル入力
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoImageEx(2, buf.GetPtr(), buf.GetSize(), pDst, pInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2

#ifdef RPI_USE_EDITDIALOG
// 編集ダイアログ
int STDCALL EditDialog(HWND hWnd, const char* szFile)
{
	return EditDialogEx(hWnd, szFile);
}
#endif		// #ifdef RPI_USE_EDITDIALOG

#ifdef RPI_USE_CONFIGDIALOG
// 設定ダイアログ
int STDCALL ConfigDialog(HWND hWnd)
{
	return ConfigDialogEx(hWnd);
}
#endif		// #ifdef RPI_USE_CONFIGDIALOG
