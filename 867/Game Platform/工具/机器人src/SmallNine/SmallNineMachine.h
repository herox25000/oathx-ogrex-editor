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
	//游戏消息
	virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL,
		WORD wDataSize=0);

protected:
	UserManager*			m_pBankerUser;
	WORD					m_wCurBanker;
	INT64					m_nMeMaxScore;
	BOOL					m_bMeBanker;
};

