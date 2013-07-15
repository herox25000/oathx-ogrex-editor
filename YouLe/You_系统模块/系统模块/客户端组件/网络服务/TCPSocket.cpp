#include "Stdafx.h"
#include "TCPSocket.h"

//////////////////////////////////////////////////////////////////////////

//消息定义
#define WM_SOCKET_NOTIFY			(WM_USER+100)						//网络消息

//时间定义
#define IDI_DETEST_SOCKET			100									//网络检测

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTCPSocket, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(WM_SOCKET_NOTIFY,OnSocketNotify)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CTCPSocket::CTCPSocket()
{
	//辅助变量
	m_wSocketID=0;
	m_cbSocketStatus=SOCKET_STATUS_IDLE;

	//内核变量
	m_pITCPSocketSink=NULL;
	m_hSocket=INVALID_SOCKET;

	//代理信息
	m_ProxyServerType=ProxyType_None;
	ZeroMemory(&m_ProxyServerInfo,sizeof(m_ProxyServerInfo));

	//接收变量
	m_wRecvSize=0;
	ZeroMemory(m_cbRecvBuf,sizeof(m_cbRecvBuf));

	//缓冲变量
	m_dwBufferData=0L;
	m_dwBufferSize=0L;
	m_bNeedBuffer=false;
	m_pcbDataBuffer=NULL;

	//加密数据
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;

	//计数变量
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;

	return;
}

//析构函数
CTCPSocket::~CTCPSocket()
{
	//关闭连接
	if (m_hSocket!=INVALID_SOCKET)
	{
		closesocket(m_hSocket);
		m_hSocket=INVALID_SOCKET;
	}

	//删除缓冲
	SafeDeleteArray(m_pcbDataBuffer);

	return;
}

//接口查询
VOID * __cdecl CTCPSocket::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocket,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocket,Guid,dwQueryVer);
	return NULL;
}

//设置接口
bool __cdecl CTCPSocket::SetTCPSocketSink(IUnknownEx * pIUnknownEx)
{
	//设置接口
	if (pIUnknownEx!=NULL)
	{
		//查询接口
		ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITCPSocketSink)!=NULL);
		m_pITCPSocketSink=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITCPSocketSink);

		//成功判断
		if (m_pITCPSocketSink==NULL) return false;
	}
	else m_pITCPSocketSink=NULL;

	return true;
}

//获取接口
VOID * __cdecl CTCPSocket::GetTCPSocketSink(const IID & Guid, DWORD dwQueryVer)
{
	if (m_pITCPSocketSink==NULL) return NULL;
	return m_pITCPSocketSink->QueryInterface(Guid,dwQueryVer);
}

//代理测试
DWORD __cdecl CTCPSocket::ProxyServerTesting()
{
	//效验参数
	ASSERT(m_hSocket==INVALID_SOCKET);
	ASSERT(m_ProxyServerType!=ProxyType_None);
	ASSERT(m_cbSocketStatus==SOCKET_STATUS_IDLE);

	//效验状态
	if (m_hSocket!=INVALID_SOCKET) return CONNECT_EXCEPTION;
	if (m_ProxyServerType==ProxyType_None) return CONNECT_EXCEPTION;
	if (m_cbSocketStatus!=SOCKET_STATUS_IDLE) return CONNECT_EXCEPTION;

	//建立 SOCKET
	m_hSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (m_hSocket==INVALID_SOCKET) return CONNECT_EXCEPTION;

	//连接代理
	DWORD dwResult=ConnectProxyServer();

	//关闭连接
	closesocket(m_hSocket);
	m_hSocket=INVALID_SOCKET;

	return dwResult;
}

//设置代理
bool __cdecl CTCPSocket::SetProxyServerInfo(enProxyServerType ProxyServerType, const tagProxyServerInfo & ProxyServerInfo)
{
	switch (ProxyServerType)
	{
	case ProxyType_None:	//没有代理
		{
			//设置变量
			m_ProxyServerType=ProxyServerType;
			ZeroMemory(&m_ProxyServerInfo,sizeof(m_ProxyServerInfo));

			return true;
		}
	case ProxyType_Http:	//HTTP 代理
	case ProxyType_Socks4:	//SOKKS4 代理
	case ProxyType_Socks5:	//SOKKS5 代理
		{
			//设置变量
			m_ProxyServerType=ProxyServerType;
			m_ProxyServerInfo=ProxyServerInfo;

			return true;
		}
	default: 
		{ 
			ASSERT(FALSE); 
			return false;
		}
	}

	return false;
}

//连接操作
DWORD __cdecl CTCPSocket::Connect(DWORD dwServerIP, WORD wPort)
{
	//效验参数
	ASSERT(dwServerIP!=INADDR_NONE);
	ASSERT(m_hSocket==INVALID_SOCKET);
	ASSERT(m_cbSocketStatus==SOCKET_STATUS_IDLE);

	//设置参数
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0x12345678;
	m_dwRecvXorKey=0x12345678;
	m_dwSendTickCount=GetTickCount()/1000L;
	m_dwRecvTickCount=GetTickCount()/1000L;

	try
	{
		//建立 SOCKET
		m_hSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if (m_hSocket==INVALID_SOCKET) throw CONNECT_EXCEPTION;

		//创建窗口
		if (m_hWnd==NULL)
		{
			CRect rcSocketWnd;
			Create(NULL,NULL,WS_CHILD,rcSocketWnd,GetDesktopWindow(),100);
		}

		//变量定义
		SOCKADDR_IN SocketAddr;
		ZeroMemory(&SocketAddr,sizeof(SocketAddr));

		//设置变量
		SocketAddr.sin_family=AF_INET;
		SocketAddr.sin_port=htons(wPort);
		SocketAddr.sin_addr.S_un.S_addr=dwServerIP;

		//代理连接
		if (m_ProxyServerType!=ProxyType_None)
		{
			//连接代理
			DWORD dwResult=ConnectProxyServer();
			if (dwResult!=CONNECT_SUCCESS) throw dwResult;

			//请求连接
			switch (m_ProxyServerType)
			{
			case ProxyType_Http:	//HTTP 代理
				{
					//构造请求
					char cbDataBuffer[512];
					BYTE * pcbServerIP=(BYTE *)&dwServerIP;
					_snprintf(cbDataBuffer,CountArray(cbDataBuffer),"CONNECT %d.%d.%d.%d:%d HTTP/1.0\r\nUser-Agent: WHPlatform/0.1\r\n\r\n",
						pcbServerIP[0],pcbServerIP[1],pcbServerIP[2],pcbServerIP[3],wPort);

					//连接请求
					INT nRequestLen=(INT)strlen(cbDataBuffer);
					if (send(m_hSocket,cbDataBuffer,nRequestLen,0)!=nRequestLen) throw CONNECT_PROXY_FAILURE;

					//接收响应
					INT nRecvCount=recv(m_hSocket,cbDataBuffer,sizeof(cbDataBuffer),0);
					if (nRecvCount>0) cbDataBuffer[nRecvCount]=0;

					//结果判断
					bool bSuccess=false;
					for (INT i=0;i<nRecvCount;i++)
					{
						if ((cbDataBuffer[i]==' ')&&(cbDataBuffer[i+1]=='2')&&(cbDataBuffer[i+2]=='0')&&(cbDataBuffer[i+3]=='0'))
						{
							bSuccess=true;
							break;
						}
					}

					//结果判断
					if (bSuccess==false) throw CONNECT_PROXY_FAILURE;

					break;
				}
			case ProxyType_Socks5:	//Socks5 代理
				{
					//构造请求
					INT nOff=4;
					char cbDataBuffer[256]={5,1,0,1};

					//连接地址
					CopyMemory(cbDataBuffer+nOff,&SocketAddr.sin_addr,sizeof(SocketAddr.sin_addr));
					nOff+=sizeof(SocketAddr.sin_addr);
					
					//连接端口
					*(WORD*)(cbDataBuffer+nOff)=SocketAddr.sin_port;
					nOff+=sizeof(WORD);

					//连接请求
					if (send(m_hSocket,cbDataBuffer,nOff,0)!=nOff) throw CONNECT_PROXY_FAILURE;

					//接收响应
					INT nRecvCount=recv(m_hSocket,cbDataBuffer,4,0);
					if (nRecvCount!=4) throw CONNECT_PROXY_FAILURE;
					if (cbDataBuffer[0]!=5) throw CONNECT_PROXY_FAILURE;

					//失败判断
					if (cbDataBuffer[1]==0) return CONNECT_PROXY_FAILURE;

					//接收数据
					INT nLeftDataLen=(cbDataBuffer[3]==1)?6:cbDataBuffer[4]+2;
					if (recv(m_hSocket,cbDataBuffer,nLeftDataLen,0)!=nLeftDataLen) throw CONNECT_PROXY_FAILURE;

					break;
				}
			case ProxyType_Socks4:	//Socks4 代理
				{
					//构造请求
					INT nOff=2;
					char cbDataBuffer[256]={4,1};

					//连接端口
					*(WORD*)(cbDataBuffer+nOff)=SocketAddr.sin_port;
					nOff+=sizeof(WORD);

					//连接地址
					CopyMemory(cbDataBuffer+nOff,&SocketAddr.sin_addr,sizeof(SocketAddr.sin_addr));
					nOff+=sizeof(SocketAddr.sin_addr);

					//保留字段
					cbDataBuffer[nOff++]=0;

					//连接请求
					INT nResult=send(m_hSocket,cbDataBuffer,nOff,0);
					if (nResult!=nOff) throw CONNECT_PROXY_FAILURE;

					//接收响应
					nResult=recv(m_hSocket,cbDataBuffer,8,0);
					if (nResult!=8) throw CONNECT_PROXY_FAILURE;
					if (cbDataBuffer[0]!=0) throw CONNECT_PROXY_FAILURE;

					//失败判断
					if (cbDataBuffer[1]!=90) return CONNECT_PROXY_FAILURE;

					break;
				}
			default:		//默认处理
				{
					ASSERT(FALSE);
					throw CONNECT_PROXY_FAILURE;
				}
			}

			//连接成功
			WSASetLastError(0);

			//设置变量
			m_cbSocketStatus=SOCKET_STATUS_CONNECT;

			//发送消息
			PostMessage(WM_SOCKET_NOTIFY,0,MAKELONG(FD_CONNECT,0));

			//绑定窗口
			WSAAsyncSelect(m_hSocket,m_hWnd,WM_SOCKET_NOTIFY,FD_READ|FD_CONNECT|FD_CLOSE|FD_WRITE);
		}
		else
		{
			//绑定窗口
			WSAAsyncSelect(m_hSocket,m_hWnd,WM_SOCKET_NOTIFY,FD_READ|FD_CONNECT|FD_CLOSE|FD_WRITE);

			//发起连接
			INT nErrorCode=connect(m_hSocket,(SOCKADDR *)&SocketAddr,sizeof(SocketAddr));
			if ((nErrorCode==SOCKET_ERROR)&&(WSAGetLastError()!=WSAEWOULDBLOCK)) throw CONNECT_EXCEPTION;

			//设置变量
			m_cbSocketStatus=SOCKET_STATUS_WAIT;
		}

		return CONNECT_SUCCESS;
	}
	catch (...)
	{
		//关闭连接
		CloseSocket(SHUT_REASON_INSIDE);
	}

	return CONNECT_EXCEPTION;
}

//连接操作
DWORD __cdecl CTCPSocket::Connect(LPCTSTR szServerIP, WORD wPort)
{
	//效验数据
	ASSERT((wPort!=0)&&(szServerIP!=NULL));
	if ((szServerIP==NULL)||(wPort==0)) return false;

	//连接操作
	return Connect(TranslateAddr(szServerIP),wPort);
}

//发送函数
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID)
{
	//效验状态
	if (m_hSocket==INVALID_SOCKET) return 0L;
	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return 0L;

	//变量定义
	BYTE cbDataBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;

	//设置变量
	pHead->CommandInfo.wSubCmdID=wSubCmdID;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;

	//加密数据
	WORD wSendSize=EncryptBuffer(cbDataBuffer,sizeof(CMD_Head),sizeof(cbDataBuffer));

	//发送数据
	return SendDataBuffer(cbDataBuffer,wSendSize);
}

//发送函数
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, VOID * const pData, WORD wDataSize)
{
	//效验状态
	if (m_hSocket==INVALID_SOCKET) return false;
	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return false;

	//效验大小
	ASSERT(wDataSize<=SOCKET_PACKET);
	if (wDataSize>SOCKET_PACKET) return false;

	//变量定义
	BYTE cbDataBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;

	//设置变量
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;

	//扩展数据
	if (wDataSize>0)
	{
		ASSERT(pData!=NULL);
		CopyMemory(pHead+1,pData,wDataSize);
	}

	//加密数据
	WORD wSendSize=EncryptBuffer(cbDataBuffer,sizeof(CMD_Head)+wDataSize,sizeof(cbDataBuffer));

	//发送数据
	return SendDataBuffer(cbDataBuffer,wSendSize);
}

//关闭连接
VOID __cdecl CTCPSocket::CloseSocket()
{
	//关闭连接
	CloseSocket(SHUT_REASON_NORMAL);

	return;
}

//关闭连接
VOID CTCPSocket::CloseSocket(BYTE cbShutReason)
{
	//设置变量
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;

	//计数变量
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;

	//缓冲变量
	m_dwBufferData=0L;
	m_dwBufferSize=0L;
	m_bNeedBuffer=false;
	SafeDeleteArray(m_pcbDataBuffer);

	//状态变量
	m_cbSocketStatus=SOCKET_STATUS_IDLE;

	//关闭判断
	if (m_hSocket!=INVALID_SOCKET)
	{
		//删除时间
		KillTimer(IDI_DETEST_SOCKET);

		//注销事件
		WSAAsyncSelect(m_hSocket,m_hWnd,WM_SOCKET_NOTIFY,0);

		//关闭连接
		closesocket(m_hSocket);
		m_hSocket=INVALID_SOCKET;

		//事件通知
		if (cbShutReason!=SHUT_REASON_INSIDE)
		{
			ASSERT(m_pITCPSocketSink!=NULL);
			if (m_pITCPSocketSink!=NULL) m_pITCPSocketSink->OnEventTCPSocketShut(m_wSocketID,cbShutReason);
		}
	}

	return;
}

//缓冲数据
VOID CTCPSocket::AmortizeBuffer(VOID * pData, WORD wDataSize)
{
	//申请缓冲
	if ((m_dwBufferData+wDataSize)>m_dwBufferSize)
	{
		//变量定义
		LPBYTE pcbDataBuffer=NULL;
		LPBYTE pcbDeleteBuffer=m_pcbDataBuffer;

		//计算大小
		DWORD dwNeedSize=m_dwBufferData+wDataSize;
		DWORD dwApplySize=__max(dwNeedSize,m_dwBufferSize*2L);

		//申请缓冲
		try
		{
			pcbDataBuffer=new BYTE [dwApplySize];
		}
		catch (...)	{ }

		//失败判断
		if (pcbDataBuffer==NULL)
		{
			CloseSocket(SHUT_REASON_EXCEPTION);
			return;
		}

		//设置变量
		m_dwBufferSize=dwApplySize;
		m_pcbDataBuffer=pcbDataBuffer;
		CopyMemory(m_pcbDataBuffer,pcbDeleteBuffer,m_dwBufferData);

		//删除缓冲
		SafeDeleteArray(pcbDeleteBuffer);
	}

	//设置变量
	m_bNeedBuffer=true;
	m_dwBufferData+=wDataSize;
	CopyMemory(m_pcbDataBuffer+m_dwBufferData-wDataSize,pData,wDataSize);

	return;
}

//发送数据
DWORD CTCPSocket::SendDataBuffer(VOID * pBuffer, WORD wSendSize)
{
	//变量定义
	WORD wTotalCount=0;

	//设置变量
	m_dwSendTickCount=GetTickCount()/1000L;

	//发送数据
	while ((m_bNeedBuffer==false)&&(wTotalCount<wSendSize))
	{
		//发生数据
		INT nSendCount=send(m_hSocket,(char *)pBuffer+wTotalCount,wSendSize-wTotalCount,0);

		//错误判断
		if (nSendCount==SOCKET_ERROR)
		{
			//缓冲判断
			if (WSAGetLastError()==WSAEWOULDBLOCK)
			{
				AmortizeBuffer((LPBYTE)pBuffer+wTotalCount,wSendSize-wTotalCount);
				return wSendSize;
			}

			//关闭连接
			CloseSocket(SHUT_REASON_EXCEPTION);

			return 0L;
		}
		else
		{
			//设置变量
			wTotalCount+=nSendCount;
		}
	}

	//缓冲数据
	if (wTotalCount>wSendSize)
	{
		AmortizeBuffer((LPBYTE)pBuffer+wTotalCount,wSendSize-wTotalCount);
	}

	return wSendSize;
}

//随机映射
WORD CTCPSocket::SeedRandMap(WORD wSeed)
{
	DWORD dwHold=wSeed;
	return (WORD)((dwHold=dwHold*241103L+2533101L)>>16);
}

//映射发送数据
BYTE CTCPSocket::MapSendByte(BYTE cbData)
{
	BYTE cbMap=g_SendByteMap[(BYTE)(cbData+m_cbSendRound)];
	m_cbSendRound+=3;
	return cbMap;
}

//映射接收数据
BYTE CTCPSocket::MapRecvByte(BYTE cbData)
{
	BYTE cbMap=g_RecvByteMap[cbData]-m_cbRecvRound;
	m_cbRecvRound+=3;
	return cbMap;
}

//连接代理
DWORD CTCPSocket::ConnectProxyServer()
{
	//效验状态
	ASSERT(m_ProxyServerType!=ProxyType_None);
	if (m_ProxyServerType==ProxyType_None) return CONNECT_EXCEPTION;

	//变量定义
	SOCKADDR_IN SocketAddrProxy;
	ZeroMemory(&SocketAddrProxy,sizeof(SocketAddrProxy));

	//设置变量
	SocketAddrProxy.sin_family=AF_INET;
	SocketAddrProxy.sin_port=htons(m_ProxyServerInfo.wProxyPort);
	SocketAddrProxy.sin_addr.S_un.S_addr=TranslateAddr(m_ProxyServerInfo.szProxyServer);

	//连接代理
	INT nErrorCode=connect(m_hSocket,(sockaddr *)&SocketAddrProxy,sizeof(SocketAddrProxy));
	if (nErrorCode==SOCKET_ERROR) return CONNECT_PROXY_FAILURE;

	//发送数据
	if (m_ProxyServerType==ProxyType_Socks5)
	{
		//变量定义
		INT nOff=2;
		char cbDataBuffer[256]={5,1};

		//发送数据
		cbDataBuffer[nOff++]=(m_ProxyServerInfo.szUserName[0]==0)?0:2;
		if (send(m_hSocket,cbDataBuffer,nOff,0)!=nOff) return CONNECT_PROXY_FAILURE;

		//接收数据
		if (recv(m_hSocket,cbDataBuffer,2,0)!=2) return CONNECT_PROXY_FAILURE;

		//数据分析
		if (cbDataBuffer[0]!=5) return CONNECT_PROXY_FAILURE;
		if ((cbDataBuffer[1]!=0)&&(cbDataBuffer[1]!=2)) return CONNECT_PROXY_FAILURE;

		//身份验证
		if (cbDataBuffer[1]==2)
		{
			//变量定义
			INT nStringLen=0;
			CT2CA strUserName(m_ProxyServerInfo.szUserName);
			CT2CA strPassword(m_ProxyServerInfo.szPassword);

			//登录帐号
			nOff=0;
			cbDataBuffer[nOff++]=1;
			nStringLen=lstrlenA(strUserName);
			cbDataBuffer[nOff++]=(char)nStringLen;
			CopyMemory(cbDataBuffer+nOff,(LPCSTR)strUserName,nStringLen);
			nOff+=nStringLen;

			//登录密码
			nStringLen=lstrlenA(strPassword);
			cbDataBuffer[nOff++]=(char)nStringLen;
			CopyMemory(cbDataBuffer+nOff,(LPCSTR)strPassword,nStringLen);
			nOff+=nStringLen;

			//发送数据
			if (send(m_hSocket,cbDataBuffer,nOff,0)!=nOff) return CONNECT_PROXY_FAILURE;

			//接受数据
			if (recv(m_hSocket,cbDataBuffer,2,0)!=2) return CONNECT_PROXY_FAILURE;

			//数据分析
			if ((cbDataBuffer[0]!=1)||(cbDataBuffer[1]!=0)) return CONNECT_PROXY_USER_INVALID;
		}
	}

	return CONNECT_SUCCESS;
}

//地址解释
DWORD CTCPSocket::TranslateAddr(LPCTSTR pszServerAddr)
{
	//转化地址
	CT2CA ServerAddr(pszServerAddr);
	DWORD dwServerIP=inet_addr(ServerAddr);

	//域名解释
	if (dwServerIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(ServerAddr);
		if (lpHost==NULL) return INADDR_NONE;
		dwServerIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}

	return dwServerIP;
}

//解密数据
WORD CTCPSocket::CrevasseBuffer(BYTE cbDataBuffer[], WORD wDataSize)
{
	//效验参数
	ASSERT(m_dwSendPacketCount>0);
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(((CMD_Head *)cbDataBuffer)->CmdInfo.wPacketSize==wDataSize);

	//调整长度
	WORD wSnapCount=0;
	if ((wDataSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wDataSize%sizeof(DWORD);
		ZeroMemory(cbDataBuffer+wDataSize,wSnapCount);
	}

	//解密数据
	DWORD dwXorKey=m_dwRecvXorKey;
	DWORD * pdwXor=(DWORD *)(cbDataBuffer+sizeof(CMD_Info));
	WORD  * pwSeed=(WORD *)(cbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wDataSize+wSnapCount-sizeof(CMD_Info))/4;
	for (WORD i=0;i<wEncrypCount;i++)
	{
		if ((i==(wEncrypCount-1))&&(wSnapCount>0))
		{
			BYTE * pcbKey=((BYTE *)&m_dwRecvXorKey)+sizeof(DWORD)-wSnapCount;
			CopyMemory(cbDataBuffer+wDataSize,pcbKey,wSnapCount);
		}
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
		*pdwXor++^=m_dwRecvXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//效验字节
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;
	BYTE cbCheckCode=pHead->CmdInfo.cbCheckCode;
	for (INT i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		cbDataBuffer[i]=MapRecvByte(cbDataBuffer[i]);
		cbCheckCode+=cbDataBuffer[i];
	}

	//关闭连接
	if (cbCheckCode!=0)
	{
		ASSERT(FALSE);
		return 0;
	}

	return wDataSize;
}

//加密数据
WORD CTCPSocket::EncryptBuffer(BYTE cbDataBuffer[], WORD wDataSize, WORD wBufferSize)
{
	//效验参数
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(wBufferSize>=(wDataSize+2*sizeof(DWORD)));
	ASSERT(wDataSize<=(sizeof(CMD_Head)+SOCKET_PACKET));

	//调整长度
	WORD wEncryptSize=wDataSize-sizeof(CMD_Command),wSnapCount=0;
	if ((wEncryptSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wEncryptSize%sizeof(DWORD);
		ZeroMemory(cbDataBuffer+sizeof(CMD_Info)+wEncryptSize,wSnapCount);
	}

	//映射字节
	BYTE cbCheckCode=0;
	for (WORD i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		cbCheckCode+=cbDataBuffer[i];
		cbDataBuffer[i]=MapSendByte(cbDataBuffer[i]);
	}

	//填写信息头
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;
	pHead->CmdInfo.cbVersion=SOCKET_VER;
	pHead->CmdInfo.wPacketSize=wDataSize;
	pHead->CmdInfo.cbCheckCode=~cbCheckCode+1;

	//创建密钥
	DWORD dwXorKey=m_dwSendXorKey;
	if (m_dwSendPacketCount==0)
	{
		//随机种子
		GUID Guid;
		CoCreateGuid(&Guid);
		dwXorKey=GetTickCount();
		dwXorKey^=Guid.Data1;
		dwXorKey^=Guid.Data2;
		dwXorKey^=Guid.Data3;
		dwXorKey^=*((DWORD *)Guid.Data4);

		//映射种子
		dwXorKey=SeedRandMap((WORD)dwXorKey);
		dwXorKey|=((DWORD)SeedRandMap((WORD)(dwXorKey>>16)))<<16;
		dwXorKey^=g_dwPacketKey;
		m_dwSendXorKey=dwXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//加密数据
	WORD * pwSeed=(WORD *)(cbDataBuffer+sizeof(CMD_Info));
	DWORD * pdwXor=(DWORD *)(cbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wEncryptSize+wSnapCount)/sizeof(DWORD);
	for (i=0;i<wEncrypCount;i++)
	{
		*pdwXor++^=dwXorKey;
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
	}

	//插入密钥
	if (m_dwSendPacketCount==0)
	{
		MoveMemory(cbDataBuffer+sizeof(CMD_Head)+sizeof(DWORD),cbDataBuffer+sizeof(CMD_Head),wDataSize);
		*((DWORD *)(cbDataBuffer+sizeof(CMD_Head)))=m_dwSendXorKey;
		pHead->CmdInfo.wPacketSize+=sizeof(DWORD);
		wDataSize+=sizeof(DWORD);
	}

	//设置变量
	m_dwSendPacketCount++;
	m_dwSendXorKey=dwXorKey;

	return wDataSize;
}

//网络读取
LRESULT CTCPSocket::OnSocketNotifyRead(WPARAM wParam, LPARAM lParam)
{
	//状态效验
	if (m_dwSendPacketCount==0L) return 0;

	//读取数据
	INT iRetCode=recv(m_hSocket,(char *)m_cbRecvBuf+m_wRecvSize,sizeof(m_cbRecvBuf)-m_wRecvSize,0);

	//关闭判断
	if (iRetCode==SOCKET_ERROR)
	{
		CloseSocket(SHUT_REASON_EXCEPTION);
		return 1L;
	}

	//设置变量
	m_wRecvSize+=iRetCode;
	m_dwRecvTickCount=GetTickCount()/1000L;

	//变量定义
	CMD_Head * pHead=(CMD_Head *)m_cbRecvBuf;
	BYTE cbDataBuffer[SOCKET_PACKET+sizeof(CMD_Head)];

	//数据处理
	while ((m_wRecvSize>=sizeof(CMD_Head))&&(m_hSocket!=INVALID_SOCKET))
	{
		//版本判断
		if (pHead->CmdInfo.cbVersion!=SOCKET_VER)
		{
			CloseSocket(SHUT_REASON_EXCEPTION);
			return 1L;
		}

		//长度判断
		if (pHead->CmdInfo.wPacketSize>(SOCKET_PACKET+sizeof(CMD_Head)))
		{
			CloseSocket(SHUT_REASON_EXCEPTION);
			return 1L;
		}

		//完整判断
		WORD wPacketSize=pHead->CmdInfo.wPacketSize;
		if (m_wRecvSize<pHead->CmdInfo.wPacketSize) return 1;

		//设置变量
		m_dwRecvPacketCount++;
		m_wRecvSize-=wPacketSize;

		//提取数据
		CopyMemory(cbDataBuffer,m_cbRecvBuf,wPacketSize);
		MoveMemory(m_cbRecvBuf,m_cbRecvBuf+wPacketSize,m_wRecvSize);

		//解密数据
		WORD wRealySize=CrevasseBuffer(cbDataBuffer,wPacketSize);

		//关闭判断
		if ((wRealySize==0)&&(m_hSocket==INVALID_SOCKET))
		{
			CloseSocket(SHUT_REASON_EXCEPTION);
			return 1L;
		}

		//解释数据
		WORD wDataSize=wRealySize-sizeof(CMD_Head);
		VOID * pDataBuffer=cbDataBuffer+sizeof(CMD_Head);
		CMD_Command Command=((CMD_Head *)cbDataBuffer)->CommandInfo;

		//内核数据
		if (Command.wMainCmdID==MDM_KN_COMMAND)
		{
			switch (Command.wSubCmdID)
			{
			case SUB_KN_DETECT_SOCKET:		//网络检测
				{
					//回应数据
					SendData(MDM_KN_COMMAND,SUB_KN_DETECT_SOCKET);

					break;
				}
			case SUB_KN_SHUT_DOWN_SOCKET:	//中断连接
				{
					//中断连接
					CloseSocket(SHUT_REASON_NORMAL);

					break;
				}
			}
		}

		//常规数据
		if ((Command.wMainCmdID!=MDM_KN_COMMAND)&&(m_pITCPSocketSink!=NULL))
		{
			try
			{
				//处理数据
				bool bSuccess=m_pITCPSocketSink->OnEventTCPSocketRead(m_wSocketID,Command,pDataBuffer,wDataSize);

				//关闭判断
				if (bSuccess==false)
				{
					CloseSocket(SHUT_REASON_EXCEPTION);
					return 1L;
				}
			}
			catch (...)
			{
				//关闭连接
				CloseSocket(SHUT_REASON_EXCEPTION);
				return 1L;
			}
		}
	}

	return 1L;
}

//网络发送
LRESULT CTCPSocket::OnSocketNotifyWrite(WPARAM wParam, LPARAM lParam)
{
	//缓冲判断
	if ((m_bNeedBuffer==true)&&(m_dwBufferData>0L))
	{
		//变量定义
		DWORD dwTotalCount=0;
		DWORD dwPacketSize=4096;

		//设置变量
		m_dwSendTickCount=GetTickCount()/1000L;

		//发送数据
		while (dwTotalCount<m_dwBufferData)
		{
			//发生数据
			WORD wSendSize=(WORD)__min(dwPacketSize,m_dwBufferData-dwTotalCount);
			INT nSendCount=send(m_hSocket,(char *)m_pcbDataBuffer+dwTotalCount,wSendSize,0);

			//错误判断
			if (nSendCount==SOCKET_ERROR)
			{
				//缓冲判断
				if (WSAGetLastError()==WSAEWOULDBLOCK)
				{
					//设置变量
					m_bNeedBuffer=false;
					m_dwBufferData-=dwTotalCount;

					//移动内存
					if (m_dwBufferData>0L)
					{
						m_bNeedBuffer=true;
						MoveMemory(m_pcbDataBuffer,m_pcbDataBuffer+dwTotalCount,m_dwBufferData);
					}

					return 1L;
				}

				//关闭连接
				CloseSocket(SHUT_REASON_EXCEPTION);

				return 1L;
			}

			//设置变量
			dwTotalCount+=nSendCount;
		}

		//设置变量
		m_dwBufferData=0L;
		m_bNeedBuffer=false;
	}

	return 1L;
}

//网络关闭
LRESULT CTCPSocket::OnSocketNotifyClose(WPARAM wParam, LPARAM lParam)
{
	//关闭连接
	CloseSocket(SHUT_REASON_REMOTE);

	return 1L;
}

//网络连接
LRESULT CTCPSocket::OnSocketNotifyConnect(WPARAM wParam, LPARAM lParam)
{
	//获取错误
	INT nErrorCode=WSAGETSELECTERROR(lParam);

	//判断状态
	if (nErrorCode==0)
	{

#ifndef _DEBUG

		//设置时间
		SetTimer(IDI_DETEST_SOCKET,10000L,NULL);

#endif

		//设置状态
		m_cbSocketStatus=SOCKET_STATUS_CONNECT;
	}
	else
	{
		//关闭连接
		CloseSocket(SHUT_REASON_INSIDE);
	}

	//发送通知
	ASSERT(m_pITCPSocketSink!=NULL);
	if (m_pITCPSocketSink!=NULL) m_pITCPSocketSink->OnEventTCPSocketLink(m_wSocketID,nErrorCode);

	return 1;
}

//时间消息
VOID CTCPSocket::OnTimer(UINT_PTR nIDEvent)
{
	//网络检测
	if (nIDEvent==IDI_DETEST_SOCKET)
	{
		//终止判断
		if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) 
		{
			ASSERT(FALSE);
			KillTimer(IDI_DETEST_SOCKET);

			return;
		}

		//检测判断
		DWORD dwCompareTickCount=GetTickCount()/1000L-30L;
		bool bIntermit=((m_dwSendTickCount<dwCompareTickCount)&&(m_dwRecvTickCount<dwCompareTickCount));

		//发送命令
		if (bIntermit==true) CloseSocket(SHUT_REASON_TIME_OUT);

		return;
	}

	__super::OnTimer(nIDEvent);
}

//网络消息
LRESULT	CTCPSocket::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:		//数据读取
		{ 
			return OnSocketNotifyRead(wParam,lParam); 
		}
	case FD_WRITE:		//网络发送
		{
			return OnSocketNotifyWrite(wParam,lParam);
		}
	case FD_CLOSE:		//网络关闭
		{ 
			return OnSocketNotifyClose(wParam,lParam);	
		}
	case FD_CONNECT:	//网络连接
		{ 
			return OnSocketNotifyConnect(wParam,lParam); 
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

//组件创建函数
DECLARE_CREATE_MODULE(TCPSocket);

//////////////////////////////////////////////////////////////////////////
