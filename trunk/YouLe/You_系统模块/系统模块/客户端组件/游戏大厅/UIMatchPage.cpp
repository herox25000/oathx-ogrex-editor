#include "StdAfx.h"
#include "UIMatchPage.h"

namespace YouLe
{
	UIMatchPage::UIMatchPage(void)
	{
	}

	UIMatchPage::~UIMatchPage(void)
	{
	}

	BOOL UIMatchPage::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);


		VisibleWidget(FALSE);

		return TRUE;
	}

}

