#ifndef _____UIGameItem_H
#define _____UIGameItem_H

#include "UIPngButton.h"

namespace YouLe
{
	// 游戏列表项
	class UIGameItem : public UIWidget , public UIProcess
	{
	public:
		// 构造函数
		UIGameItem();
		// 析构函数
		virtual ~UIGameItem();
		// 设置有效
		virtual void		EnabledWidget(bool bEnabled);
		// 按键消息
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);
		// 创建控件
		virtual BOOL		Create(INT nID, INT nDestX, INT nDestY, 
			HINSTANCE hInstance, LPCTSTR lpszBackResouceName, LPCTSTR lpszBillResouceName, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		
		// 绘制控件
		virtual BOOL		Draw(CDC* pDC);
	public:
		// 设置背景图
		virtual bool		SetBackPng(LPCTSTR pszFileName);
		// 设置背景图
		virtual bool		SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
		// 设置广告图
		virtual bool		SetBillPng(LPCTSTR pszFileName);
		// 设置广告图
		virtual bool		SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName);
		// 进入房间
		virtual bool		OnShowRoomPage();

		CListKind*			GetListKind() { return m_pListKind; }

	public:
		// 左键按下
		virtual BOOL		OnLeftDown(const CPoint& cPt);

	protected:
		CPngImage			m_PngBack;
		CPngImage			m_PngBill;
		UIPngButton*		m_pRegular;
		UIPngButton*		m_pJoinBtn; 
		
	public:
		// 游戏信息
		CListKind*			m_pListKind;
	};

	// 游戏视图
	class UIGameView : public UIWidget,public UIProcess
	{
	public:
		// 构造函数
		UIGameView();
		// 析构函数
		virtual ~UIGameView();
		// 按键消息
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);
		// 创建游戏视图
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
	
	public:
		virtual	void		VisibleTrigger();
		// 功能函数
	public:
		// 设置所有GameItem是否可用
		void				EnabledAllGameItem(bool bEnabled);
		// 枚举GameItem
		bool				EnumGameItem();
		// 显示首页
		void				ShowFirstPage(int KindType = -1);
		// 响应上一页
		void				OnClickLastPage();
		// 响应下一页
		void				OnClickNextPage();
		// 设置当前显示页
		virtual void		SetPage(INT nPage);

		// 触发进入某游戏
		void				OnEnterGame(CListKind* pKind);
		
	public:
		// 游戏页
		UIGameItem*			m_pGameItem[MAX_GICOL*MAX_GIROW];
		// 枚举序列
		int					m_EnumIndex;
		// 类型标识
		int					m_KindType;
	};
}

#endif