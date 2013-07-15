#ifndef GLOBAL_FRAME_HEAD_FILE
#define GLOBAL_FRAME_HEAD_FILE

#pragma once

#include "GlobalDef.h"

//////////////////////////////////////////////////////////////////////////
//�궨��

//��Ϸ״̬
#define GS_FREE							0								//����״̬
#define GS_PLAYING						100								//��Ϸ״̬

//////////////////////////////////////////////////////////////////////////
//IPC �����¼�

#define IPC_MAIN_SOCKET					1								//������Ϣ

#define IPC_SUB_SOCKET_SEND				1								//���緢��
#define IPC_SUB_SOCKET_RECV				2								//�������

//IPC ������ṹ
struct IPC_SocketPackage
{
	CMD_Command							Command;						//������Ϣ
	BYTE								cbBuffer[SOCKET_PACKAGE];		//���ݻ���
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONFIG					2								//������Ϣ

#define IPC_SUB_SERVER_INFO				1								//������Ϣ
#define IPC_SUB_COLUMN_INFO				2								//�б���Ϣ

//��Ϸ��Ϣ
struct IPC_GF_ServerInfo
{
	DWORD								dwUserID;						//�û� I D
	WORD								wTableID;						//���Ӻ���
	WORD								wChairID;						//���Ӻ���
	WORD								wKindID;						//���ͱ�ʶ
	WORD								wServerID;						//�����ʶ
	WORD								wGameGenre;						//��Ϸ����
	WORD								wChairCount;					//������Ŀ
	TCHAR								szKindName[KIND_LEN];			//��������
	TCHAR								szServerName[SERVER_LEN];		//��������
	tagOptionBuffer						OptionBuffer;					//������Ϣ
};

//////////////////////////////////////////////////////////////////////////
//IPC �û���Ϣ

#define IPC_MAIN_USER					3								//�û���Ϣ

#define IPC_SUB_USER_COME				1								//�û���Ϣ
#define IPC_SUB_USER_STATUS				2								//�û�״̬
#define IPC_SUB_USER_SCORE				3								//�û�����
#define IPC_SUB_GAME_START				4								//��Ϸ��ʼ
#define IPC_SUB_GAME_FINISH				5								//��Ϸ����

//�û�״̬
struct IPC_UserStatus
{
	DWORD								dwUserID;						//�û� I D
	WORD								wNetDelay;						//������ʱ
	BYTE								cbUserStatus;					//�û�״̬
};

//�û�����
struct IPC_UserScore
{
	DWORD								dwUserID;						//�û� I D
	tagUserScore						UserScore;						//�û�����
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONCTROL				4								//������Ϣ

#define IPC_SUB_START_FINISH			1								//�������
#define IPC_SUB_CLOSE_FRAME				2								//�رտ��

//////////////////////////////////////////////////////////////////////////
//����������

#define MDM_GF_GAME						100								//��Ϸ��Ϣ
#define MDM_GF_FRAME					101								//�����Ϣ

#define SUB_GF_INFO						1								//��Ϸ��Ϣ
#define SUB_GF_USER_READY				2								//�û�ͬ��
#define SUB_GF_LOOKON_CONTROL			3								//�Թۿ���

#define SUB_GF_OPTION					100								//��Ϸ����
#define SUB_GF_SCENE					101								//������Ϣ

#define SUB_GF_USER_CHAT				200								//�û�����

#define SUB_GF_MESSAGE					300								//ϵͳ��Ϣ

//�汾��Ϣ
struct CMD_GF_Info
{
	BYTE								bAllowLookon;					//�Թ۱�־
};

//��Ϸ����
struct CMD_GF_Option
{
	BYTE								bGameStatus;					//��Ϸ״̬
	BYTE								bAllowLookon;					//�����Թ�
};

//�Թۿ���
struct CMD_GF_LookonControl
{
	DWORD								dwUserID;						//�û���ʶ
	BYTE								bAllowLookon;					//�����Թ�
};

//����ṹ
struct CMD_GF_UserChat
{
	WORD								wChatLength;					//��Ϣ����
	COLORREF							crFontColor;					//��Ϣ��ɫ
	DWORD								dwSendUserID;					//�����û�
	DWORD								dwTargetUserID;					//Ŀ���û�
	TCHAR								szChatMessage[MAX_CHAT_LEN];	//������Ϣ
};

//��Ϣ����
#define SMT_INFO						0x0001							//��Ϣ��Ϣ
#define SMT_EJECT						0x0002							//������Ϣ
#define SMT_GLOBAL						0x0004							//ȫ����Ϣ
#define SMT_CLOSE_GAME					0x1000							//�ر���Ϸ

//��Ϣ���ݰ�
struct CMD_GF_Message
{
	WORD							wMessageType;						//��Ϣ����
	WORD							wMessageLength;						//��Ϣ����
	TCHAR							szContent[1024];					//��Ϣ����
};

//////////////////////////////////////////////////////////////////////////

//�����ڴ涨��
struct tagShareMemory
{
	WORD								wDataSize;						//���ݴ�С
	HWND								hWndGameFrame;					//��ܾ��
	HWND								hWndGamePlaza;					//�㳡���
	HWND								hWndGameServer;					//������
};

//////////////////////////////////////////////////////////////////////////

#endif