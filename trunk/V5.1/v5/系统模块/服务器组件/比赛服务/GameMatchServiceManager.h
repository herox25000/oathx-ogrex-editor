#ifndef GAME_MATCH_SERVICE_MANAGER_HEAD_FILE
#define GAME_MATCH_SERVICE_MANAGER_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "MatchServiceHead.h"
#include "ChampionshipMatch.h"

//////////////////////////////////////////////////////////////////////////
//��ʱ������
struct tagMatchTimerItem
{
	DWORD								dwTimerID;						//��ʱ�� ID
	DWORD								dwRealID;						//ʵ��ID
	DWORD								dwRepeatTimes;					//�ظ�����
	WPARAM								wBindParam;						//�󶨲���
};

//��������
struct tagMatchReward
{
	DWORD								dwGold;							//��ҽ���
	DWORD								dwMedal;						//���ƽ���
	DWORD								dwExperience;					//���齱��
};

class CChampionshipMatch;

//��˵��
typedef CWHArray<IServerUserItem *> CMatchUserItemArray;
typedef CWHArray<CChampionshipMatch*>CMatchGroupArray;
typedef CWHArray<tagMatchReward*> CMatchRewardArray;
typedef CWHArray<tagMatchTimerItem *> CTimerItemPtr;


//��Ϸ������������
class MATCH_SERVICE_CLASS CGameMatchServiceManager : public IGameMatchServiceManager, public IChampionshipMatchSink
{
	//��������
protected:
	CMatchUserItemArray					m_OnMatchUserItem;				//�����û�
	CMatchUserItemArray					m_OutUserItem;					//��̭���û�
	const tagGameServiceOption *		m_pGameServiceOption;			//��������
	const tagGameServiceAttrib *		m_pGameServiceAttrib;			//��������

	//�ӿڱ���
protected:
	ITCPNetworkEngineEvent *			m_pITCPNetworkEngineEvent;		//����ӿ�
	IDataBaseEngine *					m_pIDataBaseEngine;				//��������
	ITimerEngine *						m_pITimerEngine;				//ʱ������
	IMainServiceFrame				*  m_pIGameServiceFrame;			//���ܽӿ�
	IServerUserManager *				m_pIServerUserManager;			//�û�����
	ITableFrame							** m_ppITableFrame;				//��ܽӿ�
	IAndroidUserManager					*m_pAndroidUserManager;			//��������
	bool								*m_bTableUsed;					//�����Ƿ��Ѿ�������

	CMatchGroupArray					m_MatchGroup;	
	CChampionshipMatch					*m_pCurMatch;
	tagMatchRule						m_MatchRule;
	CMatchRewardArray					m_RewardArr;						//����
	WORD								m_wMatchIDCount;
	CMatchGroupArray					m_OverGroup;					//�Ѿ��������������ӵķ���
	DWORD								m_dwStartTimeID;				//��ʼ��ʱ
	CMD_GR_MatchDesc					m_MatchDesc;					//��Ϣ����
	CWHArray<WORD,WORD>					m_UnRecovery;					//û�л��յ�����
	CUserItemMap						m_ReplaceUserItem;				//����Ļ�����


	CTimerItemPtr						m_TimerItemFree;				//��������
	CTimerItemPtr						m_TimerItemActive;				//�����
	//��������
public:
	//���캯��
	CGameMatchServiceManager(void);
	//��������
	virtual ~CGameMatchServiceManager(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID  Release() { }
	//�ӿڲ�ѯ
	virtual VOID *  QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//���ƽӿ�
public:
	//ֹͣ����
	virtual bool  StopService();
	//��������
	virtual bool  StartService();
	//����ӿ�
public:
	//��ʼ���ӿ�
	virtual bool  InitMatchInterface(ITCPNetworkEngineEvent *pTCPNetworkEngine,IDataBaseEngine *pIDataBaseEngine, IServerUserManager *pIServerUserManager,
		IMainServiceFrame *pIMainServiceFrame,ITimerEngine *pITimerEngine,IAndroidUserManager *pAndroidUserManager);
	//��ʼ�����ӿ��
	virtual bool  InitTableFrame(ITableFrame * pTableFrame,WORD wChairID);
	
	//ϵͳ�¼�
public:
	//ʱ���¼�
	virtual bool  OnEventTimer(DWORD dwTimerID, WPARAM dwBindParameter);
	//�����ӿ�
public:
	//�޸Ĳ���
	virtual bool  RectifyServiceOption(tagGameServiceOption * pGameServiceOption,tagGameServiceAttrib *pGameServiceAttrib);
	//�����û�
	virtual void  UserSort(WORD wTeamID);
	//��Ϣ�ӿ�
public:
	//�û��μӱ���
	virtual bool  OnUserJoinGame(IServerUserItem * pIServerUserItem, BYTE cbReason);
	//�û��˳�����
	virtual bool  OnUserQuitGame(IServerUserItem * pIServerUserItem, BYTE cbReason,WORD *pBestRank=NULL, DWORD dwContextID=INVALID_WORD);
	//�û������ɼ�
	virtual bool  OnUserMatchResult(DWORD dwUserID, WORD wKindID, WORD wServerID, WORD wSortID);

	//�����ӿ�
public:
	//��������ģʽ
	virtual VOID *  CreateGameMatchSink(REFGUID Guid, DWORD dwQueryVer);
	//����ӿ�
public:
	//��������
	virtual bool  SendDataToServer(DWORD dwAndroidID, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
	//��������
	virtual bool SendMatchInfo(IServerUserItem * pIServerUserItem);
	//���ݿ��¼�
	virtual bool OnEventDataBase(WORD wRequestID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);
	//������Ϣ
	virtual bool OnEventSocketMatch(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem, DWORD dwSocketID);

	//�ڲ�����
private:
	//ɾ���û�
	bool DeleteUserItem(DWORD dwUserIndex);
	//������Ϣ
	bool SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType);
	//��������
	bool AssignTable(CChampionshipMatch *pMatch, WORD wTableCount);
	//��ȡ��������
	bool ReadMatchOption(LPCTSTR lpFileName);
	
public:
	//������������ʼ����
	virtual bool  OnMatchStart(CChampionshipMatch *pMatch);
	//�ȴ���ʱ
	virtual bool  OnWaitTimeOut(DWORD dwMatchNO);
	//�û���̭
	virtual bool  OnUserOut(IServerUserItem *pUserItem,LPCTSTR szReason,WORD wLen,WORD wRank,CChampionshipMatch *pMatch);
	//��������
	virtual bool  SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
	//��ʱ��
	virtual bool  SetGameTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM dwBindParameter,CChampionshipMatch *pMatch);
	//������Ϣ
	virtual bool  SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType);
	//д�뽱��
	virtual bool  WriteUserAward(IServerUserItem *pIServerUserItem, WORD wRank,DWORD dwMatchNO,LPCTSTR szDescribe,CChampionshipMatch *pMatch);
	//��������
	virtual bool  OnEventMatchOver(CChampionshipMatch *pMatch);
	//�����û�����
	virtual bool  SendGroupUserScore(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch);
	//����״̬
	virtual bool  SendGroupUserStatus(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch);
	//�������ݵ������� 
	virtual bool  SendDataToGameServer(DWORD dwAndroidID, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
	//�������ݵ�һ���û� 
	virtual bool  SendGroupData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize,CChampionshipMatch *pMatch);
	//��ȡһ�����еĻ�����
	virtual IAndroidUserItem * GetFreeAndroidUserItem();
	//�����油������
	virtual bool SetReplaceAndroidItem(IServerUserItem *pIServerUserItem);
};

//////////////////////////////////////////////////////////////////////////
//�������

//////////////////////////////////////////////////////////////////////////

#endif