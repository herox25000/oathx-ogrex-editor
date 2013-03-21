#pragma once

typedef struct tagUserInfo
{
	DWORD		dwUserID;		//���ID
	BYTE		cbUserStatus;	//��Ϸ״̬
	WORD		wTableID;		//����ID
	WORD		wChairID;		//����ID
	TCHAR		szName[32];		//�������
	BOOL		bIsRobot;		//�ǲ��ǻ�����
	INT64		lScore;			//�û�����

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

// �û�������
class UserManager
{
	// user info register tabe
	typedef std::map<DWORD, SUserInfo*>	UserRegister;
public:
	static UserManager&		GetSingleton()
	{
		static UserManager	instance;
		return instance;
	}

public:
	UserManager(void);
	virtual ~UserManager(void);

	virtual	BOOL			AddUser(SUserInfo* pUser);
	virtual	SUserInfo*		Search(LPCTSTR lpszName);
	virtual	SUserInfo*		Search(DWORD dwUserID);
	virtual SUserInfo*		Search(WORD wCharID);
	virtual BOOL			Remove(DWORD dwUserID);
protected:
	UserRegister			m_UserRegister;
};
