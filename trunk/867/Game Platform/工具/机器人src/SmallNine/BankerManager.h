#pragma once

#include "UserManager.h"
#include <deque>

class BankerManager
{
public:
	static BankerManager&		GetSingleton()
	{
		static BankerManager instance;
		return instance;
	}
public:
	BankerManager(void);
	virtual ~BankerManager(void);

	virtual	void				AddUser(SUserInfo* pUserInfo);
	virtual int					GetBankerCount() const;
	virtual void				Remove(DWORD dwUserID);
	virtual	SUserInfo*			Search(DWORD dwUserID);

	virtual	void				Lock();
	virtual int					GetLockCount() const;
	virtual	void				Unlock();
protected:
	UserManager*				m_pUserManager;
	int							m_wApplyCount;

};
