#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "PlatformSocket.h"
#include "UIFrameSheet.h"

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
	YouLe::UIFrameSheet				m_FrameSheet;
public:
	//加载图片资源
	void LoadImages();

public:
	//资源句柄
	HINSTANCE GetResInstanceHandle();
	//获取资源
	tagPlatformFrameImageNew GetPlatformRes();

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
	//IPC 消息
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT * pCopyDataStruct);
public:
	void SaveBossKey(int nCtrlKey, int nHelpKey);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


