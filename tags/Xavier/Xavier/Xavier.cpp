#include "stdafx.h"
#include "afxwinappex.h"
#include "Xavier.h"
#include "MainFrm.h"
#include "XavierDoc.h"
#include "SplashDialog.h"
#include "XavierView.h"
#include "OgreSSSDK.h"


BEGIN_MESSAGE_MAP(CXavierApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT,		&CXavierApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW,			&CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
 CXavierApp::CXavierApp() : m_pXavierLog(NULL)
{
	m_bHiColorIcons = TRUE;
}

CXavierApp theApp;

/**
 *
 * \return 
 */
BOOL	CXavierApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
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
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("Xavier-ogre-editor"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();

	EnableUserTools(ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10, RUNTIME_CLASS(CUserTool), IDR_MENU_ARGS, IDR_MENU_DIRS);

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXavierDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CXavierView));
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

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}


/**
 *
 * \return 
 */
int		CXavierApp::ExitInstance()
{
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(m_pXavierLog);
	if (m_pXavierLog != NULL)
		delete m_pXavierLog;

	/*
	* 销毁系统
	*/
	if (m_pAppSystem != NULL)
		m_pAppSystem->destroy();

	delete m_pAppSystem;

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
void	CXavierApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/**
 *
 */
void	CXavierApp::PreLoadState()
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
void	CXavierApp::LoadCustomState()
{
}

/**
 *
 */
void	CXavierApp::SaveCustomState()
{
}

/**
 *
 */
void	CXavierApp::ShowSplashDialog()
{
	CSplashDialog* pCsw = new CSplashDialog("media/Splash.bmp");
	pCsw->ShowSplash();
	
	// 创建编辑系统
	m_pAppSystem = new Ogre::System();
#ifndef _DEBUG
	m_pAppSystem->create("plugins.cfg", "resources.cfg", false);
#else
	m_pAppSystem->create("plugins_d.cfg", "resources_d.cfg", false);
#endif

	m_pXavierLog = new XavierLog();
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(m_pXavierLog);
	
	pCsw->CloseSplash();
	delete pCsw;
	pCsw = NULL;
}
