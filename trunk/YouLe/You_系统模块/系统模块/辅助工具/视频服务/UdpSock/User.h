#pragma once

#include "..\Include\CircularBuffer.h"
#include "..\Include\GameDefine.h"

#define OUT_TIME 15000 //15��

class CUserManage;
class CUser
{
protected:
	DWORD CheckTime;
	CUserManage* m_pUserManage;
	char m_IP[IP_LEN];
	unsigned int m_Port;
	CCircularBuffer* m_pBuffer; //��������
	CRITICAL_SECTION m_Critical; //�ٽ����
public:
	CUser(void);
	virtual ~CUser(void);

	void Init( CUserManage* pUserManage, char* IP, unsigned int Port );
	BOOL PullOutCore(char*& data, int& length);
	virtual void Send( char* Buf, int len, LPCTSTR lpTo = NULL, unsigned int Port = 0 );
	virtual void Parsing( char* pData, int length );
	void PutData( char* pData, int len );
	void Lock();
	void UnLock();
	void SetTime(){ CheckTime = GetTickCount() + OUT_TIME; };
	virtual BOOL Check( DWORD Time );
};
