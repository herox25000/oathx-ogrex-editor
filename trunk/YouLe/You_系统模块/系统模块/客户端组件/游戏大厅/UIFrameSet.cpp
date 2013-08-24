#include "StdAfx.h"
#include "UIFrameSet.h"

namespace YouLe
{
#define IDC_BT_CLOSE						100
#define IDC_BT_CONFIRN						101
#define IDC_BT_CANCEL						102

#define IDC_BT_NOUSE						103
#define IDC_BT_USE							104

	UIFrameSet::UIFrameSet(void)
	{
	}

	UIFrameSet::~UIFrameSet(void)
	{
	}

	BOOL UIFrameSet::Create( INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent )
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		tagPlatformFrameImageNew & FrameViewImage = CGlobalUnits::GetSingleton()->m_PlatformFrameImage;
		HINSTANCE hInstance = CGlobalUnits::GetSingleton()->m_PlatformResourceModule->GetResInstance();

		m_ImageBack.LoadImage(hInstance, FrameViewImage.pszFrameSet);
		
		UIPngButton* pClose = new UIPngButton();
		pClose->Create(IDC_BT_CLOSE, m_ImageBack.GetWidth() - 40, 2, pAttach, this, hInstance, FrameViewImage.pszBtClose, 4, this);

		UIPngButton* pBtConfirn = new UIPngButton();
		pBtConfirn->Create(IDC_BT_CONFIRN, m_ImageBack.GetWidth() / 2 - 100, 210, pAttach, this, hInstance, FrameViewImage.pszBtConfirn, 4, this);

		UIPngButton* pCancel = new UIPngButton();
		pCancel->Create(IDC_BT_CANCEL, m_ImageBack.GetWidth() / 2 + 10, 210, pAttach, this, hInstance, FrameViewImage.pszBtCancel, 4, this);

		UIPngRadioButton* pBtNoUseBoss = new UIPngRadioButton();
		pBtNoUseBoss->Create(IDC_BT_NOUSE, 30, 68, pAttach, this, this);

		UIPngRadioButton* pBtUseBoss = new UIPngRadioButton();
		pBtUseBoss->Create(IDC_BT_USE, 30, 92, pAttach, this, this);
		
		VisibleWidget(FALSE);

		return TRUE;
	}

	BOOL UIFrameSet::OnClicked( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_CLOSE:
		case IDC_BT_CANCEL:
			VisibleWidget(FALSE);
			return TRUE;
		case IDC_BT_CONFIRN:
			{
				SendMessage(WM_COMMAND, WM_SAVE_KEYBOSS, NULL);
				VisibleWidget(FALSE);
			}
			return TRUE;
		}
		return FALSE;
	}

	void UIFrameSet::GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers)
	{
		wVirtualKeyCode = LOBYTE(LOWORD(CSystemParameter::GetInstance().m_wBossHotKey));
		wModifiers = HIBYTE(LOWORD(CSystemParameter::GetInstance().m_wBossHotKey));
	}

	CString UIFrameSet::GetKeyName(UINT vk, BOOL fExtended)
	{
		LONG lScan = MapVirtualKey(vk, 0) << 16;

		if (fExtended)
			lScan |= 0x01000000L;

		CString str;
		int nBufferLen = 64;
		int nLen;
		do
		{
			nBufferLen *= 2;
			LPTSTR psz = str.GetBufferSetLength(nBufferLen);
			nLen = ::GetKeyNameText(lScan, psz, nBufferLen + 1);
			str.ReleaseBuffer(nLen);
		}
		while (nLen == nBufferLen);
		return str;
	}

	static const TCHAR szPlus[] = _T(" + ");
	CString UIFrameSet::GetHotKeyName()
	{
		CString strKeyName;
		WORD wCode;
		WORD wModifiers;

		GetHotKey(wCode, wModifiers);
		if (wCode != 0 || wModifiers != 0)
		{
			if (wModifiers & HOTKEYF_CONTROL)
			{
				strKeyName += GetKeyName(VK_CONTROL, FALSE);
				strKeyName += szPlus;
			}

			if (wModifiers & HOTKEYF_SHIFT)
			{
				strKeyName += GetKeyName(VK_SHIFT, FALSE);
				strKeyName += szPlus;
			}

			if (wModifiers & HOTKEYF_ALT)
			{
				strKeyName += GetKeyName(VK_MENU, FALSE);
				strKeyName += szPlus;
			}

			strKeyName += GetKeyName(wCode, wModifiers & HOTKEYF_EXT);
		}
		return strKeyName;
	}

	BOOL UIFrameSet::Draw( CDC* pDC )
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_ImageBack.DrawImage(pDC, cPt.x, cPt.y);

		//设置老板键
		CString strKey = GetHotKeyName();
		CRect rcAccounts;
		rcAccounts.SetRect(m_rect.left + 130, m_rect.top + 90, m_rect.left + 235, m_rect.top + 106);
		pDC->DrawText(strKey, &rcAccounts, DT_SINGLELINE|DT_LEFT|DT_END_ELLIPSIS);

		return UIWidget::Draw(pDC);
	}

	BOOL UIFrameSet::OnLeftDown( UIWidget* pWidget, const CPoint& cPt )
	{
		switch(pWidget->GetID())
		{
		case IDC_BT_NOUSE:
			{
				UIPngRadioButton* pRatioBt = (UIPngRadioButton*)Search(IDC_BT_USE);
				if (pRatioBt)
				{
					pRatioBt->SetCheck(FALSE);
				}
				SendMessage(WM_COMMAND, WM_START_KEYBOSS, 0);
			}
			return TRUE;
		case  IDC_BT_USE:
			{
				UIPngRadioButton* pRatioBt = (UIPngRadioButton*)Search(IDC_BT_NOUSE);
				if (pRatioBt)
				{
					pRatioBt->SetCheck(FALSE);
				}
				//向父窗口发送
				SendMessage(WM_COMMAND, WM_START_KEYBOSS, 1);
			}
			return TRUE;
		}

		return TRUE;
	}

	void UIFrameSet::VisibleWidget( bool bVisible )
	{
		UIPngRadioButton* pRatioUseBt = (UIPngRadioButton*)Search(IDC_BT_USE);
		UIPngRadioButton* pRatioNoUseBt = (UIPngRadioButton*)Search(IDC_BT_NOUSE);
		if (CSystemParameter::GetInstance().m_bUseBoss)
		{
			pRatioUseBt->SetCheck(TRUE);
			pRatioNoUseBt->SetCheck(FALSE);
			SendMessage(WM_COMMAND, WM_START_KEYBOSS, 1);
		}
		else
		{
			pRatioUseBt->SetCheck(FALSE);
			pRatioNoUseBt->SetCheck(TRUE);	
			SendMessage(WM_COMMAND, WM_START_KEYBOSS, 0);
		}
		UIWidget::VisibleWidget(bVisible);
	}

}

