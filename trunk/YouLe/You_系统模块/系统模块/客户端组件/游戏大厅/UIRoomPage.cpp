#include "StdAfx.h"
#include "uiroompage.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// 游戏房间构造
	//////////////////////////////////////////////////////////////////////////
	UIRoomItem::UIRoomItem(void)
	{

	}

	UIRoomItem::~UIRoomItem(void)
	{

	}

	// 创建控件
	BOOL	UIRoomItem::Create(INT nID, INT nDestX, INT nDestY,
								CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, 
			PlazaViewImage.pszGameRoomBill);

		CRect rect;
		rect.SetRect(nDestX, nDestY,
			nDestX + m_PngBill.GetWidth(), nDestY + m_PngBill.GetHeight());

		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		m_pJoinBtn = new UIPngButton();
		m_pJoinBtn->Create(100, 7, 106, m_pAttach, this,
			hInstance, PlazaViewImage.pszGameRoomJoin, 4, this);

		return TRUE;
	}

	// 绘制控件
	BOOL	UIRoomItem::Draw(CDC* pDC)
	{
		
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_PngBill.DrawImage(pDC, cPt.x, cPt.y);

		if(m_pListServer)
		{
			TCHAR	szTempStr[32];
			CopyMemory(szTempStr,m_pListServer->m_GameServer.szServerName,sizeof(szTempStr));
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x,cPt.y+5,cPt.x+100,cPt.y+30),DT_CENTER);
			sprintf(szTempStr,_T("人数：%d"),m_pListServer->m_GameServer.dwOnLineCount);		
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+30,cPt.y+30,cPt.x+100,cPt.y+30),DT_LEFT);
		}
		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UIRoomItem::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// 加入按钮
				{
					OnClickedEnterRoom();
					return TRUE;
				}
			}
		}
		return TRUE;
	}

	//
	bool	UIRoomItem::OnClickedEnterRoom()
	{
		g_GlobalUnits.m_GameRoomManager.EnterRoom(m_pListServer);
		return true;
	}


	//////////////////////////////////////////////////////////////////////////
	// 游戏房间视图构造
	//////////////////////////////////////////////////////////////////////////
	UIRoomPage::UIRoomPage(void)
	{
	}

	UIRoomPage::~UIRoomPage(void)
	{
	}

	// 创建控件
	BOOL	UIRoomPage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		
		// 标题图片
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// 创建返回按钮
		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDB_GPRETURN, rect.right - 320, 5, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		// 房间列表
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pRoomItem[index] = new UIRoomItem();
				m_pRoomItem[index] ->Create(c * MAX_GIROW + r , r * 180, 40+c * 145,pAttach, pProcess, this);
				m_pRoomItem[index] ->VisibleWidget(false);
			}
		}

		return TRUE;
	}

	// 绘制
	BOOL	UIRoomPage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		
		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x, cPt.y);
		
		pDC->DrawText(szKindName,lstrlen(szKindName),CRect(cPt.x,cPt.y+10,cPt.x+180,cPt.y+40),DT_CENTER);

		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UIRoomPage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
				case IDB_GPRETURN:	// 返回按钮
					{
						g_UIPageManager.m_pGamePage->VisibleWidget(true);
						g_UIPageManager.m_pRoomPage->VisibleWidget(false);
						return TRUE;
					}
			}
		}
		return TRUE;
	}

	// 显示房间列表
	void	UIRoomPage::ShowRoomList(CListKind* ListKind)
	{
		CopyMemory(szKindName,ListKind->m_GameKind.szKindName,sizeof(szKindName));
		CListServer* pListServer = NULL;
		int	SeverIndex = 0;
		int RoomIndex = 0;
		while(true)
		{
			pListServer = g_GlobalUnits.m_ServerListManager.EnumServerItem(SeverIndex++);
			if(pListServer == NULL)
				break;
			if(pListServer->m_GameServer.wKindID == ListKind->GetItemInfo()->wKindID )
			{
				m_pRoomItem[RoomIndex]->VisibleWidget(true);
				m_pRoomItem[RoomIndex]->m_pListServer = pListServer;
				if( ++RoomIndex >= MAX_GICOL*MAX_GIROW)
					break;	
			}
		}
	}
}