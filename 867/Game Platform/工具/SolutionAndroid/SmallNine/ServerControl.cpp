// ServerControl.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallNine.h"
#include "ServerControl.h"
#include ".\servercontrol.h"

// CServerControl 对话框

IMPLEMENT_DYNAMIC(CServerControl, CDialog)
CServerControl::CServerControl(CWnd* pParent /*=NULL*/)
	: CDialog(CServerControl::IDD, pParent)
{
}

CServerControl::~CServerControl()
{
}

void CServerControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerControl, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnBnClickedRadio9)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CServerControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadServerConfig();
	return TRUE;
}

void CServerControl::LoadServerConfig()
{
	UINT nWinControl	= GetPrivateProfileInt("Option", "OpenControl", 0, ".\\XiaoJiu.ini");
	switch(nWinControl)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		break;
	case 1:
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
		break;
	case 4:
		((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);
		break;
	case 5:
		((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE);
		break;
	case 6:
		((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(TRUE);
		break;
	case 7:
		((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(TRUE);
		break;
	case 8:
		((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(TRUE);
		break;
	default:
		break;
	}

	UINT nWinRate	= GetPrivateProfileInt("Option", "WinRate", 5, ".\\XiaoJiu.ini");
	UINT nMaxLose	= GetPrivateProfileInt("Option", "MaxLose", 100000000, ".\\XiaoJiu.ini");
	UINT nPlayerMaxWin	= GetPrivateProfileInt("Option", "PlayMaxWin", 100000000, ".\\XiaoJiu.ini");

	char szText[MAX_PATH];
	sprintf(szText, "%d", nWinRate);
	SetDlgItemText(IDC_EDIT1, szText);

	sprintf(szText, "%d", nMaxLose);
	SetDlgItemText(IDC_EDIT2, szText);

	sprintf(szText, "%d", nPlayerMaxWin);
	SetDlgItemText(IDC_EDIT3, szText);
}


// CServerControl 消息处理程序

void CServerControl::OnBnClickedRadio1()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "0", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio2()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "1", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio3()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "2", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio4()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "3", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio5()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "4", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio6()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "5", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio7()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "6", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio8()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "7", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedRadio9()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "8", ".\\XiaoJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerControl::OnBnClickedOk()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT1, buffer);
	WritePrivateProfileString("Option", "WinRate", buffer.GetBuffer(), ".\\XiaoJiu.ini");

	GetDlgItemText(IDC_EDIT2, buffer);
	WritePrivateProfileString("Option", "MaxLose", buffer.GetBuffer(), ".\\XiaoJiu.ini");

	GetDlgItemText(IDC_EDIT3, buffer);
	WritePrivateProfileString("Option", "PlayMaxWin", buffer.GetBuffer(), ".\\XiaoJiu.ini");

	OnOK();
}
