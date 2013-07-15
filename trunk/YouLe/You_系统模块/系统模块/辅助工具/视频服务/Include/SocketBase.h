#pragma once

#include <winsock2.h>
#pragma comment( lib, "ws2_32.lib" )

//�����С
#define SOCKET_BUFF_SIZE	(1024*16) //Socket��С
#define MAX_PACKET_SIZE		(1024*8) //�����С

//socket������
class CSocketBase
{
protected:
	SOCKET m_Socket;
	int m_Port;
	int m_SocketType;
	char m_pRecvBuff[SOCKET_BUFF_SIZE]; //���ջ���
	char m_pSendBuff[MAX_PACKET_SIZE]; //���ͻ���

public:
	LPWSAOVERLAPPED pRecvOvl;
	LPWSAOVERLAPPED pSendOvl;

	//���������
	short m_nSocketErr;
	short m_nPending;
	short m_nWouldblock;

public:
	CSocketBase(void);
	virtual ~CSocketBase(void);

	HANDLE GetSocketHandle() { return (HANDLE)m_Socket; };

	int GetPort(){ return m_Port; };
	// ����Socket
	virtual int Create( int type, int protocol=0, int mode=0 );
	// Socket
	void Set( SOCKET s, int type );
	// �ͷ�
	void Close(void);
	// �󶨶˿�
	int Bind( int port );
	// �����˿�
	int Listen( int port );
	//��������
	CSocketBase* Accept( sockaddr * paddr, int * plen );
	//����
	int Connect( LPCTSTR lpszHostAddress, unsigned int nHostPort );
	//����
	virtual int Recv( sockaddr* lpFrom=NULL );
	//����
	virtual int Send( char* pBuf, long length, LPCTSTR lpTo=NULL, unsigned int Port=0, int dwFlag=0  );
};
