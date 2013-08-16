#include "Stdafx.h"
#include "UIFramePage.h"
#include "Platform.h"
#include "UIFrameClose.h"

#define IDC_BT_FRAME_MIN					100							//最小按钮
#define IDC_BT_FRAME_CLOSE					101							//关闭按钮

#define IDC_BT_REFLASH						107							//信息刷新

#define IDC_BT_RETURN						109							//返回
#define IDC_BT_LOBBYSET						110							//大厅设置

#define IDC_BT_USERBAG						111							//角色背包
#define IDC_BT_SQUARE						112							
#define IDC_BT_TILL							113
#define IDC_BT_IM							114



namespace YouLe
{
	// 构造函数
	UIFramePage::UIFramePage()
	{

	}

	// 析构函数
	UIFramePage::~UIFramePage()
	{

	}

	// 窗口控件
	BOOL	UIFramePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		////加载资源
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		UIPngButton* pBtReflash = new UIPngButton();
		pBtReflash->Create(IDC_BT_REFLASH, 178, 282, pAttach, this, hInstance, PlazaViewImage.pszBtReflash, 4, this);

		UIPngButton* pBtSquare = new UIPngButton();
		pBtSquare->Create(IDC_BT_SQUARE, 26, 450, pAttach, this, hInstance, PlazaViewImage.pszBtSquare, 4, this);

		UIPngButton* pBtTill = new UIPngButton();
		pBtTill->Create(IDC_BT_TILL, 72, 450, pAttach, this, hInstance, PlazaViewImage.pszBtTill, 4, this);

		UIPngButton* pBtUserBag = new UIPngButton();
		pBtUserBag->Create(IDC_BT_USERBAG, 122, 450, pAttach, this, hInstance, PlazaViewImage.pszBtBagpack, 4, this);

		UIPngButton* pBtIm = new UIPngButton();
		pBtIm->Create(IDC_BT_IM, 172, 450, pAttach, this, hInstance, PlazaViewImage.pszBtIm, 4, this);
		
		pBtSquare->EnabledWidget(FALSE);
		pBtIm->EnabledWidget(FALSE);

		return TRUE;
	}

	// 处理按键消息
	BOOL	UIFramePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		//switch(pWidget->GetID())
		//{
		//case IDC_BT_FRAME_MIN:
		//	{
		//		m_pAttach->ShowWindow(SW_MINIMIZE);
		//		return TRUE;
		//	}
		//case IDC_BT_LOBBYSET:
		//	{
		//		SendMessage(WM_COMMAND, WM_SHOW_LOBBYSET, NULL);
		//		return TRUE;
		//	}
		//case IDC_BT_FRAME_CLOSE:
		//	{
		//		//UIWidget* pCloseWnd = Search(IDP_FRAME_CLOSE);
		//		//pCloseWnd->MoveToFront();
		//		//pCloseWnd->VisibleWidget(TRUE);
		//		return TRUE;
		//	}
		//}

		return FALSE;
	}
}