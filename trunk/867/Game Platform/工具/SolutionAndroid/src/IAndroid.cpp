#include "StdAfx.h"
#include "IAndroid.h"
#include "ConfigFile.h"
#include "AndroidTimer.h"
#include "UserManager.h"
#include "AndroidManager.h"
#include "BankerManager.h"

namespace O2
{
	bool IAndroid::m_bUpdateRobotScore = false;
	//״̬��Ϣ
	struct tagAstatInfo
	{
		ADAPTER_STATUS			AdapterStatus;						//����״̬
		NAME_BUFFER				NameBuff[16];						//���ֻ���
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	IAndroid::IAndroid(DWORD dwUserID, double fOnlineTime)
		: m_dwUserID(dwUserID), m_fOnlineTime(fOnlineTime), m_fElapsed(0), m_wSitReqCount(0), m_fSitReqTime(0), m_pUserManager(NULL), m_wStaus(US_NULL)
	{
		m_pUserManager = new UserManager();
	}

	//////////////////////////////////////////////////////////////////////////
	IAndroid::~IAndroid(void)
	{
		delete m_pUserManager;
		m_pUserManager = NULL;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void* __cdecl	IAndroid::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
	{
		QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
		QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	void __cdecl	IAndroid::Release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	WORD			IAndroid::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
	{
		//��������
		WORD wMacSize=0;
		HINSTANCE hInstance=NULL;
		typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

		try
		{
			//���� DLL
			hInstance=LoadLibrary(TEXT("NetApi32.dll"));
			if (hInstance==NULL) 
				throw TEXT("���� NetApi32.dll ʧ��");

			//��ȡ����
			NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
			if (pNetBiosProc==NULL) 
				throw TEXT("�޷��ҵ� NetBios ����");

			//��������
			NCB Ncb;
			LANA_ENUM LanaEnum;
			ZeroMemory(&Ncb,sizeof(Ncb));
			ZeroMemory(&LanaEnum,sizeof(LanaEnum));

			//ö������
			Ncb.ncb_command=NCBENUM;
			Ncb.ncb_length=sizeof(LanaEnum);
			Ncb.ncb_buffer=(BYTE *)&LanaEnum;
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("ö������ʧ��");
			if (LanaEnum.length==0)
				throw TEXT("�Ҳ����κ�����");

			//��ȡ��ַ
			tagAstatInfo Adapter;
			for (BYTE i=0;i<LanaEnum.length;i++)
			{
				//��������
				ZeroMemory(&Ncb,sizeof(Ncb));
				Ncb.ncb_command=NCBRESET;
				Ncb.ncb_lana_num=LanaEnum.lana[i];
				if (pNetBiosProc(&Ncb)!=NRC_GOODRET) 
					throw TEXT("��������ʧ��");

				//��ȡ״̬
				ZeroMemory(&Ncb,sizeof(Ncb));
				Ncb.ncb_command=NCBASTAT;
				Ncb.ncb_length=sizeof(Adapter);
				Ncb.ncb_buffer=(BYTE *)&Adapter;
				Ncb.ncb_lana_num=LanaEnum.lana[i];
				strcpy((char *)Ncb.ncb_callname,"*");
				if (pNetBiosProc(&Ncb)!=NRC_GOODRET)
					throw TEXT("��ȡ����״̬ʧ��");

				//��ȡ��ַ
				if (wMacSize<wBufferSize)
				{
					//������ַ
					WORD wCopySize=__min((wBufferSize-wMacSize),sizeof(BYTE)*6);
					CopyMemory(cbMacBuffer,Adapter.AdapterStatus.adapter_address,wCopySize);

					//����ж�
					wMacSize+=wCopySize;
					if (wMacSize==wBufferSize) break;
				}
			}

			//�ͷ���Դ
			if (hInstance!=NULL)
			{
				FreeLibrary(hInstance);
				hInstance=NULL;
			}

			return wMacSize;
		}
		catch (...) 
		{ 
			//�ͷ���Դ
			if (hInstance!=NULL)
			{
				FreeLibrary(hInstance);
				hInstance=NULL;
			}
		}

		return wMacSize;
	}

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::GetClientSerial(tagClientSerial & ClientSerial)
	{
		//��ȡ�汾
		OSVERSIONINFO OSVerInfo;
		OSVerInfo.dwOSVersionInfoSize=sizeof(OSVerInfo);
		GetVersionEx(&OSVerInfo);
		ClientSerial.dwSystemVer=MAKELONG(OSVerInfo.dwMajorVersion,OSVerInfo.dwMinorVersion);

		//������ʶ
		ZeroMemory(ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));
		WORD wMacSize=GetMACAddress((BYTE *)ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));

		//Ӳ�̱�ʶ
		WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
		LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
		for (WORD i=wIndex;i<CountArray(ClientSerial.dwComputerID);i++)
		{
			ASSERT(CountArray(pszHardDisk)>(i-wIndex));
			GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,&ClientSerial.dwComputerID[i],NULL,NULL,0,NULL);
		}

		return;
	}

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::LogEvent(const CString& lpszText, enTraceLevel lv)
	{
		CTraceService::TraceString(lpszText, lv);
	}

	/*
	* ��ȡ�û�ID
	*/
	DWORD			IAndroid::GetUserID() const
	{
		return m_dwUserID;
	}

	/*
	* ��ȡ��ϷID
	*/
	DWORD			IAndroid::GetGameID() const
	{
		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
			return pUser->dwGameID;

		return 0;
	}

	/*
	* ��ȡ�����û���Ϣ
	*/
	SUser*			IAndroid::GetUserInfo() const
	{
		return m_pUserManager->Search(m_dwUserID);
	}

	/*
	* �����û�����ʱ��
	*/
	void			IAndroid::SetOnlineTime(double fOnlineTime)
	{
		m_fOnlineTime = fOnlineTime;
	}

	/*
	* ��ȡ�û�����ʱ��
	*/
	double			IAndroid::GetOnlineTime() const
	{
		return m_fOnlineTime;
	}

	//////////////////////////////////////////////////////////////////////////
	WORD			IAndroid::GetRemaindTime() const
	{
		return (WORD)(m_fOnlineTime - (m_fElapsed / 60));
	}

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::SetStatus(WORD wStatus)
	{
		m_wStaus = wStatus;
	}

	//////////////////////////////////////////////////////////////////////////
	WORD			IAndroid::GetStatus() const
	{
		return m_wStaus;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::isSelf(WORD wChairID)
	{
		SUser* pUser = m_pUserManager->Search(wChairID);
		if (pUser != NULL && pUser->dwUserID == m_dwUserID)
			return true;

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::isSelf(DWORD dwUserID)
	{
		return m_dwUserID == dwUserID;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::CanOffline()
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	INT64			IAndroid::GetScore()
	{
		SUser* pUser = m_pUserManager->Search(m_dwUserID);
		if (pUser)
			return pUser->nScore;

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::GetScoreFromBanker(INT64 nScore)
	{
		CMD_TOOLBOX_BankTask tb;
		memset(&tb, 0, sizeof(CMD_TOOLBOX_BankTask));

		INT64 nCurScore = GetScore();
		INT64 nAfterScore = nCurScore + nScore;
		nAfterScore = nAfterScore / 100 * 100;
		nScore = nAfterScore - nCurScore;

		tb.lMoneyNumber	= nScore;
		tb.lBankTask		= 2;
		CopyMemory(tb.szPassword, m_Password.GetBuffer(), sizeof(tb.szPassword));

		m_ClientSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &tb, sizeof(tb));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::SaveScoreToBanker(INT64 nScore)
	{
		if (US_FREE != m_wStaus)
		{
			CString szMessage;
			szMessage.Format("Robot[%d] request sit up", m_dwUserID);
			CTraceService::TraceString(szMessage,
				TraceLevel_Normal);
			m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);
		}

		CMD_TOOLBOX_BankTask tb;
		memset(&tb, 0, sizeof(CMD_TOOLBOX_BankTask));

		INT64 nCurScore = GetScore();
		INT64 nLeftScore = nCurScore - nScore;
		nLeftScore = nLeftScore / 100 * 100;
		nScore = nCurScore - nLeftScore;
		
		tb.lMoneyNumber	= nScore;
		tb.lBankTask		= 1;
		CopyMemory(tb.szPassword, m_Password.GetBuffer(), sizeof(tb.szPassword));

		m_ClientSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &tb, sizeof(tb));
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	BOOL			IAndroid::Startup(const CString& szIPAdress, WORD wPort, const CString& szPwd)
	{
		//�������
		IUnknownEx* pIUnknown = QUERY_ME_INTERFACE(IUnknownEx);
		if (!m_ClientSocket.CreateInstance())
			return FALSE;

		if (!m_ClientSocket->SetTCPSocketSink(pIUnknown))
			return false;

		DWORD dwResult = m_ClientSocket->Connect(szIPAdress, wPort);
		if (!dwResult)
		{
			CString szMessage;
			szMessage.Format("[%d]��������", m_dwUserID);
			CTraceService::TraceString(szMessage,
				TraceLevel_Normal);

			m_Password = szPwd;
		}

		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::Update(float fElapsed)
	{
		if (m_wStaus == US_OFFLINE)
			return 0;

		switch( m_wStaus )
		{
		case US_FREE:
			{
				if (m_wSitReqCount <= MAX_REQ_SITDOWNCOUNT)
				{
					m_fSitReqTime += fElapsed;
					if (m_fSitReqTime >= MAX_REQ_SITDOWNTIEM)
					{
						OnReset();
						OnSwitchTable();
						m_fSitReqTime = 0;
					}
				}
				else
				{
					SetStatus(US_OFFLINE);
					return 0;
				}
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::Shutdown()
	{
		if (m_ClientSocket.GetInterface() != NULL) 
		{
			SUser* pUser = m_pUserManager->Search(m_dwUserID);
			if (pUser && pUser->cbUserStatus == US_PLAY)
			{
				m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_LEFT_GAME_REQ);
			}

			m_ClientSocket->SendData(MDM_GR_USER, 
				SUB_GR_USER_STANDUP_REQ);

			m_ClientSocket->CloseSocket();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, 
		WORD wDataSize)
	{
		if(pData)
		{
			return m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize) > 0 ? true : 0;
		}
		else
		{
			return m_ClientSocket->SendData(wMainCmdID, wSubCmdID)  > 0 ? true : 0;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/*
	* �û�����
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
	{
		CString szError;

		if ( nErrorCode != 0)
		{
			szError.Format("[%d]����ʧ��, �������:%d",m_dwUserID, nErrorCode);
			CTraceService::TraceString(szError,
				TraceLevel_Warning);

			SetStatus(US_OFFLINE);
			return 0;
		}

		//��ȡ��Ϣ
		BYTE cbBuffer[SOCKET_PACKET];

		//��¼���ݰ�
		CMD_GR_LogonByUserID* pLogonByUserID = (CMD_GR_LogonByUserID *)cbBuffer;

		pLogonByUserID->dwUserID		= m_dwUserID;
		pLogonByUserID->dwPlazaVersion	= VER_PLAZA_FRAME;
		lstrcpyn(pLogonByUserID->szPassWord, m_Password, sizeof(pLogonByUserID->szPassWord));

		//�������к�
		tagClientSerial ClientSerial;
		GetClientSerial(ClientSerial);

		//�������ݰ�
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID), 
			sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
		Packet.AddPacket(&ClientSerial, sizeof(ClientSerial), DTP_COMPUTER_ID);

		m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID, cbBuffer, sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

		szError.Format("[%i]���������ѽ���", (int)m_dwUserID);
		CTraceService::TraceString(szError,
			TraceLevel_Normal);
		
		return true;
	}
	
	/*
	* �û��Ͽ�
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
	{
		CString szMessage;
		szMessage.Format("[%d]���������ѶϿ�", m_dwUserID);
		LogEvent(szMessage, TraceLevel_Warning);
		
		// ���û�����Ϊ��Ч��
		SetStatus(US_OFFLINE);
		
		return true;
	}

	/*
	* ������Ϣ
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, 
		VOID* pBuffer, WORD wDataSize)
	{
		switch (Command.wMainCmdID)
		{
		case MDM_GR_LOGON:			//��¼��Ϣ
			{
				return OnSocketMainLogon(wSocketID, Command, pBuffer,wDataSize);
			}
		case MDM_GR_USER:			//�û���Ϣ
			{
				return OnSocketMainUser(Command, pBuffer, wDataSize);
			}
		case MDM_GR_INFO:			//������Ϣ
			{
				return OnSocketServerInfo(Command, pBuffer, wDataSize);
			}
		case MDM_GR_STATUS:			//״̬��Ϣ
			{
				return true;
			}
		case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
			{
				return true;
			}

		case MDM_GF_GAME:			//��Ϸ��Ϣ
		case MDM_GF_FRAME:			//�����Ϣ
			{
				return OnSocketMainGameFrame(Command,pBuffer,wDataSize);
			}
		case MDM_TOOLBOX:
			{
				return OnSocketToolBox(Command, pBuffer, wDataSize);
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocketMainLogon(WORD wSocketID, CMD_Command Command, 
		VOID* pBuffer, WORD wDataSize)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GR_LOGON_SUCCESS:
			{
				CString szMessage;
				szMessage.Format("[%d]��¼�ɹ�", m_dwUserID);
				LogEvent(szMessage, TraceLevel_Normal);
			}
			break;

		case SUB_GR_LOGON_ERROR:
			{
				//Ч�����
				CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;

				if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) 
					return 0;

				//�ر�����
				m_ClientSocket->CloseSocket();

				//��ʾ��Ϣ
				WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
				if (wDescribeSize>0)
				{
					pLogonError->szErrorDescribe[wDescribeSize-1]=0;
					LogEvent(pLogonError->szErrorDescribe, 
						TraceLevel_Warning);
				}

				SetStatus(US_OFFLINE);
			}
			break;

		case SUB_GR_LOGON_FINISH:
			{
				//�������ݰ�
				CMD_GR_UserRule UserRule;
				memset(&UserRule, 0, sizeof(CMD_GR_UserRule));
				UserRule.bLimitWin		= 0;
				UserRule.bLimitFlee		= 0;
				UserRule.wWinRate		= 0;
				UserRule.wFleeRate		= 0;
				UserRule.lMaxScore		= 0;
				UserRule.lLessScore		= 0;
				UserRule.bLimitScore	= 0;
				UserRule.bPassword		= 0;
				UserRule.bCheckSameIP	= 0;

				//�������ݰ�
				m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_RULE, &UserRule, sizeof(UserRule));
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocketMainUser(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch(Command.wSubCmdID)
		{
		case SUB_GR_USER_COME:
			{
				if (wDataSize<sizeof(tagUserInfoHead)) 
					return 0;

				//��ȡ������Ϣ
				tagUserInfoHead* pUserInfoHead = (tagUserInfoHead *)(pBuffer);

				SUser* pUser = m_pUserManager->Search(pUserInfoHead->dwUserID);
				if (!pUser)
					pUser = new SUser();

				if (pUser)
				{
					pUser->nScore		= pUserInfoHead->UserScoreInfo.lScore;	
					pUser->dwUserID		= pUserInfoHead->dwUserID;
					pUser->nScore		= pUserInfoHead->UserScoreInfo.lScore;
					pUser->wTableID		= pUserInfoHead->wTableID;
					pUser->wChairID		= pUserInfoHead->wChairID;
					pUser->cbUserStatus	= pUserInfoHead->cbUserStatus;
					pUser->dwGameID		= pUserInfoHead->dwGameID;

					// ���õ�¼ʱ��
					time_t		timer	= time(NULL);
					struct tm * pTblock = localtime(&timer);
					sprintf(pUser->chLoginTime, "%s", asctime(pTblock));
					
					//��ȡ��չ��Ϣ
					void* pDataBuffer		= NULL;
					tagDataDescribe DataDescribe;
					CRecvPacketHelper RecvPacket(pUserInfoHead+1, wDataSize-sizeof(tagUserInfoHead));
					while (true)
					{
						pDataBuffer=RecvPacket.GetData(DataDescribe);
						if (DataDescribe.wDataDescribe==DTP_NULL)
							break;

						switch (DataDescribe.wDataDescribe)
						{
						case DTP_USER_ACCOUNTS:		//�û��ʻ�
							{
								if (DataDescribe.wDataSize<=sizeof(pUser->szName))
								{
									CopyMemory(&pUser->szName, pDataBuffer, DataDescribe.wDataSize);
									pUser->szName[CountArray(pUser->szName)-1] = 0;
								}
								break;
							}
						}
					}

					// �����Լ���״̬��Ϣ
					if (pUser->dwUserID == m_dwUserID)
					{
						SetStatus(pUser->cbUserStatus);
					}

					// ��ӵ��û�������
					m_pUserManager->Add(pUser);
				}
			}
			break;

		case SUB_GR_USER_STATUS:
			{
				if (wDataSize<sizeof(CMD_GR_UserStatus)) 
					return true;
				//��������
				CMD_GR_UserStatus* pUserStatus  = (CMD_GR_UserStatus *)pBuffer;
				SUser* pUser = m_pUserManager->Search(pUserStatus->dwUserID);
				if (pUser == NULL)
					return true;

				WORD wNowTableID	=	pUserStatus->wTableID;
				BYTE cbNowStatus	=	pUserStatus->cbUserStatus;
				WORD wNowChairID	=	pUserStatus->wChairID;

				WORD wLastTableID	=	pUser->wTableID;			
				BYTE cbLastStatus	=	pUser->cbUserStatus;
				WORD wLastChairID	=	pUser->wChairID;

				if (pUserStatus->cbUserStatus == US_NULL || pUserStatus->cbUserStatus == US_OFFLINE)
				{
					BankerManager::GetSingleton().Remove(pUser->dwUserID);
					// �Ƴ��û�����
					m_pUserManager->Remove(pUserStatus->dwUserID);

					// ������Լ�
					if (pUserStatus->dwUserID == m_dwUserID)
					{
						SetStatus(US_OFFLINE);
					}
				}
				else
				{
					// վ��ʱ��Ӧ��Ǯ
					if (pUserStatus->cbUserStatus == US_FREE && pUserStatus->dwUserID == m_dwUserID)
					{
						BankerManager::GetSingleton().Remove(pUser->dwUserID);
						OnBanker();
						SetStatus(US_FREE);
					}
						
					//����״̬
					pUser->wTableID		= wNowTableID;
					pUser->wChairID		= wNowChairID;
					pUser->cbUserStatus = cbNowStatus;

					if (pUserStatus->cbUserStatus == US_SIT && pUserStatus->dwUserID == m_dwUserID 
						&& wNowTableID != INVALID_TABLE && ((wNowTableID!=wLastTableID) || (wNowChairID!=wLastChairID)))
					{
						// ����Ϊ����״̬
						SetStatus(US_SIT);

						CString szMessage;
						szMessage.Format("[%d]������", m_dwUserID);
						LogEvent(szMessage, 
							TraceLevel_Normal);	
					}
				}
			}
			break;

		case SUB_GR_USER_SCORE:
			{
				if (wDataSize<sizeof(CMD_GR_UserScore)) 
					return 0;

				//��������
				CMD_GR_UserScore* pUserScore = (CMD_GR_UserScore *)pBuffer;
				SUser* pGameUser = m_pUserManager->Search(pUserScore->dwUserID);
				if (pGameUser) 
				{
					pGameUser->nScore = pUserScore->UserScore.lScore;
				}
			}
			break;

		case SUB_GR_SIT_FAILED:
			{
				//��Ϣ����
				CMD_GR_SitFailed* pSitFailed = (CMD_GR_SitFailed *)pBuffer;

				SAppConfig* pConfig = ConfigFile::GetSingleton().GetAppConfig();
				SUser* pGameUser = m_pUserManager->Search(m_dwUserID);
				if (pGameUser->nScore < pConfig->nMinScore) 
				{
					INT64 nMin = pConfig->nMinScore - pGameUser->nScore;
					INT64 nMax = pConfig->nMaxScore - pGameUser->nScore;
					GetScoreFromBanker(AndroidTimer::rdit(nMin, nMax));
				}
				CString szMessage;
				szMessage.Format("[%d] %s, 5�������", m_dwUserID, pSitFailed->szFailedDescribe);
				LogEvent(szMessage, 
					TraceLevel_Normal);
			}
			break;
		}

		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocketMainGameFrame(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		if (wDataSize>SOCKET_PACKET) 
			return true;

		//��������
		IPC_SocketPackage SocketPackage;
		memset(&SocketPackage,0,sizeof(SocketPackage));
		SocketPackage.Command = Command;
		if (wDataSize>0)
		{
			ASSERT(pBuffer!=NULL);
			CopyMemory(SocketPackage.cbBuffer,pBuffer,wDataSize);
		}

		//��������
		WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;

		return OnSocket(IPC_MAIN_SOCKET, IPC_SUB_SOCKET_RECV,
			&SocketPackage, wSendSize);
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
	{
		switch (wSubCmdID)
		{
		case IPC_SUB_SOCKET_RECV:	//���ݽ���
			{
				if (wDataSize<sizeof(CMD_Command)) 
					return false;

				//��ȡ����
				WORD wPacketSize=wDataSize-sizeof(CMD_Command);
				IPC_SocketPackage * pSocketPackage=(IPC_SocketPackage *)pBuffer;

				switch(pSocketPackage->Command.wMainCmdID)
				{
				case MDM_GF_GAME:
					{
						if(wPacketSize == 0)
						{
							return OnGameMessage(pSocketPackage->Command.wSubCmdID);
						}
						else
						{
							return OnGameMessage(pSocketPackage->Command.wSubCmdID,pSocketPackage->cbBuffer,wPacketSize);
						}
					}
				case MDM_GF_FRAME:
					{
						switch(pSocketPackage->Command.wSubCmdID)
						{
						case SUB_GF_OPTION:			//��Ϸ����
							{
								//Ч�����
								if (wPacketSize!=sizeof(CMD_GF_Option)) 
									return 0;

								//��Ϣ����
								CMD_GF_Option* pOption=(CMD_GF_Option *)pSocketPackage->cbBuffer;
								m_bGameStatus = pOption->bGameStatus;

								return true;
							}
						case SUB_GF_SCENE:			//��Ϸ����
							{
								return OnGameSceneMessage(m_bGameStatus,pSocketPackage->cbBuffer,wPacketSize);
							}
						case SUB_GF_LOOKON_CONTROL:	//�Թۿ���
							{
								return true;
							}
						case SUB_GF_USER_CHAT:		//������Ϣ
							{
								return true;
							}

						case SUB_GF_MESSAGE:		//ϵͳ��Ϣ
							{
								return true;
							}
						}
					}
				}
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocketToolBox(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch(Command.wSubCmdID)
		{
		case SUB_TOOLBOX_BANKOPERATING: //���в������
			{
				if (wDataSize<sizeof(CMD_TOOLBOX_BankTask_Ret))
					return 0;

				CMD_TOOLBOX_BankTask_Ret* pBankRet = (CMD_TOOLBOX_BankTask_Ret*)pBuffer;
				if (pBankRet->lErrorCode==0)
				{
					CString szMessage;
					szMessage.Format("[%d]%s��Ǯ %I64d", m_dwUserID, pBankRet->lBankTask == 1 ? "����" : "ȡ��", pBankRet->lMoneyNumber);
					LogEvent(szMessage, TraceLevel_Debug);

					SUser* pUser = GetUserInfo();
					if (pUser)
					{
						switch( pBankRet->lBankTask )
						{
						case 1:
							pUser->nSaveScore += pBankRet->lMoneyNumber;
							break;
						case 2:
							pUser->nGetScore  += pBankRet->lMoneyNumber;
							break;
						}							
					}
				}
				else
				{
					LogEvent(pBankRet->szErrorDescribe, TraceLevel_Exception);
				}
			}
			break;
		case SUB_TOOLBOX_MESSAGE:
			{
				//Ч�����
				CMD_GR_Message * pMessage=(CMD_GR_Message *)pBuffer;
				if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)))
					return true;
				//��Ϣ����
				WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
				if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) 
					return true;
				pMessage->szContent[pMessage->wMessageLength-1]=0;
				LogEvent(pMessage->szContent, TraceLevel_Normal);
			}
			break;
		}

		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
	{
		switch(wMainCmdID)
		{
		case IPC_MAIN_SOCKET:
			{
				return OnMainSocket(wMainCmdID, wSubCmdID, pBuffer, wDataSize);
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnReset()
	{
		m_fSitReqTime	= 0;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSwitchTable()
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnSocketServerInfo(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnBanker()
	{
		return true;
	}

	void			IAndroid::OnUpdateRobotScoreStart()
	{
		if (m_bUpdateRobotScore == true)
			return;
		else
		{
			m_bUpdateRobotScore = true;
			AndroidManager::GetSingleton()->UpdateRobotScore();
		}
	}

	void IAndroid::OnUpdateRobotScoreEnd()
	{
		if (m_bUpdateRobotScore == false)
			return;
		else
			m_bUpdateRobotScore = false;
	}

}
