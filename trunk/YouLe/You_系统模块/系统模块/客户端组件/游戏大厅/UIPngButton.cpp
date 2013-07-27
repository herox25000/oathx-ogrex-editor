#include "stdafx.h"
#include "UIPngButton.h"

namespace YouLe
{
	// ��������
	UIPngButton::UIPngButton()
		: m_nState(PNG_BTNNORMAL), m_nSlice(0), m_pImage(NULL), m_bPress(FALSE)
	{

	}

	// ���캯��
	UIPngButton::~UIPngButton()
	{
		if (m_pImage != NULL)
		{
			delete m_pImage;
			m_pImage = NULL;
		}
	}

	// �����ؼ�
	BOOL	UIPngButton::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		HINSTANCE hInstance, LPCTSTR lpResourceName, INT nStatCount, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pParent))
			return FALSE;

		// button image object
		m_pImage = new CPngImage();
		ASSERT(m_pImage != NULL);

		// load image from resouce instance
		BOOL bResult = m_pImage->LoadImage(hInstance,
			lpResourceName);
		ASSERT(bResult);
		
		// calc image slice width
		m_nSlice = m_pImage->GetWidth() / nStatCount;
		
		// calc button client rect
		m_rect.SetRect(rect.left, rect.top, 
			rect.left + m_nSlice, rect.top + m_pImage->GetHeight());

		return TRUE;
	}

	// ��д����
	BOOL	UIPngButton::Draw(CDC* pDC)
	{
		if (!m_bVisible || m_pImage == NULL)
			return FALSE;

		// draw button
		m_pImage->DrawImage(pDC, m_rect.left, m_rect.top, 
			m_nSlice, m_pImage->GetHeight(), m_nSlice * m_nState, 0);

		return UIWidget::Draw(pDC);
	}

	void	UIPngButton::EnabledWidget(bool bEnabled)
	{
		UIWidget::EnabledWidget(bEnabled);

		m_nState = PNG_BTNENABLE;
		Invalidate(TRUE);
	}

	// ���ð�ť�ı�
	void	UIPngButton::SetText(LPCTSTR lpszText)
	{
		
	}
	
	// ����ƶ�
	BOOL	UIPngButton::OnMouseMove(const CPoint& cPt)
	{
		if (UIWidget::OnMouseMove(cPt))
			return TRUE;

		if (m_bVisible && m_bEnabled)
		{
			if (PtInRect(cPt))
			{
				m_nState = m_bPress ? PNG_BTNDOWN : PNG_BTNHOVER;
				Invalidate(TRUE);
				return TRUE;
			}
			else
			{
				m_nState = m_bPress ? PNG_BTNDOWN : PNG_BTNNORMAL;
				Invalidate(TRUE);
				return FALSE;
			}
		}

		return FALSE;
	}

	// �������
	BOOL	UIPngButton::OnLeftDown(const CPoint& cPt)
	{
		if (UIWidget::OnLeftDown(cPt))
			return TRUE;

		if (m_bVisible && m_bEnabled)
		{
			if (PtInRect(cPt))
			{
				m_nState = PNG_BTNDOWN;
				m_bPress = TRUE;
				Invalidate(TRUE);
				
				return TRUE;
			}
			else
			{
				m_nState = PNG_BTNNORMAL;
				Invalidate(TRUE);
				return FALSE;
			}
		}

		return FALSE;
	}

	// �������
	BOOL	UIPngButton::OnLeftUp(const CPoint& cPt)
	{
		if (UIWidget::OnLeftDown(cPt))
			return TRUE;

		if (m_bVisible && m_bEnabled)
		{
			if (PtInRect(cPt))
			{
				m_nState = PNG_BTNHOVER;
			}
			else
			{
				m_nState = PNG_BTNNORMAL;
			}

			m_bPress = FALSE;
			Invalidate(TRUE);
		}

		return FALSE;
	}
}