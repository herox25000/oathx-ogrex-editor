#include "StdAfx.h"
#include "UIFrameSet.h"
#include "GlobalUnits.h"
#include "Platform.h"

namespace YouLe
{
#define IDC_BT_CLOSE						100
#define IDC_BT_CONFIRN						101
#define IDC_BT_CANCEL						102

#define IDC_BT_NOUSE						103
#define IDC_BT_USE							104

	UIFrameSet::UIFrameSet(void)
	{
	}

	UIFrameSet::~UIFrameSet(void)
	{
	}

	BOOL UIFrameSet::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatformFrameImageNew & FrameViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, FrameViewImage.pszFrameSet);
		
		UIPngButton* pClose = new UIPngButton();
		pClose->Create(IDC_BT_CLOSE, m_ImageBack.GetWidth() - 40, 2, pAttach, this, hInstance, FrameViewImage.pszBtClose, 4, this);

		UIPngButton* pBtConfirn = new UIPngButton();
		pBtConfirn->Create(IDC_BT_CONFIRN, m_ImageBack.GetWidth() / 2 - 100, 210, pAttach, this, hInstance, FrameViewImage.pszBtConfirn, 4, this);

		UIPngButton* pCancel = new UIPngButton();
		pCancel->Create(IDC_BT_CANCEL, m_ImageBack.GetWidth() / 2 + 10, 210, pAttach, this, hInstance, FrameViewImage.pszBtCancel, 4, this);

		UIPngRadioButton* pBtNoUseBoss = new UIPngRadioButton();
		pBtNoUseBoss->Create(IDC_BT_NOUSE, 30, 68, pAttach, this, this);
		pBtNoUseBoss->SetCheck(TRUE);

		UIPngRadioButton* pBtUseBoss = new UIPngRadioButton();
		pBtUseBoss->Create(IDC_BT_USE, 30, 92, pAttach, this, this);
		pBtNoUseBoss->SetCheck(FALSE);
		
		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIFrameSet::OnClicked( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_CLOSE:
		case IDC_BT_CANCEL:
			VisibleWidget(FALSE);
			return TRUE;
		case IDC_BT_CONFIRN:
			VisibleWidget(FALSE);
			return TRUE;
		}
		return FALSE;
	}

	BOOL UIFrameSet::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	BOOL UIFrameSet::OnLeftDown( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_NOUSE:
			{
				UIPngRadioButton* pRatioBt = (UIPngRadioButton*)Search(IDC_BT_USE);
				if (pRatioBt)
				{
					pRatioBt->SetCheck(FALSE);
				}
			}
			return TRUE;
		case  IDC_BT_USE:
			{
				UIPngRadioButton* pRatioBt = (UIPngRadioButton*)Search(IDC_BT_NOUSE);
				if (pRatioBt)
				{
					pRatioBt->SetCheck(FALSE);
				}
			}
			return TRUE;
		}

		return TRUE;
	}

}

