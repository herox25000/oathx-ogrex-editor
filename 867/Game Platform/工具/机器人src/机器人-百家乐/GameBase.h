#pragma once

#include "UserManager.h"
#include "TimeEngine.h"
#include "Nb30.h"

//状态信息
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//网卡状态
	NAME_BUFFER					NameBuff[32];						//名字缓冲
};

class CGameBase : public ITCPSocketSink
{
	friend class CTimerEngine;
public:
	CGameBase(DWORD dwUserID);
	virtual ~CGameBase(void);

public:
	//释放对象
	virtual void __cdecl Release() { }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

public:
	//网卡地址
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);

	//获取序列
	void GetClientSerial(tagClientSerial & ClientSerial);

	//bool SetEventService(IUnknownEx * pIUnknownEx);

	void SetTimerEngine(CTimerEngine *pTimerEngine){m_pTimerEngine = pTimerEngine;}

	bool BeginServer(CString strIP, WORD wPort, CString strPsw);

	void EndServer();

	bool IsSitOk(){return m_bSitOk;}

	void		SetSmall(){m_bSmall = true;}
protected:
	bool OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	bool SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData=NULL, WORD wDataSize=0);

	int  ShowMessageBox(CString strMsg);

	void SendChatMessage(CString strMsg);
protected:
	CTCPSocketHelper		m_ClientSocket;				//网络连接
	//IEventService			* m_pIEventService;			//事件服务
	CUserManager			m_RoomUserManager;			//房间内玩家管理
	CUserManager			m_GameUserManager;			//游戏内玩家管理
	tagUserInfo				m_MeUserInfo;				//机器人自己的信息
	BYTE					m_bGameStatus;				//游戏状态
	CString					m_strPsw;
	CTimerEngine			*m_pTimerEngine;			//定时器
	bool					m_bPlaying;					//游戏状态
	bool					m_bSitOk;					//成功坐下
	bool					m_bSmall;					//压小
protected:
	bool SitDown();
	//设置定时器
	bool SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat);
	//删除定时器
	bool KillTimer(WORD wTimerID);
	//删除定时器
	bool KillAllTimer();
	//定时器消息
	virtual void OnTimer(WORD wTimerID) = NULL;
private:
	////网络连接消息
	//bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	////网络读取消息
	//virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	////网络关闭消息
	//virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);


	//连接事件
	bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize);


	//插入玩家信息
	void InsertTableUser(tagUserInfo *pUserInfo);
	//游戏状态更新
	void OnUserStatus(DWORD dwUserID, BYTE cbUserStatus);

	//登录消息
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户消息
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//主通信
	bool OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//游戏状态
	virtual bool OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)=NULL;
	//游戏消息
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0)=NULL;
	//重置游戏
	virtual void ResetGame()=NULL;
};
