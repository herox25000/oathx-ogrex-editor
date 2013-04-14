#include "StdAfx.h"
#include "AndroidManager.h"
#include "AndroidTimer.h"
#include "ConfigFile.h"

namespace O2
{
	AndroidManager*	AndroidManager::mpSingleton = NULL;

	//////////////////////////////////////////////////////////////////////////
	AndroidManager*	AndroidManager::GetSingleton()
	{
		return mpSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	AndroidManager::AndroidManager(IAndroidFactroy* pFactory)
		: m_pFactory(pFactory)
	{
		mpSingleton			= this;
		m_fCreate			= AndroidTimer::rdit(1, 10);
		m_fElapsed			= 0;
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
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig == NULL)
			return 0;

		m_fElapsed += fElapsed;
		
		int nCount = GetAndroidCount();
		if (nCount <= pConfig->dwOnline)
		{
			// 到达创建时间
			if (m_fElapsed >= m_fCreate)
			{
				// 随机机器人ID
				DWORD dwUserID = AndroidTimer::rdit(pConfig->dwStartID, pConfig->dwEndID);
				
				// 检查该机器人是否存在
				IAndroid* pAndroid = Search(dwUserID);
				if (pAndroid == NULL)
				{
					if (m_pFactory)
					{
						// 创建该机器人
						pAndroid = m_pFactory->Create(dwUserID, AndroidTimer::rdit(pConfig->wMinTime, pConfig->wMaxTime));
						
						// 启动机器人
						if (pAndroid && pAndroid->Startup(
							pConfig->chIPAddrss, pConfig->wPort, pConfig->chMD5))
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
			if (wStatus == US_OFFLINE)
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
	IAndroid*		AndroidManager::GetAndroid(DWORD idx)
	{
		DWORD cr = 0;
		AndroidRegister::iterator it = m_AndroidRegister.begin();
		while( it != m_AndroidRegister.end() )
		{
			if (cr == idx)
				return it->second;
			
			it ++;
			cr ++;
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
