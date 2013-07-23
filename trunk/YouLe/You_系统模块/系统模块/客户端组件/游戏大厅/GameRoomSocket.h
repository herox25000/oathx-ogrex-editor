#pragma once

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

public:
	bool InitGameRoom();
	//连接到游戏服务器
	bool ConnectToGameServer(LPCTSTR ServerIP,WORD wPort);


	//网络命令
protected:
	//发送登录命令
	bool SendLogonPacket();

	//自定义函数
public:
	//显示消息
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);
	//发送信息
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);

	//变量
public:
	CTCPSocketHelper		m_ClientSocket;						//网络连接
	CIPCRecvCopyData		m_IPCRecvCopyData;					//信道组件
	enServiceStatus			m_ServiceStatus;					//服务状态

	//进程信息
protected:
	HWND							m_hWndChannel;						//信道窗口
	HANDLE							m_hShareMemory;						//共享内存
	TCHAR							m_szShareName[64];					//共享名字
	tagShareMemory *				m_pShareMemory;						//共享内存
	PROCESS_INFORMATION				m_GameProcessInfo;					//进程信息
};
