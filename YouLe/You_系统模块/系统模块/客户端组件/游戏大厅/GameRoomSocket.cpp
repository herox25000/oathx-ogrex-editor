#include "StdAfx.h"
#include ".\gameroomsocket.h"

CGameRoomSocket::CGameRoomSocket(void)
{
}

CGameRoomSocket::~CGameRoomSocket(void)
{
}

//接口查询
void * __cdecl CGameRoomSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE(IChannelMessageSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//连接事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	return true;
}
//关闭事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	return true;
}
//读取事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	return true;
}
//信道数据处理
bool __cdecl CGameRoomSocket::OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	return true;
}

bool CGameRoomSocket::InitGameRoom()
{
	//设置组件
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false) return false;
	if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) return false;
	if (m_IPCRecvCopyData.SetChannelMessageSink(pIUnknownEx)==false) return false;
	return true;
}


//连接到游戏服务器
bool CGameRoomSocket::ConnectToGameServer(LPCTSTR ServerIP,WORD wPort)
{
	m_ServiceStatus=ServiceStatus_Connecting;
	return (m_ClientSocket->Connect(ServerIP,wPort)==CONNECT_SUCCESS);
}

//显示消息
int CGameRoomSocket::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	int nResult=ShowInformationEx(pszMessage,0,nType,"游戏房间");
	return nResult;
}

//发送信息
void CGameRoomSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}