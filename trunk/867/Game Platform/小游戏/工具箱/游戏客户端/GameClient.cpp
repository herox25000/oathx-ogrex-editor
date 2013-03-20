#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"

//应用程序对象
CGameClientApp theApp;

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameClientApp::CGameClientApp()
{
}

//析构函数
CGameClientApp::~CGameClientApp() 
{
}

//初始化函数
BOOL CGameClientApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, "CFL_ToolBox");
	if( hMutex && GetLastError() == ERROR_ALREADY_EXISTS )
	{
		CloseHandle( hMutex );
		::MessageBox(NULL, "此程序正在运行,请先退出另一个实例!", "工具箱", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	__super::InitInstance();

	//内部初始化
	InitCommonControls();

	//创建组件
	if (m_PlatformResourceModule.CreateInstance()==false) 
		return false;

	CSkinImage::ms_pImageMap = m_PlatformResourceModule->GetImageMap();
	//获取资源
	//m_PlatformResourceModule->GetChatExpViewImage(&m_ChatExpViewImage);
	m_PlatformResourceModule->GetGameFrameImage(&m_GameFrameImage);
	//m_PlatformResourceModule->GetPropertyViewImage(&m_PropertyViewImage);
	//m_PlatformResourceModule->GetVideoFrameImage(&m_VideoFrameImage);
	//m_PlatformResourceModule->GetPropertyMenuImage(&m_PropertyMenuImage);
	//m_PlatformResourceModule->GetGiftFlashImage(&m_GiftFlashImage);

	//加载资源
	ISkinResource * pISkinResource=(ISkinResource *)m_PlatformResourceModule->GetSkinResource(IID_ISkinResource,
		VER_ISkinResource);
	if (CSkinResourceManager::LoadSkinResource(pISkinResource)==false)
		return false;

	CGameClientDlg dlg;
	dlg.DoModal();

	return TRUE;
}

//退出消息
int CGameClientApp::ExitInstance()
{
	return __super::ExitInstance();
}

//////////////////////////////////////////////////////////////////////////
