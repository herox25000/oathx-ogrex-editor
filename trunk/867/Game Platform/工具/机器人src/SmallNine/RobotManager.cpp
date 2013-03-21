#include "StdAfx.h"
#include ".\robotmanager.h"

RobotManager::RobotManager(void)
{
}

RobotManager::~RobotManager(void)
{
	RobotFactoryRegister::iterator itR = m_RobotFactoryRegister.begin();
	while( itR != m_RobotFactoryRegister.end() )
	{
		delete itR->second; itR = m_RobotFactoryRegister.erase(itR);
	}

	RobotRegister::iterator it = m_RobotRegister.begin();
	while ( it != m_RobotRegister.end() )
	{
		it->second->Release(); it = m_RobotRegister.erase(it);
	}
}

BOOL			RobotManager::AddRobot(IRobot* pRobot)
{
	RobotRegister::iterator it = m_RobotRegister.find(pRobot->GetUserID());
	if ( it == m_RobotRegister.end() )
	{
		m_RobotRegister.insert(
			RobotRegister::value_type(pRobot->GetUserID(), pRobot)
			);
		return TRUE;
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

int				RobotManager::GetRobotCount() const
{
	return m_RobotRegister.size();
}

void			RobotManager::Update(float fElapsed)
{

}

void			RobotManager::DestroyRobot(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it != m_RobotRegister.end() )
	{
		it->second->Release(); m_RobotRegister.erase(it);
	}
}

void			RobotManager::RegisterRobotFactory(IRobotFactory* pFactory)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(pFactory->GetTypeName());
	if ( it == m_RobotFactoryRegister.end() )
	{
		m_RobotFactoryRegister.insert(
			RobotFactoryRegister::value_type(pFactory->GetTypeName(), pFactory)
			);
	}
}

IRobotFactory*	RobotManager::GetRobotFactory(const CString& szName)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(szName);
	if (it != m_RobotFactoryRegister.end() )
	{
		return it->second;
	}

	return NULL;
}

void			RobotManager::UnregisterRobotFactory(const CString& szName)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(szName);
	if (it != m_RobotFactoryRegister.end() )
	{
		delete it->second; m_RobotFactoryRegister.erase(it);
	}
}