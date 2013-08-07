#include "StdAfx.h"
#include ".\uipagemanager.h"

namespace YouLe
{

#define IDP_GAME_PAGE						55530
#define IDP_ROOM_PAGE						55531
#define IDP_TABLE_PAGE						55532


	UIPageManager		g_UIPageManager;
	///////////////////////////////////////////////
	//Page������
	///////////////////////////////////////////////
	UIPageManager::UIPageManager(void)
	{
		m_pGamePage = NULL;
	}

	UIPageManager::~UIPageManager(void)
	{
	}

	bool	UIPageManager::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		// ������Ϸҳ
		m_pGamePage	= new UIGamePage();
		m_pGamePage->Create(IDP_GAME_PAGE, rect, pAttach, pProcess, pParent);
		// ��������ҳ
		m_pRoomPage = new UIRoomPage();
		m_pRoomPage->Create(IDP_ROOM_PAGE, rect, pAttach, pProcess, pParent);
		// ��������ҳ
		m_pTablePage = new UITablePage();
		m_pTablePage->Create(IDP_TABLE_PAGE, rect, pAttach, pProcess, pParent);
		
		m_pRoomPage->VisibleWidget(false);
		m_pTablePage->VisibleWidget(false);

		return true;
	}
}