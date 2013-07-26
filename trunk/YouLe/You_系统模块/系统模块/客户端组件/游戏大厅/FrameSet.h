#pragma once

#include "GdipButton.h"
#include "DlgLogon.h"


class KeyManage  
{
public:
	KeyManage();
	virtual ~KeyManage();

public:
	BOOL GetKeyAllState(string &str);
	int GetKeyState(UINT vKey);
	void PreTranslateKey();
	CString GetKeyName(UINT vk, BOOL fExtended);

protected:
	BYTE m_key[256];
};

// CFrameSet 对话框
class CFrameSet : public CDialog
{
	DECLARE_DYNAMIC(CFrameSet)

public:
	CFrameSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFrameSet();

// 对话框数据
	enum { IDD = IDD_FRAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//图片资源
protected:
	CPngImage			m_ImageBack;			//背景图

	//按钮控件
protected:
	CGdipButton				m_btClose;
	CGdipButton				m_btConfirn;
	CGdipButton				m_btCancel;

	CControlCheckButton		m_btNotUse;
	CControlCheckButton		m_btUserQuick;

protected:
	std::string					m_strCtrl;
	std::string					m_strKey;
	KeyManage					m_keys;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
