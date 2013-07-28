#ifndef _____UIFramePage_H
#define _____UIFramePage_H

#include "UISheet.h"

namespace YouLe
{
	class UIFramePage : public UISheet, public UIProcess
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