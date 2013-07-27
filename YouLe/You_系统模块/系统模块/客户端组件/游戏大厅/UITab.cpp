#include "Stdafx.h"
#include "UITab.h"

namespace YouLe
{
	UITab::UITab() 
		: m_nCurPage(0)
	{

	}

	UITab::~UITab()
	{

	}

	BOOL	UITab::Create(INT nID, const RECT& rect, CWnd* pAttach, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pParent))
			return FALSE;

		return TRUE;
	}

	void	UITab::SetCurPage(INT nPage)
	{
		m_nCurPage = nPage;
	}

	INT		UITab::GetCurPage() const
	{
		return m_nCurPage;
	}

	BOOL	UITab::OnMouseMove(const CPoint& cPt)
	{
		if (!m_bVisible || !m_bEnabled)
			return TRUE;

		if (UIWidget::OnMouseMove(cPt))
			return TRUE;

		return FALSE;
	}
}