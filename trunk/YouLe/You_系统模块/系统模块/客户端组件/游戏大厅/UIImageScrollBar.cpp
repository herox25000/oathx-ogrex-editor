#include "StdAfx.h"
#include ".\uiimagescrollbar.h"
namespace YouLe
{
	enum
	{
		BT_UP = 20,
		BT_DOWN
	};

	UIImageScrollBar::UIImageScrollBar(UINT theID, UIScrollListener* ScrollListener,Bar_Dir Direction)
	{
		m_TheID = theID;
		m_ScrollListener = ScrollListener;
		m_Direction = Direction;
	}

	UIImageScrollBar::~UIImageScrollBar(void)
	{

	}


	// 窗口控件
	BOOL	UIImageScrollBar::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);
	
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_BGImage.LoadImage(hInstance , PlazaViewImage.pszBtFastJoin);
		
		m_ThumbImage.LoadImage(hInstance , PlazaViewImage.pszBtFastJoin);

		CRect rc;
		GetClientRect(&rc);

		UIPngButton* btUp = new UIPngButton();
		btUp->Create(BT_UP,     rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);
		
		UIPngButton* btDown = new UIPngButton();
		btDown->Create(BT_DOWN, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);

		return TRUE;
	}

	BOOL	UIImageScrollBar::OnDraw(CDC* pDC)
	{
		return TRUE;
	}

	BOOL	UIImageScrollBar::OnMouseDrag(const CPoint& cPt)
	{
		if(m_PressedOnThumb)
		{

		}
		return TRUE;
	}

	BOOL	UIImageScrollBar::OnLeftDown(const CPoint& cPt)
	{
		m_PressedOnThumb = true;
		return TRUE;
	}

	BOOL	UIImageScrollBar::OnLeftUp(const CPoint& cPt)
	{
		m_PressedOnThumb = false;
		return TRUE;
	}

	// 按键消息
	BOOL	UIImageScrollBar::OnLeftDown(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget == NULL)
			return FALSE;
		switch(pWidget->GetID())
		{
		case BT_UP:
			{
				return TRUE;
			}
		case BT_DOWN:
			{
				return TRUE;
			}
		}
		return TRUE;
	}


}
