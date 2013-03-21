#pragma once

//״̬��Ϣ
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//����״̬
	NAME_BUFFER					NameBuff[16];						//���ֻ���
};

class IRobot : ITCPSocketSink
{
public:
	IRobot(DWORD dwUserID);
	virtual ~IRobot(void);

	// ��ȡ�û�ID
	virtual	DWORD			GetUserID() const;
	virtual	WORD			GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	virtual	void			GetClientSerial(tagClientSerial& ClientSerial);

public:
	//�ͷŶ���
	virtual void	__cdecl Release()
	{
		delete this;
	}
	//�ӿڲ�ѯ
	virtual void*	__cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer)
	{
		QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
		QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
		return NULL;
	}

	//�����¼�
	virtual bool	__cdecl	OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool	__cdecl	OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool	__cdecl	OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);
protected:
	DWORD					m_dwUserID;
};
