#pragma once
#include "DlgLogon.h"
class CPlatformSocket :public ITCPSocketSink
{
public:
	CPlatformSocket(void);
	~CPlatformSocket(void);
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
	//连接到服务器
	void ConnectToServer(LPCTSTR ServerIP,WORD wPort);
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
	void  SetPlatFormPointer(CWnd* pPointer)	{m_pPlatformFrame = pPointer;}
	void  SetDlgLogonPointer(CDlgLogon* pPointer) {m_pDlgLogon = pPointer;}
public:
	CTCPSocketHelper				m_ClientSocket;						//网络连接
	CWnd*							m_pPlatformFrame;
	CDlgLogon*						m_pDlgLogon;
	bool							m_bLogonPlaza;
	
};
