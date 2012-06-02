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
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	ShowSplashDialog();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Xavier-ogre-editor"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();

	EnableUserTools(ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10, RUNTIME_CLASS(CUserTool), IDR_MENU_ARGS, IDR_MENU_DIRS);

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXavierDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CXavierView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
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
	* ����ϵͳ
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
	
	// �����༭ϵͳ
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
