#include "CDialogBase.h"

CDialogBase::CDialogBase()
	: hWnd(NULL)
{
}

CDialogBase::~CDialogBase()
{
}

HWND CDialogBase::Handle() const
{
	return this->hWnd;
}

INT_PTR CDialogBase::Show(HINSTANCE hInst, HWND hWndOwner, LPCTSTR lpszTemplateName)
{
	return ::DialogBoxParam(
		hInst, lpszTemplateName, hWndOwner, CDialogBase::DialogProc, reinterpret_cast<LPARAM>(this));
}

INT_PTR CDialogBase::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

INT_PTR CALLBACK CDialogBase::DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialogBase *dialog;

	if (uMsg == WM_INITDIALOG)
	{
		dialog = reinterpret_cast<CDialogBase *>(lParam);
		if (dialog != NULL)
			dialog->hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(dialog));
	}

	dialog = reinterpret_cast<CDialogBase *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (dialog != NULL)
		return dialog->DialogProc(uMsg, wParam, lParam);

	return FALSE;
}
