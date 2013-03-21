#include "StdAfx.h"
#include ".\smallninemachine.h"

SmallNineMachine::SmallNineMachine(DWORD dwUserID) : IRobot(dwUserID), m_pBankerUser(NULL)
{
	m_pBankerUser	= new UserManager();
	m_wCurBanker	= INVALID_CHAIR;
	m_bMeBanker		= FALSE;
	m_nMeMaxScore	= 0;
}

SmallNineMachine::~SmallNineMachine(void)
{
	delete m_pBankerUser;
	m_pBankerUser = NULL;
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
				if (pStatusFree->wCurrentBankerChairID == INVALID_CHAIR)
				{
					int nBankerCount = m_pBankerUser->GetCount();
					if (nBankerCount <= 0 && pStatusFree->lMeMaxScore >= 500)
					{
						// ������ׯ
						CMD_C_ApplyBanker req;
						req.bApplyBanker = true;

						//������Ϣ
						SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ) );	
					}
				}
				else
				{
					m_wCurBanker = pStatusFree->wCurrentBankerChairID;
				}

				//
				m_nMeMaxScore = pStatusFree->lMeMaxScore;
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
				m_wCurBanker = pStatusPlay->wCurrentBankerChairID;
			}
		}
		return true;
	}

	return false;
}

//��Ϸ��Ϣ
bool			SmallNineMachine::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			if (m_pBankerUser != NULL)
			{
				if (m_wCurBanker == INVALID_CHAIR)
				{
					int nCount = m_pBankerUser->GetCount();
					if (nCount <= 0  && m_nMeMaxScore > 500)
					{
						// ������ׯ
						CMD_C_ApplyBanker req;
						req.bApplyBanker = true;

						//������Ϣ
						SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ) );
					}
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

			//��Ϣ����
			CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;
			if (pApplyBanker->bApplyBanker)
			{

			}
		}
		break;
	case SUB_S_CHANGE_BANKER:	//�л�ׯ��
		{
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) 
				return 0;

			//��Ϣ����
			CMD_S_ChangeBanker* pChangeBanker=(CMD_S_ChangeBanker *)pBuffer;
			if (pChangeBanker->wChairID != INVALID_CHAIR)
			{
	
			}
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
			CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;
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
			CMD_S_GameScore * pGameScore=(CMD_S_GameScore *)pBuffer;	
		}
		break;
	}
	return true;
}

