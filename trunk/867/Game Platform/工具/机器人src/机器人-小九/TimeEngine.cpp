#include "StdAfx.h"
#include ".\timeengine.h"
#include "GameBase.h"

//构造函数
CTimerThread::CTimerThread(void)
{
	m_dwTimerSpace=0L;
	m_pTimerEngine=NULL;
}

//析构函数
CTimerThread::~CTimerThread(void)
{
}

//配置函数
bool CTimerThread::InitThread(CTimerEngine * pTimerEngine, DWORD dwTimerSpace)
{
	//效益参数
	ASSERT(dwTimerSpace>=10L);
	ASSERT(pTimerEngine!=NULL);
	if (pTimerEngine==NULL) return false;

	//设置变量
	m_dwTimerSpace=dwTimerSpace;
	m_pTimerEngine=pTimerEngine;

	return true;
}

////运行函数
//bool CTimerThread::RepetitionRun()
//{
//	ASSERT(m_pTimerEngine!=NULL);
//	Sleep(m_dwTimerSpace);
//	m_pTimerEngine->OnTimerThreadSink();
//	return true;
//}

//运行函数
bool CTimerThread::OnEventThreadRun()
{
	ASSERT(m_pTimerEngine!=NULL);
	Sleep(m_dwTimerSpace);
	m_pTimerEngine->OnTimerThreadSink();
	return true;
}

CTimerEngine::CTimerEngine(void)
{
	m_bService=false;
	m_dwTimePass=0L;
	m_dwTimerSpace=25L;
	m_dwTimeLeave=-1;
}

CTimerEngine::~CTimerEngine(void)
{
	//停止服务
	EndService();

	//清理内存
	tagTimerItem * pTimerItem=NULL;
	for(CTimerItemPtr::iterator iter = m_TimerItemFree.begin();
		iter != m_TimerItemFree.end();++iter)
	{
		pTimerItem=*iter;
		ASSERT(pTimerItem!=NULL);
		SafeDelete(pTimerItem);
	}
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		pTimerItem=*iter;
		ASSERT(pTimerItem!=NULL);
		SafeDelete(pTimerItem);
	}
}

//设置定时器
bool CTimerEngine::SetTimer(CGameBase *pGame, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat)
{
	//锁定资源
	CThreadLock LockHandle(m_CriticalSection);

	//效验参数
	ASSERT(dwRepeat>0L);
	if (dwRepeat==0) return false;
	dwElapse=(dwElapse+m_dwTimerSpace-1)/m_dwTimerSpace*m_dwTimerSpace;

	//查找定时器
	bool bTimerExist=false;
	tagTimerItem * pTimerItem=NULL;
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		pTimerItem = *iter;
		if(pTimerItem&&pTimerItem->wTimerID==wTimerID&&pTimerItem->pGame==pGame)
		{
			bTimerExist=true;
			break;
		}
	}

	//创建定时器
	if(bTimerExist==false)
	{
		int nFreeCount = m_TimerItemFree.size();
		if(nFreeCount>0)
		{
			pTimerItem=m_TimerItemFree[nFreeCount-1];
			m_TimerItemFree.pop_back();
		}
		else
		{
			try
			{
				pTimerItem=new tagTimerItem;
				ASSERT(pTimerItem!=NULL);
				if (pTimerItem==NULL) return false;
			}
			catch (...) { return false; }
		}
	}
 
 	//设置参数
	ASSERT(pTimerItem!=NULL);
	pTimerItem->wTimerID=wTimerID;
	pTimerItem->pGame=pGame;
	pTimerItem->dwElapse=dwElapse;
	pTimerItem->dwRepeatTimes=dwRepeat;
	pTimerItem->dwTimeLeave=dwElapse+m_dwTimePass;
 
	//激活定时器
	m_dwTimeLeave=__min(m_dwTimeLeave,dwElapse);
	if (bTimerExist==false) m_TimerItemActive.push_back(pTimerItem);

	return false;
}

//删除定时器
bool CTimerEngine::KillTimer(CGameBase *pGame, WORD wTimerID)
{
	//锁定资源
	CThreadLock LockHandle(m_CriticalSection);

	//查找定时器
	tagTimerItem * pTimerItem=NULL;
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		pTimerItem=*iter;
		ASSERT(pTimerItem!=NULL);
		if (pTimerItem->wTimerID==wTimerID&&pTimerItem->pGame==pGame) 
		{
			m_TimerItemActive.erase(iter);
			m_TimerItemFree.push_back(pTimerItem);
			if (m_TimerItemActive.size()==0) 
			{
				m_dwTimePass=0L;
				m_dwTimeLeave=-1;
			}
			return true;;
		}
	}

	return false;
}

//删除定时器
bool CTimerEngine::KillAllTimer()
{
	//锁定资源
	CThreadLock LockHandle(m_CriticalSection);

	//删除定时器
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		m_TimerItemFree.push_back(*iter);
	}
	m_TimerItemActive.clear();

	//设置变量
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;

	return true;
}

//开始服务
bool CTimerEngine::BeginService()
{
	//效验状态
	if (m_bService==true) 
	{
		return true;
	}

	//设置变量
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;
	if (m_TimerThread.InitThread(this,m_dwTimerSpace)==false)
	{
		return false;
	}

	//启动服务
	if (m_TimerThread.StartThread()==false)
	{
		return false;
	}

	//设置变量
	m_bService=true;

	return true;
}

//停止服务
bool CTimerEngine::EndService()
{
	//设置变量
	m_bService=false;

	//停止线程
	m_TimerThread.ConcludeThread(INFINITE);

	//设置变量
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;
	//删除定时器
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		m_TimerItemFree.push_back(*iter);
	}
	m_TimerItemActive.clear();

	return true;
}

//定时器通知
void CTimerEngine::OnTimerThreadSink()
{
	//锁定资源
	CThreadLock LockHandle(m_CriticalSection);

	//倒计时间
	if (m_dwTimeLeave==-1) 
	{
		ASSERT(m_TimerItemActive.size()==0);
		return;
	}

	//减少时间
	ASSERT(m_dwTimeLeave>=m_dwTimerSpace);
	m_dwTimeLeave-=m_dwTimerSpace;
	m_dwTimePass+=m_dwTimerSpace;

	//查询定时器
	if (m_dwTimeLeave==0)
	{
		bool bKillTimer=false;
		tagTimerItem * pTimerItem=NULL;
		DWORD dwTimeLeave=-1;
		for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
			iter != m_TimerItemActive.end();)
		{
			//效验参数
			pTimerItem=*iter;
			ASSERT(pTimerItem!=NULL);
			ASSERT(pTimerItem->dwTimeLeave>=m_dwTimePass);

			//定时器处理
			bKillTimer=false;
			pTimerItem->dwTimeLeave-=m_dwTimePass;
			if (pTimerItem->dwTimeLeave==0L)
			{
				//发送通知
				pTimerItem->pGame->OnTimer(pTimerItem->wTimerID);

				//设置次数
				if (pTimerItem->dwRepeatTimes!= TIMES_INFINITY)
				{
					ASSERT(pTimerItem->dwRepeatTimes>0);
					if (pTimerItem->dwRepeatTimes==1L)
					{
						bKillTimer=true;
						iter = m_TimerItemActive.erase(iter);
						m_TimerItemFree.push_back(pTimerItem);
					}
					else pTimerItem->dwRepeatTimes--;
				}

				//设置时间
				if (bKillTimer==false) pTimerItem->dwTimeLeave=pTimerItem->dwElapse;
			}

			//增加索引
			if (bKillTimer==false) 
			{
				++iter;
				dwTimeLeave=__min(dwTimeLeave,pTimerItem->dwTimeLeave);
				ASSERT(dwTimeLeave%m_dwTimerSpace==0);
			}
		}

		//设置响应
		m_dwTimePass=0L;
		m_dwTimeLeave=dwTimeLeave;
	}

	return;
}
