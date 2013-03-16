#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"


//时间标识
#define IDI_PLACE_JETTON			100									//下注时间
#define IDI_DISPATCH_CARD			301									//发牌时间
#define IDI_SHOW_GAME_RESULT		302									//显示结果
#define IDI_SHOW_TIME				303
#define IDI_CUO_POKER_TIME			304									//搓牌时间

BEGIN_MESSAGE_MAP(CGameClientDlg, CGameFrameDlg)
	ON_WM_TIMER()
	ON_MESSAGE(IDM_PLACE_JETTON,OnPlaceJetton)
	ON_MESSAGE(IDM_APPLY_BANKER, OnApplyBanker)
	ON_MESSAGE(IDM_CUOPAI,OnCuoPai)
	ON_MESSAGE(IDM_ONBANK,OnBank)
END_MESSAGE_MAP()

//构造函数
CGameClientDlg::CGameClientDlg() : CGameFrameDlg(&m_GameClientView)
{
	m_lCellScore=0;
	//下注信息
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	m_strDispatchCardTips = TEXT("");

	//历史信息
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//状态变量
	m_bPlaying = false;

	//扑克信息
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbSendCount,sizeof(m_cbSendCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
	m_cbWaitPre=0;

	//庄家信息
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
	m_bMeApplyBanker = false;
	m_cbShowCount=0;
	return;
}

//析构函数
CGameClientDlg::~CGameClientDlg()
{
}

//初始函数
bool CGameClientDlg::InitGameFrame()
{
	//设置标题
	SetWindowText(TEXT("牌九"));

	//设置图标
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	return true;
}

//重置框架
void CGameClientDlg::ResetGameFrame()
{
	//下注信息
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;
	
	m_strDispatchCardTips = TEXT("");
    
	//历史信息
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//状态变量
	m_bPlaying = false;
	m_bMeApplyBanker = false;

	//庄家信息
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;

	//扑克信息
	ZeroMemory(m_cbCardCount,sizeof(m_cbCardCount));
	ZeroMemory(m_cbSendCount,sizeof(m_cbSendCount));
	ZeroMemory(m_cbTableCardArray,sizeof(m_cbTableCardArray));
	m_cbWaitPre=0;

	m_cbShowCount=0;
	return;
}

//游戏设置
void CGameClientDlg::OnGameOptionSet()
{
	return;
}

//时间消息
bool CGameClientDlg::OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID)
{
	if ((nTimerID==IDI_PLACE_JETTON)&&(nElapse==0))
	{
		//设置光标
		m_GameClientView.SetCurrentJetton(0L);

		//禁止按钮
		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled(TRUE);
		}
		//庄家按钮
		m_GameClientView.m_btApplyBanker.EnableWindow( FALSE );
		m_GameClientView.m_btCancelBanker.EnableWindow( FALSE );

		//播放声音
		PlayGameSound(AfxGetInstanceHandle(),TEXT("STOP_JETTON"));
	}

	return true;
}

//旁观状态
void CGameClientDlg::OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize)
{
}

//网络消息
bool CGameClientDlg::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//游戏开始
		{
			return OnSubGameStart(pBuffer,wDataSize);
		}
	case SUB_S_PLACE_JETTON:	//用户加注
		{
			return OnSubPlaceJetton(pBuffer,wDataSize);
		}
	case SUB_S_APPLY_BANKER:	//申请做庄
		{
			return OnUserApplyBanker( pBuffer, wDataSize );
		}
	case SUB_S_CHANGE_BANKER:	//切换庄家
		{
			return OnChangeBanker( pBuffer, wDataSize );
		}
	case SUB_S_CHANGE_USER_SCORE://更新积分
		{
			return OnChangeUserScore( pBuffer, wDataSize );
		}
	case SUB_S_GAME_END:		//游戏结束
		{
			return OnSubGameEnd(pBuffer,wDataSize);
		}
	case SUB_S_SEND_RECORD:		//游戏记录
		{
			return OnSubGameRecord(pBuffer,wDataSize);
		}
	case SUB_S_GAME_SCORE:		//游戏积分
		{
			return OnSubGameScore(pBuffer, wDataSize);
		}
	}

	//错误断言
	ASSERT(FALSE);

	return true;
}

//游戏场景
bool CGameClientDlg::OnGameSceneMessage(BYTE cbGameStation, bool bLookonOther, const void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE:			//空闲状态
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_StatusFree));
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;

			//消息处理
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;

			//庄家变量
			m_lApplyBankerCondition = pStatusFree->lApplyBankerCondition;			

			//设置位置
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//玩家下注
			m_GameClientView.SetMeMaxScore(pStatusFree->lMeMaxScore);
			m_GameClientView.SetMeTieScore(pStatusFree->lMeTieScore);
			m_GameClientView.SetMeBankerScore(pStatusFree->lMeBankerScore);
			m_GameClientView.SetMePlayerScore(pStatusFree->lMePlayerScore);
			m_GameClientView.SetMeBankerKingScore(pStatusFree->lMeBankerKingScore);
			m_GameClientView.SetMePlayerKingScore(pStatusFree->lMePlayerKingScore);
			m_GameClientView.SetMeTieSamePointScore(pStatusFree->lMeTieKingScore);

			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;

			m_lCellScore=pStatusFree->lCellScore;
			//设置变量
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			m_lMeTianMenScore=pStatusFree->lMeTieScore;
			m_lMeDaoMenScore=pStatusFree->lMeBankerScore;
			m_lMeShunMenScore=pStatusFree->lMePlayerScore;
			m_lMeQiaoScore = pStatusFree->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusFree->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusFree->lMePlayerKingScore;

			//庄家信息
			if ( pStatusFree->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusFree->cbBankerTime, pStatusFree->lBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusFree->wCurrentBankerChairID ), pStatusFree->cbBankerTime, pStatusFree->lBankerScore );
			m_GameClientView.SetBankerTreasure(pStatusFree->lBankerTreasure);

			//下注界面
			m_GameClientView.PlaceUserJetton(ID_TIAN_MEN,pStatusFree->lTieScore);
			m_GameClientView.PlaceUserJetton(ID_QIAO,pStatusFree->lTieSamePointScore);
			m_GameClientView.PlaceUserJetton(ID_SHUN_MEN,pStatusFree->lPlayerScore);
			m_GameClientView.PlaceUserJetton(ID_ZUO_JIAO,pStatusFree->lPlayerKingScore);
			m_GameClientView.PlaceUserJetton(ID_DAO_MEN,pStatusFree->lBankerScore);
			m_GameClientView.PlaceUserJetton(ID_YOU_JIAO,pStatusFree->lBankerKingScore);

			//更新控制
			UpdateButtonContron();

			//播放声音
			PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

			//设置时间
			SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON,pStatusFree->cbTimeLeave);

			return true;
		}
	case GS_PLAYING:		//游戏状态
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_StatusPlay));
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;

			//消息处理
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			//庄家变量
			m_lApplyBankerCondition = pStatusPlay->lApplyBankerCondition;

			m_lCellScore=pStatusPlay->lCellScore;
			//设置变量
			m_lMeMaxScore=pStatusPlay->lMeMaxScore ;
			m_lMeTianMenScore=pStatusPlay->lMeTieScore;
			m_lMeDaoMenScore=pStatusPlay->lMeBankerScore;
			m_lMeShunMenScore=pStatusPlay->lMePlayerScore;
			m_lMeQiaoScore = pStatusPlay->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusPlay->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusPlay->lMePlayerKingScore;

			//设置位置
			WORD wMeChairID=GetMeChairID();
			m_GameClientView.SetMeChairID(SwitchViewChairID(wMeChairID));
			m_GameClientView.SetHistoryScore(m_wDrawCount,m_lMeResultCount);

			//玩家下注
			m_GameClientView.SetMeMaxScore(pStatusPlay->lMeMaxScore);	
			m_GameClientView.SetMeTieScore(pStatusPlay->lMeTieScore);
			m_GameClientView.SetMeBankerScore(pStatusPlay->lMeBankerScore);
			m_GameClientView.SetMePlayerScore(pStatusPlay->lMePlayerScore);
			m_GameClientView.SetMeBankerKingScore(pStatusPlay->lMeBankerKingScore);
			m_GameClientView.SetMePlayerKingScore(pStatusPlay->lMePlayerKingScore);
			m_GameClientView.SetMeTieSamePointScore(pStatusPlay->lMeTieKingScore);

			//庄家信息
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			if ( pStatusPlay->wCurrentBankerChairID == INVALID_CHAIR )
				m_GameClientView.SetBankerInfo( INVALID_CHAIR, pStatusPlay->cbBankerTime, pStatusPlay->lBankerScore );
			else
				m_GameClientView.SetBankerInfo( SwitchViewChairID( pStatusPlay->wCurrentBankerChairID ), pStatusPlay->cbBankerTime, pStatusPlay->lCurrentBankerScore );
			m_GameClientView.SetBankerTreasure(pStatusPlay->lBankerTreasure);


			//下注界面
			m_GameClientView.PlaceUserJetton(ID_TIAN_MEN,pStatusPlay->lTieScore);
			m_GameClientView.PlaceUserJetton(ID_QIAO,pStatusPlay->lTieSamePointScore);
			m_GameClientView.PlaceUserJetton(ID_SHUN_MEN,pStatusPlay->lPlayerScore);
			m_GameClientView.PlaceUserJetton(ID_ZUO_JIAO,pStatusPlay->lPlayerKingScore);
			m_GameClientView.PlaceUserJetton(ID_DAO_MEN,pStatusPlay->lBankerScore);
			m_GameClientView.PlaceUserJetton(ID_YOU_JIAO,pStatusPlay->lBankerKingScore);

			//播放声音
			PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));

			DispatchUserCard(pStatusPlay->cbTableCardArray[INDEX_BANKER],pStatusPlay->cbTableCardArray[INDEX_PLAYER1],
				pStatusPlay->cbTableCardArray[INDEX_PLAYER2],pStatusPlay->cbTableCardArray[INDEX_PLAYER3],pStatusPlay->cbTableCardArray[INDEX_PRECARD]);

			//禁用按钮
			m_GameClientView.m_btApplyBanker.EnableWindow( FALSE );
			m_GameClientView.m_btCancelBanker.EnableWindow( FALSE );

			return true;
		}
	}

	return false;
}

//游戏开始
bool CGameClientDlg::OnSubGameStart(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) return false;
	//消息处理
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;
	//设置状态
	SetGameStatus(GS_PLAYING);
	KillGameTimer(IDI_PLACE_JETTON);
	//SetGameTimer(GetMeChairID(),IDI_SHOW_TIME,pGameStart->cbTimeLeave);
	m_GameClientView.m_bJettonstate=false;
	//更新控制
	UpdateButtonContron();
	DispatchUserCard(pGameStart->cbTableCardArray[INDEX_BANKER],pGameStart->cbTableCardArray[INDEX_PLAYER1],
		pGameStart->cbTableCardArray[INDEX_PLAYER2],pGameStart->cbTableCardArray[INDEX_PLAYER3],pGameStart->cbTableCardArray[INDEX_PRECARD]);
	//环境设置
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));
	return true;
}

//用户加注
bool CGameClientDlg::OnSubPlaceJetton(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_PlaceJetton));
	if (wDataSize!=sizeof(CMD_S_PlaceJetton)) return false;

	//消息处理
	CMD_S_PlaceJetton * pPlaceJetton=(CMD_S_PlaceJetton *)pBuffer;
	//播放声音
	PlayGameSound(AfxGetInstanceHandle(),TEXT("ADD_GOLD"));

	//加注界面
	m_GameClientView.PlaceUserJetton(pPlaceJetton->cbJettonArea,pPlaceJetton->lJettonScore);

	return true;
}

//游戏结束
bool CGameClientDlg::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

	//消息处理
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

	m_lCellScore=pGameEnd->lCellScore;
	//设置状态
	SetGameStatus(GS_FREE);
	KillTimer(IDI_DISPATCH_CARD);
	KillTimer(IDI_SHOW_GAME_RESULT);
	KillTimer(IDI_CUO_POKER_TIME);
	m_GameClientView.SetDispatchCardFalg(false);

	//更新成绩
	for ( WORD wUserIndex = 0; wUserIndex < MAX_CHAIR; ++wUserIndex )
	{
		tagUserData const *pUserData = GetUserData(wUserIndex);

		if ( pUserData == NULL ) continue;
		tagApplyUser ApplyUser ;

		//更新信息
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

	//设置变量
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore = 0L;
	m_lMeYouJiaoScore = 0L;
	m_lMeZuoJiaoScore = 0L;
	m_lMeMaxScore=pGameEnd->lMeMaxScore;
	//庄家金币
	m_GameClientView.SetBankerTreasure(pGameEnd->lBankerTreasure);

	//状态变量
	m_bPlaying = false;

	//玩家下注
	m_GameClientView.SetMeMaxScore(m_lMeMaxScore);
	m_GameClientView.SetMeTieScore(m_lMeTianMenScore);
	m_GameClientView.SetMeBankerScore(m_lMeDaoMenScore);
	m_GameClientView.SetMePlayerScore(m_lMeShunMenScore);
	m_GameClientView.SetMeBankerKingScore(m_lMeYouJiaoScore);
	m_GameClientView.SetMePlayerKingScore(m_lMeZuoJiaoScore);
	m_GameClientView.SetMeTieSamePointScore(m_lMeQiaoScore);

	//设置界面
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

	//庄家信息
	if ( m_wCurrentBanker != INVALID_CHAIR )
		m_GameClientView.SetBankerInfo(SwitchViewChairID(m_wCurrentBanker), pGameEnd->nBankerTime, pGameEnd->lBankerTotalScore);

	//更新控制
	UpdateButtonContron();

	//扑克信息
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
	//播放声音
	PlayGameSound(AfxGetInstanceHandle(),TEXT("PLACE_JETTON"));

	KillTimer(IDI_SHOW_GAME_RESULT);
	//设置时间
	SetGameTimer(GetMeChairID(),IDI_PLACE_JETTON,pGameEnd->cbTimeLeave);
	m_GameClientView.m_bJettonstate=true;
	return true;
}

//游戏积分
bool CGameClientDlg::OnSubGameScore(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_GameScore));
	if (wDataSize!=sizeof(CMD_S_GameScore)) return false;

	//消息处理
	CMD_S_GameScore * pGameScore=(CMD_S_GameScore *)pBuffer;

	//历史成绩
	m_wDrawCount++;
	m_lMeResultCount+=pGameScore->lMeGameScore;

	//设置成绩
	m_GameClientView.SetGameScore(pGameScore->lMeGameScore, pGameScore->lMeReturnScore, pGameScore->lBankerScore);

	m_GameClientView.SetMeTieScore(pGameScore->lMeTieScore);
	m_GameClientView.SetMeBankerScore(pGameScore->lMeBankerScore);
	m_GameClientView.SetMePlayerScore(pGameScore->lMePlayerScore);
	m_GameClientView.SetMeBankerKingScore(pGameScore->lMeBankerKingScore);
	m_GameClientView.SetMePlayerKingScore(pGameScore->lMePlayerKingScore);
	m_GameClientView.SetMeTieSamePointScore(pGameScore->lMeTieKingScore);

	//设置变量
	m_lMeTianMenScore=pGameScore->lMeTieScore;
	m_lMeDaoMenScore=pGameScore->lMeBankerScore;
	m_lMeShunMenScore=pGameScore->lMePlayerScore;
	m_lMeQiaoScore = pGameScore->lMeTieKingScore;
	m_lMeYouJiaoScore = pGameScore->lMeBankerKingScore;
	m_lMeZuoJiaoScore = pGameScore->lMePlayerKingScore;

	return true;
}

//更新控制
void CGameClientDlg::UpdateButtonContron()
{
	if ((IsLookonMode()==false)&&(GetGameStatus()==GS_FREE) && m_wCurrentBanker != GetMeChairID() && m_wCurrentBanker != INVALID_CHAIR )
	{
		//计算积分
		__int64 lCurrentJetton=m_GameClientView.GetCurrentJetton();
		__int64 lLeaveScore=m_lMeMaxScore-m_lMeTianMenScore-m_lMeDaoMenScore-m_lMeShunMenScore-m_lMeYouJiaoScore-m_lMeZuoJiaoScore-m_lMeQiaoScore;

		//lLeaveScore=min(lLeaveScore, m_lCellScore);
		//设置光标
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

		//控制按钮
		UINT uFlageScore[] = {1000, 10000, 100000, 500000, 1000000, 5000000, 10000000};
		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled((lLeaveScore>=uFlageScore[i])?FALSE:TRUE);
		}

	}
	else
	{
		//设置光标
		m_GameClientView.SetCurrentJetton(0L);

		//禁止按钮
		for (int i=0; i<7; i++)
		{
			m_GameClientView.m_JettonButton[i].Enabled(TRUE);
		}
	}

	//申请按钮
	if ( ! IsLookonMode() )
	{
		//状态判断
		if ( GetGameStatus()==GS_FREE ) 
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
			m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		}
		if ( GetGameStatus()==(GS_PLAYING+1) ) 
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(TRUE);
			m_GameClientView.m_btApplyBanker.EnableWindow(TRUE);
		}
		else
		{
			m_GameClientView.m_btCancelBanker.EnableWindow(FALSE);
			m_GameClientView.m_btApplyBanker.EnableWindow(FALSE);
		}

		//显示判断
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

//派发扑克
bool CGameClientDlg::DispatchUserCard(BYTE cbBankerCard[],BYTE cbPlayerCard1[],BYTE cbPlayerCard2[],BYTE cbPlayerCard3[],BYTE cbPreCard[])
{
	//设置变量
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

	//--时间
	SetTimer(IDI_DISPATCH_CARD,500,NULL);

	return true;
}

//定时器消息
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
	case IDI_DISPATCH_CARD:		//派发扑克
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
	
			//发送扑克
			if ((m_cbSendCount[0]+m_cbSendCount[1]+m_cbSendCount[2]+m_cbSendCount[3])<8)
			{
				//定义索引
				WORD wIndex=(m_cbSendCount[0]+m_cbSendCount[1]+m_cbSendCount[2]+m_cbSendCount[3]+m_GameLogic.GetCardValue(m_cbTableCardArray[4][0])-1)%4;

				//设置扑克
				m_cbSendCount[wIndex]++;
				m_GameClientView.m_DrawCard[wIndex].SetCardData(m_cbTableCardArray[wIndex],m_cbSendCount[wIndex]);

				//更新界面
				m_GameClientView.UpdateGameView(NULL);

				//播放声音
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
					//庄家按钮
					m_GameClientView.m_btApplyBanker.EnableWindow( TRUE );
					m_GameClientView.m_btCancelBanker.EnableWindow( TRUE );
				}
				return;
			}

			//获取牌点
			BYTE cbPlayerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],m_cbCardCount[INDEX_PLAYER1]);
			BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],m_cbCardCount[INDEX_BANKER]);

			//设置胜方
			WORD cbWinnerSide=ID_TIAN_MEN;
			DeduceWinner(cbWinnerSide);

			//胜利字符
			TCHAR szGameResult[256]=TEXT("");

			CString strCardNick;
			strCardNick.Format("庄家:%s   \r\n顺门:%s  \r\n天门:%s  \r\n倒门:%s ",
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_BANKER]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER1]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER2]),
				m_GameLogic.GetCardNick(m_cbTableCardArray[INDEX_PLAYER3])
				);

			m_strDispatchCardTips += szGameResult;
			m_strDispatchCardTips +=strCardNick;
			m_GameClientView.SetDispatchCardTips(m_strDispatchCardTips);
			
			//设置界面
			m_GameClientView.SetWinnerSide(szGameResult,cbWinnerSide);
			m_GameClientView.SetDispatchCardFalg(false);

			//删除时间
			KillTimer(IDI_DISPATCH_CARD);
			//设置时间
			m_nShowResultTime = 15;
			SetTimer(IDI_SHOW_GAME_RESULT, 5*1000L, NULL);
			m_GameClientView.SetShowGameFlag(true);

			//播放剩余
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

//加注消息
LRESULT CGameClientDlg::OnPlaceJetton(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	BYTE cbJettonArea=(BYTE)wParam;
	__int64 lJettonScore=*(__int64*)lParam;

	//庄家判断
	if ( GetMeChairID() == m_wCurrentBanker ) return true;
	if ( m_wCurrentBanker == INVALID_CHAIR ) 
	{
		UpdateButtonContron();
		return true;
	}

	//设置变量
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
		case ID_QIAO:
			{
				m_lMeQiaoScore += lJettonScore;
				m_GameClientView.SetMeTieSamePointScore(m_lMeQiaoScore);
				break;
			}
		case ID_ZUO_JIAO:
			{
				m_lMeZuoJiaoScore += lJettonScore;
				m_GameClientView.SetMePlayerKingScore(m_lMeZuoJiaoScore);
				break;
			}
		case ID_YOU_JIAO:
			{
				m_lMeYouJiaoScore += lJettonScore;
				m_GameClientView.SetMeBankerKingScore(m_lMeYouJiaoScore);
				break;
			}
		}

	//变量定义
	CMD_C_PlaceJetton PlaceJetton;
	ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

	//构造变量
	PlaceJetton.cbJettonArea=cbJettonArea;
	PlaceJetton.lJettonScore=lJettonScore;

	//发送消息
	SendData(SUB_C_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));

	//更新按钮
	UpdateButtonContron();

	//设置状态
	m_bPlaying = true;

	return 0;
}

//申请消息
LRESULT CGameClientDlg::OnApplyBanker(WPARAM wParam, LPARAM lParam)
{
	//合法判断
	tagUserData const *pMeUserData = GetUserData( GetMeChairID() );
	if ( pMeUserData->lScore < m_lApplyBankerCondition ) return true;

	//旁观判断
	if ( IsLookonMode() ) return true;

	//转换变量
	bool bApplyBanker = wParam != 0 ? true : false;

	//当前判断
	if ( m_wCurrentBanker == GetMeChairID() && bApplyBanker ) return true;

	CMD_C_ApplyBanker ApplyBanker;

	//赋值变量
	ApplyBanker.bApplyBanker = bApplyBanker;

	//发送消息
	SendData( SUB_C_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );

	//设置按钮
	if ( m_wCurrentBanker == GetMeChairID() && !bApplyBanker )
	{
		m_GameClientView.m_btCancelBanker.EnableWindow(FALSE);
	}

	return true;
}

//申请做庄
bool CGameClientDlg::OnUserApplyBanker(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_ApplyBanker));
	if (wDataSize!=sizeof(CMD_S_ApplyBanker)) return false;

	//消息处理
	CMD_S_ApplyBanker * pApplyBanker=(CMD_S_ApplyBanker *)pBuffer;

	//插入玩家
	if ( pApplyBanker->bApplyBanker )
	{
		tagApplyUser ApplyUser;
		ApplyUser.strUserName = pApplyBanker->szAccount;
		ApplyUser.lUserScore = pApplyBanker->lScore;

		//插入判断
		bool bInsertApplyUser = true;

		if ( m_wCurrentBanker != INVALID_CHAIR )
		{
			tagUserData const *pBankerUserData = GetUserData(m_wCurrentBanker);
			if ( pBankerUserData != NULL && 0==lstrcmp(pBankerUserData->szName, pApplyBanker->szAccount))
				bInsertApplyUser = false;
		}

		if ( bInsertApplyUser == true ) m_GameClientView.m_ApplyUser.InserUser( ApplyUser );

		//更换按钮
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

		//更换按钮
		tagUserData const *pUserData = GetUserData( GetMeChairID() );
		if ( pUserData &&  !lstrcmp(pApplyBanker->szAccount, pUserData->szName ) )
		{
			m_bMeApplyBanker = false;
			
			UpdateButtonContron();
		}
	}

	return true;
}

//切换庄家
bool CGameClientDlg::OnChangeBanker(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_ChangeBanker));
	if (wDataSize!=sizeof(CMD_S_ChangeBanker)) return false;

	//消息处理
	CMD_S_ChangeBanker * pChangeBanker=(CMD_S_ChangeBanker *)pBuffer;

	//显示图片
	m_GameClientView.ShowChangeBanker( m_wCurrentBanker != pChangeBanker->wChairID );

	//自己判断
	if ( m_wCurrentBanker == GetMeChairID() && IsLookonMode() == false && pChangeBanker->wChairID != GetMeChairID() ) 
	{
		m_bMeApplyBanker = false;
	}

	m_wCurrentBanker = pChangeBanker->wChairID;

	//庄家信息
	if ( pChangeBanker->wChairID == INVALID_CHAIR )
	{
		m_GameClientView.SetBankerInfo( INVALID_CHAIR, pChangeBanker->cbBankerTime, pChangeBanker->lBankerScore );
	}
	else
	{
		m_GameClientView.SetBankerInfo( SwitchViewChairID( pChangeBanker->wChairID ), pChangeBanker->cbBankerTime, 0 );
	}
	m_GameClientView.SetBankerTreasure(pChangeBanker->lBankerTreasure);

	//删除玩家
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
	
	//更新界面
	UpdateButtonContron();

	return true;
}

//更新积分
bool CGameClientDlg::OnChangeUserScore(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_ChangeUserScore));
	if (wDataSize!=sizeof(CMD_S_ChangeUserScore)) return false;

	//消息处理
	CMD_S_ChangeUserScore * pChangeUserScore=(CMD_S_ChangeUserScore *)pBuffer;

	tagUserData const *pUserData = GetUserData( pChangeUserScore->wChairID );

	if ( pUserData )
	{
		tagApplyUser ApplyUser ;

		ApplyUser.lUserScore = pChangeUserScore->lScore;
		ApplyUser.strUserName = pUserData->szName;
		m_GameClientView.m_ApplyUser.UpdateUser( ApplyUser );
	}

	//庄家信息
	if ( m_wCurrentBanker == pChangeUserScore->wCurrentBankerChairID )
	{
		m_GameClientView.SetBankerInfo( SwitchViewChairID( pChangeUserScore->wCurrentBankerChairID ), pChangeUserScore->cbBankerTime, pChangeUserScore->lCurrentBankerScore );

		//更新界面
		UpdateButtonContron();
	}

	return true;
}

//取消消息
void CGameClientDlg::OnCancel()
{
	//HANDRED_GAME_QUIT_TIP;	
	__super::OnCancel();
}

//游戏记录
bool CGameClientDlg::OnSubGameRecord(const void * pBuffer, WORD wDataSize)
{
	//效验参数
	ASSERT(wDataSize%sizeof(tagServerGameRecord)==0);
	if (wDataSize%sizeof(tagServerGameRecord)!=0) return false;
	
	//结果变量
	tagGameRecord GameRecord;
	ZeroMemory(&GameRecord,sizeof(GameRecord));

	//设置记录
	WORD wRecordCount=wDataSize/sizeof(tagServerGameRecord);
	for (WORD wIndex=0;wIndex<wRecordCount;wIndex++) 
	{
		tagServerGameRecord * pServerGameRecord=(((tagServerGameRecord *)pBuffer)+wIndex);

		m_GameClientView.SetGameHistory(enOperateResult_NULL, pServerGameRecord->cbPlayerCount, pServerGameRecord->cbBankerCount,pServerGameRecord->wWinner);
	}

	return true;
}

//发牌提示
void CGameClientDlg::SetDispatchCardTips()
{
	//计算点数
	BYTE cbBankerCount=m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_BANKER],2);
	BYTE cbPlayerTwoCardCount = m_GameLogic.GetCardListPip(m_cbTableCardArray[INDEX_PLAYER1],2);

	//闲家补牌
	BYTE cbPlayerThirdCardValue = 0 ;	//第三张牌点数
	if(cbPlayerTwoCardCount<=5 && cbBankerCount<8)
	{
		//计算点数
		cbPlayerThirdCardValue = m_GameLogic.GetCardPip(m_cbTableCardArray[INDEX_PLAYER1][2]);
		CString strTips;
		strTips.Format(TEXT("闲%d点，庄%d点，闲继续拿牌\n"), cbPlayerTwoCardCount, cbBankerCount);
		m_strDispatchCardTips = strTips;
		m_GameClientView.SetDispatchCardTips(m_strDispatchCardTips);
	}

	return ;
}


//推断赢家
void CGameClientDlg::DeduceWinner(WORD &cbWinner)
{
	cbWinner = 0;

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

LRESULT CGameClientDlg::OnCuoPai(WPARAM wParam, LPARAM lParam)
{

	tagUserData const *pMeUserData = GetUserData( GetMeChairID() );
	if ( pMeUserData != NULL && pMeUserData->cbUserStatus == US_PLAY)
	{
		InsertShtickString("【系统提示】游戏中不能切换搓牌模式！",RGB(255,0,0),true);
		return true;
	}
	if(m_GameClientView.m_bAutoCard)
	{
		m_GameClientView.m_btnShouDongCuoPai.ShowWindow(SW_HIDE);
		m_GameClientView.m_btnZiDongCuoPai.ShowWindow(SW_SHOW);
		m_GameClientView.m_bAutoCard=false;
		InsertShtickString("【系统提示】当前为手工搓牌模式！",RGB(255,0,0),true);

	}
	else
	{
		m_GameClientView.m_btnShouDongCuoPai.ShowWindow(SW_SHOW);
		m_GameClientView.m_btnZiDongCuoPai.ShowWindow(SW_HIDE);
		m_GameClientView.m_bAutoCard=true;
		InsertShtickString("【系统提示】当前为自动搓牌模式！",RGB(255,0,0),true);
	}
	return true;
}

LRESULT CGameClientDlg::OnBank(WPARAM wParam, LPARAM lParam)
{
	if ( m_GameClientView.GetMeChairID() == m_GameClientView.m_wCurrentBankerChairID)
		UserOnBankBT(TRUE);
	else
		UserOnBankBT(FALSE);

	return 0;
}

