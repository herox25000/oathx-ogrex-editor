#include "stdafx.h"
#include "BankerManager.h"
#include "ConfigFile.h"
#include <algorithm>

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	BankerManager::BankerManager()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	BankerManager::~BankerManager()
	{
		BankerRegister::iterator it = m_BankerRegister.begin();
		while( it != m_BankerRegister.end() )
		{
			delete it->second; it = m_BankerRegister.erase(it);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	bool		BankerManager::Insert(SBanker* pBanker)
	{
		BankerRegister::iterator it = m_BankerRegister.find(pBanker->dwUserID);
		if ( it == m_BankerRegister.end() )
		{
			m_BankerRegister.insert(
				BankerRegister::value_type(pBanker->dwUserID, pBanker)
				);

			CString szMessage;
			szMessage.Format("[%d]添加到庄家队列, 当前排庄人数%d", pBanker->dwUserID, GetBankerCount());
			CTraceService::TraceString(szMessage,
				TraceLevel_Exception);

			return true;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void		BankerManager::Remove(DWORD dwUserID)
	{
		BankerRegister::iterator it = m_BankerRegister.find(dwUserID);
		if ( it != m_BankerRegister.end() )
		{
			delete it->second; m_BankerRegister.erase(it);

			CString szMessage;
			szMessage.Format("[%d]从庄家队列移除, 当前排庄人数%d",dwUserID, GetBankerCount());
			CTraceService::TraceString(szMessage,
				TraceLevel_Exception);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	SBanker*	BankerManager::Search(DWORD dwUserID)
	{
		BankerRegister::iterator it = m_BankerRegister.find(dwUserID);
		if ( it != m_BankerRegister.end() )
		{
			return it->second;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD		BankerManager::GetBankerCount() const
	{
		return m_BankerRegister.size();
	}

	//////////////////////////////////////////////////////////////////////////
	void		BankerManager::AddRequest(DWORD dwUserID)
	{
		BankerRequest::iterator it = std::find(m_BankerRequest.begin(), m_BankerRequest.end(), dwUserID);
		if ( it == m_BankerRequest.end() )
		{
			m_BankerRequest.push_back(dwUserID);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD		BankerManager::GetRequestCount() const
	{
		return m_BankerRequest.size();
	}

	//////////////////////////////////////////////////////////////////////////
	bool		BankerManager::CheckRequest(DWORD dwUserID)
	{
		BankerRequest::iterator it = std::find(m_BankerRequest.begin(), m_BankerRequest.end(), dwUserID);
		if ( it != m_BankerRequest.end() )
		{
			return true;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void		BankerManager::RemoveRequest(DWORD dwUserID)
	{
		BankerRequest::iterator it = std::find(m_BankerRequest.begin(), m_BankerRequest.end(), dwUserID);
		if ( it != m_BankerRequest.end() )
		{
			m_BankerRequest.erase(it);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void		BankerManager::ClearRequest()
	{
		m_BankerRequest.clear();
	}
}