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

void			SmallNineMachine::ResetGame()
{
	m_wCurBanker		= INVALID_CHAIR;
	m_bMeBanker			= FALSE;
	m_nMeMaxScore		= 0;
	m_wUpBankerCount	= 0;
	m_fElapsedTime		= 0;
	m_fAddJettonTime	= RobotTimer::rdft(1, 3);
	m_bAddJetton		= FALSE;
}

//��Ϸ״̬
bool			SmallNineMachine::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE:			//����״̬
		{
			if (wDataSize != sizeof(CMD_S_StatusFree)) 
				return 0;

			//��Ϣ����
			CMD_S_StatusFree* pStatusFree=(CMD_S_StatusFree *)pBuffer;
			if (pStatusFree)
			{
				// ��ǰׯ����
				m_nBankerScore	= pStatusFree->lBankerTreasure;
				// �Լ�����
				m_nMeMaxScore	= pStatusFree->lMeMaxScore;
				
				// ���µ�ǰׯID
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
	case GS_PLAYING:		//��Ϸ״̬
		{
			if (wDataSize != sizeof(CMD_S_StatusPlay))
				return 0;

			//��Ϣ����
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;
			if (pStatusPlay)
			{
				// ��ǰׯ����
				m_nBankerScore	= pStatusPlay->lBankerTreasure;
				// �Լ�����
				m_nMeMaxScore	= pStatusPlay->lMeMaxScore;
				// ���µ�ǰׯID
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
	// ��ȡׯ����
	const SBankerConfig& config	= RobotManager::GetSingleton().GetBankerConfig();	
	// ��ǰ������ׯ��������
	int nReqBanker				= BankerManager::GetSingleton().GetBankerCount();
	if (m_wCurBanker == INVALID_CHAIR || nReqBanker < config.wUpBankerDeque)
	{
		// ��ѯ��ǰ�Լ��Ƿ��Ѿ�����ׯ
		SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
		if (pUserInfo == NULL && !BankerManager::GetSingleton().IsLock())
		{
			if (m_nMeMaxScore >= config.nUpBankerScore)
			{
				BankerManager::GetSingleton().Lock();

				// ������ׯ
				CMD_C_ApplyBanker req;
				req.bApplyBanker	= true;
				
				//������Ϣ
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}
	}
	else
	{
		// �����ׯ
		SUserInfo* pCurBanker	= m_pGameManager->Search(m_wCurBanker);
		if (pCurBanker->dwUserID == m_dwUserID)
		{
			if (m_wUpBankerCount >= config.wUpBankerCount)
			{
				BankerManager::GetSingleton().Lock();

				// ������ׯ
				CMD_C_ApplyBanker req;
				req.bApplyBanker = 0;

				//������Ϣ
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}

		// �����ǰ��ׯ�����������ã���ô����������ׯ
		SUserInfo* pUserInfo = BankerManager::GetSingleton().Search(m_dwUserID);
		if (nReqBanker < config.wUpBankerDeque + 1 && !BankerManager::GetSingleton().IsLock())
		{
			if (m_nMeMaxScore >= config.nUpBankerScore)
			{
				BankerManager::GetSingleton().Lock();

				CString szMessage;
				szMessage.Format("Robot[%d] request banker", m_dwUserID);
				ShowMessageBox(szMessage);
				// ������ׯ
				CMD_C_ApplyBanker req;
				req.bApplyBanker =	 true;

				//������Ϣ
				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			}
		}
	}

	// ���¼�ע��Ϣ
	if ( m_bAddJetton )
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

			// ���ѹס���
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

//��Ϸ��Ϣ
bool			SmallNineMachine::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
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

	case SUB_S_PLACE_JETTON:	//�û���ע
		{
			
		}
		break;

	case SUB_S_APPLY_BANKER:	//������ׯ
		{
			if (wDataSize!=sizeof(CMD_S_ApplyBanker)) 
				return 0;

			// ��ȡׯ������
			const SBankerConfig& c = RobotManager::GetSingleton().GetBankerConfig();

			CString szMessage;
			//��Ϣ����
			CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;

			tagUserInfo* pUserInfo = m_pGameManager->Search(pApplyBanker->szAccount);
			if (pUserInfo && !strcmp(pUserInfo->szName, pApplyBanker->szAccount) && pUserInfo->dwUserID == m_dwUserID)
			{
				BankerManager::GetSingleton().Unlock();

				if (pApplyBanker->bApplyBanker)
				{
					BankerManager::GetSingleton().AddUser(pUserInfo);
				}
				else
				{
					BankerManager::GetSingleton().Remove(pUserInfo->dwUserID);
				}

				m_wUpBankerCount = 0;
			}
		}
		break;
	case SUB_S_CHANGE_BANKER:	//�л�ׯ��
		{
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) 
				return 0;

			//��Ϣ����
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

	case SUB_S_CHANGE_USER_SCORE://���»���
		{
			
		}
		break;
	case SUB_S_GAME_END:		//��Ϸ����
		{
			if (wDataSize!=sizeof(CMD_S_GameEnd)) 
				return 0;

			//��Ϣ����
			CMD_S_GameEnd* pGameEnd=(CMD_S_GameEnd *)pBuffer;

			if (m_wCurBanker != INVALID_CHAIR)
			{
				tagUserInfo* pUserInfo = m_pGameManager->Search(m_wCurBanker);
				if (pUserInfo && pUserInfo->dwUserID == m_dwUserID)
				{
					// ������ׯ����
					m_wUpBankerCount ++;
				}
			}

			// ��������
			m_nMeMaxScore	= pGameEnd->lMeMaxScore;

			// ��������
			const SBankerConfig& c = RobotManager::GetSingleton().GetBankerConfig();
			if (m_nMeMaxScore <= c.nMinScore)
			{
				CString szMessage;
				szMessage.Format("Robot[%d] �������%I64 �Զ�����", m_dwUserID, c.nMinScore);
				ShowMessageBox(szMessage, TraceLevel_Warning);

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
		}
		break;
	}
	return true;
}

