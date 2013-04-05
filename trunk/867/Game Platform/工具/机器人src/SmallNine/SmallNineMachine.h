#pragma once

#include "IRobot.h"
#include <deque>

#define MAX_PLACE_JETTON_TIME		25		

class SmallNineMachine : public IRobot
{
public:
	SmallNineMachine(DWORD dwUserID);
	virtual ~SmallNineMachine(void);

	//游戏状态
	virtual bool			OnGameSceneMessage(BYTE cbGameStation, 
		void * pBuffer, WORD wDataSize);

	//周期性更新
	virtual void			OnUpdate(float fElapsed);

	//游戏消息
	virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL,
		WORD wDataSize=0);
	virtual bool			OnBanker();
public:
	virtual bool			SendApplyBanker(bool bUp);
	virtual	void			ResetGame();
	virtual INT64			GetRandScore(__int64 nLeftJettonScore);
	virtual void			SetOnlineTime(double fOnlineTime);
protected:
	WORD					m_wCurBanker;
	double					m_fOnlineTime;
	double					m_fCurOnlineTime;
	double					m_fElapsedTime;
	double					m_fAddJettonTime;
	INT64					m_nMeMaxScore;
	BOOL					m_bAddJetton;

	INT64					m_nBankerScore;
	WORD					m_wUpBankerCount;
	INT64					m_nApplyBankerCondition;
	BOOL					m_bStart;
	BOOL					m_bApplyBankerSend;

	INT64					m_nMePlaceScore;
	INT64					m_nMeWinScore;
	INT64					m_BankerTotalScore;

//////////////////////////////////////////////////////////////////////////
protected:
	float					m_nJettonTime;		//下注时间
};

