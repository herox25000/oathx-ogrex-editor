#pragma once
#include "ServerListManager.h"
#include "UserManager.h"

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

//�������
#define	SR_CREATE_ERROR				0									//��������
#define	SR_CREATE_SUCCESS			1									//�����ɹ�
#define	SR_ALREADY_EXIST			2									//�Ѿ�����

class CGameRoomManager;
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

	//����������
protected:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//״̬��Ϣ
	bool OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool OnSocketMainServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//����������
protected:
	//�û�����
	bool OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�״̬
	bool OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�Ȩ��
	bool OnSocketSubRight(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ա�ȼ�
	bool OnSocketSubMemberOrder(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//����ʧ��
	bool OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubChat(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�˽��
	bool OnSocketSubWisper(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�������
	bool OnSocketSubUserInvite(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//������������
public:
	//���ӷ�����
	bool ConnectGameServer();
	//������Ϣ
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//���͵�¼����
	bool SendLogonPacket();
	//������������
	bool SendStandUpPacket();
	//����ǿ������
	bool SendLeftGamePacket();
	//�����Թ�����
	bool SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//������������
	bool SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//������������
	bool SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor);
	//IPC �¼�����
protected:
	//IPC �ں�����
	bool OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//IPC ��������
	bool OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//IPC ����
protected:
	//������Ϸ��Ϣ
	bool IPCSendGameInfo(CIPCSendCopyData * pSendCopyData);
	//�����û���Ϣ
	bool IPCSendTableUsers(CIPCSendCopyData * pSendCopyData);
	//�����û�
	bool SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData);
	//������Ϣ
	bool SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

protected:
	//������Ϸ
	int StartGameClient();
	//�ر���Ϸ
	void CloseGameClient();

	//�Զ��庯��
public:
	bool InitGameRoom(CListServer * pListServer,CGameRoomManager* pMgr,CWnd* pPointer);
	//������Ϣ
	tagGameKind * __cdecl GetKindInfo();
	//��ʾ��Ϣ
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//���ݻ���
protected:
	WORD							m_wPacketTableID;					//����λ��
	WORD							m_wPacketChairID;					//����λ��
	CDataQueue						m_PacketDataStorage;				//���ݻ���

	//��������
protected:
	WORD							m_wKindID;							//���� I D
	WORD							m_wTableCount;						//������Ŀ
	WORD							m_wChairCount;						//������Ŀ
	WORD							m_wGameGenre;						//��Ϸ����
	DWORD							m_dwVideoAddr;						//��Ƶ��ַ
	BYTE							m_cbHideUserInfo;					//������Ϣ

	//����
public:
	CGameRoomManager*				m_pGameRoomMgr;						//������ָ��
	CWnd*							m_pWnd;								//������ָ��
	CListServer	*					m_pListServer;						//������Ϣ
	CTCPSocketHelper				m_ClientSocket;						//��������
	CIPCRecvCopyData				m_IPCRecvCopyData;					//�ŵ����
	enServiceStatus					m_ServiceStatus;					//����״̬
	IUserItem *						m_pMeUserItem;						//�Լ���Ϣ
	CClientUserManager				m_ClientUserManager;				//�û�����

	//������Ϣ
protected:
	HWND							m_hWndChannel;						//�ŵ�����
	HANDLE							m_hShareMemory;						//�����ڴ�
	TCHAR							m_szShareName[64];					//��������
	tagShareMemory *				m_pShareMemory;						//�����ڴ�
	PROCESS_INFORMATION				m_GameProcessInfo;					//������Ϣ

	//��������
protected:
	WORD							m_wReqTableID;						//��������
	WORD							m_wReqChairID;						//����λ��

};

