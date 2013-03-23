#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"

//Ӧ�ó������
CGameClientApp theApp;

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientApp::CGameClientApp()
{
}

//��������
CGameClientApp::~CGameClientApp() 
{
}

//��ʼ������
BOOL CGameClientApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, "CFL_ToolBox");
	if( hMutex && GetLastError() == ERROR_ALREADY_EXISTS )
	{
		CloseHandle( hMutex );
		::MessageBox(NULL, "�˳�����������,�����˳���һ��ʵ��!", "������", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	__super::InitInstance();

	//�ڲ���ʼ��
	InitCommonControls();

	CGameClientDlg dlg;
	dlg.DoModal();

	return TRUE;
}

//�˳���Ϣ
int CGameClientApp::ExitInstance()
{
	return __super::ExitInstance();
}

//////////////////////////////////////////////////////////////////////////
