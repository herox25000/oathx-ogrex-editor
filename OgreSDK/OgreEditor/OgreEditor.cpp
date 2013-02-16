#include "stdafx.h"
#include "afxwinappex.h"
#include "OgreEditor.h"
#include "MainFrm.h"
#include "SplashDialog.h"
#include "OgreEditorDoc.h"
#include "OgreEditorView.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(COgreEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT,		&COgreEditorApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW,			&CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
COgreEditorApp::COgreEditorApp() : m_pAppSystem(NULL)
{
	m_bHiColorIcons = TRUE;
}

COgreEditorApp theApp;

/**
 *
 * \return 
 */
BOOL	COgreEditorApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize	= sizeof(InitCtrls);
	InitCtrls.dwICC		= ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	ShowSplashDialog();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	SetRegistryKey(_T("OGRE_EDITOR_VERSION_0.0.1"));

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
		RUNTIME_CLASS(COgreEditorDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(COgreEditorView));
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
int		COgreEditorApp::ExitInstance()
{
	/*
	* 销毁系统
	*/
	if (m_pAppSystem != NULL)
	{
		m_pAppSystem->clearUp();
		delete m_pAppSystem;
	}

	return CWinAppEx::ExitInstance();
}



/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-03-08
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
void	CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/**
 *
 */
void	COgreEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/**
 *
 */
void	COgreEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

/**
 *
 */
void	COgreEditorApp::LoadCustomState()
{
}

/**
 *
 */
void	COgreEditorApp::SaveCustomState()
{
}

/**
 *
 */
void	COgreEditorApp::ShowSplashDialog()
{
	CSplashDialog* pCsw = new CSplashDialog("media/Splash.bmp");
	pCsw->ShowSplash();
	
	try{
		// 创建编辑系统
		m_pAppSystem = new EditorSystem();
#ifndef _DEBUG
		m_pAppSystem->createEditorSystem("plugins.cfg", "resources.cfg", false);
#else
		m_pAppSystem->createEditorSystem("plugins_d.cfg", "resources_d.cfg", false);
#endif
	}
	catch(Exception& e)
	{
		AfxMessageBox(_T(e.getFullDescription().c_str()));
	}

	pCsw->CloseSplash();
	delete pCsw;
	pCsw = NULL;
}