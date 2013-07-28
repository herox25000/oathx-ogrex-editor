#include "Stdafx.h"
#include "UIWidget.h"

namespace YouLe
{
	// 构造函数
	UIWidget::UIWidget() 
		: m_nID(0), m_bVisible(TRUE), m_bEnabled(TRUE), m_pParent(NULL), m_pAttach(NULL), m_pProcess(NULL)
	{

	}

	// 析构函数
	UIWidget::~UIWidget()
	{
		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			delete it->second; it = m_WidgetReg.erase(it);
		}
	}

	// 创建控件
	BOOL		UIWidget::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		m_pAttach	= pAttach;
		m_nID		= nID;
		m_rect		= rect;
		m_pProcess	= pProcess;

		if (pParent)
			pParent->Add(this);

		return TRUE;
	}

	// 设置ID
	void		UIWidget::SetID(const INT nID)
	{
		m_nID = nID;
	}

	// 获取ID
	INT			UIWidget::GetID() const
	{
		return m_nID;
	}

	// 属性控件
	void		UIWidget::Invalidate(BOOL bErase)
	{
		ASSERT(m_pAttach != NULL); 
		m_pAttach->InvalidateRect(&m_rect, bErase);
	}

	BOOL		UIWidget::IsWidgetEnabled() const
	{
		return m_bEnabled;
	}

	BOOL		UIWidget::IsWidgetVisible() const
	{
		return m_bVisible;
	}

	void		UIWidget::EnabledWidget(bool bEnabled)
	{
		m_bEnabled = bEnabled;
		Invalidate(TRUE);
	}

	void		UIWidget::VisibleWidget(bool bVisible)
	{
		m_bVisible = bVisible;
		Invalidate(TRUE);
	}
	
	void		UIWidget::GetWidgetRect(LPRECT lpRect)
	{
		lpRect->left = m_rect.left; lpRect->top = m_rect.top; lpRect->right = m_rect.right; lpRect->bottom = m_rect.bottom;
	}

	void		UIWidget::GetClientRect(LPRECT lpRect)
	{
		lpRect->left =0; lpRect->top = 0; lpRect->right = m_rect.Width(); lpRect->bottom = m_rect.Height();
	}

	void		UIWidget::SetWidgetPos(INT nTop, INT x, INT y, INT w, INT h)
	{
		m_rect.SetRect(x, y, x + w, y + h);
	}

	BOOL		UIWidget::PtInRect(const CPoint& cPt)
	{
		return m_rect.PtInRect(cPt);
	}

	LRESULT		UIWidget::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(m_pAttach); return m_pAttach->SendMessage(Msg, wParam, lParam);
	}

	BOOL		UIWidget::Draw(CDC* pDC)
	{
		if (!m_bVisible)
			return FALSE;
		
		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while(it != m_WidgetReg.end())
		{
			it->second->Draw(pDC); it ++;
		}

// #ifndef _DEBUG
// 		pDC->FillRect(&m_rect, &CBrush(RGB(0, 255, 0)));
// #endif
		
		return TRUE;
	}

	BOOL		UIWidget::Add(UIWidget* pWidget)
	{
		UIWidgetRegister::iterator it = m_WidgetReg.find(pWidget->GetID());
		if (it != m_WidgetReg.end())
			return FALSE;

		// get widget rect
		CRect rectWidget;
		pWidget->GetWidgetRect(&rectWidget);

		// widget relative postion
		CPoint cRelatively = rectWidget.TopLeft();

		// if the widget have a parent
		UIWidget* pParent = pWidget->GetParent();
		if (pParent)
		{
			CRect rectParent;
			pParent->GetWidgetRect(&rectParent);

			// calc the widget relative position
			cRelatively = rectWidget.TopLeft() - rectParent.TopLeft();

			// remove the widget from parent
			pParent->Remove(pWidget->GetID(), FALSE);
		}

		// set new parent
		pWidget->SetParent(this);

		// adjust postion
		CPoint cPt = m_rect.TopLeft();
		pWidget->SetWidgetPos(0, cPt.x + cRelatively.x, cPt.y + cRelatively.y, 
			rectWidget.Width(), rectWidget.Height());

		// insert widget
		m_WidgetReg.insert(
			UIWidgetRegister::value_type(pWidget->GetID(), pWidget)
			);
		return TRUE;
	}

	// 查找窗口
	UIWidget*	UIWidget::Search(INT nID)
	{
		UIWidgetRegister::iterator it = m_WidgetReg.find(nID);
		if (it != m_WidgetReg.end() )
			return it->second;

		return NULL;
	}

	// 移除控件
	void		UIWidget::Remove(INT nID, BOOL bDestroy/* =TRUE */)
	{
		UIWidgetRegister::iterator it = m_WidgetReg.find(nID);
		if (it != m_WidgetReg.end() )
		{
			if (bDestroy)
			{
				delete it->second;
			}

			m_WidgetReg.erase(it);
		}
	}

	// 获取子控件数
	INT			UIWidget::GetWidgetCount() const
	{
		return (INT)(m_WidgetReg.size());
	}

	// 设置父亲
	void		UIWidget::SetParent(UIWidget* pParent)
	{
		m_pParent = pParent;
	}

	// 获取父亲
	UIWidget*	UIWidget::GetParent() const
	{
		return m_pParent;
	}

	// 鼠标移动
	BOOL		UIWidget::OnMouseMove(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			if (it->second->IsWidgetVisible() && it->second->IsWidgetEnabled())
			{
				if (it->second->OnMouseMove(cPt))
					return TRUE;
			}

			it ++;
		}

		return FALSE;
	}

	BOOL		UIWidget::OnLeftDown(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			if (it->second->IsWidgetVisible() && it->second->IsWidgetEnabled())
			{
				if (it->second->OnLeftDown(cPt))
					return TRUE;
			}

			it ++;
		}

		return FALSE;
	}

	BOOL		UIWidget::OnLeftUp(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			if (it->second->IsWidgetVisible() && it->second->IsWidgetEnabled())
			{
				if (it->second->OnLeftUp(cPt))
					return TRUE;
			}

			it ++;
		}

		return FALSE;
	}

	BOOL		UIWidget::OnRightDown(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			if (it->second->IsWidgetVisible() && it->second->IsWidgetEnabled())
			{
				if (it->second->OnRightDown(cPt))
					return TRUE;
			}

			it ++;
		}

		return FALSE;
	}

	BOOL		UIWidget::OnRightUp(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while( it != m_WidgetReg.end() )
		{
			if (it->second->IsWidgetVisible() && it->second->IsWidgetEnabled())
			{
				if (it->second->OnRightUp(cPt))
					return TRUE;
			}

			it ++;
		}

		return FALSE;
	}
}