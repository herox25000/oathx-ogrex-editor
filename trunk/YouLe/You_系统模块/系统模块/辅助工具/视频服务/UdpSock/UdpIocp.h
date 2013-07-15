#pragma once
#include "..\Include\SocketBase.h"
#include "..\Include\Common.h"

#include <Queue>
#include <vector>
using namespace std;
typedef vector<HANDLE> HANDLE_VECTOR;

//�����־
#define PACKET_START1		0XAA
#define PACKET_START2		0XBB
#define PACKET_END1			0XBB
#define PACKET_END2			0XAA

#pragma pack(1)
typedef struct _CHECK_SUM
{
	WORD Head;
	WORD Length;
	char Data;
}CHECK_SUM, *PCHECK_SUM;
#pragma pack()

class CUdpSocket : public CSocketBase
{
protected:
	int m_Sid;
	sockaddr_in m_FromAddr;

	WSAOVERLAPPED m_RecvOverlapped; //�����¼��ṹ
	WSAOVERLAPPED m_SendOverlapped; //�����¼��ṹ
public:
	CUdpSocket(void);
	virtual ~CUdpSocket(void);

	virtual int Create( int type, int protocol, int mode=0 );
	// ����Socket
	int Create( int id=0 );

	int GetSocketID() { return m_Sid; }; //�õ�ID

	virtual void Init( LPVOID p ){}; //��ʼ��
	virtual void ReceivedData( int length ); //�������ݴ���
	virtual BOOL CheckSum( int length ); //�����
	virtual int Recv(); //����
	virtual int Send( char* pBuf, long length, LPCTSTR lpTo=NULL, unsigned int Port=0, int dwFlag=0  ); //����
};

typedef queue<CUdpSocket*> QUEUE_RECV;
class CUdpIocp
{
protected:
	DWORD m_dwNumberOfWorkers; //�����߳���
	DWORD m_dwConcurrency; //cpu��
	HANDLE_VECTOR m_ThreadHandleVector;
	QUEUE_RECV m_QueueRecv;
public:
	HANDLE m_hServerIOCPort; //�ⲿ��ɶ˿ھ��
	int m_ServerSocketSize; //����
	CUdpSocket **m_pSocketArray; //��̬Socket����ָ��
public:
	CUdpIocp(void);
	virtual ~CUdpIocp(void);
	// ��ʼ��
	int Init( int ServerSocketSize=1, int WorkerNum=0 );
	void Release();

	//��ʼ��socket
	template <typename T>
	void CreateSocket( int port )
	{
		for( int i=0;i<m_ServerSocketSize;i++ )
		{
			m_pSocketArray[i] = (CUdpSocket *)new T();
			if( m_pSocketArray[i] )
			{
				m_pSocketArray[i]->Init( this );
				m_pSocketArray[i]->Create( i );
				m_pSocketArray[i]->Listen( port );
				Associate( m_pSocketArray[i], m_hServerIOCPort );
				//PushSocket( m_pSocketArray[i] );
				m_pSocketArray[i]->Recv();
			}
		}
		//Recv();
	};

	//��ɶ˿ں�ID��
	bool Associate(CUdpSocket* pSocket, HANDLE hPort);
	//ѹ�����
	void PushSocket( CUdpSocket* p );
	//����
	void Send( char* Buf, int len, char* IP, unsigned int Port );
	CUdpSocket* GetActiveSocket();
	CUdpSocket* GetSocket( int i );
	// ����
	void Recv(void);
	// ���������߳�
	void CreateReceiveWorkerThread( int WorkerNum=0 );
};