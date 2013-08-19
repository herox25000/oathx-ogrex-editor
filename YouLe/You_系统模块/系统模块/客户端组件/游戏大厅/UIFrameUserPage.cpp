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

			CRect rcAccounts;
			char toStr[25];
			//昵称
			rcAccounts.SetRect(m_rect.left + 66, m_rect.top + 176, m_rect.left + 166, m_rect.top + 192);
			pDC->DrawText(UserData.szNickName,lstrlen(UserData.szNickName), &rcAccounts, DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//输出帐号
			rcAccounts.SetRect(m_rect.left + 66, m_rect.top + 198, m_rect.left + 166, m_rect.top + 214);
			pDC->DrawText(UserData.szAccounts,lstrlen(UserData.szAccounts), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//等级
			rcAccounts.SetRect(m_rect.left + 54, m_rect.top + 226, m_rect.left + 76, m_rect.top + 242);
			itoa(UserData.wLevel, toStr, 10);
			pDC->DrawText(toStr,lstrlen(toStr), &rcAccounts,DT_SINGLELINE|DT_CENTER|DT_END_ELLIPSIS);
			//游币
			rcAccounts.SetRect(m_rect.left + 74, m_rect.top + 254, m_rect.left + 202, m_rect.top + 270);
			itoa(UserData.lScore, toStr, 10);
			pDC->DrawText(toStr,lstrlen(toStr), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//乐豆
			rcAccounts.SetRect(m_rect.left + 74, m_rect.top + 284, m_rect.left + 202, m_rect.top + 300);
			itoa(UserData.lBeans, toStr, 10);
			pDC->DrawText(toStr,lstrlen(toStr), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//奖券
			rcAccounts.SetRect(m_rect.left + 74, m_rect.top + 314, m_rect.left + 202, m_rect.top + 330);
			itoa(UserData.lLottery, toStr, 10);
			pDC->DrawText(toStr,lstrlen(toStr), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
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
