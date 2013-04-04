#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"

//////////////////////////////////////////////////////////////////////////

//ʱ���ʶ
#define IDI_PLACE_JETTON			100									//��עʱ��
#define IDI_OTHER_TIME				101									//��עʱ��

#define IDI_PLAY_ANIMAL				301									//����ʱ��
#define IDI_SHOW_GAME_RESULT		302									//��ʾ���

#define IDI_RAND_ANIMAL				401									//�����ͼ

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientDlg, CGameFrameDlg)
	ON_WM_TIMER()
	ON_MESSAGE(IDM_PLACE_JETTON,OnPlaceJetton)
	ON_MESSAGE(IDM_APPLY_BANKER, OnApplyBanker)
	ON_MESSAGE(IDM_ONBANK,OnBank)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientDlg::CGameClientDlg() : CGameFrameDlg(&m_GameClientView)
{
	m_lCellScore=0;
	//��ע��Ϣ
	m_lMeMaxScore=0L;

	m_lMeBigTigerScore=0L;
	m_lMeSmlTigerScore=0L;
	m_lMeBigBogScore=0L;
	m_lMeSmlBogScore=0L;
	m_lMeBigHorseScore=0L;
	m_lMeSmlHorseScore=0L;
	m_lMeBigSnakeScore=0L;
	m_lMeSmlSnakeScore=0L;

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bPlaying = false;
	m_lBeginTime=0;
	m_lTotalTime=0;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
	m_bMeApplyBanker = false;

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
	SetWindowText(TEXT("�������"));

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

	m_lMeBigTigerScore=0L;
	m_lMeSmlTigerScore=0L;
	m_lMeBigBogScore=0L;
	m_lMeSmlBogScore=0L;
	m_lMeBigHorseScore=0L;
	m_lMeSmlHorseScore=0L;
	m_lMeBigSnakeScore=0L;
	m_lMeSmlSnakeScore=0L;

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bPlaying = false;
	m_bMeApplyBanker = false;
	m_lBeginTime=0;
	m_lTotalTime=0;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;

	//�˿���Ϣ
	m_GameClientView.m_cbAnimalBox=0;
	m_GameClientView.m_cbNowAnimalBox=0;

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
		m_GameClientView.m_btJetton100.EnableWindow(FALSE);
		m_GameClientView.m_btJetton1000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton10000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton100000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton1000000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton5000000.EnableWindow(FALSE);

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

			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusFree->lApplyBankerCondition;			

			//����λ��
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//�����ע
			m_GameClientView.SetMeMaxScore(pStatusFree->lMeMaxScore);
			
			m_GameClientView.SetMeBigTigerScore(pStatusFree->lMeBigTigerScore);
			m_GameClientView.SetMeSmlTigerScore(pStatusFree->lMeSmlTigerScore);
			m_GameClientView.SetMeBigDogScore(pStatusFree->lMeBigBogScore);
			m_GameClientView.SetMeSmlDogScore(pStatusFree->lMeSmlBogScore);
			m_GameClientView.SetMeBigHorseScore(pStatusFree->lMeBigHorseScore);
			m_GameClientView.SetMeSmlHorseScore(pStatusFree->lMeSmlHorseScore);
			m_GameClientView.SetMeBigSnakeScore(pStatusFree->lMeBigSnakeScore);
			m_GameClientView.SetMeSmlSnakeScore(pStatusFree->lMeSmlSnakeScore);

			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;

			m_lCellScore=pStatusFree->lCellScore;
			//���ñ���
			m_lMeMaxScore= pStatusFree->lMeMaxScore;

			m_lMeBigTigerScore	= pStatusFree->lMeBigTigerScore;
			m_lMeSmlTigerScore	= pStatusFree->lMeSmlTigerScore;
			m_lMeBigBogScore	= pStatusFree->lMeBigBogScore;
			m_lMeSmlBogScore	= pStatusFree->lMeSmlBogScore;
			m_lMeBigHorseScore	= pStatusFree->lMeBigHorseScore;
			m_lMeSmlHorseScore	= pStatusFree->lMeSmlHorseScore;
			m_lMeBigSnakeScore	= pStatusFree->lMeBigSnakeScore;
			m_lMeSmlSnakeScore	= pStatusFree->lMeSmlSnakeScore;

			//ׯ����Ϣ
			if ( pStatusFree->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusFree->cbBankerTime, pStatusFree->lCurrentBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusFree->wCurrentBankerChairID ), pStatusFree->cbBankerTime, pStatusFree->lCurrentBankerScore );
			
			m_GameClientView.SetBankerTreasure(pStatusFree->lBankerTreasure);

			//��ע����
			m_GameClientView.PlaceUserJetton(ID_BIG_TIGER,pStatusFree->lBigTigerScore);
			m_GameClientView.PlaceUserJetton(ID_SML_TIGER,pStatusFree->lSmlTigerScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_DOG,pStatusFree->lBigBogScore);
			m_GameClientView.PlaceUserJetton(ID_SML_DOG,pStatusFree->lSmlBogScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_HORSE,pStatusFree->lBigHorseScore);
			m_GameClientView.PlaceUserJetton(ID_SML_HORSE,pStatusFree->lSmlHorseScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_SNAKE,pStatusFree->lBigSnakeScore);
			m_GameClientView.PlaceUserJetton(ID_SML_SNAKE,pStatusFree->lSmlSnakeScore);

			//���¿���
			UpdateButtonContron();

			//��������
			PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

			//����ʱ��
			SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON, pStatusFree->cbTimeLeave);
			m_GameClientView.m_bShowKXF=true;
			SetTimer(IDI_RAND_ANIMAL, 250, NULL);
			
			return true;
		}
	case GS_PLAYING:		//��Ϸ״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusPlay));
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;

			//��Ϣ����
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusPlay->lApplyBankerCondition;

			m_lCellScore=pStatusPlay->lCellScore;
			//���ñ���
			m_lMeMaxScore=pStatusPlay->lMeMaxScore;

			m_lMeBigTigerScore	=	pStatusPlay->lMeBigTigerScore;
			m_lMeSmlTigerScore	=	pStatusPlay->lMeSmlTigerScore;
			m_lMeBigBogScore	=	pStatusPlay->lMeBigBogScore;
			m_lMeSmlBogScore	=	pStatusPlay->lMeSmlBogScore;
			m_lMeBigHorseScore  =	pStatusPlay->lMeBigHorseScore;
			m_lMeSmlHorseScore  =	pStatusPlay->lMeSmlHorseScore;
			m_lMeBigSnakeScore  =	pStatusPlay->lMeBigSnakeScore;
			m_lMeSmlSnakeScore  =	pStatusPlay->lMeSmlSnakeScore;

			//����λ��
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//�����ע
			m_GameClientView.SetMeMaxScore(pStatusPlay->lMeMaxScore);

			m_GameClientView.SetMeBigTigerScore(pStatusPlay->lMeBigTigerScore);
			m_GameClientView.SetMeSmlTigerScore(pStatusPlay->lMeSmlTigerScore);
			m_GameClientView.SetMeBigDogScore(pStatusPlay->lMeBigBogScore);
			m_GameClientView.SetMeSmlDogScore(pStatusPlay->lMeSmlBogScore);
			m_GameClientView.SetMeBigHorseScore(pStatusPlay->lMeBigHorseScore);
			m_GameClientView.SetMeSmlHorseScore(pStatusPlay->lMeSmlHorseScore);
			m_GameClientView.SetMeBigSnakeScore(pStatusPlay->lMeBigSnakeScore);
			m_GameClientView.SetMeSmlSnakeScore(pStatusPlay->lMeSmlSnakeScore);

			//ׯ����Ϣ
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			
			if ( pStatusPlay->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusPlay->cbBankerTime, pStatusPlay->lCurrentBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusPlay->wCurrentBankerChairID ), pStatusPlay->cbBankerTime, pStatusPlay->lCurrentBankerScore );
			
			m_GameClientView.SetBankerTreasure(pStatusPlay->lBankerTreasure);

			//��ע����
			m_GameClientView.PlaceUserJetton(ID_BIG_TIGER,pStatusPlay->lBigTigerScore);
			m_GameClientView.PlaceUserJetton(ID_SML_TIGER,pStatusPlay->lSmlTigerScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_DOG,pStatusPlay->lBigBogScore);
			m_GameClientView.PlaceUserJetton(ID_SML_DOG,pStatusPlay->lSmlBogScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_HORSE,pStatusPlay->lBigHorseScore);
			m_GameClientView.PlaceUserJetton(ID_SML_HORSE,pStatusPlay->lSmlHorseScore);
			m_GameClientView.PlaceUserJetton(ID_BIG_SNAKE,pStatusPlay->lBigSnakeScore);
			m_GameClientView.PlaceUserJetton(ID_SML_SNAKE,pStatusPlay->lSmlSnakeScore);

			//��������
			PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));

			//�����˿�
			DispatchUserCard(pStatusPlay->cbAnimalBox);

			//���ð�ť
			m_GameClientView.m_btApplyBanker.EnableWindow( FALSE );
			m_GameClientView.m_btCancelBanker.EnableWindow( FALSE );

			//����ʱ��
			SetGameTimer(GetMeChairID(), IDI_OTHER_TIME, pStatusPlay->cbTimeLeave);
			return true;
		}
	}

	return false;
}

//ˢ����
bool CGameClientDlg::UpdateView()
{
	UpdateButtonContron();
	return true;
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
	m_GameClientView.m_bShowKXF=false;
	KillGameTimer(IDI_PLACE_JETTON);

	//���¿���
	UpdateButtonContron();

	//�ɷ��˿�
	DispatchUserCard(pGameStart->cbAnimalBox);

	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));

	SetGameTimer(GetMeChairID(), IDI_OTHER_TIME, pGameStart->cbTimeLeave);

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

	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("ADD_GOLD"));

	//��ע����
	m_GameClientView.PlaceUserJetton(pPlaceJetton->cbJettonArea, pPlaceJetton->lJettonScore);

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
	m_GameClientView.m_bShowKXF=true;
	SetTimer(IDI_RAND_ANIMAL, 250, NULL);

	KillTimer(IDI_PLAY_ANIMAL);
	KillTimer(IDI_SHOW_GAME_RESULT);
	m_GameClientView.SetPlayAnimalFalg(false);

	//���ñ���
	m_lMeBigTigerScore=0L;
	m_lMeSmlTigerScore=0L;
	m_lMeBigBogScore=0L;
	m_lMeSmlBogScore=0L;
	m_lMeBigHorseScore=0L;
	m_lMeSmlHorseScore=0L;
	m_lMeBigSnakeScore=0L;
	m_lMeSmlSnakeScore=0L;

	m_lMeMaxScore=pGameEnd->lMeMaxScore;
	m_lCellScore=pGameEnd->lCellScore;

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

	BYTE cbWinner=DeduceWinner();

	enOperateResult OperateResult = enOperateResult_NULL;
	if ( 0 < m_GameClientView.m_lMeCurGameScore )
		OperateResult = enOperateResult_Win;
	else if ( m_GameClientView.m_lMeCurGameScore < 0 )
		OperateResult = enOperateResult_Lost;
	else
		OperateResult = enOperateResult_NULL;

	m_GameClientView.SetGameHistory(OperateResult, cbWinner);

	//ׯ�ҽ��
	m_GameClientView.SetBankerTreasure(pGameEnd->lBankerTreasure);

	//״̬����
	m_bPlaying = false;

	//�����ע
	m_GameClientView.SetMeMaxScore(m_lMeMaxScore);

	m_GameClientView.SetMeBigTigerScore(m_lMeBigTigerScore);
	m_GameClientView.SetMeSmlTigerScore(m_lMeSmlTigerScore);
	m_GameClientView.SetMeBigDogScore(m_lMeBigBogScore);
	m_GameClientView.SetMeSmlDogScore(m_lMeSmlBogScore);
	m_GameClientView.SetMeBigHorseScore(m_lMeBigHorseScore);
	m_GameClientView.SetMeSmlHorseScore(m_lMeSmlHorseScore);
	m_GameClientView.SetMeBigSnakeScore(m_lMeBigSnakeScore);
	m_GameClientView.SetMeSmlSnakeScore(m_lMeSmlSnakeScore);

	//���ý���
	m_GameClientView.CleanUserJetton();
	m_GameClientView.SetWinnerSide(0xFF);

	KillTimer(IDI_SHOW_GAME_RESULT);
	m_GameClientView.SetShowGameFlag(false);
	m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

	//ׯ����Ϣ
	if ( m_wCurrentBanker != INVALID_CHAIR )
		m_GameClientView.SetBankerInfo(SwitchViewChairID(m_wCurrentBanker), pGameEnd->nBankerTime, pGameEnd->lBankerTotalScore);

	//���¿���
	UpdateButtonContron();

	//�˿���Ϣ
	m_GameClientView.m_cbAnimalBox=0;
	m_GameClientView.m_cbNowAnimalBox=0;

	m_lBeginTime=0;
	m_lTotalTime=0;

	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

	//����ʱ��
	SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON,pGameEnd->cbTimeLeave);

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
	m_GameClientView.SetGameScore(pGameScore->lMeGameScore, pGameScore->lMeReturnScore, pGameScore->lBankerWinScore);


	m_GameClientView.SetMeBigTigerScore(pGameScore->lMeBigTigerScore);
	m_GameClientView.SetMeSmlTigerScore(pGameScore->lMeSmlTigerScore);
	m_GameClientView.SetMeBigDogScore(pGameScore->lMeBigBogScore);
	m_GameClientView.SetMeSmlDogScore(pGameScore->lMeSmlBogScore);
	m_GameClientView.SetMeBigHorseScore(pGameScore->lMeBigHorseScore);
	m_GameClientView.SetMeSmlHorseScore(pGameScore->lMeSmlHorseScore);
	m_GameClientView.SetMeBigSnakeScore(pGameScore->lMeBigSnakeScore);
	m_GameClientView.SetMeSmlSnakeScore(pGameScore->lMeSmlSnakeScore);

	//���ñ���
	m_lMeBigTigerScore=pGameScore->lMeBigTigerScore;
	m_lMeSmlTigerScore=pGameScore->lMeSmlTigerScore;
	m_lMeBigBogScore=pGameScore->lMeBigBogScore;
	m_lMeSmlBogScore=pGameScore->lMeSmlBogScore;
	m_lMeBigHorseScore=pGameScore->lMeBigHorseScore;
	m_lMeSmlHorseScore=pGameScore->lMeSmlHorseScore;
	m_lMeBigSnakeScore=pGameScore->lMeBigSnakeScore;
	m_lMeSmlSnakeScore=pGameScore->lMeSmlSnakeScore;

	return true;
}

//���¿���
void CGameClientDlg::UpdateButtonContron()
{
	if ((IsLookonMode()==false)&&(GetGameStatus()==GS_FREE) && m_wCurrentBanker != GetMeChairID() && m_wCurrentBanker != INVALID_CHAIR )
	{
		//�õ�ׯ����Ϣ
		const tagUserData* pBankerInfo = m_GameClientView.GetUserInfo(m_GameClientView.m_wCurrentBankerChairID);
		if(pBankerInfo==NULL)
			return;
		//�õ��Լ���Ϣ
		const tagUserData* pMeInfo = m_GameClientView.GetUserInfo(m_GameClientView.m_wMeChairID);
		if(pMeInfo == NULL)
			return;
		//�������
		__int64 lCurrentJetton=m_GameClientView.GetCurrentJetton();
		__int64 lLeaveScore=pMeInfo->lScore;

		lLeaveScore-=m_lMeBigTigerScore;					//�������ע
		lLeaveScore-=m_lMeSmlTigerScore;					//����С����ע
		lLeaveScore-=m_lMeBigBogScore;						//�������ע
		lLeaveScore-=m_lMeSmlBogScore;						//�������ע
		lLeaveScore-=m_lMeBigHorseScore;					//���������ע
		lLeaveScore-=m_lMeSmlHorseScore;					//����С����ע
		lLeaveScore-=m_lMeBigSnakeScore;					//���������ע
		lLeaveScore-=m_lMeSmlSnakeScore;					//����С����ע
		
		__int64 uCurrntReamtionScore = pBankerInfo->lScore - m_GameClientView.CalcAllJetton();
		lLeaveScore=min(lLeaveScore, uCurrntReamtionScore);
		//���ù��
		if (lCurrentJetton>lLeaveScore)
		{
			if (lLeaveScore>=5000000L) m_GameClientView.SetCurrentJetton(5000000L);
			else if (lLeaveScore>=1000000L) m_GameClientView.SetCurrentJetton(1000000L);
			else if (lLeaveScore>=500000L)  m_GameClientView.SetCurrentJetton(500000L);
			else if (lLeaveScore>=100000L)  m_GameClientView.SetCurrentJetton(100000L);
			else if (lLeaveScore>=10000L)   m_GameClientView.SetCurrentJetton(10000L);
			else if (lLeaveScore>=1000L)    m_GameClientView.SetCurrentJetton(1000L);
			else if (lLeaveScore>=100L)     m_GameClientView.SetCurrentJetton(100L);
			else m_GameClientView.SetCurrentJetton(0L);
		}

		//���ư�ť
		m_GameClientView.m_btJetton100.EnableWindow((lLeaveScore>=100)?TRUE:FALSE);
		m_GameClientView.m_btJetton1000.EnableWindow((lLeaveScore>=1000)?TRUE:FALSE);
		m_GameClientView.m_btJetton10000.EnableWindow((lLeaveScore>=10000)?TRUE:FALSE);
		m_GameClientView.m_btJetton100000.EnableWindow((lLeaveScore>=100000)?TRUE:FALSE);
		m_GameClientView.m_btJetton1000000.EnableWindow((lLeaveScore>=1000000)?TRUE:FALSE);
		m_GameClientView.m_btJetton5000000.EnableWindow((lLeaveScore>=5000000)?TRUE:FALSE);	

	}
	else
	{
		//���ù��
		m_GameClientView.SetCurrentJetton(0L);

		//��ֹ��ť
		m_GameClientView.m_btJetton100.EnableWindow(FALSE);
		m_GameClientView.m_btJetton1000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton10000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton100000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton1000000.EnableWindow(FALSE);
		m_GameClientView.m_btJetton5000000.EnableWindow(FALSE);;
	}

	//���밴ť
	if ( ! IsLookonMode() )
	{
		//״̬�ж�
		if ( GetGameStatus()==GS_FREE ) 
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
			m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		}
		else if ( GetGameStatus()==GS_SHOW_RESULT ) 
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
			m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		}
		else
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(FALSE);
			m_GameClientView.m_btApplyBanker.EnableWindow(FALSE);
		}

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
bool CGameClientDlg::DispatchUserCard(BYTE cbAnimalBox)
{
	//���ý���
	m_GameClientView.m_cbAnimalBox=cbAnimalBox;
	m_GameClientView.m_cbNowAnimalBox=0;

	m_GameClientView.SetPlayAnimalFalg(true);

	//���ö�ʱ��
	m_lBeginTime=::GetTickCount();
	m_lTotalTime=cbAnimalBox*ANIMAL_ROLL_SPEED*2;

	SetTimer(IDI_PLAY_ANIMAL, 50, NULL);

	return true;
}

//��ʱ����Ϣ
void CGameClientDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_PLAY_ANIMAL:		//�ɷ��˿�
		{
			__int64 dwSub=::GetTickCount()-m_lBeginTime;
			__int64 half = m_lTotalTime/2;
			__int64 halfhalf = m_lTotalTime/4;

			__int64 cbNew=0;
			if ( dwSub < halfhalf )
			{
				cbNew=(dwSub*dwSub*dwSub)*(m_GameClientView.m_cbAnimalBox/3)/(halfhalf*halfhalf*halfhalf);
			}
			else if (dwSub >= halfhalf && dwSub < half)
			{
				__int64 unOver=(half - dwSub);
				cbNew=m_GameClientView.m_cbAnimalBox * 2 / 3;
				cbNew -= (unOver*unOver*unOver)*(m_GameClientView.m_cbAnimalBox/3)/(half*half*half);
			}
			else if ( dwSub >= half && dwSub <= m_lTotalTime)
			{
				__int64 unOver = (m_lTotalTime-dwSub);
				cbNew = m_GameClientView.m_cbAnimalBox;
				cbNew -= (unOver*unOver*unOver)*(m_GameClientView.m_cbAnimalBox/3)/(half*half*half);
			}
			else
				cbNew=m_GameClientView.m_cbAnimalBox;

			if ( m_GameClientView.m_cbNowAnimalBox!=cbNew )
			{
				m_GameClientView.m_cbNowAnimalBox=cbNew;
				m_GameClientView.UpdateGameView(NULL);
				PlayGameSound(AfxGetInstanceHandle(),TEXT("SEND_CARD"));
			}

			if ( dwSub<(m_lTotalTime+2*ANIMAL_ROLL_SPEED) )
				return;

			//����ʤ��
			BYTE cbWinnerSide=DeduceWinner();

			//���ý���
			m_GameClientView.SetWinnerSide(cbWinnerSide);
			m_GameClientView.SetPlayAnimalFalg(false);

			//ɾ��ʱ��
			KillTimer(IDI_PLAY_ANIMAL);

			//����ʱ��
			m_nShowResultTime = 5;
			SetTimer(IDI_SHOW_GAME_RESULT, 1000, NULL);
			m_GameClientView.SetShowGameFlag(true);
			m_lBeginTime=0;
			m_lTotalTime=0;
			
			SetGameStatus(GS_SHOW_RESULT);
			//ׯ�Ұ�ť
			m_GameClientView.m_btApplyBanker.EnableWindow( TRUE );
			m_GameClientView.m_btCancelBanker.EnableWindow( TRUE );

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
	case IDI_RAND_ANIMAL:
		{
			if (false == m_GameClientView.m_bShowKXF)
			{
				KillTimer(IDI_RAND_ANIMAL);
			}
			m_GameClientView.UpdateGameView(NULL);
			return;
		}
	}

	__super::OnTimer(nIDEvent);
}

//��ע��Ϣ
LRESULT CGameClientDlg::OnPlaceJetton(WPARAM wParam, LPARAM lParam)
{
	//��������
	BYTE cbJettonArea=(BYTE)wParam;
	__int64 lJettonScore=*(__int64*)lParam;

	//ׯ���ж�
	if ( GetMeChairID() == m_wCurrentBanker ) 
		return true;

	if ( m_wCurrentBanker == INVALID_CHAIR ) 
	{
		UpdateButtonContron();
		return true;
	}

	//���ñ���
	switch ( cbJettonArea )
	{
	case ID_BIG_TIGER:
		{
			m_lMeBigTigerScore += lJettonScore;
			m_GameClientView.SetMeBigTigerScore(m_lMeBigTigerScore);
			break;
		}
	case ID_SML_TIGER:
		{
			m_lMeSmlTigerScore += lJettonScore;
			m_GameClientView.SetMeSmlTigerScore(m_lMeSmlTigerScore);
			break;
		}
	case ID_BIG_DOG:
		{
			m_lMeBigBogScore += lJettonScore;
			m_GameClientView.SetMeBigDogScore(m_lMeBigBogScore);
			break;
		}
	case ID_SML_DOG:
		{
			m_lMeSmlBogScore += lJettonScore;
			m_GameClientView.SetMeSmlDogScore(m_lMeSmlBogScore);
			break;
		}
	case ID_BIG_HORSE:
		{
			m_lMeBigHorseScore += lJettonScore;
			m_GameClientView.SetMeBigHorseScore(m_lMeBigHorseScore);
			break;
		}
	case ID_SML_HORSE:
		{
			m_lMeSmlHorseScore += lJettonScore;
			m_GameClientView.SetMeSmlHorseScore(m_lMeSmlHorseScore);
			break;
		}
	case ID_BIG_SNAKE:
		{
			m_lMeBigSnakeScore += lJettonScore;
			m_GameClientView.SetMeBigSnakeScore(m_lMeBigSnakeScore);
			break;
		}
	case ID_SML_SNAKE:
		{
			m_lMeSmlSnakeScore += lJettonScore;
			m_GameClientView.SetMeSmlSnakeScore(m_lMeSmlSnakeScore);
			break;
		}
	}

	//��������
	CMD_C_PlaceJetton PlaceJetton;
	ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));
	PlaceJetton.cbJettonArea=cbJettonArea;
	PlaceJetton.lJettonScore=lJettonScore;

	//������Ϣ
	SendData(SUB_C_PLACE_JETTON, &PlaceJetton, sizeof(PlaceJetton));

	UpdateButtonContron();

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
		m_GameClientView.SetBankerInfo( INVALID_CHAIR, pChangeBanker->cbBankerTime, pChangeBanker->lBankerWinScore );
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
		m_GameClientView.SetGameHistory(enOperateResult_NULL, pServerGameRecord->cbWinner );
	}

	return true;
}

//�ƶ�Ӯ��
BYTE CGameClientDlg::DeduceWinner()
{
	return s_arJettonArea[m_GameClientView.m_cbAnimalBox%MAX_ANIMAL_COUNT];
}

LRESULT CGameClientDlg::OnBank(WPARAM wParam, LPARAM lParam)
{
	UserOnBankBT(2);
	return 0;
}


