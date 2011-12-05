#include "stdafx.h"
#include "afxwinappex.h"
#include "Editor.h"
#include "MainFrm.h"
#include "Splash.h"

#include "EditorDoc.h"
#include "EditorView.h"

BEGIN_MESSAGE_MAP(CEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CEditorApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

CEditorApp::CEditorApp()
:m_pRoot(NULL)
{
	m_bHiColorIcons = TRUE;
}

CEditorApp theApp;

BOOL		CEditorApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	ShowSplash();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
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
		RUNTIME_CLASS(CEditorDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CEditorView));
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

int			CEditorApp::ExitInstance()
{
	if (m_pRoot != NULL)
		delete m_pRoot;

	m_pRoot = NULL;

	return CWinAppEx::ExitInstance();
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void		CEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void		CEditorApp::PreLoadState()
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

void		CEditorApp::LoadCustomState()
{
}

void		CEditorApp::SaveCustomState()
{
}

void		CEditorApp::ShowSplash()
{
	CSplashWnd* pCsw = new CSplashWnd("media/Splash.bmp");
	pCsw->ShowSplash();
	
#ifdef _DEBUG
	m_pRoot = new Ogre::Root("plugins_d.cfg");
	ASSERT(m_pRoot != NULL);
#else
	m_pRoot = new Ogre::Root("plugins.cfg");
	ASSERT(m_pRoot != NULL);
#endif

#ifdef _DEBUG
	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");
#else
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");
#endif

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	/*
	 *	创建渲染系统
	 */
	Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
	while(pRend != m_pRoot->getAvailableRenderers().end())
	{
		Ogre::String rName = (*pRend)->getName();
		if (rName == "OpenGL Rendering Subsystem")
			break;

		pRend++;
	}
	Ogre::RenderSystem *rsys = *pRend;

	rsys->setConfigOption("Colour Depth", "32" );
	rsys->setConfigOption( "Full Screen", "No" );
	rsys->setConfigOption( "VSync", "No" );
	rsys->setConfigOption( "Video Mode", "800 x 600" );
	rsys->setConfigOption( "Display Frequency", "60" );

	m_pRoot->setRenderSystem( rsys );

	// 不创建渲染窗口
	m_pRoot->initialise(false);

	pCsw->CloseSplash();
	delete pCsw;
	pCsw = NULL;
}

