#include "sueLib_LE.h"


//=============================================================================
//		ファイルサイズを取得する
//=============================================================================
// input
//		szFile	: ファイル名
//
// return
//		ファイルサイズ(存在しない場合は0を返す)
//
//=============================================================================
DWORD fsize(const char* szFile)
{
	HANDLE	hf;
	DWORD	filesize;

	DWORD	ret = GetFileAttributes(szFile);
	if(ret==0xFFFFFFFF)								return 0;	// エラー(パスが見つからない)
	else if((ret & FILE_ATTRIBUTE_DIRECTORY) != 0)	return 0;	// ディレクトリ

	hf = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hf == INVALID_HANDLE_VALUE) return 0;

	filesize = GetFileSize(hf,NULL);
	CloseHandle(hf);

	if(filesize==0xFFFFFFFF)		return 0;	// GetFileSizeのエラー

	return filesize;
}

//=============================================================================
//		ファイルからメモリへの簡易読み込み
//=============================================================================
// input
//		szFile	: ファイル名
//		saDest	: 出力先
//		dwSize	: 読み込むサイズ。ファイルサイズがこれに満たなければエラー
//				  0(省略時)の時はとりあえず全部読み込んでおく
//		bError	: ファイルサイズがdwSizeに足りない時の挙動
//				  true:エラーを返す  false:その分だけ読み込む(エラーにしない)
//
// return
//		読み込み成功したかどうか
//
//=============================================================================
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize, bool bError)
{
	DWORD filesize = fsize(szFile);
	if(filesize==0)								return false;	// ファイルサイズ取得失敗
	else if(dwSize>0 && filesize<dwSize){
		if(bError)	return false;		// ファイルサイズが小さすぎ
		else		dwSize = filesize;
	}
	else if(dwSize==0 || dwSize>filesize)	dwSize = filesize;	// 引数省略時とかはファイルを全部読み込む

	FILE* fp = fopen(szFile, "rb");
	if(!fp)				return false;	// ファイル開けない

	saDest.Reset(new char[dwSize], dwSize);

	// ファイル読み込み
	fread(saDest.GetPtr(), saDest.GetSize(), 1, fp);

	fclose(fp);

	return true;
}
