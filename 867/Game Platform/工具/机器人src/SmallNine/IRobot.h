#pragma once

#include "UserManager.h"

//状态信息
struct tagAstatInfo
{
	ADAPTER_STATUS			AdapterStatus;						//网卡状态
	NAME_BUFFER				NameBuff[16];						//名字缓冲
};

class IRobot : ITCPSocketSink
{
public:
	IRobot(DWORD dwUserID);
	virtual ~IRobot(void);

	// 获取用户ID
	virtual	DWORD			GetUserID() const;
	virtual	WORD			GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	virtual	void			GetClientSerial(tagClientSerial& ClientSerial);

	virtual BOOL			Start(const CString& szIPAdress, WORD wPort, const CString& szPwd);
	virtual	BOOL			Update(float fElapsed);
	virtual void			Stop();
	virtual	void			ShowMessageBox(const CString& szMessage);
	virtual	void			SitDown();
	virtual void			AddGameUser(SUserInfo* pUserInfo);
	virtual	void			SetUserStatus(DWORD dwUserID, BYTE cbUserStatus);
	virtual	void			ResetGame();
	virtual	BOOL			GetSitState() const;
	virtual bool			SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData=NULL, WORD wDataSize=0);
public:
	//释放对象
	virtual void	__cdecl Release()
	{
		delete this;
	}
	//接口查询
	virtual void*	__cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer)
	{
		QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
		QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
		return NULL;
	}

	//连接事件
	virtual bool	__cdecl	OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool	__cdecl	OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool	__cdecl	OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID* pBuffer, WORD wDataSize);

public:
	//登录消息
	virtual bool			OnSocketMainLogon(CMD_Command Command, void* pBuffer, WORD wDataSize);
	//用户消息
	virtual bool			OnSocketMainUser(CMD_Command Command, void* pBuffer, WORD wDataSize);
	//游戏消息
	virtual bool			OnSocketMainGameFrame(CMD_Command Command, void* pBuffer, WORD wDataSize);

	//主通信
	virtual bool			OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//游戏状态
	virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize);
	//游戏消息
	virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0);
	virtual bool			OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);
protected:
	DWORD					m_dwUserID;
	CString					m_szPwd;
	CTCPSocketHelper		m_ClientSocket;
	SUserInfo*				m_pAppUser;
	UserManager*			m_pRoomManager;
	UserManager*			m_pGameManager;
	BOOL					m_bSitState;
	BYTE					m_bGameStatus;
};

// 机器人创建工厂
class IRobotFactory
{
public:
	IRobotFactory(const CString& szName)
		: m_typeName(szName)
	{

	}

	virtual ~IRobotFactory()
	{

	}

public:
	virtual	IRobot*			Create(DWORD dwUserID) = 0;

	virtual	void			SetTypeName(const CString& szName)
	{
		m_typeName = szName;
	}
	virtual CString			GetTypeName() const
	{
		return m_typeName;
	}
protected:
	CString					m_typeName;
};
