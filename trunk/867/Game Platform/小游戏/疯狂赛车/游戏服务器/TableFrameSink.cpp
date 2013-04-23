#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////


//��עʱ��
#define IDI_PLACE_JETTON			1									//��עʱ��
#define TIME_PLACE_JETTON			20									//��עʱ��

//����ʱ��
#define IDI_GAME_END				2									//����ʱ��
#define TIME_GAME_END				15									//����ʱ��

#define IDI_GAME_FREE				3									//���н׶�
#define TIME_FREE					10									//����ʱ��

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

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��ע��Ϣ
	m_lAllBigTigerScore=0L;
	m_lAllSmlTigerScore=0L;
	m_lAllBigBogScore=0L;
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;
	m_lAllSmlSnakeScore=0L;

	//״̬����
	m_dwJettonTime=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserBigTigerScore,sizeof(m_lUserBigTigerScore));
	ZeroMemory(m_lUserSmlTigerScore,sizeof(m_lUserSmlTigerScore));
	ZeroMemory(m_lUserBigBogScore,  sizeof(m_lUserBigBogScore));
	ZeroMemory(m_lUserSmlBogScore,  sizeof(m_lUserSmlBogScore));
	ZeroMemory(m_lUserBigHorseScore,sizeof(m_lUserBigHorseScore));
	ZeroMemory(m_lUserSmlHorseScore,sizeof(m_lUserSmlHorseScore));
	ZeroMemory(m_lUserBigSnakeScore,sizeof(m_lUserBigSnakeScore));
	ZeroMemory(m_lUserSmlSnakeScore,sizeof(m_lUserSmlSnakeScore));

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	//�˿���Ϣ
	m_cbAnimalBox=0;

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

	//���ƽӿ�
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
	m_lAllBigTigerScore=0L;
	m_lAllSmlTigerScore=0L;
	m_lAllBigBogScore=0L;
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;
	m_lAllSmlSnakeScore=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserBigTigerScore,sizeof(m_lUserBigTigerScore));
	ZeroMemory(m_lUserSmlTigerScore,sizeof(m_lUserSmlTigerScore));
	ZeroMemory(m_lUserBigBogScore,sizeof(m_lUserBigBogScore));
	ZeroMemory(m_lUserSmlBogScore,sizeof(m_lUserSmlBogScore));
	ZeroMemory(m_lUserBigHorseScore,sizeof(m_lUserBigHorseScore));
	ZeroMemory(m_lUserSmlHorseScore,sizeof(m_lUserSmlHorseScore));
	ZeroMemory(m_lUserBigSnakeScore,sizeof(m_lUserBigSnakeScore));
	ZeroMemory(m_lUserSmlSnakeScore,sizeof(m_lUserSmlSnakeScore));

	//�˿���Ϣ
	m_cbAnimalBox=0;

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

	//��������
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));

	MakeAnimate();

	ChuLaoQian();

	//��������
	GameStart.cbAnimalBox=m_cbAnimalBox;
	GameStart.cbTimeLeave=(m_cbAnimalBox*ANIMAL_ROLL_SPEED)/1000+TIME_GAME_END;
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
			GameEnd.cbWinner=DeduceWinner();			

			//д�����
			for ( WORD wUserChairID = 0; wUserChairID < GAME_PLAYER; ++wUserChairID )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserChairID);
				if ( pIServerUserItem == NULL ) continue;

				//ʤ������
				enScoreKind ScoreKind=(m_lUserWinScore[wUserChairID]>0L)?enScoreKind_Win:enScoreKind_Lost;

				//д�����
				if (m_lUserWinScore[wUserChairID]!=0L) 
					m_pITableFrame->WriteUserScore(wUserChairID,m_lUserWinScore[wUserChairID], 0, ScoreKind);

				//ׯ���ж�
				if ( m_CurrentBanker.dwUserID == pIServerUserItem->GetUserID() ) 
					m_CurrentBanker.lUserScore = pIServerUserItem->GetUserScore()->lScore;
			}

			//���ͻ���
			GameEnd.cbTimeLeave=TIME_FREE;	
			if ( m_CurrentBanker.dwUserID != 0 ) GameEnd.lBankerTreasure = m_CurrentBanker.lUserScore;
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

// 			TCHAR szPokerInfo[MAX_DB_JETTON_LEN]={0};
// 			TCHAR szPointInfo[MAX_DB_JETTON_LEN]={0};
// 			_snprintf(szPokerInfo, CountArray(szPokerInfo), TEXT("AnimalBox=%d"), m_cbAnimalBox);
// 			_snprintf(szPointInfo, CountArray(szPointInfo), TEXT("Winner:%d"), GameEnd.cbWinner);
// 			m_pITableFrame->WriteRoundInfomation(szPokerInfo, szPointInfo, m_CurrentBanker.dwUserID, m_lBankerWinScore);

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
	case GER_USER_LEFT:		//�û��뿪
		{
			//ʤ������
			__int64	allZhu=0;
			if ( pIServerUserItem->GetUserID()==m_CurrentBanker.dwUserID ) //ׯ��ǿ��
			{
				allZhu=Get_ALL_MultiDesktopScore();
			}
			else
			{
				//��Ѻע״̬�£������˳����۷�
				if (m_pITableFrame->GetGameStatus() == GS_FREE + 1)
				{
					JettonChangeByUserLeft( wChairID, pIServerUserItem);
				}
				else
				{
					allZhu=Get_User_DesktopScore(wChairID);
				}
			}

			if ( allZhu>0 )
			{
				if ( allZhu >pIServerUserItem->GetUserScore()->lScore )
					allZhu=pIServerUserItem->GetUserScore()->lScore;
				//��������
				tagScoreInfo ScoreInfo;
				ZeroMemory(&ScoreInfo,sizeof(ScoreInfo));

				//���ñ���
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
			//���ͼ�¼
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
				CopyMemory(cbBuffer+wBufferSize, &m_GameRecordArrary[nIndex], sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}

			if (wBufferSize>0) m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);

			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			//��ע��Ϣ
			StatusFree.lBigTigerScore	= m_lAllBigTigerScore;
			StatusFree.lSmlTigerScore	= m_lAllSmlTigerScore;
			StatusFree.lBigBogScore		= m_lAllBigBogScore;
			StatusFree.lSmlBogScore		= m_lAllSmlBogScore;
			StatusFree.lBigHorseScore   = m_lAllBigHorseScore;
			StatusFree.lSmlHorseScore	= m_lAllSmlHorseScore;
			StatusFree.lBigSnakeScore   = m_lAllBigSnakeScore;
			StatusFree.lSmlSnakeScore	= m_lAllSmlSnakeScore;

			//ׯ����Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lMeMaxScore	= pIServerUserItem->GetUserScore()->lScore;
				//-------------------------------------------------------------------
				StatusFree.lMeBigTigerScore	= m_lUserBigTigerScore[wChiarID];
				StatusFree.lMeSmlTigerScore	= m_lUserSmlTigerScore[wChiarID];
				StatusFree.lMeBigBogScore	= m_lUserBigBogScore[wChiarID];
				StatusFree.lMeSmlBogScore	= m_lUserSmlBogScore[wChiarID];
				StatusFree.lMeSmlBogScore	= m_lUserBigHorseScore[wChiarID];
				StatusFree.lMeBigHorseScore = m_lUserSmlHorseScore[wChiarID];
				StatusFree.lMeSmlHorseScore	= m_lUserBigSnakeScore[wChiarID];
				StatusFree.lMeBigHorseScore = m_lUserSmlSnakeScore[wChiarID];
			}

			if ( m_CurrentBanker.dwUserID != 0 ) 
			{
				StatusFree.cbBankerTime = m_cbBankerTimer;
				StatusFree.lCurrentBankerScore = m_lBankerWinScore;
				StatusFree.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				StatusFree.lBankerTreasure = m_CurrentBanker.lUserScore;
			}
			else 
				StatusFree.wCurrentBankerChairID = INVALID_CHAIR;
			
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
			//���ͼ�¼
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
				CopyMemory(cbBuffer+wBufferSize, &m_GameRecordArrary[nIndex], sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}

			if (wBufferSize>0) m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);

			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			//��ע��Ϣ
			StatusFree.lBigTigerScore	= m_lAllBigTigerScore;
			StatusFree.lSmlTigerScore	= m_lAllSmlTigerScore;
			StatusFree.lBigBogScore		= m_lAllBigBogScore;
			StatusFree.lSmlBogScore		= m_lAllSmlBogScore;
			StatusFree.lBigHorseScore   = m_lAllBigHorseScore;
			StatusFree.lSmlHorseScore	= m_lAllSmlHorseScore;
			StatusFree.lBigSnakeScore   = m_lAllBigSnakeScore;
			StatusFree.lSmlSnakeScore	= m_lAllSmlSnakeScore;

			//ׯ����Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lMeMaxScore	= pIServerUserItem->GetUserScore()->lScore;
				//-------------------------------------------------------------------
				StatusFree.lMeBigTigerScore	= m_lUserBigTigerScore[wChiarID];
				StatusFree.lMeSmlTigerScore	= m_lUserSmlTigerScore[wChiarID];
				StatusFree.lMeBigBogScore	= m_lUserBigBogScore[wChiarID];
				StatusFree.lMeSmlBogScore	= m_lUserSmlBogScore[wChiarID];
				StatusFree.lMeSmlBogScore	= m_lUserBigHorseScore[wChiarID];
				StatusFree.lMeBigHorseScore = m_lUserSmlHorseScore[wChiarID];
				StatusFree.lMeSmlHorseScore	= m_lUserBigSnakeScore[wChiarID];
				StatusFree.lMeBigHorseScore = m_lUserSmlSnakeScore[wChiarID];
			}

			if ( m_CurrentBanker.dwUserID != 0 ) 
			{
				StatusFree.cbBankerTime = m_cbBankerTimer;
				StatusFree.lCurrentBankerScore = m_lBankerWinScore;
				StatusFree.wCurrentBankerChairID = m_CurrentBanker.wChairID;
				StatusFree.lBankerTreasure = m_CurrentBanker.lUserScore;
			}
			else 
				StatusFree.wCurrentBankerChairID = INVALID_CHAIR;

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
			//��������
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay,sizeof(StatusPlay));

			StatusPlay.lCellScore=m_pGameServiceOption->lCellScore;

			StatusPlay.lBigTigerScore	= m_lAllBigTigerScore;
			StatusPlay.lSmlTigerScore	= m_lAllSmlTigerScore;
			StatusPlay.lBigBogScore		= m_lAllBigBogScore;
			StatusPlay.lSmlBogScore		= m_lAllSmlBogScore;
			StatusPlay.lBigHorseScore   = m_lAllBigHorseScore;
			StatusPlay.lSmlHorseScore	= m_lAllSmlHorseScore;
			StatusPlay.lBigSnakeScore   = m_lAllBigSnakeScore;
			StatusPlay.lSmlSnakeScore	= m_lAllSmlSnakeScore;

			//ׯ����Ϣ
			StatusPlay.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if ( pIServerUserItem->GetUserStatus()!=US_LOOKON )
			{
				StatusPlay.lMeMaxScore	    = pIServerUserItem->GetUserScore()->lScore;
				//-------------------------------------------------------------------
				StatusPlay.lMeBigTigerScore	= m_lUserBigTigerScore[wChiarID];
				StatusPlay.lMeSmlTigerScore	= m_lUserSmlTigerScore[wChiarID];
				StatusPlay.lMeBigBogScore	= m_lUserBigBogScore[wChiarID];
				StatusPlay.lMeSmlBogScore	= m_lUserSmlBogScore[wChiarID];
				StatusPlay.lMeSmlBogScore	= m_lUserBigHorseScore[wChiarID];
				StatusPlay.lMeBigHorseScore = m_lUserSmlHorseScore[wChiarID];
				StatusPlay.lMeSmlHorseScore	= m_lUserBigSnakeScore[wChiarID];
				StatusPlay.lMeBigHorseScore = m_lUserSmlSnakeScore[wChiarID];
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
			StatusPlay.cbAnimalBox=m_cbAnimalBox;

			//ȫ����Ϣ
			int Time = (m_cbAnimalBox*ANIMAL_ROLL_SPEED)/1000+TIME_GAME_END;
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusPlay.cbTimeLeave=(BYTE)(Time-__min(dwPassTime,Time));
			//���ͳ���
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
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
			m_pITableFrameControl->StartGame();
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_GAME_END, (m_cbAnimalBox*ANIMAL_ROLL_SPEED)+TIME_GAME_END*1000,1,0L);
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
				if ( pServerUserItem ) 
					OnUserApplyBanker( pServerUserItem->GetUserData(), false );
			}

			//����ʱ��
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_GAME_FREE, TIME_FREE*1000L, 1, 0L);
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
			if (wDataSize!=sizeof(CMD_C_PlaceJetton)) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();

			if (pUserData->cbUserStatus!=US_SIT) return true;

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
		m_pITableFrame->SetGameTimer(IDI_GAME_FREE, TIME_FREE*1000L,1,NULL);	
	}

	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//��¼�ɼ�
	if ( bLookonUser==false )
	{
		if ( m_pITableFrame->GetGameStatus() != GS_PLAYING )
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
					m_CurrentBanker.dwUserID=0;
					m_cbBankerTimer=0;
					m_lBankerWinScore=0;

					//������Ϣ
					SendChangeBankerMsg();
				}
			}
		}

		WORD wNowCount=m_pITableFrame->GetNowPlayerCount();
		CString str;
		str.Format("���仹ʣ������%d",wNowCount);
		OutputDebugString(str);
		if ( wNowCount==0 )
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
	ASSERT( cbJettonArea>=ID_BIG_TIGER && cbJettonArea<=ID_SML_SNAKE);
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) 
		return false;
	if ( lJettonScore<=0L ) return false;

	//Ч��״̬
	ASSERT(m_pITableFrame->GetGameStatus()==GS_FREE+1);
	if (m_pITableFrame->GetGameStatus()!=GS_FREE+1) return true;

	//ˢ����ׯ�ҵķ���
	IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
	if(pBankerItem)
	{
		if(m_CurrentBanker.dwUserID != 0L)
			m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
	}


	//ׯ���ж�
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) return true;
	if ( m_CurrentBanker.dwUserID == 0 ) return true;

	//��������
	IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);

	__int64 lJettonCount=
		m_lUserBigTigerScore[wChairID]+
		m_lUserSmlTigerScore[wChairID]+
		m_lUserBigBogScore[wChairID]+
		m_lUserSmlBogScore[wChairID]+
		m_lUserBigHorseScore[wChairID]+
		m_lUserSmlHorseScore[wChairID]+
		m_lUserBigSnakeScore[wChairID]+
		m_lUserSmlSnakeScore[wChairID];

	__int64 lUserScore = pIServerUserItem->GetUserScore()->lScore;

	if ( lUserScore < lJettonCount + lJettonScore ) return true;

	//�Ϸ���֤
	if ( ID_BIG_TIGER == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllBigTigerScore += lJettonScore;
		m_lUserBigTigerScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_TIGER == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllSmlTigerScore += lJettonScore;
		m_lUserSmlTigerScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_DOG == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllBigBogScore += lJettonScore;
		m_lUserBigBogScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_DOG == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllSmlBogScore += lJettonScore;
		m_lUserSmlBogScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_HORSE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllBigHorseScore += lJettonScore;
		m_lUserBigHorseScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_HORSE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllSmlHorseScore += lJettonScore;
		m_lUserSmlHorseScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_SNAKE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllBigSnakeScore += lJettonScore;
		m_lUserBigSnakeScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_SNAKE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//������ע
		m_lAllSmlSnakeScore += lJettonScore;
		m_lUserSmlSnakeScore[wChairID] += lJettonScore;
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
		ChangeBanker.lBankerWinScore = m_lBankerWinScore;
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

//�õ���������ע�Ļ���
__int64 CTableFrameSink::Get_ALL_MultiDesktopScore()
{
	//�������ע��
	__int64  lAllDesktopJetton=0L;

	lAllDesktopJetton+=m_lAllBigTigerScore*s_Multiple[0];		//��������ע
	lAllDesktopJetton+=m_lAllSmlTigerScore*s_Multiple[1];		//�����С����ע
	lAllDesktopJetton+=m_lAllBigBogScore*s_Multiple[2];			//��������ע
	lAllDesktopJetton+=m_lAllSmlBogScore*s_Multiple[3];			//��������ע
	lAllDesktopJetton+=m_lAllBigHorseScore*s_Multiple[4];		//����������ע
	lAllDesktopJetton+=m_lAllSmlHorseScore*s_Multiple[5];		//�����С����ע
	lAllDesktopJetton+=m_lAllBigSnakeScore*s_Multiple[6];		//����������ע
	lAllDesktopJetton+=m_lAllSmlSnakeScore*s_Multiple[7];		//�����С����ע

	return lAllDesktopJetton;
}

//�õ���������ע�Ļ���
__int64 CTableFrameSink::Get_User_DesktopScore(WORD wChairID)
{
	//ĳ������ע��
	__int64 lUserDesktopJetton = 0;
	lUserDesktopJetton += m_lUserBigTigerScore[wChairID];    //ĳ�������ע
	lUserDesktopJetton += m_lUserSmlTigerScore[wChairID];	 //ĳ����С����ע
	lUserDesktopJetton += m_lUserBigBogScore[wChairID];		 //ĳ�������ע
	lUserDesktopJetton += m_lUserSmlBogScore[wChairID];		 //ĳ�������ע
	lUserDesktopJetton += m_lUserBigHorseScore[wChairID];	 //ĳ���������ע
	lUserDesktopJetton += m_lUserSmlHorseScore[wChairID];	 //ĳ����С����ע
	lUserDesktopJetton += m_lUserBigSnakeScore[wChairID];	 //ĳ���������ע
	lUserDesktopJetton += m_lUserSmlSnakeScore[wChairID];	 //ĳ����С����ע

	return lUserDesktopJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxPutScore(WORD wChairID, BYTE cbJettonArea)
{
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) 
		return 0L;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);
	if (pServerUserItem==NULL)
		return 0L;

	//�������ע��
	__int64 lAllDesktopJetton=Get_ALL_MultiDesktopScore();
	__int64 lAllLeftSpace = m_CurrentBanker.lUserScore-lAllDesktopJetton;
	lAllLeftSpace=max(lAllLeftSpace, 0);
	lAllLeftSpace=lAllLeftSpace/s_Multiple[cbJettonArea-ID_BIG_TIGER];

	//ĳ��������ע��
	__int64 lUserDesktopJetton=Get_User_DesktopScore(wChairID);
	__int64 lUserLeftSpace = pServerUserItem->GetUserScore()->lScore-lUserDesktopJetton;
	lUserLeftSpace = max(lUserLeftSpace, 0);
	
	__int64 lMinSpace = min(lUserLeftSpace, lAllLeftSpace);

	return lMinSpace;
}

//����÷�
void CTableFrameSink::CalculateScore()
{
	//������Ϣ
	CMD_S_GameScore GameScore;
	ZeroMemory(&GameScore,sizeof(GameScore));

	//�ƶ����
	GameScore.cbWinner=DeduceWinner();

	//��Ϸ��¼
	tagServerGameRecord &ServerGameRecord = m_GameRecordArrary[m_nRecordLast];

	ServerGameRecord.lBigTigerScore	= m_lAllBigTigerScore;		
	ServerGameRecord.lSmlTigerScore	= m_lAllSmlTigerScore;		
	ServerGameRecord.lBigBogScore	= m_lAllBigBogScore;		
	ServerGameRecord.lSmlBogScore	= m_lAllSmlBogScore;		
	ServerGameRecord.lBigHorseScore	= m_lAllBigHorseScore;		
	ServerGameRecord.lSmlHorseScore	= m_lAllSmlHorseScore;		
	ServerGameRecord.lBigSnakeScore	= m_lAllBigSnakeScore;		
	ServerGameRecord.lSmlSnakeScore	= m_lAllSmlSnakeScore;		
	ServerGameRecord.cbWinner		= DeduceWinner();

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
	__int64 *pUserScore[] = 
	{
		m_lUserBigTigerScore,
		m_lUserSmlTigerScore,
		m_lUserBigBogScore,
		m_lUserSmlBogScore, 
		m_lUserBigHorseScore, 
		m_lUserSmlHorseScore,
		m_lUserBigSnakeScore,
		m_lUserSmlSnakeScore
	};

	//�������
	for (WORD i=0; i<GAME_PLAYER; i++)
	{
		//ׯ���ж�
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i ) continue;

		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		for ( BYTE cbJettonArea = ID_BIG_TIGER; cbJettonArea <= ID_SML_SNAKE; cbJettonArea++ )
		{
			LONG ArrayIndex=cbJettonArea-ID_BIG_TIGER;
			if ( cbJettonArea == GameScore.cbWinner ) 
			{
				m_lUserWinScore[i]    += pUserScore[ArrayIndex][i] * s_Multiple[ArrayIndex];
				m_lUserReturnScore[i] += pUserScore[ArrayIndex][i];
				lBankerWinScore       -= pUserScore[ArrayIndex][i] * s_Multiple[ArrayIndex];
			}
			else
			{
				lUserLostScore[i] -= pUserScore[ArrayIndex][i];
				lBankerWinScore   += pUserScore[ArrayIndex][i];
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
		//�ۼƻ���
		m_lBankerWinScore += lBankerWinScore;
	}

	//��ע����
	GameScore.lDrawBigTigerScore	=m_lAllBigTigerScore;					//����ϻ���ע
	GameScore.lDrawSmlTigerScore	=m_lAllSmlTigerScore;					//��С�ϻ���ע
	GameScore.lDrawBigBogScore		=m_lAllBigBogScore;					//�����ע
	GameScore.lDrawSmlBogScore		=m_lAllSmlBogScore;					//�����ע
	GameScore.lDrawBigHorseScore	=m_lAllBigHorseScore;					//�������ע
	GameScore.lDrawSmlHorseScore	=m_lAllSmlHorseScore;					//��С����ע
	GameScore.lDrawBigSnakeScore	=m_lAllBigSnakeScore;					//�������ע
	GameScore.lDrawSmlSnakeScore	=m_lAllSmlSnakeScore;					//��С����ע
	
	GameScore.lBankerWinScore		=m_lBankerWinScore;

	//���ͻ���
	for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
		if ( pIServerUserItem == NULL ) 
			continue;

		GameScore.lMeBigTigerScore	= m_lUserBigTigerScore[wUserIndex];
		GameScore.lMeSmlTigerScore	= m_lUserSmlTigerScore[wUserIndex];
		GameScore.lMeBigBogScore	= m_lUserBigBogScore[wUserIndex];
		GameScore.lMeSmlBogScore	= m_lUserSmlBogScore[wUserIndex];
		GameScore.lMeBigHorseScore	= m_lUserBigHorseScore[wUserIndex];
		GameScore.lMeSmlHorseScore	= m_lUserSmlHorseScore[wUserIndex];
		GameScore.lMeBigSnakeScore	= m_lUserBigSnakeScore[wUserIndex];
		GameScore.lMeSmlSnakeScore	= m_lUserSmlSnakeScore[wUserIndex];

		//������Ϣ
		GameScore.lMeGameScore		= m_lUserWinScore[wUserIndex];
		GameScore.lMeReturnScore	= m_lUserReturnScore[wUserIndex];

		m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_SCORE, &GameScore, sizeof(GameScore));
		m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_SCORE, &GameScore, sizeof(GameScore));
	}
	return ;
}

//�ƶ�Ӯ��
BYTE CTableFrameSink::DeduceWinner()
{
	return s_arJettonArea[m_cbAnimalBox%MAX_ANIMAL_COUNT];
}

void CTableFrameSink::MakeAnimate()
{
	SuperRand();

	const BYTE s_RandZone[MAX_ANIMAL_COUNT]={2, 24, 4, 24, 6, 24, 12, 24 };

	const BYTE s_arJettonArea[MAX_ANIMAL_COUNT]=
	{
		ID_BIG_TIGER, ID_SML_TIGER, ID_BIG_DOG,   ID_SML_DOG, 
		ID_BIG_HORSE, ID_SML_HORSE, ID_BIG_SNAKE, ID_SML_SNAKE
	};

	LONG ok=rand()%120;

	LONG cbAnimalBox=0;
	LONG Zone=0;
	for ( int i=0; i<MAX_ANIMAL_COUNT; i++ )
	{
		Zone+=s_RandZone[i];
		if (ok<Zone)
		{
			cbAnimalBox=(s_arJettonArea[i]-ID_BIG_TIGER);
			break;
		}
	}
	CString str;
	str.Format("cbAnimalBox��%d",cbAnimalBox);
	OutputDebugString(str);

	m_cbAnimalBox=BYTE(rand()%4*8+cbAnimalBox+96);
}

void CTableFrameSink::ChuLaoQian()
{
	TCHAR szINI[512];
	::GetModulePath(szINI, sizeof(szINI));
	SafeStrCat(szINI, "\\BumperCar.ini", sizeof(szINI));
	LONG lWinRate=GetPrivateProfileInt("Option", "WinRate", 3, szINI);
	__int64 lMaxPerLose = GetPrivateProfileInt("Option", "MaxPerLose", 50000000, szINI);
	__int64 lMaxLose = GetPrivateProfileInt("Option", "MaxLose", 100000000, szINI);
	__int64 lPlayerMaxMin = GetPrivateProfileInt("Option", "PlayMaxWin", 100000000, szINI);
	LIMIT_VALUE(lWinRate, 1, 10);

	//��ȡ���
	if (m_CurrentBanker.dwUserID != 0)
	{
		//������30%�ĸ���ӮǮ
		if ( m_CurrentBanker.dwUserType == 10 )
		{
			bool bWin = false;
			if ( rand() % lWinRate == 0 || m_lBankerWinScore <= (-lMaxLose) )
			{
				bool bWin = false;
				while (PreCalcScore() < 0)
				{
					MakeAnimate();
				}
			}
			else if (bWin == false)
			{
				while(PreCalcScore() < (-lMaxPerLose))
				{
					MakeAnimate();
				}
			}
		}
		else
		{
			//��������ׯ
			if (m_lBankerWinScore >= lPlayerMaxMin)
			{
				while(PreCalcScore() > 0)
				{
					MakeAnimate();
				}
			}
			else if(m_lBankerWinScore > 0)
			{
				__int64 nLoseRate = m_lBankerWinScore * 100 / lPlayerMaxMin;
				int nRand = rand()%100;
				if (nRand < nLoseRate)
				{
					while(PreCalcScore() > 0)
					{
						MakeAnimate();
					}
				}
			}
		}
	}

}

__int64 CTableFrameSink::PreCalcScore()
{
	//�����ע
	__int64 allUserScore[MAX_ANIMAL_COUNT] =  {
		m_lAllBigTigerScore*s_Multiple[0],	//��������ע
		m_lAllSmlTigerScore*s_Multiple[1],	//�����С����ע
		m_lAllBigBogScore  *s_Multiple[2],	//��������ע
		m_lAllSmlBogScore  *s_Multiple[3],	//��������ע
		m_lAllBigHorseScore*s_Multiple[4],	//����������ע
		m_lAllSmlHorseScore*s_Multiple[5],	//�����С����ע
		m_lAllBigSnakeScore*s_Multiple[6],	//����������ע
		m_lAllSmlSnakeScore*s_Multiple[7]	//�����С����ע
	};
	BYTE cbAnimal=m_cbAnimalBox%MAX_ANIMAL_COUNT;
	//�����ע
	__int64 sxWinOrLose=0;
	for ( BYTE i=0; i<MAX_ANIMAL_COUNT; i++ )
	{
		if ( i==cbAnimal )
			sxWinOrLose-=allUserScore[i];
		else
			sxWinOrLose+=allUserScore[i];
	}
	return sxWinOrLose;
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

void CTableFrameSink::JettonChangeByUserLeft( WORD wChairID, IServerUserItem * pIServerUserItem )
{
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) 
		return;

	__int64 nBigTiger = m_lUserBigTigerScore[wChairID];
	__int64 nSmlTiger = m_lUserSmlTigerScore[wChairID];
	__int64 nBigBog  = m_lUserBigBogScore[wChairID];
	__int64 nSmlBog = m_lUserSmlBogScore[wChairID];
	__int64 nBigHorse = m_lUserBigHorseScore[wChairID];
	__int64 nSmlHorse  = m_lUserSmlHorseScore[wChairID];
	__int64 nBigSnake = m_lUserBigSnakeScore[wChairID];
	__int64 nSmlSnake = m_lUserSmlSnakeScore[wChairID];

	m_lAllBigTigerScore -= nBigTiger;
	m_lAllSmlTigerScore -= nSmlTiger;
	m_lAllBigBogScore	-= nBigBog;
	m_lAllSmlBogScore	-= nSmlBog;
	m_lAllBigHorseScore -= nBigHorse;
	m_lAllSmlHorseScore -= nSmlHorse;
	m_lAllBigSnakeScore -= nBigSnake;
	m_lAllSmlSnakeScore -= nSmlSnake;

	m_lUserBigTigerScore[wChairID] = 0;
	m_lUserSmlTigerScore[wChairID] = 0;
	m_lUserBigBogScore[wChairID] = 0;
	m_lUserSmlBogScore[wChairID] = 0;
	m_lUserBigHorseScore[wChairID] = 0;
	m_lUserSmlHorseScore[wChairID] = 0;
	m_lUserBigSnakeScore[wChairID] = 0;
	m_lUserSmlSnakeScore[wChairID] = 0;

// 	//��������
// 	CMD_S_JettonChange JettonChange;
// 	ZeroMemory(&JettonChange,sizeof(JettonChange));
// 	JettonChange.lTianMenScore=nTianmen;
// 	JettonChange.lDaoMenScore=nDaomen;
// 	JettonChange.lShunMenScore=nShunmen;
// 	JettonChange.lZhuangSocre=m_CurrentBanker.lUserScore; 
// 	JettonChange.lKexiaSocre=m_CurrentBanker.lUserScore-(m_lTianMenScore+m_lDaoMenScore+m_lShunMenScore);
// 	//������Ϣ
// 	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));
// 	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));
}

