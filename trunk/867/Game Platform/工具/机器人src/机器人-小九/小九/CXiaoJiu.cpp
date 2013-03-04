#include "stdafx.h"
#include "CXiaoJiu.h"

//ʱ���ʶ
#define IDI_PLACE_JETTON			100									//��עʱ��
#define IDI_APPLY_BANKER			101									//������ׯ
#define IDI_APPLY_NOT_BANKER		102									//������ׯ

CPaiJiu::CPaiJiu(DWORD dwUserID)
:CGameBase(dwUserID)
{

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bPlaying = false;


	//ׯ����Ϣ
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

	//��ע��Ϣ
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
	//��ע��Ϣ

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//״̬����
	m_bMeApplyBanker = false;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
}

void CPaiJiu::OnPlaceJetton()
{
	SetTimer(IDI_PLACE_JETTON, rand()%20000+1000, 1);
}

//�����ע
__int64 CPaiJiu::GetMaxPlayerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//��������
	__int64 lAllAreaScore = m_lAllTieScore + 
		m_lAllTieSamePointScore + 
		m_lAllBankerScore+ 
		m_lAllBankerKingScore+
		m_lAllPlayerScore+
		m_lAllPlayerKingScore;

	//�����ע
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//�����ע
__int64 CPaiJiu::GetMaxPlayerKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//��������
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;

	//�����ע
	__int64 lMaxPlayerScore = m_lBankerTreasure-lAllAreaScore;
	return lMaxPlayerScore;
}

//�����ע
__int64 CPaiJiu::GetMaxBankerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//��������
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;


	//�����ע
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//�����ע
__int64 CPaiJiu::GetMaxBankerKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;
	//��������
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;

	//�����ע
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

//�����ע
__int64 CPaiJiu::GetMaxTieScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	__int64 lMaxTieScore = lMaxPlayerScore;

	return lMaxTieScore;
}

//�����ע
__int64 CPaiJiu::GetMaxTieKingScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;
	//���ػ���
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

				//������Ϣ
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

				//������Ϣ
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
				switch(rand()%4)
				{
				case 0:
					{
						PlaceJetton.lJettonScore = 100;
						break;
					}
				case 1:
					{
						PlaceJetton.lJettonScore = 1000;
						break;
					}
				case 2:
					{
						PlaceJetton.lJettonScore = 10000;
						break;
					}
				case 3:
					{
						PlaceJetton.lJettonScore = 100000;
						break;
					}
				}
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
	case SUB_S_GAME_START:		//��Ϸ��ʼ
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
	case SUB_S_PLACE_JETTON:	//�û���ע
		{
			break;
		}
	case SUB_S_APPLY_BANKER:	//������ׯ
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_ApplyBanker));
			if (wDataSize!=sizeof(CMD_S_ApplyBanker)) return false;

			//��Ϣ����
			CMD_S_ApplyBanker * pApplyBanker=(CMD_S_ApplyBanker *)pBuffer;
		
			//�������
			if ( pApplyBanker->bApplyBanker )
			{
				//�����ж�
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
	case SUB_S_CHANGE_BANKER:	//�л�ׯ��
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_ChangeBanker));
			if (wDataSize!=sizeof(CMD_S_ChangeBanker)) return false;

			//��Ϣ����
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

			//ɾ�����
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
	case SUB_S_CHANGE_USER_SCORE://���»���
		{
			break;
		}
	case SUB_S_GAME_END:		//��Ϸ����
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
			if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

			//��Ϣ����
			CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

			m_bPlaying = false;

			m_lMeMaxScore=pGameEnd->lMeMaxScore;
			m_lMeTianMenScore=0L;
			m_lMeDaoMenScore=0L;
			m_lMeShunMenScore=0L;
			m_lMeQiaoScore=0L;
			m_lMeZuoJiaoScore=0L;
			m_lMeYouJiaoScore=0L;

			//��ע��Ϣ
			m_lAllTieScore=0L;			
			m_lAllBankerScore=0L;		
			m_lAllPlayerScore=0L;		
			m_lAllTieSamePointScore=0L;
			m_lAllBankerKingScore=0L;	
			m_lAllPlayerKingScore=0L;

			//��ע��Ϣ
			m_lBankerTreasure=pGameEnd->lBankerTreasure;

			if(m_lMeMaxScore<100000)
			{
				CString strMsg;
				strMsg.Format("%d ��Ǯ����10���Զ����ߣ�", m_MeUserInfo.dwUserID);
				ShowMessageBox(strMsg);
				EndServer();
				return false;
			}

			//״̬����
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
	case SUB_S_SEND_RECORD:		//��Ϸ��¼
		{
			break;
		}
	case SUB_S_GAME_SCORE:		//��Ϸ����
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_GameScore));
			if (wDataSize!=sizeof(CMD_S_GameScore)) return false;

			//��Ϣ����
			CMD_S_GameScore * pGameScore=(CMD_S_GameScore *)pBuffer;

			m_lMeResultCount+=pGameScore->lMeGameScore;

			//���ñ���
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
	case GS_FREE:			//����״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusFree));
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;

			//��Ϣ����
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;

			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusFree->lApplyBankerCondition;			
 
 			//ׯ����Ϣ
			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;
			m_lBankerScore = pStatusFree->lBankerKingScore;
			m_lBankerTreasure = pStatusFree->lBankerTreasure;
			//���ñ���
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			//���ñ���
			m_lMeMaxScore= pStatusFree->lMeMaxScore ;
			m_lMeTianMenScore=pStatusFree->lMeTieScore;
			m_lMeDaoMenScore=pStatusFree->lMeBankerScore;
			m_lMeShunMenScore=pStatusFree->lMePlayerScore;
			m_lMeQiaoScore = pStatusFree->lMeTieKingScore;
			m_lMeYouJiaoScore = pStatusFree->lMeBankerKingScore;
			m_lMeZuoJiaoScore = pStatusFree->lMePlayerKingScore;
			return true;
		}
	case GS_PLAYING:		//��Ϸ״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusPlay));
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;

			//��Ϣ����
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusPlay->lApplyBankerCondition;
 
			//ׯ����Ϣ
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			m_lBankerScore = pStatusPlay->lBankerKingScore;
			m_lBankerTreasure = pStatusPlay->lBankerTreasure;
			//���ñ���
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
