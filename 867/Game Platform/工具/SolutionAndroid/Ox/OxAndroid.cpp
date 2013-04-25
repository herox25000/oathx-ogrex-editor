#include "stdafx.h"
#include "OxAndroid.h"
#include "AndroidTimer.h"
#include "ConfigFile.h"

namespace O2
{
	enum {
		OXT_CALL_BANKER,
		OXT_USER_ADD_SCORE,
		OXT_OPEN_CARD,
		OXT_START_GAME,
	};

	static WORD		s_wCurTableID = INVALID_TABLE;

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	Ox::Ox(DWORD dwUserID, double fOnlineTime)
		: IAndroid(dwUserID, fOnlineTime)
	{
		OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	Ox::~Ox()
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.begin();
		while ( itA != m_TimerItemActive.end() )
		{
			delete itA->second; itA = m_TimerItemActive.erase(itA);
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.begin();
		while ( itD != m_TimerItemDetive.end() )
		{
			delete itD->second; itD = m_TimerItemDetive.erase(itD);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//获取类型
	BYTE		Ox::GetCardType(BYTE cbCardData[], BYTE cbCardCount)
	{
		ASSERT(cbCardCount==MAX_COUNT);

		BYTE bKingCount=0,bTenCount=0;
		for(BYTE i=0;i<cbCardCount;i++)
		{
			if(GetCardValue(cbCardData[i])>10)
			{
				bKingCount++;
			}
			else if(GetCardValue(cbCardData[i])==10)
			{
				bTenCount++;
			}
		}

		if(bKingCount==MAX_COUNT)
		{
			return OX_FIVEKING;
		}
		else if(bKingCount==MAX_COUNT-1 && bTenCount==1)
		{
			return OX_FOURKING;
		}

		BYTE bTemp[MAX_COUNT];
		BYTE bSum=0;
		for (BYTE i=0;i<cbCardCount;i++)
		{
			bTemp[i]=GetCardLogicValue(cbCardData[i]);
			bSum+=bTemp[i];
		}

		for (BYTE i=0;i<cbCardCount-1;i++)
		{
			for (BYTE j=i+1;j<cbCardCount;j++)
			{
				if((bSum-bTemp[i]-bTemp[j])%10==0)
				{
					return ((bTemp[i]+bTemp[j])>10)?(bTemp[i]+bTemp[j]-10):(bTemp[i]+bTemp[j]);
				}
			}
		}

		return OX_VALUE0;
	}
	//获取数值
	BYTE		Ox::GetCardValue(BYTE cbCardData) 
	{
		return cbCardData&LOGIC_MASK_VALUE; 
	}

	//获取花色
	BYTE		Ox::GetCardColor(BYTE cbCardData) 
	{ 
		return cbCardData&LOGIC_MASK_COLOR; 
	}

	//逻辑数值
	BYTE		Ox::GetCardLogicValue(BYTE cbCardData)
	{
		//扑克属性
		BYTE bCardColor=GetCardColor(cbCardData);
		BYTE bCardValue=GetCardValue(cbCardData);

		//转换数值
		return (bCardValue>10)?(10):bCardValue;
	}

	WORD		Ox::GetWorkTime()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig)
			return AndroidTimer::rdit(pConfig->wMinWorkTime, pConfig->wMaxWorkTime);

		return 0;
	}

	bool		Ox::GetTableID(WORD& wTableID, WORD& wChairID)
	{
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
			
			if (pUser->nScore >= pConfig->nMinScore && pUser->nScore <= pConfig->nMaxScore)
			{
				if (s_wCurTableID == INVALID_TABLE)
					s_wCurTableID = AndroidTimer::rdit(pConfig->wMinTableID, pConfig->wMaxTableID);

				WORD wCount = m_pUserManager->GetTableChairCount(s_wCurTableID);
				if (wCount <= rand() % 4)
				{
					wChairID = m_pUserManager->GetEmptyChairID(s_wCurTableID);
					wTableID = s_wCurTableID;
					return true;
				}
				else
				{
					s_wCurTableID = AndroidTimer::rdit(pConfig->wMinTableID, pConfig->wMaxTableID);
				}
			}
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::Update(float fElapsed)
	{
		if (!IAndroid::Update(fElapsed))
			return 0;

		switch( m_wStaus )
		{
		case US_SIT:
			{
				UpdateOnline(fElapsed);
				UpdateTimer(fElapsed);
			}
			break;
		}

		return 0;
	}

	bool		Ox::UpdateOnline(float fElapsed)
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
					szMessage.Format("[%d][%d]到达在线时间, 立刻下线", GetUserID(), GetGameID());
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
	bool		Ox::OnSwitchTable()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig == NULL)
			return 0;

		SUser* pUser = GetUserInfo();
		if (pUser == NULL)
			return 0;

		INT64 nMin;
		INT64 nMax;
		if (pUser->nScore < pConfig->nMinScore)
		{
			nMin = pConfig->nMinScore - pUser->nScore;
			nMax = pConfig->nMaxScore - pUser->nScore;

			GetScoreFromBanker( AndroidTimer::rdit( nMin,  nMax) );
			return 0;
		}
		else if (pUser->nScore > pConfig->nMaxScore)
		{
			nMin = pUser->nScore - pConfig->nMaxScore;
			nMax = pUser->nScore - pConfig->nMinScore;

			SaveScoreToBanker( AndroidTimer::rdit( nMin,  nMax) );
			return 0;
		}

		WORD wTableID;
		WORD wChairID;
		if (!GetTableID(wTableID, wChairID))
			return 0;

		//构造数据包
		CMD_GR_UserSitReq UserSitReq;
		memset(&UserSitReq, 0, sizeof(UserSitReq));
		UserSitReq.wTableID	= wTableID;
		UserSitReq.wChairID	= wChairID;

		//发送数据包
		WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
		m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_SIT_REQ, &UserSitReq, wSendSize);
	
		m_wSitReqCount ++;
		CString szMessage;
		szMessage.Format("[%d]第%d次请求坐下 桌子ID[%d] 椅子ID[%d]", m_dwUserID, m_wSitReqCount, wTableID, wChairID);
		CTraceService::TraceString(szMessage,
			TraceLevel_Normal);

		//获取场景
		CMD_GF_Info Info;
		ZeroMemory(&Info,sizeof(Info));
		Info.bAllowLookon	= true;

		//发送消息
		m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO, &Info, sizeof(Info));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnReset()
	{	
		m_wTableCount		= 0;
		m_wChairCount		= 0;
		m_nTurnMaxScore		= 0;
		m_nChipInScore		= 0;
		m_wCurBanker		= INVALID_CHAIR;
		ZeroMemory(m_byCard, sizeof(m_byCard));

		return IAndroid::OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnBanker()
	{
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();

			INT64 nMin;
			INT64 nMax;
			if (pUser->nScore < pConfig->nMinScore)
			{
				nMin = pConfig->nMinScore - pUser->nScore;
				nMax = pConfig->nMaxScore - pUser->nScore;

				GetScoreFromBanker( AndroidTimer::rdit( nMin,  nMax) );
			}
			else if (pUser->nScore > pConfig->nMaxScore)
			{
				nMin = pUser->nScore - pConfig->nMaxScore;
				nMax = pUser->nScore - pConfig->nMinScore;

				SaveScoreToBanker( AndroidTimer::rdit( nMin,  nMax) );
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnSocketServerInfo(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch( Command.wSubCmdID )
		{
		case SUB_GR_SERVER_INFO:
			{
				CMD_GR_ServerInfo* pServerInfo = (CMD_GR_ServerInfo*)(pBuffer);

				m_wTableCount	= pServerInfo->wTableCount;
				m_wChairCount	= pServerInfo->wChairCount;
			}
			break;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		switch (cbGameStation)
		{
		case GS_FREE:
			{
				SetTimer(OXT_START_GAME, GetWorkTime());
			}
			break;

		case GS_TK_CALL:	// 叫庄状态
			{
				//效验数据
				if (wDataSize!=sizeof(CMD_S_StatusCall)) 
					return 0;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					CMD_S_StatusCall* pStatusCall = (CMD_S_StatusCall*)(pBuffer);
					//始叫用户
					if(pStatusCall->wCallBanker == pUser->wChairID)
					{
						SetTimer(OXT_CALL_BANKER, GetWorkTime());
					}
				}
			}
			break;

		case GS_TK_SCORE:	//下注状态
			{
				//效验数据
				if (wDataSize!=sizeof(CMD_S_StatusScore)) 
					return 0;

				CMD_S_StatusScore* pStatusScore = (CMD_S_StatusScore *)(pBuffer);
				m_nTurnMaxScore					= pStatusScore->lTurnMaxScore;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					//设置筹码
					if (pStatusScore->lTurnMaxScore > 0L && pStatusScore->lTableScore[pUser->wChairID] == 0L )
					{
						SetTimer(OXT_USER_ADD_SCORE, GetWorkTime());
					}
				}

				return true;
			}
			break;

		case GS_TK_PLAYING:	//游戏状态
			{
				//效验数据
				if (wDataSize!=sizeof(CMD_S_StatusPlay))
					return 0;

				CMD_S_StatusPlay* pStatusPlay	= (CMD_S_StatusPlay *)(pBuffer);
				m_nTurnMaxScore					= pStatusPlay->lTurnMaxScore;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					CopyMemory(m_byCard, pStatusPlay->cbHandCardData[pUser->wChairID], MAX_COUNT);

					//控件处理
					if(pStatusPlay->bOxCard[pUser->wChairID] == 0xff)
					{
						SetTimer(OXT_OPEN_CARD, GetWorkTime());
					}
				}
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnTimerEvent(DWORD dwID)
	{
		switch( dwID )
		{
		case OXT_START_GAME:
			{
				if (m_wStaus == US_SIT)
				{
					SendData(MDM_GF_FRAME, SUB_GF_USER_READY);
				}
			}
			break;
		case OXT_CALL_BANKER:
			{
				if (m_wStaus == US_SIT)
				{
					SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
					if (pConfig)
					{
						int nBankerRate = rand() % 100;

						CMD_C_CallBanker CallBanker;
						CallBanker.bBanker = pConfig->wBankerRate >= nBankerRate ? 1 : 0;

						SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
					}
				}
			}
			break;
		case OXT_OPEN_CARD:
			{
				if (m_wStaus == US_SIT)
				{
					//发送消息
					CMD_C_OxCard OxCard;
					OxCard.bOX=(GetCardType(m_byCard, MAX_COUNT) > 0 ) ? TRUE : FALSE;

					SendData(MDM_GF_GAME, SUB_C_OPEN_CARD, &OxCard, sizeof(OxCard));
				}
			}
			break;
		case OXT_USER_ADD_SCORE:
			{
				INT64 nUserMaxScore[4];
				ZeroMemory(nUserMaxScore, sizeof(nUserMaxScore));

				INT64 nTempScore = m_nTurnMaxScore;
				for (int i=0; i<4; i++)
				{
					if (i>0)
						nTempScore /= 2;

					nUserMaxScore[i] = max(nTempScore, 1L);
				}

				//发送消息
				CMD_C_AddScore AddScore;
				AddScore.lScore = nUserMaxScore[rand()%4];
				SendData(MDM_GF_GAME, SUB_C_ADD_SCORE, &AddScore, sizeof(AddScore));

				m_nChipInScore	+= AddScore.lScore;
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnGameMessage(WORD wSubCmdID, const void * pBuffer, 
		WORD wDataSize)
	{
		switch (wSubCmdID)
		{
		case SUB_S_CALL_BANKER:	//用户叫庄
			{
				//消息处理
				return OnSubCallBanker(pBuffer,wDataSize);
			}
		case SUB_S_GAME_START:	//游戏开始
			{
				//消息处理
				return OnSubGameStart(pBuffer,wDataSize);
			}
		case SUB_S_ADD_SCORE:	//用户下注
			{
				//消息处理
				return OnSubAddScore(pBuffer,wDataSize);
			}
		case SUB_S_SEND_CARD:	//发牌消息
			{
				//消息处理
				return OnSubSendCard(pBuffer,wDataSize);
			}
		case SUB_S_OPEN_CARD:	//用户摊牌
			{
				//消息处理
				return OnSubOpenCard(pBuffer,wDataSize);
			}
		case SUB_S_PLAYER_EXIT:	//用户强退
			{
				//消息处理
				return OnSubPlayerExit(pBuffer,wDataSize);
			}
		case SUB_S_GAME_END:	//游戏结束
			{
				//消息处理
				return OnSubGameEnd(pBuffer,wDataSize);
			}
		}

		return true;
	}


	//用户叫庄
	bool		Ox::OnSubCallBanker(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_CallBanker))
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_StatusCall* pStatusCall = (CMD_S_StatusCall*)(pBuffer);
			//始叫用户
			if(pStatusCall->wCallBanker == pUser->wChairID)
			{
				SetTimer(OXT_CALL_BANKER, GetWorkTime());
			}
		}

		return true;
	}

	//游戏开始
	bool		Ox::OnSubGameStart(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_GameStart)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_GameStart* pGameStart	= (CMD_S_GameStart *)pBuffer;

			m_nTurnMaxScore				= pGameStart->lTurnMaxScore;
			m_wCurBanker				= pGameStart->wBankerUser;
			if (m_nTurnMaxScore > 0)
			{
				SetTimer(OXT_USER_ADD_SCORE, GetWorkTime());
			}			
		}

		return true;
	}

	//用户下注
	bool		Ox::OnSubAddScore(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_AddScore)) return false;
		CMD_S_AddScore * pAddScore=(CMD_S_AddScore *)pBuffer;

		return true;
	}

	//发牌消息
	bool		Ox::OnSubSendCard(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_SendCard)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;
			CopyMemory(m_byCard, pSendCard->cbCardData[pUser->wChairID], MAX_COUNT);

			SetTimer(OXT_OPEN_CARD, GetWorkTime());
		}

		return true;
	}

	//用户摊牌
	bool		Ox::OnSubOpenCard(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_Open_Card)) return false;
		CMD_S_Open_Card* pOpenCard=(CMD_S_Open_Card *)pBuffer;

		return true;
	}

	//用户强退
	bool		Ox::OnSubPlayerExit(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_PlayerExit)) return false;
		CMD_S_PlayerExit * pPlayerExit=(CMD_S_PlayerExit *)pBuffer;

		return true;
	}	

	//游戏结束
	bool		Ox::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
	{
		//效验参数
		if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
		CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

		if (m_wStaus == US_SIT)
		{
			SetTimer(OXT_START_GAME, GetWorkTime());
		}
		
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();

			INT64 nMin;
			INT64 nMax;
			if (pUser->nScore < pConfig->nMinScore)
			{
				nMin = pConfig->nMinScore - pUser->nScore;
				nMax = pConfig->nMaxScore - pUser->nScore;

				GetScoreFromBanker( AndroidTimer::rdit( nMin,  nMax) );
			}
			else if (pUser->nScore > pConfig->nMaxScore)
			{
				nMin = pUser->nScore - pConfig->nMaxScore;
				nMax = pUser->nScore - pConfig->nMinScore;

				SaveScoreToBanker( AndroidTimer::rdit( nMin,  nMax) );
			}
			
			pUser->nWinScore += pGameEnd->lGameScore[pUser->wChairID];
			if (pUser->nWinScore >= pConfig->nMaxWinScore)
			{
				CString szMessage;
				szMessage.Format("[%d][%s]已赢取了额定金币，立刻下线", GetUserID(), pUser->szName);
				LogEvent(szMessage, TraceLevel_Debug);
				SetStatus(US_OFFLINE);
			}

			if (pUser->nWinScore <= (-pConfig->nMaxWinScore))
			{
				CString szMessage;
				szMessage.Format("[%d][%s]已输掉额定金币，立刻下线", GetUserID(), pUser->szName);
				LogEvent(szMessage, TraceLevel_Debug);
				SetStatus(US_OFFLINE);
			}
		}

		//清理变量
		m_wCurBanker	= INVALID_CHAIR;
		m_nTurnMaxScore = 0;
		m_nChipInScore	= 0;
		ZeroMemory(m_byCard,sizeof(m_byCard));

		return true;
	}

	bool		Ox::SetTimer(DWORD dwID, double fElapsed)
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.find(dwID);
		if ( itA != m_TimerItemActive.end())
		{
			itA->second->fElapsed	= fElapsed;
			return true;
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.find(dwID);
		if ( itD != m_TimerItemDetive.end() )
		{
			itD->second->fElapsed	= fElapsed;
			
			m_TimerItemActive.insert(
				TimerItemRegister::value_type(dwID, itD->second)
				);
			m_TimerItemDetive.erase(itD);
		}
		else
		{
			STimerItem* pItem = new STimerItem(dwID, fElapsed);
			m_TimerItemActive.insert(
				TimerItemRegister::value_type(dwID, pItem)
				);
		}

		return true;
	}

	bool		Ox::KillTimer(DWORD dwID)
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.find(dwID);
		if ( itA != m_TimerItemActive.end() )
		{
			delete itA->second; m_TimerItemActive.erase(itA);
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.find(dwID);
		if ( itD != m_TimerItemDetive.end() )
		{
			delete itD->second; m_TimerItemDetive.erase(itD);
		}
		return 0;
	}

	void		Ox::UpdateTimer(float fElapsed)
	{
		TimerItemRegister::iterator it = m_TimerItemActive.begin();
		while ( it != m_TimerItemActive.end() )
		{
			it->second->fElapsed -= fElapsed;
			if (it->second->fElapsed <= 0)
			{
				m_TimerItemDetive.insert(
					TimerItemRegister::value_type(it->second->dwID, it->second)
					);
				OnTimerEvent(it->second->dwID);

				it = m_TimerItemActive.erase(it);
			}
			else
			{
				it ++;
			}
		}
	}
}