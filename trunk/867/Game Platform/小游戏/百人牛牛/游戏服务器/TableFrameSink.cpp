#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��������
#define SEND_COUNT					100									//���ʹ���

//��������
#define INDEX_PLAYER				0									//�м�����
#define INDEX_BANKER				1									//ׯ������

//��עʱ��
#define IDI_FREE					1									//����ʱ��
#ifdef _DEBUG
#define TIME_FREE					10									//����ʱ��
#else
#define TIME_FREE					10									//����ʱ��
#endif

//��עʱ��
#define IDI_PLACE_JETTON			2									//��עʱ��

#ifdef _DEBUG
#define TIME_PLACE_JETTON			20									//��עʱ��
#else
#define TIME_PLACE_JETTON			20									//��עʱ��
#endif

//����ʱ��
#define IDI_GAME_END				3									//����ʱ��

#ifdef _DEBUG
#define TIME_GAME_END				25								//����ʱ��
#else
#define TIME_GAME_END				25									//����ʱ��
#endif

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;				//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_TimeControl;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//����ע��
	ZeroMemory(m_lAllJettonScore,sizeof(m_lAllJettonScore));
	
	//������ע
	ZeroMemory(m_lUserJettonScore,sizeof(m_lUserJettonScore));

	//���Ʊ���
	m_cbWinSideControl=0;
	m_nSendCardCount=0;

	//��ҳɼ�	
	ZeroMemory(m_lUserWinScore,sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore,sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue,sizeof(m_lUserRevenue));

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));

	//״̬����
	m_dwJettonTime=0L;

	//ׯ����Ϣ
	m_ApplyUserArray.RemoveAll();
	m_wCurrentBanker=INVALID_CHAIR;
	m_wBankerTime=0;
	m_lBankerWinScore=0L;		
	m_lBankerCurGameScore=0L;
	m_bEnableSysBanker=true;
	m_cbLeftCardCount=0;
	m_bContiueCard=false;

	//��¼����
	ZeroMemory(m_GameRecordArrary,sizeof(m_GameRecordArrary));
	m_nRecordFirst=0;
	m_nRecordLast=0;
	m_dwRecordCount=0;
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
#ifdef __SPECIAL___
	QUERYINTERFACE(ITableUserActionEX,Guid,dwQueryVer);	
#endif
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


	//�����ļ���
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);
	_snprintf(m_szConfigFileName,sizeof(m_szConfigFileName),
		TEXT("%s\\Config\\����ţţ\\%d.ini"),szPath,m_pGameServiceOption->wServerID);

	//���Ʊ���
	LONG lMaxScore=2147483647/10;
	m_lApplyBankerCondition=GetPrivateProfileInt(TEXT("BankerCondition"), TEXT("Score"), 10000000, m_szConfigFileName);
	m_lAreaLimitScore=GetPrivateProfileInt(TEXT("ScoreLimit"), TEXT("AreaLimitScore"), lMaxScore, m_szConfigFileName);
	m_lUserLimitScore=GetPrivateProfileInt(TEXT("ScoreLimit"), TEXT("UserLimitScore"), lMaxScore, m_szConfigFileName);
	BYTE cbEnableSysBanker=GetPrivateProfileInt(TEXT("BankerCondition"), TEXT("EnableSysBanker"), 1, m_szConfigFileName);
	m_bEnableSysBanker=cbEnableSysBanker?true:false;

	if(m_lUserLimitScore*10<0)
	{
		m_lUserLimitScore = 2147483647/10;	
	}

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//����ע��
	ZeroMemory(m_lAllJettonScore,sizeof(m_lAllJettonScore));
	
	//������ע
	ZeroMemory(m_lUserJettonScore,sizeof(m_lUserJettonScore));

	//��ҳɼ�	
	ZeroMemory(m_lUserWinScore,sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore,sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue,sizeof(m_lUserRevenue));

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
	//��������
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));

	//��ȡׯ��
	IServerUserItem *pIBankerServerUserItem=NULL;
	if (INVALID_CHAIR!=m_wCurrentBanker) pIBankerServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);

	//���ñ���
	GameStart.cbTimeLeave=TIME_PLACE_JETTON;
	GameStart.wBankerUser=m_wCurrentBanker;
	if (pIBankerServerUserItem!=NULL)
		GameStart.lBankerScore=pIBankerServerUserItem->GetUserScore()->lScore;
	GameStart.bContiueCard=m_bContiueCard;
	
    //�Թ����
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));	

	//��Ϸ���
	for (WORD wChairID=0; wChairID<GAME_PLAYER; ++wChairID)
	{
		IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
		if (pIServerUserItem==NULL) continue;
		int iTimer = 10;

		//���û���
		GameStart.lUserMaxScore=min(pIServerUserItem->GetUserScore()->lScore,m_lUserLimitScore*iTimer);

		m_pITableFrame->SendTableData(wChairID,SUB_S_GAME_START,&GameStart,sizeof(GameStart));	
	}

	return true;
}

//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//�������	
		{
			//�ɷ��˿�
			DispatchTableCard();
			RobotAi();
			//�������
			__int64 lBankerWinScore=CalculateScore();
			//��������
			m_wBankerTime++;
			//������Ϣ
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));

			//ׯ����Ϣ
			GameEnd.nBankerTime = m_wBankerTime;
			GameEnd.lBankerTotallScore=m_lBankerWinScore;
			GameEnd.lBankerScore=lBankerWinScore;
			GameEnd.bcFirstCard = m_bcFirstPostCard;
			
			//�˿���Ϣ
			CopyMemory(GameEnd.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
			GameEnd.cbLeftCardCount=m_cbLeftCardCount;

			//���ͻ���
			GameEnd.cbTimeLeave=TIME_GAME_END;	
			for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
				if ( pIServerUserItem == NULL ) continue;

				//���óɼ�
				GameEnd.lUserScore=m_lUserWinScore[wUserIndex];
				//��������
				GameEnd.lUserReturnScore=m_lUserReturnScore[wUserIndex];
				//������Ϣ					
				m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			}

			return true;
		}
	case GER_USER_LEFT:		//�û��뿪
		{
			//�м����ܴ���
			if (m_wCurrentBanker!=wChairID)
			{
				//��������
				__int64 lScore=0;
				enScoreKind ScoreKind=enScoreKind_Flee;
				if(m_pITableFrame->GetGameStatus() == GS_PLACE_JETTON)
				{
					//ȡ����ע���� ��������ע����
					for (int nAreaIndex=1; nAreaIndex<=AREA_COUNT; ++nAreaIndex)
					{
						lScore += m_lUserJettonScore[nAreaIndex][wChairID];
						m_lAllJettonScore[nAreaIndex]-=lScore;
						m_lUserJettonScore[nAreaIndex][wChairID]=0;
					}
					lScore*=-10;
				}
				else if(m_pITableFrame->GetGameStatus() == GS_GAME_END)
				{
					lScore = m_lUserWinScore[wChairID];
				}

				//��ֹ�����û�Я�����
				if(lScore > pIServerUserItem->GetUserScore()->lScore)
					lScore = pIServerUserItem->GetUserScore()->lScore;

				if (lScore != 0 )
					m_pITableFrame->WriteUserScore(pIServerUserItem, lScore,0, ScoreKind);
				
				//�������Ľ��
				m_lUserWinScore[wChairID]=0;
			}
			else //ׯ������
			{
				//��������
				__int64 lScore=0;
				enScoreKind ScoreKind=enScoreKind_Flee;
				//�������۱���
				if (m_pITableFrame->GetGameStatus()==GS_PLACE_JETTON)
				{
					//��ʾ��Ϣ
					TCHAR szTipMsg[128];
					_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("����ׯ��[ %s ]ǿ�ˣ���Ϸ��ǰ������"),pIServerUserItem->GetAccounts());
					SendGameMessage(INVALID_CHAIR,szTipMsg);	
					//����״̬
					m_dwJettonTime=(DWORD)time(NULL);
					m_pITableFrame->SetGameStatus(GS_GAME_END);
					m_pITableFrame->KillGameTimer(IDI_PLACE_JETTON);
					m_pITableFrame->SetGameTimer(IDI_GAME_END,TIME_GAME_END*1000,1,0L);
					//�ɷ��˿�
					DispatchTableCard();
					//�������
					__int64 lBankerWinScore=CalculateScore();
					//������Ϣ
					CMD_S_GameEnd GameEnd;
					ZeroMemory(&GameEnd,sizeof(GameEnd));
					//ׯ����Ϣ
					GameEnd.nBankerTime = m_wBankerTime;
					GameEnd.lBankerTotallScore=m_lBankerWinScore;
					GameEnd.lBankerScore=lBankerWinScore;
					//�˿���Ϣ
					CopyMemory(GameEnd.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
					GameEnd.cbLeftCardCount=m_cbLeftCardCount;
					//���ͻ���
					GameEnd.cbTimeLeave=TIME_GAME_END;	
					for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
					{
						IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
						if ( pIServerUserItem == NULL ) 
							continue;

						//���óɼ�
						GameEnd.lUserScore=m_lUserWinScore[wUserIndex];
						//��������
						GameEnd.lUserReturnScore=m_lUserReturnScore[wUserIndex];
						//������Ϣ					
						m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
						m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
					}
				}
				lScore=m_lUserWinScore[m_wCurrentBanker];
				if (lScore != 0)
					m_pITableFrame->WriteUserScore(pIServerUserItem, lScore,0, ScoreKind);
				m_lUserWinScore[m_wCurrentBanker]=0;
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
			SendGameRecord(pIServerUserItem);

			//��������
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));			

			//������Ϣ
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;
			StatusFree.lAreaLimitScore = m_lAreaLimitScore;

			//ׯ����Ϣ
			StatusFree.bEnableSysBanker=m_bEnableSysBanker;
			StatusFree.wBankerUser=m_wCurrentBanker;	
			StatusFree.cbBankerTime=m_wBankerTime;
			StatusFree.lBankerWinScore=m_lBankerWinScore;
			if (m_wCurrentBanker!=INVALID_CHAIR)
			{
				IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);
				StatusFree.lBankerScore=pIServerUserItem->GetUserScore()->lScore;
			}

			//�����Ϣ
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				StatusFree.lUserMaxScore=min(pIServerUserItem->GetUserScore()->lScore,m_lUserLimitScore*10); 
			}

			//ȫ����Ϣ
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusFree.cbTimeLeave=(BYTE)(TIME_FREE-__min(dwPassTime,TIME_FREE));

			//���ͳ���
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));

			//������ʾ
			TCHAR szTipMsg[128];
			_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("��������ׯ����Ϊ��%ld,��������Ϊ��%ld,�������Ϊ��%ld"),m_lApplyBankerCondition,
				m_lAreaLimitScore,m_lUserLimitScore);
			
			m_pITableFrame->SendGameMessage(pIServerUserItem,szTipMsg,SMT_INFO);
						
			//����������
			SendApplyUser(pIServerUserItem);

			return bSuccess;
		}
	case GS_PLACE_JETTON:		//��Ϸ״̬
	case GS_GAME_END:			//����״̬
		{
			//���ͼ�¼
			SendGameRecord(pIServerUserItem);		

			//��������
			CMD_S_StatusPlay StatusPlay={0};

			//ȫ����ע
			CopyMemory(StatusPlay.lAllJettonScore,m_lAllJettonScore,sizeof(StatusPlay.lAllJettonScore));

			//�����ע
			if (pIServerUserItem->GetUserStatus()!=US_LOOKON)
			{
				for (int nAreaIndex=1; nAreaIndex<=AREA_COUNT; ++nAreaIndex)
					StatusPlay.lUserJettonScore[nAreaIndex] = m_lUserJettonScore[nAreaIndex][wChiarID];

				//�����ע
				StatusPlay.lUserMaxScore=min(pIServerUserItem->GetUserScore()->lScore,m_lUserLimitScore*10);
			}

			//������Ϣ
			StatusPlay.lApplyBankerCondition=m_lApplyBankerCondition;		
			StatusPlay.lAreaLimitScore=m_lAreaLimitScore;		

			//ׯ����Ϣ
			StatusPlay.bEnableSysBanker=m_bEnableSysBanker;
			StatusPlay.wBankerUser=m_wCurrentBanker;			
			StatusPlay.cbBankerTime=m_wBankerTime;
			StatusPlay.lBankerWinScore=m_lBankerWinScore;	
			if (m_wCurrentBanker!=INVALID_CHAIR)
			{
				IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);
				StatusPlay.lBankerScore=pIServerUserItem->GetUserScore()->lScore;
			}	

			//ȫ����Ϣ
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusPlay.cbGameStatus=m_pITableFrame->GetGameStatus();			
			StatusPlay.cbTimeLeave=(BYTE)(TIME_PLACE_JETTON-__min(dwPassTime,TIME_PLACE_JETTON));
			//�����ж�
			if (cbGameStatus==GS_GAME_END)
			{
				StatusPlay.cbTimeLeave=(BYTE)(TIME_GAME_END-__min(dwPassTime,TIME_GAME_END));
				//���óɼ�
				StatusPlay.lEndUserScore=m_lUserWinScore[wChiarID];

				//��������
				StatusPlay.lEndUserReturnScore=m_lUserReturnScore[wChiarID];

				////����˰��
				//if (m_lUserRevenue[wChiarID]>0) StatusPlay.lEndRevenue=m_lUserRevenue[wChiarID];
				//else if (m_wCurrentBanker!=INVALID_CHAIR) StatusPlay.lEndRevenue=m_lUserRevenue[m_wCurrentBanker];
				//else StatusPlay.lEndRevenue=0;

				//ׯ�ҳɼ�
				StatusPlay.lEndBankerScore=m_lBankerCurGameScore;

				//�˿���Ϣ
				CopyMemory(StatusPlay.cbTableCardArray,m_cbTableCardArray,sizeof(m_cbTableCardArray));
			}

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
	case IDI_FREE:		//����ʱ��
		{
			//��ʼ��Ϸ
			m_pITableFrameControl->StartGame();
			//����ʱ��
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_PLACE_JETTON,TIME_PLACE_JETTON*1000,1,0L);
			//����״̬
			m_pITableFrame->SetGameStatus(GS_PLACE_JETTON);
			return true;
		}
	case IDI_PLACE_JETTON:		//��עʱ��
		{
			//״̬�ж�(��ֹǿ���ظ�����)
			if (m_pITableFrame->GetGameStatus()!=GS_GAME_END)
			{
				//����״̬
				m_pITableFrame->SetGameStatus(GS_GAME_END);			
				//������Ϸ
				OnEventGameEnd(INVALID_CHAIR,NULL,GER_NORMAL);
				//����ʱ��
				m_dwJettonTime=(DWORD)time(NULL);
				m_pITableFrame->SetGameTimer(IDI_GAME_END,TIME_GAME_END*1000,1,0L);			
			}
			return true;
		}
	case IDI_GAME_END:			//������Ϸ
		{
			//д�����
			for ( WORD wUserChairID = 0; wUserChairID < GAME_PLAYER; ++wUserChairID )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserChairID);
				if ( pIServerUserItem == NULL ) continue;

				//ʤ������
				enScoreKind ScoreKind=(m_lUserWinScore[wUserChairID]>0L)?enScoreKind_Win:enScoreKind_Lost;

				//д�����
				if (m_lUserWinScore[wUserChairID]!=0L) 
					m_pITableFrame->WriteUserScore(wUserChairID,m_lUserWinScore[wUserChairID],0, ScoreKind);

				//��ׯ�ж�
				__int64 lUserScore=pIServerUserItem->GetUserScore()->lScore;
				if (wUserChairID!=m_wCurrentBanker && lUserScore<m_lApplyBankerCondition)
				{
					for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
					{
						if (wUserChairID!=m_ApplyUserArray[i]) continue;

						//ɾ�����
						m_ApplyUserArray.RemoveAt(i);

						//������Ϣ
						CMD_S_CancelBanker CancelBanker;
						ZeroMemory(&CancelBanker,sizeof(CancelBanker));

						//���ñ���
						lstrcpyn(CancelBanker.szCancelUser,pIServerUserItem->GetAccounts(),CountArray(CancelBanker.szCancelUser));

						//������Ϣ
						m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));
						m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));

						//��ʾ��Ϣ
						TCHAR szTipMsg[128];
						_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("������Ľ����������ׯ����������%ld��,���Զ���ׯ��"),m_lApplyBankerCondition);
						SendGameMessage(wUserChairID,szTipMsg);

						break;
					}
				}
			}

			//������Ϸ
			m_pITableFrame->ConcludeGame();
			//����ʱ��
			m_pITableFrame->SetGameStatus(GS_FREE);
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_FREE,TIME_FREE*1000,1,0L);

			//�л�ׯ��
			ChangeBanker(false);

			//������Ϣ
			CMD_S_GameFree GameFree;
			ZeroMemory(&GameFree,sizeof(GameFree));
			GameFree.cbTimeLeave=TIME_FREE;
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_FREE,&GameFree,sizeof(GameFree));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_FREE,&GameFree,sizeof(GameFree));

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
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			CMD_C_PlaceJetton * pPlaceJetton=(CMD_C_PlaceJetton *)pDataBuffer;
			return OnUserPlaceJetton(pUserData->wChairID,pPlaceJetton->cbJettonArea,pPlaceJetton->lJettonScore);
		}
	case SUB_C_APPLY_BANKER:		//������ׯ
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus==US_LOOKON) return true;

			return OnUserApplyBanker(pIServerUserItem);	
		}
	case SUB_C_CANCEL_BANKER:		//ȡ����ׯ
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus==US_LOOKON) return true;

			return OnUserCancelBanker(pIServerUserItem);	
		}
	case SUB_C_CONTINUE_CARD:		//��������
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus==US_LOOKON) return true;
			if (pUserData->wChairID!=m_wCurrentBanker) return true;
			if (m_cbLeftCardCount < 8) return true;

			//���ñ���
			m_bContiueCard=true;

			//������Ϣ
			SendGameMessage(pUserData->wChairID,TEXT("���óɹ�����һ�ֽ��������ƣ�"));

			return true;
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
		m_pITableFrame->SetGameTimer(IDI_FREE,TIME_FREE*1000,1,NULL);
		m_pITableFrame->SetGameStatus(GS_FREE);
	}

	//������ʾ
	TCHAR szTipMsg[128];
	_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("��������ׯ����Ϊ��%ld,��������Ϊ��%ld,�������Ϊ��%ld"),m_lApplyBankerCondition,
		m_lAreaLimitScore,m_lUserLimitScore);
	m_pITableFrame->SendGameMessage(pIServerUserItem,szTipMsg,SMT_INFO);

	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//��¼�ɼ�
	if (bLookonUser==false)
	{
		//�л�ׯ��
		if (wChairID==m_wCurrentBanker)
		{
			if(m_pITableFrame->GetGameStatus() == GS_FREE)
				ChangeBanker(true);
			m_bContiueCard=false;
		}

		//ȡ������
		for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
		{
			if (wChairID!=m_ApplyUserArray[i]) 
				continue;

			//ɾ�����
			m_ApplyUserArray.RemoveAt(i);

			//�������
			CMD_S_CancelBanker CancelBanker;
			ZeroMemory(&CancelBanker,sizeof(CancelBanker));

			//���ñ���
			lstrcpyn(CancelBanker.szCancelUser,pIServerUserItem->GetAccounts(),CountArray(CancelBanker.szCancelUser));

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));
			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));

			break;
		}

		return true;
	}

	return true;
}

//��ע�¼�
bool CTableFrameSink::OnUserPlaceJetton(WORD wChairID, BYTE cbJettonArea, LONG lJettonScore)
{
	//Ч�����
	ASSERT((cbJettonArea<=ID_HUANG_MEN && cbJettonArea>=ID_TIAN_MEN)&&(lJettonScore>0L));
	if ((cbJettonArea>ID_HUANG_MEN)||(lJettonScore<=0L) || cbJettonArea<ID_TIAN_MEN)
	{
		return false;
	}
	////Ч��״̬
	if (m_pITableFrame->GetGameStatus()!=GS_PLACE_JETTON)
	{
		CMD_S_PlaceJettonFail PlaceJettonFail;
		ZeroMemory(&PlaceJettonFail,sizeof(PlaceJettonFail));
		PlaceJettonFail.lJettonArea=cbJettonArea;
		PlaceJettonFail.lPlaceScore=lJettonScore;
		PlaceJettonFail.wPlaceUser=wChairID;
		//������Ϣ
		m_pITableFrame->SendTableData(wChairID,SUB_S_PLACE_JETTON_FAIL,&PlaceJettonFail,sizeof(PlaceJettonFail));
		return true;
	}
	//ׯ���ж�
	if (m_wCurrentBanker==wChairID)
	{
		return true;
	}
	if (m_bEnableSysBanker==false && m_wCurrentBanker==INVALID_CHAIR) 
	{	
		return true;
	}
	//��������
	IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
	__int64 lJettonCount=0L;
	for (int nAreaIndex=1; nAreaIndex<=AREA_COUNT; ++nAreaIndex) 
		lJettonCount += m_lUserJettonScore[nAreaIndex][wChairID];

	//��һ���
	__int64 lUserScore = pIServerUserItem->GetUserScore()->lScore;

	//�Ϸ�У��
	if (lUserScore < lJettonCount + lJettonScore) 
		return true;
	if (m_lUserLimitScore < lJettonCount + lJettonScore)
		return true;

	//�ɹ���ʶ
	bool bPlaceJettonSuccess=true;

	//�Ϸ���֤
	if (GetUserMaxJetton(wChairID) >= lJettonScore)
	{
		//������ע
		m_lAllJettonScore[cbJettonArea] += lJettonScore;
		m_lUserJettonScore[cbJettonArea][wChairID] += lJettonScore;			
	}
	else
	{
		bPlaceJettonSuccess=false;
	}

	if (bPlaceJettonSuccess)
	{
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
	}
	else
	{
		CMD_S_PlaceJettonFail PlaceJettonFail;
		ZeroMemory(&PlaceJettonFail,sizeof(PlaceJettonFail));
		PlaceJettonFail.lJettonArea=cbJettonArea;
		PlaceJettonFail.lPlaceScore=lJettonScore;
		PlaceJettonFail.wPlaceUser=wChairID;

		//������Ϣ
		m_pITableFrame->SendTableData(wChairID,SUB_S_PLACE_JETTON_FAIL,&PlaceJettonFail,sizeof(PlaceJettonFail));
	}

	return true;
}

//�����˿�
bool CTableFrameSink::DispatchTableCard()
{
	//��������
	int const static nDispatchCardCount=25;
	bool bContiueCard=m_bContiueCard;
	if (m_cbLeftCardCount<nDispatchCardCount) bContiueCard=false;

	//��������
	if (true==bContiueCard)
	{
		//�����˿�
		CopyMemory(&m_cbTableCardArray[0][0],m_cbTableCard,sizeof(m_cbTableCardArray));
		m_cbLeftCardCount -= nDispatchCardCount;
		if (m_cbLeftCardCount>0) CopyMemory(m_cbTableCard, m_cbTableCard + nDispatchCardCount, sizeof(BYTE)*m_cbLeftCardCount);
	}
	else
	{
		//����ϴ��
		BYTE bcCard[CARD_COUNT];
		m_GameLogic.RandCardList(bcCard,54);
		m_bcFirstPostCard = bcCard[0];
		m_GameLogic.RandCardList(m_cbTableCard,CountArray(m_cbTableCard));	

		//�����˿�
		CopyMemory(&m_cbTableCardArray[0][0], m_cbTableCard, sizeof(m_cbTableCardArray));

		if(0)
		{

			BYTE temp1[5]={0x3D,0x08,0x38,0x26,0x05};
			BYTE temp2[5]={0x41,0x08,0x08,0x28,0x17};
			BYTE temp3[]={ 0x2D,0x0C,0x18,0x33,0x31};
			BYTE temp4[]={ 0x27,0x02,0x42,0x0D,0x07};
			BYTE temp5[]={ 0x16,0x12,0x1C,0x3B,0x3A};
			CopyMemory(&m_cbTableCardArray[0][0], temp1, sizeof(m_cbTableCardArray[0]));
			CopyMemory(&m_cbTableCardArray[1][0], temp2, sizeof(m_cbTableCardArray[1]));
			CopyMemory(&m_cbTableCardArray[2][0], temp3, sizeof(m_cbTableCardArray[2]));
			CopyMemory(&m_cbTableCardArray[3][0], temp4, sizeof(m_cbTableCardArray[3]));
			CopyMemory(&m_cbTableCardArray[4][0], temp5, sizeof(m_cbTableCardArray[3]));
	
		}

		//ׯ���ж�
		if (INVALID_CHAIR != m_wCurrentBanker)
		{
			m_cbLeftCardCount=CountArray(m_cbTableCard)-nDispatchCardCount;
			CopyMemory(m_cbTableCard, m_cbTableCard + nDispatchCardCount, sizeof(BYTE)*m_cbLeftCardCount);
		}
		else
		{
			m_cbLeftCardCount=0;
		}
	}

	//������Ŀ
	for (int i=0; i<CountArray(m_cbCardCount); ++i) m_cbCardCount[i]=5;

	//���Ʊ�־
	m_bContiueCard=false;

	return true;
}

//����ׯ��
bool CTableFrameSink::OnUserApplyBanker(IServerUserItem *pIApplyServerUserItem)
{
	//�Ϸ��ж�
	__int64 lUserScore=pIApplyServerUserItem->GetUserScore()->lScore;
	if (lUserScore<m_lApplyBankerCondition)
	{
		m_pITableFrame->SendGameMessage(pIApplyServerUserItem,TEXT("��Ľ�Ҳ���������ׯ�ң�����ʧ�ܣ�"),SMT_INFO|SMT_EJECT);
		return true;
	}

	//�����ж�
	WORD wApplyUserChairID=pIApplyServerUserItem->GetChairID();
	for (INT_PTR nUserIdx=0; nUserIdx<m_ApplyUserArray.GetCount(); ++nUserIdx)
	{
		WORD wChairID=m_ApplyUserArray[nUserIdx];
		if (wChairID==wApplyUserChairID)
		{
			m_pITableFrame->SendGameMessage(pIApplyServerUserItem,TEXT("���Ѿ�������ׯ�ң�����Ҫ�ٴ����룡"),SMT_INFO|SMT_EJECT);
			return true;
		}
	}

	//������Ϣ 
	m_ApplyUserArray.Add(wApplyUserChairID);

	//�������
	CMD_S_ApplyBanker ApplyBanker;
	ZeroMemory(&ApplyBanker,sizeof(ApplyBanker));

	//���ñ���
	ApplyBanker.wApplyUser=wApplyUserChairID;

	//������Ϣ
	m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof(ApplyBanker));
	m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof(ApplyBanker));

	//�л��ж�
	if (m_pITableFrame->GetGameStatus()==GS_FREE && m_ApplyUserArray.GetCount()==1)
	{
		ChangeBanker(false);
	}

	return true;
}

//ȡ������
bool CTableFrameSink::OnUserCancelBanker(IServerUserItem *pICancelServerUserItem)
{
	//��ǰׯ��
	if (pICancelServerUserItem->GetChairID()==m_wCurrentBanker && m_pITableFrame->GetGameStatus()!=GS_FREE)
	{
		//������Ϣ
		m_pITableFrame->SendGameMessage(pICancelServerUserItem,TEXT("��Ϸ�Ѿ���ʼ��������ȡ����ׯ��"),SMT_INFO|SMT_EJECT);
		return true;
	}

	//�����ж�
	for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
	{
		//��ȡ���
		WORD wChairID=m_ApplyUserArray[i];
		IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);

		//��������
		if (pIServerUserItem==NULL) continue;
		if (pIServerUserItem->GetUserID()!=pICancelServerUserItem->GetUserID()) continue;

		//ɾ�����
		m_ApplyUserArray.RemoveAt(i);

		if (m_wCurrentBanker!=wChairID)
		{
			//�������
			CMD_S_CancelBanker CancelBanker;
			ZeroMemory(&CancelBanker,sizeof(CancelBanker));

			//���ñ���
			lstrcpyn(CancelBanker.szCancelUser,pIServerUserItem->GetAccounts(),CountArray(CancelBanker.szCancelUser));

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));
			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));
		}
		else if (m_wCurrentBanker==wChairID)
		{
			//�л�ׯ�� 
			m_wCurrentBanker=INVALID_CHAIR;
			ChangeBanker(true);
		}

		return true;
	}

	return false;
}

//����ׯ��
bool CTableFrameSink::ChangeBanker(bool bCancelCurrentBanker)
{
	//�л���ʶ
	bool bChangeBanker=false;
	
	//��ׯ����
	WORD wBankerTime=GetPrivateProfileInt(TEXT("BankerCondition"), TEXT("Time"), 10, m_szConfigFileName);

	//ȡ����ǰ
	if (bCancelCurrentBanker)
	{
		for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
		{
			//��ȡ���
			WORD wChairID=m_ApplyUserArray[i];

			//��������
			if (wChairID!=m_wCurrentBanker) continue;

			//ɾ�����
			m_ApplyUserArray.RemoveAt(i);

			break;
		}

		//����ׯ��
		m_wCurrentBanker=INVALID_CHAIR;

		//�ֻ��ж�
		if (m_pITableFrame->GetGameStatus()==GS_FREE && m_ApplyUserArray.GetCount()!=0)
		{
			m_wCurrentBanker=m_ApplyUserArray[0];
		}

		//���ñ���
		bChangeBanker=true;
	}
	//��ׯ�ж�
	else if (m_wCurrentBanker!=INVALID_CHAIR)
	{
		//��ȡׯ��
		IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);
		//�����ж�
		if(pIServerUserItem!= NULL)
		{
			LONGLONG lBankerScore=pIServerUserItem->GetUserScore()->lScore;

			//�����ж�
			if (wBankerTime<=m_wBankerTime || lBankerScore<m_lApplyBankerCondition)
			{
				//�������
				for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
				{
					//��ȡ���
					WORD wChairID=m_ApplyUserArray[i];

					//��������
					if (wChairID!=m_wCurrentBanker) continue;

					//ɾ�����
					m_ApplyUserArray.RemoveAt(i);

					break;
				}

				//����ׯ��
				m_wCurrentBanker=INVALID_CHAIR;

				//�ֻ��ж�
				if (m_ApplyUserArray.GetCount()!=0)
				{
					m_wCurrentBanker=m_ApplyUserArray[0];
				}

				bChangeBanker=true;

				//��ʾ��Ϣ
				TCHAR szTipMsg[128];
				if (lBankerScore<m_lApplyBankerCondition)
					_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("[ %s ]��������(%ld)��ǿ�л�ׯ!"),pIServerUserItem->GetAccounts(),m_lApplyBankerCondition);
				else
					_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("[ %s ]��ׯ�����ﵽ(%ld)��ǿ�л�ׯ!"),pIServerUserItem->GetAccounts(),wBankerTime);

				//������Ϣ
				SendGameMessage(INVALID_CHAIR,szTipMsg);	
			}

		}
		else
		{
			for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
			{
				//��ȡ���
				WORD wChairID=m_ApplyUserArray[i];

				//��������
				if (wChairID!=m_wCurrentBanker)
					continue;

				//ɾ�����
				m_ApplyUserArray.RemoveAt(i);

				break;
			}
			//����ׯ��
			m_wCurrentBanker=INVALID_CHAIR;
		}

	}

	if (m_wCurrentBanker==INVALID_CHAIR && m_ApplyUserArray.GetCount()!=0)
	{
		m_wCurrentBanker=m_ApplyUserArray[0];
		bChangeBanker=true;
	}



	//�л��ж�
	if (bChangeBanker)
	{
		//���ñ���
		m_wBankerTime = 0;
		m_lBankerWinScore=0;

		//������Ϣ
		CMD_S_ChangeBanker ChangeBanker;
		ZeroMemory(&ChangeBanker,sizeof(ChangeBanker));
		ChangeBanker.wBankerUser=m_wCurrentBanker;
		if (m_wCurrentBanker!=INVALID_CHAIR)
		{
			IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);
			ChangeBanker.lBankerScore=pIServerUserItem->GetUserScore()->lScore;
		}
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_CHANGE_BANKER,&ChangeBanker,sizeof(ChangeBanker));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_CHANGE_BANKER,&ChangeBanker,sizeof(ChangeBanker));

		if (m_wCurrentBanker!=INVALID_CHAIR)
		{
			//��ȡ��Ϣ
			LONG lMessageCount=GetPrivateProfileInt(TEXT("Message"),TEXT("MessageCount"),0,m_szConfigFileName);
			if (lMessageCount!=0)
			{
				//��ȡ����
				LONG lIndex=rand()%lMessageCount;
				TCHAR szKeyName[32],szMessage1[256],szMessage2[256];				
				_sntprintf(szKeyName,CountArray(szKeyName),TEXT("Item%ld"),lIndex);
				GetPrivateProfileString(TEXT("Message"),szKeyName,TEXT("��ϲ[ %s ]��ׯ"),szMessage1,CountArray(szMessage1),m_szConfigFileName);

				//��ȡ���
				IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);

				//������Ϣ
				_sntprintf(szMessage2,CountArray(szMessage2),szMessage1,pIServerUserItem->GetAccounts());
				SendGameMessage(INVALID_CHAIR,szMessage2);
			}
		}
	}

	return bChangeBanker;
}



//����ׯ��
void CTableFrameSink::SendApplyUser( IServerUserItem *pRcvServerUserItem )
{
	for (INT_PTR nUserIdx=0; nUserIdx<m_ApplyUserArray.GetCount(); ++nUserIdx)
	{
		WORD wChairID=m_ApplyUserArray[nUserIdx];

		//��ȡ���
		IServerUserItem *pServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
		if (!pServerUserItem) continue;

		//ׯ���ж�
		if (pServerUserItem->GetChairID()==m_wCurrentBanker) continue;

		//�������
		CMD_S_ApplyBanker ApplyBanker;
		ApplyBanker.wApplyUser=wChairID;

		//������Ϣ
		m_pITableFrame->SendUserData(pRcvServerUserItem, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof(ApplyBanker));
	}
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) 
{
	//�л�ׯ��
	if (wChairID==m_wCurrentBanker) ChangeBanker(true);

	//ȡ������
	for (WORD i=0; i<m_ApplyUserArray.GetCount(); ++i)
	{
		if (wChairID!=m_ApplyUserArray[i]) continue;

		//ɾ�����
		m_ApplyUserArray.RemoveAt(i);

		//�������
		CMD_S_CancelBanker CancelBanker;
		ZeroMemory(&CancelBanker,sizeof(CancelBanker));

		//���ñ���
		lstrcpyn(CancelBanker.szCancelUser,pIServerUserItem->GetAccounts(),CountArray(CancelBanker.szCancelUser));

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));
		m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_CANCEL_BANKER, &CancelBanker, sizeof(CancelBanker));

		break;
	}

	return true;
}

//�����ע
__int64 CTableFrameSink::GetUserMaxJetton(WORD wChairID)
{
	IServerUserItem *pIMeServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
	if (NULL==pIMeServerUserItem)
		return 0L;

	int iTimer = 10;
	//����ע��
	LONGLONG lNowJetton = 0;	
	ASSERT(AREA_COUNT<=CountArray(m_lUserJettonScore));
	for (int nAreaIndex=1; nAreaIndex<=AREA_COUNT; ++nAreaIndex)
		lNowJetton += m_lUserJettonScore[nAreaIndex][wChairID];

	//ׯ�ҽ��
	LONGLONG lBankerScore=2147483647;
	if (m_wCurrentBanker!=INVALID_CHAIR)
	{
		IServerUserItem *pIUserItemBanker=m_pITableFrame->GetServerUserItem(m_wCurrentBanker);
		if (NULL!=pIUserItemBanker) 
			lBankerScore=pIUserItemBanker->GetUserScore()->lScore;
	}
	for (int nAreaIndex=1; nAreaIndex<=AREA_COUNT; ++nAreaIndex)
		lBankerScore-=m_lAllJettonScore[nAreaIndex]*iTimer;

	//��������
	__int64 lMeMaxScore = min((pIMeServerUserItem->GetUserScore()->lScore-lNowJetton*iTimer)/iTimer, m_lUserLimitScore);

	//const tagUserScore *Info = pIMeServerUserItem->GetUserScore();
	//const tagServerUserData *Data = pIMeServerUserItem->GetUserData();

	//��������
	lMeMaxScore=min(lMeMaxScore,m_lAreaLimitScore);

	//ׯ������
	lMeMaxScore=min(lMeMaxScore,lBankerScore/iTimer);

	//��������
	ASSERT(lMeMaxScore >= 0);
	lMeMaxScore = max(lMeMaxScore, 0);

	return (lMeMaxScore);

}
//����÷�
__int64 CTableFrameSink::CalculateScore()
{
//	return 1;
	//��������
	LONG static cbRevenue=m_pGameServiceOption->wRevenue;

	//�ƶ����
	bool static bWinTianMen, bWinDiMen, bWinXuanMen,bWinHuang;
	BYTE TianMultiple,diMultiple,TianXuanltiple,HuangMultiple;
	TianMultiple  = 1;
	diMultiple = 1 ;
	TianXuanltiple = 1;
	HuangMultiple = 1;
	DeduceWinner(bWinTianMen, bWinDiMen, bWinXuanMen,bWinHuang,TianMultiple,diMultiple,TianXuanltiple,HuangMultiple );

	//��Ϸ��¼
	tagServerGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];
	GameRecord.bWinShunMen=bWinTianMen;
	GameRecord.bWinDuiMen=bWinDiMen;
	GameRecord.bWinDaoMen=bWinXuanMen;
	GameRecord.bWinHuang = bWinHuang;

	BYTE  cbMultiple[] = {0, 1, 1, 1, 1, 1, 1};

	cbMultiple[1] = TianMultiple;
	cbMultiple[2] = diMultiple;
	cbMultiple[3] = TianXuanltiple;
	cbMultiple[4] = HuangMultiple;

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

	//�����ע
	__int64 *const pUserScore[] = {NULL,m_lUserJettonScore[ID_TIAN_MEN], m_lUserJettonScore[ID_DI_MEN], m_lUserJettonScore[ID_XUAN_MEN],
		m_lUserJettonScore[ID_HUANG_MEN]};	

	//������
	//BYTE static const cbMultiple[] = {0, 1, 1, 1, 1, 1, 1};

	//ʤ����ʶ
	bool static bWinFlag[AREA_COUNT+1];
	bWinFlag[0]=false;
	bWinFlag[ID_TIAN_MEN]=bWinTianMen;
	bWinFlag[ID_DI_MEN]=bWinDiMen;
	bWinFlag[ID_XUAN_MEN]=bWinXuanMen;
	bWinFlag[ID_HUANG_MEN]=bWinHuang;

	//FILE *pf = fopen("C://ServLong.txt","ab+");
	TCHAR szBuffer[256] = TEXT("");

	//�������
	for (WORD wChairID=0; wChairID<GAME_PLAYER; wChairID++)
	{
		//ׯ���ж�
		if (m_wCurrentBanker==wChairID) continue;

		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
		if (pIServerUserItem==NULL) continue;

		for (WORD wAreaIndex = ID_TIAN_MEN; wAreaIndex <= ID_HUANG_MEN; ++wAreaIndex)
		{
			if (true==bWinFlag[wAreaIndex]) 
			{
				m_lUserWinScore[wChairID] += ( pUserScore[wAreaIndex][wChairID] * cbMultiple[wAreaIndex] ) ;
				m_lUserReturnScore[wChairID] += pUserScore[wAreaIndex][wChairID] ;
				lBankerWinScore -= ( pUserScore[wAreaIndex][wChairID] * cbMultiple[wAreaIndex] ) ;
			}
			else
			{
				lUserLostScore[wChairID] -= pUserScore[wAreaIndex][wChairID]*cbMultiple[wAreaIndex];
				lBankerWinScore += pUserScore[wAreaIndex][wChairID]*cbMultiple[wAreaIndex];
			}
		}

		////����˰��
		//if (0 < m_lUserWinScore[wChairID])
		//{
		//	float fRevenuePer=float(cbRevenue/1000.+0.000001);
		//	m_lUserRevenue[wChairID]  = LONG(m_lUserWinScore[wChairID]*fRevenuePer);
		//	m_lUserWinScore[wChairID] -= m_lUserRevenue[wChairID];
		//}

		//�ܵķ���
		memset(szBuffer,0,256);
		m_lUserWinScore[wChairID] += lUserLostScore[wChairID];
	}

	//ׯ�ҳɼ�
	if (m_wCurrentBanker!=INVALID_CHAIR)
	{
		m_lUserWinScore[m_wCurrentBanker] = lBankerWinScore;

		////����˰��
		//if (0 < m_lUserWinScore[m_wCurrentBanker])
		//{
		//	float fRevenuePer=float(cbRevenue/1000.+0.000001);
		//	m_lUserRevenue[m_wCurrentBanker]  = LONG(m_lUserWinScore[m_wCurrentBanker]*fRevenuePer);
		//	m_lUserWinScore[m_wCurrentBanker] -= m_lUserRevenue[m_wCurrentBanker];
		//	lBankerWinScore = m_lUserWinScore[m_wCurrentBanker];
		//}	
	}

	//�ۼƻ���
	m_lBankerWinScore += lBankerWinScore;

	//��ǰ����
	m_lBankerCurGameScore=lBankerWinScore;
	//memset(szBuffer,0,256);
	//_snprintf(szBuffer,CountArray(szBuffer),TEXT("ׯ�ҵ÷� %d\r\n"),lBankerWinScore);
	//fwrite(szBuffer,1,strlen(szBuffer)+1,pf);
	//fclose(pf);


	

	return lBankerWinScore;
}


void CTableFrameSink::DeduceWinner(bool &bWinTian, bool &bWinDi, bool &bWinXuan,bool &bWinHuan,BYTE &TianMultiple,BYTE &diMultiple,BYTE &TianXuanltiple,BYTE &HuangMultiple)
{
	//��С�Ƚ�
	bWinTian=m_GameLogic.CompareCard(m_cbTableCardArray[BANKER_INDEX],5,m_cbTableCardArray[SHUN_MEN_INDEX],5,TianMultiple)==1?true:false;
	bWinDi=m_GameLogic.CompareCard(m_cbTableCardArray[BANKER_INDEX],5,m_cbTableCardArray[DUI_MEN_INDEX],5,diMultiple)==1?true:false;
	bWinXuan=m_GameLogic.CompareCard(m_cbTableCardArray[BANKER_INDEX],5,m_cbTableCardArray[DAO_MEN_INDEX],5,TianXuanltiple)==1?true:false;
	bWinHuan=m_GameLogic.CompareCard(m_cbTableCardArray[BANKER_INDEX],5,m_cbTableCardArray[HUAN_MEN_INDEX],5,HuangMultiple)==1?true:false;
}

//���ͼ�¼
void CTableFrameSink::SendGameRecord(IServerUserItem *pIServerUserItem)
{
	WORD wBufferSize=0;
	BYTE cbBuffer[SOCKET_BUFFER];
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
}

//������Ϣ
void CTableFrameSink::SendGameMessage(WORD wChairID, LPCTSTR pszTipMsg)
{
	if (wChairID==INVALID_CHAIR)
	{
		//��Ϸ���
		for (WORD i=0; i<GAME_PLAYER; ++i)
		{
			IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(i);
			if (pIServerUserItem==NULL) continue;
			m_pITableFrame->SendGameMessage(pIServerUserItem,pszTipMsg,SMT_INFO);
		}

		//�Թ����
		WORD wIndex=0;
		do {
			IServerUserItem *pILookonServerUserItem=m_pITableFrame->EnumLookonUserItem(wIndex++);
			if (pILookonServerUserItem==NULL) break;

			m_pITableFrame->SendGameMessage(pILookonServerUserItem,pszTipMsg,SMT_INFO);

		}while(true);
	}
	else
	{
		IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
		if (pIServerUserItem!=NULL) m_pITableFrame->SendGameMessage(pIServerUserItem,pszTipMsg,SMT_INFO|SMT_EJECT);
	}
}
//////////////////////////////////////////////////////////////////////////
//���в���
#ifdef __SPECIAL___
bool __cdecl CTableFrameSink::OnActionUserBank(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	if (pIServerUserItem->GetUserStatus()!=US_LOOKON && pIServerUserItem->GetUserScore()->lScore < m_lApplyBankerCondition)
	{
		//ׯ���ж�
		OnActionUserStandUp(pIServerUserItem->GetChairID(), pIServerUserItem, false);
	}
	return true;
}
#endif

void CTableFrameSink::RobotAi()
{
	TCHAR szINI[512];
	::GetModulePath(szINI, sizeof(szINI));
	SafeStrCat(szINI, "\\100nnServer.ini", sizeof(szINI));
	UINT lWinControl = GetPrivateProfileInt("Option", "OpenControl", 0, szINI);

	BYTE chCardSort[5] = { BANKER_INDEX, SHUN_MEN_INDEX, DUI_MEN_INDEX, DAO_MEN_INDEX, HUAN_MEN_INDEX };
	SortCardComp(chCardSort, 5);

	if (lWinControl == 0)
	{
		return;
	}
	switch (lWinControl)
	{
	case 1:			//ׯ��ͨ��
		{
			BYTE chDescCardSort[5] = { BANKER_INDEX, -1, -1, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 2:			//����Ӯ��ׯ�ҳ�����3��
		{
			BYTE chDescCardSort[5] = { SHUN_MEN_INDEX, BANKER_INDEX, -1, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 3:			//����Ӯ��ׯ�ҳ�����3��
		{
			BYTE chDescCardSort[5] = { DUI_MEN_INDEX, BANKER_INDEX, -1, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 4:			//����Ӯ��ׯ�ҳ�����3��
		{
			BYTE chDescCardSort[5] = { DAO_MEN_INDEX, BANKER_INDEX, -1, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 5:			//����Ӯ��ׯ�ҳ�����3��
		{
			BYTE chDescCardSort[5] = { HUAN_MEN_INDEX, BANKER_INDEX, -1, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 6:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { SHUN_MEN_INDEX, DUI_MEN_INDEX, BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 7:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { SHUN_MEN_INDEX, DAO_MEN_INDEX, BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 8:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { SHUN_MEN_INDEX, HUAN_MEN_INDEX, BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 9:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { DUI_MEN_INDEX, DAO_MEN_INDEX , BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 10:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { DUI_MEN_INDEX, HUAN_MEN_INDEX , BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 11:			//���š�����Ӯ��ׯ�ҳ�����2��
		{
			BYTE chDescCardSort[5] = { DAO_MEN_INDEX, HUAN_MEN_INDEX, BANKER_INDEX, -1, -1 };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 12:			//�졢�ء���Ӯ��ׯ�ҳ�����1��
		{
			BYTE chDescCardSort[5] = { -1, -1, -1, BANKER_INDEX, HUAN_MEN_INDEX };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 13:			//�졢�ء���Ӯ��ׯ�ҳ�����1��
		{
			BYTE chDescCardSort[5] = { -1, -1, -1, BANKER_INDEX, DAO_MEN_INDEX };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 14:			//�ء�������Ӯ��ׯ�ҳ�����1��
		{
			BYTE chDescCardSort[5] = { -1, -1, -1, BANKER_INDEX , SHUN_MEN_INDEX };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	case 15:			//ׯ��ͨ��
		{
			BYTE chDescCardSort[5] = { -1, -1, -1, -1, BANKER_INDEX };
			ChangeCard(chCardSort, chDescCardSort);
		}
		break;
	}
	
}

void CTableFrameSink::SortCardComp( BYTE chCardComp[], int nCount )
{
	for (int i = 0; i < nCount - 1; i++)
	{
		for ( int j = i + 1; j < nCount; j++)
		{
			BYTE Multiple = 0;
			bool bWin = m_GameLogic.CompareCard(m_cbTableCardArray[chCardComp[i]],5,m_cbTableCardArray[chCardComp[j]],5, Multiple)==1?true:false;
			if (bWin)
			{
				BYTE nIndex = chCardComp[i];
				chCardComp[i] = chCardComp[j];
				chCardComp[j] = nIndex; 
			}
		}
	}
}

void CTableFrameSink::ChangeCard( BYTE chCardComp[], BYTE chDescCardComp[] )
{
	for (int i = 0; i < 5; i++)
	{
		BYTE nCardIndex = chDescCardComp[i];
		if (nCardIndex != 255)
		{
			int j = 0;
			for (j = 0; j < 5; j++)
			{
				if (chCardComp[j] == nCardIndex)
					break;
			}
			//i��j��λ�õ���
			if (i != j)
			{
				BYTE bFirstCard = m_cbTableCardArray[chCardComp[i]][0];
				BYTE bNextCard = m_cbTableCardArray[chCardComp[i]][1];
				BYTE bthirdCard = m_cbTableCardArray[chCardComp[i]][2];
				BYTE bthudCard = m_cbTableCardArray[chCardComp[i]][3];
				BYTE bFriCard = m_cbTableCardArray[chCardComp[i]][4];
				m_cbTableCardArray[chCardComp[i]][0] = m_cbTableCardArray[nCardIndex][0];
				m_cbTableCardArray[chCardComp[i]][1] = m_cbTableCardArray[nCardIndex][1];
				m_cbTableCardArray[chCardComp[i]][2] = m_cbTableCardArray[nCardIndex][2];
				m_cbTableCardArray[chCardComp[i]][3] = m_cbTableCardArray[nCardIndex][3];
				m_cbTableCardArray[chCardComp[i]][4] = m_cbTableCardArray[nCardIndex][4];
				m_cbTableCardArray[nCardIndex][0] = bFirstCard;
				m_cbTableCardArray[nCardIndex][1] = bNextCard;
				m_cbTableCardArray[nCardIndex][2] = bthirdCard;
				m_cbTableCardArray[nCardIndex][3] = bthudCard;
				m_cbTableCardArray[nCardIndex][4] = bFriCard;

				chCardComp[j] = chCardComp[i];
				chCardComp[i] = nCardIndex;
			}
		}
	}
}

/////
