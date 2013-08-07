#include "StdAfx.h"
#include "UITablepage.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ���ӹ���
	//////////////////////////////////////////////////////////////////////////
	UITableItem::UITableItem(void)
	{

	}

	UITableItem::~UITableItem(void)
	{

	}

	// �����ؼ�
	BOOL	UITableItem::Create(INT nID, INT nDestX, INT nDestY,
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
	BOOL	UITableItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		// drwo normal stat image
		m_PngBill.DrawImage(pDC, cPt.x, cPt.y);

		return TRUE;
	}

	// ��Ӧҳ�ؼ�
	BOOL	UITableItem::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// ���밴ť
				{
					::AfxMessageBox("׼��ȷ����Ϸ����");
					return TRUE;
				}
			}
		}
		return TRUE;
	}



	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ������ͼ����
	//////////////////////////////////////////////////////////////////////////
	UITablePage::UITablePage(void)
	{
	}

	UITablePage::~UITablePage(void)
	{
	}

	// �����ؼ�
	BOOL	UITablePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
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
				m_pTableItem[index] = new UITableItem();
				m_pTableItem[index] ->Create(c * MAX_GIROW + r , r * 180, 40+c * 145,pAttach, pProcess, this);
				//m_pTableItem[index] ->VisibleWidget(false);
			}
		}

		return TRUE;
	}

	// ����
	BOOL	UITablePage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UITablePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
			case IDB_GPRETURN:	// ���ذ�ť
				{
					g_UIPageManager.m_pTablePage->VisibleWidget(false);
					g_UIPageManager.m_pRoomPage->VisibleWidget(true);
					return TRUE;
				}
			}
		}
		return TRUE;
	}

}