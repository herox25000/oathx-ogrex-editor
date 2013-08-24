#include "StdAfx.h"
#include ".\uiimagescrollbar.h"
namespace YouLe
{
	enum
	{
		BT_UP = 20,
		BT_DOWN
	};

	UIImageScrollBar::UIImageScrollBar(UINT theID, UIScrollListener* ScrollListener,
		Bar_Dir Direction/*= VERTICAL*/)
	{
		m_TheID = theID;
		m_ScrollListener = ScrollListener;
		m_Direction = Direction;

		m_InvisIfNoScroll = false;
		m_PressedOnThumb = false;
		m_Value = 0;
		m_MaxValue = 0;
		m_PageSize = 0;
		m_UpdateAcc = 0;
		m_ButtonAcc = 0;
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

	//	m_BGImage.LoadImage(hInstance , PlazaViewImage.pszBtFastJoin);
		
		m_ThumbImage.LoadImage(hInstance , PlazaViewImage.pszBtFastJoin);

		m_ThumbSize = m_ThumbImage.GetHeight();

		CRect rc;
		GetClientRect(&rc);

		m_btUp = new UIPngButton();
		m_btUp->Create(BT_UP,     rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);
		
		m_btDown = new UIPngButton();
		m_btDown->Create(BT_DOWN, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);

		m_btUp->GetClientRect(&rc);
		Size tempsize(rc.Width(),rc.Height());
		m_BtSize.Equals(tempsize);

		return TRUE;
	}

	BOOL	UIImageScrollBar::OnDraw(CDC* pDC)
	{
		CPoint cPt = m_rect.TopLeft();
		if (m_BGImage.IsNull())
		{
			CRect rcClientRect;
			GetClientRect(&rcClientRect);
			pDC->FillRect(&rcClientRect, &CBrush(RGB(0, 76, 149)));
		}
		else
		{
			m_BGImage.DrawImage(pDC,cPt.x,cPt.y);
		}

		int aThumbSize = GetThumbSize();
		int aThumbPosition = GetThumbPosition();

		m_ThumbImage.DrawImage(pDC,0,aThumbPosition);
		return TRUE;
	}

	BOOL	UIImageScrollBar::OnMouseDrag(const CPoint& cPt)
	{
		int x = cPt.x;
		int y = cPt.y;
		if (m_PressedOnThumb) 
		{
			SetThumbPosition(m_MouseDownThumbPos + y - m_MouseDownY);
		}

		m_LastMouseX = x;
		m_LastMouseY = y;
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
				if (++m_ButtonAcc >= 25)	
				{
					SetValue(m_Value-1);
					m_ButtonAcc = 24;	
				}
				return TRUE;
			}
		case BT_DOWN:
			{
				if (++m_ButtonAcc >= 25)	
				{
					SetValue(m_Value+1);
					m_ButtonAcc = 24;
				}
				return TRUE;
			}
		}
		return TRUE;
	}

	void UIImageScrollBar::SetInvisIfNoScroll(bool invisIfNoScroll)
	{
		m_InvisIfNoScroll = invisIfNoScroll;

		if (m_InvisIfNoScroll) 
		{
			VisibleWidget(false);
			m_btUp->VisibleWidget(false);
			m_btDown->VisibleWidget(false);
		}
	}

	int UIImageScrollBar::ThumbCompare(int x, int y) 
	{
		int aTrackPosition; 

		aTrackPosition = y;

		if (aTrackPosition < GetThumbPosition()) 
			return -1;

		if (aTrackPosition >= GetThumbPosition() + GetThumbSize()) 
			return 1;

		return 0;
	}

	void UIImageScrollBar::ClampValue() 
	{
		double anOldValue = m_Value;

		if (m_Value > m_MaxValue - m_PageSize)
			m_Value = m_MaxValue - m_PageSize;
		if (m_Value < 0.0)
			m_Value = 0.0;

		bool canScroll = m_PageSize < m_MaxValue;

		EnabledWidget(!canScroll);
		m_btDown->EnabledWidget(canScroll);
		m_btUp->EnabledWidget(canScroll);

		if (m_InvisIfNoScroll) 
		{
			VisibleWidget(canScroll);
			m_btDown->VisibleWidget(canScroll);
			m_btUp->VisibleWidget(canScroll);
		}
	

		if (m_Value != anOldValue) m_ScrollListener->ScrollPosition(m_TheID, m_Value);
	}		

	void UIImageScrollBar::SetThumbPosition(int thePosition) 
	{
		SetValue(((thePosition-m_BtSize.Width) * (m_MaxValue - m_PageSize)) / (GetTrackSize() - GetThumbSize()));				
	}

	void UIImageScrollBar::SetValue(double theNewValue) 
	{
		m_Value = theNewValue;		
		ClampValue();
		m_ScrollListener->ScrollPosition(m_TheID, m_Value);
		Invalidate(TRUE);
	}

	void UIImageScrollBar::SetMaxValue(double theNewMaxValue) 
	{
		m_MaxValue = theNewMaxValue;
		ClampValue();
		Invalidate(TRUE);
	}

	void UIImageScrollBar::SetPageSize(double theNewPageSize) 
	{
		m_PageSize = theNewPageSize;
		ClampValue();
		Invalidate(TRUE);
	}

	bool UIImageScrollBar::AtBottom() 
	{
		return m_MaxValue - m_PageSize - m_Value <= 1.0;
	}

	void UIImageScrollBar::GoToBottom() 
	{
		m_Value = m_MaxValue - m_PageSize;
		ClampValue();
		SetValue(m_Value);
	}

	int UIImageScrollBar::GetTrackSize() 
	{
		return m_rect.Height()-2*m_BtSize.Width;
	}

	int UIImageScrollBar::GetThumbSize() 
	{
		return m_ThumbSize;
	}

	int UIImageScrollBar::GetThumbPosition() 
	{
		if (m_PageSize > m_MaxValue) 
			return m_BtSize.Width;
		return (int) ((double) (((m_Value * (GetTrackSize() - GetThumbSize())) / (m_MaxValue - m_PageSize))) + 0.5) + m_BtSize.Width;
	}

}
