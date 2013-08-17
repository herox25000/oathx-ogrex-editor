#include "StdAfx.h"
#include "UIUserInfoSet.h"
#include "GlobalUnits.h"
#include "Platform.h"
#include "UIUserinfoView.h"

namespace YouLe
{
#define IDP_USERINFO_VIEW		1000
#define IDP_MODIFYPASS_VIEW		1001
#define IDP_MODIFYINFO_VIEW		1002

#define VIEW_SIZEX				540
#define VIEW_SIZEY				520

	UIUserInfoSet::UIUserInfoSet(void)
	{
		m_nCurShowPageID = -1;
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

		UIUserinfoView* pUserInfo = new UIUserinfoView();
		pUserInfo->Create(IDP_USERINFO_VIEW, CRect(0, 0, VIEW_SIZEX, VIEW_SIZEY), pAttach, this, this);

		//修改资料界面
		UIModifyUserInfoView* pModifyInfo = new UIModifyUserInfoView();
		pModifyInfo->Create(IDP_MODIFYINFO_VIEW, CRect(0, 0, VIEW_SIZEX, VIEW_SIZEY), pAttach, this, this);

		//修改密码界面
		UIModifyPasswordView* pModifyPass = new UIModifyPasswordView();
		pModifyPass->Create(IDP_MODIFYPASS_VIEW, CRect(0, 0, VIEW_SIZEX, VIEW_SIZEY), pAttach, this, this);

		VisibleWidget(FALSE);

		return TRUE;
	}

	void UIUserInfoSet::VisibleTrigger()
	{
		UIWidget* pView = Search(IDP_USERINFO_VIEW);
		if (pView)
		{
			pView->VisibleWidget(TRUE);
		}
		if (m_nCurShowPageID != IDP_USERINFO_VIEW && m_nCurShowPageID > 0)
		{
			pView = Search(m_nCurShowPageID);
			if (pView)
				pView->VisibleWidget(FALSE);
		}
		m_nCurShowPageID = IDP_USERINFO_VIEW;
	}

	BOOL UIUserInfoSet::OnClicked( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
			// 修改资料
		case IDC_BT_MODIFY_INFO:
			{
				ShowPage(IDP_MODIFYINFO_VIEW);
				return TRUE;
			}
			// 修改密码
		case IDC_BT_MODIFY_PASSWORD:
			{
				ShowPage(IDP_MODIFYPASS_VIEW);
				return TRUE;
			}
			// 修改用户
		case IDC_BT_MODIFY_USER:
			{
				return TRUE;
			}
			// 确认修改用户资料
		case IDC_BT_MD_USERINFO_OK:
			{
				ShowPage(IDP_USERINFO_VIEW);
				return TRUE;
			}
			// 取消修改用户资料
		case IDC_BT_MD_USERINFO_CANCEL:
			{
				ShowPage(IDP_USERINFO_VIEW);
				return TRUE;
			}
			// 确认修改密码
		case IDC_BT_MD_PASSWORD_OK:
			{
				ShowPage(IDP_USERINFO_VIEW);
				return TRUE;
			}
			//取消修改密码
		case IDC_BT_MD_PASSWORD_CANCEL:
			{
				ShowPage(IDP_USERINFO_VIEW);
				return TRUE;
			}
		}
		return TRUE;
	}

	void UIUserInfoSet::ShowPage( int nPageID )
	{
		UIWidget* pView = Search(nPageID);
		if (pView)
		{
			pView->VisibleWidget(TRUE);
		}
		if (m_nCurShowPageID > 0)
		{
			pView = Search(m_nCurShowPageID);
			if (pView)
				pView->VisibleWidget(FALSE);
		}
		m_nCurShowPageID = nPageID;
	}

}
