#pragma once
#include "..\Include\StlMap.h"
#include "windows.h"

//�ֽں���
typedef enum
{
	T_BYTE = 0x01,
	T_WORD,
	T_DWORD,
	T_DATA,
	T_LEN_DATA
};

typedef CSTLMap<WORD,string> MAP_PACKET_CMD; //���ṹ����

//����ṹ��
class CPacket
{
protected:
	MAP_PACKET_CMD m_PacketCmd; //�ṹ����
public:
	CPacket(void);
	virtual ~CPacket(void);

	virtual void AddPacket( WORD Packet, ... ); //��ӷ��
	virtual int GetPacket( char* pBuffer, int length, WORD Packet, ... ); //�õ����
	virtual	int GetValue( const char* pBuffer, int length, WORD Packet, ... ); //�õ�ֵ
};
