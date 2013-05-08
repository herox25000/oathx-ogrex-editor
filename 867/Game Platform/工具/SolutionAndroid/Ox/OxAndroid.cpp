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

	static WORD		oxCurTableID =  4;

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	Ox::Ox(DWORD dwUserID, double fOnlineTime)
		: IAndroid(dwUserID, fOnlineTime), m_bOffline(FALSE),m_pDesk(NULL), m_wTableCount(0), m_wChairCount(0)
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
				WORD wBegin = pConfig->wMinTableID;
				WORD wEnd	= pConfig->wMaxTableID;

				while( wBegin < wEnd )
				{
					int nCount = m_pUserManager->GetTableChairCount(oxCurTableID);
					if (nCount < 4)
					{
						wTableID	= oxCurTableID;
						wChairID	= m_pUserManager->GetEmptyChairID(wTableID);
					}
					else
					{
						oxCurTableID = AndroidTimer::rdit(pConfig->wMinTableID, pConfig->wMaxTableID);
					}

					if (wTableID != INVALID_TABLE && wChairID != INVALID_CHAIR)
						return true;

					wBegin ++;
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

		SUser* pUser = GetUserInfo();
		if (pUser && !m_bOffline)
		{
			UpdateOnline(fElapsed);
			UpdateTimer(fElapsed);
			OnChange(fElapsed);
		}

		return 0;
	}

	bool		Ox::OnChange(float fElapsed)
	{
		SUser* pUser = GetUserInfo();
		if (pUser == NULL)
			return 0;

		int nCount = m_pUserManager->GetTableChairCount(pUser->wTableID);
		if (nCount == 1)
		{
			m_fWaitTime -= fElapsed;
			if (m_fWaitTime <= 0)
			{
				m_ClientSocket->SendData(MDM_GR_USER, 
					SUB_GR_USER_STANDUP_REQ);

				m_fWaitTime = MAX_WAIT_TIME;
			}
		}

		return true;
	}

	bool		Ox::UpdateOnline(float fElapsed)
	{
		m_fElapsed += fElapsed;
		if ((m_fElapsed / 60) >= m_fOnlineTime)
		{
			SUser* pUser = GetUserInfo();
			if (pUser)
			{
				if (pUser->cbUserStatus == US_PLAY)
				{
					m_bOffline = TRUE;
					return true;
				}
			}
		
			SetStatus(US_OFFLINE);
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

		OnBanker();

		WORD wTableID = INVALID_TABLE;
		WORD wChairID = INVALID_CHAIR;
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
		m_ClientSocket->SendData(MDM_GF_FRAME, SUB_GF_INFO, &Info, sizeof(Info));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnReset()
	{	
		m_fWaitTime			= MAX_WAIT_TIME;
		m_nTurnMaxScore		= 0;
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
				m_pDesk			= new SDesk[m_wTableCount];
			}
			break;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnGameStatus(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GR_TABLE_INFO:		//桌子信息
			{
				//变量定义
				CMD_GR_TableInfo * pTableInfo	= (CMD_GR_TableInfo *)pBuffer;
				const WORD wHeadSize			= sizeof(CMD_GR_TableInfo) - sizeof(pTableInfo->TableStatus);

				if (wDataSize<wHeadSize)
					return 0;
				if ((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))!=wDataSize) 
					return 0;

				m_wTableCount = pTableInfo->wTableCount;

				//消息处理
				for (WORD i=0;i<pTableInfo->wTableCount;i++)
				{
					m_pDesk[i].wTableID		= i;
					m_pDesk[i].bPlayStatus	= pTableInfo->TableStatus[i].bPlayStatus ? true : 0;
					m_pDesk[i].bTableLock	= pTableInfo->TableStatus[i].bTableLock ? true : 0;
				}
			}
			break;

		case SUB_GR_TABLE_STATUS:	//桌子状态
			{
				CMD_GR_TableStatus * pTableStatus = (CMD_GR_TableStatus *)pBuffer;
				for (int i=0; i<m_wTableCount; i++)
				{
					if (m_pDesk[i].wTableID == pTableStatus->wTableID)
					{
						m_pDesk[i].bPlayStatus = pTableStatus->bPlayStatus;
						m_pDesk[i].bTableLock	= pTableStatus->bTableLock;
					}
				}
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

				SUser* pUser = GetUserInfo();
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

				SUser* pUser = GetUserInfo();
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

				SUser* pUser = GetUserInfo();
				if (pUser)
				{
					CopyMemory(m_byCard, pStatusPlay->cbHandCardData[pUser->wChairID], MAX_COUNT);

					//控件处理
					if(pStatusPlay->bOxCard[pUser->wChairID] == 0xff)
					{
						SetTimer(OXT_OPEN_CARD, AndroidTimer::rdft(6, 10));
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
				SendData(MDM_GF_FRAME, SUB_GF_USER_READY);
				
				CString szMessage;
				szMessage.Format("[%d] 准备", GetUserID());
				LogEvent(szMessage, TraceLevel_Normal);
			}
			break;
		case OXT_CALL_BANKER:
			{
				SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
				if (pConfig)
				{
					int nBankerRate = rand() % 100;

					CMD_C_CallBanker CallBanker;
					CallBanker.bBanker = pConfig->wBankerRate >= nBankerRate ? 1 : 0;

					SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));

					CString szMessage;
					szMessage.Format("[%d] 叫庄", GetUserID());
					LogEvent(szMessage, TraceLevel_Normal);
				}
			}
			break;
		case OXT_OPEN_CARD:
			{
				//发送消息
				CMD_C_OxCard OxCard;
				OxCard.bOX=(GetCardType(m_byCard, MAX_COUNT) > 0 ) ? TRUE : FALSE;

				SendData(MDM_GF_GAME, SUB_C_OPEN_CARD, &OxCard, sizeof(OxCard));


				CString szMessage;
				szMessage.Format("[%d] 开牌", GetUserID());
				LogEvent(szMessage, TraceLevel_Normal);

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

				CString szMessage;
				szMessage.Format("[%d] 下注(%I64d, %I64d)", GetUserID(), AddScore.lScore, m_nTurnMaxScore);
				LogEvent(szMessage, TraceLevel_Normal);
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

		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			CMD_S_GameStart* pGameStart	= (CMD_S_GameStart *)pBuffer;

			m_nTurnMaxScore				= pGameStart->lTurnMaxScore;
			m_wCurBanker				= pGameStart->wBankerUser;

			if (pUser->wChairID != m_wCurBanker && m_nTurnMaxScore > 0)
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

		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;
			CopyMemory(m_byCard, pSendCard->cbCardData[pUser->wChairID], MAX_COUNT);

			int nCount = m_pUserManager->GetTableChairCount(pUser->wTableID);
			SetTimer(OXT_OPEN_CARD, nCount * AndroidTimer::rdit(2, 6));
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
		
		if (m_bOffline)
		{
			Shutdown();
			SetStatus(US_OFFLINE);
			return true;
		}

		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
			
			OnBanker();

			pUser->nWinScore += pGameEnd->lGameScore[pUser->wChairID];
			if (pUser->nWinScore >= pConfig->nMaxWinScore)
			{
				CString szMessage;
				szMessage.Format("[%d][%s]已赢取了额定金币，立刻下线", GetUserID(), pUser->szName);
				LogEvent(szMessage, TraceLevel_Debug);
				SetStatus(US_OFFLINE);
				return true;
			}

			if (pUser->nWinScore <= (-pConfig->nMaxWinScore))
			{
				CString szMessage;
				szMessage.Format("[%d][%s]已输掉额定金币，立刻下线", GetUserID(), pUser->szName);
				LogEvent(szMessage, TraceLevel_Debug);
				SetStatus(US_OFFLINE);
				return true;
			}
	
			SetTimer(OXT_START_GAME, GetWorkTime());
		}

		//清理变量
		m_wCurBanker	= INVALID_CHAIR;
		m_nTurnMaxScore = 0;
		ZeroMemory(m_byCard,sizeof(m_byCard));

		return true;
	}

	bool		Ox::SetTimer(DWORD dwID, double fElapsed)
	{
		TimerItemRegister::iterator it = m_TimerItemActive.find(dwID);
		if ( it == m_TimerItemActive.end() )
		{
			m_TimerItemActive.insert(
				TimerItemRegister::value_type(dwID, new STimerItem(dwID, fElapsed, TRUE))
				);
		}
		else
		{
			it->second->fElapsed	= fElapsed;
			it->second->bActive		= TRUE;
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

		return 0;
	}

	void		Ox::UpdateTimer(float fElapsed)
	{
		for (TimerItemRegister::iterator it=m_TimerItemActive.begin();
			it!=m_TimerItemActive.end(); it++)
		{
			if (it->second->bActive)
			{
				it->second->fElapsed -= fElapsed;
				if ( it->second->fElapsed <= 0)
				{
					OnTimerEvent(it->second->dwID);
					
					it->second->bActive	= FALSE;
				}
			}
		}
	}
}