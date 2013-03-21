// SmallNine.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "SmallNine.h"
#include "SmallNineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CSmallNineApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()



CSmallNineApp::CSmallNineApp()
{

}

CSmallNineApp theApp;

BOOL CSmallNineApp::InitInstance()
{

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CSmallNineDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}

	return FALSE;
}
