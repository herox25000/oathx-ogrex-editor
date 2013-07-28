#include "StdAfx.h"
#include "uiframeclose.h"
#include "GlobalUnits.h"
#include "Platform.h"

#define  WM_BT_CLOSE_PLAZA			101
#define  WM_BT_SWITCH_ACCOUNTS		102
#define  WM_BT_QUITE				103

namespace YouLe
{
	// ���캯��
	UIFrameClose::UIFrameClose()
	{

	}

	// ��������
	UIFrameClose::~UIFrameClose()
	{

	}

	// ���ڿؼ�
	BOOL	UIFrameClose::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//������Դ
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_PngBack.LoadImage(hInstance, PlazaViewImage.pszEnquireBack);

		UIPngButton* pClosePlaza = new UIPngButton();
		pClosePlaza->Create(WM_BT_CLOSE_PLAZA, m_PngBack.GetWidth()-160,m_PngBack.GetHeight()-70, pAttach, this, hInstance, PlazaViewImage.pszEnquirePlaza, 4, this);

		UIPngButton* pSwitchAccount = new UIPngButton();
		pSwitchAccount->Create(WM_BT_SWITCH_ACCOUNTS, 30, m_PngBack.GetHeight()-70, pAttach, this, hInstance, PlazaViewImage.pszEnquireSwitch, 4, this);

		return TRUE;
	}

	// ��������Ϣ
	BOOL	UIFrameClose::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case WM_BT_CLOSE_PLAZA:
			{
				m_pAttach->SendMessage(WM_COMMAND, WM_CLOSE_FRAME, NULL);
				VisibleWidget(FALSE);
				return TRUE;
			}
		case WM_BT_SWITCH_ACCOUNTS:
			{
				m_pAttach->SendMessage(WM_COMMAND, WM_SWITCH_ACCOUNT, NULL);
				VisibleWidget(FALSE);
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL UIFrameClose::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_PngBack.DrawImage(pDC, cPt.x, cPt.y);
		
		return UIWidget::Draw(pDC);
	}


}