#pragma once

namespace O2
{
	// 机器人信息结构
	struct SUser
	{
		DWORD		dwUserID;		//玩家ID
		BYTE		cbUserStatus;	//游戏状态
		WORD		wTableID;		//桌子ID
		WORD		wChairID;		//椅子ID
		TCHAR		szName[32];		//玩家名称
		INT64		nScore;			//用户积分
		DWORD		dwGameID;		//游戏ID

		SUser()
			: dwUserID(0), dwGameID(0), nScore(0), wTableID(INVALID_TABLE), wChairID(INVALID_CHAIR), cbUserStatus(US_NULL)
		{

		}
	};

	// 用户映射表
	typedef std::map<DWORD, SUser*>	UserRegister;

	//////////////////////////////////////////////////////////////////////////
	// 机器人信息管理其
	//////////////////////////////////////////////////////////////////////////
	class UserManager
	{
	public:
		/*
		* 构造函数
		*/
		UserManager(void);
		
		/*
		* 析构函数
		*/		
		virtual ~UserManager(void);

		/*
		* 添加用户
		*/
		virtual void			Add(SUser* pUser);
		/*
		* 移除用户
		*/
		virtual void			Remove(DWORD dwUserID, bool bDestroy=true);
		/*
		* 由用户ID搜索
		*/		
		virtual SUser*			Search(DWORD dwID, bool bGameID=0);
		/*
		* 由用户名搜索
		*/		
		virtual SUser*			Search(LPCTSTR lpszName);
		/*
		* 由角色ID搜索
		*/		
		virtual SUser*			Search(WORD wCharID);
		/*
		* 销毁所有角色
		*/		
		virtual void			Clear(bool bDestroy=true);
	protected:
		UserRegister			m_UserRegister;
	};
}

