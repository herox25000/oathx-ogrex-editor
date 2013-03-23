#pragma once

#include "IRobot.h"
#include <deque>

class SmallNineMachine : public IRobot
{
public:
	SmallNineMachine(DWORD dwUserID);
	virtual ~SmallNineMachine(void);

	//��Ϸ״̬
	virtual bool			OnGameSceneMessage(BYTE cbGameStation, 
		void * pBuffer, WORD wDataSize);

	//�����Ը���
	virtual void			OnUpdate(float fElapsed);

	//��Ϸ��Ϣ
	virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL,
		WORD wDataSize=0);

	virtual bool			SendApplyBanker(BOOL bUp);

	virtual	void			ResetGame();

	virtual INT64			GetRandScore();
protected:
	WORD					m_wCurBanker;
	double					m_fElapsedTime;
	double					m_fAddJettonTime;
	INT64					m_nMeMaxScore;
	BOOL					m_bMeBanker;
	BOOL					m_bAddJetton;

	INT64					m_nBankerScore;
	WORD					m_wUpBankerCount;
	INT64					m_nApplyBankerCondition;
	BOOL					m_bStart;
};

