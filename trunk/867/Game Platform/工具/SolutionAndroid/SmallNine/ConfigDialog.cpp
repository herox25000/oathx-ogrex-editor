#include "stdafx.h"
#include "SmallNine.h"
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

#define SMALLNINE_CFG_FILENAME	"./SmallNine.cfg"

BOOL CConfigDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	bool bResult = O2::ConfigFile::GetSingleton().LoadConfig(SMALLNINE_CFG_FILENAME);
	if (!bResult)
	{
		SetDlgItemText(IDC_EDIT1,	"125.90.64.21");
		SetDlgItemText(IDC_EDIT2,	"11021");
		SetDlgItemText(IDC_EDIT3,	"d746e3733dff946b0db30eb3fb0069c4");
		SetDlgItemText(IDC_EDIT4,	"10");
		SetDlgItemText(IDC_EDIT5,	"240");
		SetDlgItemText(IDC_EDIT6,	"45");
		SetDlgItemText(IDC_EDIT7,	"5");
		SetDlgItemText(IDC_EDIT8,	"8");
		SetDlgItemText(IDC_EDIT9,	"60000000");
		SetDlgItemText(IDC_EDIT10,	"30");
		SetDlgItemText(IDC_EDIT11,	"120");
		SetDlgItemText(IDC_EDIT12,	"3");
		SetDlgItemText(IDC_EDIT13,	"10");
		SetDlgItemText(IDC_EDIT14,	"1000000");
		SetDlgItemText(IDC_EDIT15,	"300000000");
		SetDlgItemText(IDC_EDIT16,	"7");
		SetDlgItemText(IDC_EDIT17,  "10");
		SetDlgItemText(IDC_EDIT18,	"20");
		SetDlgItemText(IDC_EDIT19,  "50");
		SetDlgItemText(IDC_EDIT20,  "15");
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
		pApp->wMaxDeque		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT8,	buffer);
		pApp->wMaxUpBanker	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT9,	buffer);
		pApp->nMaxWinScore	= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT10,	buffer);
		pApp->wMinTime		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT11,	buffer);
		pApp->wMaxTime		= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT12,	buffer);
		pApp->wMinPlaceTime	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT13,	buffer);
		pApp->wMaxPlaceTime	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT14,	buffer);
		pApp->nMinScore		= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT15,	buffer);
		pApp->nMaxScore		= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT16,	buffer);
		pApp->wPlaceRate	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT17,	buffer);
		pApp->wHunMillionRate	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT18,	buffer);
		pApp->wTenMillionRate1	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT19,	buffer);
		pApp->wTenMillionRate2	= atol(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT20,	buffer);
		pApp->wMaxPlaceRate	= atol(buffer.GetBuffer());
	}
}

void CConfigDialog::OnLoadConfig()
{
	O2::SAppConfig* pConfig = O2::ConfigFile::GetSingleton().GetAppConfig();

	SetDlgItemText(IDC_EDIT1,	pConfig->chIPAddrss);

	char szText[256];
	sprintf(szText, "%d", pConfig->wPort);
	SetDlgItemText(IDC_EDIT2,	szText);

	SetDlgItemText(IDC_EDIT3,	pConfig->chMD5);

	sprintf(szText, "%d", pConfig->dwStartID);
	SetDlgItemText(IDC_EDIT4,	szText);

	sprintf(szText, "%d", pConfig->dwEndID);
	SetDlgItemText(IDC_EDIT5,	szText);

	sprintf(szText, "%d", pConfig->dwOnline);
	SetDlgItemText(IDC_EDIT6,	szText);

	sprintf(szText, "%d", pConfig->wMaxDeque);
	SetDlgItemText(IDC_EDIT7,	szText);

	sprintf(szText, "%d", pConfig->wMaxUpBanker);
	SetDlgItemText(IDC_EDIT8,	szText);

	sprintf(szText, "%I64d", pConfig->nMaxWinScore);
	SetDlgItemText(IDC_EDIT9,	szText);

	sprintf(szText, "%d", pConfig->wMinTime);
	SetDlgItemText(IDC_EDIT10,	szText);

	sprintf(szText, "%d", pConfig->wMaxTime);
	SetDlgItemText(IDC_EDIT11,	szText);

	sprintf(szText, "%d", pConfig->wMinPlaceTime);
	SetDlgItemText(IDC_EDIT12,	szText);

	sprintf(szText, "%d", pConfig->wMaxPlaceTime);
	SetDlgItemText(IDC_EDIT13,	szText);

	sprintf(szText, "%I64d", pConfig->nMinScore);
	SetDlgItemText(IDC_EDIT14,	szText);

	sprintf(szText, "%I64d", pConfig->nMaxScore);
	SetDlgItemText(IDC_EDIT15,	szText);

	sprintf(szText, "%d", pConfig->wPlaceRate);
	SetDlgItemText(IDC_EDIT16,	szText);

	sprintf(szText, "%d", pConfig->wHunMillionRate);
	SetDlgItemText(IDC_EDIT17,	szText);

	sprintf(szText, "%d", pConfig->wTenMillionRate1);
	SetDlgItemText(IDC_EDIT18,	szText);

	sprintf(szText, "%d", pConfig->wTenMillionRate2);
	SetDlgItemText(IDC_EDIT19,	szText);

	sprintf(szText, "%d", pConfig->wMaxPlaceRate);
	SetDlgItemText(IDC_EDIT20,	szText);
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
