#pragma once
#include "UIGamePage.h"
#include "UIRoomPage.h"
#include "UITablePage.h"

namespace YouLe
{
	//////////////////////////////////////////
	//Page������
	/////////////////////////////////////////
	class UIPageManager
	{
	public:
		UIPageManager(void);
		virtual ~UIPageManager(void);
		
		virtual bool	Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		// ��Ϸ�б�
		UIGamePage*				m_pGamePage;
		// �����б�
		UIRoomPage*				m_pRoomPage;
		// �����б�
		UITablePage*			m_pTablePage;
	};

	extern	UIPageManager		g_UIPageManager;
}