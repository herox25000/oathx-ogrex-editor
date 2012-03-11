#include "stdafx.h"
#include "Xavier.h"
#include "WizardDialog.h"


IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

/**
 *
 * \param /* 
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
void	CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CWizardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWizardDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


/**
 *
 */
void	CWizardDialog::OnBnClickedOk()
{
	OnOK();
}

/**
 *
 */
void	CWizardDialog::OnBnClickedCancel()
{

	OnCancel();
}

/**
 *
 * \return 
 */
BOOL	CWizardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
