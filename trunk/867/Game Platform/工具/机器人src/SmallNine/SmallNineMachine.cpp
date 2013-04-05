#include "StdAfx.h"
#include ".\smallninemachine.h"
#include "RobotManager.h"
#include "RobotTimer.h"
#include "BankerManager.h"

SmallNineMachine::SmallNineMachine(DWORD dwUserID) 
	: IRobot(dwUserID), m_fOnlineTime(0), m_fCurOnlineTime(0)
{
	ResetGame();
	srand(time(NULL));
}

SmallNineMachine::~SmallNineMachine(void)
{
	if (m_bApplyBankerSend)
		BankerManager::GetSingleton().Unlock();

	BankerManager::GetSingleton().Remove(m_dwUserID);
}

void			SmallNineMachine::ResetGame()
{
	IRobot::ResetGame();

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
	m_nBankerWinScore		= 0;
	m_bApplyBankerSend		= FALSE;
	m_nJettonTime			= MAX_PLACE_JETTON_TIME;
}

void			SmallNineMachine::SetOnlineTime(double fOnlineTime)
{
	m_fOnlineTime = fOnlineTime;
}

bool			SmallNineMachine::SendApplyBanker(bool bUp)
{
	if (m_bStart == false)
		return 0;

	// ��ȡׯ����
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();	
	// ��ǰ������ׯ��������
	int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();

	if (bUp)
	{
		int nApplyBankerCount	= BankerManager::GetSingleton().GetLockCount();
		if ((nReqBanker + nApplyBankerCount) < config.wUpBankerDeque  && m_nMeMaxScore >= m_nApplyBankerCondition)
		{
			BankerManager::GetSingleton().Lock();
			m_bApplyBankerSend = TRUE;

			// ������ׯ
			CMD_C_ApplyBanker req;
			req.bApplyBanker	= true;

			//������Ϣ
			SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
		}
	}
	else
	{
		// ������ׯ
		CMD_C_ApplyBanker req;
		req.bApplyBanker	= 0;

		//������Ϣ
		SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
	}

	return true;
}

INT64			SmallNineMachine::GetRandScore(__int64 nLeftJettonScore)
{
	// ��ȡׯ����
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

	// ���ѹס���
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

//��Ϸ״̬
bool			SmallNineMachine::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE + 1:
		{
			if (wDataSize != sizeof(CMD_S_StatusFree)) 
				return 0;

			m_bStart = TRUE;

			//��Ϣ����
			CMD_S_StatusFree* pStatusFree=(CMD_S_StatusFree *)pBuffer;
			if (pStatusFree)
			{
				m_nJettonTime			= pStatusFree->cbTimeLeave;
				m_nApplyBankerCondition	= pStatusFree->lApplyBankerCondition;
				// ��ǰׯ����
				m_nBankerScore			= pStatusFree->lBankerTreasure;
				// �Լ�����
				m_nMeMaxScore			= pStatusFree->lMeMaxScore;

				// ���µ�ǰׯID
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
	case GS_FREE:			//����״̬
		{
			if (wDataSize != sizeof(CMD_S_StatusFree)) 
				return 0;
			
			m_bStart = TRUE;

			//��Ϣ����
			CMD_S_StatusFree* pStatusFree=(CMD_S_StatusFree *)pBuffer;
			if (pStatusFree)
			{
				m_nJettonTime			= 0;
				m_nApplyBankerCondition	= pStatusFree->lApplyBankerCondition;
				// ��ǰׯ����
				m_nBankerScore			= pStatusFree->lBankerTreasure;
				// �Լ�����
				m_nMeMaxScore			= pStatusFree->lMeMaxScore;
				
				// ���µ�ǰׯID
				m_wCurBanker			= pStatusFree->wCurrentBankerChairID;
				if (m_wCurBanker != INVALID_CHAIR)
				{
					tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
					if (pUserInfo != NULL && pUserInfo->dwUserID != m_dwUserID)
					{
						m_bAddJetton = FALSE;
					}
				}
			}
		}
		return true;
	case GS_PLAYING:		//��Ϸ״̬
		{
			if (wDataSize != sizeof(CMD_S_StatusPlay))
				return 0;

			m_bStart = TRUE;

			//��Ϣ����
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			m_nJettonTime			= pStatusPlay->cbTimeLeave;
			m_nApplyBankerCondition	= pStatusPlay->lApplyBankerCondition;
			m_nBankerScore			= pStatusPlay->lBankerTreasure;
			m_nMeMaxScore			= pStatusPlay->lMeMaxScore;
			m_wCurBanker			= pStatusPlay->wCurrentBankerChairID;

			m_bAddJetton = FALSE;
			
		}
		return true;
	}

	return false;
}

void			SmallNineMachine::OnUpdate(float fElapsed)
{
	// ��ȡׯ����
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();
	// ��ǰ������ׯ��������
	int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();
	
	// �жϻ����˵�ǰ����ʱ��
	m_fCurOnlineTime += fElapsed;
	if ((m_fCurOnlineTime / 60) >= m_fOnlineTime)
	{
		// ��鵱ǰ�������Ƿ���ׯ
		if (m_wCurBanker != INVALID_CHAIR)
		{
			tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
			if (pUserInfo)
			{
				// ����Լ���ׯ�������ѵ�����ʱ�䣬��ô�����������ʱ��
				if (pUserInfo->dwUserID == m_dwUserID)
				{
					double dMidNewTime	= config.fMaxPlaceTime / 2;
					m_fOnlineTime		= RobotTimer::rdit(config.fMinOnlineTime, dMidNewTime >= config.fMinOnlineTime ? dMidNewTime : config.fMinOnlineTime + 5);
					m_fCurOnlineTime	= 0;
				}
				else
				{
					// ��ǰ���û���·�
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
		else
		{
			CString szMessage;
			szMessage.Format("Robot[%d] Has arrived online time, offline", m_dwUserID);
			ShowMessageBox(szMessage, TraceLevel_Debug);

			SetState(ROBOT_INVALID);
		}
	}

	// ���¼�ע��Ϣ
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
		if (nRnd < nPlaceRand)
		{
			m_fElapsedTime		+= fElapsed;
			// �Ѿ���ѹע����
			if (m_fElapsedTime >= m_fAddJettonTime)
			{
				CMD_C_PlaceJetton PlaceJetton;
				ZeroMemory(&PlaceJetton,sizeof(PlaceJetton));

				// ���ѹע��
				static BYTE cbArea[] = {
					ID_SHUN_MEN,
					ID_TIAN_MEN,
					ID_DAO_MEN,
				};
				
				PlaceJetton.cbJettonArea = cbArea[rand() % 3];
				__int64 nLeftScore = m_nMeMaxScore * config.nPlaceMaxRate / 100 - m_nMePlaceScore;
				PlaceJetton.lJettonScore = GetRandScore(nLeftScore);

				if (m_nMeMaxScore >= PlaceJetton.lJettonScore)
				{
					WORD nPlaceRate = (m_nMePlaceScore + PlaceJetton.lJettonScore) / m_nMeMaxScore * 100;
					if (nPlaceRate < config.nPlaceMaxRate)
					{
						// ����Ѻע��Ϣ
						SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, 
							&PlaceJetton, sizeof(PlaceJetton));

						// �����Լ�ѹ��Ǯ
						m_nMePlaceScore += PlaceJetton.lJettonScore;
					}
				}

				m_fAddJettonTime	= RobotTimer::rdft(config.fMinPlaceTime, config.fMaxPlaceTime);
				m_fElapsedTime		= 0;
			}
		}
	}
}

//��Ϸ��Ϣ
bool			SmallNineMachine::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			if (m_bStart)
			{
				// ��ȡׯ����
				const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();	
				// ��ǰ������ׯ��������
				int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();

				if (m_wCurBanker != INVALID_CHAIR)
				{
					tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
					if (pUserInfo)
					{
						// �����ǰׯ�����Լ�
						if (pUserInfo->dwUserID != m_dwUserID)
						{
							// ǿ���������氺
							SendApplyBanker(true);
						}
					}
				}

				// ����Ѻע����
				m_bAddJetton = FALSE;
			}
		}
		break;

	case SUB_S_PLACE_JETTON:	//�û���ע
		{
			
		}
		break;

	case SUB_S_APPLY_BANKER:	//������ׯ
		{
			if (wDataSize!=sizeof(CMD_S_ApplyBanker)) 
				return 0;

			//��Ϣ����
			CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;

			//���Ҹ��û�
			tagUserInfo* pUserInfo = m_pGameManager->Search(
				pApplyBanker->szAccount);
			if (pUserInfo)
			{
				if (pUserInfo->dwUserID == m_dwUserID)
				{
					BankerManager::GetSingleton().Unlock();
					m_bApplyBankerSend = FALSE;
				}
			
				// ������ׯ����
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
	case SUB_S_CHANGE_BANKER:	//�л�ׯ��
		{
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) 
				return 0;

			//��Ϣ����
			CMD_S_ChangeBanker* pChangeBanker	= (CMD_S_ChangeBanker *)pBuffer;
			m_wCurBanker						= pChangeBanker->wChairID;
		}
		break;

	case SUB_S_CHANGE_USER_SCORE://���»���
		{
			
		}
		break;
	case SUB_S_StartJetton:
		{
			CMD_S_JettonStart* pJettonStart = (CMD_S_JettonStart*)(pBuffer);
			m_nJettonTime	= pJettonStart->cbTimeLeave;
			m_bAddJetton	= TRUE;
		}
		break;
	case SUB_S_GAME_END:		//��Ϸ����
		{
			if (wDataSize != sizeof(CMD_S_GameEnd)) 
				return 0;

			//��Ϣ����
			CMD_S_GameEnd* pGameEnd	=(CMD_S_GameEnd *)pBuffer;

			// ��������
			m_nJettonTime			= 0;
			m_nMeMaxScore			= pGameEnd->lMeMaxScore;

			// ��ȡׯ����
			const SBankerConfig& c	= RobotManager::GetSingleton().GetBankerConfig();	
			// ��ǰ������ׯ��������
			int nReqBanker			= BankerManager::GetSingleton().GetBankerCount();

			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo)
				{
					if (pUserInfo->dwUserID == m_dwUserID)
					{
						// ������ׯ����
						m_wUpBankerCount ++;

						// �����ׯ�������������ֵ��������ׯ, Ĭ������»�����ÿ����ׯ���ٶ���������ׯ
						if (m_wUpBankerCount >= RobotTimer::rdit(1, c.wUpBankerCount > 1 ? c.wUpBankerCount : 1))
						{
							SendApplyBanker(false);
						}

						if (m_nBankerWinScore > 0)
						{
							if (m_nBankerWinScore > c.nMaxWinScore)
							{
								SendApplyBanker(false);
							}
							else
							{
								int nRate = m_nBankerWinScore * 100 / c.nMaxWinScore;
								if (rand() % 100 < nRate)
								{
									SendApplyBanker(false);
								}
							}
						}
						else if (m_nBankerWinScore < 0 && m_nBankerWinScore <= (-c.nUpBankerLoseScore))
						{
							SendApplyBanker(false);
						}
					}
				}
			}

			// ÿ����Ϸ�����󣬲�ѯ��ǰ��ׯ�����������Լ�����û����������ׯ
			SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
			if (!pUserInfo)
			{
				SendApplyBanker(true);
			}
			
			// ���û����˵�ǰѹ��Ǯ
			m_nMePlaceScore	= 0;
			m_bAddJetton	= FALSE;
			
			// �������˵Ľ�Ǯ������С����
			if (m_nMeMaxScore <= c.nMinScore)
			{
				// �Ƴ���ׯ�����е��Լ�
				BankerManager::GetSingleton().Remove(m_dwUserID);

				CString szMessage;
				szMessage.Format("Robot[%d] Gold less than %I64d automatic logoff", m_dwUserID, c.nMinScore);
				ShowMessageBox(szMessage, TraceLevel_Warning);
				
				// ���û����˶���
				SetState(ROBOT_INVALID);
			}
		}
		break;
	case SUB_S_SEND_RECORD:		//��Ϸ��¼
		{
			
		}
		break;
	case SUB_S_GAME_SCORE:		//��Ϸ����
		{
			if (wDataSize!=sizeof(CMD_S_GameScore)) 
				return 0;

			//��Ϣ����
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

