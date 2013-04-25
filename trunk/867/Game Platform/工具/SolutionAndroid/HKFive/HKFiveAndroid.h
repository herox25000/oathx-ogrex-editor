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
	// ţţ������
	//////////////////////////////////////////////////////////////////////////
	class HKFiveAndroid : public IAndroid
	{
	public:
		// ���캯��
		HKFiveAndroid(DWORD dwUserID, double fOnlineTime);
		// ��������
		virtual ~HKFiveAndroid();
		
	public:
		// �����Ը���
		virtual bool			Update(float fElapsed);

		//��ȡ����ʱ��
		virtual WORD			GetWorkTime();
		//��ȡ����ID
		virtual bool			GetTableID(WORD& wTableID, WORD& wChairID);
	protected:
		/*
		* ���۷�����Ϣ
		*/
		virtual bool			OnSocketServerInfo(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);

		/*
		* ���û���������
		*/	
		virtual bool			OnReset();

		/*
		* ѡ��������Ϣ
		*/	
		virtual bool			OnSwitchTable();

		/*
		*��Ϸ״̬
		*/
		virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, 
			WORD wDataSize=0);
		
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnTimerEvent(DWORD dwID);
		/*
		*��������ʱ��
		*/
		virtual bool			UpdateOnline(float fElapsed);

	protected:
		virtual bool			OnSubGameStart(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubAddScore(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubGiveUp(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubSendCard(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubGameEnd(const void* pBuffer, WORD wDataSize);
	protected:
		//���ö�ʱ��
		virtual bool			SetTimer(DWORD dwID, double fElapsed);
		//ɾ����ʱ��
		virtual bool			KillTimer(DWORD dwID);
		//���¶�ʱ��
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
