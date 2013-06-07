#include "stdafx.h"
#include "OgreEditor.h"
#include "WizardDialog.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

/**
 *
 * \param 
 * \return 
 */
CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CWizardDialog::~CWizardDialog()
{
}

/**
 *
 * \param pDX 
 */
void CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CWizardDialog::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDOK, &CWizardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWizardDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

/**
 *
 */
void CWizardDialog::OnBnClickedButtonBrowse()
{
	if (CFolderDialog::GetFolder(m_szPath))
	{
		SetDlgItemText(IDC_EDIT_SCHEMEPATH, m_szPath);
	}
}

/**
 *
 */
void CWizardDialog::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_SCHEMENAME, m_szName);
	
	if (m_szName.IsEmpty())
		m_szName = "Default.sandbox";

	wmNewScheme evt;
	strcpy(evt.szName, m_szName.GetBuffer());
	strcpy(evt.szPath, m_szPath.GetBuffer());

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame)
	{
		pMainFrame->SendMessage(TARGET_FILEVIEW, WM_NEWSCHEME, (WPARAM)&evt, NULL);
	}

	OnOK();
}

/**
 *
 */
void CWizardDialog::OnBnClickedCancel()
{
	OnCancel();
}
