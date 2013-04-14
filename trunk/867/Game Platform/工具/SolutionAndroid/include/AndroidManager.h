#pragma once

#include "IAndroid.h"

namespace O2
{
	// ������ע���
	typedef std::map<DWORD, IAndroid*>	AndroidRegister;

	//////////////////////////////////////////////////////////////////////////
	// �����˹�����
	//////////////////////////////////////////////////////////////////////////
	class AndroidManager
	{
	public:
		// ����ָ��
		static AndroidManager*	mpSingleton;

		/*
		* ��ȡ����
		*/
		static AndroidManager*	GetSingleton();

	public:
		/*
		* ���캯��
		*/	
		AndroidManager(IAndroidFactroy* pFactory);

		/*
		* ��������
		*/	
		virtual ~AndroidManager(void);

	public:
		/*
		* ����������
		*/	
		virtual void			Startup();

		/*
		* �����Ը���
		*/			
		virtual bool			Update(float fElapsed);

		/*
		* �رջ�����
		*/			
		virtual void			Shutdown();

		/*
		* ��ȡ��ǰ����������
		*/
		virtual	int				GetAndroidCount() const;

		/*
		* ��ӻ�����
		*/	
		virtual void			AddAndroid(IAndroid* pAndroid);

		/*
		* ���һ�����
		*/			
		virtual IAndroid*		Search(DWORD dwUserID);
		
		/*
		* ���һ�����
		*/	
		virtual IAndroid*		GetAndroid(DWORD idx);

		/*
		* ���ٻ�����
		*/			
		virtual void			Destroy(IAndroid* pAndroid);

		/*
		* �������л�����
		*/	
		virtual void			DestroyAll();
		/*
		*���»����˱���
		*/
		virtual void			UpdateRobotScore();
		virtual void			SetGameEnd(bool bGameEnd) { m_bGameEnd = bGameEnd; }
	protected:
		AndroidRegister			m_AndroidRegister;
		double					m_fElapsed;
		double					m_fCreate;
		IAndroidFactroy*		m_pFactory;
		double					m_fCheckMoneyElapsed;
		bool					m_bGameEnd;
	};
}
