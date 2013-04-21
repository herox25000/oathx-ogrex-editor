#pragma once

#include "IAndroid.h"

namespace O2
{
	//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

#define MAX_COUNT					5

	//�˿�����
#define OX_VALUE0					0									//�������
#define OX_THREE_SAME				12									//��������
#define OX_FOUR_SAME				13									//��������
#define OX_FOURKING					14									//��������
#define OX_FIVEKING					15									//��������

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
