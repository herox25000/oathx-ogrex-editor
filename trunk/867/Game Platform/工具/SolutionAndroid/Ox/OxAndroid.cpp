#include "stdafx.h"
#include "OxAndroid.h"
#include "AndroidTimer.h"

namespace O2
{
	enum {
		OXT_CALL_BANKER,
		OXT_USER_ADD_SCORE,
		OXT_OPEN_CARD,
		OXT_START_GAME,
	};

#define OXT_MIN_TIME	1
#define OXT_MAX_TIME	6
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

	}

	//////////////////////////////////////////////////////////////////////////
	//��ȡ����
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
	//��ȡ��ֵ
	BYTE		Ox::GetCardValue(BYTE cbCardData) 
	{
		return cbCardData&LOGIC_MASK_VALUE; 
	}

	//��ȡ��ɫ
	BYTE		Ox::GetCardColor(BYTE cbCardData) 
	{ 
		return cbCardData&LOGIC_MASK_COLOR; 
	}

	//�߼���ֵ
	BYTE		Ox::GetCardLogicValue(BYTE cbCardData)
	{
		//�˿�����
		BYTE bCardColor=GetCardColor(cbCardData);
		BYTE bCardValue=GetCardValue(cbCardData);

		//ת����ֵ
		return (bCardValue>10)?(10):bCardValue;
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
				UpdateTimer(fElapsed);
			}
			break;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		Ox::OnSwitchTable()
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
	bool		Ox::OnReset()
	{	
		m_wTableCount	= 0;
		m_wChairCount	= 0;
		m_nTurnMaxScore	= 0;
		ZeroMemory(m_byCard, sizeof(m_byCard));

		return IAndroid::OnReset();
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
				SetTimer(OXT_START_GAME, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
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
						SetTimer(OXT_CALL_BANKER, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
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
				m_nTurnMaxScore					= pStatusScore->lTurnMaxScore;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					//���ó���
					if (pStatusScore->lTurnMaxScore > 0L && pStatusScore->lTableScore[pUser->wChairID] == 0L )
					{
						SetTimer(OXT_USER_ADD_SCORE, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
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

				CMD_S_StatusPlay* pStatusPlay	= (CMD_S_StatusPlay *)(pBuffer);
				m_nTurnMaxScore					= pStatusPlay->lTurnMaxScore;

				SUser* pUser = m_pUserManager->Search(m_dwUserID);
				if (pUser)
				{
					CopyMemory(m_byCard, pStatusPlay->cbHandCardData[pUser->wChairID], MAX_COUNT);

					//�ؼ�����
					if(pStatusPlay->bOxCard[pUser->wChairID] == 0xff)
					{
						SetTimer(OXT_OPEN_CARD, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
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
					////���ñ���
					CMD_C_CallBanker CallBanker;
					CallBanker.bBanker = 1;

					SendData(MDM_GF_GAME, SUB_C_CALL_BANKER,&CallBanker,sizeof(CallBanker));
				}
			}
			break;
		case OXT_OPEN_CARD:
			{
				if (m_wStaus == US_SIT)
				{
					//������Ϣ
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

				//������Ϣ
				CMD_C_AddScore AddScore;
				AddScore.lScore = nUserMaxScore[rand()%4];
				SendData(MDM_GF_GAME, SUB_C_ADD_SCORE, &AddScore, sizeof(AddScore));
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
	bool		Ox::OnSubCallBanker(const void * pBuffer, WORD wDataSize)
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
				SetTimer(OXT_CALL_BANKER, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
			}
		}

		return true;
	}

	//��Ϸ��ʼ
	bool		Ox::OnSubGameStart(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_GameStart)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;

			m_nTurnMaxScore				= pGameStart->lTurnMaxScore;
			if (m_nTurnMaxScore > 0)
			{
				SetTimer(OXT_USER_ADD_SCORE, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
			}
		}

		return true;
	}

	//�û���ע
	bool		Ox::OnSubAddScore(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_AddScore)) return false;
		CMD_S_AddScore * pAddScore=(CMD_S_AddScore *)pBuffer;

		return true;
	}

	//������Ϣ
	bool		Ox::OnSubSendCard(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_SendCard)) 
			return 0;

		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
		{
			CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;

			BYTE m_byCard[MAX_COUNT];
			CopyMemory(m_byCard, pSendCard->cbCardData[pUser->wChairID], MAX_COUNT);

			SetTimer(OXT_OPEN_CARD, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
		}

		return true;
	}

	//�û�̯��
	bool		Ox::OnSubOpenCard(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_Open_Card)) return false;
		CMD_S_Open_Card* pOpenCard=(CMD_S_Open_Card *)pBuffer;

		return true;
	}

	//�û�ǿ��
	bool		Ox::OnSubPlayerExit(const void * pBuffer, WORD wDataSize)
	{
		//Ч������
		if (wDataSize!=sizeof(CMD_S_PlayerExit)) return false;
		CMD_S_PlayerExit * pPlayerExit=(CMD_S_PlayerExit *)pBuffer;

		return true;
	}	

	//��Ϸ����
	bool		Ox::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
	{
		//Ч�����
		if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
		CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

		if (m_wStaus == US_SIT)
		{
			SetTimer(OXT_START_GAME, AndroidTimer::rdft(OXT_MIN_TIME, OXT_MAX_TIME));
		}
		

		//�������
		m_nTurnMaxScore = 0;
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