#pragma once
#include "UIWidget.h"
#include "UIPngButton.h"

#define		WM_BT_CLOSE			100
#define		WM_BT_LOGON			101
#define		WM_BT_REGISTER		102
#define		WM_BT_WEBHOME		103
#define		WM_BT_CHONGZHI		104
#define		WM_BT_BANBEN		105

//�������
#define		WM_BT_KEYBOARD_MIN	110
#define		WM_BT_KEYBOARD_MAX	WM_BT_KEYBOARD_MIN+64

namespace YouLe
{
	// UI ������
	class UILogonFramSheet : public UIWidget, public UIProcess
	{
	public:
		// ���캯��
		UILogonFramSheet();
		// ��������
		virtual ~UILogonFramSheet();
		// ��������
		virtual BOOL Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		UIPngButton*	m_pBtAlphabet[52];
	};

}

