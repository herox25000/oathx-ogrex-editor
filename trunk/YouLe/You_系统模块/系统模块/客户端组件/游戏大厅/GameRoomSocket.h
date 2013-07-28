#pragma once
#include "ServerListManager.h"
#include "UserManager.h"

//房间服务状态
enum enServiceStatus
{
	ServiceStatus_Null,					//没有状态
	ServiceStatus_Connecting,			//连接状态
	ServiceStatus_EfficacyUser,			//效验用户
	ServiceStatus_RecvConfigInfo,		//接收配置
	ServiceStatus_RecvRoomInfo,			//接收信息
	ServiceStatus_Serviceing,			//服务状态
	ServiceStatus_NetShutDown,			//网络中断
};

//启动结果
#define	SR_CREATE_ERROR				0									//启动错误
#define	SR_CREATE_SUCCESS			1									//启动成功
#define	SR_ALREADY_EXIST			2									//已经存在

class CGameRoomManager;
class CGameRoomSocket : public ITCPSocketSink ,public IChannelMessageSink
{
public:
	CGameRoomSocket(void);
	~CGameRoomSocket(void);
	//基础接口
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

	//信道接口
public:
	//信道数据处理
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//网络主命令
protected:
	//登录消息
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户消息
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//配置消息
	bool OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//状态消息
	bool OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//系统消息
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//房间消息
	bool OnSocketMainServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//网络子命令
protected:
	//用户进入
	bool OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户状态
	bool OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户分数
	bool OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户权限
	bool OnSocketSubRight(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//会员等级
	bool OnSocketSubMemberOrder(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//坐下失败
	bool OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户聊天
	bool OnSocketSubChat(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户私语
	bool OnSocketSubWisper(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//邀请玩家
	bool OnSocketSubUserInvite(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//发送网络命令
public:
	//连接服务器
	bool ConnectGameServer();
	//发送信息
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//发送登录命令
	bool SendLogonPacket();
	//发送起来命令
	bool SendStandUpPacket();
	//发送强退命令
	bool SendLeftGamePacket();
	//发送旁观命令
	bool SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//发送坐下命令
	bool SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//发送聊天命令
	bool SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor);
	//IPC 事件处理
protected:
	//IPC 内核命令
	bool OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//IPC 发包命令
	bool OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//IPC 处理
protected:
	//发送游戏信息
	bool IPCSendGameInfo(CIPCSendCopyData * pSendCopyData);
	//发送用户信息
	bool IPCSendTableUsers(CIPCSendCopyData * pSendCopyData);
	//发送用户
	bool SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData);
	//发送消息
	bool SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

protected:
	//启动游戏
	int StartGameClient();
	//关闭游戏
	void CloseGameClient();

	//自定义函数
public:
	bool InitGameRoom(CListServer * pListServer,CGameRoomManager* pMgr,CWnd* pPointer);
	//类型信息
	tagGameKind * __cdecl GetKindInfo();
	//显示消息
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//数据缓冲
protected:
	WORD							m_wPacketTableID;					//缓冲位置
	WORD							m_wPacketChairID;					//缓冲位置
	CDataQueue						m_PacketDataStorage;				//数据缓冲

	//房间配置
protected:
	WORD							m_wKindID;							//类型 I D
	WORD							m_wTableCount;						//桌子数目
	WORD							m_wChairCount;						//椅子数目
	WORD							m_wGameGenre;						//游戏类型
	DWORD							m_dwVideoAddr;						//视频地址
	BYTE							m_cbHideUserInfo;					//隐藏信息

	//变量
public:
	CGameRoomManager*				m_pGameRoomMgr;						//管理类指针
	CWnd*							m_pWnd;								//房间框架指针
	CListServer	*					m_pListServer;						//房间信息
	CTCPSocketHelper				m_ClientSocket;						//网络连接
	CIPCRecvCopyData				m_IPCRecvCopyData;					//信道组件
	enServiceStatus					m_ServiceStatus;					//服务状态
	IUserItem *						m_pMeUserItem;						//自己信息
	CClientUserManager				m_ClientUserManager;				//用户管理

	//进程信息
protected:
	HWND							m_hWndChannel;						//信道窗口
	HANDLE							m_hShareMemory;						//共享内存
	TCHAR							m_szShareName[64];					//共享名字
	tagShareMemory *				m_pShareMemory;						//共享内存
	PROCESS_INFORMATION				m_GameProcessInfo;					//进程信息

	//辅助变量
protected:
	WORD							m_wReqTableID;						//请求桌子
	WORD							m_wReqChairID;						//请求位置

};

