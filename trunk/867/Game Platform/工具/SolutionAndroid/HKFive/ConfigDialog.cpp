#include "stdafx.h"
#include "HKFiveAndroid.h"
#include "ConfigDialog.h"

IMPLEMENT_DYNAMIC(CConfigDialog, CDialog)
CConfigDialog::CConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDialog::IDD, pParent)
{
}

CConfigDialog::~CConfigDialog()
{
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDB_LOADCONFIG, OnBnClickedLoadconfig)
	ON_BN_CLICKED(IDB_SAVECONFIG, OnBnClickedSaveconfig)
END_MESSAGE_MAP()

#define SMALLNINE_CFG_FILENAME	"./HKFiveAndroid.cfg"

BOOL CConfigDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	bool bResult = O2::ConfigFile::GetSingleton().LoadConfig(SMALLNINE_CFG_FILENAME);
	if (!bResult)
	{
		SetDlgItemText(IDC_EDIT1,	"192.168.1.102");
		SetDlgItemText(IDC_EDIT2,	"12061");
		SetDlgItemText(IDC_EDIT3,	"d746e3733dff946b0db30eb3fb0069c4");
		SetDlgItemText(IDC_EDIT4,	"10");
		SetDlgItemText(IDC_EDIT5,	"200");
		SetDlgItemText(IDC_EDIT6,	"60");
		SetDlgItemText(IDC_EDIT7,	"50");
		SetDlgItemText(IDC_EDIT9,	"30000000");
		SetDlgItemText(IDC_EDIT10,	"30");
		SetDlgItemText(IDC_EDIT11,	"180");
		SetDlgItemText(IDC_EDIT12,	"1");
		SetDlgItemText(IDC_EDIT13,	"5");
		SetDlgItemText(IDC_EDIT14,	"10");
		SetDlgItemText(IDC_EDIT15,	"1");
		SetDlgItemText(IDC_EDIT16,	"20");
		SetDlgItemText(IDC_EDIT15,	"2000");
		SetDlgItemText(IDC_EDIT16,	"300000");
	}
	else
	{
		OnLoadConfig();
	}

	return TRUE;
}

void CConfigDialog::OnAplyConfig()
{
	O2::SAppConfig* pApp = O2::ConfigFile::GetSingleton().GetAppConfig();
	if (pApp)
	{
		CString buffer;
		GetDlgItemText(IDC_EDIT1,	buffer);
		strcpy(pApp->chIPAddrss,	buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT2,	buffer);
		pApp->wPort			= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT3,	buffer);
		strcpy(pApp->chMD5,			buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT4,	buffer);
		pApp->dwStartID		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT5,	buffer);
		pApp->dwEndID		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT6,	buffer);
		pApp->dwOnline		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT7,	buffer);
		pApp->wBankerRate	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT9,	buffer);
		pApp->nMaxWinScore	= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT10,	buffer);
		pApp->wMinTime		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT11,	buffer);
		pApp->wMaxTime		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT12,	buffer);
		pApp->wMinWorkTime	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT13,	buffer);
		pApp->wMaxWorkTime	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT14,	buffer);
		pApp->wPlaceRate	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT15,	buffer);
		pApp->wMinTableID	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT16,	buffer);
		pApp->wMaxTableID	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT17,	buffer);
		pApp->nMinScore		= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT18,	buffer);
		pApp->nMinScore		= _atoi64(buffer.GetBuffer());
	}
}

void CConfigDialog::OnLoadConfig()
{
	O2::SAppConfig* pConfig = O2::ConfigFile::GetSingleton().GetAppConfig();

	SetDlgItemText(IDC_EDIT1,	pConfig->chIPAddrss);

	char szText[256];
	sprintf(szText, "%d", pConfig->wPort);
	SetDlgItemText(IDC_EDIT2,	szText);

	sprintf(szText, "%s", pConfig->chMD5);
	SetDlgItemText(IDC_EDIT3,	szText);

	sprintf(szText, "%d", pConfig->dwStartID);
	SetDlgItemText(IDC_EDIT4,	szText);

	sprintf(szText, "%d", pConfig->dwEndID);
	SetDlgItemText(IDC_EDIT5,	szText);

	sprintf(szText, "%d", pConfig->dwOnline);
	SetDlgItemText(IDC_EDIT6,	szText);

	sprintf(szText, "%d", pConfig->wBankerRate);
	SetDlgItemText(IDC_EDIT7,	szText);

	sprintf(szText, "%I64d", pConfig->nMaxWinScore);
	SetDlgItemText(IDC_EDIT9,	szText);

	sprintf(szText, "%d", pConfig->wMinTime);
	SetDlgItemText(IDC_EDIT10,	szText);

	sprintf(szText, "%d", pConfig->wMaxTime);
	SetDlgItemText(IDC_EDIT11,	szText);

	sprintf(szText, "%d", pConfig->wMinWorkTime);
	SetDlgItemText(IDC_EDIT12,	szText);

	sprintf(szText, "%d", pConfig->wMaxWorkTime);
	SetDlgItemText(IDC_EDIT13,	szText);

	sprintf(szText, "%d", pConfig->wPlaceRate);
	SetDlgItemText(IDC_EDIT14,	szText);

	sprintf(szText, "%d", pConfig->wMinTableID);
	SetDlgItemText(IDC_EDIT15,	szText);

	sprintf(szText, "%d", pConfig->wMaxTableID);
	SetDlgItemText(IDC_EDIT16,	szText);

	sprintf(szText, "%I64d", pConfig->nMinScore);
	SetDlgItemText(IDC_EDIT17,	szText);

	sprintf(szText, "%I64d", pConfig->nMaxScore);
	SetDlgItemText(IDC_EDIT18,	szText);
}

void CConfigDialog::OnBnClickedOk()
{
	OnAplyConfig();
	OnOK();
}

void CConfigDialog::OnBnClickedCancel()
{
	OnCancel();
}

void CConfigDialog::OnBnClickedLoadconfig()
{
	CFileDialog dlg(TRUE);
	if (IDOK == dlg.DoModal())
	{
		CString szPath = dlg.GetPathName();
		if (!szPath.IsEmpty())
		{
			if (O2::ConfigFile::GetSingleton().LoadConfig(szPath.GetBuffer()))
			{
				OnLoadConfig();
			}
		}
	}
}


void CConfigDialog::OnBnClickedSaveconfig()
{
	CString szPath = O2::ConfigFile::GetSingleton().GetFilePath();
	if (szPath.IsEmpty())
	{
		CFileDialog dlg(FALSE);
		if (IDOK == dlg.DoModal())
		{
			szPath = dlg.GetPathName();
			if (!szPath.IsEmpty())
			{
				OnAplyConfig();
				O2::ConfigFile::GetSingleton().SaveConfig(szPath.GetBuffer());
			}
		}
	}
	else
	{
		OnAplyConfig();
		O2::ConfigFile::GetSingleton().SaveConfig(szPath.GetBuffer());
	}
}
