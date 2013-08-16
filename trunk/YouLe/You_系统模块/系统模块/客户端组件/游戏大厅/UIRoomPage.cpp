#include "StdAfx.h"
#include "uiroompage.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ���乹��
	//////////////////////////////////////////////////////////////////////////
	UIRoomItem::UIRoomItem(void)
	{

	}

	UIRoomItem::~UIRoomItem(void)
	{

	}

	// �����ؼ�
	BOOL	UIRoomItem::Create(INT nID, INT nDestX, INT nDestY,
								CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		//������Դ
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

	// ���ƿؼ�
	BOOL	UIRoomItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_PngBill.DrawImage(pDC, cPt.x, cPt.y);

		if(m_pListServer)
		{
			TCHAR	szTempStr[32];
			pDC->SelectObject(g_UIPageManager.m_Font.m_StatusFont);
			pDC->SetTextColor(RGB(255,255,255));		
			CopyMemory(szTempStr,m_pListServer->m_GameServer.szServerName,sizeof(szTempStr));
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+10,cPt.y+10,cPt.x+120,cPt.y+30),DT_CENTER);
			pDC->SelectObject(g_UIPageManager.m_Font.m_InfoFont);
			pDC->SetTextColor(RGB(255,255,128));
			sprintf(szTempStr,_T("������%d"),m_pListServer->m_GameServer.dwOnLineCount);		
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+35,cPt.y+80,cPt.x+135,cPt.y+100),DT_LEFT);
		}
		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UIRoomItem::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// ���밴ť
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
	// ��Ϸ������ͼ����
	//////////////////////////////////////////////////////////////////////////
	UIRoomPage::UIRoomPage(void)
	{
	}

	UIRoomPage::~UIRoomPage(void)
	{
	}

	// �����ؼ�
	BOOL	UIRoomPage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//������Դ
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		
		// ����ͼƬ
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// �����б�
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pRoomItem[index] = new UIRoomItem();
				m_pRoomItem[index] ->Create(c * MAX_GIROW + r , r * 180, 40+c * 145, pAttach, this, this);
				m_pRoomItem[index] ->VisibleWidget(false);
			}
		}

		VisibleWidget(FALSE);

		return TRUE;
	}

	// ����
	BOOL	UIRoomPage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		
		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x, cPt.y);

		pDC->SelectObject(g_UIPageManager.m_Font.m_TitleFont);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->DrawText(szKindName,lstrlen(szKindName),CRect(cPt.x,cPt.y+8,cPt.x+150,cPt.y+30),DT_CENTER);

		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UIRoomPage::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			UIRoomItem* pItem = (UIRoomItem*)pWidget;
			if (pItem)
			{

			}
		}
		return TRUE;
	}

	// ��ʾ�����б�
	bool	UIRoomPage::ShowRoomList(CListKind* ListKind)
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
		if(RoomIndex == 0)
			return false;
		return true;
	}
}