#include "stdafx.h"
#include "UIGameItem.h"
#include "GlobalUnits.h"

namespace YouLe
{
	// ���캯��
	UIGameItem::UIGameItem()
	{

	}

	// ��������
	UIGameItem::~UIGameItem()
	{

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

		// ����ҳ�水ť
		const TCHAR* chBtnImageResouceName[] = {
			TEXT("GAMEITEM_REGULAR"),
			TEXT("GAMEITEM_JOIN"),
		};


		UIPngButton* pRegular = new UIPngButton();
		pRegular->Create(0, 5, 106, m_pAttach, pProcess,
			hInstance, chBtnImageResouceName[0], 4, this);

		UIPngButton* pJoinBtn = new UIPngButton();
		pJoinBtn->Create(1, 60, 106, m_pAttach, pProcess,
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

	// ���ñ���
	void	UIGameItem::SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName)
	{
		m_PngBack.DestroyImage();
		m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBackResouceName);
	}
	
	// ���ù��
	void	UIGameItem::SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName)
	{
		m_PngBill.DestroyImage();
		m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBillResouceName);
	}

#define MAX_GICOL	3
#define MAX_GIROW	3
#define MAX_SPACE	10

	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ��ͼ����
	//////////////////////////////////////////////////////////////////////////
	UIGameView::UIGameView()
	{

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

		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				UIGameItem* pItem = new UIGameItem();
				pItem->Create(c * MAX_GIROW + r , r * 180, c * 145, hInstance, PlazaViewImage.pszGameBack, PlazaViewImage.pszGameItemBill, 
					pAttach, pProcess, this);
			//	pItem->EnabledWidget(FALSE);
			}
		}

		return TRUE;
	}
}