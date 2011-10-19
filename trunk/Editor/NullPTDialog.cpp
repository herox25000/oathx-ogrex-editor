// NullPTDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Editor.h"
#include "NullPTDialog.h"
#include "FolderDialog.h"
#include "SolutionXML.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CNullPTDialog, CDialog)

CNullPTDialog::CNullPTDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNullPTDialog::IDD, pParent)
{

}

//////////////////////////////////////////////////////////////////////////
CNullPTDialog::~CNullPTDialog()
{
}

//////////////////////////////////////////////////////////////////////////
void		CNullPTDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNullPTDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LL, &CNullPTDialog::OnBnClickedButtonLL)
	ON_BN_CLICKED(IDOK, &CNullPTDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNullPTDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
BOOL		CNullPTDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void		CNullPTDialog::OnBnClickedButtonLL()
{
	CString curPath;

	CFolderDialog dlgOpen(&curPath);
	if (IDOK == dlgOpen.DoModal())
	{
		SetDlgItemText(IDC_EDIT_PATH, curPath);
	}
}

//////////////////////////////////////////////////////////////////////////
void		CNullPTDialog::OnBnClickedOk()
{
	CString sName;
	GetDlgItemText(IDC_EDIT_NAME, sName);

	CString sPath;
	GetDlgItemText(IDC_EDIT_PATH, sPath);

	BOOL bResult = SolutionXML::GetSingleton().Create(sPath,sName);
	if (bResult)
	{
		CMainFrame* pMain = (CMainFrame*)(AfxGetMainWnd());
		ASSERT(pMain != NULL);
		pMain->GetFileView()->CreateSolution(sPath, sPath);
	}

	OnOK();
}

//////////////////////////////////////////////////////////////////////////
void		CNullPTDialog::OnBnClickedCancel()
{
	OnCancel();
}
