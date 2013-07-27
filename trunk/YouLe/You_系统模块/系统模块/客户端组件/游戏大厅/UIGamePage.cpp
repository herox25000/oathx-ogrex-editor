#include "Stdafx.h"
#include "UIGamePage.h"
#include "GlobalUnits.h"

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

	// 构造函数
	UIGamePage::UIGamePage()
		: m_pGameView(NULL)
	{

	}

	// 析构函数
	UIGamePage::~UIGamePage()
	{
		
	}

	// 窗口控件
	BOOL	UIGamePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		INT nLeft	= GTP_OFFSETX;
		int nTop	= GTP_OFFSETY;

		m_pGameView = new UIGameView();
		m_pGameView->Create(0, CRect(nLeft, nTop, nLeft + GTP_WINDOWX * GTP_ITEMCOL, nTop + GTP_WINDOWY * GTP_ITEMROW),
			pAttach, pProcess, this);

		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// 创建页面按钮
		const TCHAR* chBtnImageResouceName[] = {
			PlazaViewImage.pszGameTabGame,
			PlazaViewImage.pszGameTabCard,
			PlazaViewImage.pszGameTabMahj,
			PlazaViewImage.pszGameTabLeis
		};

		for (int i=0; i<4; i++)
		{
			UIPngButton* pPngButton = new UIPngButton();
			pPngButton->Create(idList[i], i * 96, 0, m_pAttach, this,
				hInstance, chBtnImageResouceName[i], 3, this);
		}

		SetPage(idList[0]);

		return TRUE;
	}

	// 设置页面
	void	UIGamePage::SetPage(INT nID)
	{
		for (int i=0; i<4; i++)
		{
			UIWidget* pWidget = Search(idList[i]);
			if (pWidget)
				pWidget->EnabledWidget(idList[i] == nID ? FALSE : TRUE);
		}
	}

	// 处理按键消息
	BOOL	UIGamePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			SetPage(pWidget->GetID());
			return TRUE;
		}

		return FALSE;
	}
}