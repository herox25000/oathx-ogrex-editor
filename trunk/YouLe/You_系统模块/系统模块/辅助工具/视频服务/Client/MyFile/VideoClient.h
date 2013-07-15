#pragma once

#include "MyUserManage.h"
#include "..\..\UdpSock\UserManage.h"
#include "OutMin.h"
#include "InMin.h"
#include "VideoWindow.h"

class CVideoClient
{
private:
	CUdpManage UdpManage;
	COutMin OutMin;
	CInMin InMin;
public:
	CVideoClient(void);
	virtual ~CVideoClient(void);
	CVideoWindow m_VideoWindow[10];

	void Init(void);
	void Release(void);

	DWORD m_Room;
	DWORD m_Desk;

	//��½
	BOOL Login( char* IP/*������IP*/, int Port/*�������˿�*/, DWORD RoomID, DWORD DeskID, DWORD Pos );
	void SendAllUser( char* Buffer, int len );
	void OutSound( char* pData, int len );
	void OutVideo( DWORD Pos, char* pData, int len );
	void SaveSoundData( char* Buffer, int len );
	void OutString( DWORD Pos, char* pchar );
	CUdpSocket* GetSocket(int i);
	void Quit();
	void SendDebugMsg(char* p);
};
