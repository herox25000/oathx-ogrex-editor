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
		m_fCheckMoneyElapsed = 0;
		m_bGameEnd			= false;
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
		m_fCheckMoneyElapsed += fElapsed;
		
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

	void AndroidManager::UpdateRobotScore()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig == NULL)
			return;
		int nCount = GetAndroidCount();

		std::vector<IAndroid*> vHunMillionAndroid;
		std::vector<IAndroid*> vTenMillionAndroid1;
		std::vector<IAndroid*> vTenMillionAndroid2;
		std::vector<IAndroid*> vUnderTenAndroid;
		AndroidRegister::iterator it = m_AndroidRegister.begin();
		while( it != m_AndroidRegister.end() )
		{
			WORD wStatus = it->second->GetStatus();
			if (wStatus != US_OFFLINE)
			{
				INT64 nScore = it->second->GetScore();
				if (nScore >= 100000000)
					vHunMillionAndroid.push_back(it->second);
				else if (nScore >= 50000000 && nScore < 100000000)
					vTenMillionAndroid1.push_back(it->second);
				else if (nScore >= 10000000 && nScore < 50000000)
					vTenMillionAndroid2.push_back(it->second);
				else
					vUnderTenAndroid.push_back(it->second);
			}
			it++;
		}
		int nHunMillionCount = pConfig->dwOnline * pConfig->wHunMillionRate / 100;		//配置的机器人上亿的个数
		int nTenMillionCount1 = pConfig->dwOnline * pConfig->wTenMillionRate1 / 100;	//配置的机器人5-1亿的个数
		int nTenMillionCount2 = pConfig->dwOnline * pConfig->wTenMillionRate2 / 100;	//配置的机器人1-5千万的个数
		if (vHunMillionAndroid.size() > nHunMillionCount)
		{
			//存入到5-1亿的队列中
			int nLeftCount = vHunMillionAndroid.size() - nHunMillionCount;
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vHunMillionAndroid.size());
				IAndroid* pAndroid = vHunMillionAndroid[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = nScore - 100000000;
					INT64 nMax = nScore - 50000000;
					pAndroid->SaveScoreToBanker(AndroidTimer::rdit(nMin, nMax));
					vHunMillionAndroid.erase(vHunMillionAndroid.begin() + nRnd);
					vTenMillionAndroid1.push_back(pAndroid);
				}
			}
		}
		else if (vHunMillionAndroid.size() < nHunMillionCount && nCount != vHunMillionAndroid.size())
		{
			//从其他机器人取够上亿的值
			std::vector<IAndroid*> vMerge;
			vMerge.insert(vMerge.end(), vTenMillionAndroid1.begin(), vTenMillionAndroid1.end());
			vMerge.insert(vMerge.end(), vTenMillionAndroid2.begin(), vTenMillionAndroid2.end());
			vMerge.insert(vMerge.end(), vUnderTenAndroid.begin(), vUnderTenAndroid.end());
			int nLeftCount = nHunMillionCount - vHunMillionAndroid.size();
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vMerge.size());
				IAndroid* pAndroid = vMerge[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = 100000000 - nScore;
					INT64 nMax = 150000000 - nScore;
					pAndroid->GetScoreFromBanker(AndroidTimer::rdit(nMin, nMax));
					vMerge.erase(vMerge.begin() + nRnd);
					if (nRnd < vTenMillionAndroid1.size())
					{
						vTenMillionAndroid1.erase(vTenMillionAndroid1.begin() + nRnd);
					}
					else if (nRnd >= vTenMillionAndroid1.size() && nRnd < vTenMillionAndroid2.size() + vTenMillionAndroid1.size())
					{
						vTenMillionAndroid2.erase(vTenMillionAndroid2.begin() + nRnd - vTenMillionAndroid1.size());
					}
					else
					{
						vUnderTenAndroid.erase(vUnderTenAndroid.begin() + nRnd - vTenMillionAndroid1.size() - vTenMillionAndroid2.size());
					}
					vHunMillionAndroid.push_back(pAndroid);
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//5千万-1亿的判断
		if (vTenMillionAndroid1.size() > nTenMillionCount1)
		{
			//存入到1千万-5千万的队列中
			int nLeftCount = vTenMillionAndroid1.size() - nTenMillionCount1;
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vTenMillionAndroid1.size());
				IAndroid* pAndroid = vTenMillionAndroid1[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = nScore - 50000000;
					INT64 nMax = nScore - 10000000;
					pAndroid->SaveScoreToBanker(AndroidTimer::rdit(nMin, nMax));
					vTenMillionAndroid1.erase(vTenMillionAndroid1.begin() + nRnd);
					vTenMillionAndroid2.push_back(pAndroid);
				}
			}
		}
		else if (vTenMillionAndroid1.size() < nTenMillionCount1 && nCount != (vTenMillionAndroid1.size() + vHunMillionAndroid.size()))
		{
			//从其他机器人取够上亿的值
			std::vector<IAndroid*> vMerge;
			vMerge.insert(vMerge.end(), vTenMillionAndroid2.begin(), vTenMillionAndroid2.end());
			vMerge.insert(vMerge.end(), vUnderTenAndroid.begin(), vUnderTenAndroid.end());
			int nLeftCount = nTenMillionCount1 - vTenMillionAndroid1.size();
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vMerge.size());
				IAndroid* pAndroid = vMerge[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = 50000000 - nScore;
					INT64 nMax = 100000000 - nScore;
					pAndroid->GetScoreFromBanker(AndroidTimer::rdit(nMin, nMax));
					vMerge.erase(vMerge.begin() + nRnd);
					if (nRnd < vTenMillionAndroid2.size())
					{
						vTenMillionAndroid2.erase(vTenMillionAndroid2.begin() + nRnd);
					}
					else
					{
						vUnderTenAndroid.erase(vUnderTenAndroid.begin() + nRnd - vTenMillionAndroid2.size());
					}
					vTenMillionAndroid1.push_back(pAndroid);
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//1千万-5千万的判断
		if (vTenMillionAndroid2.size() > nTenMillionCount2)
		{
			//存入到1千万以下的队列中
			int nLeftCount = vTenMillionAndroid2.size() - nTenMillionCount2;
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vTenMillionAndroid2.size());
				IAndroid* pAndroid = vTenMillionAndroid2[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = nScore - 10000000;
					INT64 nMax = nScore - pConfig->nMinScore;
					pAndroid->SaveScoreToBanker(AndroidTimer::rdit(nMin, nMax));
					vTenMillionAndroid2.erase(vTenMillionAndroid2.begin() + nRnd);
				}
			}
		}
		else if (vTenMillionAndroid2.size() < nTenMillionCount2 && nCount != (vTenMillionAndroid1.size() + vHunMillionAndroid.size() + vTenMillionAndroid2.size()))
		{
			//从其他机器人取够上亿的值
			int nLeftCount = nTenMillionCount2 - vTenMillionAndroid2.size();
			for (int i = 0; i < nLeftCount; i++)
			{
				int nRnd = rand()%(vUnderTenAndroid.size());
				IAndroid* pAndroid = vUnderTenAndroid[nRnd];
				if (pAndroid)
				{
					INT64 nScore = pAndroid->GetScore();
					INT64 nMin = 10000000 - nScore;
					INT64 nMax = 50000000 - nScore;
					pAndroid->GetScoreFromBanker(AndroidTimer::rdit(nMin, nMax));
					vUnderTenAndroid.erase(vUnderTenAndroid.begin() + nRnd);
				}
			}
		}
		vHunMillionAndroid.clear();
		vTenMillionAndroid1.clear();
		vTenMillionAndroid2.clear();
		vUnderTenAndroid.clear();
	}
}
