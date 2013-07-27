#include "stdafx.h"
#include "UIGameItem.h"

namespace YouLe
{
	// 构造函数
	UIGameItem::UIGameItem()
	{

	}

	// 析构函数
	UIGameItem::~UIGameItem()
	{

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
		
		return UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
	}

	//
	BOOL	UIGameItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		BOOL bEnabled = IsWidgetEnabled();
		if (!bEnabled)
		{
			// draw enable background
			m_PngBack.DrawImage(pDC, 0, 0);
		}
		else
		{
			// drwo normal stat image
			m_PngBill.DrawImage(pDC, 0, 0);
		}

		return UIWidget::Draw(pDC);
	}

	// 设置背景
	void	UIGameItem::SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName)
	{
		m_PngBack.DestroyImage();
		m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBackResouceName);
	}
	
	// 设置广告
	void	UIGameItem::SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName)
	{
		m_PngBill.DestroyImage();
		m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBillResouceName);
	}

#define MAX_GICOL	3
#define MAX_GIROW	3

	//////////////////////////////////////////////////////////////////////////
	// 游戏视图构造
	//////////////////////////////////////////////////////////////////////////
	UIGameView::UIGameView()
	{

	}
	
	// 析构函数
	UIGameView::~UIGameView()
	{

	}

	// 创建游戏视图
	BOOL	UIGameView::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				UIGameItem* pItem = new UIGameItem();
				pItem->Create(c * MAX_GIROW + r , rect.left + r * 176, rect.top + c * 140, NULL, TEXT("GAMEITEM_BACK"), TEXT("GAMEITEM_BILL"), 
					pAttach, pProcess, this);
			}
		}

		return UIWidget::Create(nID, rect, pAttach, pProcess, pParent);	
	}
}