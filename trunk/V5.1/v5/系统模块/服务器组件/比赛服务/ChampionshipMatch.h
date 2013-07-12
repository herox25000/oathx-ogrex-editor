#ifndef CHAMPIONSHIP_MATCH_HEAD_FILE
#define CHAMPIONSHIP_MATCH_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "AfxTempl.h"
#include "GameMatchSink.h"
#include "MatchServiceHead.h"

typedef CMap<DWORD,DWORD,IServerUserItem *, IServerUserItem *>CUserItemMap;
typedef CMap<IServerUserItem *, IServerUserItem *, DWORD, DWORD>CUserSeatMap;

#define IDI_TURN_MATCH_START		(IDI_MATCH_MODULE_START+1)
#define IDI_DELETE_OUT_USER		 	(IDI_MATCH_MODULE_START+2)					//�ӳ�һ��ʱ��ɾ����̭�û�
#define IDI_START_MATCH_GAME		(IDI_MATCH_MODULE_START+3)					//��ʼһ�̱���  
#define IDI_DELETE_OVER_MATCH		(IDI_MATCH_MODULE_START+5)					//ɾ�������ı�����
#define IDI_NORMAL_TIMER			(IDI_MATCH_MODULE_START+6)					//���涨ʱ��
#define IDI_START_MATCH_START		(IDI_MATCH_MODULE_START+7)					//��ʼһ������ 
#define IDI_START_MATCH_END			(IDI_MATCH_MODULE_START+9)					//��ʼһ������ 
#define IDI_HALF_MINUTE				(IDI_MATCH_MODULE_START+10)					//30��
#define IDI_GROUP_START				(IDI_MATCH_MODULE_START+60)					//�������ڵĶ�ʱ��
#define IDI_STAR_NEXT_ROUND			(IDI_GROUP_START+1)							//��ʼ��һ�ֱ���
#define IDI_CHECK_MATCH_GROUP		(IDI_GROUP_START+2)							//��Ѳ���п��������� 
#define IDI_FINISH_FIRST_ROUND		(IDI_GROUP_START+3)							//ǿ�н�������


//��һ�ֹ���
enum enFirstRoundRule
{
	FirstRoundRule_Score,					//��ʱ����
	FirstRoundRule_Time						//��������
};

struct tagMatchRule
{
	DWORD				dwMatchID;							//����ID
	TCHAR				szMatchName[LEN_SERVER];			//��������
	WORD				wUserCount;							//��������
	WORD				wAndroidUserCount;					//һ�������л����˱���������
	WORD				wWaitTime;							//�ﵽ��̭������ȴ����ȷ��������������λ����
	DWORD				dwInitalBase;						//��ʼ����
	BYTE				dwGrowthTime;						//����ʱ��
	BYTE				cbGrowthRange;						//��������
	DWORD				dwFee;								//������
	DWORD				dwInitalScore;						//��ʼ����
	WORD				wRemainUserCount;					//ʣ�������ֹͣ��̭
	DWORD				dwSecRoundUserCount;				//������һ��ʣ�µ�����
	BYTE				cbLeastScore;						//���ٻ���
	BYTE				cbFirScoreRule;						//���븴���Ĵ��ֹ���
	BYTE				cbFirGameCount;						//����N�ֻ�һ����
	BYTE				cbSecGameCount;						//����N�ֻ�һ����
	BYTE				cbSecScoreRule;						//�������ֹ���
	BYTE				cbFirRoundCount;					//�����׶���Ϸ����
	BYTE				cbSecRoundCount;					//�����׶���Ϸ�ִ�
	WORD				arrSecRoundUserCount[16];			//�����׶θ�����Ϸ����
	enFirstRoundRule	enFirstRule;						//��һ�ֹ���
	DWORD				dwFirstRoundTime;					//��һ��ʱ������ʱ������Ч����λ����
	DWORD				dwAheadStatistics;					//��ǰͳ�Ƴɼ� ��λ����
	
	tagMatchRule()
	{
		ZeroMemory(this, sizeof(tagMatchRule));
	}
};

#ifdef _UNICODE
#define VER_IChampionshipMatch INTERFACE_VERSION(1,1)
static const GUID IID_IChampionshipMatch={0x786c5501,0xa7a4,0x4531,0x0091,0xc5,0x3e,0x07,0x3e,0xa6,0x0a,0xf9};
#else
#define VER_IChampionshipMatch INTERFACE_VERSION(1,1)
static const GUID IID_IChampionshipMatch={0x1a4e0406,0x8ddc,0x4e34,0x0083,0x89,0xb5,0x5e,0x4e,0xfa,0x6b,0xb7};
#endif

interface IChampionshipMatch :public IUnknownEx
{
	//���ñ�������
	virtual bool SetMatchRule(tagMatchRule *pRule)=NULL;
	//�û�����
	virtual bool OnUserSignUp(IServerUserItem *pUserItem)=NULL;
	//�û�����
	virtual bool OnUserQuitMatch(IServerUserItem *pUserItem,bool bByUser=false)=NULL;
	//��������
	virtual void SetMatchTable(ITableFrame *pTable[], WORD wTableCount)=NULL;
};

#ifdef _UNICODE
#define VER_IChampionshipMatchSink INTERFACE_VERSION(1,1)
static const GUID IID_IChampionshipMatchSink={0x30e4794a,0x610e,0x4873,0x00bd,0x23,0x9c,0xc7,0x2c,0xbe,0xd4,0xc5};
#else
#define VER_IChampionshipMatchSink INTERFACE_VERSION(1,1)
static const GUID IID_IChampionshipMatchSink={0xfc8dc7b5,0x2318,0x411f,0x00b9,0x09,0x6c,0xdd,0x39,0x38,0x0d,0x18};
#endif

class CChampionshipMatch;

interface IChampionshipMatchSink:public IUnknownEx
{
	//������������ʼ����
	virtual bool  OnMatchStart(CChampionshipMatch *pMatch)=NULL;
	//�ȴ���ʱ
	virtual bool  OnWaitTimeOut(DWORD dwMatchNO)=NULL;
	//�û���̭
	virtual bool  OnUserOut(IServerUserItem *pUserItem,LPCTSTR szReason,WORD wLen,WORD wRank,CChampionshipMatch *pMatch)=NULL;
	//��������
	virtual bool  SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)=NULL;
	//��ʱ��
	virtual bool  SetGameTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM dwBindParameter,CChampionshipMatch *pMatch)=NULL;
	//������Ϣ
	virtual bool  SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)=NULL;
	//д�뽱��
	virtual bool  WriteUserAward(IServerUserItem *pIServerUserItem, WORD wRank,DWORD dwMatchNO,LPCTSTR szDescribe,CChampionshipMatch *pMatch)=NULL;
	//��������
	virtual bool  OnEventMatchOver(CChampionshipMatch *pMatch)=NULL;
	//�����û�����
	virtual bool  SendGroupUserScore(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch)=NULL;
	//����״̬
	virtual bool  SendGroupUserStatus(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch)=NULL;
	//�������ݵ������� 
	virtual bool  SendDataToGameServer(DWORD dwAndroidID, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)=NULL;
	//�������ݵ�һ���û�
	virtual bool  SendGroupData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize,CChampionshipMatch *pMatch)=NULL;
	//��ȡһ�����еĻ�����
	virtual IAndroidUserItem * GetFreeAndroidUserItem()=NULL;
	//�����油������
	virtual bool SetReplaceAndroidItem(IServerUserItem *pIServerUserItem)=NULL;
};
typedef CWHArray<IServerUserItem *> CMatchUserItemArray;

struct ITableFramEx 
{
	ITableFrame *pTableFrame;
	BYTE cbGameCount;
	DWORD dwBase;
	BYTE cbOnSeatUserCount;
	bool bOffline[MAX_CHAIR];
	BYTE cbStartTimes;
};
typedef CWHArray<ITableFramEx *>CTableFrameMananerArray;
struct tagMatchScore
{
	DWORD dwUserID;
	IServerUserItem *pUserItem;
	SCORE  lScore;
};

typedef CWHArray<tagMatchScore *> CUserMatchScoreArray;

//����״̬
enum enMatchStatus
{
	MS_NULL_STATUS=0,
	MS_SIGNUPING,
	MS_STOP_OUT,
	MS_FIRST_ROUND,
	MS_START_NEXT_ROUND,
	MS_SECOND_ROUND
};

class CChampionshipMatch:public IGameEventSink
{
	friend class CGameMatchServiceManager;

protected:
	static WORD						m_wChairCount;					//������Ŀ
	DWORD							m_dwMatchNO;
	CUserItemMap					m_OnMatchUserMap;				//�����û�
	CUserItemMap					m_QuitUserMap;					//���ߺ�ǿ�˵��û�
	tagMatchRule					*m_pMatchRule;		
	IChampionshipMatchSink			*m_pMatchSink;
	ITableFramEx					*m_pAssignTable;
	WORD							m_wTableCount;					//��������ӵĸ���
	DWORD							m_dwCurBase;					// ��ǰ�Ļ���
	bool							m_bAssignTable;					//���ӷ������

	DWORD							m_dwTimeCount;
	bool							m_bStarted;
	
	bool							m_bGameEnd;	
	CTableFrameMananerArray			m_WaitStartTable;				//�ȴ���ʼ������	
	enMatchStatus					m_enMatchStatus;				//�����׶�
	WORD							m_wPlayingTableCount;			//�ﵽ��̭����ʱ������Ϸ��������
	WORD							m_wCurRountSec;					//��ǰ�����ڸ������Ľ׶�
	WORD							m_wFinishTable;					//��ɱ�����������
	CMatchUserItemArray				m_MaybeOutUser;					//�п�����̭���û�
	CUserMatchScoreArray			m_OutUserArray;					//��̭�û�,�ȴ������
	bool							m_bIsCanStandUp;				//�Ƿ��������
	CUserSeatMap					m_UserSeatMap;					//�û��������λ������
	CUserItemMap					m_CanReadyUserMap;				//����׼��
	CTime							m_tMatchStart;					//��ʼʱ��
	bool							m_bWillOver;					//��������
	WORD							m_wAndroidUserCount;			//�����˸���
	DWORD							m_dwWaitTime;					//�ȴ�ʱ��
	bool							m_bException;					//�Ƿ����쳣
	
public:
	CChampionshipMatch(tagMatchRule *pMatchRule, DWORD dwMatchNO,IChampionshipMatchSink *pSink);
	virtual ~CChampionshipMatch(void);

	//���ñ�������
	bool SetMatchRule(tagMatchRule *pRule);
public:
 	//�ͷŶ���
 	virtual VOID  Release(){}
 	//�ӿڲ�ѯ
	virtual VOID *  QueryInterface(REFGUID Guid, DWORD dwQueryVer);
	//���ûص��ӿ�
	 bool SetMatchSink(IChampionshipMatchSink *pSink);
	//�û�����
	 bool OnUserSignUp(IServerUserItem *pUserItem);
	//�û�����
	 BOOL OnUserQuitMatch(IServerUserItem *pUserItem,bool bByUser=false);
	//��������
	 void SetMatchTable(ITableFrame *pTable[], WORD wTableCount);
	 //��ȡ����λ
	 ITableFramEx* GetEmptyChair(WORD &wTableID, WORD &wChairID);
	 //��ʼ����
	 bool StartMatch(ITableFramEx *pTableFrame=NULL);
	 //��ʱ��
	 bool OnTimeMessage(DWORD dwTimerID, WPARAM dwBindParameter);

	 //��Ϸ��ʼ
	 virtual bool  OnEventGameStart(ITableFrame *pITableFrame, WORD wChairCount);
	 //��Ϸ����
	 virtual bool  OnEventGameEnd(ITableFrame *pITableFrame,WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	 //�Ƿ�����뿪��λ 
	 virtual bool  IsCanStanUp(IServerUserItem *pUserItem);
	 //��Ҷ��߻����� 
	 virtual void  SetUserOffline(WORD wTableID,IServerUserItem *pUserItem, bool bOffline);
	 //�û�����
	 virtual bool OnActionUserSitDown(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	 //�û�����
	 virtual bool OnActionUserStandUp(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	 //�û�ͬ��
	 virtual bool OnActionUserOnReady(WORD wTableID, WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);

protected:
	//ѡ��������
	void SelectPromotionUser();
	//�������
	WORD SortMapUser(tagMatchScore score[]);
	//�������
	WORD SortUserItemArray(tagMatchScore score[], CMatchUserItemArray &MatchUserItemArray);
	//����̭���������
	WORD SortOutUserArray(tagMatchScore *score[]);
	//���°������������λ
	void RearrangeUserSeat(tagMatchScore score[], INT_PTR nCount);
	//��ȡ����
	WORD GetUserRank(IServerUserItem *pUserItem, ITableFrame *pITableFrame=NULL);
	//��ȡ�û�
	IServerUserItem * GetSeatUserItem(DWORD dwSeatID);
	//��ʱ������Ϸ����
	void FirstRoundRuleTimeGameEnd(ITableFramEx *pITableFrameEx);
	//����������Ϸ����
	void FirstRoundRuleScoreGameEnd(ITableFramEx *pITableFrameEx,WORD wTableIndex);
    //���һ��
	bool OnTableFinishRound(ITableFramEx *pITableFrameEx);
	//��������
	void MatchOver();

	//�û���Ŀ
	WORD GetSitUserCount(ITableFrame *pTableFrame);
	//��ȡ����
	WORD GetNullChairID(ITableFrame *pTableFrame);
	//������ʾ
	VOID SendWaitTip(ITableFrame *pTableFrame);
};


#endif