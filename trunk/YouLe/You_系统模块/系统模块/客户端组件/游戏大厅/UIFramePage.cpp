#include "Stdafx.h"
#include "UIFramePage.h"
#include "Platform.h"
#include "UIFrameClose.h"

#define IDC_BT_FRAME_MIN					100							//最小按钮
#define IDC_BT_FRAME_CLOSE					101							//关闭按钮

#define IDC_BT_GAME							102							//游戏专区
#define IDC_BT_MATCH						103							//比赛专区
#define IDC_BT_PROPERTY						104							//道具商城
#define IDC_BT_PRIZE						105							//奖品中心
#define IDC_BT_RECHARGE						106							//充值中心

#define IDC_BT_REFLASH						107							//信息刷新
#define IDC_BT_USERINFOSET					108							//个人设置
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

		UIPngButton* pBtGame = new UIPngButton();
		pBtGame->Create(IDC_BT_GAME, LESS_SCREEN_CX / 2 - 264, 114, pAttach, this, hInstance, PlazaViewImage.pszBtGame, 4, this);

		UIPngButton* pBtMatch = new UIPngButton();
		pBtMatch->Create(IDC_BT_MATCH, LESS_SCREEN_CX / 2 - 156, 114, pAttach, this, hInstance, PlazaViewImage.pszBtMatch, 4, this);

		UIPngButton* pBtProperty = new UIPngButton();
		pBtProperty->Create(IDC_BT_PROPERTY, LESS_SCREEN_CX / 2 - 264 + 216, 114, pAttach, this, hInstance, PlazaViewImage.pszBtProperty, 4, this);

		UIPngButton* pBtPrize = new UIPngButton();
		pBtPrize->Create(IDC_BT_PRIZE, LESS_SCREEN_CX / 2 + 60, 114, pAttach, this, hInstance, PlazaViewImage.pszBtPrize, 4, this);

		UIPngButton* pBtRecharge = new UIPngButton();
		pBtRecharge->Create(IDC_BT_RECHARGE, LESS_SCREEN_CX / 2 + 168, 114, pAttach, this, hInstance, PlazaViewImage.pszBtRecharge, 4, this);

		UIPngButton* pBtReflash = new UIPngButton();
		pBtReflash->Create(IDC_BT_REFLASH, 178, 282, pAttach, this, hInstance, PlazaViewImage.pszBtReflash, 4, this);

		UIPngButton* pBtUserSet = new UIPngButton();
		pBtUserSet->Create(IDC_BT_USERINFOSET, 26, 250, pAttach, this, hInstance, PlazaViewImage.pszBtUserSet, 4, this);

		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDC_BT_RETURN, LESS_SCREEN_CX / 2 + 210, 170, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

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