#include "stdafx.h"
#include "UIPngButton.h"

namespace YouLe
{
	// 析构函数
	UIPngButton::UIPngButton()
		: m_nState(PNG_BTNNORMAL), m_nSlice(0), m_pImage(NULL), m_bPress(FALSE), m_nCount(4)
	{

	}

	// 构造函数
	UIPngButton::~UIPngButton()
	{
		if (m_pImage != NULL)
		{
			delete m_pImage;
			m_pImage = NULL;
		}
	}

	// 创建控件
	BOOL	UIPngButton::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName, INT nStatCount, UIWidget* pParent)
	{
		// button image object
		m_pImage = new CPngImage();
		ASSERT(m_pImage != NULL);

		// load image from resouce instance
		BOOL bResult = m_pImage->LoadImage(hInstance,
			lpResourceName);
		ASSERT(bResult);
		
		m_nCount = nStatCount;

		// calc image slice width
		m_nSlice = m_pImage->GetWidth() / nStatCount;
		
		// calc button client rect
		CRect area(rect.left, rect.top, 
			rect.left + m_nSlice, rect.top + m_pImage->GetHeight());
	
		return UIWidget::Create(nID, area, pAttach, 
			pProcess, pParent);
	}

	// 创建控件
	BOOL	UIPngButton::Create(INT nID, INT x, INT y, CWnd* pAttach, 
		UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName, INT nStatCount, UIWidget* pParent)
	{
		return Create(nID, CRect(x, y, 0, 0), pAttach, pProcess, hInstance, lpResourceName, nStatCount, pParent);
	}

	// 重写绘制
	BOOL	UIPngButton::Draw(CDC* pDC)
	{
		if (!m_bVisible || m_pImage == NULL)
			return FALSE;

		// draw button
		m_pImage->DrawImage(pDC, m_rect.left, m_rect.top, 
			m_nSlice, m_pImage->GetHeight(), m_nSlice * m_nState, 0);

		return UIWidget::Draw(pDC);
	}

	// 控制窗口无效
	void	UIPngButton::EnabledWidget(bool bEnabled)
	{
		UIWidget::EnabledWidget(bEnabled);

		if (IsWidgetEnabled())
		{
			m_nState = PNG_BTNNORMAL;
		}
		else
		{
			m_nState = (m_nCount == 3 ? PNG_BTNDOWN : PNG_BTNENABLE);
		}

		// invalid the window
		Invalidate(TRUE);
	}
	
	// 鼠标移动
	BOOL	UIPngButton::OnMouseMove(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;
	
		if (UIWidget::OnMouseMove(cPt))
			return TRUE;
	
		if (m_bPress)
			return FALSE;

		BOOL bDeliver = FALSE;

		if (PtInRect(cPt))
		{
			m_nState = m_bPress ? PNG_BTNDOWN : PNG_BTNHOVER;
			bDeliver = TRUE;
		}
		else
		{
			m_nState = m_bPress ? PNG_BTNDOWN : PNG_BTNNORMAL;
			bDeliver = FALSE;
		}

		Invalidate(TRUE);

		return FALSE;
	}

	// 左键按下
	BOOL	UIPngButton::OnLeftDown(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		if (UIWidget::OnLeftDown(cPt))
			return TRUE;

		BOOL bDeliver = FALSE;

		if (PtInRect(cPt))
		{
			m_nState = PNG_BTNDOWN;
			bDeliver = TRUE;
		}
		else
		{
			m_nState = PNG_BTNNORMAL;
			bDeliver = FALSE;
		}
		
		m_bPress = TRUE;
		Invalidate(TRUE);

		return bDeliver;
	}

	// 左键弹起
	BOOL	UIPngButton::OnLeftUp(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		if (UIWidget::OnLeftUp(cPt))
			return TRUE;

		BOOL bDeliver = FALSE;

		if (PtInRect(cPt))
		{
			m_nState = PNG_BTNHOVER;
			bDeliver = TRUE;

			if (m_pProcess != NULL)
			{
				m_pProcess->OnClicked(this, cPt);
			}
		}
		else
		{
			m_nState = PNG_BTNNORMAL;
			bDeliver = FALSE;
		}
		
		m_bPress = FALSE;
		Invalidate(TRUE);
		return bDeliver;
	}
}