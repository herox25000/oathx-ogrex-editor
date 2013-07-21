#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GamePage.h"
#include "GlobalUnits.h"

class CPlatformFrame : public CFrameWnd ,public ITCPSocketSink
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

public:
	//释放对象
	virtual void __cdecl Release() { delete this; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//网络事件
public:
	//连接事件
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);
public:
	//发送信息
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//显示消息
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);
	
	//响应服务器消息函数
public:
	//登录消息
	bool OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize);
	//列表消息
	bool OnSocketMainServerList(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//系统消息
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户消息
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);


public:
	CTCPSocketHelper				m_ClientSocket;						//网络连接
	bool							m_bLogonPlaza;		//是否已经登陆
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
	CGdipButton						m_LobbySet;

	CGdipButton						m_btGame;
	CGdipButton						m_btMatch;
	CGdipButton						m_btProperty;
	CGdipButton						m_btPrize;
	CGdipButton						m_btRecharge;
	CGdipButton						m_btReflash;
	CGdipButton						m_btUserInfoSet;
	CGdipButton						m_btReturn;

	CGamePage						m_GamePage;
public:
	//加载按钮
	void LoadButtons();
	//加载图片资源
	void LoadImages();
	//按钮背景绘制
	void SetButtonBackGrounds(CDC *pDC);


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

protected:
	DECLARE_MESSAGE_MAP()
};


