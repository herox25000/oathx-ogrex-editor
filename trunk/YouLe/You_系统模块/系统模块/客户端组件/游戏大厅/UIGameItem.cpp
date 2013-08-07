#include "stdafx.h"
#include "UIGameItem.h"

namespace YouLe
{

	//////////////////////////////////////////////////////////////////////////
	// 游戏构造
	//////////////////////////////////////////////////////////////////////////
	// 构造函数
	UIGameItem::UIGameItem()
	{
		m_pRegular = NULL;
		m_pJoinBtn = NULL;
	}

	// 析构函数
	UIGameItem::~UIGameItem()
	{

	}

	// 设置有效
	void	UIGameItem::EnabledWidget(bool bEnabled)
	{
		m_pJoinBtn->VisibleWidget(bEnabled);
		m_pRegular->VisibleWidget(bEnabled);
		__super::EnabledWidget(bEnabled);
	}

	// 按键消息
	BOOL	UIGameItem::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case 0: // 规则
			{
				char szWebPage[256];
				sprintf(szWebPage,_T("www.youle8.com//rule//%d"),m_GameKind->wKindID);
				ShellExecute(NULL,TEXT("OPEN"),szWebPage,NULL,NULL,SW_NORMAL);
				return TRUE;
			}
		case 1: // 进入游戏
			{	
				OnClickedEnterRoom();	
				return TRUE;
			}
		}
		return TRUE;
	}

	// 创建控件
	BOOL	UIGameItem::Create(INT nID, INT nDestX, INT nDestY, 
		HINSTANCE hInstance, LPCTSTR lpszBackResouceName, LPCTSTR lpszBillResouceName, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, 
			lpszBackResouceName);

		m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, 
			lpszBillResouceName);

		CRect rect;
		rect.SetRect(nDestX, nDestY,
			nDestX + m_PngBack.GetWidth(), nDestY + m_PngBack.GetHeight());
		
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		tagPlatViewImageNew & PlatViewImage = g_GlobalUnits.m_PlazaViewImage;

		// 创建页面按钮
		const TCHAR* chBtnImageResouceName[] = {
			PlatViewImage.pszGameItemRegular,
			PlatViewImage.pszGameItemJoin,
		};


		m_pRegular = new UIPngButton();
		m_pRegular->Create(0, 5, 106, m_pAttach, this,
			hInstance, chBtnImageResouceName[0], 4, this);

		m_pJoinBtn = new UIPngButton();
		m_pJoinBtn->Create(1, 60, 106, m_pAttach, this,
			hInstance, chBtnImageResouceName[1], 4, this);

		return TRUE;
	}

	//
	BOOL	UIGameItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();

		BOOL bEnabled = IsWidgetEnabled();
		if (!bEnabled)
		{
			// draw enable background
			m_PngBack.DrawImage(pDC, cPt.x, cPt.y);
		}
		else
		{
			// drwo normal stat image
			m_PngBill.DrawImage(pDC, cPt.x, cPt.y);
		}

		return UIWidget::Draw(pDC);
	}
	// 设置背景
	bool	UIGameItem::SetBackPng(LPCTSTR pszFileName)
	{
		m_PngBack.DestroyImage();
		return m_PngBack.LoadImage(pszFileName);
	}

	// 设置背景
	bool	UIGameItem::SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName)
	{
		m_PngBack.DestroyImage();
		return m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBackResouceName);
	}

	// 设置广告
	bool	UIGameItem::SetBillPng(LPCTSTR pszFileName)
	{
		m_PngBill.DestroyImage();
		return m_PngBill.LoadImage(pszFileName);
	}

	// 设置广告
	bool	UIGameItem::SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName)
	{
		m_PngBill.DestroyImage();
		return m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBillResouceName);
	}

	// 进入房间
	bool	UIGameItem::OnClickedEnterRoom()
	{
		g_UIPageManager.m_pGamePage->VisibleWidget(false);
		g_UIPageManager.m_pRoomPage->VisibleWidget(true);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// 游戏视图构造
	//////////////////////////////////////////////////////////////////////////
	UIGameView::UIGameView()
	{
		m_EnumIndex = 0;
	}
	
	// 析构函数
	UIGameView::~UIGameView()
	{

	}

	// 创建游戏视图
	BOOL	UIGameView::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pGameItem[index] = new UIGameItem();
				m_pGameItem[index] ->Create(c * MAX_GIROW + r , r * 180, c * 145, hInstance, PlazaViewImage.pszGameBack, PlazaViewImage.pszGameItemBill, 
					pAttach, pProcess, this);
				m_pGameItem[index] ->EnabledWidget(false);
			}
		}
		
		CRect rc;
		GetClientRect(&rc);
		// 绘制翻页按钮，上一页
		UIPngButton* pBtLast = new UIPngButton();
		pBtLast->Create(100, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);
		
		// 绘制翻页按钮，下一页
		UIPngButton* pBtNext = new UIPngButton();
		pBtNext->Create(101, rc.right/2 ,		rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLNext, 4, this);
		
		return TRUE;
	}

	// 按键消息
	BOOL	UIGameView::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case 100:	// 上一页
			{
				OnClickLastPage();
				return TRUE;
			}
		case 101:	// 下一页
			{
				OnClickNextPage();
				return FALSE;
			}
		}
		return TRUE;
	}

	// 设置所有GameItem是否可用
	void	UIGameView::EnabledAllGameItem(bool bEnabled)
	{
		for (int i = 0; i < MAX_GICOL*MAX_GIROW; i++)
		{
			if(m_pGameItem[i])
				m_pGameItem[i]->EnabledWidget(bEnabled);
		}
	}

	// 枚举GameItem
	bool	UIGameView::EnumGameItem()
	{
		EnabledAllGameItem(false);
		CListKind * pListKind = NULL;
		char		szFileName[MAX_PATH];
		for (int nIndex = m_EnumIndex; nIndex < (m_EnumIndex+MAX_GICOL*MAX_GIROW); nIndex++)
		{
			pListKind = g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex);
			if (pListKind == NULL) 
				return false;
			UIGameItem* pGameItem = m_pGameItem[nIndex%(MAX_GICOL*MAX_GIROW)];
			if(pGameItem)
			{
				//sprintf(szFileName,"%s\\GameItem\\%d.png", CString(g_GlobalUnits.GetWorkDirectory()),pListKind->GetItemInfo()->wKindID);
				//if( !pGameItem->SetBillPng(szFileName))
				//	continue;
				pGameItem->EnabledWidget(true);
				pGameItem->m_GameKind = pListKind->GetItemInfo();
			}
		}
		return true;
	}

	// 显示首页
	void	UIGameView::ShowFirstPage()
	{
		m_EnumIndex = 0;
		EnumGameItem();
	}

	// 响应上一页
	void	UIGameView::OnClickLastPage()
	{
		m_EnumIndex -= MAX_GICOL*MAX_GIROW;
		if(m_EnumIndex < 0)
		{
			m_EnumIndex = 0;
			return;
		}
		EnumGameItem();
	}

	// 响应下一页
	void	UIGameView::OnClickNextPage()
	{
		m_EnumIndex += MAX_GICOL*MAX_GIROW;
		// 检查后面是否还有
		CListKind * pListKind = NULL;
		pListKind = g_GlobalUnits.m_ServerListManager.EnumKindItem(m_EnumIndex);
		if (pListKind == NULL) 
		{
			m_EnumIndex -= MAX_GICOL*MAX_GIROW;
			return ;
		}
		EnumGameItem();
	}

}