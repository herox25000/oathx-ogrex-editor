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
	//��ȡ����
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
	//��ȡ��ֵ
	BYTE		Ox4::GetCardValue(BYTE cbCardData) 
	{
		return cbCardData&LOGIC_MASK_VALUE; 
	}

	//��ȡ��ɫ
	BYTE		Ox4::GetCardColor(BYTE cbCardData) 
	{ 
		return cbCardData&LOGIC_MASK_COLOR; 
	}

	//�߼���ֵ
	BYTE		Ox4::GetCardLogicValue(BYTE cbCardData)
	{
		//�˿�����
		BYTE bCardColor=GetCardColor(cbCardData);
		BYTE bCardValue=GetCardValue(cbCardData);

		//ת����ֵ
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
		//�������ݰ�
		CMD_GR_UserSitReq UserSitReq;
		memset(&UserSitReq,0,sizeof(UserSitReq));
		UserSitReq.wTableID	= rand() % 60;
		UserSitReq.wChairID	= rand() % 4;

		//�������ݰ�
		WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
		m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_SIT_REQ, &UserSitReq, wSendSize);
		
		//��ȡ����
		CMD_GF_Info Info;
		ZeroMemory(&Info,sizeof(Info));
		Info.bAllowLookon	= true;

		//������Ϣ
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
					SendData(MDM_GF_FRAME,SUB_GF_USER_READY);
				}
			}
			break;

		case GS_TK_CALL:	// ��ׯ״̬
			{
				//Ч������
				if (wDataSize!=sizeof(CMD_S_StatusCall)) 
					return 0;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					CMD_S_StatusCall* pStatusCall = (CMD_S_StatusCall*)(pBuffer);
					//ʼ���û�
					if(pStatusCall->wCallBanker == pUser->wChairID)
					{
						//���ñ���
						CMD_C_CallBanker CallBanker;
						CallBanker.bBanker = 0;

						SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
					}
				}
			}
			break;

		case GS_TK_SCORE:	//��ע״̬
			{
				//Ч������
				if (wDataSize!=sizeof(CMD_S_StatusScore)) 
					return 0;

				CMD_S_StatusScore* pStatusScore = (CMD_S_StatusScore *)(pBuffer);
				
				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					//���ó���
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

						//������Ϣ
						CMD_C_AddScore AddScore;
						AddScore.lScore = nUserMaxScore[rand()%4];
						SendData(MDM_GF_GAME, SUB_C_ADD_SCORE,&AddScore,sizeof(AddScore));
					}
				}

				return true;
			}
			break;

		case GS_TK_PLAYING:	//��Ϸ״̬
			{
				//Ч������
				if (wDataSize!=sizeof(CMD_S_StatusPlay))
					return 0;

				CMD_S_StatusPlay* pStatusPlay = (CMD_S_StatusPlay *)(pBuffer);

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					BYTE byCard[MAX_COUNT];
					CopyMemory(byCard, pStatusPlay->cbHandCardData[pUser->wChairID], MAX_COUNT);

					//�ؼ�����
					if(pStatusPlay->bOxCard[pUser->wChairID] == 0xff)
					{
						//������Ϣ
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
		case SUB_S_CALL_BANKER:	//�û���ׯ
			{
				//��Ϣ����
				return OnSubCallBanker(pBuffer,wDataSize);
			}
		case SUB_S_GAME_START:	//��Ϸ��ʼ
			{
				//��Ϣ����
				return OnSubGameStart(pBuffer,wDataSize);
			}
		case SUB_S_ADD_SCORE:	//�û���ע
			{
				//��Ϣ����
				return OnSubAddScore(pBuffer,wDataSize);
			}
		case SUB_S_SEND_CARD:	//������Ϣ
			{
				//��Ϣ����
				return OnSubSendCard(pBuffer,wDataSize);
			}
		case SUB_S_OPEN_CARD:	//�û�̯��
			{
				//��Ϣ����
				return OnSubOpenCard(pBuffer,wDataSize);
			}
		case SUB_S_PLAYER_EXIT:	//�û�ǿ��
			{
				//��Ϣ����
				return OnSubPlayerExit(pBuffer,wDataSize);
			}
		case SUB_S_GAME_END:	//��Ϸ����
			{
				//��Ϣ����
				return OnSubGameEnd(pBuffer,wDataSize);
			}
		}

		return true;
	}


	//�û���ׯ
	bool		Ox4::OnSubCallBanker(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_CallBanker))
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_StatusCall* pStatusCall = (CMD_S_StatusCall*)(pBuffer);
			//ʼ���û�
			if(pStatusCall->wCallBanker == pUser->wChairID)
			{
				//���ñ���
				CMD_C_CallBanker CallBanker;
				CallBanker.bBanker = 0;

				SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
			}
		}

		return true;
	}

	//��Ϸ��ʼ
	bool		Ox4::OnSubGameStart(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
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

				//������Ϣ
				CMD_C_AddScore AddScore;
				AddScore.lScore = nUserMaxScore[rand()%4];
				SendData(MDM_GF_GAME, SUB_C_ADD_SCORE,&AddScore,sizeof(AddScore));
			}
		}
		
		return true;
	}

	//�û���ע
	bool		Ox4::OnSubAddScore(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_AddScore)) return false;
		CMD_S_AddScore * pAddScore=(CMD_S_AddScore *)pBuffer;

		return true;
	}

	//������Ϣ
	bool		Ox4::OnSubSendCard(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_SendCard)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;

			BYTE byCard[MAX_COUNT];
			CopyMemory(byCard, pSendCard->cbCardData[pUser->wChairID], MAX_COUNT);

			//������Ϣ
			CMD_C_OxCard OxCard;
			OxCard.bOX=(GetCardType(byCard, MAX_COUNT) > 0 ) ? TRUE : FALSE;

			SendData(MDM_GF_GAME, SUB_C_OPEN_CARD, &OxCard, sizeof(OxCard));
			
		}

		return true;
	}

	//�û�̯��
	bool		Ox4::OnSubOpenCard(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_Open_Card)) return false;
		CMD_S_Open_Card* pOpenCard=(CMD_S_Open_Card *)pBuffer;

		return true;
	}

	//�û�ǿ��
	bool		Ox4::OnSubPlayerExit(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_PlayerExit)) return false;
		CMD_S_PlayerExit * pPlayerExit=(CMD_S_PlayerExit *)pBuffer;

		return true;
	}	

	//��Ϸ����
	bool		Ox4::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
	{
		//Ч�����
		if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
		CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;
		
		if (m_wStaus == STATUS_SITDOWN)
		{
			SendData(MDM_GF_FRAME, SUB_GF_USER_READY);
		}

		return true;
	}
}