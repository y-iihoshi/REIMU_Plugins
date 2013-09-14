#pragma once

#include <Windows.h>
#include "CDialogBase.h"
#include "CTh11Config.h"

class CConfigDialog : public CDialogBase
{
private:
	typedef CDialogBase base;

	CTh11Config *pConfig;

public:
	CConfigDialog(CTh11Config *pConfig);
	~CConfigDialog();

	INT_PTR Show(HINSTANCE hInst, HWND hWndOwner);
	INT_PTR DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void OnClose(HWND hwnd);
};

INT_PTR OpenConfigDialog(HINSTANCE hInstance, HWND hWndParent);
