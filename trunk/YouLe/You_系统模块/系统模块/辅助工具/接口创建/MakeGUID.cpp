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

//���캯��
CMakeGUIDApp::CMakeGUIDApp()
{
}

//��ʼ������
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
