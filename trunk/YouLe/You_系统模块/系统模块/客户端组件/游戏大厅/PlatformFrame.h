#pragma once

#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GamePage.h"


class CPlatformFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CGamePlazaDlg*					m_pGamePlazaDlg;
	CDlgLogon						m_DlgLogon;							//登录对话框

	//资源
protected:
	CPngImage						m_ImageHead;
	CPngImage						m_ImageBack;
	CPngImage						m_ImageUserInfo;
	CPngImage						m_ImageGamePublic;

	//控件按钮
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;

	CGdipButton						m_btGame;
	CGdipButton						m_btMatch;
	CGdipButton						m_btProperty;
	CGdipButton						m_btPrize;
	CGdipButton						m_btRecharge;
	
	CGamePage						m_GamePage;
public:
	//加载按钮
	void LoadButtons();
	//加载图片资源
	void LoadImages();
	//按钮背景绘制
	void SetButtonBackGrounds(CDC *pDC);
public:
	//登录消息
	virtual bool __cdecl SendLogonMessage();
	//连接消息
	virtual bool __cdecl SendConnectMessage();

public:
	virtual BOOL					RectifyResource(int nWidth, int nHeight);
	virtual void					SetFrameSize(int nWidth, int nHeight);

//重载函数
protected:
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:	
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//关闭消息
	VOID OnClose();
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//登录
	afx_msg void OnCommandLogon();
	//连接服务器
	afx_msg void OnCommandConnect();
	//取消连接
	afx_msg void OnCommandCancelConnect();

protected:
	DECLARE_MESSAGE_MAP()
};


