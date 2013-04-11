#pragma once

#include "UserManager.h"
#include <map>
#include <deque>

namespace O2
{
	struct SBanker
	{
		CString	szName;
		INT64	nScore;
		DWORD	dwUserID;

		SBanker(const CString& _szName, INT64 _nScore, DWORD _dwUserID)
			: szName(_szName), nScore(_nScore), dwUserID(_dwUserID)
		{
			
		}
	};

	typedef std::map<DWORD, SBanker*>	BankerRegister;
	typedef std::deque<DWORD>			BankerRequest;
	//////////////////////////////////////////////////////////////////////////
	// 上庄管理器
	//////////////////////////////////////////////////////////////////////////
	class BankerManager
	{
	public:
		/*
		* 获取单件对象
		*/
		static BankerManager&	GetSingleton()
		{
			static BankerManager instance;
			return instance;
		}

	public:
		/*
		* 构造函数
		*/
		BankerManager();

		/*
		* 析构函数
		*/	
		virtual ~BankerManager();

		/*
		* 插入庄家
		*/
		virtual	bool			Insert(SBanker* pBanker);
		/*
		* 获取排庄总数
		*/		
		virtual DWORD			GetBankerCount() const;
		/*
		* 移除
		*/		
		virtual void			Remove(DWORD dwUserID);
		/*
		* 查找庄家
		*/		
		virtual SBanker*		Search(DWORD dwUserID);

		/*
		* 添加庄家请求
		*/	
		virtual void			AddRequest(DWORD dwUserID);
		/*
		* 获取请求总数
		*/			
		virtual DWORD			GetRequestCount() const;

		/*
		* 获取请求总数
		*/	
		virtual bool			CheckRequest(DWORD dwUserID);

		/*
		* 移除请求
		*/			
		virtual void			RemoveRequest(DWORD dwUserID);
		/*
		* 清空全部
		*/
		virtual void			ClearRequest();
	protected:
		BankerRegister			m_BankerRegister;
		BankerRequest			m_BankerRequest;
	};
}