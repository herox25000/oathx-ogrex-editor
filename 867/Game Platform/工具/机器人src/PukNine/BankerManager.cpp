#include "StdAfx.h"
#include ".\bankermanager.h"
#include "RobotTimer.h"
#include <algorithm>

BankerManager::BankerManager(void) : m_pUserManager(NULL)
{
	m_pUserManager	= new UserManager();
}

BankerManager::~BankerManager(void)
{
}

void		BankerManager::AddUser(SUserInfo* pUserInfo)
{
	m_pUserManager->AddUser(pUserInfo);
}

int			BankerManager::GetBankerCount() const
{
	return m_pUserManager->GetCount();
}

void		BankerManager::Remove(DWORD dwUserID)
{
			m_pUserManager->Remove(dwUserID, FALSE);
}

SUserInfo*	BankerManager::Search(DWORD dwUserID)
{
	return m_pUserManager->Search(dwUserID);
}