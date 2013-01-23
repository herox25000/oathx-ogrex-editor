#include "stdafx.h"
#include "afxwinappex.h"
#include "OgreSystem.h"
#include "XavierEditor.h"
#include "MainFrm.h"
#include "XavierEditorDoc.h"
#include "XavierEditorView.h"
#include "SplashDialog.h"
#include "EditorDebugMessage.h"
#include "EditorTool.h"
#include "EditorToolManager.h"
#include "EditorToolFactoryManager.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CXavierEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT,		&CXavierEditorApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW,			&CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
CXavierEditorApp::CXavierEditorApp() : m_pAppSystem(NULL), m_pDebugLog(NULL)
{
	m_bHiColorIcons = TRUE;
}

CXavierEditorApp theApp;

/**
 *
 * \return 
 */
BOOL	CXavierEditorApp::InitInstance()
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

	SetRegistryKey(_T("XAVIER_EDITOR_VERSION_0"));

	LoadStdProfileSettings(4);
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXavierEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CXavierEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
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
int		CXavierEditorApp::ExitInstance()
{
	delete EditorToolManager::getSingletonPtr();
	delete EditorToolFactoryManager::getSingletonPtr();

	if (m_pDebugLog)
	{
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(m_pDebugLog);
		delete m_pDebugLog;
	}

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
void	CXavierEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/**
 *
 */
void	CXavierEditorApp::PreLoadState()
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
void	CXavierEditorApp::LoadCustomState()
{
}

/**
 *
 */
void	CXavierEditorApp::SaveCustomState()
{
}

/**
 *
 */
void	CXavierEditorApp::ShowSplashDialog()
{
	CSplashDialog* pCsw = new CSplashDialog("media/Splash.bmp");
	pCsw->ShowSplash();
	
	// 创建编辑系统
	m_pAppSystem = new Ogre::System();
#ifndef _DEBUG
	m_pAppSystem->createSystem("plugins.cfg", "resources.cfg", false);
#else
	m_pAppSystem->createSystem("plugins_d.cfg", "resources_d.cfg", false);
#endif
	
	m_pDebugLog = new EditorDebugMessage();
	if (m_pDebugLog)
	{
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(m_pDebugLog);
	}

	new EditorToolFactoryManager();
	new EditorToolManager("Xavier");

	pCsw->CloseSplash();
	delete pCsw;
	pCsw = NULL;
}