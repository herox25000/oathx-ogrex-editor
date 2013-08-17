#include "StdAfx.h"
#include "UIFrameUserPage.h"
#include "Platform.h"
#include "GlobalUnits.h"

namespace YouLe
{

	UIFrameUserPage::UIFrameUserPage(void)
	{
	}

	UIFrameUserPage::~UIFrameUserPage(void)
	{
	}

	BOOL UIFrameUserPage::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		////加载资源
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		
		m_UserHead.LoadImage(hInstance, PlazaViewImage.pszBtUserSexHead);

		UIPngButton* pBtUserSet = new UIPngButton();
		pBtUserSet->Create(IDC_BT_USERSET, 26, 145, pAttach, this, hInstance, PlazaViewImage.pszBtUserSet, 4, this);

		UIPngButton* pBtReflash = new UIPngButton();
		pBtReflash->Create(IDC_BT_REFLASH, 178, 176, pAttach, this, hInstance, PlazaViewImage.pszBtReflash, 4, this);

		UIPngButton* pBtSquare = new UIPngButton();
		pBtSquare->Create(IDC_BT_SQUARE, 26, 345, pAttach, this, hInstance, PlazaViewImage.pszBtSquare, 4, this);

		UIPngButton* pBtTill = new UIPngButton();
		pBtTill->Create(IDC_BT_TILL, 72, 345, pAttach, this, hInstance, PlazaViewImage.pszBtTill, 4, this);

		UIPngButton* pBtUserBag = new UIPngButton();
		pBtUserBag->Create(IDC_BT_USERBAG, 122, 345, pAttach, this, hInstance, PlazaViewImage.pszBtBagpack, 4, this);

		UIPngButton* pBtIm = new UIPngButton();
		pBtIm->Create(IDC_BT_IM, 172, 345, pAttach, this, hInstance, PlazaViewImage.pszBtIm, 4, this);

		pBtSquare->EnabledWidget(FALSE);
		pBtIm->EnabledWidget(FALSE);

		return TRUE;
	}

	BOOL UIFrameUserPage::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		//绘制用户信息
		tagGlobalUserData& UserData = g_GlobalUnits.GetGolbalUserData();
		if (UserData.dwUserID!=0L)
		{
			int nHeadNumberWidth	= m_UserHead.GetWidth() / 2;
			int nHeadNumberHeight	= m_UserHead.GetHeight(); 
			//输出头像
			if (UserData.cbGender)
			{
				m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, 0, 0);
			}
			else
			{
				m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, nHeadNumberWidth, 0);
			}

			//输出帐号
			CRect rcAccounts;
			rcAccounts.SetRect(66, 344, 166,360);
			pDC->DrawText(UserData.szAccounts,lstrlen(UserData.szAccounts),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
		}


		return UIWidget::Draw(pDC);
	}

	BOOL UIFrameUserPage::OnClicked( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_USERSET:		//用户设置
			{
				SendMessage(WM_COMMAND, WM_SHOW_USERSET, NULL);
				return TRUE;	
			}
		case IDC_BT_REFLASH:		//刷新
			{

				return TRUE;
			}
		}
		return TRUE;
	}


}
