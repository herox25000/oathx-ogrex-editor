#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��������
#define SEND_COUNT					8									//���ʹ���

//��������
//#define INDEX_PLAYER1				0									//�м�����
//#define INDEX_BANKER				1									//ׯ������

#define INDEX_BANKER				0									//ׯ������
#define INDEX_PLAYER1				1									//�м�1����
#define INDEX_PLAYER2				2									//�м�1����
#define INDEX_PLAYER3				3									//�м�1����

//��עʱ��
#define IDI_PLACE_JETTON			1									//��עʱ��

#ifdef _DEBUG
#define TIME_PLACE_JETTON			30									//��עʱ��
#else
#define TIME_PLACE_JETTON			25									//��עʱ��
#endif

//����ʱ��
#define IDI_GAME_END				2									//����ʱ��
#ifdef _DEBUG
#define TIME_GAME_END				20									//����ʱ��
#else
#define TIME_GAME_END				20									//����ʱ��
#endif

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;				//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_TimeControl;	//��ʼģʽ

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��ע��Ϣ
	m_lTianMenScore=0L;
	m_lDaoMenScore=0L;
	m_lShunMenScore=0L;
	m_lQiaoScore=0L;
	m_lYouJiaoScore=0L;
	m_lZuoJiaoScore=0L;

	//״̬����
	m_dwJettonTime=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserTianMenScore,sizeof(m_lUserTianMenScore));
	ZeroMemory(m_lUserDaoMenScore,sizeof(m_lUserDaoMenScore));
	ZeroMemory(m_lUserShunMenScore,sizeof(m_lUserShunMenScore));
	ZeroMemory(m_lUserQiaoScore,sizeof(m_lUserQiaoScore));
	ZeroMemory(m_lUserYouJiaoScore,sizeof(m_lUserYouJiaoScore));
	ZeroMemory(m_lUserZuoJiaoScore,sizeof(m_lUserZuoJiaoScore));

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));

	//ׯ�ұ���
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
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

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//��ע��Ϣ
	m_lTianMenScore=0L;
	m_lDaoMenScore=0L;
	m_lShunMenScore=0L;
	m_lQiaoScore=0L;
	m_lYouJiaoScore=0L;
	m_lZuoJiaoScore=0L;

	//��ע��Ϣ
	ZeroMemory(m_lUserTianMenScore,sizeof(m_lUserTianMenScore));
	ZeroMemory(m_lUserDaoMenScore,sizeof(m_lUserDaoMenScore));
	ZeroMemory(m_lUserShunMenScore,sizeof(m_lUserShunMenScore));
	ZeroMemory(m_lUserQiaoScore,sizeof(m_lUserQiaoScore));
	ZeroMemory(m_lUserYouJiaoScore,sizeof(m_lUserYouJiaoScore));
	ZeroMemory(m_lUserZuoJiaoScore,sizeof(m_lUserZuoJiaoScore));

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
	//�����˿�
	DispatchTableCard();
	ChuLaoQian();
	//��������
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));
	//��������
	GameStart.cbTimeLeave=TIME_GAME_END;//ʣ��ʱ��  13��		
	CopyMemory(GameStart.cbCardCount,m_cbCardCount,sizeof(m_cbCardCount));
	CopyMemory(GameStart.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
	GameStart.lApplyBankerCondition = m_lApplyBankerCondition;//������ׯ������
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

				//д�����
				if (m_lUserWinScore[wUserChairID]!=0L)
					m_pITableFrame->WriteUserScore(wUserChairID,m_lUserWinScore[wUserChairID], 0, ScoreKind);

				//ׯ���ж�
				if ( m_CurrentBanker.dwUserID == pIServerUserItem->GetUserID() ) m_CurrentBanker.lUserScore = pIServerUserItem->GetUserScore()->lScore;
			}

			//���ͻ���
			GameEnd.cbTimeLeave=TIME_PLACE_JETTON;	
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

			//TCHAR szPokerInfo[MAX_DB_JETTON_LEN]={0};
			//TCHAR szPointInfo[MAX_DB_JETTON_LEN]={0};

			//CString str;
			//str.Format("����:",m_cbCardCount);
			//OutputDebugString(str);
			//str.Format()
			//OutputRoundInfomation(szPokerInfo, "����:", m_cbCardCount, sizeof(m_cbCardCount));
			//OutputRoundInfomation(szPokerInfo, "�˿�:", m_cbTableCardArray, sizeof(m_cbTableCardArray));
			//_snprintf(szPointInfo, CountArray(szPointInfo), TEXT("Winner:%d KingWinner:%d"), GameEnd.cbWinner, GameEnd.cbKingWinner);
			//m_pITableFrame->WriteRoundInfomation(szPokerInfo, szPointInfo, m_CurrentBanker.dwUserID, m_lBankerWinScore);

			//ׯ���ж�
			if ( m_CurrentBanker.dwUserID != 0 )
			{
				//��ȡ�û�
				IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
				if (pIServerUserItem) 
				{
					//�����ж�
					if ( pIServerUserItem->GetUserScore()->lScore < m_lApplyBankerCondition )
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
	case GER_USER_LEFT:	//�û�ǿ��
		{
			__int64	allZhu=0;
			if ( pIServerUserItem->GetUserID()==m_CurrentBanker.dwUserID ) //ׯ��ǿ��
			{
				allZhu=m_lTianMenScore+m_lDaoMenScore+m_lShunMenScore+m_lQiaoScore+m_lYouJiaoScore+m_lZuoJiaoScore;
			}
			else
			{
				allZhu=m_lUserTianMenScore[wChairID]+m_lUserDaoMenScore[wChairID]+m_lUserShunMenScore[wChairID]+
					m_lUserQiaoScore[wChairID]+m_lUserYouJiaoScore[wChairID]+m_lUserZuoJiaoScore[wChairID];
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
				CopyMemory(cbBuffer+wBufferSize,&m_GameRecordArrary[nIndex],sizeof(tagServerGameRecord));
				wBufferSize+=sizeof(tagServerGameRecord);

				nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
			}
			if (wBufferSize>0) m_pITableFrame->SendUserData(pIServerUserItem,SUB_S_SEND_RECORD,cbBuffer,wBufferSize);

			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			StatusFree.lTieScore=m_lTianMenScore;
			StatusFree.lBankerScore=m_lDaoMenScore;
			StatusFree.lPlayerScore=m_lShunMenScore;
			StatusFree.lTieSamePointScore = m_lQiaoScore;
			StatusFree.lBankerKingScore = m_lYouJiaoScore;
			StatusFree.lPlayerKingScore = m_lZuoJiaoScore;
			//ׯ����Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lMeTieScore=m_lUserTianMenScore[wChiarID];
				StatusFree.lMeBankerScore=m_lUserDaoMenScore[wChiarID];
				StatusFree.lMePlayerScore=m_lUserShunMenScore[wChiarID];
				StatusFree.lMeTieKingScore = m_lUserQiaoScore[wChiarID];
				StatusFree.lMeBankerKingScore = m_lUserYouJiaoScore[wChiarID];
				StatusFree.lMePlayerKingScore = m_lUserZuoJiaoScore[wChiarID];
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
			//��������
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay,sizeof(StatusPlay));

			StatusPlay.lCellScore=m_pGameServiceOption->lCellScore;
			//��ע��Ϣ
			StatusPlay.lTieScore=m_lTianMenScore;
			StatusPlay.lBankerScore=m_lDaoMenScore;
			StatusPlay.lPlayerScore=m_lShunMenScore;
			StatusPlay.lTieSamePointScore = m_lQiaoScore;
			StatusPlay.lBankerKingScore = m_lYouJiaoScore;
			StatusPlay.lPlayerKingScore = m_lZuoJiaoScore;

			//ׯ����Ϣ
			StatusPlay.lApplyBankerCondition = m_lApplyBankerCondition;

			//��ע��Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusPlay.lMeTieScore=m_lUserTianMenScore[wChiarID];
				StatusPlay.lMeBankerScore=m_lUserDaoMenScore[wChiarID];
				StatusPlay.lMePlayerScore=m_lUserShunMenScore[wChiarID];
				StatusPlay.lMeTieKingScore = m_lUserQiaoScore[wChiarID];
				StatusPlay.lMeBankerKingScore = m_lUserYouJiaoScore[wChiarID];
				StatusPlay.lMePlayerKingScore = m_lUserZuoJiaoScore[wChiarID];
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

			//����������
			SendApplyUser( pIServerUserItem );

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	switch (wTimerID)
	{
	case IDI_PLACE_JETTON:		//��עʱ��
		{
			//��ʼ��Ϸ
			m_pITableFrameControl->StartGame();

			//����ʱ��
			m_pITableFrame->SetGameTimer(IDI_GAME_END,TIME_GAME_END*1000,1,0L);

			return true;
		}
	case IDI_GAME_END:			//������Ϸ
		{
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
			m_pITableFrame->SetGameTimer(IDI_PLACE_JETTON,TIME_PLACE_JETTON*1000,1,0L);

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
			return OnUserPlaceJetton(pUserData->wChairID,pPlaceJetton->cbJettonArea,pPlaceJetton->lJettonScore);
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
		m_pITableFrame->SetGameTimer(IDI_PLACE_JETTON,TIME_PLACE_JETTON*1000L,1,NULL);
	}

	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//��¼�ɼ�
	if (bLookonUser==false)
	{
		//״̬�ж�
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
			m_pITableFrame->KillGameTimer( IDI_PLACE_JETTON );
		}
	}

	return true;
}

bool CTableFrameSink::IsBigBanker(WORD wChairID, BYTE cbJettonArea, __int64 lJettonScore)
{
	__int64 all=m_lTianMenScore+m_lDaoMenScore+m_lShunMenScore+m_lQiaoScore+m_lYouJiaoScore+m_lZuoJiaoScore+lJettonScore;
	IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
	if (pIServerUserItem)
	{
		if ( all>pIServerUserItem->GetUserScore()->lScore )
		{
			return true;
		}
	}
	return false;
}

//��ע�¼�
bool CTableFrameSink::OnUserPlaceJetton(WORD wChairID, BYTE cbJettonArea, __int64 lJettonScore, bool bRobot)
{
	//Ч�����
	ASSERT((cbJettonArea<=ID_QIAO)&&(lJettonScore>0L));
	if ((cbJettonArea>ID_QIAO)||(lJettonScore<=0L)) return false;

	//Ч��״̬
	ASSERT(m_pITableFrame->GetGameStatus()==GS_FREE);
	if (m_pITableFrame->GetGameStatus()!=GS_FREE) return true;

	//ׯ���ж�
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) return true;
	if ( m_CurrentBanker.dwUserID == 0 ) return true;
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
	__int64 lJettonCount=m_lUserTianMenScore[wChairID]+m_lUserDaoMenScore[wChairID]+m_lUserShunMenScore[wChairID]+
		m_lUserQiaoScore[wChairID] + m_lUserZuoJiaoScore[wChairID] + m_lUserYouJiaoScore[wChairID];
	__int64 lUserScore = pIServerUserItem->GetUserScore()->lScore;

	if ( lUserScore < lJettonCount + lJettonScore ) return true;

	if (IsBigBanker(wChairID, cbJettonArea, lJettonScore)==true)  return true;

	//�Ϸ���֤
	if ( ID_SHUN_MEN == cbJettonArea )
	{
		if ( GetMaxPlayerScore(wChairID) < lJettonScore ) return true;

		//������ע
		m_lShunMenScore += lJettonScore;
		m_lUserShunMenScore[wChairID] += lJettonScore;
	}
	else if ( ID_ZUO_JIAO == cbJettonArea )
	{
		if ( GetMaxPlayerKingScore(wChairID) <lJettonScore ) return true;

		//������ע
		m_lZuoJiaoScore += lJettonScore;
		m_lUserZuoJiaoScore[wChairID] += lJettonScore;
	}
	else if ( ID_TIAN_MEN == cbJettonArea )
	{
		if ( GetMaxTieScore(wChairID) <lJettonScore ) return true;

		//������ע
		m_lTianMenScore += lJettonScore;
		m_lUserTianMenScore[wChairID] += lJettonScore;
	}
	else if ( ID_QIAO == cbJettonArea )
	{
		if ( GetMaxTieKingScore(wChairID) <lJettonScore ) return true;

		//������ע
		m_lQiaoScore += lJettonScore;
		m_lUserQiaoScore[wChairID] += lJettonScore;
	}
	else if ( ID_DAO_MEN == cbJettonArea )
	{
		if ( GetMaxBankerScore(wChairID) <lJettonScore ) return true;

		//������ע
		m_lDaoMenScore += lJettonScore;
		m_lUserDaoMenScore[wChairID] += lJettonScore;
	}
	else if ( ID_YOU_JIAO == cbJettonArea )
	{
		if ( GetMaxBankerKingScore(wChairID) <lJettonScore ) return true;

		//������ע
		m_lYouJiaoScore += lJettonScore;
		m_lUserYouJiaoScore[wChairID] += lJettonScore;
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
	pIServerUserItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
	if (pIServerUserItem)
	{
		PlaceJetton.lKeXiaSocre=pIServerUserItem->GetUserScore()->lScore; 
	}
	PlaceJetton.lAllJettonScore=m_lTianMenScore+m_lDaoMenScore+m_lShunMenScore+m_lQiaoScore+m_lYouJiaoScore+m_lZuoJiaoScore;

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
	m_cbCardCount[INDEX_PLAYER1]=2;
	m_cbCardCount[INDEX_BANKER]=2;
	return true;
}

//ӯ���ж�
__int64 CTableFrameSink::AccountPayoffScore()
{
	//�������
	BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	//ӯ������
	__int64 lPayoffScore=0L;
	if (cbPlayerCount>cbBankerCount) lPayoffScore=m_lTianMenScore+m_lDaoMenScore-m_lShunMenScore;
	else if (cbPlayerCount<cbBankerCount) lPayoffScore=m_lTianMenScore+m_lShunMenScore-m_lDaoMenScore;
	else lPayoffScore=-m_lTianMenScore*8L;

	return lPayoffScore;
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

		return true;
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

				return true;
			}
		}

		return true;
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

	//��������
	m_cbBankerTimer++;

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
				IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_ApplyUserArrary[ 0 ].wChairID );
				if (  pServerUserItem  ) OnUserApplyBanker( pServerUserItem->GetUserData(), false );
			}
			else
				break;
		}
		m_cbBankerTimer = 0;
		m_lBankerWinScore=0;
		m_bCancelBanker = false;
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
__int64 CTableFrameSink::GetMaxPlayerScore(WORD wChairID)//˳��
{
	//��������

	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;
	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	ASSERT(lMeLessScore >= 0 );
	lMeLessScore = max(lMeLessScore, 0);

	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxPlayerKingScore(WORD wChairID)//���
{
	//��������
	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;
	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore = m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	//�����ע
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxBankerScore(WORD wChairID)//����
{
	//��������
	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore =m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxBankerKingScore(WORD wChairID)//�ҽ�
{
	//��������
	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;
	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxPlayerScore =  m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	__int64 lMaxJetton = min(lMaxPlayerScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxTieScore(WORD wChairID)//����
{
	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	__int64 lMaxTieScore = m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	__int64 lMaxJetton = min(lMaxTieScore, lMeLessScore);

	return lMaxJetton;
}

//�����ע
__int64 CTableFrameSink::GetMaxTieKingScore(WORD wChairID)//��
{
	__int64 lAllAreaScore = m_lDaoMenScore+ m_lTianMenScore+ m_lQiaoScore+ m_lYouJiaoScore+m_lZuoJiaoScore+m_lShunMenScore;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);

	//�����ע
	__int64 lMaxTieScore = m_CurrentBanker.lUserScore-lAllAreaScore;

	//����ע��
	__int64 lNowJetton = 0;
	lNowJetton += m_lUserShunMenScore[wChairID];
	lNowJetton += m_lUserZuoJiaoScore[wChairID];
	lNowJetton += m_lUserDaoMenScore[wChairID];
	lNowJetton += m_lUserTianMenScore[wChairID];
	lNowJetton += m_lUserQiaoScore[wChairID];
	lNowJetton += m_lUserYouJiaoScore[wChairID];

	//�ҵ���ע
	__int64 lMeLessScore = pServerUserItem->GetUserScore()->lScore - lNowJetton;
	__int64 lMaxJetton = min(lMaxTieScore, lMeLessScore);

	return lMaxJetton;
}

//����÷�
void CTableFrameSink::CalculateScore()
{
	//������Ϣ
	CMD_S_GameScore GameScore;
	ZeroMemory(&GameScore,sizeof(GameScore));

	//�����Ƶ�
	BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	//�ƶ����
	DeduceWinner(GameScore.cbWinner, GameScore.cbKingWinner);

	//��Ϸ��¼
	tagServerGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];
	GameRecord.cbBankerCount = cbBankerCount;
	GameRecord.cbPlayerCount = cbPlayerCount;
	GameRecord.lBankerScore = m_lDaoMenScore;
	GameRecord.lPlayerScore = m_lShunMenScore;
	GameRecord.lTieScore = m_lTianMenScore;
	GameRecord.wWinner = GameScore.cbWinner;

	//�ƶ��±�
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;
	if ( m_nRecordLast == m_nRecordFirst ) m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;

	//ׯ������
	__int64 lBankerWinScore = 0;

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));
	__int64 lUserLostScore[GAME_PLAYER];
	ZeroMemory(lUserLostScore, sizeof(lUserLostScore));

	//�������
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//ׯ���ж�
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i ) continue;

		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		//˳��
		if(ID_SHUN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserShunMenScore[i];
			m_lUserReturnScore[i] += m_lUserShunMenScore[i] ;
			lBankerWinScore -= m_lUserShunMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserShunMenScore[i] ;
			lBankerWinScore += m_lUserShunMenScore[i] ;
		}
		//����
		if(ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserTianMenScore[i];
			m_lUserReturnScore[i] += m_lUserTianMenScore[i] ;
			lBankerWinScore -= m_lUserTianMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserTianMenScore[i] ;
			lBankerWinScore += m_lUserTianMenScore[i] ;
		}
		//����
		if(ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserDaoMenScore[i];
			m_lUserReturnScore[i] += m_lUserDaoMenScore[i] ;
			lBankerWinScore -= m_lUserDaoMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserDaoMenScore[i] ;
			lBankerWinScore += m_lUserDaoMenScore[i] ;
		}

		//���
		if(ID_SHUN_MEN & GameScore.cbWinner && ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserZuoJiaoScore[i];
			m_lUserReturnScore[i] += m_lUserZuoJiaoScore[i] ;
			lBankerWinScore -= m_lUserZuoJiaoScore[i];
		}
		else if(ID_SHUN_MEN & GameScore.cbWinner || ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserZuoJiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserZuoJiaoScore[i] ;
			lBankerWinScore += m_lUserZuoJiaoScore[i] ;
		}
		//�ҽ�
		if(ID_TIAN_MEN & GameScore.cbWinner && ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserYouJiaoScore[i];
			m_lUserReturnScore[i] += m_lUserYouJiaoScore[i] ;
			lBankerWinScore -= m_lUserYouJiaoScore[i];
		}
		else if(ID_TIAN_MEN & GameScore.cbWinner || ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserYouJiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserYouJiaoScore[i] ;
			lBankerWinScore += m_lUserYouJiaoScore[i] ;
		}
		//��
		if(ID_SHUN_MEN & GameScore.cbWinner && ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserQiaoScore[i];
			m_lUserReturnScore[i] += m_lUserQiaoScore[i] ;
			lBankerWinScore -= m_lUserQiaoScore[i];
		}
		else if(ID_SHUN_MEN & GameScore.cbWinner || ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserQiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserQiaoScore[i] ;
			lBankerWinScore += m_lUserQiaoScore[i] ;
		}

		//�ܵķ���
		m_lUserWinScore[i] += lUserLostScore[i];
	}

	//ׯ�ҳɼ�
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		WORD wBankerChairID = m_CurrentBanker.wChairID;
		m_lUserWinScore[wBankerChairID] = lBankerWinScore;
		IServerUserItem *pBankerUserItem = m_pITableFrame->GetServerUserItem(wBankerChairID);

		//�ۼƻ���
		m_lBankerWinScore += lBankerWinScore;
	}

	//��ע����
	GameScore.lDrawTieScore=m_lTianMenScore;
	GameScore.lDrawBankerScore=m_lDaoMenScore;
	GameScore.lDrawPlayerScore=m_lShunMenScore;
	GameScore.lDrawTieSamPointScore = m_lQiaoScore;
	GameScore.lDrawBankerKingScore = m_lYouJiaoScore;
	GameScore.lDrawPlayerKingScore = m_lZuoJiaoScore;

	GameScore.lBankerScore = lBankerWinScore;

	//���ͻ���
	for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
		if ( pIServerUserItem == NULL ) continue;

		//�ҵ���ע
		GameScore.lMeTieScore=m_lUserTianMenScore[wUserIndex];
		GameScore.lMeBankerScore=m_lUserDaoMenScore[wUserIndex];
		GameScore.lMePlayerScore=m_lUserShunMenScore[wUserIndex];
		GameScore.lMeTieKingScore = m_lUserQiaoScore[wUserIndex];
		GameScore.lMeBankerKingScore = m_lUserYouJiaoScore[wUserIndex];
		GameScore.lMePlayerKingScore = m_lUserZuoJiaoScore[wUserIndex];

		//������Ϣ
		GameScore.lMeGameScore=m_lUserWinScore[wUserIndex];
		GameScore.lMeReturnScore = m_lUserReturnScore[wUserIndex];
		m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_SCORE,&GameScore,sizeof(GameScore));
		m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_SCORE,&GameScore,sizeof(GameScore));
	}
	return ;
}

__int64 CTableFrameSink::PreCalculateBankerWin()
{
	//������Ϣ
	CMD_S_GameScore GameScore;
	ZeroMemory(&GameScore,sizeof(GameScore));

	//�����Ƶ�
	BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	//�ƶ����
	DeduceWinner(GameScore.cbWinner, GameScore.cbKingWinner);

	//��Ϸ��¼
	tagServerGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];
	GameRecord.cbBankerCount = cbBankerCount;
	GameRecord.cbPlayerCount = cbPlayerCount;
	GameRecord.lBankerScore = m_lDaoMenScore;
	GameRecord.lPlayerScore = m_lShunMenScore;
	GameRecord.lTieScore = m_lTianMenScore;
	GameRecord.wWinner = GameScore.cbWinner;

	//�ƶ��±�
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;
	if ( m_nRecordLast == m_nRecordFirst ) m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;

	//ׯ������
	__int64 lBankerWinScore = 0;

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));
	__int64 lUserLostScore[GAME_PLAYER];
	ZeroMemory(lUserLostScore, sizeof(lUserLostScore));

	//�������
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//ׯ���ж�
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i ) continue;

		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		//˳��
		if(ID_SHUN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserShunMenScore[i];
			m_lUserReturnScore[i] += m_lUserShunMenScore[i] ;
			lBankerWinScore -= m_lUserShunMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserShunMenScore[i] ;
			lBankerWinScore += m_lUserShunMenScore[i] ;
		}
		//����
		if(ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserTianMenScore[i];
			m_lUserReturnScore[i] += m_lUserTianMenScore[i] ;
			lBankerWinScore -= m_lUserTianMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserTianMenScore[i] ;
			lBankerWinScore += m_lUserTianMenScore[i] ;
		}
		//����
		if(ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserDaoMenScore[i];
			m_lUserReturnScore[i] += m_lUserDaoMenScore[i] ;
			lBankerWinScore -= m_lUserDaoMenScore[i];
		}
		else
		{
			lUserLostScore[i] -=m_lUserDaoMenScore[i] ;
			lBankerWinScore += m_lUserDaoMenScore[i] ;
		}

		//���
		if(ID_SHUN_MEN & GameScore.cbWinner && ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserZuoJiaoScore[i];
			m_lUserReturnScore[i] += m_lUserZuoJiaoScore[i] ;
			lBankerWinScore -= m_lUserZuoJiaoScore[i];
		}
		else if(ID_SHUN_MEN & GameScore.cbWinner || ID_TIAN_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserZuoJiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserZuoJiaoScore[i] ;
			lBankerWinScore += m_lUserZuoJiaoScore[i] ;
		}
		//�ҽ�
		if(ID_TIAN_MEN & GameScore.cbWinner && ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserYouJiaoScore[i];
			m_lUserReturnScore[i] += m_lUserYouJiaoScore[i] ;
			lBankerWinScore -= m_lUserYouJiaoScore[i];
		}
		else if(ID_TIAN_MEN & GameScore.cbWinner || ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserYouJiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserYouJiaoScore[i] ;
			lBankerWinScore += m_lUserYouJiaoScore[i] ;
		}
		//��
		if(ID_SHUN_MEN & GameScore.cbWinner && ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserWinScore[i]+=m_lUserQiaoScore[i];
			m_lUserReturnScore[i] += m_lUserQiaoScore[i] ;
			lBankerWinScore -= m_lUserQiaoScore[i];
		}
		else if(ID_SHUN_MEN & GameScore.cbWinner || ID_DAO_MEN & GameScore.cbWinner)
		{
			m_lUserReturnScore[i] += m_lUserQiaoScore[i] ;
		}
		else
		{
			lUserLostScore[i] -=m_lUserQiaoScore[i] ;
			lBankerWinScore += m_lUserQiaoScore[i] ;
		}

		//�ܵķ���
		m_lUserWinScore[i] += lUserLostScore[i];
	}

	//ׯ�ҳɼ�
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		WORD wBankerChairID = m_CurrentBanker.wChairID;
		m_lUserWinScore[wBankerChairID] = lBankerWinScore;
		IServerUserItem *pBankerUserItem = m_pITableFrame->GetServerUserItem(wBankerChairID);
	}

	//��ҳɼ�
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	return lBankerWinScore;
}

//�ƶ�Ӯ��
void CTableFrameSink::DeduceWinner(BYTE &cbWinner, BYTE &cbKingWinner)
{
	cbWinner = 0;
	cbKingWinner = 0;

	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER1],2))
	{
		cbWinner = (cbWinner & ~ID_SHUN_MEN);
	}
	else
	{
		cbWinner|=ID_SHUN_MEN;
	}

	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER2],2))
	{
		cbWinner = (cbWinner & ~ID_TIAN_MEN);
	}
	else
	{
		cbWinner |=ID_TIAN_MEN;
	}
	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER3],2))
	{
		cbWinner = (cbWinner & ~ID_DAO_MEN);
	}
	else
	{
		cbWinner |=ID_DAO_MEN;
	}
	if(cbWinner & ID_SHUN_MEN && cbWinner & ID_TIAN_MEN && cbWinner & ID_DAO_MEN)
	{
		cbWinner |=ID_QUAN_SHU;
	}
}


void CTableFrameSink::ChuLaoQian()
{
	TCHAR szINI[512];
	::GetModulePath(szINI, sizeof(szINI));
	SafeStrCat(szINI, "\\PaiJiu.ini", sizeof(szINI));
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
				while(PreCalculateBankerWin() < 0)
				{
					DispatchTableCard();
				}
			}
			if (false == bWin)
			{
				while(PreCalculateBankerWin() < (-lMaxPerLose))
				{
					DispatchTableCard();
				}
			}
		}
		else
		{
			//��������ׯ
			if (m_lBankerWinScore >= lPlayerMaxMin)
			{
				while(PreCalculateBankerWin() > 0)
				{
					DispatchTableCard();
				}
			}
			else if(m_lBankerWinScore > 0)
			{
				int nLoseRate = m_lBankerWinScore * 100 / lPlayerMaxMin;
				int nRand = rand()%100;
				if (nRand < nLoseRate)
				{
					while(PreCalculateBankerWin() > 0)
					{
						DispatchTableCard();
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

