#include "stdafx.h"
#include "CXiaoJiu.h"

//时间标识
#define IDI_PLACE_JETTON			100									//下注时间
#define IDI_APPLY_BANKER			101									//申请上庄
#define IDI_APPLY_NOT_BANKER		102									//申请下庄

CPaiJiu::CPaiJiu(DWORD dwUserID)
:CGameBase(dwUserID)
{

	//历史信息
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//状态变量
	m_bPlaying = false;


	//庄家信息
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
	m_bMeApplyBanker = false;

	m_bMeIsBanker = false;
	m_nBankerTimes = 0;
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	//下注信息
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	time_t seed = time(NULL);
	srand((unsigned)seed);
}

CPaiJiu::~CPaiJiu()
{
}

void CPaiJiu::ResetGame()
{
	//下注信息

	//历史信息
	m_wDrawCount=1;
	m_lMeResultCount=0;
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	//下注信息
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//状态变量
	m_bMeApplyBanker = false;

	//庄家信息
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
}

void CPaiJiu::OnPlaceJetton()
{
	SetTimer(IDI_PLACE_JETTON, rand()%20000+1000, 1);
}

//最大下注
__int64 CPaiJiu::GetMaxPlayerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//其他区域
	__int64 lAllAreaScore = m_lAllTieScore + 
		m_lAllTieSamePointScore + 
		m_lAllBankerScore+ 
		m_lAllBankerKingScore+
		m_lAllPlayerScore+
		m_lAllPlayerKingScore;

	//最大下注
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//最大下注
__int64 CPaiJiu::GetMaxPlayerKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//其他区域
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;

	//最大下注
	__int64 lMaxPlayerScore = m_lBankerTreasure-lAllAreaScore;
	return lMaxPlayerScore;
}

//最大下注
__int64 CPaiJiu::GetMaxBankerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//其他区域
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;


	//最大下注
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//最大下注
__int64 CPaiJiu::GetMaxBankerKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;
	//其他区域
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;

	//最大下注
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//最大下注
__int64 CPaiJiu::GetMaxTieScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	__int64 lMaxTieScore = lMaxPlayerScore;

	return lMaxTieScore;
}

//最大下注
__int64 CPaiJiu::GetMaxTieKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;
	//返回积分
	__int64 lMaxTieScore = lMaxPlayerScore;

	return lMaxTieScore;
}

void CPaiJiu::OnTimer(WORD wTimerID)
{
	switch(wTimerID)
	{
	case IDI_APPLY_BANKER:
		{
			if(m_ApplyBankerVec.size()<4 &&  m_lMeMaxScore >= 5000000&& m_wCurrentBanker == INVALID_CHAIR)
			{
				m_bMeApplyBanker = true;
				CMD_C_ApplyBanker ApplyBanker;
				ApplyBanker.bApplyBanker = true;

				//发送消息
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
			}
			break;
		}
	case IDI_APPLY_NOT_BANKER:
		{
			if(m_wCurrentBanker != INVALID_CHAIR)
			{
				CMD_C_ApplyBanker ApplyBanker;
				ApplyBanker.bApplyBanker = false;

				//发送消息
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &ApplyBanker, sizeof( ApplyBanker ) );
			}
			break;
		}
	case IDI_PLACE_JETTON:
		{	
			if(!m_bPlaying)
			{
				CMD_C_PlaceJetton PlaceJetton;
				ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

				switch(rand()%3)
				{
				case 0:
					{
						PlaceJetton.cbJettonArea = ID_SHUN_MEN;
						break;
					}
				case 1:
					{
						PlaceJetton.cbJettonArea = ID_TIAN_MEN;
						break;
					}
				case 2:
					{
						PlaceJetton.cbJettonArea = ID_DAO_MEN;
						break;
					}
				}

				static __int64 JScore[] = 
				{
					1000, 10000, 100000, 500000, 1000000, 5000000
				};
				
				PlaceJetton.lJettonScore = JScore[rand() % 6];
				//switch(rand()%4)
				//{
				//case 0:
				//	{
				//		PlaceJetton.lJettonScore = 100;
				//		break;
				//	}
				//case 1:
				//	{
				//		PlaceJetton.lJettonScore = 1000;
				//		break;
				//	}
				//case 2:
				//	{
				//		PlaceJetton.lJettonScore = 10000;
				//		break;
				//	}
				//case 3:
				//	{
				//		PlaceJetton.lJettonScore = 100000;
				//		break;
				//	}
				//}
				BOOL bSend=TRUE;
				switch( PlaceJetton.cbJettonArea )
				{
				case ID_SHUN_MEN:
					{
						__int64 lMaxPlayerScore = GetMaxPlayerScore();
						if ( lMaxPlayerScore < PlaceJetton.lJettonScore )
							bSend=FALSE ;
						break;
					}
				case ID_TIAN_MEN:
					{
						__int64 lMaxTieScore  = GetMaxTieScore();
						if ( lMaxTieScore < PlaceJetton.lJettonScore )
							bSend=FALSE ;
						break;
					}
				case ID_DAO_MEN:
					{
						__int64 lMaxBankerScore = GetMaxBankerScore();
						if ( lMaxBankerScore < PlaceJetton.lJettonScore )
							bSend=FALSE ;
						break;
					}
				}

				if(bSend)
				{
					switch (PlaceJetton.cbJettonArea)
					{
					case ID_SHUN_MEN:
						{
							m_lMeShunMenScore += PlaceJetton.lJettonScore;
							break;
						}
					case ID_TIAN_MEN:
						{
							m_lMeTianMenScore += PlaceJetton.lJettonScore;
							break;
						}
					case ID_DAO_MEN:
						{
							m_lMeDaoMenScore += PlaceJetton.lJettonScore;
							break;
						}
					}

					SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, &PlaceJetton, sizeof(PlaceJetton));
				}
			}
			break;
		}
	}
} 

bool CPaiJiu::OnGameMessage(WORD wSubCmdID, const void * pBuffer/* =NULL */, WORD wDataSize/* =0 */)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//游戏开始
		{
			m_bPlaying = true;

			if(!m_bMeIsBanker)
			{
				if(m_wCurrentBanker == INVALID_CHAIR)
				{
					if(m_ApplyBankerVec.empty()&&!m_bMeApplyBanker)
					{
						SetTimer(IDI_APPLY_BANKER, rand()%15000+5000, 1);
					}
				}
			}
			else
			{
				if(!m_bMeApplyBanker)
				{
					if(m_nBankerTimes>(rand()%10+6))
					{
						SetTimer(IDI_APPLY_NOT_BANKER, 6000, 1);
						m_bMeApplyBanker = true;
					}
				}
			}

			break;
		}
	case SUB_S_PLACE_JETTON:	//用户加注
		{
			break;
		}
	case SUB_S_APPLY_BANKER:	//申请做庄
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_ApplyBanker));
			if (wDataSize!=sizeof(CMD_S_ApplyBanker)) return false;

			//消息处理
			CMD_S_ApplyBanker * pApplyBanker=(CMD_S_ApplyBanker *)pBuffer;
		
			//插入玩家
			if ( pApplyBanker->bApplyBanker )
			{
				//插入判断
				bool bInsertApplyUser = true;

				if ( m_wCurrentBanker != INVALID_CHAIR )
				{
					tagUserInfo *pBankerUserInfo = m_GameUserManager.SearchUserByChairID(m_wCurrentBanker);
					if(pBankerUserInfo&&0==lstrcmp(pBankerUserInfo->szName, pApplyBanker->szAccount))
					{
						bInsertApplyUser = false;
					}
				}

				tagUserInfo *pUserInfo = m_GameUserManager.SearchUserByName(pApplyBanker->szAccount);
				if(bInsertApplyUser)
				{
					if(pUserInfo)
					{
						m_ApplyBankerVec.push_back(pUserInfo);
					}
				}
			}
			else
			{
				tagUserInfo *pUserInfo = m_GameUserManager.SearchUserByName(pApplyBanker->szAccount);
				if(pUserInfo)
				{
					for(UserVec::iterator iter = m_ApplyBankerVec.begin();
						iter != m_ApplyBankerVec.end();++iter)
					{
						if(*iter&&(*iter)->dwUserID == pUserInfo->dwUserID)
						{
							m_ApplyBankerVec.erase(iter);
							break;
						}
					}
				}
			}
			break;
		}
	case SUB_S_CHANGE_BANKER:	//切换庄家
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_ChangeBanker));
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) return false;

			//消息处理
			CMD_S_ChangeBanker * pChangeBanker=(CMD_S_ChangeBanker *)pBuffer;

			tagUserInfo *pUserInfo = m_GameUserManager.SearchUserByChairID(m_wCurrentBanker);

			if(m_wCurrentBanker != INVALID_CHAIR && pChangeBanker->wChairID == INVALID_CHAIR)
			{
				if(pUserInfo)
				{
					for(UserVec::iterator iter = m_ApplyBankerVec.begin();
						iter != m_ApplyBankerVec.end();++iter)
					{
						if(*iter&&(*iter)->dwUserID == pUserInfo->dwUserID)
						{
							m_ApplyBankerVec.erase(iter);
							break;
						}
					}
				}

				if(pUserInfo->dwUserID == m_MeUserInfo.dwUserID)
				{
					m_bMeApplyBanker = false;
					m_bMeIsBanker = false;
					m_nBankerTimes = 0;
				}
			}

			m_wCurrentBanker = pChangeBanker->wChairID;

			//删除玩家
			if ( m_wCurrentBanker != INVALID_CHAIR )
			{
				tagUserInfo *pUserInfo = m_GameUserManager.SearchUserByChairID(pChangeBanker->wChairID);
				if(pUserInfo)
				{
					for(UserVec::iterator iter = m_ApplyBankerVec.begin();
						iter != m_ApplyBankerVec.end();++iter)
					{
						if(*iter&&(*iter)->dwUserID == pUserInfo->dwUserID)
						{
							m_ApplyBankerVec.erase(iter);
							break;
						}
					}
				}
				if(pUserInfo->dwUserID == m_MeUserInfo.dwUserID)
				{
					m_bMeApplyBanker = false;
					m_bMeIsBanker = true;
					m_nBankerTimes = 0;
				}
				else
				{
					m_bMeIsBanker = false;
				}
			}

			if(m_bMeIsBanker == false && pChangeBanker->wChairID != INVALID_CHAIR)
			{
//				this->OnPlaceJetton();
			}
			break;
		}
	case SUB_S_CHANGE_USER_SCORE://更新积分
		{
			break;
		}
	case SUB_S_GAME_END:		//游戏结束
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
			if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

			//消息处理
			CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

			m_bPlaying = false;

			m_lMeMaxScore=pGameEnd->lMeMaxScore;
			m_lMeTianMenScore=0L;
			m_lMeDaoMenScore=0L;
			m_lMeShunMenScore=0L;
			m_lMeQiaoScore=0L;
			m_lMeZuoJiaoScore=0L;
			m_lMeYouJiaoScore=0L;

			//下注信息
			m_lAllTieScore=0L;			
			m_lAllBankerScore=0L;		
			m_lAllPlayerScore=0L;		
			m_lAllTieSamePointScore=0L;
			m_lAllBankerKingScore=0L;	
			m_lAllPlayerKingScore=0L;

			//下注信息
			m_lBankerTreasure=pGameEnd->lBankerTreasure;

			if(m_lMeMaxScore<100000)
			{
				CString strMsg;
				strMsg.Format("%d 金钱少于10万，自动下线！", m_MeUserInfo.dwUserID);
				ShowMessageBox(strMsg);
				EndServer();
				return false;
			}

			//状态更新
			if(m_bMeIsBanker)
			{
				++m_nBankerTimes;
			}

			if(!m_bMeIsBanker && m_wCurrentBanker != INVALID_CHAIR)
			{
				this->OnPlaceJetton();
			}

			break;
		}
	case SUB_S_SEND_RECORD:		//游戏记录
		{
			break;
		}
	case SUB_S_GAME_SCORE:		//游戏积分
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_GameScore));
			if (wDataSize!=sizeof(CMD_S_GameScore)) return false;

			//消息处理
			CMD_S_GameScore * pGameScore=(CMD_S_GameScore *)pBuffer;

			m_lMeResultCount+=pGameScore->lMeGameScore;

			//设置变量
			m_lMeTianMenScore=pGameScore->lMeTieScore;
			m_lMeDaoMenScore=pGameScore->lMeBankerScore;
			m_lMeShunMenScore=pGameScore->lMePlayerScore;
			m_lMeQiaoScore = pGameScore->lMeTieKingScore;
			m_lMeYouJiaoScore = pGameScore->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pGameScore->lMePlayerKingScore;
			break;
		}
	}
	return true;
}

bool CPaiJiu::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
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
 
 			//庄家信息
			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;
			m_lBankerScore = pStatusFree->lBankerKingScore;
			m_lBankerTreasure = pStatusFree->lBankerTreasure;
			//设置变量
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			//设置变量
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			m_lMeTianMenScore=pStatusFree->lMeTieScore;
			m_lMeDaoMenScore=pStatusFree->lMeBankerScore;
			m_lMeShunMenScore=pStatusFree->lMePlayerScore;
			m_lMeQiaoScore = pStatusFree->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusFree->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusFree->lMePlayerKingScore;
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
 
			//庄家信息
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			m_lBankerScore = pStatusPlay->lBankerKingScore;
			m_lBankerTreasure = pStatusPlay->lBankerTreasure;
			//设置变量
			m_lMeMaxScore=pStatusPlay->lMeMaxScore;
			m_lMeMaxScore=pStatusPlay->lMeMaxScore ;
			m_lMeTianMenScore=pStatusPlay->lMeTieScore;
			m_lMeDaoMenScore=pStatusPlay->lMeBankerScore;
			m_lMeShunMenScore=pStatusPlay->lMePlayerScore;
			m_lMeQiaoScore = pStatusPlay->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusPlay->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusPlay->lMePlayerKingScore;

			return true;
		}
	}

	return false;
}
