#ifndef _____UIFRAMEPage_H
#define _____UIFRAMEPage_H

#include "UIPngButton.h"

namespace YouLe
{
	class UIFramePage : public UIWidget, public UIProcess
	{
	public:
		// 构造函数
		UIFramePage();
		// 析构函数
		virtual ~UIFramePage();

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	};
}

#endif