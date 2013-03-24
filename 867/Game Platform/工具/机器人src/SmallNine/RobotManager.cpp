#include "StdAfx.h"
#include ".\robotmanager.h"

#ifndef MAX_SITDOWN
#define MAX_SITDOWN	10
#endif

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

BOOL					RobotManager::AddRobot(IRobot* pRobot)
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

IRobot*					RobotManager::Search(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it != m_RobotRegister.end() )
	{
		return it->second;
	}

	return NULL;
}

int						RobotManager::GetRobotCount() const
{
	return m_RobotRegister.size();
}

void					RobotManager::Update(float fElapsed)
{
	RobotRegister::iterator it = m_RobotRegister.begin();
	while ( it != m_RobotRegister.end() )
	{
		WORD wState = it->second->GetState();
		switch (wState)
		{
		case ROBOT_SITDOWN:
			{
				// 更新当前进入游戏的机器人
				it->second->OnUpdate(fElapsed);

				// 移除重连对象
				RemoveReconnect(
					it->second);
			}
			break;

		case ROBOT_INVALID:
			{
				// 优先移除重连对象
				RemoveReconnect(
					it->second
					);

				it->second->Stop(); it->second->Release(); it = m_RobotRegister.erase(it);
			}
			break;

		default:
			{
				AddReconnect(it->second);
			}
			break;
		}

		++ it;
	}
}

void					RobotManager::AddReconnect(IRobot* pRobot)
{
	RobotRegister::iterator it = m_Reconnect.find(pRobot->GetUserID());
	if ( it == m_Reconnect.end() )
	{
		m_Reconnect.insert(
			RobotRegister::value_type(pRobot->GetUserID(), pRobot)
			);
	}
}

void					RobotManager::RemoveReconnect(IRobot* pRobot)
{
	if (m_Reconnect.size() > 0)
	{
		RobotRegister::iterator it = m_Reconnect.find(pRobot->GetUserID());
		if ( it != m_Reconnect.end() )
		{
			m_Reconnect.erase(it);
		}
	}
}

void					RobotManager::Reconnect(const CString& ipAddress, WORD wPort, const CString& md5)
{
	if (m_Reconnect.size() > 0)
	{
		RobotRegister::iterator it = m_Reconnect.begin();
		if( it != m_Reconnect.end() )
		{
			int nReqCount = it->second->GetReconnect();
			if (nReqCount < MAX_SITDOWN)
			{
				it->second->ResetGame();
				it->second->SitDown();
			}
			else
			{
				it->second->SetState(ROBOT_INVALID);
			}
		}
	}
}

void					RobotManager::DestroyRobot(DWORD dwUserID)
{
	RobotRegister::iterator it = m_RobotRegister.find(dwUserID);
	if ( it != m_RobotRegister.end() )
	{
		it->second->Release(); m_RobotRegister.erase(it);
	}
}

void					RobotManager::RegisterRobotFactory(IRobotFactory* pFactory)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(pFactory->GetTypeName());
	if ( it == m_RobotFactoryRegister.end() )
	{
		m_RobotFactoryRegister.insert(
			RobotFactoryRegister::value_type(pFactory->GetTypeName(), pFactory)
			);
	}
}

IRobotFactory*			RobotManager::GetRobotFactory(const CString& szName)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(szName);
	if (it != m_RobotFactoryRegister.end() )
	{
		return it->second;
	}

	return NULL;
}

void					RobotManager::UnregisterRobotFactory(const CString& szName)
{
	RobotFactoryRegister::iterator it = m_RobotFactoryRegister.find(szName);
	if (it != m_RobotFactoryRegister.end() )
	{
		delete it->second; m_RobotFactoryRegister.erase(it);
	}
}

void					RobotManager::SetBankerConfig(const SBankerConfig& cfg)
{
	memcpy(&m_BankerConfig, &cfg, sizeof(SBankerConfig));
}

const SBankerConfig&	RobotManager::GetBankerConfig() const
{
	return m_BankerConfig;
}