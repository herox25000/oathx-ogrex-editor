#pragma once

#include <vector>

struct tagUserInfo
{
	tagUserInfo()
	{
		dwUserID = 0;
		cbUserStatus = US_NULL;
		wTableID = INVALID_TABLE;
		wChairID = INVALID_CHAIR;
		szName[0] = '\0';
		bIsRobot = FALSE;
		lScore = 0L;
	}
	DWORD		dwUserID;		//玩家ID
	BYTE		cbUserStatus;	//游戏状态
	WORD		wTableID;		//桌子ID
	WORD		wChairID;		//椅子ID
	TCHAR		szName[32];		//玩家名称
	BOOL		bIsRobot;		//是不是机器人
	__int64		lScore;			//用户积分
};

typedef std::vector<tagUserInfo*> UserVec;

class CUserManager
{
public:
	CUserManager(){}
	~CUserManager()
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter)
			{
				delete *iter;
			}
		}
	}

	void RemoveAll()
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter)
			{
				delete *iter;
			}
		}
		m_UserVec.clear();
	}

	tagUserInfo* SearchUserByUserID(DWORD dwUserID)
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter&&(*iter)->dwUserID == dwUserID)
			{
				return *iter;
			}
		}
		return NULL;
	}

	tagUserInfo* SearchUserByChairID(WORD wChairID)
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter&&(*iter)->wChairID == wChairID)
			{
				return *iter;
			}
		}
		return NULL;
	}

	tagUserInfo* SearchUserByName(TCHAR szName[32])
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter&&lstrcmp((*iter)->szName, szName)==0)
			{
				return *iter;
			}
		}
		return NULL;
	}

	void InsertInfo(tagUserInfo *pUserInfo)
	{
		m_UserVec.push_back(pUserInfo);
	}

	void UpdateInfo(DWORD dwUserID, __int64	lScore)
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter&&(*iter)->dwUserID == dwUserID)
			{
				(*iter)->lScore = lScore;
				break;
			}
		}
	}

	void RemoveInfo(DWORD dwUserID)
	{
		for(UserVec::iterator iter = m_UserVec.begin();
			iter != m_UserVec.end();++iter)
		{
			if(*iter&&(*iter)->dwUserID == dwUserID)
			{
				m_UserVec.erase(iter);
				break;
			}
		}
	}

	tagUserInfo* GetIndex(UserVec::size_type i)
	{
		return m_UserVec[i];
	}

	UserVec::size_type  GetSize()
	{
		return m_UserVec.size();
	}

private:
	UserVec		m_UserVec;
};