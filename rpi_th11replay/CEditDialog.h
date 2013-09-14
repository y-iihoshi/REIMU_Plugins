#pragma once

#include <Windows.h>
#include "CDialogBase.h"

INT_PTR OpenEditDialog(HINSTANCE hInstance, HWND hWndParent, LPCTSTR lpszFilename);

class CEditDialog : public CDialogBase
{
private:
	typedef CDialogBase base;

	LPCTSTR lpszFilename;
	const int nMaxTextSize;

public:
	CEditDialog(LPCTSTR lpszFilename, int nMaxTextSize = 30000);
	~CEditDialog();

	INT_PTR Show(HINSTANCE hInst, HWND hWndOwner);
	INT_PTR DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void OnClose(HWND hwnd);
};
