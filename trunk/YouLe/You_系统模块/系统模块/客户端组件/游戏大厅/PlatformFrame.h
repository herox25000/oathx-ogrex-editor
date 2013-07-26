#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GameZonePage.h"
#include "GlobalUnits.h"
#include "FrameSet.h"
#include "PlatformSocket.h"
#include "DlgEnquire.h"

class CPlatformSocket;
class CPlatformFrame : public CFrameWnd 
{
	friend class CPlatformSocket;
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CPlatformSocket					m_PlatformSocket;
	CGamePlazaDlg*					m_pGamePlazaDlg;
	CDlgLogon						m_DlgLogon;				//登录对话框
	CFrameSet						m_DlgFrameSet;			//打开大厅设置

	//资源
protected:
	CPngImage						m_ImageHead;
	CPngImage						m_ImageBack;
	CPngImage						m_ImageUserInfo;
	CPngImage						m_ImageGamePublic;

	CPngImage						m_UserHead;

	//控件按钮
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;
	CGdipButton						m_LobbySet;

	CGdipButton						m_btGame;
	CGdipButton						m_btMatch;
	CGdipButton						m_btProperty;
	CGdipButton						m_btPrize;
	CGdipButton						m_btRecharge;
	CGdipButton						m_btReflash;
	CGdipButton						m_btUserInfoSet;
	CGdipButton						m_btReturn;

	CGdipButton						m_btUserBag;
	CGdipButton						m_btSquare;
	CGdipButton						m_btTill;
	CGdipButton						m_btIm;
	
protected:
	CGameZonePage					m_ZonePage;

public:
	//加载按钮
	void LoadButtons();
	//加载图片资源
	void LoadImages();
	//按钮背景绘制
	void SetButtonBackGrounds(CDC *pDC);
	//绘制角色信息
	void DrawUserInfo(CDC *pDC);

	//重载函数
public:
	virtual BOOL RectifyResource(int nWidth, int nHeight);
	virtual void SetFrameSize(int nWidth, int nHeight);
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);	
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
	//打开大厅设置
	afx_msg void OnOpenFrameSet();
	//处理关闭大厅
	afx_msg void OnClosePlatForm();
	afx_msg void OnTabGame();
	afx_msg void OnTabCard();
	afx_msg void OnTabMahj();
	afx_msg void OnTabLeis();
public:
	void SaveBossKey(int nCtrlKey, int nHelpKey);

protected:
	DECLARE_MESSAGE_MAP()
};


