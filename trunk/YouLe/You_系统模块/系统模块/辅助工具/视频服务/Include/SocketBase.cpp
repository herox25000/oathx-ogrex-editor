#include "StdAfx.h"
#include "SocketBase.h"
//#include <ws2tcpip.h>

CSocketBase::CSocketBase(void)
{
	pSendOvl = NULL;
	pRecvOvl = NULL;
	m_Socket = INVALID_SOCKET;
	m_SocketType = 0;
	m_nSocketErr = 0;
	m_nPending = 0;
	m_nWouldblock = 0;
	WSADATA WSAData;
	WSAStartup( MAKEWORD( 2, 2 ), &WSAData );
}

CSocketBase::~CSocketBase(void)
{
	Close();
	WSACleanup();
}

//����Socket
int CSocketBase::Create( int type, int protocol, int mode )
{
	//��ʼ��socket
	m_Socket = socket( AF_INET, type/*SOCK_DGRAM*/, protocol/*IPPROTO_UDP*/ );
	if( m_Socket == INVALID_SOCKET )
		return WSAGetLastError(); //���ش������
/*
	BOOL bop = true;
	if( setsockopt( m_Socket, IPPROTO_IP, IP_HDRINCL, (char*)&bop, sizeof(bop) ) == SOCKET_ERROR )
		return WSAGetLastError(); //���ش������
*/

	if( mode )
	{
		int iMode = 1;
		if( SOCKET_ERROR == ioctlsocket( m_Socket, FIONBIO, (u_long FAR*) &iMode ) )
		{
			return WSAGetLastError(); //���ش������
		}
	}

	return 0;
}

void CSocketBase::Set( SOCKET s, int type )
{
	if( s == INVALID_SOCKET )
		return;
	m_Socket = s;
	m_SocketType = type;
}

// �ͷ�
void CSocketBase::Close(void)
{
	if( m_Socket!=INVALID_SOCKET )
	{
		shutdown( m_Socket, SD_BOTH );
		closesocket( m_Socket );
		m_Socket = INVALID_SOCKET;
	}
}

// �󶨶˿�
int CSocketBase::Bind( int port )
{
	if( m_Socket == INVALID_SOCKET )
		return -1;

	sockaddr_in addr; //��ַ�ṹ
	//bing��ַ�ṹ
	ZeroMemory( &addr, sizeof(addr) );
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	addr.sin_port			= htons(port);
	
	//������socket �󶨶˿�
/*	int opt = 1; //������
	if( setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR )
	{
		return WSAGetLastError();
	}
*/
	//���ó�ʱʱ��
//	linger lingerOpt; //�ӳٲ�����
//	lingerOpt.l_onoff = 0;
//	lingerOpt.l_linger = 0;
//	setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (char *)&lingerOpt, sizeof(lingerOpt));
	
	//bing�˿�
	if ( bind( m_Socket, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
	{
		return WSAGetLastError(); //���ش������
	}

	return 0;
}

// �����˿�
int CSocketBase::Listen(int port)
{
	int Ret = Bind( port );
	if( Ret )
		return Ret;

	sockaddr addr;
	int len = sizeof(addr);
	ZeroMemory( &addr, sizeof(addr) );
	if( getsockname( m_Socket, &addr, &len ) )
//	if( getpeername( m_Socket, &addr, &len ) )
	{
		len = WSAGetLastError();
	}

	//htons
	m_Port = htons( ((sockaddr_in*)&addr)->sin_port );

	int socklen, err;
	//���ý��ջ���
	socklen = SOCKET_BUFF_SIZE*4;
	setsockopt( m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, sizeof(socklen));
	//�����ջ���
	len = sizeof(socklen);
	err = getsockopt( m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&socklen, &len);
	if (err == SOCKET_ERROR)
	{
		return FALSE;
	}
	//���÷��ͻ���
	socklen = SOCKET_BUFF_SIZE*4;
	setsockopt( m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, sizeof(socklen));
	//��鷢�ͻ���
	len = sizeof(socklen);
	err = getsockopt( m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&socklen, &len);
	if (err == SOCKET_ERROR)
	{
		return FALSE;
	}

	if( m_SocketType == SOCK_STREAM )
	{
		//�����TCP�ͼ���
		Ret = listen( m_Socket, 5 );
		if( Ret == SOCKET_ERROR )
		{
			Ret = WSAGetLastError();
			//Close();
		}
	}

	return Ret;
}

//��������
CSocketBase* CSocketBase::Accept( sockaddr * paddr, int * plen )
{
	if( m_Socket == INVALID_SOCKET )
		return NULL;

	//��������
	ZeroMemory( paddr, sizeof(sockaddr) );
	*plen = sizeof(sockaddr);
	SOCKET s = accept( m_Socket, paddr, plen );
	if( s!=INVALID_SOCKET )
	{
		CSocketBase* pSocketBase = new CSocketBase;
		pSocketBase->Set( s, SOCK_STREAM );
		return pSocketBase;
	}
	return NULL;
}

//����
int CSocketBase::Connect( LPCTSTR lpszHostAddress, unsigned int nHostPort )
{
	if( m_Socket == INVALID_SOCKET )
		return -1;

	sockaddr_in addr; //��ַ�ṹ
	//��ʼ����ַ
	ZeroMemory( &addr, sizeof(addr) );
	addr.sin_family = AF_INET;
#ifdef _UNICODE
	USES_CONVERSION;
	addr.sin_addr.s_addr = inet_addr(W2A(lpszHostAddress));
#else
	addr.sin_addr.s_addr = inet_addr(lpszHostAddress);
#endif
	addr.sin_port = htons(nHostPort);

	//����
	int Ret = connect( m_Socket,(struct sockaddr *)&addr,sizeof(addr) );
	//��鷵��ֵ
	if ( Ret == SOCKET_ERROR )
	{
		Ret = WSAGetLastError();
		Close();
		return FALSE;
	}

	return Ret;
}

//��������
int CSocketBase::Recv( sockaddr* lpFrom )
{
	int Ret; //����ֵ
	sockaddr addr;
	int len = 0;

	if( m_Socket == INVALID_SOCKET )
		return -1;

	//��ջ���
	ZeroMemory( m_pRecvBuff, MAX_PACKET_SIZE );
		
	WSABUF Buf; //���ջ���
	Buf.len = MAX_PACKET_SIZE; //�����С
	Buf.buf = m_pRecvBuff; //����

	DWORD dwRecvSize=0, dwFlag=0;

	//����
	if( m_SocketType == SOCK_STREAM )
	{
		Ret = WSARecv( m_Socket, &Buf, 1, &dwRecvSize, &dwFlag, pRecvOvl, NULL );
	}
	else
	{
		if( lpFrom==NULL )
		{
			lpFrom = &addr;
		}

		len = sizeof(addr);
RECV_LOOP:
		Ret = WSARecvFrom( m_Socket, &Buf, 1, &dwRecvSize, &dwFlag, lpFrom, &len, pRecvOvl, NULL );
	}

	//�жϷ���ֵ
 	if ( Ret == SOCKET_ERROR )
	{
		Ret = WSAGetLastError(); //�õ�����
		switch( Ret )
		{
		case WSAECONNRESET:
			goto RECV_LOOP;
			break;
		case WSA_IO_PENDING:
			//�ۼƴ���
			m_nPending++; 
			//����3�ν�������
			//if( m_nPending > 3 )
				//Close();
			break;
		case WSAEWOULDBLOCK:
			//�ۼƴ���
			m_nWouldblock++;
			//����3�ν�������
			//if( m_nWouldblock > 3 )
				//Close();
			break;
		default:
			//�ۼƴ���
			m_nSocketErr++;
			//����3�ν�������
			//if( m_nSocketErr == 2 )
				//Close();
			break;
		}
	}

	return Ret;
}

//��������
int CSocketBase::Send( char* pBuf, long length, LPCTSTR lpTo, unsigned int Port, int dwFlag )
{
	int Ret; //����ֵ

	if( m_Socket == INVALID_SOCKET )
		return -1;

	//��鳤��
	if( length > MAX_PACKET_SIZE )
		return 0;

	WSABUF Buf; //���ջ���
	DWORD dwSentSize = 0;

	//����
	char pTBuf[MAX_PACKET_SIZE];
	//ZeroMemory( pTBuf, MAX_PACKET_SIZE );
	memcpy( pTBuf, pBuf, length );

	Buf.buf = pTBuf;
	Buf.len = length;

	if(pSendOvl)
		pSendOvl->OffsetHigh = Buf.len;
	//����
	if( m_SocketType == SOCK_STREAM )
	{
		Ret = WSASend( m_Socket, &Buf, 1, &dwSentSize, dwFlag, pSendOvl, NULL);
	}
	else
	{
		sockaddr_in addr; //��ַ�ṹ
		//��ʼ����ַ
		//ZeroMemory( &addr, sizeof(addr) );
		addr.sin_family = AF_INET;
#ifdef _UNICODE
		USES_CONVERSION;
		addr.sin_addr.s_addr = inet_addr(W2A(lpTo));
#else
		addr.sin_addr.s_addr = inet_addr(lpTo);
#endif
		addr.sin_port = htons(Port);

		Ret = WSASendTo( m_Socket, &Buf, 1, &dwSentSize, dwFlag, (sockaddr*)&addr, sizeof(addr), pSendOvl, NULL);
	}

	//�жϷ���ֵ
 	if ( Ret == SOCKET_ERROR )
	{
		Ret = WSAGetLastError(); //�õ�����
		switch( Ret )
		{
		case WSA_IO_PENDING:
			//�ۼƴ���
			m_nPending++; 
			//����3�ν�������
			if( m_nPending > 3 )
				//Close();
			break;
		case WSAEWOULDBLOCK:
			//�ۼƴ���
			m_nWouldblock++;
			//����3�ν�������
			if( m_nWouldblock > 3 )
				//Close();
			break;
		default:
			//�ۼƴ���
			m_nSocketErr++;
			//����3�ν�������
			if( m_nSocketErr == 2 )
				//Close();
			break;
		}
	}

	return Ret;
}