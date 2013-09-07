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

/*
//=============================================================================
//		タイムスタンプを取得する
//=============================================================================
// input
//		szFile	: ファイル名
//		szDest	: 出力先バッファ
//		nType	: 取得する情報(0:作成日時 1:最終アクセス日時 2:更新日時)
//		bDay	: 日付を書き出すかどうか
//		bTime	: 時刻を書き出すかどうか
//
// return
//
//=============================================================================
void GetTimeStamp(char* szDest, const char* szFile, int nType, bool bDay, bool bTime)
{
	HANDLE		hf = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	FILETIME	ft[3];
	SYSTEMTIME	st;
	char		time[200], day[200];

	ZeroMemory(time, sizeof(time));
	ZeroMemory(day , sizeof(day));

	if(nType<0 || nType>2)	nType = 2;

	// ファイルの更新時間を調べます
	if (hf != INVALID_HANDLE_VALUE){
		GetFileTime(hf, &ft[0], &ft[1], &ft[2]);
		CloseHandle(hf);
		FileTimeToSystemTime(&ft[nType], &st);
		sprintf(day , "%04d/%02d/%02d",	st.wYear       , st.wMonth , st.wDay);
		sprintf(time, "%02d:%02d:%02d",	(st.wHour+9)%24, st.wMinute, st.wSecond);
		if(bDay && bTime)	sprintf(szDest, "%s %s", day, time);
		else if(bDay)		strcpy( szDest, day);
		else if(bTime)		strcpy( szDest, time);
		else				strcpy( szDest, "");
	}
	else{
		strcpy(szDest, "");
	}
}

//=============================================================================
//		ファイル名を取得(szFileから参照)
//=============================================================================
// input
//		szFile		: ファイルパス
//
// return
//		ファイル名
//
//=============================================================================
const char* GetFileName(const char* szFile)
{
	char* str = (char*)szFile;	// 戻り値用
	char* p   = str;	// カウンタ

	while(*p!='\0'){
		if(*p=='\\' || *p=='/')		str = p + 1;
		p = JmsNext(p);
	}

	return str;
}

//=============================================================================
//		拡張子を取得する(szFileから参照)
//=============================================================================
// input
//		szFile		: ファイルパス
//
// return
//		拡張子(存在しない場合は終端の'\0'が返る)
//
//=============================================================================
const char* GetFileExt(const char* szFile)
{
	char* str  = (char*)GetFileName(szFile);	// 戻り値用
	char* str1 = str;	// strの初期値(比較用)
	char* p    = str;	// カウンタ

	while(*p!='\0'){
		if(*p=='.')			str = p + 1;
		p = JmsNext(p);
	}

	if(str==str1)		return p;	// 拡張子が存在しない場合は'\0'を返す
	return str;
}

//=============================================================================
//		ファイルのカレントディレクトリを取得
//		("c:\temp\hoge.tmp"の場合だと"c:\temp")
//=============================================================================
// input
//		szDir		: ディレクトリが格納される場所
//		szFile		: ファイルパス
//
// return
//
//=============================================================================
void GetCurDir(char* szDir, const char* szFile)
{
	// ファイル名がない＝szFileはディレクトリ
	const char* title = GetFileName(szFile);
	if(strlen(title)==0){
		strcpy(szDir, szFile);
		char* p = szDir + strlen(szDir) - 1;	// 最後の1バイト
		if(IsJms(szDir, p-szDir)==0 && (*p=='\\' || *p=='/')){
			*p = '\0';
			return;
		}
	}
	else{
		int length = strlen(szFile)-strlen(title)-1;
		strncpy(szDir, szFile, length);
		szDir[ length ] = '\0';
		return;
	}

	szDir[0] = '\0';
}

//=============================================================================
//		strcatの書式版(意外に便利(笑))
//=============================================================================
// input
//		str1		: 文字列バッファ
//		format		: 書式文字列
//
// return
//
//=============================================================================
void strcatf(char* str1, const char* format, ...)
{
	char buf[1024*10];

	if(!format){
		format = "Program aborted.";
	}
	ZeroMemory(buf, sizeof(buf));
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	if(str1[0]!='\0')	strcat(str1, buf);
	else				strcpy(str1, buf);
}
void strcatf(char* str1, char* str2)
{
	if(str1[0]!='\0')	strcat(str1, str2);
	else				strcpy(str1, str2);
}

//=============================================================================
//		汎用スプリット関数
//=============================================================================
// input
//		szSrc		: 元の文字列
//		vecDest		: 出力先
//		cSplit		: 区切り文字(半角文字のみ)
//		szCmtOut	: コメントアウト文字(NULLか""指定で無効)
//
// return
//
//=============================================================================
void Split(const char* szSrc, vector< smart_array<char> > &vecDest, char cSplit, char* szCmtOut)
{
	char* p;	// カウンタ
	char* str;	// 先頭文字列
	smart_array<char> a;

	p = str = (char*)szSrc;
	vecDest.clear();

	while(*p){
		if(*p==cSplit){
			if(p>str){
				StringCopy(a, str, p-str);
				vecDest.push_back(a);
			}
		//	str =JmsNext(p);	// 1つ後を開始位置に設定
			str = p + 1;
		}
		// コメントアウト
		else if(szCmtOut && strlen(szCmtOut)>0 && strlen(p)>=strlen(szCmtOut) &&
			strncmp(p,szCmtOut,strlen(szCmtOut))==0)
		{
			break;
		}

		p = JmsNext(p);
	}

	// 終端処理
	if(p>str){
		StringCopy(a, str, p-str);
		vecDest.push_back(a);
	}
}

//=============================================================================
//		smart_array<char> に文字列をコピーする
//=============================================================================
// input
//		sa		: コピー先
//		szStr	: 文字列
//		nLength	: コピーする長さ(0の時(省略時)は全部)
//
// return
//
//=============================================================================
void StringCopy(smart_array<char>& sa, const char* szStr, int nLength)
{
	if(nLength<=0)	nLength = strlen(szStr);

	sa.Reset(new char[nLength+1], nLength+1);
	strncpy(sa.GetPtr(), szStr, nLength);
	*(sa.GetPtr()+nLength) = '\0';
}

//=============================================================================
//		ボタン・チェックボックス・ラジオボタンの状態を取得
//=============================================================================
// input
//		hWnd		: ウィンドウハンドル
//
// return
//		チェックされている true ／ チェックされてない false
//
//=============================================================================
bool BtnGetCheck(HWND hWnd)
{
	if(SendMessage(hWnd, BM_GETCHECK, 0, 0)==BST_CHECKED)	return true;
	return false;
}

//=============================================================================
//		ボタン・チェックボックス・ラジオボタンをチェックする
//=============================================================================
// input
//		hWnd		: ウィンドウハンドル
//		bCheck		: チェックするかしないか
//
// return
//
//=============================================================================
void BtnSetCheck(HWND hWnd, bool bCheck)
{
	WPARAM wParam = (bCheck) ? BST_CHECKED : BST_UNCHECKED;
//	WPARAM wParam;

//	if(bCheck)	wParam = BST_CHECKED;
//	else		wParam = BST_UNCHECKED;

	SendMessage(hWnd, BM_SETCHECK, wParam, NULL);
}
*/
