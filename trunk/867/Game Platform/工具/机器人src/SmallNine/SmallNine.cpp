// SmallNine.cpp : ����Ӧ�ó��������Ϊ��
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


	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
