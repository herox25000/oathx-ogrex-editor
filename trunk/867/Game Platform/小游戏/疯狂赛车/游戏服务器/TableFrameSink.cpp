#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////


//下注时间
#define IDI_PLACE_JETTON			1									//下注时间
#define TIME_PLACE_JETTON			20									//下注时间

//结束时间
#define IDI_GAME_END				2									//结束时间
#define TIME_GAME_END				10									//结束时间

#define IDI_GAME_FREE				3									//空闲阶段
#define TIME_FREE					10									//空闲时间

//////////////////////////////////////////////////////////////////////////

//静态变量
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;				//游戏人数
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_TimeControl;	//开始模式

//////////////////////////////////////////////////////////////////////////

//替代结构
struct tagReplaceCard
{
	BYTE							cbCardCount[2];						//扑克数目
    BYTE							cbTableCardArray[2][3];				//桌面扑克
};

//构造函数
CTableFrameSink::CTableFrameSink()
{
	//下注信息
	m_lAllBigTigerScore=0L;
	m_lAllSmlTigerScore=0L;
	m_lAllBigBogScore=0L;
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;
	m_lAllSmlSnakeScore=0L;

	//状态变量
	m_dwJettonTime=0L;

	//下注信息
	ZeroMemory(m_lUserBigTigerScore,sizeof(m_lUserBigTigerScore));
	ZeroMemory(m_lUserSmlTigerScore,sizeof(m_lUserSmlTigerScore));
	ZeroMemory(m_lUserBigBogScore,  sizeof(m_lUserBigBogScore));
	ZeroMemory(m_lUserSmlBogScore,  sizeof(m_lUserSmlBogScore));
	ZeroMemory(m_lUserBigHorseScore,sizeof(m_lUserBigHorseScore));
	ZeroMemory(m_lUserSmlHorseScore,sizeof(m_lUserSmlHorseScore));
	ZeroMemory(m_lUserBigSnakeScore,sizeof(m_lUserBigSnakeScore));
	ZeroMemory(m_lUserSmlSnakeScore,sizeof(m_lUserSmlSnakeScore));

	//玩家成绩
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	//扑克信息
	m_cbAnimalBox=0;

	//庄家变量

	ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
	m_cbBankerTimer=0;
	m_lBankerWinScore = 0;
	m_bCancelBanker=false;
	
	//组件变量
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;
	m_pITableFrameControl=NULL;

	//游戏记录
	ZeroMemory(m_GameRecordArrary, sizeof(m_GameRecordArrary));
	m_nRecordFirst=0;	
	m_nRecordLast=0;	

	//读取分数
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;

	return;
}

//析构函数
CTableFrameSink::~CTableFrameSink(void)
{
}

//接口查询
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//初始化
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//查询接口
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//控制接口
	m_pITableFrameControl=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrameControl);
	if (m_pITableFrameControl==NULL) return false;

	//获取参数
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	m_pITableFrame->SetGameStatus(GS_FREE);

	return true;
}

//复位桌子
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//下注信息
	m_lAllBigTigerScore=0L;
	m_lAllSmlTigerScore=0L;
	m_lAllBigBogScore=0L;
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;
	m_lAllSmlSnakeScore=0L;

	//下注信息
	ZeroMemory(m_lUserBigTigerScore,sizeof(m_lUserBigTigerScore));
	ZeroMemory(m_lUserSmlTigerScore,sizeof(m_lUserSmlTigerScore));
	ZeroMemory(m_lUserBigBogScore,sizeof(m_lUserBigBogScore));
	ZeroMemory(m_lUserSmlBogScore,sizeof(m_lUserSmlBogScore));
	ZeroMemory(m_lUserBigHorseScore,sizeof(m_lUserBigHorseScore));
	ZeroMemory(m_lUserSmlHorseScore,sizeof(m_lUserSmlHorseScore));
	ZeroMemory(m_lUserBigSnakeScore,sizeof(m_lUserBigSnakeScore));
	ZeroMemory(m_lUserSmlSnakeScore,sizeof(m_lUserSmlSnakeScore));

	//扑克信息
	m_cbAnimalBox=0;

	//玩家成绩
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));

	return;
}

//开始模式
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//游戏状态
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}

//游戏开始
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	//设置状态
	m_pITableFrame->SetGameStatus(GS_PLAYING);

	//变量定义
	CMD_S_GameStart GameStart;
	ZeroMemory(&GameStart,sizeof(GameStart));

	MakeAnimate();

	ChuLaoQian();

	//构造数据
	GameStart.cbAnimalBox=m_cbAnimalBox;
	GameStart.cbTimeLeave=(m_cbAnimalBox*ANIMAL_ROLL_SPEED)/1000+TIME_GAME_END;
	GameStart.lApplyBankerCondition = m_lApplyBankerCondition;

	//发送数据
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));

	//计算分数
	CalculateScore();

	return true;
}

//游戏结束
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//常规结束
		{
			//结束消息
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));

			GameEnd.nBankerTime = m_cbBankerTimer;

			GameEnd.lBankerTotalScore = m_lBankerWinScore;

			//推断玩家
			GameEnd.cbWinner=DeduceWinner();			

			//写入积分
			for ( WORD wUserChairID = 0; wUserChairID < GAME_PLAYER; ++wUserChairID )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserChairID);
				if ( pIServerUserItem == NULL ) continue;

				//胜利类型
				enScoreKind ScoreKind=(m_lUserWinScore[wUserChairID]>0L)?enScoreKind_Win:enScoreKind_Lost;

				//写入积分
				if (m_lUserWinScore[wUserChairID]!=0L) 
					m_pITableFrame->WriteUserScore(wUserChairID,m_lUserWinScore[wUserChairID], 0, ScoreKind);

				//庄家判断
				if ( m_CurrentBanker.dwUserID == pIServerUserItem->GetUserID() ) 
					m_CurrentBanker.lUserScore = pIServerUserItem->GetUserScore()->lScore;
			}

			//发送积分
			GameEnd.cbTimeLeave=TIME_FREE;	
			if ( m_CurrentBanker.dwUserID != 0 ) GameEnd.lBankerTreasure = m_CurrentBanker.lUserScore;
			for ( WORD wUserIndex = 0; wUserIndex < GAME_PLAYER; ++wUserIndex )
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetServerUserItem(wUserIndex);
				if ( pIServerUserItem == NULL ) continue;

				//发送消息					
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

			//庄家判断
			if ( m_CurrentBanker.dwUserID != 0 )
			{
				//获取用户
				IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
				if (pIServerUserItem) 
				{
					//积分判断
					if ( pIServerUserItem->GetUserScore()->lScore < m_lApplyBankerCondition || m_cbBankerTimer >= 20 )
					{
						//玩家下庄
						OnUserApplyBanker( pIServerUserItem->GetUserData(), false );
					}
				}
			}

			//结束游戏
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:		//用户离开
		{
			//胜利类型
			__int64	allZhu=0;
			if ( pIServerUserItem->GetUserID()==m_CurrentBanker.dwUserID ) //庄家强退
			{
				allZhu=Get_ALL_MultiDesktopScore();
			}
			else
			{
				//在押注状态下，可以退出不扣分
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
				//变量定义
				tagScoreInfo ScoreInfo;
				ZeroMemory(&ScoreInfo,sizeof(ScoreInfo));

				//设置变量
				m_pITableFrame->WriteUserScore(pIServerUserItem, -allZhu, 0, enScoreKind_Flee);
			}
			return true;
		}
	}

	return false;
}

//发送场景
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_FREE:			//空闲状态
		{
			//发送记录
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

			//构造数据
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//下注信息
			//下注信息
			StatusFree.lBigTigerScore	= m_lAllBigTigerScore;
			StatusFree.lSmlTigerScore	= m_lAllSmlTigerScore;
			StatusFree.lBigBogScore		= m_lAllBigBogScore;
			StatusFree.lSmlBogScore		= m_lAllSmlBogScore;
			StatusFree.lBigHorseScore   = m_lAllBigHorseScore;
			StatusFree.lSmlHorseScore	= m_lAllSmlHorseScore;
			StatusFree.lBigSnakeScore   = m_lAllBigSnakeScore;
			StatusFree.lSmlSnakeScore	= m_lAllSmlSnakeScore;

			//庄家信息
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//下注信息
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
			
			//全局信息
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusFree.cbTimeLeave=(BYTE)(TIME_FREE-__min(dwPassTime,TIME_FREE));

			//发送场景
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
			
			//发送申请者
			SendApplyUser(  pIServerUserItem );

			return bSuccess;
		}
	case GS_FREE + 1:
		{
			//发送记录
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

			//构造数据
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			//下注信息
			//下注信息
			StatusFree.lBigTigerScore	= m_lAllBigTigerScore;
			StatusFree.lSmlTigerScore	= m_lAllSmlTigerScore;
			StatusFree.lBigBogScore		= m_lAllBigBogScore;
			StatusFree.lSmlBogScore		= m_lAllSmlBogScore;
			StatusFree.lBigHorseScore   = m_lAllBigHorseScore;
			StatusFree.lSmlHorseScore	= m_lAllSmlHorseScore;
			StatusFree.lBigSnakeScore   = m_lAllBigSnakeScore;
			StatusFree.lSmlSnakeScore	= m_lAllSmlSnakeScore;

			//庄家信息
			StatusFree.lApplyBankerCondition = m_lApplyBankerCondition;

			//下注信息
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

			//全局信息
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusFree.cbTimeLeave=(BYTE)(TIME_PLACE_JETTON-__min(dwPassTime,TIME_PLACE_JETTON));

			//发送场景
			bool bSuccess = m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));

			//发送申请者
			SendApplyUser(  pIServerUserItem );

			return bSuccess;
		}
	case GS_PLAYING:		//游戏状态
		{
			//构造数据
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

			//庄家信息
			StatusPlay.lApplyBankerCondition = m_lApplyBankerCondition;

			//下注信息
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

			//扑克信息
			StatusPlay.cbAnimalBox=m_cbAnimalBox;

			//全局信息
			DWORD dwPassTime=(DWORD)time(NULL)-m_dwJettonTime;
			StatusPlay.cbTimeLeave=(BYTE)(TIME_PLACE_JETTON-__min(dwPassTime,TIME_PLACE_JETTON));

			//发送申请者
			SendApplyUser( pIServerUserItem );

			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//定时器事件
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	switch (wTimerID)
	{
	case IDI_GAME_FREE:
		{
			//刷新下庄家的分数
			IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if(pBankerItem)
			{
				if(m_CurrentBanker.dwUserID != 0L)
					m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
			}
			OnEventStartPlaceJetton();
			m_pITableFrame->SetGameTimer(IDI_PLACE_JETTON, TIME_PLACE_JETTON*1000,1,0L);
			return true;
		}
	case IDI_PLACE_JETTON:		//下注时间
		{
			//刷新下庄家的分数
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
	case IDI_GAME_END:			//结束游戏
		{
			//刷新下庄家的分数
			IServerUserItem * pBankerItem=m_pITableFrame->GetServerUserItem(m_CurrentBanker.wChairID);
			if(pBankerItem)
			{
				if(m_CurrentBanker.dwUserID != 0L)
					m_CurrentBanker.lUserScore=pBankerItem->GetUserScore()->lScore;
			}
			OnEventGameEnd(INVALID_CHAIR,NULL,GER_NORMAL);

			//下庄判断
			if ( m_bCancelBanker && m_CurrentBanker.dwUserID != 0 )
			{
				//获取玩家
				IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );

				//重置变量
				m_cbBankerTimer = 0;
				m_lBankerWinScore=0;
				ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
				m_bCancelBanker=false;
				
				//发送消息
				SendChangeBankerMsg();

				//删除庄家
				if ( pServerUserItem ) 
					OnUserApplyBanker( pServerUserItem->GetUserData(), false );
			}

			//设置时间
			m_dwJettonTime=(DWORD)time(NULL);
			m_pITableFrame->SetGameTimer(IDI_GAME_FREE, TIME_FREE*1000L, 1, 0L);
			m_pITableFrame->SetGameStatus(GS_FREE);

			//轮换庄家
			ChangeBanker();

			//庄家信息
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

			//切换判断
			if ( m_cbBankerTimer == 0 )
			{
				SendChangeBankerMsg();
			}
			return true;
		}
	}

	return false;
}

//游戏消息处理
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_PLACE_JETTON:		//用户加注
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_C_PlaceJetton));
			if (wDataSize!=sizeof(CMD_C_PlaceJetton)) return false;

			//用户效验
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();

			if (pUserData->cbUserStatus!=US_SIT) return true;

			//消息处理
			CMD_C_PlaceJetton * pPlaceJetton=(CMD_C_PlaceJetton *)pDataBuffer;
			return OnUserPlaceJetton(pUserData->wChairID, pPlaceJetton->cbJettonArea, pPlaceJetton->lJettonScore);
		}
	case SUB_C_APPLY_BANKER:		//申请做庄
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_C_ApplyBanker));
			if (wDataSize!=sizeof(CMD_C_ApplyBanker)) return false;

			//用户效验
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();

			//消息处理
			CMD_C_ApplyBanker * pApplyBanker=(CMD_C_ApplyBanker *)pDataBuffer;

			return OnUserApplyBanker( pUserData, pApplyBanker->bApplyBanker );	
		}
	}

	return false;
}

//框架消息处理
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//用户坐下
bool __cdecl CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//设置时间
	if ((bLookonUser==false)&&(m_dwJettonTime==0L))
	{
		m_dwJettonTime=(DWORD)time(NULL);
		m_pITableFrame->SetGameTimer(IDI_GAME_FREE, TIME_FREE*1000L,1,NULL);	
	}

	return true;
}

//用户起来
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//记录成绩
	if ( bLookonUser==false )
	{
		if ( m_pITableFrame->GetGameStatus() != GS_PLAYING )
		{
			OnEventGameEnd( wChairID, pIServerUserItem, GER_USER_LEFT);
		}
		//存在判断
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

			if ( ApplyUserInfo.dwUserID == pIServerUserItem->GetUserID() )
			{
				//删除玩家
				m_ApplyUserArrary.RemoveAt( nUserIdx );

				//构造变量
				CMD_S_ApplyBanker ApplyBanker;
				CopyMemory( ApplyBanker.szAccount, pIServerUserItem->GetAccounts(), sizeof( ApplyBanker.szAccount ) );
				ApplyBanker.lScore = pIServerUserItem->GetUserScore()->lScore;
				ApplyBanker.bApplyBanker = false;

				//发送消息
				m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
				m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );

				//当前判断
				if ( ApplyUserInfo.dwUserID == m_CurrentBanker.dwUserID )
				{
					//重置变量
					ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
					m_CurrentBanker.dwUserID=0;
					m_cbBankerTimer=0;
					m_lBankerWinScore=0;

					//发送消息
					SendChangeBankerMsg();
				}
			}
		}

		WORD wNowCount=m_pITableFrame->GetNowPlayerCount();
		CString str;
		str.Format("房间还剩人数：%d",wNowCount);
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

//加注事件
bool CTableFrameSink::OnUserPlaceJetton(WORD wChairID, BYTE cbJettonArea, __int64 lJettonScore)
{
	//效验参数
	ASSERT( cbJettonArea>=ID_BIG_TIGER && cbJettonArea<=ID_SML_SNAKE);
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) 
		return false;
	if ( lJettonScore<=0L ) return false;

	//效验状态
	ASSERT(m_pITableFrame->GetGameStatus()==GS_FREE+1);
	if (m_pITableFrame->GetGameStatus()!=GS_FREE+1) return true;

	//庄家判断
	if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == wChairID ) return true;
	if ( m_CurrentBanker.dwUserID == 0 ) return true;

	//变量定义
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

	//合法验证
	if ( ID_BIG_TIGER == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllBigTigerScore += lJettonScore;
		m_lUserBigTigerScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_TIGER == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllSmlTigerScore += lJettonScore;
		m_lUserSmlTigerScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_DOG == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllBigBogScore += lJettonScore;
		m_lUserBigBogScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_DOG == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllSmlBogScore += lJettonScore;
		m_lUserSmlBogScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_HORSE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllBigHorseScore += lJettonScore;
		m_lUserBigHorseScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_HORSE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllSmlHorseScore += lJettonScore;
		m_lUserSmlHorseScore[wChairID] += lJettonScore;
	}
	else if ( ID_BIG_SNAKE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllBigSnakeScore += lJettonScore;
		m_lUserBigSnakeScore[wChairID] += lJettonScore;
	}
	else if ( ID_SML_SNAKE == cbJettonArea )
	{
		if ( GetMaxPutScore(wChairID, cbJettonArea) < lJettonScore ) return true;

		//保存下注
		m_lAllSmlSnakeScore += lJettonScore;
		m_lUserSmlSnakeScore[wChairID] += lJettonScore;
	}
	else
	{
		ASSERT(FALSE);
		return true;
	}

	//变量定义
	CMD_S_PlaceJetton PlaceJetton;
	ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

	//构造变量
	PlaceJetton.wChairID=wChairID;
	PlaceJetton.cbJettonArea=cbJettonArea;
	PlaceJetton.lJettonScore=lJettonScore;

	//发送消息
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_PLACE_JETTON,&PlaceJetton,sizeof(PlaceJetton));

	return true;
}


//申请庄家
bool CTableFrameSink::OnUserApplyBanker( tagServerUserData *pUserData, bool bApplyBanker )
{
	//合法判断
	if ( bApplyBanker && pUserData->UserScoreInfo.lScore < m_lApplyBankerCondition ) return true;

	//保存玩家
	if ( bApplyBanker )
	{
		//存在判断
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];
			if ( ApplyUserInfo.dwUserID == pUserData->dwUserID ) return true;
		}

		//构造信息
		tagApplyUserInfo ApplyUserInfo;
		ApplyUserInfo.dwUserID = pUserData->dwUserID;
		ApplyUserInfo.lUserScore = pUserData->UserScoreInfo.lScore;
		ApplyUserInfo.wChairID = pUserData->wChairID;
		ApplyUserInfo.dwUserType = pUserData->cbMasterOrder;

		//插入玩家
		INT_PTR nUserCount = m_ApplyUserArrary.GetCount();
		m_ApplyUserArrary.InsertAt( nUserCount, ApplyUserInfo );

		//构造变量
		CMD_S_ApplyBanker ApplyBanker;
		CopyMemory( ApplyBanker.szAccount, pUserData->szAccounts, sizeof( ApplyBanker.szAccount ) );
		ApplyBanker.lScore = pUserData->UserScoreInfo.lScore;
		ApplyBanker.bApplyBanker = true;

		//发送消息
		m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
		m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
	}
	else	//取消申请
	{
		//存在判断
		for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
		{
			tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

			if ( ApplyUserInfo.dwUserID == pUserData->dwUserID )
			{
				//当前判断
				if ( m_CurrentBanker.dwUserID == ApplyUserInfo.dwUserID )
				{
					m_bCancelBanker = true;
					continue;
				}

				//删除玩家
				m_ApplyUserArrary.RemoveAt( nUserIdx );

				//构造变量
				CMD_S_ApplyBanker ApplyBanker;
				CopyMemory( ApplyBanker.szAccount, pUserData->szAccounts, sizeof( ApplyBanker.szAccount ) );
				ApplyBanker.lScore = pUserData->UserScoreInfo.lScore;
				ApplyBanker.bApplyBanker = false;

				//发送消息
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
			//获取玩家
			IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
			//重置变量
			m_cbBankerTimer = 0;
			m_lBankerWinScore=0;
			ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
			m_bCancelBanker=false;
			//发送消息
			SendChangeBankerMsg();
			if ( pServerUserItem )
				OnUserApplyBanker( pServerUserItem->GetUserData(), false );
		}
		if (m_CurrentBanker.dwUserID == 0)
		{
			//轮换庄家
			ChangeBanker();
			//庄家信息
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
			//切换判断
			if ( m_cbBankerTimer == 0 )
			{
				//发送消息
				SendChangeBankerMsg();
			}

		}
	}

	return true;

}

//发送庄家
void CTableFrameSink::SendApplyUser( IServerUserItem *pRcvServerUserItem )
{
	for ( INT_PTR nUserIdx = 0; nUserIdx < m_ApplyUserArrary.GetCount(); ++nUserIdx )
	{
		tagApplyUserInfo ApplyUserInfo = m_ApplyUserArrary[ nUserIdx ];

		//获取玩家
		IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( ApplyUserInfo.wChairID );
		if ( ! pServerUserItem ) continue;

		//构造变量
		CMD_S_ApplyBanker ApplyBanker;
		CopyMemory( ApplyBanker.szAccount, pServerUserItem->GetAccounts(), sizeof( ApplyBanker.szAccount ) );
		ApplyBanker.lScore = pServerUserItem->GetUserScore()->lScore;
		ApplyBanker.bApplyBanker = true;

		//发送消息
		m_pITableFrame->SendUserData( pRcvServerUserItem, SUB_S_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
	}
}

//更换庄家
void CTableFrameSink::ChangeBanker()
{
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_cbBankerTimer++;

	//轮庄判断

	//轮庄判断
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		//轮换判断
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

		//次数判断
		if ( bChangeBanker && 10 <= m_cbBankerTimer )
		{
			m_cbBankerTimer = 0;
			m_lBankerWinScore=0;
			m_bCancelBanker = false;

			//客户端删除
			IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
			OnUserApplyBanker( pServerUserItem->GetUserData(), false ) ;

			//重新赋值
			ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );
			while( ! m_ApplyUserArrary.IsEmpty() )
			{
				m_CurrentBanker = m_ApplyUserArrary[ 0 ];
				IServerUserItem * newBanker = m_pITableFrame->GetServerUserItem( m_CurrentBanker.wChairID );
				if ( newBanker->GetUserScore()->lScore < m_lApplyBankerCondition )
				{
					ZeroMemory( &m_CurrentBanker, sizeof( m_CurrentBanker ) );

					//获取玩家
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
				//获取玩家
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

//轮换庄家
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

		//我的下注
		m_pITableFrame->SendTableData( wChairID, SUB_S_CHANGE_BANKER, &ChangeBanker, sizeof( ChangeBanker ) );
		m_pITableFrame->SendLookonData( wChairID, SUB_S_CHANGE_BANKER, &ChangeBanker, sizeof( ChangeBanker ) );
	}
}

//用户断线
bool __cdecl CTableFrameSink::OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) 
{
	return true;
}

//得到所有人下注的积分
__int64 CTableFrameSink::Get_ALL_MultiDesktopScore()
{
	//大家已下注额
	__int64  lAllDesktopJetton=0L;

	lAllDesktopJetton+=m_lAllBigTigerScore*s_Multiple[0];		//大家买大虎总注
	lAllDesktopJetton+=m_lAllSmlTigerScore*s_Multiple[1];		//大家买小虎总注
	lAllDesktopJetton+=m_lAllBigBogScore*s_Multiple[2];			//大家买大狗总注
	lAllDesktopJetton+=m_lAllSmlBogScore*s_Multiple[3];			//大家买大狗总注
	lAllDesktopJetton+=m_lAllBigHorseScore*s_Multiple[4];		//大家买大马总注
	lAllDesktopJetton+=m_lAllSmlHorseScore*s_Multiple[5];		//大家买小马总注
	lAllDesktopJetton+=m_lAllBigSnakeScore*s_Multiple[6];		//大家买大蛇总注
	lAllDesktopJetton+=m_lAllSmlSnakeScore*s_Multiple[7];		//大家买小蛇总注

	return lAllDesktopJetton;
}

//得到所有人下注的积分
__int64 CTableFrameSink::Get_User_DesktopScore(WORD wChairID)
{
	//某人已下注额
	__int64 lUserDesktopJetton = 0;
	lUserDesktopJetton += m_lUserBigTigerScore[wChairID];    //某人买大虎总注
	lUserDesktopJetton += m_lUserSmlTigerScore[wChairID];	 //某人买小虎总注
	lUserDesktopJetton += m_lUserBigBogScore[wChairID];		 //某人买大狗总注
	lUserDesktopJetton += m_lUserSmlBogScore[wChairID];		 //某人买大狗总注
	lUserDesktopJetton += m_lUserBigHorseScore[wChairID];	 //某人买大马总注
	lUserDesktopJetton += m_lUserSmlHorseScore[wChairID];	 //某人买小马总注
	lUserDesktopJetton += m_lUserBigSnakeScore[wChairID];	 //某人买大蛇总注
	lUserDesktopJetton += m_lUserSmlSnakeScore[wChairID];	 //某人买小蛇总注

	return lUserDesktopJetton;
}

//最大下注
__int64 CTableFrameSink::GetMaxPutScore(WORD wChairID, BYTE cbJettonArea)
{
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) return 0L;

	IServerUserItem *pServerUserItem = m_pITableFrame->GetServerUserItem(wChairID);
	if (pServerUserItem==NULL)
		return 0L;

	//大家已下注额
	__int64 lAllDesktopJetton=Get_ALL_MultiDesktopScore();
	__int64 lAllLeftSpace = m_CurrentBanker.lUserScore-lAllDesktopJetton;
	lAllLeftSpace=max(lAllLeftSpace, 0);
	lAllLeftSpace=lAllLeftSpace/s_Multiple[cbJettonArea-ID_BIG_TIGER];

	//某个人已下注额
	__int64 lUserDesktopJetton=Get_User_DesktopScore(wChairID);
	__int64 lUserLeftSpace = pServerUserItem->GetUserScore()->lScore-lUserDesktopJetton;
	lUserLeftSpace = max(lUserLeftSpace, 0);
	
	__int64 lMinSpace = min(lUserLeftSpace, lAllLeftSpace);

	return lMinSpace;
}

//计算得分
void CTableFrameSink::CalculateScore()
{
	//结束消息
	CMD_S_GameScore GameScore;
	ZeroMemory(&GameScore,sizeof(GameScore));

	//推断玩家
	GameScore.cbWinner=DeduceWinner();

	//游戏记录
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

	//移动下标
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;

	if ( m_nRecordLast == m_nRecordFirst )
		m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;

	//庄家总量
	__int64 lBankerWinScore = 0;

	//玩家成绩
	ZeroMemory(m_lUserWinScore, sizeof(m_lUserWinScore));
	ZeroMemory(m_lUserReturnScore, sizeof(m_lUserReturnScore));
	ZeroMemory(m_lUserRevenue, sizeof(m_lUserRevenue));
	
	__int64 lUserLostScore[GAME_PLAYER];
	ZeroMemory(lUserLostScore, sizeof(lUserLostScore));

	//玩家下注
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

	//计算积分
	for (WORD i=0; i<GAME_PLAYER; i++)
	{
		//庄家判断
		if ( m_CurrentBanker.dwUserID != 0 && m_CurrentBanker.wChairID == i ) continue;

		//获取用户
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

		//总的分数
		m_lUserWinScore[i] += lUserLostScore[i];
	}

	//庄家成绩
	if ( m_CurrentBanker.dwUserID != 0 )
	{
		WORD wBankerChairID = m_CurrentBanker.wChairID;
		m_lUserWinScore[wBankerChairID] = lBankerWinScore;
		//累计积分
		m_lBankerWinScore += lBankerWinScore;
	}

	//买注总量
	GameScore.lDrawBigTigerScore	=m_lAllBigTigerScore;					//买大老虎总注
	GameScore.lDrawSmlTigerScore	=m_lAllSmlTigerScore;					//买小老虎总注
	GameScore.lDrawBigBogScore		=m_lAllBigBogScore;					//买大狗总注
	GameScore.lDrawSmlBogScore		=m_lAllSmlBogScore;					//买大狗总注
	GameScore.lDrawBigHorseScore	=m_lAllBigHorseScore;					//买大马总注
	GameScore.lDrawSmlHorseScore	=m_lAllSmlHorseScore;					//买小马总注
	GameScore.lDrawBigSnakeScore	=m_lAllBigSnakeScore;					//买大蛇总注
	GameScore.lDrawSmlSnakeScore	=m_lAllSmlSnakeScore;					//买小蛇总注
	
	GameScore.lBankerWinScore		=m_lBankerWinScore;

	//发送积分
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

		//发送消息
		GameScore.lMeGameScore		= m_lUserWinScore[wUserIndex];
		GameScore.lMeReturnScore	= m_lUserReturnScore[wUserIndex];

		m_pITableFrame->SendTableData(wUserIndex,SUB_S_GAME_SCORE, &GameScore, sizeof(GameScore));
		m_pITableFrame->SendLookonData(wUserIndex,SUB_S_GAME_SCORE, &GameScore, sizeof(GameScore));
	}
	return ;
}

//推断赢家
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
	str.Format("cbAnimalBox：%d",cbAnimalBox);
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

	//获取玩家
	if (m_CurrentBanker.dwUserID != 0)
	{
		//机器人30%的概率赢钱
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
			//玩家如果做庄
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
	//玩家下注
	__int64 allUserScore[MAX_ANIMAL_COUNT] =  {
		m_lAllBigTigerScore*s_Multiple[0],	//大家买大虎总注
		m_lAllSmlTigerScore*s_Multiple[1],	//大家买小虎总注
		m_lAllBigBogScore  *s_Multiple[2],	//大家买大狗总注
		m_lAllSmlBogScore  *s_Multiple[3],	//大家买大狗总注
		m_lAllBigHorseScore*s_Multiple[4],	//大家买大马总注
		m_lAllSmlHorseScore*s_Multiple[5],	//大家买小马总注
		m_lAllBigSnakeScore*s_Multiple[6],	//大家买大蛇总注
		m_lAllSmlSnakeScore*s_Multiple[7]	//大家买小蛇总注
	};
	BYTE cbAnimal=m_cbAnimalBox%MAX_ANIMAL_COUNT;
	//玩家下注
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

	//变量定义
	CMD_S_JettonStart JettonStart;
	ZeroMemory(&JettonStart,sizeof(JettonStart));
	//构造数据
	JettonStart.cbTimeLeave=TIME_PLACE_JETTON;	
	//发送数据
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

// 	//变量定义
// 	CMD_S_JettonChange JettonChange;
// 	ZeroMemory(&JettonChange,sizeof(JettonChange));
// 	JettonChange.lTianMenScore=nTianmen;
// 	JettonChange.lDaoMenScore=nDaomen;
// 	JettonChange.lShunMenScore=nShunmen;
// 	JettonChange.lZhuangSocre=m_CurrentBanker.lUserScore; 
// 	JettonChange.lKexiaSocre=m_CurrentBanker.lUserScore-(m_lTianMenScore+m_lDaoMenScore+m_lShunMenScore);
// 	//发送消息
// 	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));
// 	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_JETTON_CHANGE,&JettonChange,sizeof(JettonChange));
}

