#include "stdafx.h"
#include "SmallNineAndroid.h"
#include "ConfigFile.h"
#include "BankerManager.h"
#include "AndroidTimer.h"

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	SmallNineAndroid::SmallNineAndroid(DWORD dwUserID, double fOnlineTime)
		: IAndroid(dwUserID, fOnlineTime), m_bChipIn(FALSE)
	{
		m_nPlaceRate = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	SmallNineAndroid::~SmallNineAndroid()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnReset()
	{
		m_wCurBanker		= INVALID_CHAIR;
		m_fRequestTime		= AndroidTimer::rdit(5, 15);
		m_nReqBankerScore	= 0;
		m_bChipIn			= FALSE;
		m_fChipTime			= MAX_PLACE_JETTON_TIME;
		m_nChipInScore		= 0;
		m_fAddChipTime		= AndroidTimer::rdft(1, 3);
		m_fElapsedTime		= 0;
		m_nBankerWinScore	= 0;
		m_nPlaceRate		= 0;

		return IAndroid::OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	INT64		SmallNineAndroid::GetRandScore(INT64 nLeftJettonScore)
	{
		// ��ȡׯ����
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();

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

		float nTotal		= nTenMillionRate + nFiveMillionRate + nOneMillionRate + nFiveLakhRate + nTenLakhRate + nOneW + nOneQ;
		nTenMillionRate		= nTenMillionRate / nTotal * 100;
		nFiveMillionRate	= nFiveMillionRate / nTotal * 100;
		nFiveLakhRate		= nFiveLakhRate / nTotal * 100;
		nOneMillionRate		= nOneMillionRate / nTotal * 100;
		nTenLakhRate		= nTenLakhRate / nTotal * 100;
		nOneW				= nOneW / nTotal * 100;
		nOneQ				= nOneQ / nTotal * 100;

		// ���ѹס���
		static __int64 JScore[] = 
		{
			1000, 10000, 100000, 500000, 1000000, 5000000, 10000000
		};

		float JettonRate[] = { nTenMillionRate, nFiveMillionRate, nFiveLakhRate, nOneMillionRate, nTenLakhRate, nOneW, nOneQ };

		float nRandRate = AndroidTimer::rdft(0, 100);
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

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::CanOffline()
	{
		if (isSelf(m_wCurBanker) || m_nChipInScore > 0)
			return 0;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::Update(float fElapsed)
	{
		if (!IAndroid::Update(fElapsed))
			return 0;
		
		switch( m_wStaus )
		{
		case US_SIT:
			{
				OnUpdateTime(fElapsed);
				OnUpBankerRequest(fElapsed);
				OnChipIn(fElapsed);
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnUpdateTime(float fElapsed)
	{
		m_fElapsed += fElapsed;
		if ((m_fElapsed / 60) >= m_fOnlineTime)
		{
			if (isSelf(m_wCurBanker))
			{
				m_fOnlineTime	= AndroidTimer::rdit(5, 15);
				m_fElapsed		= 0;
			}
			else
			{
				if (m_nChipInScore <= 0)
				{
					CString szMessage;
					szMessage.Format("[%d][%d]��������ʱ��, ��������", GetUserID(), GetGameID());
					LogEvent(szMessage, TraceLevel_Exception);

					SetStatus(US_OFFLINE);
				}
				else
				{
					m_fOnlineTime	= AndroidTimer::rdit(5, 15);
					m_fElapsed		= 0;
				}
			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnUpdateBank()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			INT64 nMin = 0;
			INT64 nMax = 0;

			if (pUser->nScore > pConfig->nMaxScore)
			{
				nMin = pUser->nScore - pConfig->nMaxScore;
				nMax = pUser->nScore - pConfig->nMinScore;

				SaveScoreToBanker(AndroidTimer::rdit(nMin, nMax));
			}
			else if (pUser->nScore < pConfig->nMinScore)
			{
				nMin = pConfig->nMinScore - pUser->nScore;
				nMax = pConfig->nMaxScore - pUser->nScore;

				GetScoreFromBanker(AndroidTimer::rdit(nMin, nMax));
			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnSwitchTable()
	{
		//�������ݰ�
		CMD_GR_UserSitReq UserSitReq;
		memset(&UserSitReq,0,sizeof(UserSitReq));
		UserSitReq.wTableID	=	0;
		UserSitReq.wChairID	=	rand() % 50;

		//�������ݰ�
		WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
		m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

		m_wSitReqCount ++;
		CString szMessage;
		szMessage.Format("[%d]��%d����������", m_dwUserID, m_wSitReqCount);
		CTraceService::TraceString(szMessage,
			TraceLevel_Normal);

		//��ȡ����
		CMD_GF_Info Info;
		ZeroMemory(&Info,sizeof(Info));
		Info.bAllowLookon=true;

		//������Ϣ
		m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO,&Info,sizeof(Info));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnUpBankerRequest(float fElapsed)
	{	
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		SUser* pUser		= GetUserInfo();
		if (pUser == NULL)
			return 0;

		// ��ׯ����
		if (BankerManager::GetSingleton().CheckRequest(m_dwUserID) || BankerManager::GetSingleton().Search(m_dwUserID))
			return 0;

		DWORD dwBankerCount = BankerManager::GetSingleton().GetBankerCount();
		DWORD dwRequest		= BankerManager::GetSingleton().GetRequestCount();
		if (dwBankerCount >= pConfig->wMaxDeque)
		{
			if (dwRequest > 0)
				BankerManager::GetSingleton().ClearRequest();
			return 0;
		}

		m_fRequestTime -= fElapsed;

		if (m_fRequestTime <= 0)
		{
			bool bSendReq = 0;
			if (m_wCurBanker != INVALID_CHAIR)
			{
				if (!isSelf(m_wCurBanker))
					bSendReq = ((dwBankerCount + dwRequest) < pConfig->wMaxDeque) ? true : 0;
			}
			else
			{
				bSendReq = true;
			}

			if (bSendReq && pUser->nScore > m_nReqBankerScore)
			{
				if (dwBankerCount >= MIN_LINUP)
				{
					WORD wRate = rand() % 100;
					if (wRate <= 80)
					{
						m_fRequestTime = AndroidTimer::rdit(10, 20);
						return 0;
					}
				}

				BankerManager::GetSingleton().AddRequest(GetUserID());
				CString szMessage;
				szMessage.Format("[%d][%d]�ѷ�����ׯ���󣬵�ǰ�������%d", GetUserID(), GetGameID(), BankerManager::GetSingleton().GetRequestCount());
				LogEvent(szMessage, TraceLevel_Debug);

				CMD_C_ApplyBanker req;
				req.bApplyBanker = true;

				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));	
			}
			
			m_fRequestTime = AndroidTimer::rdit(5, 15);
		}
		

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnDownBankerRequest()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		SUser* pUser		= GetUserInfo();
		if (pUser == NULL)
			return 0;

		if (pUser->wCurUpBanker >= AndroidTimer::rdit(MIN_UPBANKER, pConfig->wMaxUpBanker) || pUser->nBankerCurWin > pConfig->nMaxWinScore)
		{
			CString szMessage;
			szMessage.Format("[%d][%d]������ׯ ��ׯ����%d �ɼ�%I64d", pUser->dwUserID, 
				pUser->dwGameID, pUser->wCurUpBanker, pUser->nBankerCurWin);
			LogEvent(szMessage, TraceLevel_Debug);

			CMD_C_ApplyBanker req;
			req.bApplyBanker = 0;

			SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
			return true;
		}

		if (pUser->nBankerCurWin > 0)
		{
			int nRate = pUser->nBankerCurWin * 100 / pConfig->nMaxWinScore;
			if (rand() % 100 < nRate)
			{
				CString szMessage;
				szMessage.Format("[%d][%d]������ׯ ��ׯ����%d �ɼ�%I64d", pUser->dwUserID, 
					pUser->dwGameID, pUser->wCurUpBanker, pUser->nBankerCurWin);
				LogEvent(szMessage, TraceLevel_Debug);

				CMD_C_ApplyBanker req;
				req.bApplyBanker = 0;

				SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));
				return true;
			}
		}
		else if (pUser->nBankerCurWin < 0 && pUser->nBankerCurWin < (-pConfig->nMaxWinScore))
		{
			CString szMessage;
			szMessage.Format("[%d][%d]������ׯ ��ׯ����%d �ɼ�%I64d", pUser->dwUserID, 
				pUser->dwGameID, pUser->wCurUpBanker, pUser->nBankerCurWin);
			LogEvent(szMessage, TraceLevel_Debug);
			CMD_C_ApplyBanker req;
			req.bApplyBanker = 0;

			SendData(MDM_GF_GAME, SUB_C_APPLY_BANKER, &req, sizeof( req ));

			return true;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnChipIn(float fElapsed)
	{
		if (!m_bChipIn || m_wCurBanker == INVALID_CHAIR)
			return 0;

		float nPlaceRand = m_fChipTime * 100 / MAX_PLACE_JETTON_TIME;
		if (nPlaceRand < 10)
		{
			m_bChipIn = FALSE;
			m_nPlaceRate = 0;
			return 0;
		}

		m_fChipTime -= fElapsed;

		float nRnd = AndroidTimer::rdft(0, 100);
		if (nRnd < nPlaceRand)
		{
			m_fElapsedTime		+= fElapsed;

			if (m_fElapsedTime >= m_fAddChipTime)
			{
				SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
				SUser* pUser		= GetUserInfo();
				if (pUser != NULL)
				{
					CMD_C_PlaceJetton PlaceJetton;
					ZeroMemory(&PlaceJetton, sizeof(PlaceJetton));

					// ���ѹע��
					static BYTE cbArea[] = 
					{
						ID_SHUN_MEN,
						ID_TIAN_MEN,
						ID_DAO_MEN,
					};

					PlaceJetton.cbJettonArea = cbArea[rand() % 3];
					if (m_nPlaceRate == 0)
						m_nPlaceRate = AndroidTimer::rdft(pConfig->wPlaceRate, pConfig->wMaxPlaceRate);
					INT64 nLeftScore = pUser->nScore * m_nPlaceRate / 100 - m_nChipInScore;
					PlaceJetton.lJettonScore = GetRandScore(nLeftScore);

					if (pUser->nScore >= PlaceJetton.lJettonScore)
					{
						WORD nPlaceRate = (m_nChipInScore + PlaceJetton.lJettonScore) / pUser->nScore * 100;
						if (nPlaceRate < pConfig->wPlaceRate)
						{
							SendData(MDM_GF_GAME, SUB_C_PLACE_JETTON, 
								&PlaceJetton, sizeof(PlaceJetton));

							m_nChipInScore += PlaceJetton.lJettonScore;
						}
					}
				}
			
				m_fAddChipTime		= AndroidTimer::rdit(pConfig->wMinPlaceTime, pConfig->wMaxPlaceTime);
				m_fElapsedTime		= 0;
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		switch (cbGameStation)
		{
			//����״̬
		case GS_FREE + 1:
			{
				if (wDataSize != sizeof(CMD_S_StatusFree)) 
					return 0;
				
				CMD_S_StatusFree* pStatus = (CMD_S_StatusFree*)(pBuffer);
				
				m_nReqBankerScore	= pStatus->lApplyBankerCondition;
				m_fChipTime			= pStatus->cbTimeLeave;

				m_wCurBanker		= pStatus->wCurrentBankerChairID;
				if (m_wCurBanker != INVALID_CHAIR)
				{
					if (isSelf(m_wCurBanker))
					{
						m_bChipIn = TRUE;
					}
				}

				OnUpdateBank();
			}
			break;
		case GS_FREE:			
			{
				if (wDataSize != sizeof(CMD_S_StatusFree)) 
					return 0;

				CMD_S_StatusFree* pStatus = (CMD_S_StatusFree*)(pBuffer);
				m_wCurBanker		= pStatus->wCurrentBankerChairID;
				m_nReqBankerScore	= pStatus->lApplyBankerCondition;
				m_fChipTime			= 0;

				OnUpdateBank();
			}
			break;
			//��Ϸ״̬
		case GS_PLAYING:		
			{
				if (wDataSize != sizeof(CMD_S_StatusPlay))
					return 0;

				CMD_S_StatusPlay* pStatus = (CMD_S_StatusPlay*)(pBuffer);
				m_wCurBanker		= pStatus->wCurrentBankerChairID;
				m_nReqBankerScore	= pStatus->lApplyBankerCondition;
				m_fChipTime			= pStatus->cbTimeLeave;
				m_bChipIn			= FALSE;
				m_nPlaceRate		= 0;
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
	{
		switch (wSubCmdID)
		{
			//��Ϸ��ʼ
		case SUB_S_GAME_START:		
			{
				OnGameStart(pBuffer, wDataSize);
			}
			break;
			//�û���ע
		case SUB_S_PLACE_JETTON:	
			{

			}
			break;

			//������ׯ
		case SUB_S_APPLY_BANKER:	
			{
				OnApplyBanker(pBuffer, wDataSize);
			}
			break;

			//�л�ׯ��
		case SUB_S_CHANGE_BANKER:	
			{
				OnChangeBanker(pBuffer, wDataSize);
			}
			break;

			//���»���
		case SUB_S_CHANGE_USER_SCORE:
			{

			}
			break;

			//Ѻע��ʼ
		case SUB_S_StartJetton:
			{
				OnStartJetton(pBuffer, wDataSize);
			}
			break;

			//��Ϸ����
		case SUB_S_GAME_END:		
			{
				OnGameEnd(pBuffer, wDataSize);
			}
			break;

			//��Ϸ��¼
		case SUB_S_SEND_RECORD:		
			{

			}
			break;

			//��Ϸ����
		case SUB_S_GAME_SCORE:		
			{
				OnGameScore(pBuffer, wDataSize);
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnBanker()
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnApplyBanker(const void* pBuffer, WORD wDataSize)
	{
		if (wDataSize != sizeof(CMD_S_ApplyBanker)) 
			return 0;

		CMD_S_ApplyBanker* pApplyBanker = (CMD_S_ApplyBanker *)pBuffer;

		SUser* pUser = m_pUserManager->Search(pApplyBanker->szAccount);
		if (pUser != NULL)
		{
			if (pApplyBanker->bApplyBanker)
			{
				if (BankerManager::GetSingleton().Search(pUser->dwUserID) == NULL)
				{
					BankerManager::GetSingleton().Insert(
						new SBanker(pApplyBanker->szAccount, pApplyBanker->lScore, pUser->dwUserID)
						);
				}
			}
			else
			{
				BankerManager::GetSingleton().Remove(pUser->dwUserID);
			}

			if (isSelf(pUser->dwUserID))
			{
				BankerManager::GetSingleton().RemoveRequest(pUser->dwUserID);

				CString szMessage;
				szMessage.Format("[%d][%d]���Ƴ���ׯ���󣬵�ǰ�������%d", GetUserID(), GetGameID(), BankerManager::GetSingleton().GetRequestCount());
				LogEvent(szMessage, TraceLevel_Debug);
			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnGameStart(const void* pBuffer, WORD wDataSize)
	{
		m_bChipIn = FALSE;
		m_nPlaceRate = 0;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnGameScore(const void* pBuffer, WORD wDataSize)
	{
		if (wDataSize!=sizeof(CMD_S_GameScore)) 
			return 0;

		CMD_S_GameScore* pGameScore = (CMD_S_GameScore *)pBuffer;
		
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			if (m_wCurBanker == pUser->wChairID)
			{
				pUser->nBankerAllWin += pGameScore->lBankerScore;
			}

			pUser->nWinScore += pGameScore->lMeGameScore;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnGameEnd(const void* pBuffer, WORD wDataSize)
	{
		if (wDataSize != sizeof(CMD_S_GameEnd)) 
			return 0;

		CMD_S_GameEnd* pGameEnd = (CMD_S_GameEnd *)pBuffer;
		m_nChipInScore			= 0;

		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (isSelf(m_wCurBanker))
		{
			SUser* pUser = GetUserInfo();
			if (pUser)
			{
				pUser->nBankerCurWin = pGameEnd->lBankerTotalScore;

				pUser->wCurUpBanker ++;
				pUser->wBankerCount ++;
			}
		}

		OnDownBankerRequest();
		OnUpdateBank();
		OnUpdateRobotScoreStart();

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnChangeBanker(const void* pBuffer, WORD wDataSize)
	{
		if (wDataSize!=sizeof(CMD_S_ChangeBanker)) 
			return 0;

		CMD_S_ChangeBanker* pChangeBanker = (CMD_S_ChangeBanker *)pBuffer;
		if (isSelf(m_wCurBanker))
		{
			SUser* pUser = GetUserInfo();

			CString szMessage;
			szMessage.Format("[%d][%d]��ׯ��� ��ׯ����%d �ɼ�%I64d", pUser->dwUserID, 
				pUser->dwGameID, pUser->wCurUpBanker, pUser->nBankerCurWin);
			LogEvent(szMessage, TraceLevel_Debug);

			pUser->wCurUpBanker		= 0;
			pUser->nBankerCurWin	= 0;			
		}

		m_wCurBanker	= pChangeBanker->wChairID;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		SmallNineAndroid::OnStartJetton(const void* pBuffer, WORD wDataSize)
	{
		CMD_S_JettonStart* pJettonStart = (CMD_S_JettonStart*)(pBuffer);
		m_fChipTime	= pJettonStart->cbTimeLeave;
		m_bChipIn	= TRUE;

		OnUpdateRobotScoreEnd();
		return true;
	}
}