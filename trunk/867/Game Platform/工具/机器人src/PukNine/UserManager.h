#pragma once

typedef struct tagUserInfo
{
	DWORD		dwUserID;		//玩家ID
	BYTE		cbUserStatus;	//游戏状态
	WORD		wTableID;		//桌子ID
	WORD		wChairID;		//椅子ID
	TCHAR		szName[32];		//玩家名称
	BOOL		bIsRobot;		//是不是机器人
	INT64		lScore;			//用户积分

	tagUserInfo()
	{
		dwUserID		= 0;
		cbUserStatus	= US_NULL;
		wTableID		= INVALID_TABLE;
		wChairID		= INVALID_CHAIR;
		szName[0]		= '\0';
		bIsRobot		= FALSE;
		lScore			= 0L;
	}
}SUserInfo;

// 用户管理器
class UserManager
{
	// user info register tabe
	typedef std::map<DWORD, SUserInfo*>	UserRegister;
public:
	UserManager(void);
	virtual ~UserManager(void);

	virtual	BOOL			AddUser(SUserInfo* pUser);
	virtual	SUserInfo*		Search(LPCTSTR lpszName);
	virtual	SUserInfo*		Search(DWORD dwUserID);
	virtual SUserInfo*		Search(WORD wCharID);
	virtual BOOL			Remove(DWORD dwUserID, BOOL bDestroy=TRUE);
	virtual int				GetCount() const;
	virtual	void			ClearUp();
protected:
	UserRegister			m_UserRegister;
};
