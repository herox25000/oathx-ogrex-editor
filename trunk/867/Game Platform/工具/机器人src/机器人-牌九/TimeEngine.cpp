#include "StdAfx.h"
#include ".\timeengine.h"
#include "GameBase.h"

//���캯��
CTimerThread::CTimerThread(void)
{
	m_dwTimerSpace=0L;
	m_pTimerEngine=NULL;
}

//��������
CTimerThread::~CTimerThread(void)
{
}

//���ú���
bool CTimerThread::InitThread(CTimerEngine * pTimerEngine, DWORD dwTimerSpace)
{
	//Ч�����
	ASSERT(dwTimerSpace>=10L);
	ASSERT(pTimerEngine!=NULL);
	if (pTimerEngine==NULL) return false;

	//���ñ���
	m_dwTimerSpace=dwTimerSpace;
	m_pTimerEngine=pTimerEngine;

	return true;
}

////���к���
//bool CTimerThread::RepetitionRun()
//{
//	ASSERT(m_pTimerEngine!=NULL);
//	Sleep(m_dwTimerSpace);
//	m_pTimerEngine->OnTimerThreadSink();
//	return true;
//}

//���к���
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
	//ֹͣ����
	EndService();

	//�����ڴ�
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

//���ö�ʱ��
bool CTimerEngine::SetTimer(CGameBase *pGame, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat)
{
	//������Դ
	CThreadLock LockHandle(m_CriticalSection);

	//Ч�����
	ASSERT(dwRepeat>0L);
	if (dwRepeat==0) return false;
	dwElapse=(dwElapse+m_dwTimerSpace-1)/m_dwTimerSpace*m_dwTimerSpace;

	//���Ҷ�ʱ��
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

	//������ʱ��
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
 
 	//���ò���
	ASSERT(pTimerItem!=NULL);
	pTimerItem->wTimerID=wTimerID;
	pTimerItem->pGame=pGame;
	pTimerItem->dwElapse=dwElapse;
	pTimerItem->dwRepeatTimes=dwRepeat;
	pTimerItem->dwTimeLeave=dwElapse+m_dwTimePass;
 
	//���ʱ��
	m_dwTimeLeave=__min(m_dwTimeLeave,dwElapse);
	if (bTimerExist==false) m_TimerItemActive.push_back(pTimerItem);

	return false;
}

//ɾ����ʱ��
bool CTimerEngine::KillTimer(CGameBase *pGame, WORD wTimerID)
{
	//������Դ
	CThreadLock LockHandle(m_CriticalSection);

	//���Ҷ�ʱ��
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

//ɾ����ʱ��
bool CTimerEngine::KillAllTimer()
{
	//������Դ
	CThreadLock LockHandle(m_CriticalSection);

	//ɾ����ʱ��
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		m_TimerItemFree.push_back(*iter);
	}
	m_TimerItemActive.clear();

	//���ñ���
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;

	return true;
}

//��ʼ����
bool CTimerEngine::BeginService()
{
	//Ч��״̬
	if (m_bService==true) 
	{
		return true;
	}

	//���ñ���
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;
	if (m_TimerThread.InitThread(this,m_dwTimerSpace)==false)
	{
		return false;
	}

	//��������
	if (m_TimerThread.StartThread()==false)
	{
		return false;
	}

	//���ñ���
	m_bService=true;

	return true;
}

//ֹͣ����
bool CTimerEngine::EndService()
{
	//���ñ���
	m_bService=false;

	//ֹͣ�߳�
	m_TimerThread.ConcludeThread(INFINITE);

	//���ñ���
	m_dwTimePass=0L;
	m_dwTimeLeave=-1;
	//ɾ����ʱ��
	for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
		iter != m_TimerItemActive.end();++iter)
	{
		m_TimerItemFree.push_back(*iter);
	}
	m_TimerItemActive.clear();

	return true;
}

//��ʱ��֪ͨ
void CTimerEngine::OnTimerThreadSink()
{
	//������Դ
	CThreadLock LockHandle(m_CriticalSection);

	//����ʱ��
	if (m_dwTimeLeave==-1) 
	{
		ASSERT(m_TimerItemActive.size()==0);
		return;
	}

	//����ʱ��
	ASSERT(m_dwTimeLeave>=m_dwTimerSpace);
	m_dwTimeLeave-=m_dwTimerSpace;
	m_dwTimePass+=m_dwTimerSpace;

	//��ѯ��ʱ��
	if (m_dwTimeLeave==0)
	{
		bool bKillTimer=false;
		tagTimerItem * pTimerItem=NULL;
		DWORD dwTimeLeave=-1;
		for(CTimerItemPtr::iterator iter = m_TimerItemActive.begin();
			iter != m_TimerItemActive.end();)
		{
			//Ч�����
			pTimerItem=*iter;
			ASSERT(pTimerItem!=NULL);
			ASSERT(pTimerItem->dwTimeLeave>=m_dwTimePass);

			//��ʱ������
			bKillTimer=false;
			pTimerItem->dwTimeLeave-=m_dwTimePass;
			if (pTimerItem->dwTimeLeave==0L)
			{
				//����֪ͨ
				pTimerItem->pGame->OnTimer(pTimerItem->wTimerID);

				//���ô���
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

				//����ʱ��
				if (bKillTimer==false) pTimerItem->dwTimeLeave=pTimerItem->dwElapse;
			}

			//��������
			if (bKillTimer==false) 
			{
				++iter;
				dwTimeLeave=__min(dwTimeLeave,pTimerItem->dwTimeLeave);
				ASSERT(dwTimeLeave%m_dwTimerSpace==0);
			}
		}

		//������Ӧ
		m_dwTimePass=0L;
		m_dwTimeLeave=dwTimeLeave;
	}

	return;
}
