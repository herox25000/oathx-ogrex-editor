#pragma once

#include "IAndroid.h"

namespace O2
{
	struct STimerItem
	{
		DWORD						dwID;
		float						fElapsed;

		STimerItem(DWORD id, float fTime)
			: dwID(id), fElapsed(fTime)
		{

		}
	};
	
	typedef std::map<DWORD, STimerItem*> TimerItemRegister;

	//////////////////////////////////////////////////////////////////////////
	// 牛牛机器人
	//////////////////////////////////////////////////////////////////////////
	class HKFiveAndroid : public IAndroid
	{
	public:
		// 构造函数
		HKFiveAndroid(DWORD dwUserID, double fOnlineTime);
		// 析构函数
		virtual ~HKFiveAndroid();
		
	public:
		// 周期性更新
		virtual bool			Update(float fElapsed);

		//获取工作时间
		virtual WORD			GetWorkTime();
		//获取桌子ID
		virtual bool			GetTableID(WORD& wTableID, WORD& wChairID);
	protected:
		/*
		* 房价服务信息
		*/
		virtual bool			OnSocketServerInfo(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);

		/*
		* 重置机器人数据
		*/	
		virtual bool			OnReset();

		/*
		* 选择桌子信息
		*/	
		virtual bool			OnSwitchTable();

		/*
		*游戏状态
		*/
		virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*游戏消息
		*/
		virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, 
			WORD wDataSize=0);
		
		/*
		*游戏消息
		*/
		virtual bool			OnTimerEvent(DWORD dwID);
		/*
		*更新在线时间
		*/
		virtual bool			UpdateOnline(float fElapsed);

	protected:
		virtual bool			OnSubGameStart(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubAddScore(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubGiveUp(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubSendCard(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubGameEnd(const void* pBuffer, WORD wDataSize);
	protected:
		//设置定时器
		virtual bool			SetTimer(DWORD dwID, double fElapsed);
		//删除定时器
		virtual bool			KillTimer(DWORD dwID);
		//更新定时器
		virtual void			UpdateTimer(float fElapsed);
	protected:
		WORD					m_wTableCount;
		WORD					m_wChairCount;
		TimerItemRegister		m_TimerItemActive;
		TimerItemRegister		m_TimerItemDetive;
		INT64					m_nMaxScore;
		INT64					m_nCellScore;
		INT64					m_nTurnMaxScore;
		INT64					m_nTurnLessScore;
		INT64					m_nTableScore[10];
	};

	class HKFiveFactory : public IAndroidFactroy
	{
	public:
		HKFiveFactory(DWORD dwTypeID)
			: IAndroidFactroy(dwTypeID)
		{

		}

		virtual ~HKFiveFactory()
		{

		}

		virtual IAndroid*		Create(const DWORD dwUserID, double fOnlineTime)
		{
			return new HKFiveAndroid(dwUserID, fOnlineTime);
		}
	};
}
