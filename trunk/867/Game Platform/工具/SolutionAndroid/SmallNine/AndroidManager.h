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
		AndroidManager(DWORD dwStartID, DWORD dwEndID, DWORD dwMaxCount,
			IAndroidFactroy* pFactory);

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

	public:
		/*
		* ���ÿ�ʼID
		*/
		virtual	void			SetStartID(DWORD dwStartID);

		/*
		* ��ȡ��ʼID
		*/		
		virtual DWORD			GetStartID() const;

		/*
		* ���ý���ID
		*/		
		virtual void			SetEndID(DWORD dwEndID);

		/*
		* ��ȡ����ID
		*/		
		virtual DWORD			GetEndID() const;

		/*
		* ���������ٻ�����
		*/	
		virtual void			SetMaxCount(DWORD dwMaxCount);
		
		/*
		* ��ȡ�����ٻ�����
		*/	
		virtual DWORD			GetMaxCount() const;

		/*
		* ��ȡ��ǰ����������
		*/
		virtual	int				GetAndroidCount() const;

	public:
		/*
		* ��ӻ�����
		*/	
		virtual void			AddAndroid(IAndroid* pAndroid);

		/*
		* ���һ�����
		*/			
		virtual IAndroid*		Search(DWORD dwUserID);

		/*
		* ���ٻ�����
		*/			
		virtual void			Destroy(IAndroid* pAndroid);

		/*
		* �������л�����
		*/	
		virtual void			DestroyAll();
	protected:
		AndroidRegister			m_AndroidRegister;
		DWORD					m_dwStartID;
		DWORD					m_dwEndID;
		double					m_fElapsed;
		double					m_fCreate;
		DWORD					m_dwMaxCount;
		double					m_fMaxOnlineTime;
		double					m_fMinOnlineTime;
		IAndroidFactroy*		m_pFactory;
	};
}
