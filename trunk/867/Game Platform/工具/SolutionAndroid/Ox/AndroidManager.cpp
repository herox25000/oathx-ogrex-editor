#include "StdAfx.h"
#include "AndroidManager.h"
#include "AndroidTimer.h"
#include "ConfigFile.h"

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	AndroidManager::AndroidManager(DWORD dwStartID, DWORD dwEndID, IAndroidFactroy* pFactory)
		: m_pFactory(pFactory), m_dwStartID(dwStartID), m_dwEndID(dwEndID)
	{
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
			// ���ﴴ��ʱ��
			if (m_fElapsed >= m_fCreate)
			{
				// ���������ID
				DWORD dwUserID = AndroidTimer::rdit(m_dwStartID, m_dwEndID);
				
				// ���û������Ƿ����
				IAndroid* pAndroid = Search(dwUserID);
				if (pAndroid == NULL)
				{
					if (m_pFactory)
					{
						// �����û�����
						pAndroid = m_pFactory->Create(dwUserID, AndroidTimer::rdit(pConfig->wMinTime, pConfig->wMaxTime));
						
						// ����������
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
				
				// ���ô���ʱ��
				m_fCreate	= AndroidTimer::rdit(4, 10);
				m_fElapsed	= 0;
			}
		}

		// ����ÿ��������
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
				// ���»�����
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
