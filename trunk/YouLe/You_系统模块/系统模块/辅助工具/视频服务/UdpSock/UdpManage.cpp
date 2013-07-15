#include "StdAfx.h"
#include ".\udpmanage.h"

DWORD WINAPI WorkerThread(LPVOID lp);

CRITICAL_SECTION m_EventQueueCritical; //�ٽ����

CUdpManage::CUdpManage(void)
{
	m_hWorkerIOCPort = NULL;
	InitializeCriticalSection( &m_EventQueueCritical );
}

CUdpManage::~CUdpManage(void)
{
	if( m_hWorkerIOCPort )
		CloseHandle( m_hWorkerIOCPort );
	DeleteCriticalSection( &m_EventQueueCritical ); //ɾ���ٽ����
}

int CUdpManage::Init( int ServerSocketSize, int WorkerNum )
{
	int r = CUdpIocp::Init( ServerSocketSize, WorkerNum );

	//�����ⲿ��ɶ˿�
	m_hWorkerIOCPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );

	CreateWorkerThread( 4 );
	return r;
}

void CUdpManage::CreateWorkerThread( int WorkerNum )
{
	if( WorkerNum==0 )
        WorkerNum = 1;

	HANDLE tHandle;
	//�����ڲ��߳�
	for(int i = 0; i < (int)WorkerNum; i++)
	{
		tHandle = CreateThread(NULL,0,WorkerThread,(LPVOID)this,0,NULL);
		m_ThreadHandleVector.push_back( tHandle );
		//SetThreadPriority( tHandle, THREAD_PRIORITY_TIME_CRITICAL);
	}
}

DWORD WINAPI WorkerThread(LPVOID lp)
{
	CUdpManage* pUdpManage = (CUdpManage*)lp;
	CUser* pUser = NULL;
	
	LPOVERLAPPED	pOvl; //���ؽṹ
	BOOL	bRet; //����ֵ
	DWORD	nbytes; //���ش�С
	DWORD	WorkIndex; //ID
	char *pData = NULL;
	int len = 0; //����

	while (1)
	{
//		Sleep(1);
		//������ɶ˿�,�����ݲŻ���������
		bRet = GetQueuedCompletionStatus( pUdpManage->m_hWorkerIOCPort, &nbytes, &WorkIndex, &pOvl, INFINITE );

		if( pUdpManage->m_EventQueue.empty() )
			continue;

		EnterCriticalSection( &m_EventQueueCritical ); //Lock
		pUser = pUdpManage->m_EventQueue.front();
		pUdpManage->m_EventQueue.pop();
		LeaveCriticalSection( &m_EventQueueCritical );
		if( pUser )
		{
//			try
			{
				while (pUser->PullOutCore(pData, len))
				{
					if(pData)
					{
						//������
						pUser->Parsing( pData, len );
						delete pData; //ɾ������
						pData = NULL; //�ÿ�
					}
				}
			}
//			catch(...)
			{
			}
		}	
	}
	return 0;
}

void CUdpManage::SendAllUser( char* Tmp, int len, char* lpTo, UINT port )
{
	for( int i=0; i<m_ServerSocketSize; i++ )
	{
		if( m_pSocketArray[i]!=NULL )
		{
			m_pSocketArray[i]->Send( Tmp, len, lpTo, port );
		}
	}
}