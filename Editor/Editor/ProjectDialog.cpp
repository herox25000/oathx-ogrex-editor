// ProjectDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Editor.h"
#include "ProjectDialog.h"
#include "FolderDialog.h"

IMPLEMENT_DYNAMIC(CProjectDialog, CDialog)

CProjectDialog::CProjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDialog::IDD, pParent)
{

}

CProjectDialog::~CProjectDialog()
{
}

void		CProjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SceneTypeBox);
}

BEGIN_MESSAGE_MAP(CProjectDialog, CDialog)
	ON_BN_CLICKED(IDOK,			&CProjectDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,		&CProjectDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1,	&CProjectDialog::OnBnClickedSelectItemDire)
END_MESSAGE_MAP()

BOOL		CProjectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nItem = m_SceneTypeBox.AddString("OctreeSceneManager");
	m_SceneTypeBox.SetCurSel(nItem);

	return TRUE;
}

void		CProjectDialog::OnBnClickedOk()
{
	CString tmp;
	GetDlgItemText(IDC_EDIT1, tmp);
	if (tmp.IsEmpty())
	{
		AfxMessageBox(IDS_STRING_NOMESHSIZE);
		return;
	}
	
	CString sName;
	GetDlgItemText(IDC_EDIT2, sName);
	if (sName.IsEmpty())
	{
		AfxMessageBox(IDS_STRING_NONAME);
		return;
	}

	CString sDire;
	GetDlgItemText(IDC_EDIT3, sDire);
	if (sDire.IsEmpty())
	{
		AfxMessageBox(IDS_STRING_NODIR);
		return;
	}

	OnOK();
}

void		CProjectDialog::OnBnClickedCancel()
{
	OnCancel();
}

void		CProjectDialog::OnBnClickedSelectItemDire()
{
	CString sName("*");
	CFolderDialog dlgSelect(&sName);
	if (dlgSelect.DoModal() == IDOK)
	{
		CString sPath = dlgSelect.GetFolderPath();
		SetDlgItemText(IDC_EDIT3, sPath);
	}
}
