#include "StdAfx.h"
#include ".\gameinterface.h"
#include "define.h"
#include "Resource.h"

CGameInterface::CGameInterface(void)
{
	m_wCurrentOutCard=255;
	m_IsCanOut=false;
}

CGameInterface::~CGameInterface(void)
{
}
bool   CGameInterface::SubDelayTime()
{
	if(DelayTime<-1)
		return true;
	DelayTime--;
	if(DelayTime>0)
	{
		return true;
	}
	switch(UserStatus)
	{
	case GAMESCORE:
		{
			//if(GameStatus==US_PLAY)
			OnScore();
			//else
			//	DelayTime=100;
			return true;
		}
	case OUTCARD:
		{
			//if(GameStatus==US_PLAY)
			//{
				m_IsCanOut=OnOutCard();
				if(m_IsCanOut)
				{
					m_wCurrentOutCard=ChairID;
					m_IsCanOut=false;
				}
			//}
			//else
			//	DelayTime=100;
			return true;
		}
	case OUTCARDPASS:
		{
			//if(GameStatus==US_PLAY)
		//	{
				SendGameData(SUB_C_PASS_CARD);
				UserStatus=GAMEPLAYING;
			//}
			//else
			//	DelayTime=100;
			return true;
		}
	}
	__super::SubDelayTime();
	return true;
}
bool  CGameInterface::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	//游戏消息发送
	switch (wSubCmdID)
	{
	case SUB_S_SEND_CARD:		//发送扑克
		{
			return OnSubSendCard(pBuffer,wDataSize);
		}
	case SUB_S_LAND_SCORE:	//用户叫分
		{
			return OnSubCavernScore(pBuffer,wDataSize);
		}
	case SUB_S_GAME_START:		//游戏开始
		{
			return OnSubGameStart(pBuffer,wDataSize);
		}
	case SUB_S_OUT_CARD:		//用户出牌
		{
			return OnSubOutCard(pBuffer,wDataSize);
		}
	case SUB_S_PASS_CARD:		//放弃出牌
		{
			return OnSubPassCard(pBuffer,wDataSize);
		}
	case SUB_S_GAME_END:		//游戏结束
		{
			return OnSubGameEnd(pBuffer,wDataSize);
		}
	}

	return false;
}
//发送扑克
bool CGameInterface::OnSubSendCard(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	if (wDataSize!=sizeof(CMD_S_SendCard)) return false;

	//变量定义
	CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;
	m_bHandCardCount=CountArray(pSendCard->bCardData);
	CopyMemory(m_bHandCardData,pSendCard->bCardData,sizeof(pSendCard->bCardData));
	//设置数据
	m_wCurrentOutCard=pSendCard->wCurrentUser;
	m_wCurrentScore=0;
	if(pSendCard->wCurrentUser==ChairID)
	{
		DelayTime=50+20*(rand()%10);
		UserStatus=GAMESCORE;
	}
	return true;
}
//用户叫分
bool CGameInterface::OnSubCavernScore(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	if (wDataSize!=sizeof(CMD_S_LandScore)) return false;
	//消息处理
	CMD_S_LandScore * pCavernScore=(CMD_S_LandScore *)pBuffer;
	
	if(pCavernScore->bCurrentScore!=3)
	{
		if(pCavernScore->wCurrentUser==ChairID)
		{
			m_wCurrentScore=pCavernScore->bCurrentScore;
			DelayTime=50+20*(rand()%10);
			UserStatus=GAMESCORE;
		}
	}
	return true;
}
bool CGameInterface::OnSubGameStart(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) return false;
	//消息处理
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;
	//设置变量
	m_bTurnCardCount=0;
	m_bTurnOutType=CT_INVALID;
	m_wCavernUser=pGameStart->wLandUser;
	memset(m_bTurnCardData,0,sizeof(m_bTurnCardData));
	if (pGameStart->wLandUser==ChairID)
	{
		BYTE bCardCound=m_bHandCardCount;
		m_bHandCardCount+=CountArray(pGameStart->bBackCard);
		CopyMemory(&m_bHandCardData[bCardCound],pGameStart->bBackCard,sizeof(pGameStart->bBackCard));
		m_GameLogic.SortCardList(m_bHandCardData,m_bHandCardCount);
		DelayTime=50+10*(rand()%20);
		UserStatus=OUTCARD;
	}
	m_wCurrentOutCard=pGameStart->wLandUser;
	return true;
}
//用户出牌
bool CGameInterface::OnSubOutCard(const void * pBuffer, WORD wDataSize)
{
	//变量定义
	CMD_S_OutCard * pOutCard=(CMD_S_OutCard *)pBuffer;
	CopyMemory(m_bTurnCardData,pOutCard->bCardData,20);
	m_bTurnCardCount=pOutCard->bCardCount;
	m_bTurnOutType=m_GameLogic.GetCardType(m_bTurnCardData,m_bTurnCardCount);
	m_wCurrentOutCard=pOutCard->wOutCardUser;
	if(pOutCard->wCurrentUser==ChairID)
	{
		if(pOutCard->wCurrentUser==pOutCard->wOutCardUser)
		{
		    memset(m_bTurnCardData,0,20);
			m_bTurnCardCount=0;
			DelayTime=50+10*(rand()%20);
			UserStatus=OUTCARD;
			return true;
		}
		if(pOutCard->wOutCardUser!=m_wCavernUser&&pOutCard->wCurrentUser!=m_wCavernUser)
		{
			switch(m_bTurnOutType)
			{
			case CT_SINGLE:
			case CT_DOUBLE:
			case CT_THREE:
				if(m_GameLogic.GetCardValue(m_bTurnCardData[0])<3)
				{
					DelayTime=200+50*(rand()%10);
					UserStatus=OUTCARDPASS;
					return true;
				}
				break;
			case CT_ONE_LINE:
				if(m_GameLogic.GetCardValue(m_bTurnCardData[0])>11)
				{
					DelayTime=200+50*(rand()%10);
					UserStatus=OUTCARDPASS;
					return true;
				}
				break;
			case CT_DOUBLE_LINE:
			case CT_THREE_LINE:
			case CT_THREE_LINE_TAKE_ONE:
			case CT_THREE_LINE_TAKE_DOUBLE:
			case CT_FOUR_LINE_TAKE_ONE:
			case CT_FOUR_LINE_TAKE_DOUBLE:
			case  CT_BOMB_CARD:
				DelayTime=200+50*(rand()%10);
				UserStatus=OUTCARDPASS;
				return true;
				break;
			default:
				{
					DelayTime=200+50*(rand()%10);
					UserStatus=OUTCARDPASS;
					return true;
				}
			}
		}
		DelayTime=50+10*(rand()%20);
		UserStatus=OUTCARD;
	}
	return true;
}
//放弃出牌
bool CGameInterface::OnSubPassCard(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	if (wDataSize!=sizeof(CMD_S_PassCard)) return false;
	CMD_S_PassCard * pPassCard=(CMD_S_PassCard *)pBuffer;
	if(pPassCard->wCurrentUser==ChairID)
	{
		if(m_wCurrentOutCard==pPassCard->wCurrentUser)
		{
			if(pPassCard->bNewTurn)
			{
				memset(m_bTurnCardData,0,20);
				m_bTurnCardCount=0;
			}
			DelayTime=50+10*(rand()%20);
			UserStatus=OUTCARD;
			return true;
		}
		if(pPassCard->wPassUser==m_wCavernUser)
		{
			DelayTime=200+50*(rand()%10);
			UserStatus=OUTCARDPASS;
			return true;
		}
		else
		{
			DelayTime=50+10*(rand()%20);
			UserStatus=OUTCARD;
		}
	}
	return true;
}
//游戏结束
bool CGameInterface::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
{
	//效验数据
	if(m_CurrentGameNum++>m_GameNum)
	{
		SendReqStandUpData();
		/*if(TableID<TABLE_NUM&&ChairID<CHAIR_NUM)
		{
			//mTableInfo[TableID].TableStatus=TABLEFREE;
			//mTableInfo[TableID].ChairStatus[ChairID]=US_FREE;
		}*/
		m_wCurrentOutCard=255;
		m_bTurnOutType=CT_INVALID;
		m_bTurnCardCount=0;
		m_CurrentGameNum=0;
		m_GameNum=3+(rand()%10);
		m_IsCanOut=false;
	}
	else
	{
		if(UserStatus!=CLOSECONNECT)
		{
			DelayTime=50+20*(rand()%10);
			UserStatus=SITINDESK;
			m_wCurrentOutCard=255;
			m_bTurnOutType=CT_INVALID;
			m_bTurnCardCount=0;
			m_IsCanOut=false;
		}
	}
	return true;
}
//叫分逻辑判断
bool CGameInterface::OnScore()
{
	//发送数据
	DelayTime=100;
	UserStatus=GAMEPLAYING;
	CMD_C_LandScore CavernScore;
	for(int i=0;i<m_bHandCardCount;i++)
	{
		if(m_GameLogic.GetCardValue(m_bHandCardData[i])==2)
		{
			if(i>1)
				CavernScore.bLandScore=3;
			else
				if(m_wCurrentScore<2)
					CavernScore.bLandScore=m_wCurrentScore+1;
				else
					CavernScore.bLandScore=255;
		}
		else
		{
			if(i==0)
				CavernScore.bLandScore=255;
		}
	}
	return SendGameData(SUB_C_LAND_SCORE,&CavernScore,sizeof(CavernScore));
}
//出牌逻辑判断
bool CGameInterface::OnOutCard()
{
	UserStatus=GAMEPLAYING;
	if(m_bTurnCardCount>m_bHandCardCount)
	{
		SendGameData(SUB_C_PASS_CARD);
		return false;
	}
	int i=0;
	BYTE							m_bTempCardCount=0;					//扑克数目
	BYTE							m_bTempCardData[20];				//手上扑克
	BYTE							m_bTempSCardCount=0;					//扑克数目
	BYTE							m_bTempSCardData[20];				//手上扑克
	BYTE							m_bTempDCardCount=0;					//扑克数目
	BYTE							m_bTempDCardData[20];				//手上扑克
	BOOL                            mIsNewOut=FALSE;
	CopyMemory(m_bTempCardData,m_bHandCardData,m_bHandCardCount);
	m_bTempCardCount=m_bHandCardCount;

	BYTE m_TempCard=0;
	if(m_bHandCardCount>4)
	{
		for(i=0;i<m_bHandCardCount;i++)
		{	
			BYTE m_GetCard=m_GameLogic.GetCardLogicValue(m_bHandCardData[i]);
			if(m_TempCard!=m_GetCard&&m_GetCard<15)
			{
				m_bTempSCardData[m_bTempSCardCount++]=m_bHandCardData[i];
				m_TempCard=m_GetCard;
			}
		}
		if(m_bTempSCardCount<5)
			m_bTempSCardCount=0;
	}
	else
		m_bTempSCardCount=0;
	if(m_bHandCardCount>5)
	{
		m_TempCard=0;
		for(i=0;i<m_bHandCardCount;i++)
		{	
			BYTE m_GetCard1=m_GameLogic.GetCardLogicValue(m_bHandCardData[i]);
			BYTE m_GetCard2=m_GameLogic.GetCardLogicValue(m_bHandCardData[i+1]);
			if(m_TempCard!=m_GetCard1&&m_GetCard1<15&&m_GetCard1==m_GetCard2)
			{
				if(i<m_bHandCardCount)
					i++;
				m_bTempDCardData[m_bTempDCardCount++]=m_bHandCardData[i];
				m_bTempDCardData[m_bTempDCardCount++]=m_bHandCardData[i+1];
				m_TempCard=m_GetCard1;
			}
		}
		if(m_bTempDCardCount<6)
			m_bTempDCardCount=0;
	}
	else
		m_bTempDCardCount=0;
	//发送数据
	CMD_C_OutCard OutCard;
	if(m_bTurnCardCount==0)
	{
		mIsNewOut=TRUE;
		memset(m_bTurnCardData,0,20);
		m_bTurnCardCount=1;
		m_bTurnOutType=CT_SINGLE;
		BOOL bIsFindContinue=TRUE;
		while(m_bHandCardCount>m_bTurnCardCount&&bIsFindContinue)
		{
			BYTE mTempType=m_GameLogic.GetCardType(&m_bHandCardData[m_bHandCardCount-m_bTurnCardCount-1],m_bTurnCardCount+1);
			if(mTempType>CT_SINGLE&&mTempType<=CT_FOUR_LINE_TAKE_DOUBLE)
			{
				m_bTurnCardCount++;
				m_bTurnOutType=mTempType;
			}
			else
			{
				bIsFindContinue=FALSE;
			}
		}
		if(m_bTurnOutType==CT_DOUBLE&&m_bTempDCardCount>5)
		{
			BYTE  TempTurnCardOut=6;
			bIsFindContinue=TRUE;
			while(m_bTempDCardCount>=TempTurnCardOut&&bIsFindContinue)
			{
				BYTE mTempType=m_GameLogic.GetCardType(&m_bTempDCardData[m_bTempDCardCount-TempTurnCardOut],TempTurnCardOut);
				if(mTempType==CT_DOUBLE_LINE&&mTempType<=CT_FOUR_LINE_TAKE_DOUBLE)
				{
					m_bTurnCardCount=TempTurnCardOut;
					TempTurnCardOut+=2;
					m_bTurnOutType=mTempType;
				}
				else
				{
					bIsFindContinue=FALSE;
				}
			}
		}
		if(m_bTurnOutType==CT_SINGLE&&m_bTempSCardCount>4)
		{
			BYTE  TempTurnCardOut=5;
			bIsFindContinue=TRUE;
			while(m_bTempSCardCount>=TempTurnCardOut&&bIsFindContinue)
			{
				BYTE mTempType=m_GameLogic.GetCardType(&m_bTempSCardData[m_bTempSCardCount-TempTurnCardOut],TempTurnCardOut);
				if(mTempType==CT_ONE_LINE)
				{
					m_bTurnCardCount=TempTurnCardOut;
					TempTurnCardOut++;
					m_bTurnOutType=mTempType;
				}
				else
				{
					bIsFindContinue=FALSE;
				}
			}
		}
		if(m_bTurnOutType<=CT_SINGLE)
		{
			BYTE  TempTurnCardOut=8;
			if(TempTurnCardOut>m_bHandCardCount)
				TempTurnCardOut=m_bHandCardCount;
			BYTE mTempType;
			do{
				mTempType=m_GameLogic.GetCardType(&m_bHandCardData[m_bHandCardCount-TempTurnCardOut],TempTurnCardOut);
				if(mTempType!=CT_INVALID&&mTempType<=CT_FOUR_LINE_TAKE_DOUBLE)
				{
					m_bTurnOutType=mTempType;
					m_bTurnCardCount=TempTurnCardOut;
				}
			}while((TempTurnCardOut--)>0&&mTempType<CT_SINGLE);
		}
	}
	OutCard.bCardCount=m_bTurnCardCount;
	BYTE  TempTurnOutType=m_bTurnOutType;
	if(m_bTurnOutType==CT_DOUBLE_LINE&&m_bTempDCardCount>=m_bTurnCardCount)
	{
		CopyMemory(m_bTempCardData,m_bTempDCardData,m_bTempDCardCount);
		m_bTempCardCount=m_bTempDCardCount;
	}
	else
	{
		if(m_bTurnOutType==CT_ONE_LINE&&m_bTempSCardCount>=m_bTurnCardCount)
		{
			CopyMemory(m_bTempCardData,m_bTempSCardData,m_bTempSCardCount);
			m_bTempCardCount=m_bTempSCardCount;
		}
		else
		{
			CopyMemory(m_bTempCardData,m_bHandCardData,m_bHandCardCount);
			m_bTempCardCount=m_bHandCardCount;
		}
	}
	if(m_bTempCardCount<m_bTurnCardCount)
	{
		SendGameData(SUB_C_PASS_CARD);
		return  false;
	}
	BYTE m_TempGetCard=0;
	if(!mIsNewOut)
	{
		m_TempGetCard=m_GameLogic.GetCardLogicValue(m_bTurnCardData[0]);
		BYTE m_TempGetCount=0;
		switch(m_bTurnOutType)
		{
		case CT_THREE_LINE_TAKE_ONE:
		case CT_THREE_LINE_TAKE_DOUBLE:
			{
				TempTurnOutType=CT_THREE;
				for(i=1;i<m_bTurnCardCount;i++)
				{
					if(m_TempGetCard==m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]))
					{
						if((m_TempGetCount++)>0)
						{
							m_TempGetCard=m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]);
						}
					}
					else
					{
						if(m_TempGetCount<2)
						{
							m_TempGetCount=0;
							m_TempGetCard=m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]);
						}
					}
				}
				if(m_bTurnCardCount>6)
					m_bTurnCardCount=6;
				else
					m_bTurnCardCount=3;
			}
			break;
		case CT_FOUR_LINE_TAKE_ONE:
		case CT_FOUR_LINE_TAKE_DOUBLE:
			{
				TempTurnOutType=CT_BOMB_CARD;
				for(i=1;i<m_bTurnCardCount;i++)
				{
					if(m_TempGetCard==m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]))
					{
						if((m_TempGetCount++)>1)
							m_TempGetCard=m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]);
					}
					else
					{
						if(m_TempGetCount<3)
						{
							m_TempGetCount=0;
							m_TempGetCard=m_GameLogic.GetCardLogicValue(m_bTurnCardData[i]);
						}
					}
				}
				if(m_bTurnCardCount>8)
					m_bTurnCardCount=8;
				else
					m_bTurnCardCount=4;
			}
			break;
		}
	}
	else
		m_TempGetCard=0;
	BYTE m_DelNum=0;
	for(i=m_bTempCardCount;i>=m_bTurnCardCount;i--)
	{
		if(!mIsNewOut&&m_TempGetCard>=m_GameLogic.GetCardLogicValue(m_bTempCardData[i-m_bTurnCardCount]))
			continue;
		if(m_GameLogic.GetCardType(&m_bTempCardData[i-m_bTurnCardCount],m_bTurnCardCount)==TempTurnOutType)
		{
			CopyMemory(m_bTurnCardData,&m_bTempCardData[i-m_bTurnCardCount],m_bTurnCardCount);
			//预先删除
			BYTE bSourceCount=m_bHandCardCount;
			BYTE TempTurnCardCount=0;
			m_bHandCardCount-=m_bTurnCardCount;
			m_DelNum=m_bTurnCardCount;
			m_GameLogic.RemoveCard(m_bTurnCardData,m_bTurnCardCount,m_bHandCardData,bSourceCount);
			if(!mIsNewOut)
			{
				bSourceCount=m_bHandCardCount;
				bool m_IsReFindOther=false;
				switch(m_bTurnOutType)
				{
				case CT_THREE_LINE_TAKE_ONE:
				case CT_FOUR_LINE_TAKE_ONE:
					{
						m_IsReFindOther=true;
						TempTurnCardCount=OutCard.bCardCount-m_bTurnCardCount;
						for(int j=m_bHandCardCount;j>=TempTurnCardCount;j--)
						{
							BOOL bIsFindContinue=TRUE;
							BYTE mNumCompareCard=0;
							while(j-mNumCompareCard>0&&bIsFindContinue)
							{
								BYTE mTempType=m_GameLogic.GetCardType(&m_bHandCardData[j-mNumCompareCard-1],mNumCompareCard+1);
								if(mTempType!=CT_INVALID)
								{
									mNumCompareCard++;
								}
								else
									bIsFindContinue=FALSE;
							}
							if(mNumCompareCard==1)//&&m_GameLogic.GetCardLogicValue(m_bHandCardData[j-1]<12)&&m_GameLogic.GetCardLogicValue(m_bHandCardData[j-1])>m_GameLogic.GetCardLogicValue(m_bTurnCardData[m_bTurnCardCount]))
							{
								m_bTurnCardData[m_bTurnCardCount++]=m_bHandCardData[j-1];
								if(m_bTurnCardCount==OutCard.bCardCount)
									j=-1;
							}
						}
						if(j>-1)
						{
							for(int n=m_bTurnCardCount;n<OutCard.bCardCount;n++)
							{
								m_bTurnCardData[n]=m_bHandCardData[--m_bHandCardCount];
							}
						}
						else
						{
							m_bHandCardCount-=TempTurnCardCount;
						}
						m_bTurnCardCount=OutCard.bCardCount;
						break;
					}
					case CT_THREE_LINE_TAKE_DOUBLE:
					case CT_FOUR_LINE_TAKE_DOUBLE:
					{
						/*BYTE m_bTempAllDCardCount=m_bTempDCardCount;
						for(int n=0;n<m_bTurnCardCount;n++)
						{
							if(m_GameLogic.RemoveCard(&m_bTurnCardData[n],1,m_bTempDCardData,m_bTempAllDCardCount))
							{
								m_bTempDCardCount--;
							}
						}*/
						if(m_bHandCardCount>1)
						{
							m_TempCard=0;
							m_bTempDCardCount=0;
							for(i=0;i<m_bHandCardCount;i++)
							{	
								BYTE m_GetCard1=m_GameLogic.GetCardLogicValue(m_bHandCardData[i]);
								BYTE m_GetCard2=m_GameLogic.GetCardLogicValue(m_bHandCardData[i+1]);
								if(m_TempCard!=m_GetCard1&&m_GetCard1<15&&m_GetCard1==m_GetCard2)
								{
									if(i<m_bHandCardCount)
										i++;
									m_bTempDCardData[m_bTempDCardCount++]=m_bHandCardData[i];
									m_bTempDCardData[m_bTempDCardCount++]=m_bHandCardData[i+1];
									m_TempCard=m_GetCard1;
								}
							}
						}
						m_IsReFindOther=true;
						TempTurnCardCount=OutCard.bCardCount-m_bTurnCardCount;
						if(m_bTempDCardCount<TempTurnCardCount)
						{
							SendGameData(SUB_C_PASS_CARD);
							return true;
						}
						for(int j=TempTurnCardCount/2;j>0;j--)
						{
							m_bTurnCardData[m_bTurnCardCount++]=m_bTempDCardData[m_bTempDCardCount-j*2];
							m_bTurnCardData[m_bTurnCardCount++]=m_bTempDCardData[m_bTempDCardCount-j*2+1];
						}
						m_bHandCardCount-=TempTurnCardCount;
						m_bTurnCardCount=OutCard.bCardCount;
						break;
					}
				}
				if(m_IsReFindOther)
				{
					m_DelNum+=TempTurnCardCount;
					m_GameLogic.RemoveCard(&m_bTurnCardData[m_bTurnCardCount-TempTurnCardCount],TempTurnCardCount,m_bHandCardData,bSourceCount);
				}
			}
			CopyMemory(OutCard.bCardData,m_bTurnCardData,OutCard.bCardCount);
			SendGameData(SUB_C_OUT_CART,&OutCard,sizeof(OutCard)-sizeof(OutCard.bCardData)+OutCard.bCardCount*sizeof(BYTE));
			return true;
		}
	}
	SendGameData(SUB_C_PASS_CARD);
	return  false;
}