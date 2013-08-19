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

		// ����
		UIPngButton* pModidyUser = new UIPngButton();
		pModidyUser->Create(IDC_BT_MODIFY_USER, 112, 235, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyUser, 4, this);

		// �޸�����
		UIPngButton* pModifyPass = new UIPngButton();
		pModifyPass->Create(IDC_BT_MODIFY_PASSWORD, 344, 244, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyPassword, 4, this);

		// �޸�����
		UIPngButton* pModifyInfo = new UIPngButton();
		pModifyInfo->Create(IDC_BT_MODIFY_INFO, 206, 244, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyInfo, 4, this);
		
		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIUserinfoView::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		//��ʾ��ҵ���Ϣ
		tagGlobalUserData& UserData = g_GlobalUnits.GetGolbalUserData();
		if (UserData.dwUserID)
		{
			CRect rcAccounts;
			char toStr[25];
			//�ǳ�
			rcAccounts.SetRect(m_rect.left + 262, m_rect.top + 76, m_rect.left + 346, m_rect.top + 94);
			pDC->DrawText(UserData.szNickName,lstrlen(UserData.szNickName), &rcAccounts, DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//����ʺ�
			rcAccounts.SetRect(m_rect.left + 416, m_rect.top + 76, m_rect.left + 520, m_rect.top + 94);
			pDC->DrawText(UserData.szAccounts,lstrlen(UserData.szAccounts), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//����
			rcAccounts.SetRect(m_rect.left + 262, m_rect.top + 110, m_rect.left + 346, m_rect.top + 126);
			pDC->DrawText(UserData.szUserName,lstrlen(UserData.szUserName), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//�Ա�
			rcAccounts.SetRect(m_rect.left + 416, m_rect.top + 110, m_rect.left + 520, m_rect.top + 126);
			if (UserData.cbGender)
				sprintf(toStr, "%s", "��");
			else
				sprintf(toStr, "%s", "Ů");
			pDC->DrawText(toStr,lstrlen(toStr), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//���ڳ���
			rcAccounts.SetRect(m_rect.left + 262, m_rect.top + 150, m_rect.left + 520, m_rect.top + 166);
			pDC->DrawText(UserData.szAddress,lstrlen(UserData.szAddress), &rcAccounts,DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);
			//����ǩ��
		}

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

		// ȷ��
		UIPngButton* pModidyOk = new UIPngButton();
		pModidyOk->Create(IDC_BT_MD_USERINFO_OK, 164, 400, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyConfirn, 4, this);

		// ȡ��
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

		//��ʾ��ҵ���Ϣ

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

		// ȷ��
		UIPngButton* pModidyOk = new UIPngButton();
		pModidyOk->Create(IDC_BT_MD_PASSWORD_OK, 164, 285, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyConfirn, 4, this);

		// ȡ��
		UIPngButton* pModifyCancel= new UIPngButton();
		pModifyCancel->Create(IDC_BT_MD_PASSWORD_CANCEL, 280, 285, pAttach, pProcess, hInstance, PlazaViewImage.pszBtModifyCancel, 4, this);

		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIModifyPasswordView::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		//��ʾ��ҵ���Ϣ

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		return UIWidget::Draw(pDC);
	}
}

