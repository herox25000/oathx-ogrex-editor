#include "stdafx.h"
#include "UIGameItem.h"

namespace YouLe
{

	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ����
	//////////////////////////////////////////////////////////////////////////
	// ���캯��
	UIGameItem::UIGameItem()
	{
		m_pRegular = NULL;
		m_pJoinBtn = NULL;
	}

	// ��������
	UIGameItem::~UIGameItem()
	{

	}

	// ������Ч
	void	UIGameItem::EnabledWidget(bool bEnabled)
	{
		m_pJoinBtn->VisibleWidget(bEnabled);
		m_pRegular->VisibleWidget(bEnabled);
		__super::EnabledWidget(bEnabled);
	}

	// ������Ϣ
	BOOL	UIGameItem::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case 0: // ����
			{
				if(m_pListKind)
				{
					char szWebPage[256];
					sprintf(szWebPage,_T("www.youle8.com//rule//%d"),m_pListKind->m_GameKind.wKindID);
					ShellExecute(NULL,TEXT("OPEN"),szWebPage,NULL,NULL,SW_NORMAL);
				}
				return TRUE;
			}
		case 1: // ������Ϸ
			{	
				if(m_pListKind)
				{
					OnShowRoomPage();	
				}
				return TRUE;
			}
		}
		return TRUE;
	}

	// �����ؼ�
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

		// ����ҳ�水ť
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

#ifdef _DEBUG
			pDC->SelectObject(g_UIPageManager.m_Font.m_StatusFont);
			pDC->SetTextColor(RGB(255,255,255));
			if(m_pListKind)
				pDC->DrawText(m_pListKind->m_GameKind.szKindName,lstrlen(m_pListKind->m_GameKind.szKindName),
				CRect(cPt.x,cPt.y+10,cPt.x+180,cPt.y+40),DT_CENTER);
#endif
		}
		return UIWidget::Draw(pDC);
	}
	// ���ñ���
	bool	UIGameItem::SetBackPng(LPCTSTR pszFileName)
	{
		m_PngBack.DestroyImage();
		return m_PngBack.LoadImage(pszFileName);
	}

	// ���ñ���
	bool	UIGameItem::SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName)
	{
		m_PngBack.DestroyImage();
		return m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBackResouceName);
	}

	// ���ù��
	bool	UIGameItem::SetBillPng(LPCTSTR pszFileName)
	{
		m_PngBill.DestroyImage();
		return m_PngBill.LoadImage(pszFileName);
	}

	// ���ù��
	bool	UIGameItem::SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName)
	{
		m_PngBill.DestroyImage();
		return m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBillResouceName);
	}

	// ���뷿��
	bool	UIGameItem::OnShowRoomPage()
	{
		UIGameView* pView = (UIGameView*)GetParent();
		if (pView)
		{
			pView->OnEnterGame(m_pListKind);
		}
		return true;
	}

	BOOL	UIGameItem::OnLeftDown(const CPoint& cPt)
	{
		if (UIWidget::OnLeftDown(cPt))
		{
			OnShowRoomPage();
			return TRUE;
		}
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ��ͼ����
	//////////////////////////////////////////////////////////////////////////
	static const INT idList[] = {
		1, 2, 3, 4
	};

	UIGameView::UIGameView()
	{
		m_EnumIndex = 0;
	}
	
	// ��������
	UIGameView::~UIGameView()
	{

	}

	// ������Ϸ��ͼ
	BOOL	UIGameView::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// ����ҳ�水ť
		const TCHAR* chBtnImageResouceName[] = {
				PlazaViewImage.pszGameTabGame,
				PlazaViewImage.pszGameTabCard,
				PlazaViewImage.pszGameTabMahj,
				PlazaViewImage.pszGameTabLeis
		};

		for (int i=0; i<4; i++)
		{
			UIPngButton* pPngButton = new UIPngButton();
			pPngButton->Create(idList[i], i * 96, 0, m_pAttach, this,
				hInstance, chBtnImageResouceName[i], 3, this);
		}

		SetPage(idList[0]);

		// ��ȡС��Ϸ���ݣ�����item
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c * MAX_GIROW + r;
				m_pGameItem[index] = new UIGameItem();
				m_pGameItem[index] ->Create(c * MAX_GIROW + r + 5 , r * 180, c * 145 + 45, hInstance, PlazaViewImage.pszGameBack, PlazaViewImage.pszGameItemBill, 
					pAttach, this, this);
				m_pGameItem[index]->EnabledWidget(false);
			}
		}
		
		CRect rc;
		GetClientRect(&rc);
		// ���Ʒ�ҳ��ť����һҳ
		UIPngButton* pBtLast = new UIPngButton();
		pBtLast->Create(100, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);
		
		// ���Ʒ�ҳ��ť����һҳ
		UIPngButton* pBtNext = new UIPngButton();
		pBtNext->Create(101, rc.right/2 ,		rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLNext, 4, this);
		
		VisibleWidget(FALSE);

		return TRUE;
	}

	// ����ҳ��
	void	UIGameView::SetPage(INT nID)
	{
		for (int i=0; i<4; i++)
		{
			UIWidget* pWidget = Search(idList[i]);
			if (pWidget)
				pWidget->EnabledWidget(idList[i] == nID ? FALSE : TRUE);
		}
	}

	// ������Ϣ
	BOOL	UIGameView::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case 100:	// ��һҳ
			{
				OnClickLastPage();
				return TRUE;
			}
		case 101:	// ��һҳ
			{
				OnClickNextPage();
				return TRUE;
			}
		case 1:
			{
				ShowFirstPage();
				SetPage(idList[0]);
				return TRUE;
			}
		case 2:
			{
				ShowFirstPage(idList[1]);
				SetPage(idList[1]);
				return TRUE;
			}
		case 3:
			{
				ShowFirstPage(idList[2]);
				SetPage(idList[2]);
				return TRUE;
			}
		case 4:
			{
				ShowFirstPage(idList[3]);
				SetPage(idList[3]);
				return TRUE;
			}
		}
		return TRUE;
	}

	// ��������GameItem�Ƿ����
	void	UIGameView::EnabledAllGameItem(bool bEnabled)
	{
		for (int i = 0; i < MAX_GICOL*MAX_GIROW; i++)
		{
			if(m_pGameItem[i])
				m_pGameItem[i]->EnabledWidget(bEnabled);
		}
	}

	// ö��GameItem
	bool	UIGameView::EnumGameItem()
	{
		EnabledAllGameItem(false);
		CListKind * pListKind = NULL;
		char		szFileName[MAX_PATH];
		int			GameIndex = 0;
		for (int nIndex = m_EnumIndex; nIndex < (m_EnumIndex+MAX_GICOL*MAX_GIROW); nIndex++)
		{
			pListKind = g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex);
			if (pListKind == NULL) 
				return false;
			if(pListKind->m_GameKind.wTypeID != m_KindType && m_KindType != -1)
				continue;
			UIGameItem* pGameItem = m_pGameItem[GameIndex];
			if(pGameItem)
			{
				CString strName(pListKind->GetItemInfo()->szProcessName);
				strName.TrimRight(".exe");
				sprintf(szFileName,"%s\\GameLobby\\GameKind\\%s\\Bill.png", 
					CString(g_GlobalUnits.GetWorkDirectory()),strName);
				if( !pGameItem->SetBillPng(szFileName))
					continue;
				pGameItem->EnabledWidget(true);
				pGameItem->m_pListKind = pListKind;
			}
			GameIndex++;
		}
		return true;
	}

	// ��ʾ��ҳ
	void	UIGameView::ShowFirstPage(int KindType /*= -1*/)
	{
		m_EnumIndex = 0;
		m_KindType = KindType;
		EnumGameItem();
	}

	// ��Ӧ��һҳ
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

	// ��Ӧ��һҳ
	void	UIGameView::OnClickNextPage()
	{
		m_EnumIndex += MAX_GICOL*MAX_GIROW;
		// �������Ƿ���
		CListKind * pListKind = NULL;
		pListKind = g_GlobalUnits.m_ServerListManager.EnumKindItem(m_EnumIndex);
		if (pListKind == NULL) 
		{
			m_EnumIndex -= MAX_GICOL*MAX_GIROW;
			return ;
		}
		EnumGameItem();
	}

	void	UIGameView::OnEnterGame(CListKind* pKind)
	{
		// �򸸴���
		UIGamePage* pPage = (UIGamePage*)GetParent();
		if (pPage)
		{
			pPage->ShowRoomView(pKind);
		}
	}

	void	UIGameView::VisibleTrigger()
	{
		SetPage(idList[0]);
		ShowFirstPage();
	}

}