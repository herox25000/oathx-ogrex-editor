#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
#define VER_IGameEventSink INTERFACE_VERSION(1,1)
static const GUID IID_IGameEventSink={0x9d49ab20,0x472c,0x4b3a,0x00bc,0xb4,0x92,0xfe,0x8c,0x41,0xcd,0xaa};
#else
#define VER_IGameEventSink INTERFACE_VERSION(1,1)
static const GUID IID_IGameEventSink={0x91cf29a0,0x04d3,0x48da,0x0083,0x36,0x64,0xb2,0xda,0x6a,0x21,0xdb};
#endif

interface IGameEventSink :public IUnknownEx
{
	//��Ϸ��ʼ
	virtual bool  OnEventGameStart(ITableFrame *pITableFrame, WORD wChairCount)=NULL;
	//��Ϸ����
	virtual bool  OnEventGameEnd(ITableFrame *pITableFrame,WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)=NULL;
	//�Ƿ�����뿪��λ 
	virtual bool  IsCanStanUp(IServerUserItem *pUserItem)=NULL;
	//��Ҷ��߻����� 
	virtual void  SetUserOffline(WORD wTableID,IServerUserItem *pUserItem, bool bOffline)=NULL;

	//�û�����
	virtual bool OnActionUserSitDown(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)=NULL;
	//�û�����
	virtual bool OnActionUserStandUp(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)=NULL;
	//�û�ͬ��
	virtual bool OnActionUserOnReady(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)=NULL;
};
//��Ϸ������
class CGameMatchSink : public IGameMatchSink,public ITableUserAction
{
	//��Ԫ����
	friend class CGameServiceManager;
	//��Ϸ����
protected:
	
	//������Ϣ
protected:
	
	//�ӿڱ���
protected:
	ITableFrame						* m_pITableFrame;					//��ܽӿ�
	const tagGameServiceOption		* m_pGameServiceOption;				//���ò���
	IGameEventSink					* m_pGameEventSink;	
	
	//���Ա���
protected:
	static const WORD				m_wPlayerCount;						//��Ϸ����

	//��������
public:
	//���캯��
	CGameMatchSink();
	//��������
	virtual ~CGameMatchSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID  Release() { }
	//�Ƿ���Ч
	virtual bool  IsValid() { return AfxIsValidAddress(this,sizeof(CGameMatchSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void *  QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool  InitTableFrameSink(IUnknownEx * pIUnknownEx);

	//��Ϣ�ӿ�
public:	
	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool  OnEventGameStart(ITableFrame *pITableFrame, WORD wChairCount);
	//��Ϸ����
	virtual bool  OnEventGameEnd(ITableFrame *pITableFrame,WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool  SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE bGameStatus, bool bSendSecret);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool  OnTimerMessage(WORD wTimerID, WPARAM wBindParam){return false;}
	//��Ϸ��Ϣ
	virtual bool  OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem){return false;}
	//�����Ϣ
	virtual bool  OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem){return false;}
	//���������¼��ӿ� 
	virtual bool  SetGameEventSink(IUnknownEx * pIUnknownEx);
	//����Ƿ��������
	virtual bool  IsCanStanUp(IServerUserItem *pUserItem);
	//��Ҷ��߻�����
	virtual void  SetUserOffline(WORD wChairID, bool bOffline);

	//�û�����
public:	
	//�û�����
	virtual bool OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool OnActionUserOnReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);	
};

//////////////////////////////////////////////////////////////////////////

#endif