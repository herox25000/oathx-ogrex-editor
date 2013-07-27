#ifndef _____UITab_H
#define _____UITab_H

#include "UIPngButton.h"

namespace YouLe
{
	// Tab 控件
	class UITab : public UIWidget
	{
	public:
		// 构造函数
		UITab();
		// 析构函数
		virtual ~UITab();

		// 创建控件
		virtual BOOL	Create(INT nID, const RECT& rect, CWnd* pAttach, UIWidget* pParent);
		
		// 设置当前页
		virtual void	SetCurPage(INT nPage);
		// 获取当前页
		virtual INT		GetCurPage() const;
	public:
		virtual BOOL	OnMouseMove(const CPoint& cPt);
	protected:
		INT				m_nCurPage;
	};
}

#endif