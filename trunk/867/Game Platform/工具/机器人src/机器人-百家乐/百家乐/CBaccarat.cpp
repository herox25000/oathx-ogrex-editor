#include "stdafx.h"
#include "CBaccarat.h"

//ʱ���ʶ
#define IDI_PLACE_JETTON			100									//��עʱ��
#define IDI_APPLY_BANKER			101									//������ׯ
#define IDI_APPLY_NOT_BANKER		102									//������ׯ

#define JETTON_COUNT				7									//������Ŀ

CBaccarat::CBaccarat(DWORD dwUserID)
:CGameBase(dwUserID)
{
	m_lCellScore=0;
	//��ע��Ϣ
	m_lMeMaxScore=0L;
	m_lMeTieScore=0L;
	m_lMeBankerScore=0L;
	m_lMePlayerScore=0L;
	m_lMeTieSamePointScore=0L;
	m_lMePlayerKingScore=0L;
	m_lMeBankerKingScore=0L;

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

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

	time_t seed = time(NULL);
	srand((unsigned)seed);

	TCHAR szINI[512];
	::GetModulePath(szINI, sizeof(szINI));
	SafeStrCat(szINI, "\\RM-Baccarat.ini", sizeof(szINI));
	m_nMaxBankerCount = GetPrivateProfileInt("RobotOption", "MaxBankerTime", 6, szINI);
	m_nUnBankerForWin = GetPrivateProfileInt("RobotOption", "UnBankerForWin", 20000000, szINI);
	m_nOfflineForWin = GetPrivateProfileInt("RobotOption", "OfflineForWin", 60000000, szINI);
	m_nJettonMaxNum = GetPrivateProfileInt("RobotOption", "JettonMaxNum", 10, szINI);

}

CBaccarat::~CBaccarat()
{
}

void CBaccarat::ResetGame()
{
	//��ע��Ϣ
	m_lMeMaxScore=0L;
	m_lMeTieScore=0L;
	m_lMeBankerScore=0L;
	m_lMePlayerScore=0L;
	m_lMeTieSamePointScore=0L;
	m_lMePlayerKingScore=0L;
	m_lMeBankerKingScore=0L;

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//��ʷ��Ϣ
	m_wDrawCount=1;
	m_lMeResultCount=0;

	//״̬����
	m_bMeApplyBanker = false;

	//ׯ����Ϣ
	m_lApplyBankerCondition = BANK_CONDITION_MONEY;
	m_wCurrentBanker = INVALID_CHAIR;
}

void CBaccarat::OnPlaceJetton()
{
	int nNum = rand() % m_nJettonMaxNum;
	m_nBeforeJettonScore = m_lMeMaxScore;
	SetTimer(IDI_PLACE_JETTON, rand()%2000+1000, nNum);
}

__int64 CBaccarat::GetMaxPlayerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//��������
	__int64 lOtherAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore;

	//�����ע
	__int64 lMaxPlayerScore = lOtherAreaScore + m_lBankerTreasure;
	lMaxPlayerScore -= (m_lAllPlayerScore + m_lAllPlayerKingScore*2);

	return lMaxPlayerScore;
}

__int64 CBaccarat::GetMaxTieScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//���ػ���
	__int64 lReturnScore = m_lAllTieSamePointScore * 33 + m_lAllTieScore * 8;

	//���»���
	__int64 lMaxTieScore = (m_lBankerTreasure - lReturnScore)/8;

	return lMaxTieScore;
}

__int64 CBaccarat::GetMaxBankerScore()
{
	if ( m_wCurrentBanker == INVALID_CHAIR ) return 0;

	//��������
	__int64 lOtherAreaScore = m_lAllTieScore + m_lAllPlayerScore + m_lAllTieSamePointScore + m_lAllPlayerKingScore;

	//�����ע
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
						PlaceJetton.cbJettonArea = ID_XIAN_JIA;
						break;
					}
				case 1:
					{
						PlaceJetton.cbJettonArea = ID_PING_JIA;
						break;
					}
				case 2:
					{
						PlaceJetton.cbJettonArea = ID_ZHUANG_JIA;
						break;
					}
				}

				static __int64 JScore[] = 
				{
					1000, 10000, 100000, 500000, 1000000, 5000000
				};
				int nRand = rand() % 100;
				__int64 nNowJettonScore = GetNowJettonScore();
				if (nRand < 40)
					PlaceJetton.lJettonScore = JScore[0];
				else if (nRand < 64)
					PlaceJetton.lJettonScore = JScore[1];
				else if (nRand < 76)
					PlaceJetton.lJettonScore = JScore[2];
				else if (nRand < 86)
					PlaceJetton.lJettonScore = JScore[3];
				else if (nRand < 95)
					PlaceJetton.lJettonScore = JScore[4];
				else
					PlaceJetton.lJettonScore = JScore[5];

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

				if (m_nBeforeJettonScore * 0.1 < nNowJettonScore + PlaceJetton.lJettonScore)
					bSend = FALSE;

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
			break;
		}
	}
}

bool CBaccarat::OnGameMessage(WORD wSubCmdID, const void * pBuffer/* =NULL */, WORD wDataSize/* =0 */)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			m_bPlaying = true;
			break;
		}
	case SUB_S_PLACE_JETTON:	//�û���ע
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_PlaceJetton));
			if (wDataSize!=sizeof(CMD_S_PlaceJetton)) return false;

			//��Ϣ����
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

			//��ע��Ϣ
			m_lAllTieScore=0L;			
			m_lAllBankerScore=0L;		
			m_lAllPlayerScore=0L;		
			m_lAllTieSamePointScore=0L;
			m_lAllBankerKingScore=0L;	
			m_lAllPlayerKingScore=0L;

			//���ñ���
			m_lMeTieScore=0L;
			m_lMeBankerScore=0L;
			m_lMePlayerScore=0L;
			m_lMeTieSamePointScore = 0L;
			m_lMeBankerKingScore = 0L;
			m_lMePlayerKingScore = 0L;
			m_lMeMaxScore=pGameEnd->lMeMaxScore;
			m_lCellScore=pGameEnd->lCellScore;
			m_lBankerTreasure=pGameEnd->lBankerTreasure;

			if(m_lMeMaxScore<100000)//��������������10W������
			{
				CString strMsg;
				strMsg.Format("%d ��Ǯ����10���Զ����ߣ�", m_MeUserInfo.dwUserID);
				ShowMessageBox(strMsg);
				EndServer();
				return false;
			}

			if (m_lMeResultCount >= m_nOfflineForWin)
			{
				CString strMsg;
				strMsg.Format("%d ���泬���ֵ���Զ����ߣ�", m_MeUserInfo.dwUserID);
				ShowMessageBox(strMsg);
				EndServer();
				return false;
			}

			//״̬����
			if(m_bMeIsBanker)
			{
				++m_nBankerTimes;
			}

			if(!m_bMeIsBanker)//�������ׯ��
			{
				if(m_wCurrentBanker == INVALID_CHAIR)
				{
					if(m_ApplyBankerVec.empty()&&!m_bMeApplyBanker)
					{
						SetTimer(IDI_APPLY_BANKER, rand()%15000+5000, 1);
					}
				}
				else
				{
					//if(m_bMeApplyBanker==false)
					//{
						OnPlaceJetton();
					//}
				}
			}
			else
			{
				if(!m_bMeApplyBanker)
				{
					if(m_nBankerTimes>m_nMaxBankerCount || m_lBankerScore >= m_nUnBankerForWin)//�����������8��ׯ
					{
						SetTimer(IDI_APPLY_NOT_BANKER, 6000, 1);
						m_bMeApplyBanker = false;
					}
					if(m_lMeMaxScore<=1000000)//��������������100�򣬾��Զ���ׯ
					{
						SetTimer(IDI_APPLY_NOT_BANKER, 6000, 1);
						m_bMeApplyBanker = false;
					}
				}

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
	case GS_FREE:			//����״̬
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_S_StatusFree));
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;

			//��Ϣ����
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;

			//ׯ�ұ���
			m_lApplyBankerCondition = pStatusFree->lApplyBankerCondition;			

			//�����ע
 			m_lCellScore=pStatusFree->lCellScore;
			//���ñ���
			m_lMeMaxScore= pStatusFree->lMeMaxScore;
			m_lMeTieScore=pStatusFree->lMeTieScore;
			m_lMeBankerScore=pStatusFree->lMeBankerScore;
			m_lMePlayerScore=pStatusFree->lMePlayerScore;
			m_lMeTieSamePointScore = pStatusFree->lMeTieKingScore;
			m_lMeBankerKingScore = pStatusFree->lMeBankerKingScore;
			m_lMePlayerKingScore = pStatusFree->lMePlayerKingScore;
 
 			//ׯ����Ϣ
			m_wCurrentBanker = pStatusFree->wCurrentBankerChairID;
			m_lBankerScore = pStatusFree->lBankerKingScore;
			m_lBankerTreasure = pStatusFree->lBankerTreasure;
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

			m_lCellScore=pStatusPlay->lCellScore;
			//���ñ���
			m_lMeMaxScore=pStatusPlay->lMeMaxScore;
			m_lMeTieScore=pStatusPlay->lMeTieScore;
			m_lMeBankerScore=pStatusPlay->lMeBankerScore;
			m_lMePlayerScore=pStatusPlay->lMePlayerScore;
			m_lMeTieSamePointScore = pStatusPlay->lMeTieKingScore;
			m_lMeBankerKingScore = pStatusPlay->lMeBankerKingScore;
			m_lMePlayerKingScore = pStatusPlay->lMePlayerKingScore;
 
			//ׯ����Ϣ
			m_wCurrentBanker = pStatusPlay->wCurrentBankerChairID;
			m_lBankerScore = pStatusPlay->lBankerKingScore;
			m_lBankerTreasure = pStatusPlay->lBankerTreasure;

			return true;
		}
	}

	return false;
}

__int64 CBaccarat::GetNowJettonScore()
{
	return m_lMeTieScore + m_lMeBankerScore + m_lMePlayerScore +m_lMeTieSamePointScore + m_lMeBankerKingScore + m_lMePlayerKingScore;
}

