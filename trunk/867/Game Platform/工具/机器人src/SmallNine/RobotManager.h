#pragma once

#include "IRobot.h"

typedef struct tagBankerConfig
{
	//INT64							nUpBankerScore;
	WORD							wUpBankerCount;
	WORD							wUpBankerDeque;

	INT64							nMaxWinScore;
	INT64							nUpBankerLoseScore;
	INT64							nMinScore;
	double							fMaxPlaceTime;
	double							fMinPlaceTime;

	INT64							nGameMaxScore;
	INT64							nGameMinScore;

	WORD							nTenLakhRate;
	WORD							nPlaceMaxRate;

	double							fMinOnlineTime;
	double							fMaxOnlineTime;

}SBankerConfig;

class RobotManager
{
	typedef std::map<DWORD, IRobot*>			RobotRegister;
	typedef std::map<CString, IRobotFactory*>	RobotFactoryRegister;
public:
	static	RobotManager&	GetSingleton()
	{
		static	RobotManager instance;
		return instance;
	}

public:
	RobotManager(void);
	virtual ~RobotManager(void);

	virtual	BOOL					AddRobot(IRobot* pRobot);
	virtual	IRobot*					Search(DWORD dwUserID);
	virtual IRobot*					SearchRobotByGameID(DWORD dwGameID);

	virtual void					DestroyRobot(DWORD dwUserID);
	virtual int						GetRobotCount() const;
public:
	virtual	void					Update(float fElapsed);
	virtual	void					AddReconnect(IRobot* pRobot);
	virtual void					RemoveReconnect(IRobot* pRobot);
	virtual	void					Reconnect(const CString& ipAddress, WORD wPort,  const CString& md5);
public:
	virtual	void					RegisterRobotFactory(IRobotFactory* pFactory);
	virtual	IRobotFactory*			GetRobotFactory(const CString& szName);
	virtual void					UnregisterRobotFactory(const CString& szName);

public:
	virtual	void					SetBankerConfig(const SBankerConfig& cfg);
	virtual const SBankerConfig&	GetBankerConfig() const;
protected:
	RobotRegister					m_RobotRegister;
	RobotRegister					m_Reconnect;
	RobotFactoryRegister			m_RobotFactoryRegister;
	SBankerConfig					m_BankerConfig;
};
