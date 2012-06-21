
#include "stdafx.h"
#include "afxwinappex.h"
#include "Barcelona.h"
#include "MainFrm.h"
#include "BarcelonaDoc.h"
#include "BarcelonaView.h"
#include "Guardiola.h"
#include "SplashDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CBarcelonaApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT,		&CBarcelonaApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW,			&CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
CBarcelonaApp::CBarcelonaApp() : m_bHiColorIcons(TRUE), m_pAppSystem(NULL)
{
}

CBarcelonaApp theApp;

/**
 *
 * \return 
 */
BOOL CBarcelonaApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize	= sizeof(InitCtrls);
	InitCtrls.dwICC		= ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	ShowSplashDialog();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	SetRegistryKey(_T("Barcelona0.0.1"));

	LoadStdProfileSettings(4);
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBarcelonaDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CBarcelonaView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/**
 *
 * \return 
 */
int CBarcelonaApp::ExitInstance()
{
	/*
	* Ïú»ÙÏµÍ³
	*/
	if (m_pAppSystem != NULL)
		delete m_pAppSystem;

	return CWinAppEx::ExitInstance();
}



/**
* \ingroup : Barcelona
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-06-22
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CAboutDlg : public CDialog
{
public:
	/**
	 *
	 * \return 
	 */
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

/**
 *
 * \return 
 */
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

/**
 *
 * \param pDX 
 */
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/**
 *
 */
void CBarcelonaApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/**
 *
 */
void CBarcelonaApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, 
		IDR_POPUP_EDIT);

	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, 
		IDR_POPUP_EXPLORER);
}

/**
 *
 */
void CBarcelonaApp::LoadCustomState()
{
}

/**
 *
 */
void CBarcelonaApp::SaveCustomState()
{
}

/**
 *
 */
void CBarcelonaApp::ShowSplashDialog()
{
	CSplashDialog* pCsw = new CSplashDialog("media/Splash.bmp");
	pCsw->ShowSplash();
	
#ifndef _DEBUG
	m_pAppSystem = new Barcelona::System("plugins.cfg", 
		"resources.cfg", false);
#else
	m_pAppSystem = new Barcelona::System("plugins_d.cfg",
		"resources_d.cfg", false);
#endif

	pCsw->CloseSplash();
	delete pCsw;
	pCsw = NULL;
}
