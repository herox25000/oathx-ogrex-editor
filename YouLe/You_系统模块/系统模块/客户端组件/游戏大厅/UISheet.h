#ifndef _____UISheet_H
#define _____UISheet_H

#include "UIWidget.h"

namespace YouLe
{
	// 基本UI管理
	class UISheet : public UIWidget
	{
	public:
		// 构造函数
		UISheet();
		// 析构函数
		virtual ~UISheet();

	public:
		// 鼠标移动
		virtual BOOL		InjectMouseMove(const CPoint& cPt);
		// 鼠标按下
		virtual BOOL		InjectLeftDown(const CPoint& cPt);
		// 鼠标弹起
		virtual BOOL		InjectLeftUp(const CPoint& cPt);
		// 键盘按下
		virtual BOOL		InjectKeyDwon(UINT nChar, UINT nRepCnt, UINT nFlags);
		// 键盘弹起
		virtual BOOL		InjectKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		// 字符输入
		virtual BOOL		InjectChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	protected:
		// 当前焦点
		UIWidget*			m_pFocus;
		// 当前输入
		UIWidget*			m_pInput;
		// 是否按下
		BOOL				m_bPress;
	};
}

#endif