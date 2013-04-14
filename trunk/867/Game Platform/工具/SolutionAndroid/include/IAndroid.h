#pragma once

#include "UserManager.h"

namespace O2
{
#define MAX_REQ_SITDOWNTIEM		5
#define MAX_REQ_SITDOWNCOUNT	8

	//////////////////////////////////////////////////////////////////////////
	// clas android
	//////////////////////////////////////////////////////////////////////////
	class IAndroid : public ITCPSocketSink
	{
	public:
		/*
		* ���캯��
		*/
		IAndroid(DWORD dwUserID, double fOnlineTime);

		/*
		* ��������
		*/
		virtual ~IAndroid(void);
		
	public:
		/*
		* ����������
		*/
		virtual BOOL			Startup(const CString& szIPAdress, WORD wPort, const CString& szPwd);
		/*
		* �����Ը��»�����
		*/		
		virtual bool			Update(float fElapsed);
		/*
		* �رջ�����
		*/		
		virtual void			Shutdown();

	public:
		/*
		* ��ȡ�û�ID
		*/
		virtual DWORD			GetUserID() const;

		/*
		* ��ȡ��ϷID
		*/
		virtual DWORD			GetGameID() const;

		/*
		* ��ȡ�û���Ϣ
		*/
		virtual SUser*			GetUserInfo() const;

		/*	
		* �����û�����ʱ��
		*/
		virtual void			SetOnlineTime(double fOnlineTime);

		/*
		* ��ȡ�û�����ʱ��
		*/
		virtual double			GetOnlineTime() const;
		
		/*
		* ��ȡ�û�ʣ��ʱ��
		*/
		virtual WORD			GetRemaindTime() const;
		/*
		* �����û���ǰ״̬
		*/
		virtual	void			SetStatus(WORD wStatus);
		/*
		* ��ȡ�û���ǰ״̬
		*/		
		virtual WORD			GetStatus() const;
		/*
		* �Ƿ����Լ�
		*/	
		virtual bool			isSelf(WORD wChairID);

		/*
		* �Ƿ����Լ�
		*/	
		virtual bool			isSelf(DWORD wChairID);

		/*
		* ȡǮ
		*/	
		virtual bool			GetScoreFromBanker(INT64 nScore);

		/*
		* ��Ǯ
		*/	
		virtual bool			SaveScoreToBanker(INT64 nScore);
		/*
		* �Ƿ���������
		*/	
		virtual bool			CanOffline();
		/*
		* ��ȡ���н�Ǯ
		*/	
		virtual INT64			GetScore();

		/*
		* ����Э�鷢��
		*/		
		virtual bool			SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData=NULL, 
			WORD wDataSize=0);
	public:
		/*
		* ��ѯ�ӿ�
		*/
		virtual void*	__cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

		/*
		* �ͷŶ���
		*/
		virtual void	__cdecl Release();

		/*
		* �û�����
		*/
		virtual bool	__cdecl	OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
		/*
		* �û��Ͽ�
		*/
		virtual bool	__cdecl	OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
		/*
		* ������Ϣ
		*/
		virtual bool	__cdecl	OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, 
			VOID* pBuffer, WORD wDataSize);

	protected:
		/*
		* ��¼����
		*/
		virtual bool			OnSocketMainLogon(WORD wSocketID, CMD_Command Command, 
			VOID* pBuffer, WORD wDataSize);

		/*
		*�û���Ϣ
		*/
		virtual bool			OnSocketMainUser(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);

		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnSocketMainGameFrame(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);
		/*
		*������Ϣ
		*/
		virtual bool			OnSocketToolBox(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);
		
		/*
		*��ͨ��
		*/
		virtual bool			OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, 
			WORD wDataSize);
	protected:
		/*
		* ���۷�����Ϣ
		*/
		virtual bool			OnSocketServerInfo(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);

		/*
		* ���û���������
		*/	
		virtual bool			OnReset();

		/*
		* ѡ��������Ϣ
		*/	
		virtual bool			OnSwitchTable();

		/*
		*��Ϸ״̬
		*/
		virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, 
			WORD wDataSize=0);
		
		/*
		*��Ӧ��Ǯ
		*/
		virtual bool			OnBanker();
		/*
		*���·�������˳��н�Ǯ
		*/
		virtual void			OnUpdateRobotScoreStart();
		virtual void			OnUpdateRobotScoreEnd();
	protected:
		/*
		* ��ȡ�ͻ���MAC
		*/
		virtual	WORD			GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
		/*
		* ��ȡ�ͻ������к�
		*/		
		virtual	void			GetClientSerial(tagClientSerial& ClientSerial);
		/*
		* ���LOG
		*/	
		virtual void			LogEvent(const CString& lpszText, enTraceLevel lv);
	protected:
		// �û�����ʱ��
		double					m_fOnlineTime;
		double					m_fElapsed;
		double					m_fSitReqTime;
		WORD					m_wSitReqCount;
		DWORD					m_dwUserID;
		CTCPSocketHelper		m_ClientSocket;
		CString					m_Password;
		UserManager*			m_pUserManager;
		BYTE					m_wStaus;
		BYTE					m_bGameStatus;	

		static bool				m_bUpdateRobotScore;
	};

	//////////////////////////////////////////////////////////////////////////
	// �����˴�������
	//////////////////////////////////////////////////////////////////////////
	class IAndroidFactroy
	{
	public:
		/*
		* ���캯��
		*/	
		IAndroidFactroy(DWORD dwTypeID)
			: m_dwTypeID(dwTypeID)
		{

		}
		
		/*
		* ��������
		*/	
		virtual ~IAndroidFactroy()
		{

		}

		/*
		* ����������
		*/	
		virtual IAndroid*		Create(const DWORD dwUserID, double fOnlineTime) = 0;

		/*
		* ���ù�������
		*/	
		virtual void			SetTypeID(DWORD dwTypeID)
		{
			m_dwTypeID = dwTypeID;
		}

		/*
		* ��ȡ��������
		*/	
		virtual DWORD			GetTypeID() const
		{
			return m_dwTypeID;
		}
	protected:
		DWORD					m_dwTypeID;
	};
}

