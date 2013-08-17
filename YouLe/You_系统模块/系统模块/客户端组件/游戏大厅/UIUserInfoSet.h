#pragma once

#include "UIPngButton.h"

namespace YouLe
{
	class UIUserInfoSet : public UIWidget, public UIProcess
	{
	public:
		UIUserInfoSet(void);
		virtual ~UIUserInfoSet(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		// 按下消息
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		// 设置触发显示
		virtual void		VisibleTrigger();

	public:
		void				ShowPage(int nPageID);

	protected:
		CPngImage			m_ImageBack;

		int					m_nCurShowPageID;

	};

};
