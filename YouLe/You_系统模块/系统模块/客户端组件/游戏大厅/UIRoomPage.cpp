#include "StdAfx.h"
#include "uiroompage.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// 游戏房间构造
	//////////////////////////////////////////////////////////////////////////
	UIRoomItem::UIRoomItem(void)
	{
		//创建字体
		m_InfoFont.CreateFont(12,8,0,0,100,0,0,0,134,3,2,1,2,TEXT("黑体"));
		m_RuleFont.CreateFont(11,8,0,0,100,0,0,0,134,3,2,1,2,TEXT("黑体"));
	}

	UIRoomItem::~UIRoomItem(void)
	{

	}

	// 创建控件
	BOOL	UIRoomItem::Create(INT nID, INT nDestX, INT nDestY,
								CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		//加载资源
		tagPlatViewImageNew & PlazaViewImage = CGlobalUnits::GetSingleton()->m_PlazaViewImage;
		HINSTANCE hInstance = CGlobalUnits::GetSingleton()->m_PlatformResourceModule->GetResInstance();

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
			tagRoomConfig Config = m_pListServer->m_GameServer.RoomConfig;

			pDC->SelectObject(m_RuleFont);
			pDC->SetTextColor(RGB(255,255,255));
			
			WORD wRoomRule[5]={ROOM_JUNIOR,ROOM_MIDDLE,ROOM_HIGH,ROOM_BAIREN,ROOM_NOCHEAT};
			LPCTSTR pszRoomRule[5]={TEXT("初级"),TEXT("中级"),TEXT("高级"),TEXT("百人房"),TEXT("防作弊")};
			for(int i = 0; i < CountArray(wRoomRule); i++)
			{
				if(Config.wServerRule == wRoomRule[i])
				{
					pDC->TextOut(cPt.x + 7, cPt.y + 10, pszRoomRule[i]);
					break;
				}
			}
			pDC->SelectObject(m_InfoFont);
			pDC->TextOut(cPt.x + 70, cPt.y + 10, m_pListServer->m_GameServer.szServerName);

			TCHAR szTemp[128];
			if(Config.BaseScore > 0)
			{
				sprintf(szTemp,"%I64d",Config.BaseScore);
				pDC->TextOut(cPt.x + 60, cPt.y + 39, szTemp);
			}
			if(Config.HighestScore > 0)
			{
				sprintf(szTemp,"%I64d",Config.HighestScore);
				pDC->TextOut(cPt.x + 60, cPt.y + 61,szTemp);
			}
			if(Config.LowestScore > 0)
			{
				sprintf(szTemp,"%I64d",Config.LowestScore);
				pDC->TextOut(cPt.x + 60, cPt.y + 85, szTemp);
			}
		}
		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UIRoomItem::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
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
		CGlobalUnits::GetSingleton()->m_GameRoomManager.EnterRoom(m_pListServer);
		UIRoomPage* pPage = (UIRoomPage*)GetParent();
		if(pPage)
			pPage->SetEnterRoom(true);
		return true;
	}


	//////////////////////////////////////////////////////////////////////////
	// 游戏房间视图构造
	//////////////////////////////////////////////////////////////////////////
	UIRoomPage::UIRoomPage(void)
	{
		m_bEnterRoom = false;
		//创建字体
		m_DrawFont.CreateFont(18,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("黑体"));
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
		tagPlatViewImageNew & PlazaViewImage = CGlobalUnits::GetSingleton()->m_PlazaViewImage;
		HINSTANCE hInstance = CGlobalUnits::GetSingleton()->m_PlatformResourceModule->GetResInstance();
		
		// 标题图片
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// 房间列表
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pRoomItem[index] = new UIRoomItem();
				m_pRoomItem[index] ->Create(c * MAX_GIROW + r , GTP_OFFSETX + r * 180, GTP_OFFSETY + c * 145, pAttach, this, this);
				m_pRoomItem[index] ->VisibleWidget(false);
			}
		}

		VisibleWidget(FALSE);

		return TRUE;
	}

	// 绘制
	BOOL	UIRoomPage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		
		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x + GTP_OFFSETX, cPt.y);

		pDC->SelectObject(m_DrawFont);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->DrawText(m_szKindName,lstrlen(m_szKindName),CRect(cPt.x + GTP_OFFSETX,cPt.y+8,cPt.x+150+GTP_OFFSETX,cPt.y+30),DT_CENTER);

		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UIRoomPage::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		return TRUE;
	}

	// 显示房间列表
	bool	UIRoomPage::ShowRoomList(CListKind* ListKind)
	{
		CopyMemory(m_szKindName,ListKind->m_GameKind.szKindName,sizeof(m_szKindName));
		CListServer* pListServer = NULL;
		int	SeverIndex = 0;
		int RoomIndex = 0;
		while(true)
		{
			pListServer = CGlobalUnits::GetSingleton()->m_ServerListManager.EnumServerItem(SeverIndex++);
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
		if(RoomIndex == 0)
			return false;
		return true;
	}
}