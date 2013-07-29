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
			delete (*it); it = m_WidgetReg.erase(it);
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
			(*it)->Draw(pDC); it ++;
		}

// #ifndef _DEBUG
// 		pDC->FillRect(&m_rect, &CBrush(RGB(0, 255, 0)));
// #endif
		
		return TRUE;
	}

	BOOL		UIWidget::Add(UIWidget* pWidget)
	{
		if (Search(pWidget->GetID()))
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
		
		// add the widget
		m_WidgetReg.push_back(pWidget);

		return TRUE;
	}

	// 查找窗口
	UIWidget*	UIWidget::Search(INT nID)
	{
		for (size_t i=0; i<m_WidgetReg.size(); i++)
		{
			if (m_WidgetReg[i]->GetID() == nID)
				return m_WidgetReg[i];
		}

		return NULL;
	}

	//鼠标查找
	UIWidget*	UIWidget::GetChildWidget(const CPoint& cPt)
	{
		// get end element
		const UIWidgetRegister::const_reverse_iterator end = m_WidgetReg.rend();

		// reverse find
		UIWidgetRegister::const_reverse_iterator child;
		for (child=m_WidgetReg.rbegin(); child!=end; child++)
		{
			if ((*child)->IsWidgetVisible())
			{
				UIWidget* pWidget = (*child)->GetChildWidget(cPt);
				if (pWidget == NULL)
				{
					if ((*child)->PtInRect(cPt))
						return (*child);
				}
				else
				{
					return pWidget;
				}
			}
		}
		
		return NULL;
	}

	// 移除控件
	void		UIWidget::Remove(INT nID, BOOL bDestroy/* =TRUE */)
	{
		UIWidgetRegister::iterator it = m_WidgetReg.begin();
		while (it != m_WidgetReg.end() )
		{
			if ((*it)->GetID() == nID)
			{
				if (bDestroy)
					delete (*it);

				m_WidgetReg.erase(it);
				break;
			}
			
			it ++;
		}
	}

	// 移除控件
	void		UIWidget::Remove(UIWidget* pWidget, BOOL bDestroy/* =TRUE */)
	{
		UIWidgetRegister::iterator it = std::find(m_WidgetReg.begin(), m_WidgetReg.end(), pWidget);
		if (it != m_WidgetReg.end() )
		{
			if (bDestroy)
				delete (*it);

			m_WidgetReg.erase(it);
		}
	}

	// 获取子控件数
	INT			UIWidget::GetWidgetCount() const
	{
		return (INT)(m_WidgetReg.size());
	}

	// 强制置顶
	BOOL		UIWidget::MoveToFront()
	{
		if (m_pParent == NULL)
			return FALSE;

		BOOL bTookAction = m_pParent->MoveToFront();

		if (m_pParent)
		{
			m_pParent->Remove(this, FALSE);

			// add this
			m_pParent->Add(this);
		}

		return bTookAction;
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

		if (m_pProcess)
			m_pProcess->OnMouseMove(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}
	
	// 左键按下
	BOOL		UIWidget::OnLeftDown(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		if (m_pProcess)
		{
			m_pProcess->OnLeftDown(this, cPt);
		}

		Invalidate(TRUE);

		return TRUE;
	}

	// 左键弹起
	BOOL		UIWidget::OnLeftUp(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		if (m_pProcess)
			m_pProcess->OnLeftUp(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}
	
	// 鼠标响应
	BOOL		UIWidget::OnClicked(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		if (m_pProcess)
			m_pProcess->OnClicked(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}

	// 鼠标离开
	BOOL		UIWidget::OnMouseLeave(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		if (m_pProcess)
			m_pProcess->OnMouseLeave(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}

	// 鼠标进入
	BOOL		UIWidget::OnMouseEnter(const CPoint& cPt)
	{
		if (!m_bEnabled || !m_bVisible)
			return FALSE;

		if (m_pProcess)
			m_pProcess->OnMouseEnter(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}
}