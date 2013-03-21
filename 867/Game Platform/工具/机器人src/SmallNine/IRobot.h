#pragma once

//状态信息
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//网卡状态
	NAME_BUFFER					NameBuff[16];						//名字缓冲
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
	virtual bool	__cdecl	OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);
protected:
	DWORD					m_dwUserID;
};
