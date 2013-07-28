#pragma once
#include "UIWidget.h"
#include "UIPngButton.h"

#define		WM_BT_CLOSE			100
#define		WM_BT_LOGON			101
#define		WM_BT_REGISTER		102
#define		WM_BT_WEBHOME		103
#define		WM_BT_CHONGZHI		104
#define		WM_BT_BANBEN		105

//软件键盘
#define		WM_BT_KEYBOARD_MIN	110
#define		WM_BT_KEYBOARD_MAX	WM_BT_KEYBOARD_MIN+64

namespace YouLe
{
	// UI 根窗口
	class UILogonFramSheet : public UIWidget, public UIProcess
	{
	public:
		// 构造函数
		UILogonFramSheet();
		// 析构函数
		virtual ~UILogonFramSheet();
		// 创建窗口
		virtual BOOL Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		UIPngButton*	m_pBtAlphabet[52];
	};

}

