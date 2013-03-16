#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"


//ʱ���ʶ
#define IDI_PLACE_JETTON			100									//��עʱ��
#define IDI_DISPATCH_CARD			301									//����ʱ��
#define IDI_SHOW_GAME_RESULT		302									//��ʾ���
#define IDI_SHOW_TIME				303
#define IDI_CUO_POKER_TIME			304									//����ʱ��

BEGIN_MESSAGE_MAP(CGameClientDlg, CGameFrameDlg)
	ON_WM_TIMER()
	ON_MESSAGE(IDM_PLACE_JETTON,OnPlaceJetton)
	ON_MESSAGE(IDM_APPLY_BANKER, OnApplyBanker)
	ON_MESSAGE(IDM_CUOPAI,OnCuoPai)
	ON_MESSAGE(IDM_ONBANK,OnBank)
END_MESSAGE_MAP()

//���캯��
CGameClientDlg::CGameClientDlg() : CGameFrameDlg(&m_GameClientView)
{
	//��ע��Ϣ
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	m_strDispatchCardTips = TEXT("");

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bPlaying = false;

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbSendCount,sizeof(m_cbSendCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
	m_cbWaitPre=0;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
	m_bMeApplyBanker = false;
	m_cbShowCount=0;
	return;
}

//��������
CGameClientDlg::~CGameClientDlg()
{
}

//��ʼ����
bool CGameClientDlg::InitGameFrame()
{
	//���ñ���
	SetWindowText(TEXT("С��"));

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	return true;
}

//���ÿ��
void CGameClientDlg::ResetGameFrame()
{
	//��ע��Ϣ
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;
	
	m_strDispatchCardTips = TEXT("");
    
	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bPlaying = false;
	m_bMeApplyBanker = false;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbSendCount,sizeof(m_cbSendCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
	m_cbWaitPre=0;

	m_cbShowCount=0;
	return;
}

//��Ϸ����
void CGameClientDlg::OnGameOptionSet()
{
	return;
}

//ʱ����Ϣ
bool CGameClientDlg::OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID)
{
	if ((nTimerID==IDI_PLACE_JETTON)&&(nElapse==0))
	{
		//���ù��
		m_GameClientView.SetCurrentJetton(0L);

		//��ֹ��ť
		//m_GameClientView.m_btJetton10000000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton1000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton10000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton100000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton500000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton1000000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton5000000.EnableWindow(FALSE);

		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled(TRUE);
		}
		//ׯ�Ұ�ť
		m_GameClientView.m_btApplyBanker.EnableWindow( FALSE );
		m_GameClientView.m_btCancelBanker.EnableWindow( FALSE );

		//��������
		PlayGameSound(AfxGetInstanceHandle(),TEXT("STOP_JETTON"));
	}

	return true;
}

//�Թ�״̬
void CGameClientDlg::OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize)
{
}

//������Ϣ
bool CGameClientDlg::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			return OnSubGameStart(pBuffer,wDataSize);
		}
	case SUB_S_PLACE_JETTON:	//�û���ע
		{
			return OnSubPlaceJetton(pBuffer,wDataSize);
		}
	case SUB_S_APPLY_BANKER:	//������ׯ
		{
			return OnUserApplyBanker( pBuffer, wDataSize );
		}
	case SUB_S_CHANGE_BANKER:	//�л�ׯ��
		{
			return OnChangeBanker( pBuffer, wDataSize );
		}
	case SUB_S_CHANGE_USER_SCORE://���»���
		{
			return OnChangeUserScore( pBuffer, wDataSize );
		}
	case SUB_S_GAME_END:		//��Ϸ����
		{
			return OnSubGameEnd(pBuffer,wDataSize);
		}
	case SUB_S_SEND_RECORD:		//��Ϸ��¼
		{
			return OnSubGameRecord(pBuffer,wDataSize);
		}
	case SUB_S_GAME_SCORE:		//��Ϸ����
		{
			return OnSubGameScore(pBuffer, wDataSize);
		}
	}

	//�������
	ASSERT(FALSE);

	return true;
}

//��Ϸ����
bool CGameClientDlg::OnGameSceneMessage(BYTE cbGameStation, bool bLookonOther, const void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE:			//����״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusFree));
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;

			//��Ϣ����
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;
			//��¼���ŵĻ�ʤ����
			m_GameClientView.m_fWinCount[0]=pStatusFree->fShunMen;
			m_GameClientView.m_fWinCount[1]=pStatusFree->fTianMen;
			m_GameClientView.m_fWinCount[2]=pStatusFree->fDaomMen;
			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusFree->lApplyBankerCondition;			

			//����λ��
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//�����ע
			m_GameClientView.SetMeMaxScore(pStatusFree->lMeMaxScore);
			m_GameClientView.SetMeTieScore(pStatusFree->lMeTieScore);
			m_GameClientView.SetMeBankerScore(pStatusFree->lMeBankerScore);
			m_GameClientView.SetMePlayerScore(pStatusFree->lMePlayerScore);
			m_GameClientView.SetMeBankerKingScore(pStatusFree->lMeBankerKingScore);
			m_GameClientView.SetMePlayerKingScore(pStatusFree->lMePlayerKingScore);
			m_GameClientView.SetMeTieSamePointScore(pStatusFree->lMeTieKingScore);

			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;
			//���ñ���
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			m_lMeTianMenScore=pStatusFree->lMeTieScore;
			m_lMeDaoMenScore=pStatusFree->lMeBankerScore;
			m_lMeShunMenScore=pStatusFree->lMePlayerScore;
			m_lMeQiaoScore = pStatusFree->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusFree->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusFree->lMePlayerKingScore;

			//ׯ����Ϣ
			if ( pStatusFree->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusFree->cbBankerTime, pStatusFree->lBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusFree->wCurrentBankerChairID ), pStatusFree->cbBankerTime, pStatusFree->lBankerScore );
			m_GameClientView.SetBankerTreasure(pStatusFree->lBankerTreasure);

			m_GameClientView.m_lKexiaScore = pStatusFree->lCurrentBankerScore-pStatusFree->lTieScore-pStatusFree->lBankerScore-pStatusFree->lPlayerScore;

			//��ע����
			m_GameClientView.PlaceUserJetton(ID_TIAN_MEN,pStatusFree->lTieScore);
			m_GameClientView.PlaceUserJetton(ID_DAO_MEN,pStatusFree->lBankerScore);
			m_GameClientView.PlaceUserJetton(ID_SHUN_MEN,pStatusFree->lPlayerScore);
			//m_GameClientView.PlaceUserJetton(ID_ZUO_JIAO,pStatusFree->lPlayerKingScore);
			//m_GameClientView.PlaceUserJetton(ID_QIAO,pStatusFree->lTieSamePointScore);
			//m_GameClientView.PlaceUserJetton(ID_YOU_JIAO,pStatusFree->lBankerKingScore);

			//���¿���
			UpdateButtonContron();

			//��������
			PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

			//����ʱ��
			SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON,pStatusFree->cbTimeLeave);

			return true;
		}
	case GS_PLAYING:		//��Ϸ״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusPlay));
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;

			//��Ϣ����
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pBuffer;
			//��¼���ŵĻ�ʤ����
			m_GameClientView.m_fWinCount[0]=pStatusPlay->fShunMen;
			m_GameClientView.m_fWinCount[1]=pStatusPlay->fTianMen;
			m_GameClientView.m_fWinCount[2]=pStatusPlay->fDaomMen;
			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusPlay->lApplyBankerCondition;
			//���ñ���
			m_lMeMaxScore=pStatusPlay->lMeMaxScore ;
			m_lMeTianMenScore=pStatusPlay->lMeTieScore;
			m_lMeDaoMenScore=pStatusPlay->lMeBankerScore;
			m_lMeShunMenScore=pStatusPlay->lMePlayerScore;
			m_lMeQiaoScore = pStatusPlay->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusPlay->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusPlay->lMePlayerKingScore;

			//����λ��
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//�����ע
			m_GameClientView.SetMeMaxScore(pStatusPlay->lMeMaxScore);	
			m_GameClientView.SetMeTieScore(pStatusPlay->lMeTieScore);
			m_GameClientView.SetMeBankerScore(pStatusPlay->lMeBankerScore);
			m_GameClientView.SetMePlayerScore(pStatusPlay->lMePlayerScore);
			m_GameClientView.SetMeBankerKingScore(pStatusPlay->lMeBankerKingScore);
			m_GameClientView.SetMePlayerKingScore(pStatusPlay->lMePlayerKingScore);
			m_GameClientView.SetMeTieSamePointScore(pStatusPlay->lMeTieKingScore);

			//ׯ����Ϣ
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			if ( pStatusPlay->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusPlay->cbBankerTime, pStatusPlay->lBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusPlay->wCurrentBankerChairID ), pStatusPlay->cbBankerTime, pStatusPlay->lCurrentBankerScore );
			m_GameClientView.SetBankerTreasure(pStatusPlay->lBankerTreasure);


			//��ע����
			m_GameClientView.PlaceUserJetton(ID_TIAN_MEN,pStatusPlay->lTieScore);
			m_GameClientView.PlaceUserJetton(ID_SHUN_MEN,pStatusPlay->lPlayerScore);
			m_GameClientView.PlaceUserJetton(ID_DAO_MEN,pStatusPlay->lBankerScore);
			//m_GameClientView.PlaceUserJetton(ID_ZUO_JIAO,pStatusPlay->lPlayerKingScore);
			//m_GameClientView.PlaceUserJetton(ID_YOU_JIAO,pStatusPlay->lBankerKingScore);
			//m_GameClientView.PlaceUserJetton(ID_QIAO,pStatusPlay->lTieSamePointScore);
			//��������
			PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));

			DispatchUserCard(pStatusPlay->cbTableCardArray[INDEX_BANKER],pStatusPlay->cbTableCardArray[INDEX_PLAYER1],
				pStatusPlay->cbTableCardArray[INDEX_PLAYER2],pStatusPlay->cbTableCardArray[INDEX_PLAYER3],pStatusPlay->cbTableCardArray[INDEX_PRECARD]);

			m_GameClientView.m_lKexiaScore = pStatusPlay->lCurrentBankerScore-pStatusPlay->lTieScore-pStatusPlay->lBankerScore-pStatusPlay->lPlayerScore;
			//���ð�ť
			m_GameClientView.m_btApplyBanker.EnableWindow( FALSE );
			m_GameClientView.m_btCancelBanker.EnableWindow( FALSE );

			return true;
		}
	}

	return false;
}

//��Ϸ��ʼ
bool CGameClientDlg::OnSubGameStart(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) return false;
	//��Ϣ����
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;
	//����״̬
	SetGameStatus(GS_PLAYING);
	KillGameTimer(IDI_PLACE_JETTON);
	//SetGameTimer(GetMeChairID(),IDI_SHOW_TIME,pGameStart->cbTimeLeave);
	m_GameClientView.m_bJettonstate=false;
	m_GameClientView.m_lZhuangScore=pGameStart->lBankerScore;
	m_GameClientView.m_lKexiaScore=pGameStart->lBankerScore;
	//���¿���
	UpdateButtonContron();
	DispatchUserCard(pGameStart->cbTableCardArray[INDEX_BANKER],pGameStart->cbTableCardArray[INDEX_PLAYER1],
		pGameStart->cbTableCardArray[INDEX_PLAYER2],pGameStart->cbTableCardArray[INDEX_PLAYER3],pGameStart->cbTableCardArray[INDEX_PRECARD]);
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));
	return true;
}

//�û���ע
bool CGameClientDlg::OnSubPlaceJetton(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_PlaceJetton));
	if (wDataSize!=sizeof(CMD_S_PlaceJetton)) return false;
	//��Ϣ����
	CMD_S_PlaceJetton * pPlaceJetton=(CMD_S_PlaceJetton *)pBuffer;
	m_GameClientView.m_lZhuangScore = pPlaceJetton->lZhuangSocre;
	m_GameClientView.m_lKexiaScore = pPlaceJetton->lKexiaSocre;
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("ADD_GOLD"));
	//��ע����
	m_GameClientView.PlaceUserJetton(pPlaceJetton->cbJettonArea,pPlaceJetton->lJettonScore);
	
	UpdateButtonContron();
	return true;
}

//��Ϸ����
bool CGameClientDlg::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

	//��Ϣ����
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;
	//����״̬
	SetGameStatus(GS_FREE);
	KillTimer(IDI_DISPATCH_CARD);
	KillTimer(IDI_SHOW_GAME_RESULT);
	KillTimer(IDI_CUO_POKER_TIME);
	m_GameClientView.SetDispatchCardFalg(false);

	//��¼���ŵĻ�ʤ����
	m_GameClientView.m_fWinCount[0]=pGameEnd->fShunMen;
	m_GameClientView.m_fWinCount[1]=pGameEnd->fTianMen;
	m_GameClientView.m_fWinCount[2]=pGameEnd->fDaomMen;

	//���³ɼ�
	for ( WORD wUserIndex = 0; wUserIndex < MAX_CHAIR; ++wUserIndex )
	{
		tagUserData const *pUserData = GetUserData(wUserIndex);

		if ( pUserData == NULL ) continue;
		tagApplyUser ApplyUser ;

		//������Ϣ
		ApplyUser.lUserScore = pUserData->lScore;
		ApplyUser.strUserName = pUserData->szName;
		m_GameClientView.m_ApplyUser.UpdateUser( ApplyUser );
	}

	BYTE cbPlayerPoint=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
	BYTE cbBankerPoint=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

	enOperateResult OperateResult = enOperateResult_NULL;
	if ( 0 < m_GameClientView.m_lMeCurGameScore ) OperateResult = enOperateResult_Win;
	else if ( m_GameClientView.m_lMeCurGameScore < 0 ) OperateResult = enOperateResult_Lost;
	else OperateResult = enOperateResult_NULL;

	WORD wWinnerSide;
	DeduceWinner(wWinnerSide);
	m_GameClientView.SetGameHistory(OperateResult, cbPlayerPoint, cbBankerPoint,wWinnerSide);

	//���ñ���
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore = 0L;
	m_lMeYouJiaoScore = 0L;
	m_lMeZuoJiaoScore = 0L;
	m_lMeMaxScore=pGameEnd->lMeMaxScore;
	//ׯ�ҽ��
	m_GameClientView.SetBankerTreasure(pGameEnd->lBankerTreasure);

	//״̬����
	m_bPlaying = false;

	//�����ע
	m_GameClientView.SetMeMaxScore(m_lMeMaxScore);
	m_GameClientView.SetMeTieScore(m_lMeTianMenScore);
	m_GameClientView.SetMeBankerScore(m_lMeDaoMenScore);
	m_GameClientView.SetMePlayerScore(m_lMeShunMenScore);
	m_GameClientView.SetMeBankerKingScore(m_lMeYouJiaoScore);
	m_GameClientView.SetMePlayerKingScore(m_lMeZuoJiaoScore);
	m_GameClientView.SetMeTieSamePointScore(m_lMeQiaoScore);

	//���ý���
	m_GameClientView.CleanUserJetton();
	m_GameClientView.SetWinnerSide(NULL,0xFF);

	for(int i=0;i<5;i++)
	{
		m_GameClientView.m_DrawCard[i].SetCardData(NULL,0);
	}

	m_GameClientView.SetShowGameFlag(false);
	m_strDispatchCardTips = TEXT("");
    m_GameClientView.SetDispatchCardTips(TEXT(""));

	m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

	//ׯ����Ϣ
	if ( m_wCurrentBanker != INVALID_CHAIR )
		m_GameClientView.SetBankerInfo(SwitchViewChairID(m_wCurrentBanker), pGameEnd->nBankerTime, pGameEnd->lBankerTotalScore);

	//���¿���
	UpdateButtonContron();

	//�˿���Ϣ
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbSendCount,sizeof(m_cbSendCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
	m_cbWaitPre=0;
	m_cbShowCount=0;

	m_GameClientView.m_bCanGo=false;
	m_GameClientView.m_bSet=false;
	for(int i=0;i<4;i++)
	{
		m_GameClientView.m_DrawCard[i].SetTuiPai(false);
	}
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

	KillTimer(IDI_SHOW_GAME_RESULT);
	//����ʱ��
	SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON,pGameEnd->cbTimeLeave);

	m_GameClientView.m_bJettonstate=true;
	m_GameClientView.m_lKexiaScore=pGameEnd->lBankerTreasure;
	return true;
}

//��Ϸ����
bool CGameClientDlg::OnSubGameScore(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameScore));
	if (wDataSize!=sizeof(CMD_S_GameScore)) return false;

	//��Ϣ����
	CMD_S_GameScore * pGameScore=(CMD_S_GameScore *)pBuffer;

	//��ʷ�ɼ�
	m_wDrawCount++;
	m_lMeResultCount+=pGameScore->lMeGameScore;

	//���óɼ�
	m_GameClientView.SetGameScore(pGameScore->lMeGameScore, pGameScore->lMeReturnScore, pGameScore->lBankerScore);

	m_GameClientView.SetMeTieScore(pGameScore->lMeTieScore);
	m_GameClientView.SetMeBankerScore(pGameScore->lMeBankerScore);
	m_GameClientView.SetMePlayerScore(pGameScore->lMePlayerScore);
	m_GameClientView.SetMeBankerKingScore(pGameScore->lMeBankerKingScore);
	m_GameClientView.SetMePlayerKingScore(pGameScore->lMePlayerKingScore);
	m_GameClientView.SetMeTieSamePointScore(pGameScore->lMeTieKingScore);

	//���ñ���
	m_lMeTianMenScore=pGameScore->lMeTieScore;
	m_lMeDaoMenScore=pGameScore->lMeBankerScore;
	m_lMeShunMenScore=pGameScore->lMePlayerScore;
	m_lMeQiaoScore = pGameScore->lMeTieKingScore;
	m_lMeYouJiaoScore = pGameScore->lMeBankerKingScore;
	m_lMeZuoJiaoScore = pGameScore->lMePlayerKingScore;

	return true;
}

//���¿���
void CGameClientDlg::UpdateButtonContron()
{
	if ((IsLookonMode()==false)&&(GetGameStatus()==GS_FREE) && m_wCurrentBanker != GetMeChairID() && m_wCurrentBanker != INVALID_CHAIR )
	{
		//�������
		__int64 lCurrentJetton=m_GameClientView.GetCurrentJetton();
		__int64 lLeaveScore = min(m_lMeMaxScore-m_lMeTianMenScore-m_lMeDaoMenScore-m_lMeShunMenScore, 
			m_GameClientView.m_lKexiaScore);

		//���ù��
		if (lCurrentJetton>lLeaveScore)
		{
			if (lLeaveScore>=10000000L) m_GameClientView.SetCurrentJetton(10000000L);
			else if (lLeaveScore>=5000000L) m_GameClientView.SetCurrentJetton(5000000L);
			else if (lLeaveScore>=1000000L) m_GameClientView.SetCurrentJetton(1000000L);
			else if (lLeaveScore>=500000L) m_GameClientView.SetCurrentJetton(500000L);
			else if (lLeaveScore>=100000L) m_GameClientView.SetCurrentJetton(100000L);
			else if (lLeaveScore>=10000L) m_GameClientView.SetCurrentJetton(10000L);
			else if (lLeaveScore>=1000L) m_GameClientView.SetCurrentJetton(1000L);
			
			else m_GameClientView.SetCurrentJetton(0L);
		}

		//���ư�ť
		//m_GameClientView.m_btJetton1000.EnableWindow((lLeaveScore>=1000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton10000.EnableWindow((lLeaveScore>=10000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton100000.EnableWindow((lLeaveScore>=100000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton500000.EnableWindow((lLeaveScore>=500000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton1000000.EnableWindow((lLeaveScore>=1000000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton5000000.EnableWindow((lLeaveScore>=5000000)?TRUE:FALSE);
		//m_GameClientView.m_btJetton10000000.EnableWindow((lLeaveScore>=10000000)?TRUE:FALSE);
		UINT uFlageScore[] = {1000, 10000, 100000, 500000, 1000000, 5000000, 10000000};
		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled((lLeaveScore>=uFlageScore[i])?FALSE:TRUE);
		}
	}
	else
	{
		//���ù��
		m_GameClientView.SetCurrentJetton(0L);

		//��ֹ��ť
		//m_GameClientView.m_btJetton10000000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton1000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton10000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton100000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton500000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton1000000.EnableWindow(FALSE);
		//m_GameClientView.m_btJetton5000000.EnableWindow(FALSE);
		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled(TRUE);
		}
	}

	//���밴ť
	if ( ! IsLookonMode() )
	{
		////״̬�ж�
		//if ( GetGameStatus()==GS_FREE ) 
		//{
		//	m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
		//	m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		//}
		//if ( GetGameStatus()==(GS_PLAYING+1) ) 
		//{
			m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
			m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		//}
		//else
		//{
		//	m_GameClientView.m_btCancelBanker.EnableWindow(FALSE);
		//	m_GameClientView.m_btApplyBanker.EnableWindow(FALSE);
		//}

		//��ʾ�ж�
		const tagUserData *pMeUserData = GetUserData( GetMeChairID() );
		if ( m_bMeApplyBanker )
		{
			m_GameClientView.m_btCancelBanker.ShowWindow(SW_SHOW);
			m_GameClientView.m_btApplyBanker.ShowWindow(SW_HIDE);

			bool bMeBanker = pMeUserData->wChairID == m_wCurrentBanker ? true : false;
			if ( bMeBanker ) m_GameClientView.m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_BANKER,AfxGetInstanceHandle(),false);
			else m_GameClientView.m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_APPLY,AfxGetInstanceHandle(),false);

		}
		else if ( m_lApplyBankerCondition <= pMeUserData->lScore )
		{
			m_GameClientView.m_btCancelBanker.ShowWindow(SW_HIDE);
			m_GameClientView.m_btApplyBanker.ShowWindow(SW_SHOW);
		}
	}

	return;
}

//�ɷ��˿�
bool CGameClientDlg::DispatchUserCard(BYTE cbBankerCard[],BYTE cbPlayerCard1[],BYTE cbPlayerCard2[],BYTE cbPlayerCard3[],BYTE cbPreCard[])
{
	//���ñ���
	m_cbSendCount[INDEX_PLAYER1]=0;
	m_cbSendCount[INDEX_PLAYER2]=0;
	m_cbSendCount[INDEX_PLAYER3]=0;
	m_cbSendCount[INDEX_BANKER]=0;
	m_cbWaitPre=0;

	m_cbCardCount[INDEX_PLAYER1]=2;
	m_cbCardCount[INDEX_BANKER]=2;

	CopyMemory(m_cbTableCardArray[INDEX_BANKER],cbBankerCard,sizeof(BYTE)*2);
	CopyMemory(m_cbTableCardArray[INDEX_PLAYER1],cbPlayerCard1,sizeof(BYTE)*2);
	CopyMemory(m_cbTableCardArray[INDEX_PLAYER2],cbPlayerCard2,sizeof(BYTE)*2);
	CopyMemory(m_cbTableCardArray[INDEX_PLAYER3],cbPlayerCard3,sizeof(BYTE)*2);
	CopyMemory(m_cbTableCardArray[INDEX_PRECARD],cbPreCard,sizeof(BYTE)*2);


	for(int i=0;i<5;i++)
	{
		m_GameClientView.m_DrawCard[i].SetCardData(NULL,0);
	}

	m_GameClientView.SetDispatchCardFalg(true);

	//--ʱ��
	SetTimer(IDI_DISPATCH_CARD,500,NULL);

	return true;
}

//��ʱ����Ϣ
void CGameClientDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_CUO_POKER_TIME:
		{
			for(int i=0;i<4;i++)
			{
				int t=(i+1)%4;
				m_GameClientView.m_DrawCard[t].TuiPai();
				if(m_GameClientView.m_bAutoCard)
				{
					m_GameClientView.UpdateGameView(NULL);
					if(!m_GameClientView.m_DrawCard[t].GetIsTuiPai())
						return;
				}
			}
			
			if(!m_GameClientView.m_bAutoCard && m_cbShowCount<120)
			{
				m_cbShowCount++;
				m_GameClientView.UpdateGameView(NULL);
				if(!m_GameClientView.m_DrawCard[i].GetIsTuiPai())
					return;
			}

			for(int i=0;i<4;i++)
			{
				m_GameClientView.m_DrawCard[i].SetShowHandFalse();
			}

			m_GameClientView.m_bCanGo=true;
			KillTimer(IDI_CUO_POKER_TIME);
		}
		break;
	case IDI_DISPATCH_CARD:		//�ɷ��˿�
		{
			m_GameClientView.m_DrawCard[4].ShowCard(true);
			if(m_cbWaitPre<2)
			{
				m_GameClientView.m_DrawCard[4].SetCardData(m_cbTableCardArray[4],1);
				m_GameClientView.m_DrawCard[4].IsFirstCard(true);
				m_GameClientView.UpdateGameView(NULL);
				m_cbWaitPre++;
				return;
			}
			
			for(int i=0;i<4;i++)
			{
				m_GameClientView.m_DrawCard[i].ShowCard(true);
			}
			m_GameClientView.m_DrawCard[4].ShowCard(false);
			m_GameClientView.m_DrawCard[4].IsFirstCard(false);
	
			//�����˿�
			if ((m_cbSendCount[0]+m_cbSendCount[1]+m_cbSendCount[2]+m_cbSendCount[3])<8)
			{
				//��������
				WORD wIndex=(m_cbSendCount[0]+m_cbSendCount[1]+m_cbSendCount[2]+m_cbSendCount[3]+m_GameLogic.GetCardValue(m_cbTableCardArray[4][0])-1)%4;

				//�����˿�
				m_cbSendCount[wIndex]++;
				m_GameClientView.m_DrawCard[wIndex].SetCardData(m_cbTableCardArray[wIndex],m_cbSendCount[wIndex]);

				//���½���
				m_GameClientView.UpdateGameView(NULL);

				//��������
				PlayGameSound(AfxGetInstanceHandle(),TEXT("SEND_CARD"));
				return;
			}
				
			if(!m_GameClientView.m_bCanGo)
			{
				if(!m_GameClientView.m_bSet)
				{
					m_GameClientView.m_bSet=true;
					SetTimer(IDI_CUO_POKER_TIME,60,NULL);
					SetGameStatus(GS_PLAYING+1);
					//ׯ�Ұ�ť
					m_GameClientView.m_btApplyBanker.EnableWindow( TRUE );
					m_GameClientView.m_btCancelBanker.EnableWindow( TRUE );
				}
				return;
			}

			//��ȡ�Ƶ�
			BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
			BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

			//����ʤ��
			WORD cbWinnerSide=ID_TIAN_MEN;
			DeduceWinner(cbWinnerSide);

			//ʤ���ַ�
			TCHAR szGameResult[256]=TEXT("");

			CString strCardNick;
			strCardNick.Format("ׯ��:%s   \r\n˳��:%s  \r\n����:%s  \r\n����:%s ",
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_BANKER]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER1]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER2]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER3])
				);

			m_strDispatchCardTips += szGameResult;
			m_strDispatchCardTips +=strCardNick;
			m_GameClientView.SetDispatchCardTips(m_strDispatchCardTips);
			
			//���ý���
			m_GameClientView.SetWinnerSide(szGameResult,cbWinnerSide);
			m_GameClientView.SetDispatchCardFalg(false);

			//ɾ��ʱ��
			KillTimer(IDI_DISPATCH_CARD);
			//����ʱ��
			m_nShowResultTime = 15;
			SetTimer(IDI_SHOW_GAME_RESULT, 5*1000L, NULL);
			m_GameClientView.SetShowGameFlag(true);

			//����ʣ��
			PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_END"));

			return;
		}
	case IDI_SHOW_GAME_RESULT:
		{
			m_nShowResultTime--;
			if ( m_nShowResultTime <= 0 )
			{
				KillTimer(IDI_SHOW_GAME_RESULT);
				m_GameClientView.SetShowGameFlag(false);
			}
			return;
		}
	}

	__super::OnTimer(nIDEvent);
}

//��ע��Ϣ
LRESULT CGameClientDlg::OnPlaceJetton(WPARAM wParam, LPARAM lParam)
{
	//��������
	BYTE cbJettonArea		=	(BYTE)wParam;
	__int64 lJettonScore	=	*(__int64*)lParam;

	//ׯ���ж�
	if ( GetMeChairID() == m_wCurrentBanker )
		return true;
	if ( m_wCurrentBanker == INVALID_CHAIR ) 
	{
		UpdateButtonContron();
		return true;
	}
	//���ñ���
	switch (cbJettonArea)
	{
	case ID_SHUN_MEN:
		{
			m_lMeShunMenScore += lJettonScore;
			m_GameClientView.SetMePlayerScore(m_lMeShunMenScore);
			break;
		}
	case ID_TIAN_MEN:
		{
			m_lMeTianMenScore += lJettonScore;
			m_GameClientView.SetMeTieScore(m_lMeTianMenScore);
			break;
		}
	case ID_DAO_MEN:
		{
			m_lMeDaoMenScore += lJettonScore;
			m_GameClientView.SetMeBankerScore(m_lMeDaoMenScore);
			break;
		}
	}
	//��������
	CMD_C_PlaceJetton PlaceJetton;
	ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));
	//�������
	PlaceJetton.cbJettonArea=cbJettonArea;
	PlaceJetton.lJettonScore=lJettonScore;
	//������Ϣ
	SendData(SUB_C_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));
	//���°�ť
	UpdateButtonContron();
	//����״̬
	m_bPlaying = true;
	return 0;
}

//������Ϣ
LRESULT CGameClientDlg::OnApplyBanker(WPARAM wParam, LPARAM lParam)
{
	//�Ϸ��ж�
	tagUserData const *pMeUserData = GetUserData( GetMeChairID() );
	if ( pMeUserData->lScore < m_lApplyBankerCondition ) return true;

	//�Թ��ж�
	if ( IsLookonMode() ) return true;

	//ת������
	bool bApplyBanker = wParam != 0 ? true : false;

	//��ǰ�ж�
	if ( m_wCurrentBanker == GetMeChairID() && bApplyBanker ) return true;

	CMD_C_ApplyBanker ApplyBanker;

	//��ֵ����
	ApplyBanker.bApplyBanker = bApplyBanker;

	//������Ϣ
	SendData( SUB_C_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );

	//���ð�ť
	if ( m_wCurrentBanker == GetMeChairID() && !bApplyBanker )
	{
		m_GameClientView.m_btCancelBanker.EnableWindow(FALSE);
	}

	return true;
}

//������ׯ
bool CGameClientDlg::OnUserApplyBanker(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_ApplyBanker));
	if (wDataSize!=sizeof(CMD_S_ApplyBanker)) return false;

	//��Ϣ����
	CMD_S_ApplyBanker * pApplyBanker=(CMD_S_ApplyBanker *)pBuffer;

	//�������
	if ( pApplyBanker->bApplyBanker )
	{
		tagApplyUser ApplyUser;
		ApplyUser.strUserName = pApplyBanker->szAccount;
		ApplyUser.lUserScore = pApplyBanker->lScore;

		//�����ж�
		bool bInsertApplyUser = true;

		if ( m_wCurrentBanker != INVALID_CHAIR )
		{
			tagUserData const *pBankerUserData = GetUserData(m_wCurrentBanker);
			if ( pBankerUserData != NULL && 0==lstrcmp(pBankerUserData->szName, pApplyBanker->szAccount))
				bInsertApplyUser = false;
		}

		if ( bInsertApplyUser == true ) m_GameClientView.m_ApplyUser.InserUser( ApplyUser );

		//������ť
		tagUserData const *pUserData = GetUserData( GetMeChairID() );
		if ( pUserData && !lstrcmp(pApplyBanker->szAccount, pUserData->szName ) )
		{
			m_bMeApplyBanker = true;
			UpdateButtonContron();
		}
	}
	else
	{
		tagApplyUser ApplyUser;
		ApplyUser.strUserName = pApplyBanker->szAccount;
		ApplyUser.lUserScore = pApplyBanker->lScore;
		m_GameClientView.m_ApplyUser.DeleteUser( ApplyUser );

		//������ť
		tagUserData const *pUserData = GetUserData( GetMeChairID() );
		if ( pUserData &&  !lstrcmp(pApplyBanker->szAccount, pUserData->szName ) )
		{
			m_bMeApplyBanker = false;
			
			UpdateButtonContron();
		}
	}

	return true;
}

//�л�ׯ��
bool CGameClientDlg::OnChangeBanker(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_ChangeBanker));
	if (wDataSize!=sizeof(CMD_S_ChangeBanker)) return false;

	//��Ϣ����
	CMD_S_ChangeBanker * pChangeBanker=(CMD_S_ChangeBanker *)pBuffer;

	//��ʾͼƬ
	m_GameClientView.ShowChangeBanker( m_wCurrentBanker != pChangeBanker->wChairID );

	//�Լ��ж�
	if ( m_wCurrentBanker == GetMeChairID() && IsLookonMode() == false && pChangeBanker->wChairID != GetMeChairID() ) 
	{
		m_bMeApplyBanker = false;
	}

	m_wCurrentBanker = pChangeBanker->wChairID;

	//ׯ����Ϣ
	if ( pChangeBanker->wChairID == INVALID_CHAIR )
	{
		m_GameClientView.SetBankerInfo( INVALID_CHAIR, pChangeBanker->cbBankerTime, pChangeBanker->lBankerScore );
	}
	else
	{
		m_GameClientView.SetBankerInfo( SwitchViewChairID( pChangeBanker->wChairID ), pChangeBanker->cbBankerTime, 0 );
	}
	m_GameClientView.SetBankerTreasure(pChangeBanker->lBankerTreasure);

	//ɾ�����
	if ( m_wCurrentBanker != INVALID_CHAIR )
	{
		tagUserData const *pBankerUserData = GetUserData(m_wCurrentBanker);
		if ( pBankerUserData != NULL )
		{
			tagApplyUser ApplyUser;
			ApplyUser.strUserName = pBankerUserData->szName;
			m_GameClientView.m_ApplyUser.DeleteUser( ApplyUser );
		}
	}
	
	//���½���
	UpdateButtonContron();

	return true;
}

//���»���
bool CGameClientDlg::OnChangeUserScore(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_ChangeUserScore));
	if (wDataSize!=sizeof(CMD_S_ChangeUserScore)) return false;

	//��Ϣ����
	CMD_S_ChangeUserScore * pChangeUserScore=(CMD_S_ChangeUserScore *)pBuffer;

	tagUserData const *pUserData = GetUserData( pChangeUserScore->wChairID );

	if ( pUserData )
	{
		tagApplyUser ApplyUser ;

		ApplyUser.lUserScore = pChangeUserScore->lScore;
		ApplyUser.strUserName = pUserData->szName;
		m_GameClientView.m_ApplyUser.UpdateUser( ApplyUser );
	}

	//ׯ����Ϣ
	if ( m_wCurrentBanker == pChangeUserScore->wCurrentBankerChairID )
	{
		m_GameClientView.SetBankerInfo( SwitchViewChairID( pChangeUserScore->wCurrentBankerChairID ), pChangeUserScore->cbBankerTime, pChangeUserScore->lCurrentBankerScore );

		//���½���
		UpdateButtonContron();
	}

	return true;
}

//ȡ����Ϣ
void CGameClientDlg::OnCancel()
{
	//HANDRED_GAME_QUIT_TIP;	
	__super::OnCancel();
}

//��Ϸ��¼
bool CGameClientDlg::OnSubGameRecord(const void * pBuffer, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize%sizeof(tagServerGameRecord)==0);
	if (wDataSize%sizeof(tagServerGameRecord)!=0) return false;
	
	//�������
	tagGameRecord GameRecord;
	ZeroMemory(&GameRecord,sizeof(GameRecord));

	//���ü�¼
	WORD wRecordCount=wDataSize/sizeof(tagServerGameRecord);
	for (WORD wIndex=0;wIndex<wRecordCount;wIndex++) 
	{
		tagServerGameRecord * pServerGameRecord=(((tagServerGameRecord *)pBuffer)+wIndex);

		m_GameClientView.SetGameHistory(enOperateResult_NULL, pServerGameRecord->cbPlayerCount, pServerGameRecord->cbBankerCount,pServerGameRecord->wWinner);
	}

	return true;
}

//������ʾ
void CGameClientDlg::SetDispatchCardTips()
{
	//�������
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],2);
	BYTE cbPlayerTwoCardCount = m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],2);

	//�мҲ���
	BYTE cbPlayerThirdCardValue = 0 ;	//�������Ƶ���
	if(cbPlayerTwoCardCount<=5 && cbBankerCount<8)
	{
		//�������
		cbPlayerThirdCardValue = m_GameLogic.GetCardPip(m_cbTableCardArray[INDEX_PLAYER1][2]);
		CString strTips;
		strTips.Format(TEXT("��%d�㣬ׯ%d�㣬�м�������\n"), cbPlayerTwoCardCount, cbBankerCount);
		m_strDispatchCardTips = strTips;
		m_GameClientView.SetDispatchCardTips(m_strDispatchCardTips);
	}

	return ;
}


//�ƶ�Ӯ��
void CGameClientDlg::DeduceWinner(WORD &cbWinner)
{
	bool bTongdian=false;
	cbWinner = 0;
	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER1],2,bTongdian))
	{
		cbWinner = (cbWinner & ~ID_SHUN_MEN);
	}
	else
	{
		cbWinner|=ID_SHUN_MEN;
	}

	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER2],2,bTongdian))
	{
		cbWinner = (cbWinner & ~ID_TIAN_MEN);
	}
	else
	{
		cbWinner |=ID_TIAN_MEN;
	}
	if(m_GameLogic.CompareCard(m_cbTableCardArray[INDEX_BANKER],m_cbTableCardArray[INDEX_PLAYER3],2,bTongdian))
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

LRESULT CGameClientDlg::OnCuoPai(WPARAM wParam, LPARAM lParam)
{

	tagUserData const *pMeUserData = GetUserData( GetMeChairID() );
	if ( pMeUserData != NULL && pMeUserData->cbUserStatus == US_PLAY)
	{
		InsertShtickString("��ϵͳ��ʾ����Ϸ�в����л�����ģʽ��",RGB(255,0,0),true);
		return true;
	}
	if(m_GameClientView.m_bAutoCard)
	{
		m_GameClientView.m_btnShouDongCuoPai.ShowWindow(SW_HIDE);
		m_GameClientView.m_btnZiDongCuoPai.ShowWindow(SW_SHOW);
		m_GameClientView.m_bAutoCard=false;
		InsertShtickString("��ϵͳ��ʾ����ǰΪ�ֹ�����ģʽ��",RGB(255,0,0),true);

	}
	else
	{
		m_GameClientView.m_btnShouDongCuoPai.ShowWindow(SW_SHOW);
		m_GameClientView.m_btnZiDongCuoPai.ShowWindow(SW_HIDE);
		m_GameClientView.m_bAutoCard=true;
		InsertShtickString("��ϵͳ��ʾ����ǰΪ�Զ�����ģʽ��",RGB(255,0,0),true);
	}
	return true;
}

LRESULT CGameClientDlg::OnBank(WPARAM wParam, LPARAM lParam)
{
	UserOnBankBT();
	return true;
}

