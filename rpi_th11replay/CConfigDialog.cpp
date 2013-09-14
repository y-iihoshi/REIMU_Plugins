#include <cstring>
#include "windowsx.h"
#include "resource.h"
#include "CConfigDialog.h"
#include "CTh11Config.h"

CConfigDialog::CConfigDialog(CTh11Config *pConfig)
	: pConfig(pConfig)
{
}

CConfigDialog::~CConfigDialog()
{
}

INT_PTR CConfigDialog::Show(HINSTANCE hInst, HWND hWndOwner)
{
	return base::Show(hInst, hWndOwner, MAKEINTRESOURCE(IDD_CONFIG));
}

INT_PTR CConfigDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(this->Handle(), WM_INITDIALOG, this->OnInitDialog);
		HANDLE_MSG(this->Handle(), WM_COMMAND, this->OnCommand);
		HANDLE_MSG(this->Handle(), WM_CLOSE, this->OnClose);
	}

	return FALSE;
}

BOOL CConfigDialog::OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	switch (this->pConfig->GetNameBlt())
	{
	case CTh11Config::NAME_BLT_EN:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_EN), BST_CHECKED);
		break;
	case CTh11Config::NAME_BLT_JA_FULL:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_JA_FULL), BST_CHECKED);
		break;
	case CTh11Config::NAME_BLT_JA_REPLAY:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_JA_REPLAY), BST_CHECKED);
		break;
	}

	switch (this->pConfig->GetCommentBlt())
	{
	case CTh11Config::COMMENT_BLT_ALL:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_ALL), BST_CHECKED);
		break;
	case CTh11Config::COMMENT_BLT_FIRST:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_FIRST), BST_CHECKED);
		break;
	case CTh11Config::COMMENT_BLT_CONCAT:
		Button_SetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_CONCAT), BST_CHECKED);
		break;
	}

	return TRUE;
}

void CConfigDialog::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDOK:
		if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_EN)) == BST_CHECKED)
			this->pConfig->SetNameBlt(CTh11Config::NAME_BLT_EN);
		else if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_JA_FULL)) == BST_CHECKED)
			this->pConfig->SetNameBlt(CTh11Config::NAME_BLT_JA_FULL);
		else if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_CHARA_JA_REPLAY)) == BST_CHECKED)
			this->pConfig->SetNameBlt(CTh11Config::NAME_BLT_JA_REPLAY);

		if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_ALL)) == BST_CHECKED)
			this->pConfig->SetCommentBlt(CTh11Config::COMMENT_BLT_ALL);
		else if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_FIRST)) == BST_CHECKED)
			this->pConfig->SetCommentBlt(CTh11Config::COMMENT_BLT_FIRST);
		else if (Button_GetCheck(::GetDlgItem(hwnd, IDC_RADIO_COMMENT_CONCAT)) == BST_CHECKED)
			this->pConfig->SetCommentBlt(CTh11Config::COMMENT_BLT_CONCAT);

		this->pConfig->Save((HINSTANCE)::GetWindowLong(hwnd, GWL_HINSTANCE));
		// fall through

	case IDCANCEL:
		EndDialog(hwnd, id);
		break;
	}
}

void CConfigDialog::OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}
