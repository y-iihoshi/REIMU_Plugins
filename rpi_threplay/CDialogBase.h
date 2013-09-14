#pragma once

#include <Windows.h>

class CDialogBase
{
private:
	HWND hWnd;

public:
	CDialogBase();
	virtual ~CDialogBase();

	HWND Handle() const;

	INT_PTR Show(HINSTANCE hInst, HWND hWndOwner, LPCTSTR lpszTemplateName);
	virtual INT_PTR DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
