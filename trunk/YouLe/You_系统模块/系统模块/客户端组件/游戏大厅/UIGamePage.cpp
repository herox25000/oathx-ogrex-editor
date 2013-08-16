#include "Stdafx.h"
#include "UIGamePage.h"

namespace YouLe
{
#define IDP_GAME_VIEW						55530
#define IDP_ROOM_VIEW						55531
#define IDP_TABLE_VIEW						55532

	// 构造函数
	UIGamePage::UIGamePage()
		: m_pGameView(NULL)
	{

	}

	// 析构函数
	UIGamePage::~UIGamePage()
	{
		
	}

	// 窗口控件
	BOOL	UIGamePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		m_pGameView = new UIGameView();
		m_pGameView->Create(IDP_GAME_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);
		// 创建房间页
		m_pRoomView = new UIRoomPage();
		m_pRoomView->Create(IDP_ROOM_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);
		// 创建桌子页
		m_pTableView = new UITablePage();
		m_pTableView->Create(IDP_TABLE_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);

		VisibleWidget(FALSE);

		return TRUE;
	}

	void UIGamePage::ShowRoomView( CListKind* pKind )
	{
		if(!m_pRoomView->ShowRoomList(pKind))
		{
			ShowMessageBox("对不起，游戏服务器没开启！",MB_ICONQUESTION);
			return;
		}
		m_pGameView->VisibleWidget(FALSE);
		m_pRoomView->VisibleWidget(TRUE);	
	}

	void UIGamePage::VisibleTrigger()
	{
		m_pGameView->VisibleWidget(TRUE);
		m_pRoomView->VisibleWidget(FALSE);
		m_pTableView->VisibleWidget(FALSE);
	}

}