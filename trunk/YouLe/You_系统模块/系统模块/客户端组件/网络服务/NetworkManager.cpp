#include "StdAfx.h"
#include "TCPSocket.h"
#include "NetworkManager.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CNetworkManager::CNetworkManager()
{
}

//��������
CNetworkManager::~CNetworkManager()
{
}

//�ӿڲ�ѯ
VOID * __cdecl CNetworkManager::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(INetworkManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(INetworkManager,Guid,dwQueryVer);
	return NULL;
}

//ö�ٴ���
bool __cdecl CNetworkManager::EnumProxyServerType(WORD wIndex, tagProxyTypeDescribe & ProxyTypeDescribe)
{
	//��������
	enProxyServerType ProxyServerType=(enProxyServerType)wIndex;

	//��Ϣ���
	switch (ProxyServerType)
	{
	case ProxyType_None:		//��ʹ�ô���
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("��ʹ�ô���"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Http:		//HTTP ����
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("HTTP ����"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Socks4:		//SOCKS 4 ����
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("SOCKS 4 ����"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Socks5:		//SOCKS 5 ����
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("SOCKS 5 ����"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	}

	return false;
}

//�������
DWORD __cdecl CNetworkManager::ProxyServerTesting(enProxyServerType ProxyServerType, const tagProxyServerInfo & ProxyServerInfo)
{
	//Ч�����
	ASSERT(ProxyServerType!=ProxyType_None);
	if (ProxyServerType==ProxyType_None) return CONNECT_EXCEPTION;

	//��������
	CTCPSocket TCPSocket;
	if (TCPSocket.SetProxyServerInfo(ProxyServerType,ProxyServerInfo)==false) return CONNECT_EXCEPTION;

	//�������
	return TCPSocket.ProxyServerTesting();
}

//////////////////////////////////////////////////////////////////////////

//�������
CNetworkManager g_NetworkManager;

//�����������
extern "C" __declspec(dllexport) VOID * __cdecl CreateNetworkManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	return g_NetworkManager.QueryInterface(Guid,dwInterfaceVer);
}

//////////////////////////////////////////////////////////////////////////
