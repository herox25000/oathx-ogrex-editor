#include "StdAfx.h"
#include ".\mypacket.h"

CMyPacket::CMyPacket(void)
{
	//�������
	AddPacket( PACKET_LOGIN, T_DWORD/*����ID*/, T_DWORD/*����ID*/, T_DWORD/*λ��*/, T_DWORD/*�ڲ�IP*/, T_DWORD/*�ڲ�PORT*/, NULL );
	AddPacket( PACKET_LOGIN_OK, T_DWORD/*IP*/, T_DWORD/*PORT*/, T_DWORD/*λ��*/, NULL );
	AddPacket( PACKET_LOGIN_ERR, T_DWORD/*�����*/, NULL );
	AddPacket( PACKET_QUIT, T_DWORD, NULL );
    AddPacket( PACKET_ADDCLIENT, T_DWORD/*�ⲿIP*/, T_DWORD/*�ⲿPORT*/, T_DWORD/*�ڲ�IP*/, T_DWORD/*�ڲ�PORT*/, T_DWORD/*λ��*/, NULL );
	AddPacket( PACKET_USER_CONNECT, T_DWORD/**/, NULL );
	AddPacket( PACKET_USER_CONNECT_OK, T_DWORD/**/, NULL );
	AddPacket( PACKET_USER_VEDIO, T_DWORD/*����*/, T_LEN_DATA/*����*/, NULL );
	AddPacket( PACKET_USER_VEDIO_OK, T_DWORD/*��־*/, T_DWORD/*����*/, NULL );
	AddPacket( PACKET_USER_VEDIO_NEW, T_DWORD/*��־*/, NULL );
	AddPacket( PACKET_USER_GET_NEW_VEDIO, T_DWORD/*����*/, NULL );
	AddPacket( PACKET_USER_GET_VEDIO, T_LEN_DATA/*����*/, NULL );
	AddPacket( PACKET_USER_VEDIO_ERR, T_LEN_DATA/*����*/, NULL );

	AddPacket( PACKET_USER_SOUND, T_DWORD/*����*/, T_LEN_DATA/*����*/, NULL );
	AddPacket( PACKET_USER_SOUND_OK, T_DWORD/*��־*/, T_DWORD/*����*/, NULL );
	AddPacket( PACKET_USER_SOUND_NEXT, T_DWORD/*��־*/, NULL );
	AddPacket( PACKET_USER_GET_SOUND, T_LEN_DATA/*����*/, NULL );
	AddPacket( PACKET_USER_SOUND_ERR, T_LEN_DATA/*����*/, NULL );

	AddPacket( PACKET_SWAP_CONNECT, T_DWORD/*����ID*/, T_DWORD/*����ID*/, T_DWORD/*λ��*/, T_DWORD/*����λ��*/, NULL );
}

CMyPacket::~CMyPacket(void)
{
}