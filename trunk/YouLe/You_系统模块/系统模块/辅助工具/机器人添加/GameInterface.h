#pragma once
#include "userinterface.h"

class CGameInterface :
	public CUserInterface
{
public:
	CGameInterface(void);
	~CGameInterface(void);
private:
	//挖坑游戏变量
	WORD							m_wCavernUser;						//挖坑用户
	BYTE							m_bHandCardCount;					//扑克数目
	BYTE							m_bHandCardData[20];				//手上扑克
	WORD                            m_wCurrentOutCard;                   //出牌的用户
	BYTE                            m_wCurrentScore;                    //当前的叫分
			//出牌变量
	BYTE							m_bTurnOutType;						//出牌类型
	BYTE							m_bTurnCardCount;					//出牌数目
	BYTE							m_bTurnCardData[20];				//出牌列表
	bool							m_IsCanOut;
public:
	//发送扑克
	bool OnSubSendCard(const void * pBuffer, WORD wDataSize);
	//用户叫分
	bool OnSubCavernScore(const void * pBuffer, WORD wDataSize);
	//游戏开始
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//用户出牌
	bool OnSubOutCard(const void * pBuffer, WORD wDataSize);
	//放弃出牌
	bool OnSubPassCard(const void * pBuffer, WORD wDataSize);
	//游戏结束
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);
	//逻辑判断
	bool   SubDelayTime();
	bool   OnScore();
	bool   OnOutCard();
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
};
