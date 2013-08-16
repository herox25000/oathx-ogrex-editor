#ifndef _____UIGamePage_H
#define _____UIGamePage_H

#include "UIPngButton.h"
#include "UIGameItem.h"
#include "UIRoomPage.h"
#include "UITablePage.h"

namespace YouLe
{
	// 游戏专区
	class UIGamePage : public UIWidget, public UIProcess
	{
	public:
		// 构造函数
		UIGamePage();
		// 析构函数
		virtual ~UIGamePage();
		
		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		virtual void		VisibleTrigger();
	public:
		void				ShowRoomView(CListKind* pKind);

	public:
		//游戏视图
		UIGameView*			m_pGameView;
		//房间视图
		UIRoomPage*			m_pRoomView;
		//桌子视图
		UITablePage*		m_pTableView;
	};
}

#endif