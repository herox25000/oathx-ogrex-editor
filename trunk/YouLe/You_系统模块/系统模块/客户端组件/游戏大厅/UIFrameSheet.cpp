#include "Stdafx.h"
#include "UIFrameSheet.h"
#include "UIFrameClose.h"
#include "UIFrameSet.h"
#include "UIPlazaView.h"
#include "UIFrameUserPage.h"
#include "Platform.h"

namespace YouLe
{
#define IDB_FRAME_CLOSE						65535
#define IDB_FRAME_MIN						65534
#define IDB_FRAME_SET						65533

#define IDP_FRAME_CLOSE						55580
#define IDP_FRAME_SET						55579
#define IDP_PLAZA_PAGE						55578
#define IDP_USER_PAGE						55577

#define PFS_CAPTION_HEIGHT					40

	// 系统按钮ID
	const static INT idFrameList[] = {
		IDB_FRAME_CLOSE, IDB_FRAME_MIN, IDB_FRAME_SET
	};

	// 构造函数
	UIFrameSheet::UIFrameSheet()
	{	

	}
	
	// 析构函数
	UIFrameSheet::~UIFrameSheet()
	{

	}

	// 创建窗口
	BOOL UIFrameSheet::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
		
		//加载资源
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		ASSERT(hInstance != NULL);

		// 按钮资源
		const TCHAR* chSystemResouceName[] = {
			PlazaViewImage.pszBtClose,
			PlazaViewImage.pszBtMin,
			PlazaViewImage.pszBtFrameSet,
		};

		for (int i=0; i<3; i++)
		{
			UIPngButton* pSystemButton = new UIPngButton();
			pSystemButton->Create(idFrameList[i], rect.right - (i + 1) * 40, 3, pAttach, this, hInstance, chSystemResouceName[i], 4, this);
		}

		tagPlatformFrameImageNew & PlazaFrameImage = g_GlobalUnits.m_PlatformFrameImage;
		
		// 广告头页
		
		// 用户信息页
		UIFrameUserPage* pUserPage = new UIFrameUserPage();
		pUserPage->Create(IDP_USER_PAGE, CRect(PUP_OFFSETX, PUP_OFFSETY, PUP_OFFSETX + PUP_WITH, PUP_OFFSETY + PUP_HEIGHT), pAttach, this, this);

		// 广场页
		UIPlazaView* pPlazaPage = new UIPlazaView();
		pPlazaPage->Create(IDP_PLAZA_PAGE, CRect(PGP_OFFSETX, PGP_OFFSETY, PGP_OFFSETX+PGP_WITH, PGP_OFFSETY+PGP_HEIGHT), pAttach, this, this);
		
		//活动公告管理页

		// 创建退出框
		UIFrameClose* pClose	= new UIFrameClose();
		INT x = rect.right	/ 2 - 180;
		INT y = rect.bottom / 2 - 109;
		pClose->Create(IDP_FRAME_CLOSE, CRect(x, y, x + 360, y+218), pAttach, this, this);

		//创建框架设置框
		UIFrameSet* pSet = new UIFrameSet();
		x = rect.right / 2 - 180;
		y = rect.bottom / 2 - 120;
		pSet->Create(IDP_FRAME_SET, CRect(x, y, x + 359, y+240), pAttach, this, this);

		return TRUE;
	}

	// 按钮按下
	BOOL UIFrameSheet::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case IDB_FRAME_SET:
			{
				UIWidget* pSet = Search(IDP_FRAME_SET);
				if (pSet)
				{
					pSet->VisibleWidget(TRUE);
				}
			}
			break;
		case IDB_FRAME_MIN:
			{
				if (m_pAttach)
					m_pAttach->ShowWindow(SW_MINIMIZE);
			}
			break;
		case IDB_FRAME_CLOSE:
			{
				UIWidget* pClose = Search(IDP_FRAME_CLOSE);
				if (pClose)
				{
					pClose->VisibleWidget(TRUE);
				}
			}
			break;
		}

		return TRUE;
	}

	void UIFrameSheet::ProcessCommand( int nCommand )
	{
		switch(nCommand)
		{
		case WM_SHOW_USERSET:
			{
				UIPlazaView* pPage = (UIPlazaView*)Search(IDP_PLAZA_PAGE);
				if (pPage)
				{
					pPage->ShowPage(IDP_USERSET_VIEW);
				}
				break;
			}
		case WM_SHOW_GAMEPAGE:
			{
				UIPlazaView* pPage = (UIPlazaView*)Search(IDP_PLAZA_PAGE);
				if (pPage)
				{
					pPage->ShowPage(IDP_GAME_VIEW);
				}
				break;
			}
		}
	}

}