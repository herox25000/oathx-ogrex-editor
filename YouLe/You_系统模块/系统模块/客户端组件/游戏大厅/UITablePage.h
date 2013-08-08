#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子构造
	//////////////////////////////////////////////////////////////////////////
	class UITableItem : public UIWidget, public UIProcess
	{
	public:
		UITableItem(void);

		virtual ~UITableItem(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY,
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// 绘制
		virtual BOOL		Draw(CDC* pDC);
	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_PngBill;
		UIPngButton*		m_pJoinBtn; 
	public:
		TableInfo*			m_pTableInfo;
	};


	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子视图构造
	//////////////////////////////////////////////////////////////////////////
	class UITablePage : public UIWidget, public UIProcess
	{
	public:
		UITablePage(void);

		virtual ~UITablePage(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// 绘制
		virtual BOOL		Draw(CDC* pDC);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// 响应上一页
		void				OnClickLastPage();
		// 响应下一页
		void				OnClickNextPage();
		// 枚举GameItem
		bool				EnumTableItem();
		// 显示首页
		void				ShowFirstPage();
		//
		void				SetListServer(CListServer* ListServer){m_pListServer = ListServer;}
	public:
		// 
		UITableItem*		m_pTableItem[MAX_GICOL*MAX_GIROW];
		// 枚举序列
		int					m_EnumIndex;
		// 返回按钮
		UIPngButton*		m_pBtBack;
		// 标题
		CPngImage			m_TilteImage;
		// 
		CListServer*		m_pListServer;
	};
}