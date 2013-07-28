#ifndef _____UIFRAMECLOSE_H
#define _____UIFRAMECLOSE_H

#include "UIPngButton.h"

namespace YouLe
{
	class UIFrameClose : public UIWidget, public UIProcess
	{
	public:
		// 构造函数
		UIFrameClose();
		// 析构函数
		virtual ~UIFrameClose();

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
				UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		

	protected:
		CPngImage			m_PngBack;

	};
};
#endif