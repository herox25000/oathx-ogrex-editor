#include "StdAfx.h"
#include "uiframeclose.h"
#include "Platform.h"

#define  WM_BT_CLOSE_PLAZA			101
#define  WM_BT_SWITCH_ACCOUNTS		102
#define  WM_BT_QUITE				103

namespace YouLe
{
	// 构造函数
	UIFrameClose::UIFrameClose()
	{

	}

	// 析构函数
	UIFrameClose::~UIFrameClose()
	{

	}

	// 窗口控件
	BOOL	UIFrameClose::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//加载资源
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_PngBack.LoadImage(hInstance, PlazaViewImage.pszEnquireBack);

		UIPngButton* pClosePlaza = new UIPngButton();
		pClosePlaza->Create(WM_BT_CLOSE_PLAZA, m_PngBack.GetWidth()-160,m_PngBack.GetHeight()-62, pAttach, this, hInstance, PlazaViewImage.pszEnquirePlaza, 4, this);

		UIPngButton* pSwitchAccount = new UIPngButton();
		pSwitchAccount->Create(WM_BT_SWITCH_ACCOUNTS, 30, m_PngBack.GetHeight()-62, pAttach, this, hInstance, PlazaViewImage.pszEnquireSwitch, 4, this);

		return TRUE;
	}

	// 处理按键消息
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