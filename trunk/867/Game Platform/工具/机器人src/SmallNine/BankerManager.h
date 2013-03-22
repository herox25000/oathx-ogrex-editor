#pragma once

#include "UserManager.h"

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

protected:
	UserManager*				m_pUserManager;
};
