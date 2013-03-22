#pragma once

#include "IRobot.h"

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
protected:
	WORD					m_wCurBanker;
	double					m_fElapsedTime;
	double					m_fAddJettonTime;
	INT64					m_nBankerScore;
	INT64					m_nMeMaxScore;
	BOOL					m_bMeBanker;
	WORD					m_wUpBankerCount;
	BOOL					m_bAddJetton;
};

