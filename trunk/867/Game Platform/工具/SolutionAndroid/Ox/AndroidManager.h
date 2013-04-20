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
		/*
		* 构造函数
		*/	
		AndroidManager(DWORD dwStartID, DWORD dwEndID, IAndroidFactroy* pFactory);

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

		/*
		* 获取当前机器人总数
		*/
		virtual	int				GetAndroidCount() const;

		/*
		* 添加机器人
		*/	
		virtual void			AddAndroid(IAndroid* pAndroid);

		/*
		* 查找机器人
		*/			
		virtual IAndroid*		Search(DWORD dwUserID);
		
		/*
		* 查找机器人
		*/	
		virtual IAndroid*		GetAndroid(DWORD idx);

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
		double					m_fElapsed;
		double					m_fCreate;
		IAndroidFactroy*		m_pFactory;
		DWORD					m_dwStartID;
		DWORD					m_dwEndID;
	};
}
