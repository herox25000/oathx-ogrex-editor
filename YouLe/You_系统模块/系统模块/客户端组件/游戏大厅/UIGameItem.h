#ifndef _____UIGameItem_H
#define _____UIGameItem_H

#include "UIPngButton.h"

namespace YouLe
{
	// 游戏列表项
	class UIGameItem : public UIWidget
	{
	public:
		// 构造函数
		UIGameItem();
		// 析构函数
		virtual ~UIGameItem();
		
		// 创建控件
		virtual BOOL		Create(INT nID, INT nDestX, INT nDestY, 
			HINSTANCE hInstance, LPCTSTR lpszBackResouceName, LPCTSTR lpszBillResouceName, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		
		// 绘制控件
		virtual BOOL		Draw(CDC* pDC);
	public:
		// 设置背景图
		virtual void		SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
		// 设置广告图
		virtual void		SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName);
	protected:
		CPngImage			m_PngBack;
		CPngImage			m_PngBill;
	};

	// 游戏视图
	class UIGameView : public UIWidget
	{
	public:
		// 构造函数
		UIGameView();
		// 析构函数
		virtual ~UIGameView();
		
		// 创建游戏视图
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
	};
}

#endif