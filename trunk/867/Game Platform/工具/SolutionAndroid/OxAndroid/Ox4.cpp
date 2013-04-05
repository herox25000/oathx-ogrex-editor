#include "stdafx.h"
#include "Ox4.h"

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	Ox4::Ox4(DWORD dwUserID, double fOnlineTime)
		: IAndroid(dwUserID, fOnlineTime)
	{
		OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	Ox4::~Ox4()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	//获取类型
	BYTE		Ox4::GetCardType(BYTE cbCardData[], BYTE cbCardCount)
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
	BYTE		Ox4::GetCardValue(BYTE cbCardData) 
	{
		return cbCardData&LOGIC_MASK_VALUE; 
	}

	//获取花色
	BYTE		Ox4::GetCardColor(BYTE cbCardData) 
	{ 
		return cbCardData&LOGIC_MASK_COLOR; 
	}

	//逻辑数值
	BYTE		Ox4::GetCardLogicValue(BYTE cbCardData)
	{
		//扑克属性
		BYTE bCardColor=GetCardColor(cbCardData);
		BYTE bCardValue=GetCardValue(cbCardData);

		//转换数值
		return (bCardValue>10)?(10):bCardValue;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox4::Update(float fElapsed)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox4::OnSwitchTable()
	{
		//构造数据包
		CMD_GR_UserSitReq UserSitReq;
		memset(&UserSitReq,0,sizeof(UserSitReq));
		UserSitReq.wTableID	= rand() % 60;
		UserSitReq.wChairID	= rand() % 4;

		//发送数据包
		WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
		m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_SIT_REQ, &UserSitReq, wSendSize);
		
		//获取场景
		CMD_GF_Info Info;
		ZeroMemory(&Info,sizeof(Info));
		Info.bAllowLookon	= true;

		//发送消息
		m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO, &Info, sizeof(Info));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox4::OnReset()
	{	
		m_wTableCount	= 0;
		m_wChairCount	= 0;
	
		return IAndroid::OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox4::OnSocketServerInfo(CMD_Command Command, void* pBuffer, WORD wDataSize)
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
	bool		Ox4::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		switch (cbGameStation)
		{
		case GS_FREE:
			{
				if (m_wStaus == STATUS_SITDOWN)
				{
					SendData(MDM_GF_FRAME, SUB_GF_USER_READY);
				}
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
						//设置变量
						CMD_C_CallBanker CallBanker;
						CallBanker.bBanker = 0;

						SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
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
				
				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					//设置筹码
					if (pStatusScore->lTurnMaxScore > 0L && pStatusScore->lTableScore[pUser->wChairID] == 0L )
					{
						INT64 nUserMaxScore[4];
						ZeroMemory(nUserMaxScore, sizeof(nUserMaxScore));

						INT64 nTempScore = pStatusScore->lTurnMaxScore;
						for (int i=0; i<4; i++)
						{
							if (i>0)
								nTempScore /= 2;

							nUserMaxScore[i] = max(nTempScore, 1L);
						}

						//发送消息
						CMD_C_AddScore AddScore;
						AddScore.lScore = nUserMaxScore[rand()%4];
						SendData(MDM_GF_GAME, SUB_C_ADD_SCORE,&AddScore,sizeof(AddScore));
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

				CMD_S_StatusPlay* pStatusPlay = (CMD_S_StatusPlay *)(pBuffer);

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					BYTE byCard[MAX_COUNT];
					CopyMemory(byCard, pStatusPlay->cbHandCardData[pUser->wChairID], MAX_COUNT);

					//控件处理
					if(pStatusPlay->bOxCard[pUser->wChairID] == 0xff)
					{
						//发送消息
						CMD_C_OxCard OxCard;
						OxCard.bOX=(GetCardType(byCard, MAX_COUNT) > 0 ) ? TRUE : FALSE;

						SendData(MDM_GF_GAME, SUB_C_OPEN_CARD, &OxCard, sizeof(OxCard));
					}
				}
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox4::OnGameMessage(WORD wSubCmdID, const void * pBuffer, 
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
	bool		Ox4::OnSubCallBanker(const void * pBuffer, WORD wDataSize)
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
				//设置变量
				CMD_C_CallBanker CallBanker;
				CallBanker.bBanker = 0;

				SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
			}
		}

		return true;
	}

	//游戏开始
	bool		Ox4::OnSubGameStart(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_GameStart)) 
			return 0;
		
		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;
			
			if (pGameStart->wBankerUser != pUser->wChairID)
			{
				INT64 nUserMaxScore[4];
				ZeroMemory(nUserMaxScore, sizeof(nUserMaxScore));

				INT64 nTempScore = pGameStart->lTurnMaxScore;
				for (int i=0; i<4; i++)
				{
					if (i>0)
						nTempScore /= 2;

					nUserMaxScore[i] = max(nTempScore, 1L);
				}

				//发送消息
				CMD_C_AddScore AddScore;
				AddScore.lScore = nUserMaxScore[rand()%4];
				SendData(MDM_GF_GAME, SUB_C_ADD_SCORE,&AddScore,sizeof(AddScore));
			}
		}
		
		return true;
	}

	//用户下注
	bool		Ox4::OnSubAddScore(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_AddScore)) return false;
		CMD_S_AddScore * pAddScore=(CMD_S_AddScore *)pBuffer;

		return true;
	}

	//发牌消息
	bool		Ox4::OnSubSendCard(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_SendCard)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;

			BYTE byCard[MAX_COUNT];
			CopyMemory(byCard, pSendCard->cbCardData[pUser->wChairID], MAX_COUNT);

			//发送消息
			CMD_C_OxCard OxCard;
			OxCard.bOX=(GetCardType(byCard, MAX_COUNT) > 0 ) ? TRUE : FALSE;

			SendData(MDM_GF_GAME, SUB_C_OPEN_CARD, &OxCard, sizeof(OxCard));
			
		}

		return true;
	}

	//用户摊牌
	bool		Ox4::OnSubOpenCard(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_Open_Card)) return false;
		CMD_S_Open_Card* pOpenCard=(CMD_S_Open_Card *)pBuffer;

		return true;
	}

	//用户强退
	bool		Ox4::OnSubPlayerExit(const void * pBuffer, WORD wDataSize)
	{
		//效验数据
		if (wDataSize!=sizeof(CMD_S_PlayerExit)) return false;
		CMD_S_PlayerExit * pPlayerExit=(CMD_S_PlayerExit *)pBuffer;

		return true;
	}	

	//游戏结束
	bool		Ox4::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
	{
		//效验参数
		if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
		CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;
		
		if (m_wStaus == STATUS_SITDOWN)
		{
			SendData(MDM_GF_FRAME, SUB_GF_USER_READY);
		}

		return true;
	}
}