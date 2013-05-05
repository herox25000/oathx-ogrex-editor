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
	ON_BN_CLICKED(IDC_RADIO10, OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO17, OnBnClickedRadio17)
	ON_BN_CLICKED(IDC_RADIO16, OnBnClickedRadio16)
END_MESSAGE_MAP()

BOOL CServerConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadServerConfig();
	return TRUE;
}

void CServerConfig::LoadServerConfig()
{
	UINT nWinControl	= GetPrivateProfileInt("Option", "OpenControl", 0, ".\\100nnServer.ini");
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
	case 9:
		((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(TRUE);
		break;
	case 10:
		((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(TRUE);
		break;
	case 11:
		((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(TRUE);
		break;
	case 12:
		((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(TRUE);
		break;
	case 13:
		((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(TRUE);
		break;
	case 14:
		((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(TRUE);
		break;
	case 15:
		((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(TRUE);
		break;
	case 16:
		((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(TRUE);
		break;
	default:
		break;
	}

}


// CServerConfig 消息处理程序

void CServerConfig::OnBnClickedRadio1()
{
	WritePrivateProfileString("Option", "OpenControl", "0", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio2()
{
	WritePrivateProfileString("Option", "OpenControl", "1", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio3()
{
	WritePrivateProfileString("Option", "OpenControl", "2", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio4()
{
	WritePrivateProfileString("Option", "OpenControl", "3", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio5()
{
	WritePrivateProfileString("Option", "OpenControl", "4", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio6()
{
	WritePrivateProfileString("Option", "OpenControl", "5", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio7()
{
	WritePrivateProfileString("Option", "OpenControl", "6", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio8()
{
	WritePrivateProfileString("Option", "OpenControl", "7", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio9()
{
	WritePrivateProfileString("Option", "OpenControl", "8", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio10()
{
	WritePrivateProfileString("Option", "OpenControl", "9", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio11()
{
	WritePrivateProfileString("Option", "OpenControl", "10", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio12()
{
	WritePrivateProfileString("Option", "OpenControl", "11", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio13()
{
	WritePrivateProfileString("Option", "OpenControl", "12", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio14()
{
	WritePrivateProfileString("Option", "OpenControl", "13", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio15()
{
	WritePrivateProfileString("Option", "OpenControl", "14", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio16()
{
	WritePrivateProfileString("Option", "OpenControl", "15", ".\\100nnServer.ini");
}

void CServerConfig::OnBnClickedRadio17()
{
	WritePrivateProfileString("Option", "OpenControl", "16", ".\\100nnServer.ini");
}

