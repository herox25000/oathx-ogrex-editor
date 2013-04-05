#include "StdAfx.h"
#include "AndroidManager.h"
#include "AndroidTimer.h"

namespace O2
{
	AndroidManager*	AndroidManager::mpSingleton = NULL;

	//////////////////////////////////////////////////////////////////////////
	AndroidManager*	AndroidManager::GetSingleton()
	{
		return mpSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	AndroidManager::AndroidManager(DWORD dwStartID, DWORD dwEndID, DWORD dwMaxCount, const CString& ipAddress, WORD wPort, 
		const CString& szPassword, IAndroidFactroy* pFactory)
		: m_dwStartID(dwStartID), m_dwEndID(dwEndID), m_dwMaxCount(dwMaxCount), m_ipAddress(ipAddress), m_wPort(wPort), m_Password(szPassword), m_pFactory(pFactory)
	{
		mpSingleton			= this;
		m_fCreate			= AndroidTimer::rdit(1, 10);
		m_fElapsed			= 0;
		m_fMinOnlineTime	= 10;
		m_fMaxOnlineTime	= 60;
	}

	//////////////////////////////////////////////////////////////////////////
	AndroidManager::~AndroidManager(void)
	{
		DestroyAll();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::Startup()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	bool			AndroidManager::Update(float fElapsed)
	{
		m_fElapsed += fElapsed;
		
		int nCount = GetAndroidCount();
		if (nCount <= m_dwMaxCount)
		{
			// 到达创建时间
			if (m_fElapsed >= m_fCreate)
			{
				// 随机机器人ID
				DWORD dwUserID = AndroidTimer::rdit(m_dwStartID, m_dwEndID);
				
				// 检查该机器人是否存在
				IAndroid* pAndroid = Search(dwUserID);
				if (pAndroid == NULL)
				{
					if (m_pFactory)
					{
						// 创建该机器人
						pAndroid = m_pFactory->Create(dwUserID, AndroidTimer::rdit(m_fMinOnlineTime, m_fMaxOnlineTime));
						if (pAndroid && pAndroid->Startup(m_ipAddress, m_wPort, m_Password))
						{
							AddAndroid(pAndroid);
						}
						else
						{
							pAndroid->Release();
						}
					}
				}
				
				// 重置创建时间
				m_fCreate	= AndroidTimer::rdit(4, 10);
				m_fElapsed	= 0;
			}
		}

		// 更新每个机器人
		AndroidRegister::iterator it = m_AndroidRegister.begin();
		while( it != m_AndroidRegister.end() )
		{
			WORD wStatus = it->second->GetStatus();
			if (wStatus == STATUS_INVALID)
			{
				it->second->Shutdown(); it->second->Release(); it = m_AndroidRegister.erase(it);
			}
			else
			{
				// 更新机器人
				it->second->Update(fElapsed);
				it++;
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::Shutdown()
	{
		DestroyAll();
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::SetStartID(DWORD dwStartID)
	{
		m_dwStartID = dwStartID;
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD			AndroidManager::GetStartID() const
	{
		return m_dwStartID;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::SetEndID(DWORD dwEndID)
	{
		m_dwEndID = dwEndID;
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD			AndroidManager::GetEndID() const
	{
		return m_dwEndID;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::SetMaxCount(DWORD dwMaxCount)
	{
		m_dwMaxCount = dwMaxCount;
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD			AndroidManager::GetMaxCount() const
	{
		return m_dwMaxCount;
	}

	//////////////////////////////////////////////////////////////////////////
	int				AndroidManager::GetAndroidCount() const
	{
		return m_AndroidRegister.size();
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::AddAndroid(IAndroid* pAndroid)
	{
		AndroidRegister::iterator it = m_AndroidRegister.find(pAndroid->GetUserID());
		if( it == m_AndroidRegister.end() )
		{
			m_AndroidRegister.insert(
				AndroidRegister::value_type(pAndroid->GetUserID(), pAndroid)
				);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	IAndroid*		AndroidManager::Search(DWORD dwUserID)
	{
		AndroidRegister::iterator it = m_AndroidRegister.find(dwUserID);
		if ( it != m_AndroidRegister.end() )
		{
			return it->second;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::Destroy(IAndroid* pAndroid)
	{
		AndroidRegister::iterator it = m_AndroidRegister.find(pAndroid->GetUserID());
		if ( it != m_AndroidRegister.end() )
		{
			it->second->Shutdown(); it->second->Release(); it = m_AndroidRegister.erase(it);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void			AndroidManager::DestroyAll()
	{
		AndroidRegister::iterator it = m_AndroidRegister.begin();
		while( it != m_AndroidRegister.end() )
		{
			it->second->Shutdown(); it->second->Release(); it = m_AndroidRegister.erase(it);
		}
	}
}
