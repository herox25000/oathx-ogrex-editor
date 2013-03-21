#pragma once

#include "IRobot.h"

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

	virtual	BOOL			AddRobot(IRobot* pRobot);
	virtual	IRobot*			Search(DWORD dwUserID);
	virtual void			DestroyRobot(DWORD dwUserID);
	virtual int				GetRobotCount() const;
public:
	virtual	void			Update(float fElapsed);

public:
	virtual	void			RegisterRobotFactory(IRobotFactory* pFactory);
	virtual	IRobotFactory*	GetRobotFactory(const CString& szName);
	virtual void			UnregisterRobotFactory(const CString& szName);

protected:
	RobotRegister			m_RobotRegister;
	RobotFactoryRegister	m_RobotFactoryRegister;
};
