#pragma once

#include "IAndroid.h"

namespace O2
{
	// 机器人注册表
	typedef std::map<DWORD, IAndroid*>	AndroidRegister;

	//////////////////////////////////////////////////////////////////////////
	// 机器人管理其
	//////////////////////////////////////////////////////////////////////////
	class AndroidManager
	{
	public:
		// 单件指针
		static AndroidManager*	mpSingleton;

		/*
		* 获取单件
		*/
		static AndroidManager*	GetSingleton();

	public:
		/*
		* 构造函数
		*/	
		AndroidManager(DWORD dwStartID, DWORD dwEndID, DWORD dwMaxCount,
			IAndroidFactroy* pFactory);

		/*
		* 析构函数
		*/	
		virtual ~AndroidManager(void);

	public:
		/*
		* 启动机器人
		*/	
		virtual void			Startup();

		/*
		* 周期性更新
		*/			
		virtual bool			Update(float fElapsed);

		/*
		* 关闭机器人
		*/			
		virtual void			Shutdown();

	public:
		/*
		* 设置开始ID
		*/
		virtual	void			SetStartID(DWORD dwStartID);

		/*
		* 获取开始ID
		*/		
		virtual DWORD			GetStartID() const;

		/*
		* 设置结束ID
		*/		
		virtual void			SetEndID(DWORD dwEndID);

		/*
		* 获取结束ID
		*/		
		virtual DWORD			GetEndID() const;

		/*
		* 设置最大多少机器人
		*/	
		virtual void			SetMaxCount(DWORD dwMaxCount);
		
		/*
		* 获取最大多少机器人
		*/	
		virtual DWORD			GetMaxCount() const;

		/*
		* 获取当前机器人总数
		*/
		virtual	int				GetAndroidCount() const;

	public:
		/*
		* 添加机器人
		*/	
		virtual void			AddAndroid(IAndroid* pAndroid);

		/*
		* 查找机器人
		*/			
		virtual IAndroid*		Search(DWORD dwUserID);

		/*
		* 销毁机器人
		*/			
		virtual void			Destroy(IAndroid* pAndroid);

		/*
		* 销毁所有机器人
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
