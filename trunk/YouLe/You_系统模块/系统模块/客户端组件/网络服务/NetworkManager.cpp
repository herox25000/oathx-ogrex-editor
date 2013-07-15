#include "StdAfx.h"
#include "TCPSocket.h"
#include "NetworkManager.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CNetworkManager::CNetworkManager()
{
}

//析构函数
CNetworkManager::~CNetworkManager()
{
}

//接口查询
VOID * __cdecl CNetworkManager::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(INetworkManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(INetworkManager,Guid,dwQueryVer);
	return NULL;
}

//枚举代理
bool __cdecl CNetworkManager::EnumProxyServerType(WORD wIndex, tagProxyTypeDescribe & ProxyTypeDescribe)
{
	//变量定义
	enProxyServerType ProxyServerType=(enProxyServerType)wIndex;

	//信息填充
	switch (ProxyServerType)
	{
	case ProxyType_None:		//不使用代理
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("不使用代理"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Http:		//HTTP 代理
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("HTTP 代理"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Socks4:		//SOCKS 4 代理
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("SOCKS 4 代理"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	case ProxyType_Socks5:		//SOCKS 5 代理
		{
			ProxyTypeDescribe.ProxyServerType=ProxyServerType;
			lstrcpyn(ProxyTypeDescribe.szDescribe,TEXT("SOCKS 5 代理"),CountArray(ProxyTypeDescribe.szDescribe));
			return true;
		}
	}

	return false;
}

//代理测试
DWORD __cdecl CNetworkManager::ProxyServerTesting(enProxyServerType ProxyServerType, const tagProxyServerInfo & ProxyServerInfo)
{
	//效验参数
	ASSERT(ProxyServerType!=ProxyType_None);
	if (ProxyServerType==ProxyType_None) return CONNECT_EXCEPTION;

	//代理设置
	CTCPSocket TCPSocket;
	if (TCPSocket.SetProxyServerInfo(ProxyServerType,ProxyServerInfo)==false) return CONNECT_EXCEPTION;

	//代理测试
	return TCPSocket.ProxyServerTesting();
}

//////////////////////////////////////////////////////////////////////////

//输出管理
CNetworkManager g_NetworkManager;

//组件创建函数
extern "C" __declspec(dllexport) VOID * __cdecl CreateNetworkManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	return g_NetworkManager.QueryInterface(Guid,dwInterfaceVer);
}

//////////////////////////////////////////////////////////////////////////
