#include "StdAfx.h"
#include "logonframsheet.h"

namespace YouLe
{
		// ���캯��
	UILogonFramSheet::UILogonFramSheet()
	{
	}
		// ��������
	UILogonFramSheet::~UILogonFramSheet()
	{

	}

		// ��������
	BOOL UILogonFramSheet::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//������Դ
		tagPlatformFrameImageNew & FrameViewImage = CGlobalUnits::GetSingleton()->m_PlatformFrameImage;
		HINSTANCE hInstance = CGlobalUnits::GetSingleton()->m_PlatformResourceModule->GetResInstance();
		
		const INT idList[] = {
			WM_BT_CLOSE, WM_BT_LOGON, WM_BT_REGISTER, WM_BT_WEBHOME,WM_BT_CHONGZHI,WM_BT_BANBEN
		};

		UIPngButton* pBtColse = new UIPngButton;
		pBtColse->Create(WM_BT_CLOSE,490,5,pAttach,this,hInstance,FrameViewImage.pszBtQuit,5,this);

		UIPngButton* pBtLogon = new UIPngButton;
		pBtLogon->Create(WM_BT_LOGON,400,135,pAttach,this,hInstance,FrameViewImage.pszBtLogin,5,this);

		UIPngButton* pBtRegister = new UIPngButton;
		pBtRegister->Create(WM_BT_WEBHOME,175,75,pAttach,this,hInstance,FrameViewImage.pszBtWebHome,5,this);

		UIPngButton* pBtWebHome = new UIPngButton;
		pBtWebHome->Create(WM_BT_REGISTER,260,75,pAttach,this,hInstance,FrameViewImage.pszBtRegister,5,this);

		UIPngButton* pBtChongzhi = new UIPngButton;
		pBtChongzhi->Create(WM_BT_CHONGZHI,350,75,pAttach,this,hInstance,FrameViewImage.pszBtChongzhi,5,this);

		UIPngButton* pBtBanben = new UIPngButton;
		pBtBanben->Create(WM_BT_BANBEN,440,75,pAttach,this,hInstance,FrameViewImage.pszBtVersion,5,this);

		UIPngButton* pBtOther1 = new UIPngButton;
		pBtOther1->Create(WM_BT_KEYBOARD_MIN,414,312,pAttach,this,hInstance,FrameViewImage.pszBtNormalKey[0],3,this);
		
		UIPngButton* pBtOther2 = new UIPngButton;
		pBtOther2->Create(WM_BT_KEYBOARD_MIN+1,414,349,pAttach,this,hInstance,FrameViewImage.pszBtNormalKey[1],3,this);

		//���������
		UINT windowsID = 0;
		int i=0;
		for (i=0;i<10;i++)
		{
			windowsID = WM_BT_KEYBOARD_MIN+2+i; 
			UIPngButton* pBtNumber = new UIPngButton;
			pBtNumber->Create(windowsID,30+(46+2)*i, 275,pAttach,this,hInstance,FrameViewImage.pszBtNormalKey[i+2],3,this);
		}
		for(i=0;i<52;i++)
		{
			windowsID = WM_BT_KEYBOARD_MIN+12+i; 
			m_pBtAlphabet[i] = new UIPngButton;
			int index = i%26;
			LPCTSTR resName = NULL;
			if(i<26)
				resName = FrameViewImage.pszBtLowKey[index];
			else
				resName = FrameViewImage.pszBtUpperKey[index];

			if(index<8)
				m_pBtAlphabet[i]->Create(windowsID,30+(46+2)*index,312,pAttach,this,hInstance,resName,3,this);
			else if(index<16)
				m_pBtAlphabet[i]->Create(windowsID,30+(46+2)*(index-8),349,pAttach,this,hInstance,resName,3,this);
			else
				m_pBtAlphabet[i]->Create(windowsID,30+(46+2)*(index-16),387,pAttach,this,hInstance,resName,3,this);
			if(i>=26)
				m_pBtAlphabet[i]->VisibleWidget(false);
		}

		return TRUE;
	}

	// ��Ӧҳ�ؼ�
	BOOL UILogonFramSheet::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		SendMessage(WM_COMMAND, WPARAM(pWidget->GetID()), NULL);
		return TRUE;
	}
}