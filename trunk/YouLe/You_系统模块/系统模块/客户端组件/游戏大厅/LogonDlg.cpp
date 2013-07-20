#include "stdafx.h"
#include "GamePlaza.h"
#include "LogonDlg.h"


IMPLEMENT_DYNAMIC(CLogonDlg, CDialog)
CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogonDlg::IDD, pParent)
{
}

CLogonDlg::~CLogonDlg()
{
}

void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogonDlg, CDialog)
END_MESSAGE_MAP()
