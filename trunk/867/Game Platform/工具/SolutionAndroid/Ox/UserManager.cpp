#include "StdAfx.h"
#include "UserManager.h"
#include <algorithm>

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	UserManager::UserManager(void)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	UserManager::~UserManager(void)
	{
		Clear(true);
	}
	
	//////////////////////////////////////////////////////////////////////////
	void		UserManager::Add(SUser* pUser)
	{
		UserRegister::iterator it = m_UserRegister.find(pUser->dwUserID);
		if ( it == m_UserRegister.end() )
		{
			m_UserRegister.insert(
				UserRegister::value_type(pUser->dwUserID, pUser)
				);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void		UserManager::Remove(DWORD dwUserID, bool bDestroy)
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
	}

	//////////////////////////////////////////////////////////////////////////
	SUser*		UserManager::Search(DWORD dwID, bool bGameID)
	{
		if (bGameID)
		{
			UserRegister::iterator it = m_UserRegister.begin();
			while( it != m_UserRegister.end() )
			{
				if (dwID == it->second->dwGameID)
					return it->second;

				it++;
			}
		}
		else
		{
			UserRegister::iterator it = m_UserRegister.find(dwID);
			if ( it != m_UserRegister.end() )
			{
				return it->second;
			}
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	SUser*		UserManager::Search(LPCTSTR lpszName)
	{
		UserRegister::iterator it = m_UserRegister.begin();
		while( it != m_UserRegister.end() )
		{
			if ( !strcmp(lpszName, it->second->szName))
				return it->second;

			it++;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	SUser*		UserManager::Search(WORD wCharID)
	{
		UserRegister::iterator it = m_UserRegister.begin();
		while( it != m_UserRegister.end() )
		{
			if ( wCharID == it->second->wChairID )
				return it->second;

			it++;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	WORD		UserManager::GetTableChairCount(WORD wTableID)
	{
		WORD wCount = 0;

		UserRegister::iterator it = m_UserRegister.begin();
		while( it != m_UserRegister.end() )
		{
			if ( wTableID == it->second->wTableID )
				wCount ++;

			it++;
		}

		return wCount;
	}

	//////////////////////////////////////////////////////////////////////////
	WORD		UserManager::GetEmptyChairID(WORD wTableID)
	{
		std::vector<WORD> vEmpty;

		UserRegister::iterator it = m_UserRegister.begin();
		while( it != m_UserRegister.end() )
		{
			if ( wTableID == it->second->wTableID )
			{
				vEmpty.push_back(it->second->wChairID);
			}

			it++;
		}

		for (int i=0; i<4; i++)
		{
			std::vector<WORD>::iterator it = std::find(vEmpty.begin(), vEmpty.end(), i);
			if ( it == vEmpty.end() )
				return i;
		}

		return rand() % 4;
	}

	//////////////////////////////////////////////////////////////////////////
	void		UserManager::Clear(bool bDestroy/* =true */)
	{
		UserRegister::iterator it = m_UserRegister.begin();
		while( it != m_UserRegister.end() )
		{
			if (bDestroy)
			{
				delete it->second;
			}

			it = m_UserRegister.erase(it);
		}
	}
}
