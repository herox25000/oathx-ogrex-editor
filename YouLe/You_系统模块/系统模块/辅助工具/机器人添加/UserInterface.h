#pragma once
#include "Stdafx.h"
#include "GameLogic.h"
#define GAME_PLAYER 3
class CUserInterface :public CClientSocketHelper,public IClientSocketSink
{
public:
	bool    bIsExitByUser;
	CUserInterface(void);
	~CUserInterface(void);
protected:
	int     DelayTime;             //当前状态结束需要的时间
	DWORD   UserID;                //用户ID
	TCHAR   szPassword[33];        //用户密码
	BYTE	UserStatus;			   //用户当前状态（自己定义）
	BYTE    GameStatus;            //用户游戏状态（游戏定义）
	BYTE    ExitGameStatus;        //用户退出游戏状态
	BYTE    TableID;			   //坐的桌子号
	BYTE    ChairID;			   //坐的位置号
	BYTE    TableOldID;			   //坐的桌子号
	BOOL    bIsInvite;
	int     m_TableNum;           //桌子总数
	int     m_ChairNum;           //椅子总数
	DWORD			dwIP;           //ip地址
	WORD			wPort;          //端口
	int          m_GameNum;         //玩的局数
	int          m_CurrentGameNum;   //现在玩的局数
	BOOL         bIsReSel;
	CGameLogic						m_GameLogic;						//游戏逻辑
public:
	void   CreateSocketInstance();

	//释放对象
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//是否有效
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CUserInterface))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//网络连接消息
	virtual bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	//网络读取消息
	virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//网络关闭消息
	virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);
	//设置用户数据
	void   SetUserStatus(BYTE mUserStatus);
	void   SetUserID(DWORD mUserID);
	void   SetUserPass(TCHAR *mUserPass);
	void   SetTable(BYTE mTable,BYTE mChair);
	void   SetDealyTime(int mDelayTime);
	void   SetConnectInfo(DWORD	mIP,WORD mPort);
	//取得用户数据
	BYTE   GetUserStatus();
	DWORD  GetUserID();
	BYTE   GetTableID();
	BYTE   GetChairID();
	//时间片减少
	bool   ConnectSever();
	//发送数据包
	void   SendLogonData();
	//发送函数
	bool SendGameData(WORD wSubCmdID);
	//发送函数
	bool SendGameData(WORD wSubCmdID, void * pData, WORD wDataSize);
	//接收游戏消息
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	virtual bool SubDelayTime();
protected:
	//发送数据包
	void   SendReqSiteData();
	void   SendReqStandUpData();
	void   SendUserReadyData();
	bool   SearchTableChair();
public:
	BOOL          bIsMannageTableInfo;  //管理桌子的用户
};