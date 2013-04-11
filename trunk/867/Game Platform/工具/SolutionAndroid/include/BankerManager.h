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
	// ��ׯ������
	//////////////////////////////////////////////////////////////////////////
	class BankerManager
	{
	public:
		/*
		* ��ȡ��������
		*/
		static BankerManager&	GetSingleton()
		{
			static BankerManager instance;
			return instance;
		}

	public:
		/*
		* ���캯��
		*/
		BankerManager();

		/*
		* ��������
		*/	
		virtual ~BankerManager();

		/*
		* ����ׯ��
		*/
		virtual	bool			Insert(SBanker* pBanker);
		/*
		* ��ȡ��ׯ����
		*/		
		virtual DWORD			GetBankerCount() const;
		/*
		* �Ƴ�
		*/		
		virtual void			Remove(DWORD dwUserID);
		/*
		* ����ׯ��
		*/		
		virtual SBanker*		Search(DWORD dwUserID);

		/*
		* ���ׯ������
		*/	
		virtual void			AddRequest(DWORD dwUserID);
		/*
		* ��ȡ��������
		*/			
		virtual DWORD			GetRequestCount() const;

		/*
		* ��ȡ��������
		*/	
		virtual bool			CheckRequest(DWORD dwUserID);

		/*
		* �Ƴ�����
		*/			
		virtual void			RemoveRequest(DWORD dwUserID);
		/*
		* ���ȫ��
		*/
		virtual void			ClearRequest();
	protected:
		BankerRegister			m_BankerRegister;
		BankerRequest			m_BankerRequest;
	};
}