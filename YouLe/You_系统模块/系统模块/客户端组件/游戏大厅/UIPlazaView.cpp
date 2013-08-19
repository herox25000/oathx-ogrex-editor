#include "StdAfx.h"
#include "UIPlazaView.h"
#include "UIGamePage.h"
#include "Platform.h"
#include "UIUserInfoSet.h"

namespace YouLe
{
#define IDP_GAME_VIEW						55530				//导航游戏对应界面
#define IDP_MATCH_VIEW						55529
#define IDP_PROPERTY_VIEW					55528
#define IDP_PRIZE_VIEW						55527
#define IDP_RECHARGE_VIEW					55526

#define IDP_USERSET_VIEW					55525

//中间显示大小
#define LFET_GAME							23
#define TOP_GAME							59
#define GAMEPAGE_WIDTH						540	
#define GAMEPAGE_HEIGTH						520

//导航位置
#define BUTTON_X							26
#define BUTTON_Y							5

	static const INT ButtonID[] = { IDC_BT_GAME, IDC_BT_MATCH, IDC_BT_PROPERTY, IDC_BT_PRIZE, IDC_BT_RECHARGE };

	UIPlazaView::UIPlazaView(void)
	{
		m_mViewList.insert(make_pair(IDC_BT_GAME, IDP_GAME_VIEW));
		m_mViewList.insert(make_pair(IDC_BT_MATCH, IDP_MATCH_VIEW));
		m_mViewList.insert(make_pair(IDC_BT_PROPERTY, IDP_PROPERTY_VIEW));
		m_mViewList.insert(make_pair(IDC_BT_PRIZE, IDP_PRIZE_VIEW));
		m_mViewList.insert(make_pair(IDC_BT_RECHARGE, IDP_RECHARGE_VIEW));

		m_mViewList.insert(make_pair(IDC_BT_USERSET, IDP_USERSET_VIEW));

		m_nCurDispView = -1;
	}

	UIPlazaView::~UIPlazaView(void)
	{
		m_mViewList.clear();
	}

	BOOL UIPlazaView::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//加载资源
		tagPlatViewImageNew	& PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// 创建导航条
		const TCHAR* chBtnImageResouceName[] = {
				PlazaViewImage.pszBtGame,
				PlazaViewImage.pszBtMatch,
				PlazaViewImage.pszBtProperty,
				PlazaViewImage.pszBtPrize,
				PlazaViewImage.pszBtRecharge
		};

		for (int i = 0; i < 5; i++)
		{
			UIPngButton* pButton = new UIPngButton();
			pButton->Create(ButtonID[i], BUTTON_X + 108 * i, BUTTON_Y, pAttach, this, hInstance, chBtnImageResouceName[i], 4, this);
		}

		//游戏列表
		UIGamePage* pGamePage = new UIGamePage();
		pGamePage->Create(IDP_GAME_VIEW, CRect(LFET_GAME, TOP_GAME, LFET_GAME + GAMEPAGE_WIDTH, TOP_GAME + GAMEPAGE_HEIGTH), pAttach, this, this);

		//用户信息
		UIUserInfoSet* pUserSet = new UIUserInfoSet();
		pUserSet->Create(IDP_USERSET_VIEW, CRect(LFET_GAME - 5, TOP_GAME + 36, LFET_GAME + GAMEPAGE_WIDTH - 5, TOP_GAME + GAMEPAGE_HEIGTH + 36), 
						pAttach, this, this);

		// 创建返回按钮
		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDB_GPRETURN, rect.right - 300, 62, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		ShowPage(IDC_BT_GAME);
		return TRUE;
	}

	BOOL UIPlazaView::OnLeftDown( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDB_GPRETURN:
			{
				ShowPage(IDC_BT_GAME);
				return TRUE;
			}
		case IDC_BT_GAME:
			{
				ShowPage(IDC_BT_GAME);
				return TRUE;
			}
		}
		return TRUE;
	}

	void UIPlazaView::ShowPage( int nPageID )
	{
		std::map<int, int>::iterator it = m_mViewList.find(nPageID);
		if (it != m_mViewList.end())
		{
			if (m_nCurDispView > 0)
			{
				UIWidget* pHidePage = Search(m_nCurDispView);
				if (pHidePage)
				{
					pHidePage->VisibleWidget(FALSE);
				}
			}
			int nWidgetID = it->second;
			UIWidget* pShowPage = Search(nWidgetID);
			if (pShowPage)
			{
				pShowPage->VisibleWidget(TRUE);
			}
			m_nCurDispView = nWidgetID;
		}
	}

}

