#pragma once

#include "UdpManage.h"
#include "..\Include\STLMap.h"
#include "User.h"
typedef CSTLMap<string,CUser> USER_MAP;

class CUserManage : public CUdpSocket
{
public:
	CUserManage(void);
	virtual ~CUserManage(void);

	static USER_MAP m_UserMap; //�û�����
	CUdpManage* m_pUdpManage;
	static HANDLE m_CheckThreadHandle;

	virtual void Init( LPVOID p ); //��ʼ��
	virtual void ReceivedData( int length );
	void CreateCheckUserThread(void);
	virtual void CheckUser(DWORD Time);
	virtual void SendAllUser( char* Buffer, int len );
};
