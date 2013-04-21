#include "stdafx.h"
#include "HKFiveAndroid.h"
#include "BankerDialog.h"
#include "HKFiveDlg.h"

IMPLEMENT_DYNAMIC(CBankerDialog, CDialog)
CBankerDialog::CBankerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBankerDialog::IDD, pParent)
{
	m_bType = false;
}

CBankerDialog::~CBankerDialog()
{
}

void CBankerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBankerDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

void CBankerDialog::SetText(LPCTSTR lpszText)
{
	SetDlgItemText(IDC_STATIC_BANKER, lpszText);
}

void CBankerDialog::SetType(bool bType)
{
	m_bType = bType;
}

void CBankerDialog::OnBnClickedOk()
{
	HKFiveDlg* pDlg = (HKFiveDlg*)(AfxGetMainWnd());
	if (pDlg)
	{
		CString buffer;
		GetDlgItemText(IDC_EDIT_BANKER, buffer);

		INT64 nScore = _atoi64(buffer.GetBuffer());
		if (m_bType)
			pDlg->SaveScore(nScore);
		else
			pDlg->GetScore(nScore);
	}

	OnOK();
}

void CBankerDialog::OnBnClickedCancel()
{
	OnCancel();
}
