#include "stdafx.h"
#include "FolderDialog.h"
#include <DLGS.H>
#include <WINUSER.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFolderDialog, CFileDialog)

WNDPROC CFolderDialog::m_wndProc = NULL;

bool	 CFolderDialog::GetFolder(CString& folderpath, const char* szCaption /* = NULL */, HWND hOwner /* = NULL */)
{
	bool retVal = false;  

	// The BROWSEINFO struct tells the shell  
	// how it should display the dialog.  
	BROWSEINFO bi;  
	memset(&bi, 0, sizeof(bi));  
	bi.ulFlags   = BIF_USENEWUI;  
	bi.hwndOwner = hOwner;  
	bi.lpszTitle = szCaption;  

	// must call this if using BIF_USENEWUI  
	::OleInitialize(NULL);  

	// Show the dialog and get the itemIDList for the selected folder.  
	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);  

	if(pIDL != NULL)  
	{  
		// Create a buffer to store the path, then get the path.  
		char buffer[_MAX_PATH] = {'\0'};  
		if(::SHGetPathFromIDList(pIDL, buffer) != 0)  
		{  
			// Set the string value.  
			folderpath = buffer;  
			retVal = true;  
		}         

		// free the item id list  
		CoTaskMemFree(pIDL);  
	}  

	::OleUninitialize();  

	return retVal;
}

CFolderDialog::CFolderDialog(CString* pPath) : CFileDialog(TRUE, NULL, _T("*..*"))
{

}


BEGIN_MESSAGE_MAP(CFolderDialog, CFileDialog)
END_MESSAGE_MAP()

LRESULT CALLBACK WindowProcNew(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	
	if (message ==  WM_COMMAND)
		if (HIWORD(wParam) == BN_CLICKED)
			if (LOWORD(wParam) == IDOK)
			{
				if (CFileDialog* pDlg = (CFileDialog*)CWnd::FromHandle(hwnd))
				{
					TCHAR path[MAX_PATH];
					GetCurrentDirectory(MAX_PATH, path);
					((CFolderDialog*)pDlg->GetDlgItem(0))->m_pPath = CString(path);
					pDlg->EndDialog(IDOK);
					return NULL;
				}
			}
	return CallWindowProc(CFolderDialog::m_wndProc, hwnd, message, wParam, lParam);
}

void CFolderDialog::OnInitDone()
{
	HideControl(edt1);
	HideControl(stc3);
	HideControl(cmb1);
	HideControl(stc2);
	CWnd* pFD = GetParent();
	CRect rectCancel; pFD->GetDlgItem(IDCANCEL)->GetWindowRect(rectCancel);
	pFD->ScreenToClient(rectCancel);
	CRect rectOK; pFD->GetDlgItem(IDOK)->GetWindowRect(rectOK);
	pFD->ScreenToClient(rectOK);
	pFD->GetDlgItem(IDOK)->SetWindowPos(0,rectCancel.left - rectOK.Width() - 4, rectCancel.top, 0,0, SWP_NOZORDER | SWP_NOSIZE);
	CRect rectList2; pFD->GetDlgItem(lst1)->GetWindowRect(rectList2);
	pFD->ScreenToClient(rectList2);
	pFD->GetDlgItem(lst1)->SetWindowPos(0,0,0,rectList2.Width(), abs(rectList2.top - (rectCancel.top - 4)), SWP_NOMOVE | SWP_NOZORDER);
	SetControlText(IDOK, _T("Select"));
	pFD->SetWindowText(_T("Choose folder"));
	m_wndProc = (WNDPROC)SetWindowLong(pFD->m_hWnd, GWL_WNDPROC, (long)WindowProcNew);
}
