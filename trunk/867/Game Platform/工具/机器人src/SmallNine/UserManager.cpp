#include "StdAfx.h"
#include ".\usermanager.h"

UserManager::UserManager(void)
{
}

UserManager::~UserManager(void)
{
	ClearUp();
}

BOOL		UserManager::AddUser(SUserInfo* pUser)
{
	UserRegister::iterator it = m_UserRegister.find(pUser->dwUserID);
	if ( it == m_UserRegister.end() )
	{
		m_UserRegister.insert(
			UserRegister::value_type(pUser->dwUserID, pUser)
			);
		return TRUE;
	}

	return FALSE;
}

SUserInfo*	UserManager::Search(DWORD dwUserID)
{
	UserRegister::iterator it = m_UserRegister.find(dwUserID);
	if ( it != m_UserRegister.end() )
	{
		return it->second;
	}

	return NULL;
}

SUserInfo*	UserManager::Search(LPCTSTR lpszName)
{
	UserRegister::iterator it = m_UserRegister.begin();
	while (it != m_UserRegister.end())
	{
		if ( !strcmp(it->second->szName, lpszName) )
		{
			return it->second;
		}
		else
		{
			it ++;
		}
	}

	return NULL;
}

SUserInfo*	UserManager::Search(WORD wCharID)
{
	UserRegister::iterator it = m_UserRegister.begin();
	while (it != m_UserRegister.end())
	{
		if ( it->second->wChairID == wCharID  )
		{
			return it->second;
		}
		else
		{
			it ++;
		}
	}

	return NULL;
}

BOOL		UserManager::Remove(DWORD dwUserID, BOOL bDestroy)
{
	UserRegister::iterator it = m_UserRegister.find(dwUserID);
	if ( it != m_UserRegister.end() )
	{
		if (bDestroy)
		{
			delete it->second;
		}
		
		m_UserRegister.erase(it);
	}

	return TRUE;
}

void		UserManager::ClearUp()
{
	UserRegister::iterator it = m_UserRegister.begin();
	while( it != m_UserRegister.end() )
	{
		delete it->second; it = m_UserRegister.erase(it);
	}
}

int			UserManager::GetCount() const
{
	return m_UserRegister.size();
}
