#include "StdAfx.h"
#include ".\udpsocket.h"

CUDPSocket::CUDPSocket(void)
{
	//WSADATA wsaData;
	//WSAStartup(MAKEWORD(2,2),&wsaData);
	//InitializeCriticalSection(&m_CriticalSec);
}

CUDPSocket::~CUDPSocket(void)
{
	try
	{
		Disconnect();
		//WSACleanup();
		//DeleteCriticalSection(&m_CriticalSec);
	}
	catch(...)
	{
		int ii=GetLastError();
	}
}

bool CUDPSocket::CreateSocket()
{
	if(m_Socket!=INVALID_SOCKET)
	{
		Disconnect();
	}
	m_Socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(m_Socket==INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool CUDPSocket::Bind(UINT nPort,const char* sServerIP)
{
	if(m_Socket==INVALID_SOCKET)
	{
		return false;
	}
	sockaddr_in localAddr;
	memset(&localAddr,0,sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(nPort);
	localAddr.sin_addr.S_un.S_addr = inet_addr(sServerIP);
	//localAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	//localAddr.sin_addr.s_addr =htonl(INADDR_ANY);
	if(bind(m_Socket,(sockaddr *)&localAddr, sizeof(localAddr)) == -1)
	{
		int iErr=GetLastError();
		return false;
	}
	return true;
}

int CUDPSocket::SetTimeOut(int iTimeOut)
{
	int nRet=setsockopt(m_Socket,SOL_SOCKET,SO_RCVTIMEO,(char*)&iTimeOut,sizeof(iTimeOut));
	return nRet;
}

void CUDPSocket::Disconnect()
{
    Shutdown();
    closesocket(m_Socket);
    m_Socket = INVALID_SOCKET;
}

void CUDPSocket::Shutdown()
{
    shutdown(m_Socket,2);
}

int CUDPSocket::SendTo(void* pBuffer,int iLen,UINT nHostPort, const char* lpszHostAddress)
{
	int iReturn=0;
	int nRet=-1;
	//EnterCriticalSection(&m_CriticalSec);
	if(m_Socket == INVALID_SOCKET)
	{iReturn=1;}
	else
	{
		sockaddr_in RemoteAddr;
		memset(&RemoteAddr,0,sizeof(RemoteAddr));

		RemoteAddr.sin_family = AF_INET;
		RemoteAddr.sin_addr.s_addr = inet_addr(lpszHostAddress);
		RemoteAddr.sin_port = htons((u_short)nHostPort);

		nRet=sendto(m_Socket,(const char*)pBuffer,iLen,0,(const sockaddr*)&RemoteAddr,sizeof(RemoteAddr));
		if(nRet==SOCKET_ERROR)
		{

			iReturn=2;
		}
	}
   //LeaveCriticalSection(&m_CriticalSec);
   return nRet;
}
int CUDPSocket::RecvFrom(void* pBuffer,int iLen,CString& rSocketAddress,UINT& rSocketPort)
{
	int iReturn=0;
	int nRet=-1;
	//EnterCriticalSection(&m_CriticalSec);
	if(m_Socket == INVALID_SOCKET)
	{iReturn=-1;}
	else
	{
		sockaddr_in RemoteAddr;
		memset((void*)&RemoteAddr,0,sizeof(RemoteAddr));
		int sinlen = sizeof(RemoteAddr);
		nRet=recvfrom(m_Socket,(char *)pBuffer,iLen,0,(sockaddr*)&RemoteAddr,&sinlen);
		if(nRet==SOCKET_ERROR)
		{iReturn=-1;}
		else
		{
			rSocketPort = ntohs(RemoteAddr.sin_port);
			rSocketAddress = inet_ntoa(RemoteAddr.sin_addr);
		}
	}
	//LeaveCriticalSection(&m_CriticalSec);
	return nRet;
}