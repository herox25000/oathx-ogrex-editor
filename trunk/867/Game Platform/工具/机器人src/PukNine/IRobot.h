#pragma once

#include "UserManager.h"

//״̬��Ϣ
struct tagAstatInfo
{
	ADAPTER_STATUS			AdapterStatus;						//����״̬
	NAME_BUFFER				NameBuff[16];						//���ֻ���
};

enum
{
	ROBOT_CREATE,
	ROBOT_SITDOWN,
	ROBOT_INVALID,
};

class IRobot : ITCPSocketSink
{
public:
	IRobot(DWORD dwUserID);
	virtual ~IRobot(void);

	// ��ȡ�û�ID
	virtual	DWORD			GetUserID() const;
	virtual	WORD			GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	virtual	void			GetClientSerial(tagClientSerial& ClientSerial);

	virtual BOOL			Start(const CString& szIPAdress, WORD wPort, const CString& szPwd);
	virtual void			Stop();
	virtual	void			ShowMessageBox(const CString& szMessage, enTraceLevel lev=TraceLevel_Normal);
	virtual	void			SitDown();
	virtual void			AddGameUser(SUserInfo* pUserInfo);
	virtual	void			SetUserStatus(DWORD dwUserID, BYTE cbUserStatus);
	virtual	void			ResetGame();
	virtual bool			SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData=NULL, WORD wDataSize=0);
	
	virtual	WORD			GetReconnect() const;
	virtual	WORD			GetState() const;
	virtual void			SetState(WORD wState);
	virtual void			SetReqSitDownTime(double fTime);
	virtual double			GetReqSitDownTime() const;
	virtual SUserInfo*		GetUserInfo() const;
	virtual WORD			GetSocketState();
	virtual void			Lock();
	virtual int				GetLockCount() const;
	virtual void			Unlock();
public:
	//�ͷŶ���
	virtual void	__cdecl Release()
	{
		delete this;
	}
	//�ӿڲ�ѯ
	virtual void*	__cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer)
	{
		QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
		QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
		return NULL;
	}

	//�����¼�
	virtual bool	__cdecl	OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool	__cdecl	OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool	__cdecl	OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID* pBuffer, WORD wDataSize);

public:
	//��¼��Ϣ
	virtual bool			OnSocketMainLogon(CMD_Command Command, void* pBuffer, WORD wDataSize);
	//�û���Ϣ
	virtual bool			OnSocketMainUser(CMD_Command Command, void* pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	virtual bool			OnSocketMainGameFrame(CMD_Command Command, void* pBuffer, WORD wDataSize);

	//��ͨ��
	virtual bool			OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//��Ϸ״̬
	virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize);
	//�����Ը���
	virtual void			OnUpdate(float fElapsed);
	//��Ϸ��Ϣ
	virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0);

	virtual bool			OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);
protected:
	DWORD					m_dwUserID;
	CString					m_szPwd;
	CTCPSocketHelper		m_ClientSocket;
	SUserInfo*				m_pAppUser;
	UserManager*			m_pGameManager;
	WORD					m_wState;
	BYTE					m_bGameStatus;
	WORD					m_wReconnect;
	double					m_fReqSitDownTime;
	int						m_nApplyBankerCount;
};

// �����˴�������
class IRobotFactory
{
public:
	IRobotFactory(const CString& szName)
		: m_typeName(szName)
	{

	}

	virtual ~IRobotFactory()
	{

	}

public:
	virtual	IRobot*			Create(DWORD dwUserID) = 0;

	virtual	void			SetTypeName(const CString& szName)
	{
		m_typeName = szName;
	}
	virtual CString			GetTypeName() const
	{
		return m_typeName;
	}
protected:
	CString					m_typeName;
};
