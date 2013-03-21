#pragma once

#include "IRobot.h"

class RobotManager
{
	typedef std::map<DWORD, IRobot*>	RobotRegister;

public:
	static	RobotManager&	GetSingleton()
	{
		static	RobotManager instance;
		return instance;
	}

public:
	RobotManager(void);
	virtual ~RobotManager(void);

	virtual	IRobot*			CreateRobot(DWORD dwUserID);
	virtual	IRobot*			Search(DWORD dwUserID);
	virtual void			DestroyRobot(DWORD dwUserID);
protected:
	RobotRegister			m_RobotRegister;
};
