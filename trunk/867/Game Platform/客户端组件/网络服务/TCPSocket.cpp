#include "Stdafx.h"
#include "TCPSocket.h"

//////////////////////////////////////////////////////////////////////////

//�궨��
#define ID_SOCKET_WND				10								//SOCKET ���� ID
#define WM_SOCKET_NOTIFY			WM_USER+10						//SOCKET ��Ϣ

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTCPSocket, CWnd)
	ON_MESSAGE(WM_SOCKET_NOTIFY,OnSocketNotify)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

////�����ֽ�ӳ���
//BYTE CTCPSocket::g_SendByteMap[256]=				
//{
//	0x70,0x2F,0x40,0x5F,0x44,0x8E,0x6E,0x45,0x7E,0xAB,0x2C,0x1F,0xB4,0xAC,0x9D,0x91,
//	0x0D,0x36,0x9B,0x0B,0xD4,0xC4,0x39,0x74,0xBF,0x23,0x16,0x14,0x06,0xEB,0x04,0x3E,
//	0x12,0x5C,0x8B,0xBC,0x61,0x63,0xF6,0xA5,0xE1,0x65,0xD8,0xF5,0x5A,0x07,0xF0,0x13,
//	0xF2,0x20,0x6B,0x4A,0x24,0x59,0x89,0x64,0xD7,0x42,0x6A,0x5E,0x3D,0x0A,0x77,0xE0,
//	0x80,0x27,0xB8,0xC5,0x8C,0x0E,0xFA,0x8A,0xD5,0x29,0x56,0x57,0x6C,0x53,0x67,0x41,
//	0xE8,0x00,0x1A,0xCE,0x86,0x83,0xB0,0x22,0x28,0x4D,0x3F,0x26,0x46,0x4F,0x6F,0x2B,
//	0x72,0x3A,0xF1,0x8D,0x97,0x95,0x49,0x84,0xE5,0xE3,0x79,0x8F,0x51,0x10,0xA8,0x82,
//	0xC6,0xDD,0xFF,0xFC,0xE4,0xCF,0xB3,0x09,0x5D,0xEA,0x9C,0x34,0xF9,0x17,0x9F,0xDA,
//	0x87,0xF8,0x15,0x05,0x3C,0xD3,0xA4,0x85,0x2E,0xFB,0xEE,0x47,0x3B,0xEF,0x37,0x7F,
//	0x93,0xAF,0x69,0x0C,0x71,0x31,0xDE,0x21,0x75,0xA0,0xAA,0xBA,0x7C,0x38,0x02,0xB7,
//	0x81,0x01,0xFD,0xE7,0x1D,0xCC,0xCD,0xBD,0x1B,0x7A,0x2A,0xAD,0x66,0xBE,0x55,0x33,
//	0x03,0xDB,0x88,0xB2,0x1E,0x4E,0xB9,0xE6,0xC2,0xF7,0xCB,0x7D,0xC9,0x62,0xC3,0xA6,
//	0xDC,0xA7,0x50,0xB5,0x4B,0x94,0xC0,0x92,0x4C,0x11,0x5B,0x78,0xD9,0xB1,0xED,0x19,
//	0xE9,0xA1,0x1C,0xB6,0x32,0x99,0xA3,0x76,0x9E,0x7B,0x6D,0x9A,0x30,0xD6,0xA9,0x25,
//	0xC7,0xAE,0x96,0x35,0xD0,0xBB,0xD2,0xC8,0xA2,0x08,0xF3,0xD1,0x73,0xF4,0x48,0x2D,
//	0x90,0xCA,0xE2,0x58,0xC1,0x18,0x52,0xFE,0xDF,0x68,0x98,0x54,0xEC,0x60,0x43,0x0F
//};
//
////�����ֽ�ӳ���
//BYTE CTCPSocket::m_RecvByteMap[256]=				
//{
//	0x51,0xA1,0x9E,0xB0,0x1E,0x83,0x1C,0x2D,0xE9,0x77,0x3D,0x13,0x93,0x10,0x45,0xFF,
//	0x6D,0xC9,0x20,0x2F,0x1B,0x82,0x1A,0x7D,0xF5,0xCF,0x52,0xA8,0xD2,0xA4,0xB4,0x0B,
//	0x31,0x97,0x57,0x19,0x34,0xDF,0x5B,0x41,0x58,0x49,0xAA,0x5F,0x0A,0xEF,0x88,0x01,
//	0xDC,0x95,0xD4,0xAF,0x7B,0xE3,0x11,0x8E,0x9D,0x16,0x61,0x8C,0x84,0x3C,0x1F,0x5A,
//	0x02,0x4F,0x39,0xFE,0x04,0x07,0x5C,0x8B,0xEE,0x66,0x33,0xC4,0xC8,0x59,0xB5,0x5D,
//	0xC2,0x6C,0xF6,0x4D,0xFB,0xAE,0x4A,0x4B,0xF3,0x35,0x2C,0xCA,0x21,0x78,0x3B,0x03,
//	0xFD,0x24,0xBD,0x25,0x37,0x29,0xAC,0x4E,0xF9,0x92,0x3A,0x32,0x4C,0xDA,0x06,0x5E,
//	0x00,0x94,0x60,0xEC,0x17,0x98,0xD7,0x3E,0xCB,0x6A,0xA9,0xD9,0x9C,0xBB,0x08,0x8F,
//	0x40,0xA0,0x6F,0x55,0x67,0x87,0x54,0x80,0xB2,0x36,0x47,0x22,0x44,0x63,0x05,0x6B,
//	0xF0,0x0F,0xC7,0x90,0xC5,0x65,0xE2,0x64,0xFA,0xD5,0xDB,0x12,0x7A,0x0E,0xD8,0x7E,
//	0x99,0xD1,0xE8,0xD6,0x86,0x27,0xBF,0xC1,0x6E,0xDE,0x9A,0x09,0x0D,0xAB,0xE1,0x91,
//	0x56,0xCD,0xB3,0x76,0x0C,0xC3,0xD3,0x9F,0x42,0xB6,0x9B,0xE5,0x23,0xA7,0xAD,0x18,
//	0xC6,0xF4,0xB8,0xBE,0x15,0x43,0x70,0xE0,0xE7,0xBC,0xF1,0xBA,0xA5,0xA6,0x53,0x75,
//	0xE4,0xEB,0xE6,0x85,0x14,0x48,0xDD,0x38,0x2A,0xCC,0x7F,0xB1,0xC0,0x71,0x96,0xF8,
//	0x3F,0x28,0xF2,0x69,0x74,0x68,0xB7,0xA3,0x50,0xD0,0x79,0x1D,0xFC,0xCE,0x8A,0x8D,
//	0x2E,0x62,0x30,0xEA,0xED,0x2B,0x26,0xB9,0x81,0x7C,0x46,0x89,0x73,0xA2,0xF7,0x72
//};
//
////���ݼ�����Կ
//const static DWORD g_dwPacketKey=0xA55AA55A;

//////////////////////////////////////////////////////////////////////////

//���캯��
CTCPSocket::CTCPSocket()
{
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;
	//m_cbSocketStatus=SHUT_REASON_NORMAL;
	m_hSocket=INVALID_SOCKET;
	m_pITCPSocketSink=NULL;
	//m_ProxyInfo.wProxyPort=0;
	//m_ProxyInfo.cbProxyType=PROXY_NONE;
	m_cbSocketStatus=SOCKET_STATUS_IDLE;
}

//��������
CTCPSocket::~CTCPSocket()
{
	CloseSocket();
}

//�ӿڲ�ѯ
void * __cdecl CTCPSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocket,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocket,Guid,dwQueryVer);
	return NULL;
}

//ȡ������
/*void __cdecl CTCPSocket::CancelProxyServer()
{
	memset(&m_ProxyInfo,0,sizeof(m_ProxyInfo));
	m_ProxyInfo.wProxyPort=0;
	m_ProxyInfo.strHttpDomain.Empty();
	m_ProxyInfo.strProxyName.Empty();
	m_ProxyInfo.strProxyPass.Empty();
	m_ProxyInfo.strProxyServer.Empty();
	m_ProxyInfo.cbProxyType=PROXY_NONE;
	return;
}*/

//���������
bool __cdecl CTCPSocket::SetProxyServerInfo(enProxyServerType ProxyServerType, const tagProxyServerInfo & ProxyServerInfo)
{
	m_ProxyServerInfo=ProxyServerInfo;
	return true;
}

//���ýӿ�
bool __cdecl CTCPSocket::SetTCPSocketSink(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pITCPSocketSink=(ITCPSocketSink *)pIUnknownEx->QueryInterface(IID_ITCPSocketSink,VER_ITCPSocketSink);
	ASSERT(m_pITCPSocketSink!=NULL);
	return (m_pITCPSocketSink!=NULL);
}

//��ȡ�ӿ�
void * __cdecl CTCPSocket::GetTCPSocketSink(const IID & Guid, DWORD dwQueryVer)
{
	if (m_pITCPSocketSink==NULL) return NULL;
	return m_pITCPSocketSink->QueryInterface(Guid,dwQueryVer);
}

//���ӷ�����
DWORD __cdecl CTCPSocket::Connect(DWORD dwServerIP, WORD wPort)
{
	//Ч�����
	ASSERT(m_hSocket==INVALID_SOCKET);
	ASSERT(m_cbSocketStatus==SOCKET_STATUS_IDLE);

	//Ч��״̬
	if (m_hSocket!=INVALID_SOCKET) throw TEXT("���� SOCKET ����Ѿ�����");
	if (m_cbSocketStatus!=SOCKET_STATUS_IDLE) throw TEXT("����״̬���ǵȴ�����״̬");
	if (dwServerIP==INADDR_NONE) throw TEXT("Ŀ���������ַ��ʽ����ȷ��������ٴγ��ԣ�");

	//���ò���
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0x12345678;
	m_dwRecvXorKey=0x12345678;
	m_dwSendTickCount=GetTickCount()/1000L;
	m_dwRecvTickCount=GetTickCount()/1000L;

	try
	{
		//���� SOCKET
		m_hSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if (m_hSocket==INVALID_SOCKET) throw TEXT("SOCKET ����ʧ��");
		if ((m_hWnd==NULL)&&(!Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),GetDesktopWindow(),ID_SOCKET_WND,NULL)))
			throw TEXT("SOCKET �ڲ����ڴ���ʧ��");

		//��д��������ַ
		m_wSocketID=m_hSocket;
		SOCKADDR_IN SocketAddr;
		memset(&SocketAddr,0,sizeof(SocketAddr));
		SocketAddr.sin_family=AF_INET;
		SocketAddr.sin_port=htons(wPort);
		SocketAddr.sin_addr.S_un.S_addr=dwServerIP;

		//���ӷ�����
		int iErrorCode=0;
		WSASetLastError(0);
		//if (m_ProxyInfo.cbProxyType!=PROXY_NONE)
		//{
		//	throw TEXT("δ֧�ִ��������");
		//}
		//else
		{
			//�󶨴���
			iErrorCode=WSAAsyncSelect(m_hSocket,m_hWnd,WM_SOCKET_NOTIFY,FD_READ|FD_CONNECT|FD_CLOSE);
			if (iErrorCode==SOCKET_ERROR) throw TEXT("���ڲ����ڴ���");

			//���ӷ�����
			iErrorCode=connect(m_hSocket,(SOCKADDR *)&SocketAddr,sizeof(SocketAddr));
			if (iErrorCode==SOCKET_ERROR)
			{
				iErrorCode=WSAGetLastError();
				if (iErrorCode!=WSAEWOULDBLOCK)
				{
					static TCHAR szBuffer[64];
					_snprintf(szBuffer,sizeof(szBuffer),TEXT("���ӷ������󣬴������ [ %d ]"),iErrorCode);
					throw szBuffer;
				}
			}

			//���ñ���
			m_cbSocketStatus=SOCKET_STATUS_WAIT;
		}

		return CONNECT_SUCCESS;
	}
	catch (LPCTSTR pszError)
	{
		CloseSocket();
		throw pszError;
		return CONNECT_FAILURE;
	}
	catch (...)
	{
		CloseSocket();
		throw TEXT("���Ӳ���δ֪�쳣����");
		return CONNECT_EXCEPTION;
	}

	
}

//���ӷ�����
DWORD __cdecl CTCPSocket::Connect(const LPCTSTR szServerIP, WORD wPort)
{
	//Ч������
	ASSERT(wPort!=0);
	ASSERT(szServerIP!=NULL);
	if ((szServerIP==NULL)||(wPort==0)) return false;
	return Connect(TranslateAddr(szServerIP),wPort);
}

//���ͺ���
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID)
{
	//Ч��״̬
	if (m_hSocket==INVALID_SOCKET) return false;
	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return false;

	//��������
	BYTE cbDataBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;

	//��������
	WORD wSendSize=EncryptBuffer(cbDataBuffer,sizeof(CMD_Head),sizeof(cbDataBuffer));

	//��������
	return SendDataBuffer(cbDataBuffer,wSendSize);
}

//���ͺ���
DWORD __cdecl CTCPSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//Ч��״̬
	if (m_hSocket==INVALID_SOCKET) return false;
	if (m_cbSocketStatus!=SOCKET_STATUS_CONNECT) return false;

	//Ч���С
	ASSERT(wDataSize<=SOCKET_PACKET);
	if (wDataSize>SOCKET_PACKET) return false;

	//��������
	BYTE cbDataBuffer[SOCKET_BUFFER];
	CMD_Head * pHead=(CMD_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;
	if (wDataSize>0)
	{
		ASSERT(pData!=NULL);
		CopyMemory(pHead+1,pData,wDataSize);
	}

	//��������
	WORD wSendSize=EncryptBuffer(cbDataBuffer,sizeof(CMD_Head)+wDataSize,sizeof(cbDataBuffer));

	//��������
	return SendDataBuffer(cbDataBuffer,wSendSize);
}

//�ر�����
void __cdecl CTCPSocket::CloseSocket()
{
	//�ر�����
	bool bClose=(m_hSocket!=INVALID_SOCKET);
	m_cbSocketStatus=SOCKET_STATUS_IDLE;
	if (m_hSocket!=INVALID_SOCKET)
	{
		WSAAsyncSelect(m_hSocket,GetSafeHwnd(),WM_SOCKET_NOTIFY,0);
		closesocket(m_hSocket);
		m_hSocket=INVALID_SOCKET;
		m_cbSocketStatus=SOCKET_STATUS_IDLE;
	}
	if ((bClose==true)&&(m_pITCPSocketSink!=NULL))
	{
		ASSERT(m_pITCPSocketSink!=NULL);
		try { m_pITCPSocketSink->OnEventTCPSocketShut(m_wSocketID,SHUT_REASON_NORMAL); }
		catch (...) {}
	}

	//�ָ�����
	m_wRecvSize=0;
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;
	m_dwSendTickCount=0;
	m_dwRecvTickCount=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;
	return;
}

//��������
DWORD CTCPSocket::SendDataBuffer(void * pBuffer, WORD wSendSize)
{
	//Ч�����
	ASSERT(wSendSize!=0);
	ASSERT(pBuffer!=NULL);
	
	//��������
	WORD wSended=0;
	while (wSended<wSendSize)
	{
		int iErrorCode=send(m_hSocket,(char *)pBuffer+wSended,wSendSize-wSended,0);
		if (iErrorCode==SOCKET_ERROR)
		{
			if (WSAGetLastError()==WSAEWOULDBLOCK)
			{
				m_dwSendTickCount=GetTickCount()/1000L;
				return true;
			}
			return false;
		}
		wSended+=iErrorCode;
	}
	m_dwSendTickCount=GetTickCount()/1000L;

	return true;
}

//���ӳ��
WORD CTCPSocket::SeedRandMap(WORD wSeed)
{
	DWORD dwHold=wSeed;
	return (WORD)((dwHold=dwHold*241103L+2533101L)>>16);
}

//ӳ�䷢������
BYTE CTCPSocket::MapSendByte(BYTE const cbData)
{
	BYTE cbMap=g_SendByteMap[(BYTE)(cbData+m_cbSendRound)];
	m_cbSendRound+=3;
	return cbMap;
}

//ӳ���������
BYTE CTCPSocket::MapRecvByte(BYTE const cbData)
{
	BYTE cbMap=g_RecvByteMap[cbData]-m_cbRecvRound;
	m_cbRecvRound+=3;
	return cbMap;
}

//���ͷ�������ַ
DWORD CTCPSocket::TranslateAddr(LPCTSTR pszServerAddr)
{
	//ת����ַ
	DWORD dwServerIP=inet_addr(pszServerAddr);
	if (dwServerIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(pszServerAddr);
		if (lpHost==NULL) return INADDR_NONE;
		dwServerIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}
	return dwServerIP;
}

//���ʹ���
/*LPCTSTR CTCPSocket::GetConnectError(int iErrorCode, LPTSTR pszBuffer, WORD wBufferSize)
{
	//Ч�����
	ASSERT(pszBuffer!=NULL);
	if (pszBuffer==NULL) return NULL;

	//���ʹ���
	switch (iErrorCode)
	{
	case 0:					//û�д���
		{
			lstrcpyn(pszBuffer,TEXT("����ִ�гɹ�"),wBufferSize);
			break;
		}
	case WSAEADDRNOTAVAIL:	//��ַ��ʽ����
		{
			lstrcpyn(pszBuffer,TEXT("Ŀ���������ַ��ʽ����ȷ��������ٴγ��ԣ�"),wBufferSize);
			break;
		}
	case WSAECONNREFUSED:	//������û������
		{
			lstrcpyn(pszBuffer,TEXT("Ŀ���������æ����û��������"),wBufferSize);
			break;
		}
	case WSAETIMEDOUT:		//���ӳ�ʱ
		{
			lstrcpyn(pszBuffer,TEXT("���ӳ�ʱ��������Ŀ������������ڻ��߷�������ַ��ʽ����ȷ��"),wBufferSize);
			break;
		}
	case WSAEHOSTUNREACH:
		{
			lstrcpyn(pszBuffer,TEXT("��������ʧ�ܣ������Ƿ��Ѿ��ɹ����ź����� Internet ��"),wBufferSize);
			break;
		}
	default:				//Ĭ�ϴ���
		{
			_snprintf(pszBuffer,wBufferSize,TEXT("���Ӵ���ţ�%ld����ϸ������Ϣ��ο����������ֲᣡ"),iErrorCode);
			break;
		}
	}

	return pszBuffer;
}*/
//�������
DWORD  CTCPSocket::ProxyServerTesting()
{
	return 0;
}

//��������
WORD CTCPSocket::EncryptBuffer(BYTE pcbDataBuffer[], WORD wDataSize, WORD wBufferSize)
{
	//Ч�����
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(wBufferSize>=(wDataSize+2*sizeof(DWORD)));
	ASSERT(wDataSize<=(sizeof(CMD_Head)+SOCKET_PACKET));

	//��������
	WORD wEncryptSize=wDataSize-sizeof(CMD_Command),wSnapCount=0;
	if ((wEncryptSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wEncryptSize%sizeof(DWORD);
		memset(pcbDataBuffer+sizeof(CMD_Info)+wEncryptSize,0,wSnapCount);
	}

	//Ч�������ֽ�ӳ��
	BYTE cbCheckCode=0;
	for (WORD i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		cbCheckCode+=pcbDataBuffer[i];
		pcbDataBuffer[i]=MapSendByte(pcbDataBuffer[i]);
	}

	//��д��Ϣͷ
	CMD_Head * pHead=(CMD_Head *)pcbDataBuffer;
	pHead->CmdInfo.cbCheckCode=~cbCheckCode+1;
	pHead->CmdInfo.wPacketSize=wDataSize;
	pHead->CmdInfo.cbVersion=SOCKET_VER;

	//������Կ
	DWORD dwXorKey=m_dwSendXorKey;
	if (m_dwSendPacketCount==0)
	{
		//���ɵ�һ���������
		GUID Guid;
		CoCreateGuid(&Guid);
		dwXorKey=GetTickCount()*GetTickCount();
		dwXorKey^=Guid.Data1;
		dwXorKey^=Guid.Data2;
		dwXorKey^=Guid.Data3;
		dwXorKey^=*((DWORD *)Guid.Data4);
		
		//���ӳ������
		dwXorKey=SeedRandMap((WORD)dwXorKey);
		dwXorKey|=((DWORD)SeedRandMap((WORD)(dwXorKey>>16)))<<16;
		dwXorKey^=g_dwPacketKey;
		m_dwSendXorKey=dwXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//��������
	WORD * pwSeed=(WORD *)(pcbDataBuffer+sizeof(CMD_Info));
	DWORD * pdwXor=(DWORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wEncryptSize+wSnapCount)/sizeof(DWORD);
	for (i=0;i<wEncrypCount;i++)
	{
		*pdwXor++^=dwXorKey;
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
	}

	//������Կ
	if (m_dwSendPacketCount==0)
	{
		MoveMemory(pcbDataBuffer+sizeof(CMD_Head)+sizeof(DWORD),pcbDataBuffer+sizeof(CMD_Head),wDataSize);
		*((DWORD *)(pcbDataBuffer+sizeof(CMD_Head)))=m_dwSendXorKey;
		pHead->CmdInfo.wPacketSize+=sizeof(DWORD);
		wDataSize+=sizeof(DWORD);
	}

	//���ñ���
	m_dwSendPacketCount++;
	m_dwSendXorKey=dwXorKey;

	return wDataSize;
}

//��������
WORD CTCPSocket::CrevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize)
{
	//Ч�����
	ASSERT(m_dwSendPacketCount>0);
	ASSERT(wDataSize>=sizeof(CMD_Head));
	ASSERT(((CMD_Head *)pcbDataBuffer)->CmdInfo.wPacketSize==wDataSize);

	//��������
	WORD wSnapCount=0;
	if ((wDataSize%sizeof(DWORD))!=0)
	{
		wSnapCount=sizeof(DWORD)-wDataSize%sizeof(DWORD);
		memset(pcbDataBuffer+wDataSize,0,wSnapCount);
	}

	//��������
	DWORD dwXorKey=m_dwRecvXorKey;
	DWORD * pdwXor=(DWORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD  * pwSeed=(WORD *)(pcbDataBuffer+sizeof(CMD_Info));
	WORD wEncrypCount=(wDataSize+wSnapCount-sizeof(CMD_Info))/4;
	for (WORD i=0;i<wEncrypCount;i++)
	{
		if ((i==(wEncrypCount-1))&&(wSnapCount>0))
		{
			BYTE * pcbKey=((BYTE *)&m_dwRecvXorKey)+sizeof(DWORD)-wSnapCount;
			CopyMemory(pcbDataBuffer+wDataSize,pcbKey,wSnapCount);
		}
		dwXorKey=SeedRandMap(*pwSeed++);
		dwXorKey|=((DWORD)SeedRandMap(*pwSeed++))<<16;
		dwXorKey^=g_dwPacketKey;
		*pdwXor++^=m_dwRecvXorKey;
		m_dwRecvXorKey=dwXorKey;
	}

	//Ч�������ֽ�ӳ��
	CMD_Head * pHead=(CMD_Head *)pcbDataBuffer;
	BYTE cbCheckCode=pHead->CmdInfo.cbCheckCode;
	for (int i=sizeof(CMD_Info);i<wDataSize;i++)
	{
		pcbDataBuffer[i]=MapRecvByte(pcbDataBuffer[i]);
		cbCheckCode+=pcbDataBuffer[i];
	}
	if (cbCheckCode!=0) throw TEXT("���ݰ�Ч�������");

	return wDataSize;
}

//��������
LRESULT CTCPSocket::OnSocketNotifyConnect(WPARAM wParam, LPARAM lParam)
{
	//�ж�״̬
	int iErrorCode=WSAGETSELECTERROR(lParam);
	if (iErrorCode==0) m_cbSocketStatus=SOCKET_STATUS_CONNECT;
	else CloseSocket();

	//����֪ͨ
	//TCHAR szErrorDesc[128]=TEXT("");
	//GetConnectError(iErrorCode,szErrorDesc,sizeof(szErrorDesc));
	m_pITCPSocketSink->OnEventTCPSocketLink(m_wSocketID,iErrorCode);

	return 1;
}

//�����ȡ
LRESULT CTCPSocket::OnSocketNotifyRead(WPARAM wParam, LPARAM lParam)
{
	try
	{
		//��ȡ����
		int iRetCode=recv(m_hSocket,(char *)m_cbRecvBuf+m_wRecvSize,sizeof(m_cbRecvBuf)-m_wRecvSize,0);
		if (iRetCode==SOCKET_ERROR) throw TEXT("�������ӹرգ���ȡ����ʧ��");
		ASSERT(m_dwSendPacketCount>0);
		m_wRecvSize+=iRetCode;
		m_dwRecvTickCount=GetTickCount()/1000L;

		//��������
		WORD wPacketSize=0;
		BYTE cbDataBuffer[SOCKET_PACKET+sizeof(CMD_Head)];
		CMD_Head * pHead=(CMD_Head *)m_cbRecvBuf;

		while (m_wRecvSize>=sizeof(CMD_Head))
		{
			//Ч�����
			wPacketSize=pHead->CmdInfo.wPacketSize;
			ASSERT(pHead->CmdInfo.cbVersion==SOCKET_VER);
			ASSERT(wPacketSize<=(SOCKET_PACKET+sizeof(CMD_Head)));
			if (pHead->CmdInfo.cbVersion!=SOCKET_VER) throw TEXT("���ݰ��汾����");
			if (wPacketSize>(SOCKET_PACKET+sizeof(CMD_Head))) throw TEXT("���ݰ�̫��");
			if (m_wRecvSize<wPacketSize) return 1;

			//��������
			m_dwRecvPacketCount++;
			CopyMemory(cbDataBuffer,m_cbRecvBuf,wPacketSize);
			m_wRecvSize-=wPacketSize;
			MoveMemory(m_cbRecvBuf,m_cbRecvBuf+wPacketSize,m_wRecvSize);

			//��������
			WORD wRealySize=CrevasseBuffer(cbDataBuffer,wPacketSize);
			ASSERT(wRealySize>=sizeof(CMD_Head));

			//��������
			WORD wDataSize=wRealySize-sizeof(CMD_Head);
			void * pDataBuffer=cbDataBuffer+sizeof(CMD_Head);
			CMD_Command Command=((CMD_Head *)cbDataBuffer)->CommandInfo;

			//�ں�����
			if (Command.wMainCmdID==MDM_KN_COMMAND)
			{
				switch (Command.wSubCmdID)
				{
				case SUB_KN_DETECT_SOCKET:	//������
					{
						//��������
						SendData(MDM_KN_COMMAND,SUB_KN_DETECT_SOCKET,pDataBuffer,wDataSize);
						break;
					}
				}
				continue;
			}

			//��������
			bool bSuccess=m_pITCPSocketSink->OnEventTCPSocketRead(m_wSocketID,Command,pDataBuffer,wDataSize);
			if (bSuccess==false) throw TEXT("�������ݰ�����ʧ��");
		};
	}
	catch (...) 
	{ 
		CloseSocket(); 
	}

	return 1;
}

//����ر�
LRESULT CTCPSocket::OnSocketNotifyClose(WPARAM wParam, LPARAM lParam)
{
	//m_cbSocketStatus=SHUT_REASON_NORMAL;
	CloseSocket();
	return 1;
}

//SOCKET ��Ϣ�������
LRESULT	CTCPSocket::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:	//��������
		{ 
			return OnSocketNotifyConnect(wParam,lParam); 
		}
	case FD_READ:		//���ݶ�ȡ
		{ 
			return OnSocketNotifyRead(wParam,lParam); 
		}
	case FD_CLOSE:		//����ر�
		{ 
			return OnSocketNotifyClose(wParam,lParam);	
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

//����������
DECLARE_CREATE_MODULE(TCPSocket)
/*extern "C" __declspec(dllexport) void * __cdecl CreateTCPSocket(const GUID & Guid, DWORD dwInterfaceVer)
{
	//��������
	CTCPSocket * pTCPSocket=NULL;
	try
	{
		pTCPSocket=new CTCPSocket();
		if (pTCPSocket==NULL) throw TEXT("����ʧ��");
		void * pObject=pTCPSocket->QueryInterface(Guid,dwInterfaceVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		return pObject;
	}
	catch (...) {}

	//�������
	SafeDelete(pTCPSocket);
	return NULL;
}*/

//////////////////////////////////////////////////////////////////////////
