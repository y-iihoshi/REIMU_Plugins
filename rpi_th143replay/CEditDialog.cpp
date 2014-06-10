#include <cstring>
#include <windowsx.h>
#include "resource.h"
#include "CEditDialog.h"
#include "CTh143Replay.h"
#include "..\rpi_threplay\smart_array.h"
#include "..\rpi_threplay\sueLib_LE.h"

CEditDialog::CEditDialog(LPCTSTR lpszFilename, int nMaxTextSize)
	: lpszFilename(lpszFilename), nMaxTextSize(nMaxTextSize)
{
}

CEditDialog::~CEditDialog()
{
}

INT_PTR CEditDialog::Show(HINSTANCE hInst, HWND hWndOwner)
{
	return base::Show(hInst, hWndOwner, MAKEINTRESOURCE(IDD_EDIT));
}

INT_PTR CEditDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(this->Handle(), WM_INITDIALOG, this->OnInitDialog);
		HANDLE_MSG(this->Handle(), WM_COMMAND, this->OnCommand);
		HANDLE_MSG(this->Handle(), WM_CLOSE, this->OnClose);
	}

	return FALSE;
}

BOOL CEditDialog::OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hWndEdit = ::GetDlgItem(hwnd, IDC_EDIT);
	Edit_LimitText(hWndEdit, this->nMaxTextSize);

	HFONT hFont = CreateFont(
		14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, (DEFAULT_PITCH | FF_DONTCARE),
		TEXT("ÇlÇr ÉSÉVÉbÉN"));
	SetWindowFont(hWndEdit, hFont, TRUE);

	smart_array<char> buf;
	if (File2Memory(this->lpszFilename, buf))
	{
		const char *pComment = NULL;
		size_t size = 0;
		int retval = CTh143Replay().GetComment(buf.GetPtr(), buf.GetSize(), &pComment, &size);
		if (retval == RET_OK)
			Edit_SetText(hWndEdit, pComment);
	}

	return TRUE;
}

void CEditDialog::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDOK:
		{
			LPTSTR lpszBuffer = new TCHAR[this->nMaxTextSize + 1];
			if (lpszBuffer != NULL)
			{
				HWND hWndEdit = ::GetDlgItem(hwnd, IDC_EDIT);
				int nLength = Edit_GetText(hWndEdit, lpszBuffer, this->nMaxTextSize);
				CTh143Replay().WriteComment(this->lpszFilename, lpszBuffer, nLength + 1);
				delete [] lpszBuffer;
			}
		}
		// fall through
	case IDCANCEL:
		EndDialog(hwnd, id);
	}
}

void CEditDialog::OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}
