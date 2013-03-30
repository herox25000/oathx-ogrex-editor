#include "StdAfx.h"
#include ".\smallninemachine.h"
#include "RobotManager.h"
#include "RobotTimer.h"
#include "BankerManager.h"

SmallNineMachine::SmallNineMachine(DWORD dwUserID) 
	: IRobot(dwUserID), m_fOnlineTime(0), m_fCurOnlineTime(0)
{
	ResetGame();
}

SmallNineMachine::~SmallNineMachine(void)
{

}

void			SmallNineMachine::ResetGame()
{
	m_wCurBanker			= INVALID_CHAIR;
	m_nMeMaxScore			= 0;
	m_wUpBankerCount		= 0;
	m_fElapsedTime			= 0;
	m_fAddJettonTime		= RobotTimer::rdft(1, 3);
	m_bAddJetton			= FALSE;
	m_nApplyBankerCondition	= 0;
	m_bStart				= 0;
	m_nMePlaceScore			= 0;
	m_nMeWinScore			= 0;
	
}

void			SmallNineMachine::SetOnlineTime(double fOnlineTime)
{
	m_fOnlineTime = fOnlineTime;
}

bool			SmallNineMachine::SendApplyBanker(bool bUp)
{
	if (m_bStart == false)
		return 0;

	// 获取庄配置
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();	
	// 当前申请坐庄的总人数
	int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();

	if (bUp)
	{
		int nApplyBankerCount	= BankerManager::GetSingleton().GetLockCount();
		if ((nReqBanker + nApplyBankerCount) < config.wUpBankerDeque  && m_nMeMaxScore >= m_nApplyBankerCondition)
		{
			BankerManager::GetSingleton().Lock();

			// 申请坐庄
			CMD_C_ApplyBanker req;
			req.bApplyBanker	= true;

			//发送消息
			SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
		}
	}
	else
	{
		// 申请坐庄
		CMD_C_ApplyBanker req;
		req.bApplyBanker	= 0;

		//发送消息
		SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
	}

	return true;
}

INT64			SmallNineMachine::GetRandScore(__int64 nLeftJettonScore)
{
	// 获取庄配置
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();
	float nTenMillionRate = 0, nFiveMillionRate = 0, nOneMillionRate = 0, nFiveLakhRate = 0, nTenLakhRate = 0, nOneW = 0, nOneQ = 0;

	if (nLeftJettonScore >= 10000000)
		nTenMillionRate = 10000000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 5000000)
		nFiveMillionRate = 5000000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 1000000)
		nOneMillionRate = 1000000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 500000)
		nFiveLakhRate = 500000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 100000)
		nTenLakhRate = 100000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 10000)
		nOneW = 10000.0 / nLeftJettonScore * 100;
	if (nLeftJettonScore >= 1000)
		nOneQ = 1000.0 / nLeftJettonScore * 100;

	float nTotal = nTenMillionRate + nFiveMillionRate + nOneMillionRate + nFiveLakhRate + nTenLakhRate + nOneW + nOneQ;
	nTenMillionRate = nTenMillionRate / nTotal * 100;
	nFiveMillionRate = nFiveMillionRate / nTotal * 100;
	nFiveLakhRate = nFiveLakhRate / nTotal * 100;
	nOneMillionRate = nOneMillionRate / nTotal * 100;
	nTenLakhRate = nTenLakhRate / nTotal * 100;
	nOneW = nOneW / nTotal * 100;
	nOneQ = nOneQ / nTotal * 100;

	// 随机压住金币
	static __int64 JScore[] = 
	{
		1000, 10000, 100000, 500000, 1000000, 5000000, 10000000
	};

	float JettonRate[] = { nTenMillionRate, nFiveMillionRate, nFiveLakhRate, nOneMillionRate, nTenLakhRate, nOneW, nOneQ };

	float nRandRate = RobotTimer::rdft(0, 100);
	int nCurIndex = 0;

	float nFlase = 0;
	for (int i = 0; i < 7; i++)
	{
		if (nRandRate < nFlase + JettonRate[i])
		{
			nCurIndex = 6 - i;
			break;
		}
		nFlase += JettonRate[i];
	}
	return JScore[nCurIndex];
}

//游戏状态
bool			SmallNineMachine::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE:			//空闲状态
		{
			if (wDataSize != sizeof(CMD_S_StatusFree)) 
				return 0;
			
			m_bStart = TRUE;

			//消息处理
			CMD_S_StatusFree* pStatusFree=(CMD_S_StatusFree *)pBuffer;
			if (pStatusFree)
			{
				m_nJettonTime			= pStatusFree->cbTimeLeave;
				m_nApplyBankerCondition	= pStatusFree->lApplyBankerCondition;
				// 当前庄积分
				m_nBankerScore			= pStatusFree->lBankerTreasure;
				// 自己积分
				m_nMeMaxScore			= pStatusFree->lMeMaxScore;
				
				// 更新当前庄ID
				m_wCurBanker			= pStatusFree->wCurrentBankerChairID;
				if (m_wCurBanker != INVALID_CHAIR)
				{
					tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
					if (pUserInfo != NULL && pUserInfo->dwUserID != m_dwUserID)
					{
						m_bAddJetton = TRUE;
					}
				}
			}

		}
		return true;
	case GS_PLAYING:		//游戏状态
		{
			if (wDataSize != sizeof(CMD_S_StatusPlay))
				return 0;

			m_bStart = TRUE;

			//消息处理
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;
			if (pStatusPlay)
			{
				m_nJettonTime			= pStatusPlay->cbTimeLeave;
				m_nApplyBankerCondition	= pStatusPlay->lApplyBankerCondition;
				m_nBankerScore			= pStatusPlay->lBankerTreasure;
				m_nMeMaxScore			= pStatusPlay->lMeMaxScore;
				m_wCurBanker			= pStatusPlay->wCurrentBankerChairID;

				if (m_wCurBanker != INVALID_CHAIR)
				{
					tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
					if (pUserInfo != NULL && pUserInfo->dwUserID != m_dwUserID)
					{
						m_bAddJetton = TRUE;
					}
				}
			}
		}
		return true;
	}

	return false;
}

void			SmallNineMachine::OnUpdate(float fElapsed)
{
	// 获取庄配置
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();
	
	// 判断机器人当前在线时间
	m_fCurOnlineTime += fElapsed;
	if ((m_fCurOnlineTime / 60) >= m_fOnlineTime)
	{
		// 检查当前机器人是否是庄
		if (m_wCurBanker != INVALID_CHAIR)
		{
			tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
			if (pUserInfo)
			{
				// 如果自己是庄，但是已到在线时间，那么重新随机在线时间
				if (pUserInfo->dwUserID == m_dwUserID || BankerManager::GetSingleton().Search(m_dwUserID))
				{
					m_fOnlineTime	= RobotTimer::rdft(config.fMinOnlineTime / 2, config.fMaxPlaceTime / 2);
					m_fCurOnlineTime= 0;
				}
				else
				{
					// 当前玩家没有下分
					if (m_nMePlaceScore <= 0)
					{
						CString szMessage;
						szMessage.Format("Robot[%d] Has arrived online time, offline", pUserInfo->dwUserID);
						ShowMessageBox(szMessage, TraceLevel_Debug);

						SetState(ROBOT_INVALID);
					}
				}
			}
		}
	}

	// 更新加注信息
	if ( m_bAddJetton && m_wCurBanker != INVALID_CHAIR)
	{
		float nPlaceRand = m_nJettonTime * 100 / MAX_PLACE_JETTON_TIME;
		if (nPlaceRand < 10)
		{
			m_bAddJetton = FALSE;
			return;
		}
		float nRnd = RobotTimer::rdft(0, 100);
		m_nJettonTime -= fElapsed;
		if (nRnd <= nPlaceRand)
		{
			m_fElapsedTime		+= fElapsed;
			
			// 已经到压注条件
			if (m_fElapsedTime >= m_fAddJettonTime)
			{
				CMD_C_PlaceJetton PlaceJetton;
				ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));
				
				PlaceJetton.cbJettonArea = GetRandArea();
				__int64 nLeftScore = m_nMeMaxScore * config.nPlaceMaxRate / 100 - m_nMePlaceScore;
				PlaceJetton.lJettonScore = GetRandScore(nLeftScore);

				if (m_nMeMaxScore >= PlaceJetton.lJettonScore)
				{
					WORD nPlaceRate = (m_nMePlaceScore + PlaceJetton.lJettonScore) / m_nMeMaxScore * 100;
					if (nPlaceRate < config.nPlaceMaxRate)
					{
						// 发送押注消息
						SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, 
							&PlaceJetton, sizeof(PlaceJetton));

						// 增加自己压的钱
						m_nMePlaceScore += PlaceJetton.lJettonScore;
					}
				}

				m_fAddJettonTime	= RobotTimer::rdit(config.fMinPlaceTime, config.fMaxPlaceTime);
				m_fElapsedTime		= 0;
			}

		}

	}
}

//游戏消息
bool			SmallNineMachine::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//游戏开始
		{
			if (m_bStart)
			{
				// 获取庄配置
				const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();	
				// 当前申请坐庄的总人数
				int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();

				if (m_wCurBanker != INVALID_CHAIR)
				{
					tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
					if (pUserInfo)
					{
						// 如果当前庄不是自己
						if (pUserInfo->dwUserID != m_dwUserID)
						{
							// 强制申请上祖昂
							SendApplyBanker(true);

							// 设置押注启动
							m_bAddJetton = TRUE;
						}
					}
				}
			}
		}
		break;

	case SUB_S_PLACE_JETTON:	//用户加注
		{
			
		}
		break;

	case SUB_S_APPLY_BANKER:	//申请做庄
		{
			if (wDataSize!=sizeof(CMD_S_ApplyBanker)) 
				return 0;

			//消息处理
			CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;

			//查找该用户
			tagUserInfo* pUserInfo = m_pGameManager->Search(
				pApplyBanker->szAccount);
			if (pUserInfo)
			{
				if (pUserInfo->dwUserID == m_dwUserID)
				{
					BankerManager::GetSingleton().Unlock();
				}
			
				// 处理上庄队列
				if (pApplyBanker->bApplyBanker)
				{
					BankerManager::GetSingleton().AddUser(pUserInfo);
				}
				else
				{
					BankerManager::GetSingleton().Remove(pUserInfo->dwUserID);
				}
			}
		}
		break;
	case SUB_S_CHANGE_BANKER:	//切换庄家
		{
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) 
				return 0;

			//消息处理
			CMD_S_ChangeBanker* pChangeBanker	= (CMD_S_ChangeBanker *)pBuffer;
			m_wCurBanker						= pChangeBanker->wChairID;
			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo && pUserInfo->dwUserID != m_dwUserID)
				{
					m_bAddJetton = TRUE;
				}
			}
		}
		break;

	case SUB_S_CHANGE_USER_SCORE://更新积分
		{
			
		}
		break;
	case SUB_S_GAME_END:		//游戏结束
		{
			if (wDataSize != sizeof(CMD_S_GameEnd)) 
				return 0;

			//消息处理
			CMD_S_GameEnd* pGameEnd	=(CMD_S_GameEnd *)pBuffer;

			// 更新数据
			m_nJettonTime			= pGameEnd->cbTimeLeave;
			m_nMeMaxScore			= pGameEnd->lMeMaxScore;
			m_nBankerWinScore		= pGameEnd->lBankerTotalScore;

			// 获取庄配置
			const SBankerConfig& c	= RobotManager::GetSingleton().GetBankerConfig();	
			// 当前申请坐庄的总人数
			int nReqBanker			= BankerManager::GetSingleton().GetBankerCount();

			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo)
				{
					if (pUserInfo->dwUserID == m_dwUserID)
					{
						// 增加上庄次数
						m_wUpBankerCount ++;

						// 如果上庄次数大于了随机值就请求下庄, 默认情况下机器人每次上庄最少都会做两次庄
						if (m_wUpBankerCount >= RobotTimer::rdit(1, c.wUpBankerCount > 1 ? c.wUpBankerCount : 1))
						{
							SendApplyBanker(false);
						}
						else if (m_nBankerWinScore > 0)
						{
							int nRate = m_nBankerWinScore * 100 / c.nMaxWinScore;
							if (rand() % 100 < nRate)
							{
								SendApplyBanker(false);
							}
						}
						else if (m_nBankerWinScore < 0 && m_nBankerWinScore <= (-c.nUpBankerLoseScore))
						{
							SendApplyBanker(false);
						}
					}
				}
			}
		
			// 每局游戏结束后，查询当前排庄队列中是有自己，若没有则申请上庄
			SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
			if (!pUserInfo)
			{
				SendApplyBanker(true);
			}
			
			// 重置机器人当前压的钱
			m_nMePlaceScore			= 0;
			
			// 若机器人的金钱少于最小积分
			if (m_nMeMaxScore <= c.nMinScore)
			{
				// 移除排庄队列中的自己
				BankerManager::GetSingleton().Remove(m_dwUserID);

				CString szMessage;
				szMessage.Format("Robot[%d] Gold less than %I64 automatic logoff", m_dwUserID, c.nMinScore);
				ShowMessageBox(szMessage, TraceLevel_Warning);
				
				// 设置机器人断线
				SetState(ROBOT_INVALID);
			}
		}
		break;
	case SUB_S_SEND_RECORD:		//游戏记录
		{
			
		}
		break;
	case SUB_S_GAME_SCORE:		//游戏积分
		{
			if (wDataSize!=sizeof(CMD_S_GameScore)) 
				return 0;

			//消息处理
			CMD_S_GameScore* pGameScore = (CMD_S_GameScore *)pBuffer;
			if (pGameScore)
			{
				m_nMeWinScore += pGameScore->lMeGameScore;
			}
		}
		break;
	}
	return true;
}

BYTE SmallNineMachine::GetRandArea()
{
	// 获取庄配置
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();
	int nTotal = config.nShunMenRate + config.nTianMenRate + config.nDaoMenRate + config.nZuoJiaoRate + config.nYouJiaoRate + config.nQiaoRate;
	int nShunRate = config.nShunMenRate * 100 / nTotal;
	int nTianRate = config.nTianMenRate * 100 / nTotal;
	int nDaoRate = config.nDaoMenRate * 100 / nTotal;
	int nZuoJiao = config.nZuoJiaoRate * 100 / nTotal;
	int nYouJiao = config.nYouJiaoRate * 100 / nTotal;
	int nQiao = config.nQiaoRate * 100 / nTotal;
	// 随机压注门
	static BYTE cbArea[] = {
		ID_SHUN_MEN,
		ID_TIAN_MEN,
		ID_DAO_MEN,
		ID_ZUO_JIAO,
		ID_YOU_JIAO,
		ID_QIAO
	};
	int nRandRate = rand() % 100;
	int nCurIndex = 0;

	if (nRandRate>= 0 && nRandRate <= nShunRate)
	{
		nCurIndex = 0;
	}
	else if (nRandRate > nShunRate && nRandRate <= nTianRate + nShunRate)
	{
		nCurIndex = 1;
	}
	else if (nRandRate > nTianRate + nShunRate && nRandRate <= nTianRate + nShunRate + nDaoRate)
	{
		nCurIndex = 2;
	}
	else if (nRandRate > nTianRate + nShunRate + nDaoRate && nRandRate <= nTianRate + nShunRate + nDaoRate + nZuoJiao)
	{
		nCurIndex = 3;
	}
	else if (nRandRate > nTianRate + nShunRate + nDaoRate + nZuoJiao && nRandRate <= nTianRate + nShunRate + nDaoRate + nZuoJiao + nYouJiao)
	{
		nCurIndex = 4;
	}
	else if (nRandRate >nTianRate + nShunRate + nDaoRate + nZuoJiao + nYouJiao && nRandRate <= nTianRate + nShunRate + nDaoRate + nZuoJiao + nYouJiao + nQiao)
	{
		nCurIndex = 5;
	}
	else
	{
		nCurIndex = rand()%6;
	}
	return cbArea[nCurIndex];
}

