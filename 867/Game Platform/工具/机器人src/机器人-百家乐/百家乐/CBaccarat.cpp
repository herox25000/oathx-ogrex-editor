#include "stdafx.h"
#include "CBaccarat.h"

//时间标识
#define IDI_PLACE_JETTON			100									//下注时间
#define IDI_APPLY_BANKER			101									//申请上庄
#define IDI_APPLY_NOT_BANKER		102									//申请下庄

#define JETTON_COUNT				7									//筹码数目

CBaccarat::CBaccarat(DWORD dwUserID)
:CGameBase(dwUserID)
{
	m_lCellScore=0;
	//下注信息
	m_lMeMaxScore=0L;
	m_lMeTieScore=0L;
	m_lMeBankerScore=0L;
	m_lMePlayerScore=0L;
	m_lMeTieSamePointScore=0L;
	m_lMePlayerKingScore=0L;
	m_lMeBankerKingScore=0L;

	//下注信息
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

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

	time_t seed = time(NULL);
	srand((unsigned)seed);
}

CBaccarat::~CBaccarat()
{
}

void CBaccarat::ResetGame()
{
	//下注信息
	m_lMeMaxScore=0L;
	m_lMeTieScore=0L;
	m_lMeBankerScore=0L;
	m_lMePlayerScore=0L;
	m_lMeTieSamePointScore=0L;
	m_lMePlayerKingScore=0L;
	m_lMeBankerKingScore=0L;

	//下注信息
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//历史信息
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//状态变量
	m_bMeApplyBanker = false;

	//庄家信息
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
}

void CBaccarat::OnPlaceJetton()
{
	m_JecVec.clear();
	for (int i = 0; i < 2; ++i)
	{
		BYTE cbJettonArea;
		//变量定义
		if (i == 0)
		{
			cbJettonArea = ID_ZHUANG_JIA;
		}
		else
		{
			cbJettonArea = ID_XIAN_JIA;
		}
		/*int nType = rand()%2;
		switch(nType)
		{
		case 0:
		{
			cbJettonArea=ID_ZHUANG_JIA;
			break;
		}
		case 1:
		{
			cbJettonArea=ID_XIAN_JIA;
			break;
		}
		}*/

		int nType2 = rand()%2;
		int nScore = 0;
		switch (nType2)
		{
		case 0:
			{
				nScore = 10000;
				break;
			}
		case 1:
			{
				nScore = 100000;
				break;
			}
		}

		if (m_bSmall)
		{
			if(rand()%10==1)
			{
				cbJettonArea = ID_PING_JIA;
			}

			switch(nType2)
			{
			case 0:
				{
					nScore = 100;
					break;
				}
			case 1:
				{
					nScore = 1000;
					break;
				}
			}
		}

		m_JecVec.push_back(tagJetInfo(cbJettonArea, nScore));
	}

	if (!m_JecVec.empty())
	{
		SetTimer(IDI_PLACE_JETTON, rand()%5000+1000, (DWORD)m_JecVec.size());
	}
}

__int64 CBaccarat::GetMaxPlayerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//其他区域
	__int64 lOtherAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore;

	//最大下注
	__int64 lMaxPlayerScore = lOtherAreaScore + m_lBankerTreasure;
	lMaxPlayerScore -= (m_lAllPlayerScore + m_lAllPlayerKingScore*2);

	return lMaxPlayerScore;
}

__int64 CBaccarat::GetMaxTieScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//返回积分
	__int64 lReturnScore = m_lAllTieSamePointScore * 33 + m_lAllTieScore * 8;

	//可下积分
	__int64 lMaxTieScore = (m_lBankerTreasure - lReturnScore)/8;

	return lMaxTieScore;
}

__int64 CBaccarat::GetMaxBankerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//其他区域
	__int64 lOtherAreaScore = m_lAllTieScore + m_lAllPlayerScore + m_lAllTieSamePointScore + m_lAllPlayerKingScore;

	//最大下注
	__int64 lMaxPlayerScore = lOtherAreaScore + m_lBankerTreasure;
	lMaxPlayerScore -= (m_lAllBankerScore + m_lAllBankerKingScore*2);

	return lMaxPlayerScore;
}

void CBaccarat::OnTimer(WORD wTimerID)
{
	switch(wTimerID)
	{
	case IDI_APPLY_BANKER:
		{
			if(m_ApplyBankerVec.size()<4 && m_lMeMaxScore >= 5000000 && m_wCurrentBanker == INVALID_CHAIR)
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

				if (!m_JecVec.empty())
				{
					JecVec::iterator iter = m_JecVec.begin();
					PlaceJetton.cbJettonArea = (*iter).cbJettonArea;
					PlaceJetton.lJettonScore = (*iter).lJettonScore;
					m_JecVec.erase(iter);
					BOOL bSend=TRUE;
					switch( PlaceJetton.cbJettonArea )
					{
					case ID_XIAN_JIA:
						{
							__int64 lMaxPlayerScore = GetMaxPlayerScore();
							if ( lMaxPlayerScore < PlaceJetton.lJettonScore )
								bSend = FALSE ;
							break;
						}
					case ID_PING_JIA:
						{
							__int64 lMaxPlayerScore = GetMaxTieScore();
							if ( lMaxPlayerScore < PlaceJetton.lJettonScore )
								bSend = FALSE ;
							break;
						}
					case ID_ZHUANG_JIA:
						{
							__int64 lMaxPlayerScore = GetMaxBankerScore();
							if ( lMaxPlayerScore < PlaceJetton.lJettonScore )
								bSend = FALSE ;
							break;
						}
					}
					if(bSend)
					{
						switch (PlaceJetton.cbJettonArea)
						{
						case ID_XIAN_JIA:
							{
								m_lMePlayerScore += PlaceJetton.lJettonScore;
								break;
							}
						case ID_PING_JIA:
							{
								m_lMeTieScore += PlaceJetton.lJettonScore;
								break;
							}
						case ID_ZHUANG_JIA:
							{
								m_lMeBankerScore += PlaceJetton.lJettonScore;
								break;
							}
						case ID_TONG_DIAN_PING:
							{
								m_lMeTieSamePointScore += PlaceJetton.lJettonScore;
								break;
							}
						case ID_XIAN_TIAN_WANG:
							{
								m_lMePlayerKingScore += PlaceJetton.lJettonScore;
								break;
							}
						case ID_ZHUANG_TIAN_WANG:
							{
								m_lMeBankerKingScore += PlaceJetton.lJettonScore;
								break;
							}
						}

						SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, &PlaceJetton, sizeof(PlaceJetton));
					}
				}
			}
			else
			{
				KillTimer(IDI_PLACE_JETTON);
			}
			break;
		}
	}
}

bool CBaccarat::OnGameMessage(WORD wSubCmdID, const void * pBuffer/* =NULL */, WORD wDataSize/* =0 */)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//游戏开始
		{
			m_bPlaying = true;
			break;
		}
	case SUB_S_PLACE_JETTON:	//用户加注
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_S_PlaceJetton));
			if (wDataSize!=sizeof(CMD_S_PlaceJetton)) return false;

			//消息处理
			CMD_S_PlaceJetton * pPlaceJetton=(CMD_S_PlaceJetton *)pBuffer;

			__int64 lScoreIndex[JETTON_COUNT]={100L,1000L,10000L,100000L,500000L,1000000L,5000000LL};

			switch ( pPlaceJetton->cbJettonArea )
			{
			case ID_XIAN_JIA:
				{ 
					m_lAllPlayerScore += pPlaceJetton->lJettonScore;
					break;
				}
			case ID_PING_JIA:
				{
					m_lAllTieScore += pPlaceJetton->lJettonScore;
					break;
				}
			case ID_ZHUANG_JIA:
				{ 
					m_lAllBankerScore += pPlaceJetton->lJettonScore;
					break;
				}
			case ID_XIAN_TIAN_WANG:
				{ 
					m_lAllPlayerKingScore += pPlaceJetton->lJettonScore;
					break;
				}
			case ID_ZHUANG_TIAN_WANG:
				{ 
					m_lAllBankerKingScore += pPlaceJetton->lJettonScore;
					break;
				}
			case ID_TONG_DIAN_PING:
				{ 
					m_lAllTieSamePointScore += pPlaceJetton->lJettonScore;
					break;
				}
			}
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

////				m_wCurrentBanker = pChangeBanker->wChairID;
////
//// 				if(m_ApplyBankerVec.empty()&&!m_bMeApplyBanker)
//// 				{
//// 					SetTimer(IDI_APPLY_BANKER, rand()%10000+5000, 1);
//// 					m_bMeApplyBanker = true;
//// 				}
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

			//if(m_bMeIsBanker == false && pChangeBanker->wChairID != INVALID_CHAIR)
			//{
			//	//this->OnPlaceJetton();
			//}
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

			//下注信息
			m_lAllTieScore=0L;			
			m_lAllBankerScore=0L;		
			m_lAllPlayerScore=0L;		
			m_lAllTieSamePointScore=0L;
			m_lAllBankerKingScore=0L;	
			m_lAllPlayerKingScore=0L;

			//设置变量
			m_lMeTieScore=0L;
			m_lMeBankerScore=0L;
			m_lMePlayerScore=0L;
			m_lMeTieSamePointScore = 0L;
			m_lMeBankerKingScore = 0L;
			m_lMePlayerKingScore = 0L;
			m_lMeMaxScore=pGameEnd->lMeMaxScore;
			m_lCellScore=pGameEnd->lCellScore;
			m_lBankerTreasure=pGameEnd->lBankerTreasure;

			if(m_lMeMaxScore<100000)//机器人银子少于10W就下线
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

			if(!m_bMeIsBanker)//如果不是庄家
			{
				if(m_wCurrentBanker == INVALID_CHAIR)
				{
					if(m_ApplyBankerVec.empty()&&!m_bMeApplyBanker)
					{
						SetTimer(IDI_APPLY_BANKER, rand()%15000+1000, 1);
					}
				}
				else
				{
					if(m_bMeApplyBanker==false)
					{
						this->OnPlaceJetton();
					}
				}
			}
			else
			{
				if(!m_bMeApplyBanker)
				{
					if(m_nBankerTimes>/*(rand()%10+6)*/8)//机器人最多做8次庄
					{
						SetTimer(IDI_APPLY_NOT_BANKER, 2000, 1);
						m_bMeApplyBanker = false;
					}
					if(m_lMeMaxScore<=1000000)//机器人银子少于100万，就自动下庄
					{
						SetTimer(IDI_APPLY_NOT_BANKER, 2000, 1);
						m_bMeApplyBanker = false;
					}
				}

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
			m_lMeTieScore=pGameScore->lMeTieScore;
			m_lMeBankerScore=pGameScore->lMeBankerScore;
			m_lMePlayerScore=pGameScore->lMePlayerScore;
			m_lMeTieSamePointScore = pGameScore->lMeTieKingScore;
			m_lMeBankerKingScore = pGameScore->lMeBankerKingScore;
			m_lMePlayerKingScore = pGameScore->lMePlayerKingScore;
			break;
		}
	}
	return true;
}

bool CBaccarat::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
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

			//玩家下注
 			m_lCellScore=pStatusFree->lCellScore;
			//设置变量
			m_lMeMaxScore= pStatusFree->lMeMaxScore;
			m_lMeTieScore=pStatusFree->lMeTieScore;
			m_lMeBankerScore=pStatusFree->lMeBankerScore;
			m_lMePlayerScore=pStatusFree->lMePlayerScore;
			m_lMeTieSamePointScore = pStatusFree->lMeTieKingScore;
			m_lMeBankerKingScore = pStatusFree->lMeBankerKingScore;
			m_lMePlayerKingScore = pStatusFree->lMePlayerKingScore;
 
 			//庄家信息
			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;
			m_lBankerScore = pStatusFree->lBankerKingScore;
			m_lBankerTreasure = pStatusFree->lBankerTreasure;
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
			m_lMeMaxScore=pStatusPlay->lMeMaxScore;
			m_lMeTieScore=pStatusPlay->lMeTieScore;
			m_lMeBankerScore=pStatusPlay->lMeBankerScore;
			m_lMePlayerScore=pStatusPlay->lMePlayerScore;
			m_lMeTieSamePointScore = pStatusPlay->lMeTieKingScore;
			m_lMeBankerKingScore = pStatusPlay->lMeBankerKingScore;
			m_lMePlayerKingScore = pStatusPlay->lMePlayerKingScore;
 
			//庄家信息
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			m_lBankerScore = pStatusPlay->lBankerKingScore;
			m_lBankerTreasure = pStatusPlay->lBankerTreasure;

			return true;
		}
	}

	return false;
}
