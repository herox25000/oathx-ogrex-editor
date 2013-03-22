#include "StdAfx.h"
#include ".\smallninemachine.h"
#include "RobotManager.h"
#include "RobotTimer.h"
#include "BankerManager.h"

SmallNineMachine::SmallNineMachine(DWORD dwUserID) : IRobot(dwUserID)
{
	m_wCurBanker		= INVALID_CHAIR;
	m_bMeBanker			= FALSE;
	m_nMeMaxScore		= 0;
	m_wUpBankerCount	= 0;
	m_fElapsedTime		= 0;
	m_fAddJettonTime	= RobotTimer::rdft(1, 3);
	m_bAddJetton		= FALSE;
}

SmallNineMachine::~SmallNineMachine(void)
{

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

			//消息处理
			CMD_S_StatusFree* pStatusFree=(CMD_S_StatusFree *)pBuffer;
			if (pStatusFree)
			{
				// 当前庄积分
				m_nBankerScore	= pStatusFree->lBankerTreasure;
				// 自己积分
				m_nMeMaxScore	= pStatusFree->lMeMaxScore;
				
				// 更新当前庄ID
				m_wCurBanker	= pStatusFree->wCurrentBankerChairID;
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

			//消息处理
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;
			if (pStatusPlay)
			{
				// 当前庄积分
				m_nBankerScore	= pStatusPlay->lBankerTreasure;
				// 自己积分
				m_nMeMaxScore	= pStatusPlay->lMeMaxScore;
				// 更新当前庄ID
				m_wCurBanker	= pStatusPlay->wCurrentBankerChairID;
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
	// 当前申请坐庄的总人数
	int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();
	if (m_wCurBanker == INVALID_CHAIR || nReqBanker < config.wUpBankerDeque)
	{
		// 查询当前自己是否已经在排庄
		SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
		if (pUserInfo == NULL && !BankerManager::GetSingleton().IsLock())
		{
			if (m_nMeMaxScore >= config.nUpBankerScore)
			{
				BankerManager::GetSingleton().Lock();

				// 申请坐庄
				CMD_C_ApplyBanker req;
				req.bApplyBanker	= true;
				
				//发送消息
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}
	}
	else
	{
		// 检查下庄
		SUserInfo* pCurBanker	= m_pGameManager->Search(m_wCurBanker);
		if (pCurBanker->dwUserID == m_dwUserID)
		{
			if (m_wUpBankerCount >= config.wUpBankerCount)
			{
				// 申请下庄
				CMD_C_ApplyBanker req;
				req.bApplyBanker = 0;

				//发送消息
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}

		// 如果当前排庄人数少于配置，那么继续申请坐庄
		SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
		if (nReqBanker < config.wUpBankerDeque + 1 && !BankerManager::GetSingleton().IsLock())
		{
			if (m_nMeMaxScore >= config.nUpBankerScore)
			{
				BankerManager::GetSingleton().Lock();

				CString szMessage;
				szMessage.Format("Robot[%d] request banker", m_dwUserID);
				ShowMessageBox(szMessage);
				// 申请坐庄
				CMD_C_ApplyBanker req;
				req.bApplyBanker =	 true;

				//发送消息
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}
	}

	// 更新加注信息
	if ( m_bAddJetton )
	{
		m_fElapsedTime		+= fElapsed;
		
		// 已经到压注条件
		if (m_fElapsedTime >= m_fAddJettonTime)
		{
			CMD_C_PlaceJetton PlaceJetton;
			ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

			// 随机压注门
			static BYTE cbArea[] = {
				ID_SHUN_MEN,
				ID_TIAN_MEN,
				ID_DAO_MEN,
			};
			
			PlaceJetton.cbJettonArea = cbArea[rand() % 3];

			// 随机压住金币
			static __int64 JScore[] = 
			{
				1000, 10000, 100000, 500000, 1000000, 5000000, 10000000
			};

			int nRandRate = rand() % 100;
			int nCurIndex = 0;

			if (nRandRate>= 0 && nRandRate <= config.nTenMillionRate)
			{
				nCurIndex = 6;
			}
			else if (nRandRate > config.nTenMillionRate && nRandRate <= config.nFiveMillionRate)
			{
				nCurIndex = 5;
			}
			else if (nRandRate > config.nFiveMillionRate && nRandRate <= config.nOneMillionRate)
			{
				nCurIndex = 4;
			}
			else if (nRandRate > config.nOneMillionRate && nRandRate <= config.nFiveLakhRate)
			{
				nCurIndex = 3;
			}
			else if (nRandRate > config.nFiveLakhRate && nRandRate <= config.nTenLakhRate)
			{
				nCurIndex = 2;
			}
			else
			{
				nCurIndex = rand() % 2;
			}

			PlaceJetton.lJettonScore = JScore[nCurIndex];
			if (m_nMeMaxScore >= PlaceJetton.lJettonScore)
			{
				SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, &PlaceJetton, sizeof(PlaceJetton));
			}
			m_fAddJettonTime	= RobotTimer::rdit(config.fMinPlaceTime, config.fMaxPlaceTime);
			m_fElapsedTime		= 0;
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
			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo != NULL && pUserInfo->dwUserID != m_dwUserID)
				{
					m_bAddJetton = TRUE;
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

			// 获取庄家配置
			const SBankerConfig& c = RobotManager::GetSingleton().GetBankerConfig();

			CString szMessage;
			//消息处理
			CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;
			if (pApplyBanker->bApplyBanker)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_dwUserID);
				if (pUserInfo && !strcmp(pUserInfo->szName, pApplyBanker->szAccount))
				{
					BankerManager::GetSingleton().AddUser(pUserInfo);
					BankerManager::GetSingleton().Unlock();
				}
			}
			else
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(pApplyBanker->szAccount);
				if (pUserInfo)
				{
					if (pUserInfo->dwUserID == m_dwUserID)
					{	
						m_wUpBankerCount = 0;
						
						BankerManager::GetSingleton().Unlock();
					}

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
			CMD_S_ChangeBanker* pChangeBanker = (CMD_S_ChangeBanker *)pBuffer;

			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo)
				{
					BankerManager::GetSingleton().Remove(pUserInfo->dwUserID);
				}
			}

			m_wCurBanker = pChangeBanker->wChairID;
		}
		break;

	case SUB_S_CHANGE_USER_SCORE://更新积分
		{
			
		}
		break;
	case SUB_S_GAME_END:		//游戏结束
		{
			if (wDataSize!=sizeof(CMD_S_GameEnd)) 
				return 0;

			//消息处理
			CMD_S_GameEnd* pGameEnd=(CMD_S_GameEnd *)pBuffer;

			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo && pUserInfo->dwUserID == m_dwUserID)
				{
					// 增加上庄次数
					m_wUpBankerCount ++;
				}
			}

			// 更新数据
			m_nMeMaxScore	= pGameEnd->lMeMaxScore;

			// 保护下线
			const SBankerConfig& c = RobotManager::GetSingleton().GetBankerConfig();
			if (m_nMeMaxScore <= c.nMinScore)
			{
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
		}
		break;
	}
	return true;
}

