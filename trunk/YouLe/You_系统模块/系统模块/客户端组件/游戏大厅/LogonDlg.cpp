// LogonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "LogonDlg.h"


// CLogonDlg 对话框

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


// CLogonDlg 消息处理程序
