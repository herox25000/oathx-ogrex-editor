#pragma once

#include "UdpIocp.h"
#include "User.h"

#include <Queue>
typedef queue<CUser*> EVENT_QUEUE; //�¼���ջ

//udp������
class CUdpManage : public CUdpIocp
{
public:
	CUdpManage(void);
	virtual ~CUdpManage(void);

	EVENT_QUEUE m_EventQueue; //�¼�����
	HANDLE m_hWorkerIOCPort; //�¼���ɶ˿ھ��

	int Init( int ServerSocketSize=1, int WorkerNum=0 ); //��ʼ��

	//�����������
	void CreateWorkerThread( int WorkerNum=0 );
	void SendAllUser( char* Tmp, int len, char* lpTo, UINT port );
};
