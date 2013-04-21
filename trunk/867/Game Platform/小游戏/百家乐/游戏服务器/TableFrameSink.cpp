#include "StdAfx.h"
#include "TableFrameSink.h"
#include "MMSystem.h"
#pragma comment(lib, "winmm.lib")

//////////////////////////////////////////////////////////////////////////

//��������
#define SEND_COUNT					8									//���ʹ���

//��������
#define INDEX_PLAYER				0									//�м�����
#define INDEX_BANKER				1									//ׯ������

//��עʱ��
#define IDI_PLACE_JETTON			1									//��עʱ��

#ifdef _DEBUG
#define TIME_PLACE_JETTON			25									//��עʱ��
#else
#define TIME_PLACE_JETTON			25									//��עʱ��
#endif
#define TIME_FREE					10									//����ʱ��

//����ʱ��
#define IDI_GAME_END				2									//����ʱ��
#ifdef _DEBUG
#define TIME_GAME_END				13									//����ʱ��
#else
#define TIME_GAME_END				13									//����ʱ��
#endif
#define IDI_GAME_FREE				3									//���н׶�

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;				//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_TimeControl;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

//����ṹ
struct tagReplaceCard
{
	BYTE							cbCardCount[2];						//�˿���Ŀ
    BYTE							cbTableCardArray[2][3];				//�����˿�
};

//ƽ�Ҵ���
tagReplaceCard CardTieWinCard[]=
{
	3,3,0x12,0x05,0x00,0x22,0x25,0x32,
	3,3,0x11,0x05,0x00,0x14,0x2B,0x32,
	3,3,0x1A,0x2B,0x3D,0x1C,0x3C,0x0B,
	3,3,0x27,0x2D,0x00,0x01,0x39,0x3D,
	3,3,0x3C,0x28,0x00,0x12,0x15,0x01,
};

//ׯ�Ҵ���
tagReplaceCard CardBankerWinCard[]=
{
	3,3,0x17,0x1A,0x05,0x36,0x0D,0x1C,
	3,3,0x17,0x03,0x3A,0x1C,0x1A,0x34,
	3,3,0x11,0x0D,0x1D,0x35,0x32,0x00,
	3,3,0x18,0x29,0x00,0x22,0x16,0x00,
	3,3,0x38,0x1A,0x00,0x25,0x04,0x00,
};

//�мҴ���
tagReplaceCard CardPlayerWinCard[]=
{
	3,3,0x37,0x3D,0x00,0x31,0x3D,0x0D,
	3,3,0x16,0x24,0x08,0x03,0x3D,0x00,
	3,3,0x0B,0x39,0x00,0x09,0x35,0x00,
	3,3,0x2C,0x08,0x00,0x02,0x15,0x00,
	3,3,0x16,0x33,0x00,0x1A,0x27,0x00,
};

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��ע��Ϣ
	m_lTieScore=0L;
	m_lBankerScore=0L;
	m_lPlayerScore=0L;
	m_lTieSamePointScore=0L;
	m_lBankerKingScore=0L;
	m_lPlayerKingScore=0L;

	//״̬����
	m_dwJettonTime=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserTieScore,sizeof(m_lUserTieScore));
	ZeroMemory(m_lUserBankerScore,sizeof(m_lUserBankerScore));
	ZeroMemory(m_lUserPlayerScore,sizeof(m_lUserPlayerScore));
	ZeroMemory(m_lUserTieSamePointScore,sizeof(m_lUserTieSamePointScore));
	ZeroMemory(m_lUserBankerKingScore,sizeof(m_lUserBankerKingScore));
	ZeroMemory(m_lUserPlayerKingScore,sizeof(m_lUserPlayerKingScore));

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));

	//ׯ�ұ���

	ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
	m_cbBankerTimer=0;
	m_lBankerWinScore = 0;
	m_bCancelBanker=false;
	
	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;
	m_pITableFrameControl=NULL;

	//��Ϸ��¼
	ZeroMemory(m_GameRecordArrary, sizeof(m_GameRecordArrary));
	m_nRecordFirst=0;	
	m_nRecordLast=0;	
	
	m_lBankerWinRound=0;	

	//��ȡ����
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;

	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrameControl=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrameControl);
	if (m_pITableFrameControl==NULL) return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	m_pITableFrame->SetGameStatus(GS_FREE);

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//��ע��Ϣ
	m_lTieScore=0L;
	m_lBankerScore=0L;
	m_lPlayerScore=0L;
	m_lTieSamePointScore=0L;
	m_lBankerKingScore=0L;
	m_lPlayerKingScore=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserTieScore,sizeof(m_lUserTieScore));
	ZeroMemory(m_lUserBankerScore,sizeof(m_lUserBankerScore));
	ZeroMemory(m_lUserPlayerScore,sizeof(m_lUserPlayerScore));
	ZeroMemory(m_lUserTieSamePointScore,sizeof(m_lUserTieSamePointScore));
	ZeroMemory(m_lUserBankerKingScore,sizeof(m_lUserBankerKingScore));
	ZeroMemory(m_lUserPlayerKingScore,sizeof(m_lUserPlayerKingScore));

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	return;
}

//��ʼģʽ
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}

//��Ϸ��ʼ
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	//����״̬
	m_pITableFrame->SetGameStatus(GS_PLAYING);

	//BOOL bBankerLaoQian=FALSE;
	////��ȡ���
	//IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
	//if ( pServerUserItem )
	//{
	//	tagServerUserData const *pBankerData=pServerUserItem->GetUserData();
	//	bBankerLaoQian=pBankerData->dwLaoQian>0;
	//}

	SuperRand();
	DispatchTableCard();

	//-----------Ϊ�˾���������ٷ�����-------------------------------------------------
	LONG dis_count=rand()%8;
	for( int i=0; i<dis_count; i++ )
	{
		ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
		ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
		DispatchTableCard();
	}

	ChuLaoQian();

	//��������
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));
	GameStart.cbTimeLeave = TIME_GAME_END;
	//��������
	CopyMemory(GameStart.cbCardCount,m_cbCardCount,sizeof(m_cbCardCount));
	CopyMemory(GameStart.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
	GameStart.lApplyBankerCondition = m_lApplyBankerCondition;

	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));

	//�������
	CalculateScore();

	return true;
}

//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//�������
		{
			//������Ϣ
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.nBankerTime = m_cbBankerTimer;
			GameEnd.lBankerTotalScore = m_lBankerWinScore;
			//�ƶ����
			DeduceWinner(GameEnd.cbWinner, GameEnd.cbKingWinner);			
			//д�����
			for ( WORD wUserChairID = 0; wUserChairID < GAME_PLAYER; ++wUserChairID )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserChairID);
				if ( pIServerUserItem == NULL ) continue;
				//ʤ������
				enScoreKind ScoreKind=(m_lUserWinScore[wUserChairID]>0L)?enScoreKind_Win:enScoreKind_Lost;
				TCHAR szJetton[MAX_DB_JETTON_LEN];
				MakeJettonString(wUserChairID, szJetton);//�ƶ�Ӯ��
				//д�����
				if (m_lUserWinScore[wUserChairID]!=0L) 
				{
					m_pITableFrame->WriteUserScore(wUserChairID,m_lUserWinScore[wUserChairID], 0, ScoreKind);
				}
			
				//ׯ���ж�
				if ( m_CurrentBanker.dwUserID == pIServerUserItem->GetUserID() ) 
					m_CurrentBanker.lUserScore = pIServerUserItem->GetUserScore()->lScore;
			}

			//���ͻ���
			GameEnd.cbTimeLeave=TIME_FREE;	//ʣ��ʱ��
			if ( m_CurrentBanker.dwUserID != 0 ) 
				GameEnd.lBankerTreasure = m_CurrentBanker.lUserScore;//ׯ�ҽ��
			for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
				if ( pIServerUserItem == NULL ) continue;
				//������Ϣ					
				GameEnd.lCellScore=m_pGameServiceOption->lCellScore;
				GameEnd.lMeMaxScore=pIServerUserItem->GetUserScore()->lScore;
				m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			}

			//�����Ƶ�
			BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER],m_cbCardCount[INDEX_PLAYER]);
			BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

			TCHAR szPokerInfo[MAX_DB_JETTON_LEN]={0};
			TCHAR szPointInfo[MAX_DB_JETTON_LEN]={0};
			_snprintf(szPokerInfo, CountArray(szPokerInfo), TEXT("ׯ:%d�� ��:%d�� ׯ_%X_%X_%X ��_%X_%X_%X"), 
				m_cbCardCount[INDEX_BANKER],
				m_cbCardCount[INDEX_PLAYER],
				m_cbTableCardArray[INDEX_BANKER][0], 
				m_cbTableCardArray[INDEX_BANKER][1],
				m_cbTableCardArray[INDEX_BANKER][2],
				m_cbTableCardArray[INDEX_PLAYER][0], 
				m_cbTableCardArray[INDEX_PLAYER][1],
				m_cbTableCardArray[INDEX_PLAYER][2]);

			_snprintf(szPointInfo, CountArray(szPointInfo), TEXT("ׯ:%d�� ��:%d��"), cbBankerCount, cbPlayerCount);
			//д��غ���Ϣ
			//m_pITableFrame->WriteRoundInfomation(szPokerInfo, szPointInfo, m_CurrentBanker.dwUserID, m_lBankerWinScore);

			//ׯ���ж�
			if ( m_CurrentBanker.dwUserID != 0 )
			{
				//��ȡ�û�
				IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
				if (pIServerUserItem) 
				{
					//�����ж�
					if ( pIServerUserItem->GetUserScore()->lScore < m_lApplyBankerCondition || m_cbBankerTimer >= 20 )
					{
						//�����ׯ
						OnUserApplyBanker( pIServerUserItem->GetUserData(), false );
					}
				}
			}
			//������Ϸ
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:		//�û�ǿ���˳�
		{
			//ʤ������
			__int64	allZhu=0;
			if ( pIServerUserItem->GetUserID()==m_CurrentBanker.dwUserID ) //ׯ��ǿ��
			{
				allZhu=m_lTieScore*9+
					m_lBankerScore*2+
					m_lPlayerScore*2+
					m_lTieSamePointScore*33+
					m_lBankerKingScore*3+
					m_lPlayerKingScore*3;
			}
			else
			{
				if (m_pITableFrame->GetGameStatus() == GS_FREE + 1)
				{
					JettonChangeByUserLeft( wChairID, pIServerUserItem);
				}
				else
				{
					allZhu=m_lUserTieScore[wChairID]+
						m_lUserBankerScore[wChairID]+
						m_lUserPlayerScore[wChairID]+
						m_lUserTieSamePointScore[wChairID]+
						m_lUserBankerKingScore[wChairID]+
						m_lUserPlayerKingScore[wChairID];
				}
			}

			if ( allZhu>0 )
			{
				if (m_pGameServiceOption->wServerType == GAME_GENRE_GOLD)
					if ( allZhu >pIServerUserItem->GetUserScore()->lScore )
						allZhu=pIServerUserItem->GetUserScore()->lScore;
				//��������
				tagScoreInfo ScoreInfo;
				ZeroMemory(&ScoreInfo,sizeof(ScoreInfo));

				//���ñ���
				TCHAR szJetton[MAX_DB_JETTON_LEN];
				MakeJettonString(wChairID, szJetton);//�ƶ�Ӯ��
				m_pITableFrame->WriteUserScore(pIServerUserItem, -allZhu, 0, enScoreKind_Flee);
			}
			return true;
		}
	}

	return false;
}

//���ͳ���
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_FREE:			//����״̬
		{
			//������Ϸ��¼
			WORD wBufferSize=0;
			BYTE cbBuffer[SOCKET_PACKAGE];
			int nIndex = m_nRecordFirst;
			while ( nIndex != m_nRecordLast )
			{
				if ((wBufferSize+sizeof(tagServerGameRecord))>sizeof(cbBuffer))
				{
					m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);
					wBufferSize=0;
				}
				CopyMemory(cbBuffer+wBufferSize,&m_GameRecordArrary[nIndex],sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}
			if (wBufferSize>0)
				m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);

			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			StatusFree.lTieScore=m_lTieScore;
			StatusFree.lBankerScore=m_lBankerScore;
			StatusFree.lPlayerScore=m_lPlayerScore;
			StatusFree.lTieSamePointScore = m_lTieSamePointScore;
			StatusFree.lBankerKingScore = m_lBankerKingScore;
			StatusFree.lPlayerKingScore = m_lPlayerKingScore;

			//ׯ����Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lMeTieScore=m_lUserTieScore[wChiarID];
				StatusFree.lMeBankerScore=m_lUserBankerScore[wChiarID];
				StatusFree.lMePlayerScore=m_lUserPlayerScore[wChiarID];
				StatusFree.lMeTieKingScore = m_lUserTieSamePointScore[wChiarID];
				StatusFree.lMeBankerKingScore = m_lUserBankerKingScore[wChiarID];
				StatusFree.lMePlayerKingScore = m_lUserPlayerKingScore[wChiarID];
				StatusFree.lMeMaxScore=pIServerUserItem->GetUserScore()->lScore;
			}

			if ( m_CurrentBanker.dwUserID != 0 ) 
			{
				StatusFree.cbBankerTime = m_cbBankerTimer;
				StatusFree.lCurrentBankerScore = m_lBankerWinScore;
				StatusFree.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				StatusFree.lBankerTreasure = m_CurrentBanker.lUserScore;
			}
			else StatusFree.wCurrentBankerChairID = INVALID_CHAIR;
			
			//ȫ����Ϣ
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusFree.cbTimeLeave=(BYTE)(TIME_FREE-__min(dwPassTime,TIME_FREE));

			//���ͳ���
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
			
			//����������
			SendApplyUser(  pIServerUserItem );

			return bSuccess;
		}
	case GS_FREE + 1:
		{
			//������Ϸ��¼
			WORD wBufferSize=0;
			BYTE cbBuffer[SOCKET_PACKAGE];
			int nIndex = m_nRecordFirst;
			while ( nIndex != m_nRecordLast )
			{
				if ((wBufferSize+sizeof(tagServerGameRecord))>sizeof(cbBuffer))
				{
					m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);
					wBufferSize=0;
				}
				CopyMemory(cbBuffer+wBufferSize,&m_GameRecordArrary[nIndex],sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}
			if (wBufferSize>0)
				m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);


			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			StatusFree.lTieScore=m_lTieScore;
			StatusFree.lBankerScore=m_lBankerScore;
			StatusFree.lPlayerScore=m_lPlayerScore;
			StatusFree.lTieSamePointScore = m_lTieSamePointScore;
			StatusFree.lBankerKingScore = m_lBankerKingScore;
			StatusFree.lPlayerKingScore = m_lPlayerKingScore;

			//ׯ����Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lMeTieScore=m_lUserTieScore[wChiarID];
				StatusFree.lMeBankerScore=m_lUserBankerScore[wChiarID];
				StatusFree.lMePlayerScore=m_lUserPlayerScore[wChiarID];
				StatusFree.lMeTieKingScore = m_lUserTieSamePointScore[wChiarID];
				StatusFree.lMeBankerKingScore = m_lUserBankerKingScore[wChiarID];
				StatusFree.lMePlayerKingScore = m_lUserPlayerKingScore[wChiarID];
				StatusFree.lMeMaxScore=pIServerUserItem->GetUserScore()->lScore;
			}

			if ( m_CurrentBanker.dwUserID != 0 ) 
			{
				StatusFree.cbBankerTime = m_cbBankerTimer;
				StatusFree.lCurrentBankerScore = m_lBankerWinScore;
				StatusFree.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				StatusFree.lBankerTreasure = m_CurrentBanker.lUserScore;
			}
			else StatusFree.wCurrentBankerChairID = INVALID_CHAIR;

			//ȫ����Ϣ
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusFree.cbTimeLeave=(BYTE)(TIME_PLACE_JETTON-__min(dwPassTime,TIME_PLACE_JETTON));
			//���ͳ���
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
			//����������
			SendApplyUser(  pIServerUserItem );
			return bSuccess;
		}
	case GS_PLAYING:		//��Ϸ״̬
		{
			//������Ϸ��¼
			WORD wBufferSize=0;
			BYTE cbBuffer[SOCKET_PACKAGE];
			int nIndex = m_nRecordFirst;
			while ( nIndex != m_nRecordLast )
			{
				if ((wBufferSize+sizeof(tagServerGameRecord))>sizeof(cbBuffer))
				{
					m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);
					wBufferSize=0;
				}
				CopyMemory(cbBuffer+wBufferSize,&m_GameRecordArrary[nIndex],sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}
			if (wBufferSize>0)
				m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);

			//��������
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay,sizeof(StatusPlay));
			//ȫ����Ϣ
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusPlay.cbTimeLeave=(BYTE)(TIME_GAME_END-__min(dwPassTime,TIME_GAME_END));
			StatusPlay.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			StatusPlay.lTieScore=m_lTieScore;
			StatusPlay.lBankerScore=m_lBankerScore;
			StatusPlay.lPlayerScore=m_lPlayerScore;
			StatusPlay.lTieSamePointScore = m_lTieSamePointScore;
			StatusPlay.lBankerKingScore = m_lBankerKingScore;
			StatusPlay.lPlayerKingScore = m_lPlayerKingScore;

			//ׯ����Ϣ
			StatusPlay.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusPlay.lMeTieScore=m_lUserTieScore[wChiarID];
				StatusPlay.lMeBankerScore=m_lUserBankerScore[wChiarID];
				StatusPlay.lMePlayerScore=m_lUserPlayerScore[wChiarID];
				StatusPlay.lMeTieKingScore = m_lUserTieSamePointScore[wChiarID];
				StatusPlay.lMeBankerKingScore = m_lUserBankerKingScore[wChiarID];
				StatusPlay.lMePlayerKingScore = m_lUserPlayerKingScore[wChiarID];	
				StatusPlay.lMeMaxScore=pIServerUserItem->GetUserScore()->lScore;
			}

			if ( m_CurrentBanker.dwUserID != 0 ) 
			{
				StatusPlay.cbBankerTime = m_cbBankerTimer;
				StatusPlay.lCurrentBankerScore = m_lBankerWinScore;
				StatusPlay.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				StatusPlay.lBankerTreasure = m_CurrentBanker.lUserScore;
			}
			else 
				StatusPlay.wCurrentBankerChairID = INVALID_CHAIR;

			//�˿���Ϣ
			CopyMemory(StatusPlay.cbCardCount,m_cbCardCount,sizeof(m_cbCardCount));
			CopyMemory(StatusPlay.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
			//���ͳ���
			bool bSuccess= m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));

			//����������
			SendApplyUser( pIServerUserItem );
			return bSuccess;
		}
	}

	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	switch (wTimerID)
	{
	case IDI_GAME_FREE:
		{
			//ˢ����ׯ�ҵķ���
			IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if(pBankerItem)
			{
				if(m_CurrentBanker.dwUserID != 0L)
					m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
			}
			OnEventStartPlaceJetton();
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_PLACE_JETTON, TIME_PLACE_JETTON*1000,1,0L);
			return true;
		}
	case IDI_PLACE_JETTON:		//��עʱ��
		{
			//ˢ����ׯ�ҵķ���
			IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if(pBankerItem)
			{
				if(m_CurrentBanker.dwUserID != 0L)
					m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
			}
			//��ʼ��Ϸ
			m_pITableFrameControl->StartGame();
			//����ʱ��
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_GAME_END,TIME_GAME_END*1000L,1,0L);

			return true;
		}
	case IDI_GAME_END:			//������Ϸ
		{
			//ˢ����ׯ�ҵķ���
			IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if(pBankerItem)
			{
				if(m_CurrentBanker.dwUserID != 0L)
					m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
			}
			//������Ϸ
			OnEventGameEnd(INVALID_CHAIR,NULL,GER_NORMAL);
			//��ׯ�ж�
			if ( m_bCancelBanker && m_CurrentBanker.dwUserID != 0 )
			{
				//��ȡ���
				IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );

				//���ñ���
				m_cbBankerTimer = 0;
				m_lBankerWinScore=0;
				ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
				m_bCancelBanker=false;	
				//������Ϣ
				SendChangeBankerMsg();
				//ɾ��ׯ��
				if ( pServerUserItem ) OnUserApplyBanker( pServerUserItem->GetUserData(), false );
			}

			//����ʱ��
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_GAME_FREE,TIME_FREE*1000L,1,0L);
			m_pITableFrame->SetGameStatus(GS_FREE);

			//�ֻ�ׯ��
			ChangeBanker();

			//ׯ����Ϣ
			if ( m_CurrentBanker.dwUserID != 0 )
			{
				CMD_S_ChangeUserScore ChangeUserScore;
				ZeroMemory( &ChangeUserScore, sizeof( ChangeUserScore ) );
				ChangeUserScore.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				ChangeUserScore.lCurrentBankerScore = m_lBankerWinScore;
				ChangeUserScore.cbBankerTime = m_cbBankerTimer;
				ChangeUserScore.lScore = m_CurrentBanker.lUserScore;
				ChangeUserScore.wChairID = m_CurrentBanker.wChairID;
				m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_CHANGE_USER_SCORE,&ChangeUserScore,sizeof(ChangeUserScore));
				m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_CHANGE_USER_SCORE,&ChangeUserScore,sizeof(ChangeUserScore));
			}

			//�л��ж�
			if ( m_cbBankerTimer == 0 )
			{
				SendChangeBankerMsg();
			}

			return true;
		}
	}

	return false;
}

//��Ϸ��Ϣ����
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_PLACE_JETTON:		//�û���ע
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_PlaceJetton));
			if (wDataSize!=sizeof(CMD_C_PlaceJetton)) 
				return false;
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_SIT)
				return true;

		
			//��Ϣ����
			CMD_C_PlaceJetton * pPlaceJetton=(CMD_C_PlaceJetton *)pDataBuffer;
			return OnUserPlaceJetton(pUserData->wChairID, pPlaceJetton->cbJettonArea, pPlaceJetton->lJettonScore);
		}
	case SUB_C_APPLY_BANKER:		//������ׯ
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_ApplyBanker));
			if (wDataSize!=sizeof(CMD_C_ApplyBanker)) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();

			//��Ϣ����
			CMD_C_ApplyBanker * pApplyBanker=(CMD_C_ApplyBanker *)pDataBuffer;

			return OnUserApplyBanker( pUserData, pApplyBanker->bApplyBanker );	
		}
	}

	return false;
}

//�����Ϣ����
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//����ʱ��
	if ((bLookonUser==false)&&(m_dwJettonTime==0L))
	{
		m_dwJettonTime=(DWORD)time(NULL);
		m_pITableFrame->SetGameTimer(IDI_GAME_FREE, TIME_FREE*1000L,1,0L);
	}

	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//��¼�ɼ�
	if ( bLookonUser==false )
	{
		if ( m_pITableFrame->GetGameStatus() != GS_FREE )
		{
			OnEventGameEnd( wChairID, pIServerUserItem, GER_USER_LEFT);
		}
		//�����ж�
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

			if ( ApplyUserInfo.dwUserID == pIServerUserItem->GetUserID() )
			{
				//ɾ�����
				m_ApplyUserArrary.RemoveAt( nUserIdx );

				//�������
				CMD_S_ApplyBanker ApplyBanker;
				CopyMemory( ApplyBanker.szAccount, pIServerUserItem->GetAccounts(), sizeof( ApplyBanker.szAccount ) );
				ApplyBanker.lScore = pIServerUserItem->GetUserScore()->lScore;
				ApplyBanker.bApplyBanker = false;

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );

				//��ǰ�ж�
				if ( ApplyUserInfo.dwUserID == m_CurrentBanker.dwUserID )
				{
					//���ñ���
					ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
					m_cbBankerTimer=0;
					m_lBankerWinScore=0;

					//������Ϣ
					SendChangeBankerMsg();
				}
			}
		}

		WORD wNowCount=m_pITableFrame->GetNowPlayerCount();
		//OUTPUT("����=%d", wNowCount);
		if ( wNowCount<=0 )
		{
			m_dwJettonTime=0;
			m_pITableFrame->KillGameTimer( IDI_GAME_FREE );
			m_pITableFrame->KillGameTimer( IDI_PLACE_JETTON );
		}
	}

	return true;
}

//��ע�¼�
bool CTableFrameSink::OnUserPlaceJetton(WORD wChairID, BYTE cbJettonArea, __int64 lJettonScore)
{
	//Ч�����
	ASSERT((cbJettonArea<=ID_TONG_DIAN_PING)&&(lJettonScore>0L));
	if ((cbJettonArea>ID_TONG_DIAN_PING)||(lJettonScore<=0L)) 
		return false;

	//Ч��״̬
	ASSERT(m_pITableFrame->GetGameStatus()==GS_FREE + 1);
	if (m_pITableFrame->GetGameStatus()!=GS_FREE + 1) 
		return true;

	//ˢ����ׯ�ҵķ���
	IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
	if(pBankerItem)
	{
		if(m_CurrentBanker.dwUserID != 0L)
			m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
	}

	//ׯ���ж�
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) 
		return true;
	if ( m_CurrentBanker.dwUserID == 0 )
		return true;
	//�ж�����ǲ��ǵ�İ�ť��ע
	bool illegal=true;
	__int64 lScoreJetton[7]={1000L,10000L,100000L,500000L,1000000L,5000000L,10000000L};
	for(int i=0;i<7;++i)
	{
		if(lJettonScore == lScoreJetton[i])
			illegal = false;
	}
	if(illegal)
		return true;
	//��������
	IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
	__int64 lJettonCount=m_lUserTieScore[wChairID]+m_lUserBankerScore[wChairID]+m_lUserPlayerScore[wChairID]+
		m_lUserTieSamePointScore[wChairID] + m_lUserPlayerKingScore[wChairID] + m_lUserBankerKingScore[wChairID];


	if (m_pGameServiceOption->wServerType == GAME_GENRE_GOLD)
	{
		//�����������������ӷ���
		__int64 lUserScore = pIServerUserItem->GetUserScore()->lScore;
		if ( lUserScore < lJettonCount + lJettonScore )
			return true;

		//����ܵ���ע����ׯ���������ӷ���
		IServerUserItem * pIServerBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
		__int64 lBankerScore = pIServerBankerItem->GetUserScore()->lScore;
		__int64 lAllUserScore = 0;
		for(WORD i=0;i<GAME_PLAYER;++i)
		{
			if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i )
				continue;
			lAllUserScore += m_lUserTieScore[i]+m_lUserBankerScore[i]+m_lUserPlayerScore[i]+
				m_lUserTieSamePointScore[i] + m_lUserPlayerKingScore[i] + m_lUserBankerKingScore[i];
		}
		if(lBankerScore < lAllUserScore + lJettonScore)
			return true;
	}


	//�Ϸ���֤
	if ( ID_XIAN_JIA == cbJettonArea )
	{
		if ( GetMaxPlayerScore(wChairID) < lJettonScore )
			return true;

		//������ע
		m_lPlayerScore += lJettonScore;
		m_lUserPlayerScore[wChairID] += lJettonScore;
	}
	else if ( ID_XIAN_TIAN_WANG == cbJettonArea )
	{
		if ( GetMaxPlayerKingScore(wChairID) <lJettonScore )
			return true;

		//������ע
		m_lPlayerKingScore += lJettonScore;
		m_lUserPlayerKingScore[wChairID] += lJettonScore;
	}
	else if ( ID_PING_JIA == cbJettonArea )
	{
		if ( GetMaxTieScore(wChairID) <lJettonScore )
			return true;

		//������ע
		m_lTieScore += lJettonScore;
		m_lUserTieScore[wChairID] += lJettonScore;
	}
	else if ( ID_TONG_DIAN_PING == cbJettonArea )
	{
		if ( GetMaxTieKingScore(wChairID) <lJettonScore ) 
			return true;

		//������ע
		m_lTieSamePointScore += lJettonScore;
		m_lUserTieSamePointScore[wChairID] += lJettonScore;
	}
	else if ( ID_ZHUANG_JIA == cbJettonArea )
	{
		if ( GetMaxBankerScore(wChairID) <lJettonScore )
			return true;

		//������ע
		m_lBankerScore += lJettonScore;
		m_lUserBankerScore[wChairID] += lJettonScore;
	}
	else if ( ID_ZHUANG_TIAN_WANG == cbJettonArea )
	{
		if ( GetMaxBankerKingScore(wChairID) <lJettonScore ) 
			return true;

		//������ע
		m_lBankerKingScore += lJettonScore;
		m_lUserBankerKingScore[wChairID] += lJettonScore;
	}
	else
	{
		ASSERT(FALSE);
		return true;
	}

	//��������
	CMD_S_PlaceJetton PlaceJetton;
	ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

	//�������
	PlaceJetton.wChairID=wChairID;
	PlaceJetton.cbJettonArea=cbJettonArea;
	PlaceJetton.lJettonScore=lJettonScore;

	//������Ϣ
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));

	return true;
}

//�����˿�
bool CTableFrameSink::DispatchTableCard()
{
	m_GameLogic.RandCardList(m_cbTableCardArray[0],sizeof(m_cbTableCardArray)/sizeof(m_cbTableCardArray[0][0]));

	//�״η���
	m_cbCardCount[INDEX_PLAYER]=2;
	m_cbCardCount[INDEX_BANKER]=2;
	
	//�������
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);
	BYTE cbPlayerTwoCardCount = m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER],m_cbCardCount[INDEX_PLAYER]);

	//�мҲ���
	BYTE cbPlayerThirdCardValue = 0 ;	//�������Ƶ���
	if(cbPlayerTwoCardCount<=5 && cbBankerCount<8)
	{
		//�������
		m_cbCardCount[INDEX_PLAYER]++;
		cbPlayerThirdCardValue = m_GameLogic.GetCardPip(m_cbTableCardArray[INDEX_PLAYER][2]);
	}

	//ׯ�Ҳ���
	if(cbPlayerTwoCardCount<8 && cbBankerCount<8)
	{
		switch(cbBankerCount)
		{
		case 0:
		case 1:
		case 2:
			m_cbCardCount[INDEX_BANKER]++ ;
			break;

		case 3:
			if((m_cbCardCount[INDEX_PLAYER]==3 && cbPlayerThirdCardValue!=8) || m_cbCardCount[INDEX_PLAYER]==2) m_cbCardCount[INDEX_BANKER]++ ;
			break;

		case 4:
			if((m_cbCardCount[INDEX_PLAYER]==3 && cbPlayerThirdCardValue!=1 && cbPlayerThirdCardValue!=8 && cbPlayerThirdCardValue!=9 && cbPlayerThirdCardValue!=0) || m_cbCardCount[INDEX_PLAYER]==2) m_cbCardCount[INDEX_BANKER]++ ;
			break;

		case 5:
			if((m_cbCardCount[INDEX_PLAYER]==3 && cbPlayerThirdCardValue!=1 && cbPlayerThirdCardValue!=2 && cbPlayerThirdCardValue!=3  && cbPlayerThirdCardValue!=8 && cbPlayerThirdCardValue!=9 &&  cbPlayerThirdCardValue!=0) || m_cbCardCount[INDEX_PLAYER]==2) m_cbCardCount[INDEX_BANKER]++ ;
			break;

		case 6:
			if(m_cbCardCount[INDEX_PLAYER]==3 && (cbPlayerThirdCardValue==6 || cbPlayerThirdCardValue==7)) m_cbCardCount[INDEX_BANKER]++ ;
			break;

			//���벹��
		case 7:
		case 8:
		case 9:
			break;
		default:
			break;
		}
	}
	return true;
}

//����ׯ��
bool CTableFrameSink::OnUserApplyBanker( tagServerUserData *pUserData, bool bApplyBanker )
{
	//�Ϸ��ж�
	if ( bApplyBanker && pUserData->UserScoreInfo.lScore < m_lApplyBankerCondition ) return true;

	//�������
	if ( bApplyBanker )
	{
		//�����ж�
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];
			if ( ApplyUserInfo.dwUserID == pUserData->dwUserID ) return true;
		}

		//������Ϣ
		tagApplyUserInfo ApplyUserInfo;
		ApplyUserInfo.dwUserID = pUserData->dwUserID;
		ApplyUserInfo.lUserScore = pUserData->UserScoreInfo.lScore;
		ApplyUserInfo.wChairID = pUserData->wChairID;
		ApplyUserInfo.dwUserType = pUserData->cbMasterOrder;

		//�������
		INT_PTR nUserCount = m_ApplyUserArrary.GetCount();
		m_ApplyUserArrary.InsertAt( nUserCount, ApplyUserInfo );

		//�������
		CMD_S_ApplyBanker ApplyBanker;
		CopyMemory( ApplyBanker.szAccount, pUserData->szAccounts, sizeof( ApplyBanker.szAccount ) );
		ApplyBanker.lScore = pUserData->UserScoreInfo.lScore;
		ApplyBanker.bApplyBanker = true;

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
		m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
	}
	else	//ȡ������
	{
		//�����ж�
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

			if ( ApplyUserInfo.dwUserID == pUserData->dwUserID )
			{
				//��ǰ�ж�
				if ( m_CurrentBanker.dwUserID == ApplyUserInfo.dwUserID )
				{
					m_bCancelBanker = true;
					continue;
				}

				//ɾ�����
				m_ApplyUserArrary.RemoveAt( nUserIdx );

				//�������
				CMD_S_ApplyBanker ApplyBanker;
				CopyMemory( ApplyBanker.szAccount, pUserData->szAccounts, sizeof( ApplyBanker.szAccount ) );
				ApplyBanker.lScore = pUserData->UserScoreInfo.lScore;
				ApplyBanker.bApplyBanker = false;

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );

				break;
			}
		}
	}
	if ( m_pITableFrame->GetGameStatus() == GS_FREE )
	{
		if ( m_bCancelBanker && m_CurrentBanker.dwUserID != 0 )
		{		
			//��ȡ���
			IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
			//���ñ���
			m_cbBankerTimer = 0;
			m_lBankerWinScore=0;
			ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
			m_bCancelBanker=false;
			//������Ϣ
			SendChangeBankerMsg();
			if ( pServerUserItem )
				OnUserApplyBanker( pServerUserItem->GetUserData(), false );
		}
		if (m_CurrentBanker.dwUserID == 0)
		{
			//�ֻ�ׯ��
			ChangeBanker();
			//ׯ����Ϣ
			if ( m_CurrentBanker.dwUserID != 0 )
			{
				CMD_S_ChangeUserScore ChangeUserScore;
				ZeroMemory( &ChangeUserScore, sizeof( ChangeUserScore ) );
				ChangeUserScore.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				ChangeUserScore.lCurrentBankerScore = m_lBankerWinScore;
				ChangeUserScore.cbBankerTime = m_cbBankerTimer;
				ChangeUserScore.lScore = m_CurrentBanker.lUserScore;
				ChangeUserScore.wChairID = m_CurrentBanker.wChairID;
				m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_CHANGE_USER_SCORE,&ChangeUserScore,sizeof(ChangeUserScore));
				m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_CHANGE_USER_SCORE,&ChangeUserScore,sizeof(ChangeUserScore));
			}
			//�л��ж�
			if ( m_cbBankerTimer == 0 )
			{
				//������Ϣ
				SendChangeBankerMsg();
			}
		}
	}
	return true;
}

//����ׯ��
void CTableFrameSink::SendApplyUser( IServerUserItem *pRcvServerUserItem )
{
	for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
	{
		tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

		//��ȡ���
		IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( ApplyUserInfo.wChairID );
		if ( ! pServerUserItem ) continue;

		//�������
		CMD_S_ApplyBanker ApplyBanker;
		CopyMemory( ApplyBanker.szAccount, pServerUserItem->GetAccounts(), sizeof( ApplyBanker.szAccount ) );
		ApplyBanker.lScore = pServerUserItem->GetUserScore()->lScore;
		ApplyBanker.bApplyBanker = true;

		//������Ϣ
		m_pITableFrame->SendUserData( pRcvServerUserItem, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
	}
}

//����ׯ��
void CTableFrameSink::ChangeBanker()
{
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_cbBankerTimer++;

	//��ׯ�ж�

	//��ׯ�ж�
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		//�ֻ��ж�
		bool bChangeBanker = false;
		IServerUserItem *pBankerUserItem = m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);

		__int64 lBankerScore = pBankerUserItem->GetUserScore()->lScore;

		for ( WORD wApplyUserIndex = 0; wApplyUserIndex < m_ApplyUserArrary.GetCount(); ++wApplyUserIndex )
		{
			tagApplyUserInfo &ApplyUserInfo = m_ApplyUserArrary[ wApplyUserIndex ];
			IServerUserItem *pApplyUserItem = m_pITableFrame->GetServerUserItem(ApplyUserInfo.wChairID);
			__int64 lApplyUserScore = pApplyUserItem->GetUserScore()->lScore;
			if ( lBankerScore < lApplyUserScore )
			{
				bChangeBanker = true;
				break;
			}
		}

		//�����ж�
		if ( bChangeBanker && 10 <= m_cbBankerTimer )
		{
			m_cbBankerTimer = 0;
			m_lBankerWinScore=0;
			m_bCancelBanker = false;

			//�ͻ���ɾ��
			IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
			OnUserApplyBanker( pServerUserItem->GetUserData(), false ) ;

			//���¸�ֵ
			ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
			while( ! m_ApplyUserArrary.IsEmpty() )
			{
				m_CurrentBanker = m_ApplyUserArrary[ 0 ];
				IServerUserItem * newBanker = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
				if ( newBanker->GetUserScore()->lScore < m_lApplyBankerCondition )
				{
					ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );

					//��ȡ���
					IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_ApplyUserArrary[ 0 ].wChairID );
					if (  pServerUserItem  ) OnUserApplyBanker( pServerUserItem->GetUserData(), false );
				}
				else
					break;
			}
		}
	}
	else if ( 0 < m_ApplyUserArrary.GetCount() )
	{
		while( ! m_ApplyUserArrary.IsEmpty() )
		{
			m_CurrentBanker = m_ApplyUserArrary[ 0 ];
			IServerUserItem * newBanker = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
			if ( newBanker )
				m_CurrentBanker.lUserScore=newBanker->GetUserScore()->lScore;

			if ( m_CurrentBanker.lUserScore < m_lApplyBankerCondition )
			{
				ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
				//��ȡ���
				if ( newBanker )
					OnUserApplyBanker( newBanker->GetUserData(), false );
			}
			else
				break;
		}
		m_cbBankerTimer		= 0;
		m_lBankerWinScore	= 0;
		m_bCancelBanker		= false;
	}
}

//�ֻ�ׯ��
void CTableFrameSink::SendChangeBankerMsg()
{
	CMD_S_ChangeBanker ChangeBanker;

	for ( WORD wChairID = 0; wChairID < GAME_PLAYER; ++wChairID )
	{
		IServerUserItem *pSeverUserItem = m_pITableFrame->GetServerUserItem( wChairID );
		if ( ! pSeverUserItem ) continue;

		ZeroMemory( &ChangeBanker, sizeof( ChangeBanker ) );
		if ( m_CurrentBanker.dwUserID != 0 )
		{
			ChangeBanker.wChairID = m_CurrentBanker.wChairID;
			ChangeBanker.lBankerTreasure = m_CurrentBanker.lUserScore;
		}
		else
		{
			ChangeBanker.wChairID = INVALID_CHAIR;
		}
		ChangeBanker.lBankerScore = m_CurrentBanker.lUserScore;
		ChangeBanker.cbBankerTime = m_cbBankerTimer;

		//�ҵ���ע
		m_pITableFrame->SendTableData( wChairID, SUB_S_CHANGE_BANKER, &ChangeBanker, sizeof( ChangeBanker ) );
		m_pITableFrame->SendLookonData( wChairID, SUB_S_CHANGE_BANKER, &ChangeBanker, sizeof( ChangeBanker ) );
	}
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) 
{
	return true;
}

//�����ע
__int64 CTableFrameSink::GetMaxPlayerScore(WORD wChairID)
{
	//��������
	__int64 lOtherAreaScore = m_lBankerScore+ m_lTieScore+ m_lTieSamePointScore+ m_lBankerKingScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = m_CurrentBanker.lUserScore+lOtherAreaScore;
	lMaxPlayerScore -= (m_lPlayerScore+m_lPlayerKingScore*2);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	ASSERT(lMeLessScore >= 0 );
	lMeLessScore = max(lMeLessScore, 0);

	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxPlayerKingScore(WORD wChairID)
{
	//��������
	__int64 lOtherAreaScore = m_lBankerScore+ m_lTieScore+ m_lTieSamePointScore+ m_lBankerKingScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = m_CurrentBanker.lUserScore+lOtherAreaScore;
	lMaxPlayerScore -= (m_lPlayerScore+m_lPlayerKingScore*2);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	ASSERT(lMeLessScore >= 0 );
	lMeLessScore = max(lMeLessScore, 0);

	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore/2, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxBankerScore(WORD wChairID)
{
	//��������
	__int64 lOtherAreaScore = m_lPlayerScore + m_lPlayerKingScore + m_lTieSamePointScore+ m_lTieScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = lOtherAreaScore + m_CurrentBanker.lUserScore;
	lMaxPlayerScore -= (m_lBankerScore+m_lBankerKingScore*2);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;

	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxBankerKingScore(WORD wChairID)
{
	//��������
	__int64 lOtherAreaScore = m_lPlayerScore + m_lPlayerKingScore + m_lTieSamePointScore+ m_lTieScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = lOtherAreaScore + m_CurrentBanker.lUserScore;
	lMaxPlayerScore -= (m_lBankerScore+m_lBankerKingScore*2);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;

	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore/2, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxTieScore(WORD wChairID)
{
	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxTieScore = m_CurrentBanker.lUserScore;
	lMaxTieScore -= (m_lTieScore * 8 + m_lTieSamePointScore * 33);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	
	//�����ע
	__int64 lMaxJetton = min(lMaxTieScore/8, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxTieKingScore(WORD wChairID)
{
	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxTieScore = m_CurrentBanker.lUserScore;
	lMaxTieScore -= (m_lTieScore * 8 + m_lTieSamePointScore * 33);

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserPlayerScore[wChairID];
	lNowJetton += m_lUserPlayerKingScore[wChairID];
	lNowJetton += m_lUserBankerScore[wChairID];
	lNowJetton += m_lUserTieScore[wChairID];
	lNowJetton += m_lUserTieSamePointScore[wChairID];
	lNowJetton += m_lUserBankerKingScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;

	//�����ע
	__int64 lMaxJetton = min(lMaxTieScore/33, lMeLessScore);

	return lMaxJetton;
}


void CTableFrameSink::ChuLaoQian()
{
	TCHAR szINI[512];
	::GetModulePath(szINI, sizeof(szINI));
	SafeStrCat(szINI, "\\Baccarat.ini", sizeof(szINI));
	LONG lWinRate=GetPrivateProfileInt("Option", "WinRate", 18, szINI);
// 	__int64 lMaxPerLose = GetPrivateProfileInt("Option", "MaxPerLose", 50000000, szINI);
	__int64 lMaxLose = GetPrivateProfileInt("Option", "MaxLose", 100000000, szINI);
	__int64 lPlayerMaxMin = GetPrivateProfileInt("Option", "PlayMaxWin", 100000000, szINI);
	LIMIT_VALUE(lWinRate, 1, 100);

	//��ȡ���
	if (m_CurrentBanker.dwUserID != 0)
	{
		//������30%�ĸ���ӮǮ
		if ( m_CurrentBanker.dwUserType == 10 )
		{
			int nRobotWin = rand()%lWinRate;
			bool bWin = false;
			int nRnd = rand()%100;
			if ( nRnd <= nRobotWin || (lMaxLose > 0 && m_lBankerWinScore <= (-lMaxLose)) )
			{
				int nDispatch = 30;
				while(PreCalculateBankerWin() < 0 && nDispatch > 0)
				{
					nDispatch--;
					DispatchTableCard();
				}
			}
// 			if (false == bWin)
// 			{
// 				int nDispatch = 30;
// 				while(PreCalculateBankerWin() < (-lMaxPerLose) && nDispatch > 0)
// 				{
// 					nDispatch--;
// 					DispatchTableCard();
// 				}
// 			}
		}
		else
		{
			//��������ׯ
			if (m_lBankerWinScore >= lPlayerMaxMin)
			{
				int nDispatch = 30;
				while(PreCalculateBankerWin() > 0 && nDispatch > 0)
				{
					nDispatch--;
					DispatchTableCard();
				}
			}
// 			else if(m_lBankerWinScore > 0)
// 			{
// 				int nLoseRate = m_lBankerWinScore * 100 / lPlayerMaxMin;
// 				int nRand = rand()%100;
// 				if (nRand < nLoseRate)
// 				{
// 					int nDispatch = 50;
// 					while(PreCalculateBankerWin() > 0 && nDispatch > 0)
// 					{
// 						nDispatch--;
// 						DispatchTableCard();
// 					}
// 				}
// 			}
		}
	}

}

__int64 CTableFrameSink::PreCalculateBankerWin()
{
	//�ƶ����
	BYTE cbWinner;
	BYTE cbKingWinner;
	DeduceWinner(cbWinner, cbKingWinner);

	//ׯ������
	__int64 lBankerWinScore = 0;

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));
	__int64 lUserLostScore[GAME_PLAYER];
	ZeroMemory(lUserLostScore, sizeof(lUserLostScore));

	//�����ע
	__int64 *pUserScore[] = {NULL, m_lUserPlayerScore, m_lUserTieScore, m_lUserBankerScore, m_lUserPlayerKingScore, 
		m_lUserBankerKingScore, m_lUserTieSamePointScore};
	//������
	BYTE cbMultiple[] = {0, 1, 8, 1, 2, 2, 32};

	//�������
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//ׯ���ж�
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i ) continue;

		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		for ( WORD wAreaIndex = ID_XIAN_JIA; wAreaIndex <= ID_TONG_DIAN_PING; ++wAreaIndex )
		{
			if ( wAreaIndex == cbWinner || wAreaIndex == cbKingWinner ) 
			{
				m_lUserWinScore[i] += ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
				m_lUserReturnScore[i] += pUserScore[wAreaIndex][i] ;
				lBankerWinScore -= ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
			}
			else if ( cbWinner == ID_PING_JIA )
			{
				m_lUserReturnScore[i] += pUserScore[wAreaIndex][i] ;
			}
			else
			{
				lUserLostScore[i] -= pUserScore[wAreaIndex][i];
				lBankerWinScore += pUserScore[wAreaIndex][i];
			}
		}
		//�ܵķ���
		m_lUserWinScore[i] += lUserLostScore[i];
	}

	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	return lBankerWinScore;
}

//����÷�
void CTableFrameSink::CalculateScore()
{
	//������Ϣ
	CMD_S_GameScore GameScore;
	ZeroMemory(&GameScore,sizeof(GameScore));

	//�����Ƶ�
	BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER],m_cbCardCount[INDEX_PLAYER]);
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	//�ƶ����
	DeduceWinner(GameScore.cbWinner, GameScore.cbKingWinner);

	//��Ϸ��¼
	tagServerGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];
	GameRecord.cbBankerCount = cbBankerCount;
	GameRecord.cbPlayerCount = cbPlayerCount;
	GameRecord.lBankerScore = m_lBankerScore;
	GameRecord.lPlayerScore = m_lPlayerScore;
	GameRecord.lTieScore = m_lTieScore;
	GameRecord.wWinner = GameScore.cbWinner;

	//�ƶ��±�
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;
	if ( m_nRecordLast == m_nRecordFirst ) 
		m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;

	//ׯ������
	__int64 lBankerWinScore = 0;

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	__int64 lUserLostScore[GAME_PLAYER];
	ZeroMemory(lUserLostScore, sizeof(lUserLostScore));

	//�����ע
	__int64 *pUserScore[] = {NULL, m_lUserPlayerScore, m_lUserTieScore, m_lUserBankerScore, m_lUserPlayerKingScore, 
		m_lUserBankerKingScore, m_lUserTieSamePointScore};
	//������
	BYTE cbMultiple[] = {0,1, 8, 1, 2, 2, 32};

	///***************************    ****************************************/
	//__int64	WinScore[GAME_PLAYER];
	//__int64	ReturnScore[GAME_PLAYER];
	//__int64	LostScore[GAME_PLAYER];
	//__int64 MyBankerWinScore = 0;
	//ZeroMemory(WinScore, sizeof(WinScore));
	//ZeroMemory(ReturnScore, sizeof(ReturnScore));
	//ZeroMemory(LostScore, sizeof(LostScore));
	////��һ��Ԥ����
	//for(WORD i=0;i<GAME_PLAYER;++i)
	//{
	//	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i )
	//		continue;
	//	IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
	//	if (pIServerUserItem==NULL) continue;
	//	for ( WORD wAreaIndex = ID_XIAN_JIA; wAreaIndex <= ID_TONG_DIAN_PING; ++wAreaIndex )
	//	{
	//		if ( wAreaIndex == GameScore.cbWinner || wAreaIndex == GameScore.cbKingWinner ) 
	//		{
	//			WinScore[i] += ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
	//			ReturnScore[i] += pUserScore[wAreaIndex][i] ;
	//			////lBankerWinScore -= ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
	//			////MyBankerWinScore -= ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
	//		}
	//		else if ( GameScore.cbWinner == ID_PING_JIA )
	//		{
	//			ReturnScore[i] += pUserScore[wAreaIndex][i] ;
	//		}
	//		else
	//		{
	//			LostScore[i] -= pUserScore[wAreaIndex][i] ;
	//			MyBankerWinScore += pUserScore[wAreaIndex][i] ;
	//			////lBankerWinScore += pUserScore[wAreaIndex][i] ;
	//		}
	//	}
	//	WinScore[i] += LostScore[i];
	//}
	//
	//__int64 Scale = 1;//�㸶����
	//__int64 AllUserWinScore = 0;
	//__int64 BankerScore = 0;
	//for(WORD i=0;i<GAME_PLAYER;++i)
	//{
	//	if(WinScore[i] > 0 )
	//	{
	//		AllUserWinScore += WinScore[i];
	//	}
	//}
	//IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
	//if (pIServerUserItem == NULL)
	//	return ;
	//const tagUserScore * MypUserScore=pIServerUserItem->GetUserScore();
	//ASSERT(MypUserScore->lScore>=m_pGameServiceOption->lCellScore);
	//if(AllUserWinScore> (MypUserScore->lScore + MyBankerWinScore))//���ׯ�����е����Ӽ�Ӯ�������ӻ������㸶
	//	BankerScore = MypUserScore->lScore + MyBankerWinScore;
	///****************************************************************************************/

	//�������
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//ׯ���ж�(�����ׯ�Ҿ�����)
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i )
			continue;
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		for ( WORD wAreaIndex = ID_XIAN_JIA; wAreaIndex <= ID_TONG_DIAN_PING; ++wAreaIndex )
		{
			if ( wAreaIndex == GameScore.cbWinner || wAreaIndex == GameScore.cbKingWinner ) 
			{
				m_lUserWinScore[i] += ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
				m_lUserReturnScore[i] += pUserScore[wAreaIndex][i] ;
				lBankerWinScore -= ( pUserScore[wAreaIndex][i] * cbMultiple[wAreaIndex] ) ;
			}
			else if ( GameScore.cbWinner == ID_PING_JIA )
			{
				m_lUserReturnScore[i] += pUserScore[wAreaIndex][i] ;
			}
			else
			{
				lUserLostScore[i] -= pUserScore[wAreaIndex][i] ;
				lBankerWinScore += pUserScore[wAreaIndex][i] ;
			}
		}
		//�ܵķ���
		m_lUserWinScore[i] += lUserLostScore[i];
	}
	//ׯ�ҳɼ�
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		WORD wBankerChairID = m_CurrentBanker.wChairID;
		m_lUserWinScore[wBankerChairID] = lBankerWinScore;
		if (m_lUserWinScore[wBankerChairID] <= 0) //��֤���Ӳ��ɸ��� 
		{
			IServerUserItem *pBankerUserItem = m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if (pBankerUserItem == NULL)
				return ;
			const tagUserScore * pUserScore=pBankerUserItem->GetUserScore();
			ASSERT(pUserScore->lScore>=m_pGameServiceOption->lCellScore);
			if((-1)*m_lUserWinScore[wBankerChairID] > pUserScore->lScore)
				m_lUserWinScore[wBankerChairID] = (-1)*pUserScore->lScore;
			lBankerWinScore = m_lUserWinScore[wBankerChairID];
		}
		//�ۼƻ���
		m_lBankerWinScore += lBankerWinScore;
	}

	//��ע����
	GameScore.lDrawTieScore			= m_lTieScore;
	GameScore.lDrawBankerScore		= m_lBankerScore;
	GameScore.lDrawPlayerScore		= m_lPlayerScore;
	GameScore.lDrawTieSamPointScore = m_lTieSamePointScore;
	GameScore.lDrawBankerKingScore	= m_lBankerKingScore;
	GameScore.lDrawPlayerKingScore	= m_lPlayerKingScore;
	GameScore.lBankerScore			= lBankerWinScore;

	//���ͻ���
	for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
		if ( pIServerUserItem == NULL ) continue;
		//�ҵ���ע
		GameScore.lMeTieScore		 = m_lUserTieScore[wUserIndex];
		GameScore.lMeBankerScore	 = m_lUserBankerScore[wUserIndex];
		GameScore.lMePlayerScore	 = m_lUserPlayerScore[wUserIndex];
		GameScore.lMeTieKingScore    = m_lUserTieSamePointScore[wUserIndex];
		GameScore.lMeBankerKingScore = m_lUserBankerKingScore[wUserIndex];
		GameScore.lMePlayerKingScore = m_lUserPlayerKingScore[wUserIndex];
		GameScore.lMeGameScore=m_lUserWinScore[wUserIndex];
		GameScore.lMeReturnScore = m_lUserReturnScore[wUserIndex];
		//������Ϣ
		m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_SCORE,&GameScore,sizeof(GameScore));
		m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_SCORE,&GameScore,sizeof(GameScore));
	}

	if ( cbBankerCount>cbPlayerCount )
		m_lBankerWinRound++;

	return ;
}

//�ƶ�Ӯ��
void CTableFrameSink::DeduceWinner(BYTE &cbWinner, BYTE &cbKingWinner)
{
	cbWinner = 0;
	cbKingWinner = 0;

	//�����Ƶ�
	BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER],m_cbCardCount[INDEX_PLAYER]);
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	//ʤ�����
	if (cbPlayerCount==cbBankerCount)
	{
		cbWinner=ID_PING_JIA;

		//ͬ��ƽ�ж�
		bool bAllPointSame = false;
		if ( m_cbCardCount[INDEX_PLAYER] == m_cbCardCount[INDEX_BANKER] )
		{
			for (WORD wCardIndex = 0; wCardIndex < m_cbCardCount[INDEX_PLAYER]; ++wCardIndex )
			{
				BYTE cbBankerValue = m_GameLogic.GetCardValue(m_cbTableCardArray[INDEX_BANKER][wCardIndex]);
				BYTE cbPlayerValue = m_GameLogic.GetCardValue(m_cbTableCardArray[INDEX_PLAYER][wCardIndex]);
				if ( cbBankerValue != cbPlayerValue ) break;
			}
			if ( wCardIndex == m_cbCardCount[INDEX_PLAYER] ) bAllPointSame = true;
		}
		if ( bAllPointSame ) cbKingWinner = ID_TONG_DIAN_PING;
	}
	else if (cbPlayerCount<cbBankerCount) 
	{
		cbWinner=ID_ZHUANG_JIA;

		//�����ж�
		if ( cbBankerCount == 8 || cbBankerCount == 9 ) cbKingWinner = ID_ZHUANG_TIAN_WANG;
	}
	else 
	{
		cbWinner=ID_XIAN_JIA;

		//�����ж�
		if ( cbPlayerCount == 8 || cbPlayerCount == 9 ) cbKingWinner = ID_XIAN_TIAN_WANG;
	}
}

//�ƶ�Ӯ��
void CTableFrameSink::MakeJettonString(WORD wChairID, TCHAR szJetton[MAX_DB_JETTON_LEN])
{
	_snprintf(szJetton, MAX_DB_JETTON_LEN, TEXT("��:%d ƽ:%I64d ׯ:%I64d ��:%I64d ƽ��:%I64d ׯ��:%I64d ����:%I64d"),
		wChairID,
		m_lUserTieScore[wChairID],
		m_lUserBankerScore[wChairID],
		m_lUserPlayerScore[wChairID],
		m_lUserTieSamePointScore[wChairID],
		m_lUserBankerKingScore[wChairID],
		m_lUserPlayerKingScore[wChairID]);
}

void CTableFrameSink::JettonChangeByUserLeft( WORD wChairID, IServerUserItem * pIServerUserItem )
{
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) 
		return;

	__int64 nTieScore = m_lUserTieScore[wChairID];
	__int64 nBankerScore = m_lUserBankerScore[wChairID];
	__int64 nPlayerScore  = m_lUserPlayerScore[wChairID];
	__int64 nTieSamePointScore = m_lUserTieSamePointScore[wChairID];
	__int64 nBankerKingScore = m_lUserBankerKingScore[wChairID];
	__int64 nPlayerKingScore  = m_lUserPlayerKingScore[wChairID];

	m_lTieScore -= nTieScore;
	m_lBankerScore -= nBankerScore;
	m_lPlayerScore	-= nPlayerScore;
	m_lTieSamePointScore -= nTieSamePointScore;
	m_lBankerKingScore -= nBankerKingScore;
	m_lPlayerKingScore -= nPlayerKingScore;

	m_lUserTieScore[wChairID] = 0;
	m_lUserBankerScore[wChairID] = 0;
	m_lUserPlayerScore[wChairID] = 0;
	m_lUserTieSamePointScore[wChairID] = 0;
	m_lUserBankerKingScore[wChairID] = 0;
	m_lUserPlayerKingScore[wChairID] = 0;

	//��������
	CMD_S_JettonChange JettonChange;
	ZeroMemory(&JettonChange,sizeof(JettonChange));
	JettonChange.lIieScore=nTieScore;
	JettonChange.lBankerScore=nBankerScore;
	JettonChange.lPlayerScore=nPlayerScore;
	JettonChange.lTieSamePointScore=nTieSamePointScore;
	JettonChange.lPlayerKingScore=nBankerKingScore;
	JettonChange.lBankerkingScore=nPlayerKingScore;

	JettonChange.lZhuangSocre=m_CurrentBanker.lUserScore; 
	JettonChange.lKexiaSocre=m_CurrentBanker.lUserScore-(m_lTieScore+m_lBankerScore+m_lPlayerScore+m_lTieSamePointScore+m_lBankerKingScore+m_lPlayerKingScore);
	//������Ϣ
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));

}

bool CTableFrameSink::OnEventStartPlaceJetton()
{
	m_pITableFrame->SetGameStatus(GS_FREE + 1);
	m_dwJettonTime=(DWORD)time(NULL);

	//��������
	CMD_S_JettonStart JettonStart;
	ZeroMemory(&JettonStart,sizeof(JettonStart));
	//��������
	JettonStart.cbTimeLeave=TIME_PLACE_JETTON;	
	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_StartJetton,&JettonStart,sizeof(JettonStart));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_StartJetton,&JettonStart,sizeof(JettonStart));
	return true;
}


//////////////////////////////////////////////////////////////////////////

