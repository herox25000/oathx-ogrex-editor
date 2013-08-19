#include "StdAfx.h"
#include "UIUserinfoView.h"
#include "Platform.h"

namespace YouLe
{
	UIUserinfoView::UIUserinfoView(void)
	{
	}

	UIUserinfoView::~UIUserinfoView(void)
	{
	}

	BOOL UIUserinfoView::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszUserInfo);

		// 更改
		UIPngButton* pModidyUser = new UIPngButton();
		pModidyUser->Create(IDC_BT_MODIFY_USER, 112, 235, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyUser, 4, this);

		// 修改密码
		UIPngButton* pModifyPass = new UIPngButton();
		pModifyPass->Create(IDC_BT_MODIFY_PASSWORD, 344, 244, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyPassword, 4, this);

		// 修改资料
		UIPngButton* pModifyInfo = new UIPngButton();
		pModifyInfo->Create(IDC_BT_MODIFY_INFO, 206, 244, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyInfo, 4, this);
		
		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIUserinfoView::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		//显示玩家的信息

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UIModifyUserInfoView::UIModifyUserInfoView(void)
	{
	}

	UIModifyUserInfoView::~UIModifyUserInfoView(void)
	{
	}

	BOOL UIModifyUserInfoView::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszModifyUserInfoBack);

		// 确认
		UIPngButton* pModidyOk = new UIPngButton();
		pModidyOk->Create(IDC_BT_MD_USERINFO_OK, 164, 400, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyConfirn, 4, this);

		// 取消
		UIPngButton* pModifyCancel= new UIPngButton();
		pModifyCancel->Create(IDC_BT_MD_USERINFO_CANCEL, 280, 400, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyCancel, 4, this);

		// eidt
		//m_Password.Create(WS_VISIBLE|WS_CHILD, CRect(m_rect.left + 152, m_rect.top + 126, m_rect.left + 418, m_rect.top + 148), pAttach, 0);

		VisibleWidget(FALSE);
	
		return TRUE;

	}

	void UIModifyUserInfoView::VisibleWidget(bool bVisible)
	{
		UIWidget::VisibleWidget(bVisible);

		//m_Password.ShowWindow(bVisible ? SW_SHOW : SW_HIDE);
	}

	BOOL UIModifyUserInfoView::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		//显示玩家的信息

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UIModifyPasswordView::UIModifyPasswordView(void)
	{
	}

	UIModifyPasswordView::~UIModifyPasswordView(void)
	{
	}

	BOOL UIModifyPasswordView::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszModifyPasswordBack);

		// 确认
		UIPngButton* pModidyOk = new UIPngButton();
		pModidyOk->Create(IDC_BT_MD_PASSWORD_OK, 164, 285, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyConfirn, 4, this);

		// 取消
		UIPngButton* pModifyCancel= new UIPngButton();
		pModifyCancel->Create(IDC_BT_MD_PASSWORD_CANCEL, 280, 285, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyCancel, 4, this);

		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIModifyPasswordView::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		//显示玩家的信息

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}
}

