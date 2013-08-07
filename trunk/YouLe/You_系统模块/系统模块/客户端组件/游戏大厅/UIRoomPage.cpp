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
		// drwo normal stat image
		m_PngBill.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UIRoomItem::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// ���밴ť
				{
					g_UIPageManager.m_pRoomPage->VisibleWidget(false);
					g_UIPageManager.m_pTablePage->VisibleWidget(true);
					return TRUE;
				}
			}
		}
		return TRUE;
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

		// �������ذ�ť
		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDB_GPRETURN, rect.right - 320, 5, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		// �����б�
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pRoomItem[index] = new UIRoomItem();
				m_pRoomItem[index] ->Create(c * MAX_GIROW + r , r * 180, 40+c * 145,pAttach, pProcess, this);
				//m_pRoomItem[index] ->VisibleWidget(false);
			}
		}

		return TRUE;
	}

	// ����
	BOOL	UIRoomPage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		
		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UIRoomPage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
				case IDB_GPRETURN:	// ���ذ�ť
					{
						g_UIPageManager.m_pGamePage->VisibleWidget(true);
						g_UIPageManager.m_pRoomPage->VisibleWidget(false);
						return TRUE;
					}
			}
		}
		return TRUE;
	}
}