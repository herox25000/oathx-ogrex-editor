#include "stdafx.h"
#include "HKFiveAndroid.h"
#include "AndroidTimer.h"
#include "ConfigFile.h"

namespace O2
{
	static WORD		s_wCurTableID = INVALID_TABLE;

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	HKFiveAndroid::HKFiveAndroid(DWORD dwUserID, double fOnlineTime)
		: IAndroid(dwUserID, fOnlineTime)
	{
		OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	HKFiveAndroid::~HKFiveAndroid()
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.begin();
		while ( itA != m_TimerItemActive.end() )
		{
			delete itA->second; itA = m_TimerItemActive.erase(itA);
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.begin();
		while ( itD != m_TimerItemDetive.end() )
		{
			delete itD->second; itD = m_TimerItemDetive.erase(itD);
		}
	}

	WORD		HKFiveAndroid::GetWorkTime()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig)
			return AndroidTimer::rdit(pConfig->wMinWorkTime, pConfig->wMaxWorkTime);

		return 0;
	}

	bool		HKFiveAndroid::GetTableID(WORD& wTableID, WORD& wChairID)
	{
		SUser* pUser = GetUserInfo();
		if (pUser)
		{
			SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
			
			if (pUser->nScore >= pConfig->nMinScore && pUser->nScore < pConfig->nMaxScore)
			{
				if (s_wCurTableID == INVALID_TABLE)
					s_wCurTableID = AndroidTimer::rdit(pConfig->wMinTableID, pConfig->wMaxTableID);

				WORD wCount = m_pUserManager->GetTableChairCount(s_wCurTableID);
				if (wCount <= rand() % 4)
				{
					wChairID = m_pUserManager->GetEmptyChairID(s_wCurTableID);
					wTableID = s_wCurTableID;
					return true;
				}
				else
				{
					s_wCurTableID = AndroidTimer::rdit(pConfig->wMinTableID, pConfig->wMaxTableID);
				}
			}
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::Update(float fElapsed)
	{
		if (!IAndroid::Update(fElapsed))
			return 0;

		switch( m_wStaus )
		{
		case US_SIT:
			{
				UpdateTimer(fElapsed);
			}
			break;
		}

		return 0;
	}

	bool		HKFiveAndroid::UpdateOnline(float fElapsed)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnSwitchTable()
	{
		SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
		if (pConfig == NULL)
			return 0;

		SUser* pUser = GetUserInfo();
		if (pUser == NULL)
			return 0;

		INT64 nMin;
		INT64 nMax;
		if (pUser->nScore < pConfig->nMinScore)
		{
			nMin = pConfig->nMinScore - pUser->nScore;
			nMax = pConfig->nMaxScore - pUser->nScore;

			GetScoreFromBanker( AndroidTimer::rdit( nMin,  nMax) );
			return 0;
		}
		else if (pUser->nScore > pConfig->nMaxScore)
		{
			nMin = pUser->nScore - pConfig->nMaxScore;
			nMax = pUser->nScore - pConfig->nMinScore;

			SaveScoreToBanker( AndroidTimer::rdit( nMin,  nMax) );
			return 0;
		}

		WORD wTableID;
		WORD wChairID;
		if (!GetTableID(wTableID, wChairID))
			return 0;

		//构造数据包
		CMD_GR_UserSitReq UserSitReq;
		memset(&UserSitReq, 0, sizeof(UserSitReq));
		UserSitReq.wTableID	= wTableID;
		UserSitReq.wChairID	= wChairID;

		//发送数据包
		WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
		m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_SIT_REQ, &UserSitReq, wSendSize);
	
		m_wSitReqCount ++;
		CString szMessage;
		szMessage.Format("[%d]第%d次请求坐下 桌子ID[%d] 椅子ID[%d]", m_dwUserID, m_wSitReqCount, wTableID, wChairID);
		CTraceService::TraceString(szMessage,
			TraceLevel_Normal);

		//获取场景
		CMD_GF_Info Info;
		ZeroMemory(&Info,sizeof(Info));
		Info.bAllowLookon	= true;

		//发送消息
		m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO, &Info, sizeof(Info));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnReset()
	{	
		m_wTableCount		= 0;
		m_wChairCount		= 0;

		return IAndroid::OnReset();
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnSocketServerInfo(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch( Command.wSubCmdID )
		{
		case SUB_GR_SERVER_INFO:
			{
				CMD_GR_ServerInfo* pServerInfo = (CMD_GR_ServerInfo*)(pBuffer);

				m_wTableCount	= pServerInfo->wTableCount;
				m_wChairCount	= pServerInfo->wChairCount;
			}
			break;
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnTimerEvent(DWORD dwID)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::OnGameMessage(WORD wSubCmdID, const void * pBuffer, 
		WORD wDataSize)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::SetTimer(DWORD dwID, double fElapsed)
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.find(dwID);
		if ( itA != m_TimerItemActive.end())
		{
			itA->second->fElapsed	= fElapsed;
			return true;
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.find(dwID);
		if ( itD != m_TimerItemDetive.end() )
		{
			itD->second->fElapsed	= fElapsed;
			
			m_TimerItemActive.insert(
				TimerItemRegister::value_type(dwID, itD->second)
				);
			m_TimerItemDetive.erase(itD);
		}
		else
		{
			STimerItem* pItem = new STimerItem(dwID, fElapsed);
			m_TimerItemActive.insert(
				TimerItemRegister::value_type(dwID, pItem)
				);
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		HKFiveAndroid::KillTimer(DWORD dwID)
	{
		TimerItemRegister::iterator itA = m_TimerItemActive.find(dwID);
		if ( itA != m_TimerItemActive.end() )
		{
			delete itA->second; m_TimerItemActive.erase(itA);
		}

		TimerItemRegister::iterator itD = m_TimerItemDetive.find(dwID);
		if ( itD != m_TimerItemDetive.end() )
		{
			delete itD->second; m_TimerItemDetive.erase(itD);
		}
		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void		HKFiveAndroid::UpdateTimer(float fElapsed)
	{
		TimerItemRegister::iterator it = m_TimerItemActive.begin();
		while ( it != m_TimerItemActive.end() )
		{
			it->second->fElapsed -= fElapsed;
			if (it->second->fElapsed <= 0)
			{
				m_TimerItemDetive.insert(
					TimerItemRegister::value_type(it->second->dwID, it->second)
					);
				OnTimerEvent(it->second->dwID);

				it = m_TimerItemActive.erase(it);
			}
			else
			{
				it ++;
			}
		}
	}
}