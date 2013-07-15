#include "Stdafx.h"
#include "SDKBuilder.h"
#include "SDKBuilderDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSDKBuilderApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CSDKBuilderApp theApp;

//构造函数
CSDKBuilderApp::CSDKBuilderApp()
{
}

//初始化
BOOL CSDKBuilderApp::InitInstance()
{
	//内部初始化
	AfxInitRichEdit();
	InitCommonControls();
	__super::InitInstance();
	AfxEnableControlContainer();
//	SetRegistryKey(szSystemRegKey);

	//初始化界面库
//	IUnknownEx * pIUnknownEx=(IUnknownEx *)m_SkinRecordFile.QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
//	CSkinAttribute::LoadSkinAttribute(pIUnknownEx);

	CSDKBuilderDlg SDKBuilderDlg;
	m_pMainWnd=&SDKBuilderDlg;
	SDKBuilderDlg.DoModal();

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
