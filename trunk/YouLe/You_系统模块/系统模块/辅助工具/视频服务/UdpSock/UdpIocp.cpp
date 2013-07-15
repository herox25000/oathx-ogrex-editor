#include "StdAfx.h"
#include "UdpIocp.h"

//�¼�
#define OVL_RECEIVE			0X01 //����
#define OVL_SEND			0X02 //����
#define OVL_CLOSE			0X03 //�ر�

DWORD WINAPI ReceiveWorkerThread(LPVOID lp);

CUdpSocket::CUdpSocket(void)
{
	m_Sid = 0;
	ZeroMemory( &m_RecvOverlapped, sizeof(m_RecvOverlapped) );
	ZeroMemory( &m_SendOverlapped, sizeof(m_SendOverlapped) );
	pRecvOvl = &m_RecvOverlapped;
	pSendOvl = &m_SendOverlapped;

	pRecvOvl->Offset = OVL_RECEIVE; //�����¼�
	pSendOvl->Offset = OVL_SEND;
}

CUdpSocket::~CUdpSocket(void)
{
}

void CUdpSocket::ReceivedData( int length )
{
	//��鳤��
	if(!length)
		return; //���ش���
}

BOOL CUdpSocket::CheckSum( int length )
{
	if( length<=6 )
		return FALSE;
	PCHECK_SUM pCheckSum = (PCHECK_SUM)m_pRecvBuff;
	if( pCheckSum->Head != ((DWORD)PACKET_START2<<8) + PACKET_START1 )
		return FALSE;
	if( pCheckSum->Length+6 != length )
		return FALSE;
	if( *PWORD(&m_pRecvBuff[pCheckSum->Length+4]) != ((DWORD)PACKET_END2<<8) + PACKET_END1 )
		return FALSE;
	return TRUE;
}

int CUdpSocket::Recv()
{
	return CSocketBase::Recv( (sockaddr*)&m_FromAddr );
}

int CUdpSocket::Send( char* pBuf, long length, LPCTSTR lpTo, unsigned int Port, int dwFlag )
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
	int index = 0;
	//�����ʽ
	pTBuf[index++] = (BYTE)PACKET_START1;
	pTBuf[index++] = (BYTE)PACKET_START2;
	*PWORD( &pTBuf[index] ) = (WORD)length;
	index += 2;
	memcpy( pTBuf+index, pBuf, length );
	index += length;
	pTBuf[index++] = (BYTE)PACKET_END1;
	pTBuf[index++] = (BYTE)PACKET_END2;

	Buf.buf = pTBuf;
	Buf.len = index;

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

int CUdpSocket::Create( int type, int protocol, int mode )
{
	return CSocketBase::Create( type, protocol, mode );
}

int CUdpSocket::Create( int id )
{
	m_Sid = id;
	//��ʼ��socket
	return CSocketBase::Create( SOCK_DGRAM, IPPROTO_UDP );
//	m_Socket = WSASocket( AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, NULL, WSA_FLAG_OVERLAPPED );
//	m_Socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
//	if( m_Socket == INVALID_SOCKET )
//		return WSAGetLastError(); //���ش������

//	return 0;
}

CUdpIocp::CUdpIocp(void)
{
	m_dwNumberOfWorkers = 0; //�����߳���
	m_dwConcurrency = 0; //cpu��
	m_ServerSocketSize = 0;
	m_hServerIOCPort = NULL;
	
	m_ThreadHandleVector.reserve( 1 );
	
	m_pSocketArray = NULL;
}

CUdpIocp::~CUdpIocp(void)
{
	Release();
}

int CUdpIocp::Init( int ServerSocketSize, int WorkerNum )
{
	//��ʼ��ID
	int i;
	m_ServerSocketSize = ServerSocketSize;

	m_pSocketArray = new CUdpSocket* [ServerSocketSize];
	for( i = 0; i<ServerSocketSize; i++ )
		m_pSocketArray[i] = NULL;

	//�����ⲿ�����߳�
	CreateReceiveWorkerThread(WorkerNum);

	return 0;
}

void CUdpIocp::Release()
{
	int i;
	//�ͷ��߳�
	for( i=0; i<(int)m_ThreadHandleVector.size();i++ )
	{
		TerminateThread( m_ThreadHandleVector[i], 0 );
	}
	m_ThreadHandleVector.clear();
	//�ͷ�Socket
	if( m_pSocketArray )
	{
		for( i=0;i<m_ServerSocketSize;i++ )
			delete m_pSocketArray[i];
		delete[] m_pSocketArray;
		m_pSocketArray = NULL;
	}
	//�رվ��
	if( m_hServerIOCPort )
	{
		CloseHandle( m_hServerIOCPort );
		m_hServerIOCPort = NULL;
	}
	m_ServerSocketSize = 0;
}

//��ɶ˿ں�ID��
bool CUdpIocp::Associate(CUdpSocket* pSocket, HANDLE hPort)
{
	//�����ɶ˿�
	if (!hPort) 
	{
		return FALSE; //���ش���
	}
	
	//ID����ɶ˿ڰ�
	HANDLE hTemp;
	hTemp = CreateIoCompletionPort( pSocket->GetSocketHandle(), hPort, (DWORD)pSocket->GetSocketID(), 1/*m_dwConcurrency*/ );

	//����
	return (hTemp == hPort);
}

void CUdpIocp::PushSocket( CUdpSocket* p )
{
	m_QueueRecv.push( p );
}

CUdpSocket* CUdpIocp::GetActiveSocket()
{
	for( int i=0; i<m_ServerSocketSize; i++ )
	{
		if( m_pSocketArray[i]!=NULL )
		{
			return m_pSocketArray[i];
		}
	}
	return NULL;
}

CUdpSocket* CUdpIocp::GetSocket( int i )
{
	if( i>=0 && i<m_ServerSocketSize )
	{
		if( m_pSocketArray[i]!=NULL )
		{
			return m_pSocketArray[i];
		}
	}
	return NULL;
}

//����
void CUdpIocp::Send( char* Buf, int len, char* IP, unsigned int Port )
{
	for( int i=0; i<m_ServerSocketSize; i++ )
	{
		if( m_pSocketArray[i]!=NULL )
		{
			m_pSocketArray[i]->Send( Buf, len, IP, Port );
			break;
		}
	}
}

// ����
void CUdpIocp::Recv(void)
{
	while( m_QueueRecv.empty() )
	{
		Sleep( 1 );
	}
	CUdpSocket* pUdpSocket = m_QueueRecv.front();
	m_QueueRecv.pop();
	pUdpSocket->Recv();
}

void CUdpIocp::CreateReceiveWorkerThread( int WorkerNum )
{
	SYSTEM_INFO SystemInfo; //ϵͳ��Ϣ
	// �����߳�Ȩ�� 15:��
//	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	// �õ�ϵͳ��Ϣ
	GetSystemInfo ( &SystemInfo );
	//�Ƿ��Զ�����ʹ����Դ
	if( !WorkerNum )
		//CPU��2��,�����Ż�
		m_dwNumberOfWorkers = 2 * SystemInfo.dwNumberOfProcessors;
	else
		//�û�����
		m_dwNumberOfWorkers = WorkerNum;
	//����CPU��
	m_dwConcurrency = SystemInfo.dwNumberOfProcessors;

	//�����ⲿ��ɶ˿�
	m_hServerIOCPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, m_dwNumberOfWorkers );

	HANDLE tHandle;
	//�����ڲ��߳�
	for(int i = 0; i < (int)m_dwNumberOfWorkers; i++)
	{
		tHandle = CreateThread(NULL,0,ReceiveWorkerThread,(LPVOID)this,0,NULL);
		m_ThreadHandleVector.push_back( tHandle );
		//SetThreadPriority( tHandle, THREAD_PRIORITY_TIME_CRITICAL);
	}
}

//�ⲿ���������߳�
DWORD WINAPI ReceiveWorkerThread(LPVOID lp)
{
	CUdpIocp* pUdpIocp = (CUdpIocp*)lp;
	BOOL	bRet = 0; //����ֵ
	DWORD	nbytes = 0; //���ش�С
	DWORD	WorkIndex = 0; //ID
	LPOVERLAPPED	pOvl = NULL; //���ؽṹ
	CUdpSocket*	pSocket = NULL; //socket
	while (1)
	{
		//������ɶ˿�,�����ݲŻ���������
		bRet = GetQueuedCompletionStatus(pUdpIocp->m_hServerIOCPort,&nbytes,
										&WorkIndex,&pOvl,INFINITE);
		//����Ϣ�ж��Ƿ���ȷ
		if(bRet || pOvl)
		{
			if(bRet) //�����Ϣ������ȷ
			{
				//����Ƿ񳬹��������
				if( WorkIndex > (DWORD)pUdpIocp->m_ServerSocketSize )
					goto loop_pass; //����

				//�õ�Ҫ�����Socket
				pSocket = (CUdpSocket*)pUdpIocp->m_pSocketArray[WorkIndex];
				//���pSocket�Ƿ�Ϊ��
				if( !pSocket )
					goto loop_pass; //����
				//�ж����ĸ���Ϣ
				switch( pOvl->Offset )
				{
				case OVL_RECEIVE: //����
					//pUdpIocp->Recv();
					//����Ƿ����
					if( !nbytes ) 
					{
						//pSocket->Close(); //�ر�
						pSocket->Recv(); //��������
						//pUdpIocp->PushSocket( pSocket );
						goto loop_pass; //����
					}
					//�ָ����������
					pSocket->m_nPending = 0;
					pSocket->m_nWouldblock = 0;
					pSocket->ReceivedData( (int)nbytes ); //������յ�����
					pSocket->Recv(); //��������
					//pUdpIocp->PushSocket( pSocket );
					break;
				case OVL_SEND: //����
					//�ָ����������
					pSocket->m_nPending = 0;
					pSocket->m_nWouldblock = 0;
					break;
				case OVL_CLOSE: //�ر�
					//pSocket->Close(); //�ر�
					break;
				default:
					break;
				}
			}
			else
			{
				if( pOvl ) //�ر�
				{
					//����Ƿ񳬹��������
					if( WorkIndex > (DWORD)pUdpIocp->m_ServerSocketSize )
						goto loop_pass; //����
					//�õ�Ҫ�����Socket
					pSocket = (CUdpSocket*)pUdpIocp->m_pSocketArray[WorkIndex];
					//���pSocket�Ƿ�Ϊ��
					if( !pSocket )
						goto loop_pass; //����
					//�ж����ĸ���Ϣ
					switch( pOvl->Offset )
					{
					case OVL_RECEIVE: //����
						//pUdpIocp->Recv();
						//����Ƿ����
						if( !nbytes ) 
						{
							pSocket->Recv(); //��������
							//pUdpIocp->PushSocket( pSocket );
							goto loop_pass; //����
						}
						//�ָ����������
						pSocket->m_nPending = 0;
						pSocket->m_nWouldblock = 0;
						//pSocket->ReceivedData( (int)nbytes ); //������յ�����
						pSocket->Recv(); //��������
						//pUdpIocp->PushSocket( pSocket );
						break;
					case OVL_SEND: //����
						//�ָ����������
						pSocket->m_nPending = 0;
						pSocket->m_nWouldblock = 0;
						break;
					case OVL_CLOSE: //�ر�
						//pSocket->Close(); //�ر�
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			OutInfo( "ERROR:GetQueuedCompletionStatus()" );
		}
loop_pass:
		continue; //����ѭ��
	}
	return 1; //����1
}