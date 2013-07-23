#pragma once

//�������״̬
enum enServiceStatus
{
	ServiceStatus_Null,					//û��״̬
	ServiceStatus_Connecting,			//����״̬
	ServiceStatus_EfficacyUser,			//Ч���û�
	ServiceStatus_RecvConfigInfo,		//��������
	ServiceStatus_RecvRoomInfo,			//������Ϣ
	ServiceStatus_Serviceing,			//����״̬
	ServiceStatus_NetShutDown,			//�����ж�
};

class CGameRoomSocket : public ITCPSocketSink ,public IChannelMessageSink
{
public:
	CGameRoomSocket(void);
	~CGameRoomSocket(void);
	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�����¼�
public:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

	//�ŵ��ӿ�
public:
	//�ŵ����ݴ���
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

public:
	bool InitGameRoom();
	//���ӵ���Ϸ������
	bool ConnectToGameServer(LPCTSTR ServerIP,WORD wPort);


	//��������
protected:
	//���͵�¼����
	bool SendLogonPacket();

	//�Զ��庯��
public:
	//��ʾ��Ϣ
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);
	//������Ϣ
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);

	//����
public:
	CTCPSocketHelper		m_ClientSocket;						//��������
	CIPCRecvCopyData		m_IPCRecvCopyData;					//�ŵ����
	enServiceStatus			m_ServiceStatus;					//����״̬

	//������Ϣ
protected:
	HWND							m_hWndChannel;						//�ŵ�����
	HANDLE							m_hShareMemory;						//�����ڴ�
	TCHAR							m_szShareName[64];					//��������
	tagShareMemory *				m_pShareMemory;						//�����ڴ�
	PROCESS_INFORMATION				m_GameProcessInfo;					//������Ϣ
};
