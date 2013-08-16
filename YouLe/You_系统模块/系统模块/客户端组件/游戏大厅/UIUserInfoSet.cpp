#include "StdAfx.h"
#include "UIUserInfoSet.h"
#include "GlobalUnits.h"
#include "Platform.h"

namespace YouLe
{
	UIUserInfoSet::UIUserInfoSet(void)
	{
	}

	UIUserInfoSet::~UIUserInfoSet(void)
	{
	}

	BOOL UIUserInfoSet::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszUserInfo);

		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIUserInfoSet::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

}
