#include "stdafx.h"
#include "UIPngButton.h"
#include "GlobalUnits.h"

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
		if ( m_nState < m_nCount )
		{
			m_pImage->DrawImage(pDC, m_rect.left, m_rect.top, 
				m_nSlice, m_pImage->GetHeight(), m_nSlice * m_nState, 0);
		}

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
	
		if (m_pProcess)
			m_pProcess->OnMouseMove(this, cPt);

		Invalidate(TRUE);

		return TRUE;
	}

	// 左键按下
	BOOL	UIPngButton::OnLeftDown(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		UIWidget::OnLeftDown(cPt);

		m_bPress = TRUE;

		if (PtInRect(cPt))
			m_nState = PNG_BTNDOWN;

		Invalidate(TRUE);

		return TRUE;
	}

	// 左键弹起
	BOOL	UIPngButton::OnLeftUp(const CPoint& cPt)
	{
		m_bPress = FALSE;

		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		UIWidget::OnLeftUp(cPt);
		
		if (PtInRect(cPt))
			m_nState = PNG_BTNHOVER;
		else
			m_nState = PNG_BTNNORMAL;

		Invalidate(TRUE);

		return TRUE;
	}
	
	// 鼠标离开
	BOOL	UIPngButton::OnMouseLeave(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		UIWidget::OnMouseLeave(cPt);

		m_nState = m_bPress ? PNG_BTNDOWN : PNG_BTNNORMAL;
		Invalidate(TRUE);

		return TRUE;
	}

	// 鼠标进入
	BOOL	UIPngButton::OnMouseEnter(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		UIWidget::OnMouseEnter(cPt);

		m_nState = PNG_BTNHOVER;
		Invalidate(TRUE);

		return TRUE;
	}

	void UIPngButton::SetButtonState( int nType )
	{
		if (!m_bVisible || !m_bEnabled)
			return;
		m_nState = nType;
		Invalidate(TRUE);
	}

	/////////////////////////////////////////////////////////////////////////////
	//单选框
	UIPngRadioButton::UIPngRadioButton(void)
	{
		m_nState = 0;
	}

	UIPngRadioButton::~UIPngRadioButton(void)
	{
	}

	BOOL UIPngRadioButton::Create( INT nID, INT x, INT y, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		tagPlatformFrameImageNew & FrameViewImage = CGlobalUnits::GetSingleton()->m_PlatformFrameImage;
		HINSTANCE hInstance = CGlobalUnits::GetSingleton()->m_PlatformResourceModule->GetResInstance();

		m_pImage = new CPngImage();
		ASSERT(m_pImage != NULL);

		BOOL bResult = m_pImage->LoadImage(hInstance, FrameViewImage.pszBtChose);
		ASSERT(bResult);

		// calc image slice width
		m_nSlice = m_pImage->GetWidth() / 2;

		// calc button client rect
		CRect area(x, y, 
			x + m_nSlice, y + m_pImage->GetHeight());

		return UIWidget::Create(nID, area, pAttach, 
			pProcess, pParent);
	}

	void UIPngRadioButton::SetCheck( BOOL bCheck )
	{
		if (bCheck)
			m_nState = PNG_BTNDOWN;
		else
			m_nState = PNG_BTNNORMAL;
		Invalidate(TRUE);
	}

	BOOL UIPngRadioButton::OnLeftDown( const CPoint& cPt )
	{
		if (!m_bVisible || !m_bEnabled)
			return FALSE;

		UIWidget::OnLeftDown(cPt);

		if (PtInRect(cPt))
			m_nState = PNG_BTNDOWN;

		Invalidate(TRUE);

		return TRUE;
	}

	BOOL	UIPngRadioButton::Draw(CDC* pDC)
	{
		if (!m_bVisible || m_pImage == NULL)
			return FALSE;

		// draw button
		if ( m_nState < 2 )
		{
			m_pImage->DrawImage(pDC, m_rect.left, m_rect.top, 
				m_nSlice, m_pImage->GetHeight(), m_nSlice * m_nState, 0);
		}

		return UIWidget::Draw(pDC);
	}

}