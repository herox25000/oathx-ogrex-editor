#include "StdAfx.h"
#include ".\irobot.h"

IRobot::IRobot(DWORD dwUserID) : m_dwUserID(dwUserID), m_pAppUser(NULL), m_pGameManager(NULL), m_fReqSitDownTime(0)
{
	m_pGameManager	= new UserManager();

	m_pAppUser		= new SUserInfo();
	m_pAppUser->dwUserID = dwUserID;
	m_bGameStatus	= 0;
	m_wReconnect	= 0;
	m_wState		= ROBOT_CREATE;
}

IRobot::~IRobot(void)
{
	CString szMessage;
	szMessage.Format("delete robot [%d]", m_dwUserID);
	ShowMessageBox(szMessage);

	delete m_pAppUser;
	m_pAppUser = NULL;

	m_pGameManager->ClearUp();
	delete m_pGameManager;
	m_pGameManager = NULL;
}

DWORD			IRobot::GetUserID() const
{
	return m_dwUserID;
}

WORD			IRobot::GetReconnect() const
{
	return m_wReconnect;
}

void			IRobot::SetReqSitDownTime(double fTime)
{
	m_fReqSitDownTime = fTime;
}

double			IRobot::GetReqSitDownTime() const
{
	return m_fReqSitDownTime;
}

SUserInfo*		IRobot::GetUserInfo() const
{
	return m_pAppUser;
}

//������ַ
WORD			IRobot::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
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


//��ȡ����
void		IRobot::GetClientSerial(tagClientSerial & ClientSerial)
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

BOOL			IRobot::Start(const CString& szIPAdress, WORD wPort, const CString& szPwd)
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
		szMessage.Format("robot[%d] connect to server", m_dwUserID);
		CTraceService::TraceString(szMessage,
			TraceLevel_Normal);

		m_szPwd = szPwd;
	}

	return TRUE;
}

void			IRobot::ShowMessageBox(const CString& szMessage, enTraceLevel lev)
{
	CTraceService::TraceString(szMessage, lev);
}

void			IRobot::OnUpdate(float fElapsed)
{
	
}

void			IRobot::SitDown()
{
	//�������ݰ�
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID	=	0;
	UserSitReq.wChairID	=	rand() % 50;

	//�������ݰ�
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	m_wReconnect ++;
	CString szMessage;
	szMessage.Format("robot[%d] sit down request count %d ", m_dwUserID, m_wReconnect);
	CTraceService::TraceString(szMessage,
		TraceLevel_Normal);

	//��ȡ����
	CMD_GF_Info Info;
	ZeroMemory(&Info,sizeof(Info));
	Info.bAllowLookon=true;

	//������Ϣ
	m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO,&Info,sizeof(Info));
}

void			IRobot::AddGameUser(SUserInfo* pUserInfo)
{
	if (m_pGameManager)
	{
		m_pGameManager->AddUser(pUserInfo);
	}
}

void			IRobot::SetUserStatus(DWORD dwUserID, BYTE cbUserStatus)
{
	tagUserInfo *pUserInfo = m_pGameManager->Search(dwUserID);
	if(pUserInfo)
	{
		pUserInfo->cbUserStatus = cbUserStatus;
	}
}

void			IRobot::ResetGame()
{
	
}

WORD			IRobot::GetState() const
{
	return m_wState;
}

void			IRobot::SetState(WORD wState)
{
	m_wState = wState;
}

WORD			IRobot::GetSocketState()
{
	return m_ClientSocket->GetSocketStatus();
}

void			IRobot::BankSaveScore(INT64 nScore)
{
	CMD_TOOLBOX_BankTask BankTask;
	memset(&BankTask, 0, sizeof(CMD_TOOLBOX_BankTask));
	BankTask.lMoneyNumber	= nScore;
	BankTask.lBankTask		= 1;
	CopyMemory(BankTask.szPassword,m_szPwd.GetBuffer(),sizeof(BankTask.szPassword));
	m_ClientSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &BankTask, sizeof(BankTask));
}

void			IRobot::BankGetScore(INT64 nScore)
{
	CMD_TOOLBOX_BankTask BankTask;
	memset(&BankTask, 0, sizeof(CMD_TOOLBOX_BankTask));
	BankTask.lMoneyNumber	= nScore;
	BankTask.lBankTask		= 2;
	CopyMemory(BankTask.szPassword,m_szPwd.GetBuffer(),sizeof(BankTask.szPassword));
	m_ClientSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &BankTask, sizeof(BankTask));
}

void			IRobot::Stop()
{
	if (m_ClientSocket.GetInterface() != NULL) 
	{
		if(m_pAppUser->cbUserStatus == US_PLAY)
		{
			m_ClientSocket->SendData(MDM_GR_USER, SUB_GR_USER_LEFT_GAME_REQ);
		}

		m_ClientSocket->SendData(MDM_GR_USER, 
			SUB_GR_USER_STANDUP_REQ);

		m_ClientSocket->CloseSocket();
	}
}

bool __cdecl	IRobot::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	CString szError;

	if ( nErrorCode != 0)
	{
		szError.Format("Connect room failed, error coid  %d",nErrorCode);
		ShowMessageBox(szError);

		return 0;
	}
	

	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKET];
	
	//��¼���ݰ�
	CMD_GR_LogonByUserID* pLogonByUserID = (CMD_GR_LogonByUserID *)cbBuffer;

	pLogonByUserID->dwUserID		= m_dwUserID;
	pLogonByUserID->dwPlazaVersion	= VER_PLAZA_FRAME;
	lstrcpyn(pLogonByUserID->szPassWord, m_szPwd, sizeof(pLogonByUserID->szPassWord));

	//�������к�
	tagClientSerial ClientSerial;
	GetClientSerial(ClientSerial);

	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

	szError.Format("Robot[%i], Start connect to game", (int)m_dwUserID);
	ShowMessageBox(szError);

	return true;
}

bool __cdecl	IRobot::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			ShowMessageBox("Net Error, Is disconnected");
		}
		else
		{
			ShowMessageBox("Data packet proc error");
		}
	}
	else
	{
		ShowMessageBox("Is disconnected");
	}

	SetState(ROBOT_INVALID);

	return true;
}

bool __cdecl	IRobot::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID* pBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
		{
			return OnSocketMainLogon(Command, pBuffer,wDataSize);
		}
	case MDM_GR_USER:			//�û���Ϣ
		{
			return OnSocketMainUser(Command, pBuffer, wDataSize);
		}
	case MDM_GR_INFO:			//������Ϣ
		{
			return true;
		}
	case MDM_GR_STATUS:			//״̬��Ϣ
		{
			return true;
		}
	case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
		{
			return true;
		}
	case MDM_GR_SERVER_INFO:	//������Ϣ
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

bool			IRobot::OnSocketMainLogon(CMD_Command Command, void* pBuffer, WORD wDataSize)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:
		{
			CString szMessage;
			szMessage.Format("Robot[%i], Check In Game", (int)m_dwUserID);
			ShowMessageBox(szMessage);

			SitDown();
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
				ShowMessageBox(pLogonError->szErrorDescribe);
			}

			SetState(ROBOT_INVALID);
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
			m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_RULE,&UserRule,sizeof(UserRule));
		}
		break;
	}

	return true;
}

bool			IRobot::OnSocketMainUser(CMD_Command Command, void* pBuffer, WORD wDataSize)
{
	switch(Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:
		{
			if (wDataSize<sizeof(tagUserInfoHead)) 
				return 0;

			//��ȡ������Ϣ
			tagUserInfoHead* pUserInfoHead = (tagUserInfoHead *)(pBuffer);

			SUserInfo* pUserInfo = m_pGameManager->Search(pUserInfoHead->dwUserID);
			if (pUserInfo)
			{
				pUserInfo->lScore = pUserInfoHead->UserScoreInfo.lScore;
			}
			else
			{
				pUserInfo = new SUserInfo();
				pUserInfo->dwUserID		= pUserInfoHead->dwUserID;
				pUserInfo->lScore		= pUserInfoHead->UserScoreInfo.lScore;
				pUserInfo->wTableID		= pUserInfoHead->wTableID;
				pUserInfo->wChairID		= pUserInfoHead->wChairID;
				pUserInfo->cbUserStatus	= pUserInfoHead->cbUserStatus;
				pUserInfo->dwGameID		= pUserInfoHead->dwGameID;

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
							if (DataDescribe.wDataSize<=sizeof(pUserInfo->szName))
							{
								CopyMemory(&pUserInfo->szName, pDataBuffer, DataDescribe.wDataSize);
								pUserInfo->szName[CountArray(pUserInfo->szName)-1] = 0;
							}
							break;
						}
					}
				}
				
				// �����Լ�����Ϣ
				if (m_dwUserID == pUserInfo->dwUserID)
				{
					memcpy(m_pAppUser, pUserInfo, sizeof(SUserInfo));
				}
				
				// ��ӵ��û�������
				AddGameUser(pUserInfo);
			}
		}
		break;

	case SUB_GR_USER_STATUS:
		{
			if (wDataSize<sizeof(CMD_GR_UserStatus)) 
				return 0;
			//��������
			CMD_GR_UserStatus* pUserStatus  = (CMD_GR_UserStatus *)pBuffer;
			tagUserInfo* pUserInfo			= m_pGameManager->Search(pUserStatus->dwUserID);
			if (pUserInfo == NULL)
				return true;

			WORD wNowTableID	=	pUserStatus->wTableID;
			BYTE cbNowStatus	=	pUserStatus->cbUserStatus;
			WORD wNowChairID	=	pUserStatus->wChairID;

			WORD wLastTableID	=	pUserInfo->wTableID;			
			BYTE cbLastStatus	=	pUserInfo->cbUserStatus;
			WORD wLastChairID	=	pUserInfo->wChairID;
			
			if (pUserStatus->cbUserStatus == US_NULL || pUserStatus->cbUserStatus == US_OFFLINE)
			{
				// �Ƴ��û�����
				m_pGameManager->Remove(pUserStatus->dwUserID);

				if (pUserStatus->dwUserID == m_dwUserID)
				{
					SetState(ROBOT_INVALID);
				}
			}
			else
			{
				//����״̬
				pUserInfo->wTableID		= wNowTableID;
				pUserInfo->wChairID		= wNowChairID;
				pUserInfo->cbUserStatus = cbNowStatus;

				if (pUserStatus->cbUserStatus == US_SIT && pUserStatus->dwUserID == m_dwUserID 
					&& wNowTableID != INVALID_TABLE && ((wNowTableID!=wLastTableID) || (wNowChairID!=wLastChairID)))
				{
					// ���µ�ǰ������Ϣ
					memcpy(m_pAppUser, 
						pUserInfo, sizeof(SUserInfo));

					// ����Ϊ����״̬
					SetState(ROBOT_SITDOWN);

					CString szMessage;
					szMessage.Format("Robot[%i], sit down ok", 
						(int)m_dwUserID);

					ShowMessageBox(szMessage);	
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
			tagUserInfo* pGameUser		 = m_pGameManager->Search(pUserScore->dwUserID);
			if (pGameUser) 
			{
				if (pUserScore->dwUserID == m_dwUserID)
				{
					m_pAppUser->lScore = pUserScore->UserScore.lScore;
				}

				pGameUser->lScore = pUserScore->UserScore.lScore;
			}
		}
		break;

	case SUB_GR_SIT_FAILED:
		{
			//��Ϣ����
			CMD_GR_SitFailed* pSitFailed = (CMD_GR_SitFailed *)pBuffer;

			CString szMessage;
			szMessage.Format("[%i] %s, 5 ms Reconnect", (int)m_dwUserID, pSitFailed->szFailedDescribe);
			ShowMessageBox(szMessage);
		}
		break;
	}

	return true;
}

bool			IRobot::OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
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

bool			IRobot::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	if(pData)
	{
		return m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	}
	else
	{
		return m_ClientSocket->SendData(wMainCmdID, wSubCmdID);
	}

	return true;
}

bool			IRobot::OnSocketMainGameFrame(CMD_Command Command, void* pBuffer, WORD wDataSize)
{
	if (wDataSize>SOCKET_PACKET) 
		return 0;

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

bool			IRobot::OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case IPC_SUB_SOCKET_RECV:	//���ݽ���
		{
			if (wDataSize<sizeof(CMD_Command)) return false;

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
							if (wPacketSize!=sizeof(CMD_GF_Option)) return false;

							//��Ϣ����
							CMD_GF_Option * pOption=(CMD_GF_Option *)pSocketPackage->cbBuffer;
							m_bGameStatus=pOption->bGameStatus;

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

	return 0;
}

bool			IRobot::OnSocketToolBox(CMD_Command Command, void* pBuffer, WORD wDataSize)
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
				szMessage.Format("������Ǯ %I64d", pBankRet->lMoneyNumber);
				ShowMessageBox(szMessage, TraceLevel_Debug);

				MessageBox(NULL, "�����ɹ���", NULL, NULL);
			}
			else
			{
				MessageBox(NULL, pBankRet->szErrorDescribe, NULL, NULL);
			}
		}
		break;
	case SUB_TOOLBOX_MESSAGE:
		{
			//Ч�����
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pBuffer;
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)))
				return 0;
			//��Ϣ����
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) 
				return 0;
			pMessage->szContent[pMessage->wMessageLength-1]=0;
			MessageBox(NULL, pMessage->szContent, NULL, NULL);
		}
		break;
	}

	return true;
}

bool			IRobot::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
{
	return true;
}

bool			IRobot::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	return true;
}