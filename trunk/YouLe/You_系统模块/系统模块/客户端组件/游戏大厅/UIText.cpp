#include "Stdafx.h"
#include "UIText.h"

namespace YouLe
{
	UIText::UIText()
		: m_dwColour(RGB(0, 0, 0)), m_uFormat(DT_LEFT|DT_VCENTER)
	{

	}

	UIText::~UIText()
	{

	}

	// �����ؼ�
	BOOL	UIText::Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
		CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		// to do:  create a new font
		return TRUE;
	}

	// �����ı�
	void	UIText::SetText(LPCTSTR lpszText)
	{
		m_szText = lpszText;
	}

	// ��ȡ�ı�
	CString	UIText::GetText() const
	{
		return m_szText;
	}

	// ���ö���
	void	UIText::SetTextFormat(UINT nFormat)
	{
		m_uFormat = nFormat;
	}

	// ��ȡ����
	UINT	UIText::GetTextFormat() const
	{
		return m_uFormat;
	}

	// ������ɫ
	void	UIText::SetColour(DWORD dwColour)
	{
		m_dwColour = dwColour;
	}

	// ��ȡ��ɫ
	DWORD	UIText::GetColour() const
	{
		return m_dwColour;
	}

	// �ؼ�����
	BOOL	UIText::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		// ��ȡ�ı����ƿ��
		CSize cSize = pDC->GetTextExtent(m_szText);

		// �����ı���������
		CRect rectText;
		rectText.SetRect(m_rect.left, 
			m_rect.top, m_rect.left + cSize.cx, m_rect.top + m_rect.Height());
		if (IsWidgetEnabled())
		{
			// ���������ı�
			pDC->SetTextColor(m_dwColour);
			pDC->DrawText(m_szText, &rectText, m_uFormat);
		}
		else{
			// ���ƻ�ɫ�ı�
			pDC->SetTextColor(RGB(195, 195, 195));
			pDC->DrawText(m_szText, &rectText, m_uFormat);
		}

		return UIWidget::Draw(pDC);
	}
}