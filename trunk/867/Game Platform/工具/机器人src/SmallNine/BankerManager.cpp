#include "StdAfx.h"
#include ".\bankermanager.h"
#include "RobotTimer.h"
#include <algorithm>

BankerManager::BankerManager(void) : m_pUserManager(NULL), m_bLockBanker(FALSE)
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

void		BankerManager::Lock()
{
	m_bLockBanker = TRUE;
}

BOOL		BankerManager::IsLock() const
{
	return m_bLockBanker;
}

void		BankerManager::Unlock()
{
	m_bLockBanker = FALSE;
}
