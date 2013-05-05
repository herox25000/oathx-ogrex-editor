// ServerConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallNine.h"
#include "ServerConfig.h"
#include ".\serverconfig.h"


// CServerConfig 对话框

IMPLEMENT_DYNAMIC(CServerConfig, CDialog)
CServerConfig::CServerConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CServerConfig::IDD, pParent)
{
}

CServerConfig::~CServerConfig()
{
}

void CServerConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerConfig, CDialog)
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

BOOL CServerConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadServerConfig();
	return TRUE;
}

void CServerConfig::LoadServerConfig()
{
	UINT nWinControl	= GetPrivateProfileInt("Option", "OpenControl", 0, ".\\PaiJiu.ini");
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

	UINT nWinRate	= GetPrivateProfileInt("Option", "WinRate", 5, ".\\PaiJiu.ini");
	UINT nMaxLose	= GetPrivateProfileInt("Option", "MaxLose", 100000000, ".\\PaiJiu.ini");
	UINT nPlayerMaxWin	= GetPrivateProfileInt("Option", "PlayMaxWin", 100000000, ".\\PaiJiu.ini");

	char szText[MAX_PATH];
	sprintf(szText, "%d", nWinRate);
	SetDlgItemText(IDC_EDIT1, szText);

	sprintf(szText, "%d", nMaxLose);
	SetDlgItemText(IDC_EDIT2, szText);

	sprintf(szText, "%d", nPlayerMaxWin);
	SetDlgItemText(IDC_EDIT3, szText);
}


// CServerConfig 消息处理程序

void CServerConfig::OnBnClickedRadio1()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "0", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio2()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "1", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio3()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "2", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio4()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "3", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio5()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "4", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio6()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "5", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio7()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "6", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio8()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "7", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedRadio9()
{
	bool bRet = WritePrivateProfileString("Option", "OpenControl", "8", ".\\PaiJiu.ini");
	if (!bRet)
	{
		MessageBox("找不到配置文件", NULL, MB_OK);
	}
}

void CServerConfig::OnBnClickedOk()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT1, buffer);
	WritePrivateProfileString("Option", "WinRate", buffer.GetBuffer(), ".\\PaiJiu.ini");

	GetDlgItemText(IDC_EDIT2, buffer);
	WritePrivateProfileString("Option", "MaxLose", buffer.GetBuffer(), ".\\PaiJiu.ini");

	GetDlgItemText(IDC_EDIT3, buffer);
	WritePrivateProfileString("Option", "PlayMaxWin", buffer.GetBuffer(), ".\\PaiJiu.ini");

	OnOK();
}
