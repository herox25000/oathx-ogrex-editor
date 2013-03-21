#include "StdAfx.h"
#include ".\robotmanager.h"

RobotManager::RobotManager(void)
{
}

RobotManager::~RobotManager(void)
{
}

IRobot*			RobotManager::CreateRobot(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it == m_RobotRegister.end() )
	{
		IRobot*	pRobot = new IRobot(dwUserID);
		m_RobotRegister.insert(
			RobotRegister::value_type(dwUserID, pRobot)
			);

		return pRobot;
	}

	return FALSE;
}

IRobot*			RobotManager::Search(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it != m_RobotRegister.end() )
	{
		return it->second;
	}

	return NULL;
}

void			RobotManager::DestroyRobot(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it != m_RobotRegister.end() )
	{
		it->second->Release(); m_RobotRegister.erase(it);
	}
}