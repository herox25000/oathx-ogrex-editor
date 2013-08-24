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

	// 创建控件
	BOOL	UIText::Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
		CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		// to do:  create a new font
		return TRUE;
	}

	// 设置文本
	void	UIText::SetText(LPCTSTR lpszText)
	{
		m_szText = lpszText;
	}

	// 获取文本
	CString	UIText::GetText() const
	{
		return m_szText;
	}

	// 设置对齐
	void	UIText::SetTextFormat(UINT nFormat)
	{
		m_uFormat = nFormat;
	}

	// 获取对齐
	UINT	UIText::GetTextFormat() const
	{
		return m_uFormat;
	}

	// 设置颜色
	void	UIText::SetColour(DWORD dwColour)
	{
		m_dwColour = dwColour;
	}

	// 获取颜色
	DWORD	UIText::GetColour() const
	{
		return m_dwColour;
	}

	// 控件绘制
	BOOL	UIText::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		// 获取文本绘制宽度
		CSize cSize = pDC->GetTextExtent(m_szText);

		// 计算文本绘制区域
		CRect rectText;
		rectText.SetRect(m_rect.left, 
			m_rect.top, m_rect.left + cSize.cx, m_rect.top + m_rect.Height());
		if (IsWidgetEnabled())
		{
			// 绘制正常文本
			pDC->SetTextColor(m_dwColour);
			pDC->DrawText(m_szText, &rectText, m_uFormat);
		}
		else{
			// 绘制灰色文本
			pDC->SetTextColor(RGB(195, 195, 195));
			pDC->DrawText(m_szText, &rectText, m_uFormat);
		}

		return UIWidget::Draw(pDC);
	}
}