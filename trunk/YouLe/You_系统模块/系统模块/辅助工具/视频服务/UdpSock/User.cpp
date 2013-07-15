#include "StdAfx.h"
#include "UdpManage.h"
#include "UserManage.h"
#include "User.h"

//�����С
#define SOCKET_BUFF_SIZE	(1024*16) //Socket��С
#define MAX_PACKET_SIZE		(1024*8) //�����С

CUser::CUser(void)
{
	SetTime();
	InitializeCriticalSection( &m_Critical );
	ZeroMemory( m_IP, sizeof(m_IP) );
	m_Port = 0;
	m_pBuffer = new CCircularBuffer(SOCKET_BUFF_SIZE);
	m_pBuffer->SetEmpty();
}

CUser::~CUser(void)
{
	DeleteCriticalSection( &m_Critical ); //ɾ���ٽ����
	delete m_pBuffer;
}

void CUser::Init( CUserManage* pUserManage, char* IP, unsigned int Port )
{
	m_pUserManage = pUserManage;
	strcpy( m_IP, IP );
	m_Port = Port;
}

BOOL CUser::PullOutCore(char*& data, int& length)
{
	Lock();
	int len = m_pBuffer->GetValidCount();

	//��鳤��
	if(len <= 0) 
	{
        UnLock();
		return FALSE;
	}

	//������ʱ����
	BYTE* pTmp = new BYTE[len];
	//ȡ����
	m_pBuffer->GetData((char*)pTmp, len);
	
	BOOL foundCore = FALSE; //���ݱ�ʾ -���������=True
	
	PCHECK_SUM pCheckSum = (PCHECK_SUM)pTmp;
	if( pCheckSum->Length+6<=len )
	{
		data = new char[pCheckSum->Length+1];
		length = pCheckSum->Length;
		CopyMemory((void *)data, (const void *)&pCheckSum->Data, length);
		data[pCheckSum->Length]=0;
		m_pBuffer->HeadIncrease(pCheckSum->Length+6);
		foundCore = TRUE;
	}
	UnLock();
	delete pTmp; //ɾ������
	return foundCore;
}

void CUser::Send( char* Buf, int len, LPCTSTR lpTo, unsigned int Port )
{
	if( lpTo == NULL )
	{
		lpTo = m_IP;
	}
	if( Port == 0 )
	{
        Port = m_Port;
	}
	m_pUserManage->Send( Buf, len, lpTo, Port );
}

void CUser::PutData( char* pData, int len )
{
	SetTime();
    Lock();
	m_pBuffer->PutData( pData, len );
    UnLock();	
}

void CUser::Lock()
{
	EnterCriticalSection( &m_Critical ); //Lock
}

void CUser::UnLock()
{
	LeaveCriticalSection( &m_Critical ); //UnLock
}

void CUser::Parsing( char* pData, int length )
{
}

BOOL CUser::Check( DWORD Time )
{
	char Tmp[2];
	ZeroMemory( Tmp, sizeof(Tmp) );
	Send( Tmp, 2 );
	return Time>CheckTime?TRUE:FALSE;
}