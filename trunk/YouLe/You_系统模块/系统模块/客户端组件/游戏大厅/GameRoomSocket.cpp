#include "StdAfx.h"
#include ".\gameroomsocket.h"

CGameRoomSocket::CGameRoomSocket(void)
{
}

CGameRoomSocket::~CGameRoomSocket(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CGameRoomSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE(IChannelMessageSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//�����¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	return true;
}
//�ر��¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	return true;
}
//��ȡ�¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	return true;
}
//�ŵ����ݴ���
bool __cdecl CGameRoomSocket::OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	return true;
}

bool CGameRoomSocket::InitGameRoom()
{
	//�������
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false) return false;
	if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) return false;
	if (m_IPCRecvCopyData.SetChannelMessageSink(pIUnknownEx)==false) return false;
	return true;
}


//���ӵ���Ϸ������
bool CGameRoomSocket::ConnectToGameServer(LPCTSTR ServerIP,WORD wPort)
{
	m_ServiceStatus=ServiceStatus_Connecting;
	return (m_ClientSocket->Connect(ServerIP,wPort)==CONNECT_SUCCESS);
}

//��ʾ��Ϣ
int CGameRoomSocket::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	int nResult=ShowInformationEx(pszMessage,0,nType,"��Ϸ����");
	return nResult;
}

//������Ϣ
void CGameRoomSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}