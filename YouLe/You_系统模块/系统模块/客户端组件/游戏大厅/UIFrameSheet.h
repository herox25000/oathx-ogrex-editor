#ifndef _____UIFrameSheet_H
#define _____UIFrameSheet_H

#include "UIGamePage.h"
#include "UIFramePage.h"

namespace YouLe
{
	// UI 根窗口
	class UIFrameSheet : public UIWidget
	{
	public:
		// 构造函数
		UIFrameSheet();
		// 析构函数
		virtual ~UIFrameSheet();

		// 创建窗口
		virtual BOOL			Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// 注入鼠标移动
		virtual BOOL			InjectMouseMove(const CPoint& cPt);
		// 注入鼠标按下
		virtual BOOL			InjectLeftDown(const CPoint& cPt);
		// 注入鼠标弹起
		virtual BOOL			InjectLeftUp(const CPoint& cPt);
	};
}

#endif