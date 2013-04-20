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
		/*
		* ���캯��
		*/	
		AndroidManager(DWORD dwStartID, DWORD dwEndID, IAndroidFactroy* pFactory);

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
	protected:
		AndroidRegister			m_AndroidRegister;
		double					m_fElapsed;
		double					m_fCreate;
		IAndroidFactroy*		m_pFactory;
		DWORD					m_dwStartID;
		DWORD					m_dwEndID;
	};
}
