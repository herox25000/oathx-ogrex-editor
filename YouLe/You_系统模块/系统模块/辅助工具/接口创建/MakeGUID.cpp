#include "Stdafx.h"
#include "MakeGUID.h"
#include "MakeGUIDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMakeGUIDApp, CWinApp)
END_MESSAGE_MAP()

CMakeGUIDApp theApp;

//////////////////////////////////////////////////////////////////////////

//构造函数
CMakeGUIDApp::CMakeGUIDApp()
{
}

//初始化函数
BOOL CMakeGUIDApp::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	SetRegistryKey(TEXT("GamePlatForm"));

	CMakeGUIDDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
