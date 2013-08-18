#pragma once

#include "UIPngButton.h"
#include "DlgLogon.h"

namespace YouLe
{
	class UIFrameSet : public UIWidget, public UIProcess
	{
	public:
		UIFrameSet(void);
		virtual ~UIFrameSet(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// 左键按下
		virtual BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_ImageBack;
	};
};
