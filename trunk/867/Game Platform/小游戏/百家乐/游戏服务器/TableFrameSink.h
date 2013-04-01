#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////
//��ʷ��¼
#define MAX_SCORE_HISTORY			16									//��ʷ����
//////////////////////////////////////////////////////////////////////////
//�����Ϣ
struct tagApplyUserInfo
{
	DWORD							dwUserID;							//���ID
	WORD							wChairID;							//���Ӻ���
	__int64							lUserScore;							//��һ���
	DWORD							dwUserType;							//����Ȩ��
};

typedef CArrayTemplate< tagApplyUserInfo > ApplyUserArrary;

//��Ϸ������
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{
	//��ע��Ϣ
protected:
	__int64							m_lTieScore;						//��ƽ��ע
	__int64							m_lBankerScore;						//��ׯ��ע
	__int64							m_lPlayerScore;						//������ע
	__int64							m_lTieSamePointScore;				//ƽ����ע
	__int64							m_lBankerKingScore;					//ׯ����ע
	__int64							m_lPlayerKingScore;					//������ע

	//��ע��Ϣ
protected:
	__int64							m_lUserTieScore[GAME_PLAYER];		//��ƽ��ע
	__int64							m_lUserBankerScore[GAME_PLAYER];	//��ׯ��ע
	__int64							m_lUserPlayerScore[GAME_PLAYER];	//������ע
	__int64							m_lUserTieSamePointScore[GAME_PLAYER];//ƽ����ע
	__int64							m_lUserBankerKingScore[GAME_PLAYER];//ׯ����ע
	__int64							m_lUserPlayerKingScore[GAME_PLAYER];//������ע

	//��ҳɼ�
protected:
	__int64							m_lUserWinScore[GAME_PLAYER];			//��ҳɼ�
	__int64							m_lUserReturnScore[GAME_PLAYER];	//������ע
	__int64							m_lUserRevenue[GAME_PLAYER];		//���˰��

	//�˿���Ϣ
protected:
	BYTE							m_cbCardCount[2];					//�˿���Ŀ
    BYTE							m_cbTableCardArray[2][3];			//�����˿�

	//״̬����
protected:
	DWORD							m_dwJettonTime;						//��ʼʱ��

	//ׯ����Ϣ
protected:
	__int64							m_lApplyBankerCondition;			//��������
	ApplyUserArrary					m_ApplyUserArrary;					//�����б�
	tagApplyUserInfo				m_CurrentBanker;					//��ǰׯ��
	BYTE							m_cbBankerTimer;					//��ׯ����
	__int64							m_lBankerWinScore;					//ׯ�ҳɼ�
	bool							m_bCancelBanker;					//�����ׯ

	//��¼����
protected:
	tagServerGameRecord				m_GameRecordArrary[MAX_SCORE_HISTORY];//��Ϸ��¼
	LONG							m_nRecordFirst;						//��ʼ��¼
	LONG							m_nRecordLast;						//����¼
	LONG							m_lBankerWinRound;					//ׯ��Ӯ�Ļغ���Ŀ
	//�������
protected:
	CGameLogic						m_GameLogic;						//��Ϸ�߼�
	ITableFrame						* m_pITableFrame;					//��ܽӿ�
	ITableFrameControl				* m_pITableFrameControl;			//��ܽӿ�
	const tagGameServiceOption		* m_pGameServiceOption;				//���ò���

	//���Ա���
protected:
	static const WORD				m_wPlayerCount;						//��Ϸ����
	static const enStartMode		m_GameStartMode;					//��ʼģʽ

	std::map<DWORD, __int64>		m_vForseLeave;						//ǿ���б�	

	//��������
public:
	//���캯��
	CTableFrameSink();
	//��������
	virtual ~CTableFrameSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID __cdecl Release() { }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool __cdecl InitTableFrameSink(IUnknownEx * pIUnknownEx);
	//��λ����
	virtual void __cdecl RepositTableFrameSink();

	//��Ϣ�ӿ�
public:
	//��ʼģʽ
	virtual enStartMode __cdecl GetGameStartMode();
	//��Ϸ״̬
	virtual bool __cdecl IsUserPlaying(WORD wChairID);

	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool __cdecl OnEventGameStart();
	//��Ϸ����
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);
	//��Ϸ��Ϣ����
	virtual bool __cdecl OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����Ϣ����
	virtual bool __cdecl OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);

	//�����¼�
public:
	//����ͬ��
	virtual bool __cdecl OnEventUserReqReady(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//�������
	virtual bool __cdecl OnEventUserReqOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//��������
	virtual bool __cdecl OnEventUserReqReConnect(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//��������
	virtual bool __cdecl OnEventUserReqSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bReqLookon) { return true; }
	//��������
	virtual bool __cdecl OnEventUserReqStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bReqLookon) { return true; }

	//�����¼�
public:
	//�û�����
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) ;
	//�û�����
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem){ return true; }
	//�û�����
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool __cdecl OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize){ return true; }

	//��Ϸ�¼�
protected:
	//��ע�¼�
	bool OnUserPlaceJetton(WORD wChairID, BYTE cbJettonArea, __int64 lJettonScore);
	//����ׯ��
	bool OnUserApplyBanker( tagServerUserData *pUserData, bool bApplyBanker );

	//��������
private:
	//�����˿�
	bool DispatchTableCard();
	//����ׯ��
	void SendApplyUser( IServerUserItem *pServerUserItem );
	//����ׯ��
	void ChangeBanker();
	//�ֻ�ׯ��
	void SendChangeBankerMsg();

	//�����ע
	__int64 GetMaxPlayerScore(WORD wChairID);
	//�����ע
	__int64 GetMaxPlayerKingScore(WORD wChairID);
	//�����ע
	__int64 GetMaxBankerScore(WORD wChairID);
	//�����ע
	__int64 GetMaxBankerKingScore(WORD wChairID);
	//�����ע
	__int64 GetMaxTieScore(WORD wChairID);
	//�����ע
	__int64 GetMaxTieKingScore(WORD wChairID);
	//����÷�
    void	CalculateScore();
	//����ǧ
	void ChuLaoQian();
	//����÷�
	__int64	PreCalculateBankerWin();
	//�ƶ�Ӯ��
	void	DeduceWinner(BYTE &cbWinner, BYTE &cbKingWinner);
	//�ƶ�Ӯ��
	void    MakeJettonString(WORD wChairID, TCHAR szJetton[MAX_DB_JETTON_LEN]);

	void AddUserLeft(DWORD nUserID, __int64 allZhu);
	bool FindUserLeft(DWORD nUserID);
};

//////////////////////////////////////////////////////////////////////////

#endif