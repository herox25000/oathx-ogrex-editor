#ifndef _____UIGamePage_H
#define _____UIGamePage_H

#include "UIPngButton.h"
#include "UIGameItem.h"

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
		// 设置当前显示页
		virtual void		SetPage(INT nPage);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
	public:
		UIGameView*			m_pGameView;
	};
}

#endif