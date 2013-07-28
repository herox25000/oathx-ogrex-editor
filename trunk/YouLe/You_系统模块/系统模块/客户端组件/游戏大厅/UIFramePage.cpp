#include "Stdafx.h"
#include "UIFramePage.h"
#include "GlobalUnits.h"
#include "Platform.h"

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
#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WINDOWX			176
#define GTP_WINDOWY			140
#define GTP_ITEMCOL			3
#define GTP_ITEMROW			3

	static const INT idList[] = {
		IDB_GAMETAB_GAME, IDB_GAMETAB_CARD, IDB_GAMETAB_MAHJ, IDB_GAMETAB_LEIS
	};
	
	struct sResourceInfo
	{
	public:
		sResourceInfo(TCHAR* chResourcName, int x, int y)
		{
			pResourceName = chResourcName;
			nPosx = x;
			nPosy = y;
		}
	public:
		TCHAR* pResourceName;
		int nPosx; 
		int nPosy;
	};

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

		//加载资源
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		UIPngButton* pLobbySet = new UIPngButton();
		pLobbySet->Create(IDC_BT_LOBBYSET, LESS_SCREEN_CX - 120, 3, pAttach, this, hInstance, PlazaViewImage.pszBtFrameSet, 4, this);

		UIPngButton* pMin = new UIPngButton();
		pMin->Create(IDC_BT_FRAME_MIN, LESS_SCREEN_CX - 80, 3, pAttach, this, hInstance, PlazaViewImage.pszBtMin, 4, this);

		UIPngButton* pClose = new UIPngButton();
		pClose->Create(IDC_BT_FRAME_CLOSE, LESS_SCREEN_CX - 42, 3, pAttach, this, hInstance, PlazaViewImage.pszBtClose, 4, this);

		UIPngButton* pBtGame = new UIPngButton();
		pBtGame->Create(IDC_BT_GAME, LESS_SCREEN_CX / 2 - 264, 154, pAttach, this, hInstance, PlazaViewImage.pszBtGame, 4, this);

		UIPngButton* pBtMatch = new UIPngButton();
		pBtMatch->Create(IDC_BT_MATCH, LESS_SCREEN_CX / 2 - 156, 154, pAttach, this, hInstance, PlazaViewImage.pszBtMatch, 4, this);

		UIPngButton* pBtProperty = new UIPngButton();
		pBtProperty->Create(IDC_BT_PROPERTY, LESS_SCREEN_CX / 2 - 264 + 216, 154, pAttach, this, hInstance, PlazaViewImage.pszBtProperty, 4, this);

		UIPngButton* pBtPrize = new UIPngButton();
		pBtPrize->Create(IDC_BT_PRIZE, LESS_SCREEN_CX / 2 + 60, 154, pAttach, this, hInstance, PlazaViewImage.pszBtPrize, 4, this);

		UIPngButton* pBtRecharge = new UIPngButton();
		pBtRecharge->Create(IDC_BT_RECHARGE, LESS_SCREEN_CX / 2 + 168, 154, pAttach, this, hInstance, PlazaViewImage.pszBtRecharge, 4, this);

		UIPngButton* pBtReflash = new UIPngButton();
		pBtReflash->Create(IDC_BT_REFLASH, 178, 322, pAttach, this, hInstance, PlazaViewImage.pszBtReflash, 4, this);

		UIPngButton* pBtUserSet = new UIPngButton();
		pBtUserSet->Create(IDC_BT_USERINFOSET, 26, 290, pAttach, this, hInstance, PlazaViewImage.pszBtUserSet, 4, this);

		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDC_BT_RETURN, LESS_SCREEN_CX / 2 + 210, 210, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		UIPngButton* pBtSquare = new UIPngButton();
		pBtSquare->Create(IDC_BT_SQUARE, 26, 490, pAttach, this, hInstance, PlazaViewImage.pszBtSquare, 4, this);

		UIPngButton* pBtTill = new UIPngButton();
		pBtTill->Create(IDC_BT_TILL, 72, 490, pAttach, this, hInstance, PlazaViewImage.pszBtTill, 4, this);

		UIPngButton* pBtUserBag = new UIPngButton();
		pBtUserBag->Create(IDC_BT_USERBAG, 122, 490, pAttach, this, hInstance, PlazaViewImage.pszBtBagpack, 4, this);

		UIPngButton* pBtIm = new UIPngButton();
		pBtIm->Create(IDC_BT_IM, 172, 490, pAttach, this, hInstance, PlazaViewImage.pszBtIm, 4, this);
		
		pBtSquare->EnabledWidget(FALSE);
		pBtIm->EnabledWidget(FALSE);

		return TRUE;
	}

	// 处理按键消息
	BOOL	UIFramePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_FRAME_MIN:
			{
				m_pAttach->ShowWindow(SW_MINIMIZE);
				return TRUE;
			}
		case IDC_BT_LOBBYSET:
			{
				return TRUE;
			}
		case IDC_BT_FRAME_CLOSE:
			{
				return TRUE;
			}
		case IDC_BT_FRAME_CLOSE:
			{
				return TRUE;
			}
		}

		return FALSE;
	}
}