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
	//�������
	if (m_PlatformResourceModule.CreateInstance()==false) 
		return false;

	CSkinImage::ms_pImageMap = m_PlatformResourceModule->GetImageMap();
	//��ȡ��Դ
	//m_PlatformResourceModule->GetChatExpViewImage(&m_ChatExpViewImage);
	m_PlatformResourceModule->GetGameFrameImage(&m_GameFrameImage);
	//m_PlatformResourceModule->GetPropertyViewImage(&m_PropertyViewImage);
	//m_PlatformResourceModule->GetVideoFrameImage(&m_VideoFrameImage);
	//m_PlatformResourceModule->GetPropertyMenuImage(&m_PropertyMenuImage);
	//m_PlatformResourceModule->GetGiftFlashImage(&m_GiftFlashImage);

	//������Դ
	ISkinResource * pISkinResource=(ISkinResource *)m_PlatformResourceModule->GetSkinResource(IID_ISkinResource,
		VER_ISkinResource);
	if (CSkinResourceManager::LoadSkinResource(pISkinResource)==false)
		return false;

	return TRUE;
}

//�˳���Ϣ
int CGameClientApp::ExitInstance()
{
	return __super::ExitInstance();
}

//////////////////////////////////////////////////////////////////////////
