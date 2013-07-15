// VideoServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyUserManage.h"
#include "..\Include\Common.h"
#include "..\Include\IniFile.h"
#include "UserProcess.h"

extern ROOM_ID_LIST m_RoomIDList;
extern CRITICAL_SECTION g_CheckCritical; //�ٽ����

int _tmain(int argc, _TCHAR* argv[])
{
	//�����
	if( CheckInstance( _T("VideoServer") ) )
		exit(0);
	
	InitializeCriticalSection( &g_CheckCritical );
	//�����ļ�
	TCHAR path[MAX_PATH];
	GetProgPath( path, _T("VideoServer.ini")  );
	CIniFile IniFile;
	IniFile.Load( path );

	//�����˿�
	unsigned int Port = IniFile.GetInt( _T("SETUP"), _T("PORT") );


	CUdpManage UdpManage;
	UdpManage.Init( 1, 1 );
	UdpManage.CreateSocket<CMyUserManage>( Port );

	//��Ϣѭ��
	MSG msg;
	while(true)
	{
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	m_RoomIDList.DeleteAllData();
	DeleteCriticalSection( &g_CheckCritical ); //ɾ���ٽ����

	return 0;
}

