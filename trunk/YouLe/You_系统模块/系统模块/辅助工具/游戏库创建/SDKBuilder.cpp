#include "Stdafx.h"
#include "SDKBuilder.h"
#include "SDKBuilderDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSDKBuilderApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CSDKBuilderApp theApp;

//���캯��
CSDKBuilderApp::CSDKBuilderApp()
{
}

//��ʼ��
BOOL CSDKBuilderApp::InitInstance()
{
	//�ڲ���ʼ��
	AfxInitRichEdit();
	InitCommonControls();
	__super::InitInstance();
	AfxEnableControlContainer();
//	SetRegistryKey(szSystemRegKey);

	//��ʼ�������
//	IUnknownEx * pIUnknownEx=(IUnknownEx *)m_SkinRecordFile.QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
//	CSkinAttribute::LoadSkinAttribute(pIUnknownEx);

	CSDKBuilderDlg SDKBuilderDlg;
	m_pMainWnd=&SDKBuilderDlg;
	SDKBuilderDlg.DoModal();

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
