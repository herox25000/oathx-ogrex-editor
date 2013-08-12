#pragma once
#include "UIGamePage.h"
#include "UIRoomPage.h"
#include "UITablePage.h"
#include "UIFont.h"

namespace YouLe
{
	//////////////////////////////////////////
	//Page管理类
	/////////////////////////////////////////
	class UIPageManager
	{
	public:
		UIPageManager(void);
		virtual ~UIPageManager(void);
		
		virtual bool	Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		// 游戏列表
		UIGamePage*				m_pGamePage;
		// 房间列表
		UIRoomPage*				m_pRoomPage;
		// 桌子列表
		UITablePage*			m_pTablePage;
		// 字体
		UIFont					m_Font;
	};

	extern	UIPageManager		g_UIPageManager;
}