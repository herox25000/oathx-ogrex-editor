#include "StdAfx.h"
#include ".\gamebase.h"

CGameBase::CGameBase(DWORD dwUserID)
{
	m_MeUserInfo.dwUserID = dwUserID;
	m_bGameStatus = false;
	m_pTimerEngine = NULL;
	m_bPlaying = false;
	m_bSitOk = false;
	//m_pIEventService = NULL;
	m_bSmall = false;

	time_t seed = time(NULL);
	srand((unsigned)seed);
}

CGameBase::~CGameBase(void)
{
}
//������ַ
WORD CGameBase::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
{
	//��������
	WORD wMacSize=0;
	HINSTANCE hInstance=NULL;
	typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

	try
	{
		//���� DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) throw TEXT("���� NetApi32.dll ʧ��");

		//��ȡ����
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) throw TEXT("�޷��ҵ� NetBios ����");

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
		if (LanaEnum.length==0) throw TEXT("�Ҳ����κ�����");

		//��ȡ��ַ
		tagAstatInfo Adapter;
		for (BYTE i=0;i<LanaEnum.length;i++)
		{
			//��������
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("��������ʧ��");

			//��ȡ״̬
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("��ȡ����״̬ʧ��");

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
void CGameBase::GetClientSerial(tagClientSerial & ClientSerial)
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


////�����¼�
//bool CGameBase::SetEventService(IUnknownEx * pIUnknownEx)
//{
//	//ASSERT(pIUnknownEx!=NULL);
//	//m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
//	//ASSERT(m_pIEventService!=NULL);
//	//return (m_pIEventService!=NULL);
//}

void * __cdecl CGameBase::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

bool CGameBase::BeginServer(CString strIP, WORD wPort, CString strPsw)
{
	//�������
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false)
		return false;
	if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false)
		return false;

	m_ClientSocket->Connect(strIP, wPort);
	m_strPsw = strPsw;

	return true;
}

void CGameBase::EndServer()
{
	if (m_ClientSocket.GetInterface()!=NULL) 
	{
		if(m_MeUserInfo.cbUserStatus == US_PLAY)
		{
			m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);
		}
		m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);
		m_ClientSocket->CloseSocket();
	}
}

//���ö�ʱ��
bool CGameBase::SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat)
{
	if(m_pTimerEngine)
	{
		return m_pTimerEngine->SetTimer(this, wTimerID, dwElapse, dwRepeat);
	}
	return false;
}

//ɾ����ʱ��
bool CGameBase::KillTimer(WORD wTimerID)
{
	if(m_pTimerEngine)
	{
		return m_pTimerEngine->KillTimer(this, wTimerID);
	}
	return false;
}

//ɾ����ʱ��
bool CGameBase::KillAllTimer()
{
	if(m_pTimerEngine)
	{
		return m_pTimerEngine->KillAllTimer();
	}
	return false;
}

int CGameBase::ShowMessageBox(CString strMsg)
{
	CTraceService::TraceString(strMsg,TraceLevel_Normal);
	return 0;//MessageBox(NULL, strMsg, "�����˹�����", MB_OK);
}

void CGameBase::SendChatMessage(CString strMsg)
{
	CMD_GF_UserChat UserChat;
	UserChat.crFontColor=0;
	UserChat.dwTargetUserID=0L;
	UserChat.dwSendUserID= m_MeUserInfo.dwUserID;
	lstrcpyn(UserChat.szChatMessage,strMsg,CountArray(UserChat.szChatMessage));
	UserChat.wChatLength=CountStringBuffer(UserChat.szChatMessage);

	//��������
	WORD wSendSize=sizeof(UserChat)-sizeof(UserChat.szChatMessage)+UserChat.wChatLength;
	m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_USER_CHAT,&UserChat,wSendSize);
}

//����������Ϣ
bool __cdecl CGameBase::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if (nErrorCode!=0)
	{
		CString str;
		str.Format("���ӷ���ʧ�ܣ�����ID%d",nErrorCode);
		ShowMessageBox(str);
		return false;
	}

	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKET];
	//��¼���ݰ�
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=m_MeUserInfo.dwUserID;
	pLogonByUserID->dwPlazaVersion=VER_PLAZA_FRAME;
	lstrcpyn(pLogonByUserID->szPassWord,m_strPsw,sizeof(pLogonByUserID->szPassWord));

	//�������к�
	tagClientSerial ClientSerial;
	GetClientSerial(ClientSerial);

	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());



	CString strMsg;
	strMsg.Format("�������û�(UserID)[%i], ��ʼ���ӵ���Ϸ��", (int)m_MeUserInfo.dwUserID);
	ShowMessageBox(strMsg);

	return true;
}

//�����ȡ��Ϣ
bool __cdecl CGameBase::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
		{
			return OnSocketMainLogon(Command,pBuffer,wDataSize);
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
	}

	return true;
}

//����ر���Ϣ
//�ر��¼�
bool __cdecl CGameBase::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	ShowMessageBox("�������ӶϿڣ�������������������");
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			ShowMessageBox("�����������⣬���Ѿ���������Ͽ����ӣ�����������");
		}
		else
		{
			ShowMessageBox("�����������ݰ�����ʧ�ܣ������ж���");
		}
	}
	return true;
}

bool CGameBase::SitDown()
{
	//�������ݰ�
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=0;
	UserSitReq.wChairID=rand()%50;

	//�������ݰ�
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	//��ȡ����
	CMD_GF_Info Info;
	ZeroMemory(&Info,sizeof(Info));
	Info.bAllowLookon=true;

	//������Ϣ
	m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO,&Info,sizeof(Info));
	return true;
}

bool CGameBase::OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:
		{
			CString strMsg;
			strMsg.Format("�������û�(UserID)[%i], �ɹ����ӵ���Ϸ��׼��������Ϸ���ӣ�", (int)m_MeUserInfo.dwUserID);
			ShowMessageBox(strMsg);

			this->SitDown();
			return true;
		}
	case SUB_GR_LOGON_ERROR:
		{
			//Ч�����
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			m_ClientSocket->CloseSocket();

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe);
			}

			return true;
		}
	case SUB_GR_LOGON_FINISH:		//��¼���
		{
			//�������ݰ�
			CMD_GR_UserRule UserRule;
			memset(&UserRule, 0, sizeof(CMD_GR_UserRule));
			UserRule.bLimitWin=false;
			UserRule.bLimitFlee=false;
			UserRule.wWinRate=0;
			UserRule.wFleeRate=0;
			UserRule.lMaxScore=0;
			UserRule.lLessScore	=0;
			UserRule.bLimitScore=false;
			UserRule.bPassword=false;
			UserRule.bCheckSameIP=false;

			//�������ݰ�
			m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_RULE,&UserRule,sizeof(UserRule));

			return true;
		}
	}

	return true;
}

void CGameBase::InsertTableUser(tagUserInfo *pUserInfo)
{
	tagUserInfo *pGameUserInfo = new tagUserInfo;
	memcpy(pGameUserInfo, pUserInfo, sizeof(tagUserInfo));

	m_GameUserManager.InsertInfo(pGameUserInfo);
}

bool CGameBase::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch(Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:
		{
			ASSERT(wDataSize>=sizeof(tagUserInfoHead));
			if (wDataSize<sizeof(tagUserInfoHead)) return false;
	
			//��ȡ������Ϣ
			tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pBuffer;
			tagUserInfo *pUserInfo = NULL;
			if(m_RoomUserManager.SearchUserByUserID(pUserInfoHead->dwUserID))
			{
				m_RoomUserManager.UpdateInfo(pUserInfoHead->dwUserID, pUserInfoHead->UserScoreInfo.lScore);
			}
			else
			{
				pUserInfo = new tagUserInfo;
				pUserInfo->dwUserID = pUserInfoHead->dwUserID;
				pUserInfo->lScore = pUserInfoHead->UserScoreInfo.lScore;
				pUserInfo->wTableID = pUserInfoHead->wTableID;
				pUserInfo->wChairID = pUserInfoHead->wChairID;
				pUserInfo->cbUserStatus = pUserInfoHead->cbUserStatus;
				//fixed me
				//�ж��Ƿ��ǻ�����
				pUserInfo->bIsRobot = FALSE;

				//��ȡ��չ��Ϣ
				void * pDataBuffer=NULL;
				tagDataDescribe DataDescribe;
				CRecvPacketHelper RecvPacket(pUserInfoHead+1,wDataSize-sizeof(tagUserInfoHead));
				while (true)
				{
					pDataBuffer=RecvPacket.GetData(DataDescribe);
					if (DataDescribe.wDataDescribe==DTP_NULL) break;
					switch (DataDescribe.wDataDescribe)
					{
					case DTP_USER_ACCOUNTS:		//�û��ʻ�
						{
							ASSERT(pDataBuffer!=NULL);
							ASSERT(DataDescribe.wDataSize<=sizeof(pUserInfo->szName));
							if (DataDescribe.wDataSize<=sizeof(pUserInfo->szName))
							{
								CopyMemory(&pUserInfo->szName,pDataBuffer,DataDescribe.wDataSize);
								pUserInfo->szName[CountArray(pUserInfo->szName)-1]=0;
							}
							break;
						}
					}
				}
				m_RoomUserManager.InsertInfo(pUserInfo);
			}

			if(pUserInfo && pUserInfoHead->dwUserID == m_MeUserInfo.dwUserID)
			{
				m_MeUserInfo = *pUserInfo;
			}
			break;
		}
	case SUB_GR_USER_STATUS:
		{
			ASSERT(wDataSize>=sizeof(CMD_GR_UserStatus));
			if (wDataSize<sizeof(CMD_GR_UserStatus)) return false;
			
			//��������
			CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pBuffer;
			tagUserInfo * pUserInfo=m_RoomUserManager.SearchUserByUserID(pUserStatus->dwUserID);
			//ASSERT(pUserInfo!=NULL);
			if (pUserInfo==NULL) return true;

			WORD wNowTableID=pUserStatus->wTableID,wLastTableID=pUserInfo->wTableID;
			WORD wNowChairID=pUserStatus->wChairID,wLastChairID=pUserInfo->wChairID;
			BYTE cbNowStatus=pUserStatus->cbUserStatus,cbLastStatus=pUserInfo->cbUserStatus;

			//�û��뿪
			if (pUserStatus->cbUserStatus==US_NULL) 
			{
				if(m_MeUserInfo.wTableID != INVALID_TABLE && m_MeUserInfo.wTableID == wLastTableID)
				{
					OnUserStatus(pUserInfo->dwUserID, pUserInfo->cbUserStatus);
				}
				m_RoomUserManager.RemoveInfo(pUserStatus->dwUserID);

				if(pUserStatus->dwUserID == m_MeUserInfo.dwUserID)
				{
					CString strMsg;
					strMsg.Format("%i �뿪��Ϸ��", 
						(int)m_MeUserInfo.dwUserID);
					ShowMessageBox(strMsg);
				}
				break;
			}

			//����״̬
			pUserInfo->wTableID = wNowTableID;
			pUserInfo->wChairID = wNowChairID;
			pUserInfo->cbUserStatus = cbNowStatus;

			//������״̬
			if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
			{
				//�����û�
				if ((pUserInfo->dwUserID != m_MeUserInfo.dwUserID)&&(m_MeUserInfo.wTableID==wNowTableID))
				{
					this->InsertTableUser(pUserInfo);
				}
			}

			//�жϷ���
			bool bNotifyGame=false;
			if (pUserInfo->dwUserID == m_MeUserInfo.dwUserID) bNotifyGame=true;
			else if ((m_MeUserInfo.wTableID!=INVALID_TABLE)&&(m_MeUserInfo.wTableID==wNowTableID)) bNotifyGame=true;
			else if ((m_MeUserInfo.wTableID!=INVALID_TABLE)&&(m_MeUserInfo.wTableID==wLastTableID)) bNotifyGame=true;

			//����״̬
			if (bNotifyGame==true)
			{
				OnUserStatus(pUserInfo->dwUserID, pUserInfo->cbUserStatus);
			}

			if(pUserStatus->dwUserID == m_MeUserInfo.dwUserID)
			{
 				m_MeUserInfo = *pUserInfo;
				//������Ϸ
				if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
				{
					InsertTableUser(&m_MeUserInfo);
					for(UserVec::size_type st = 0; st<m_RoomUserManager.GetSize();++st)
					{
						tagUserInfo *pUserInfo = m_RoomUserManager.GetIndex(st);
						if((pUserInfo->dwUserID != m_MeUserInfo.dwUserID)&&
							pUserInfo->wTableID == m_MeUserInfo.wTableID)
						{
							InsertTableUser(pUserInfo);
						}
					}

					CString strMsg;
					strMsg.Format("�������û�(UserID)[%i], ������Ϸ���ӳɹ�����ʼ������Ϸ������", 
						(int)m_MeUserInfo.dwUserID);
					ShowMessageBox(strMsg);

					m_bSitOk = true;
				}
			}
			break;
		}
	case SUB_GR_USER_SCORE:
		{
			ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
			if (wDataSize<sizeof(CMD_GR_UserScore)) return false;

			//��������
			CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pBuffer;
			tagUserInfo * pUserInfo=m_RoomUserManager.SearchUserByUserID(pUserScore->dwUserID);
			//ASSERT(pUserInfo!=NULL);
			if (pUserInfo==NULL) return true;
			
			m_RoomUserManager.UpdateInfo(pUserScore->dwUserID, pUserScore->UserScore.lScore);
			m_GameUserManager.UpdateInfo(pUserScore->dwUserID, pUserScore->UserScore.lScore);
			break;
		}
	case SUB_GR_SIT_FAILED:
		{
			//��Ϣ����
 			CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pBuffer;
 
			CString strMsg;
			strMsg.Format("%i ������Ϸ����ʧ�ܣ�%s, 5����Զ����ԣ�", (int)m_MeUserInfo.dwUserID, pSitFailed->szFailedDescribe);
			ShowMessageBox(strMsg);
			break;
		}
	}

	return true;
}

bool CGameBase::OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize<=SOCKET_PACKET);
	if (wDataSize>SOCKET_PACKET) return false;

	//��������
	IPC_SocketPackage SocketPackage;
	memset(&SocketPackage,0,sizeof(SocketPackage));
	SocketPackage.Command=Command;
	if (wDataSize>0)
	{
		ASSERT(pBuffer!=NULL);
		CopyMemory(SocketPackage.cbBuffer,pBuffer,wDataSize);
	}

	//��������
	WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;
	return this->OnSocket(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize);

	return true;
}


bool CGameBase::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData/* =NULL */, WORD wDataSize/* =0 */)
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

bool CGameBase::OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
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

void CGameBase::OnUserStatus(DWORD dwUserID, BYTE cbUserStatus)
{
	if (cbUserStatus<US_SIT)
	{
		if (dwUserID==m_MeUserInfo.dwUserID)
		{
			m_GameUserManager.RemoveAll();
			this->ResetGame();
			return;
		}
		else m_GameUserManager.RemoveInfo(dwUserID);
	}
	else
	{
 		tagUserInfo *pUserInfo = m_GameUserManager.SearchUserByUserID(dwUserID);
		if(pUserInfo)
		{
			pUserInfo->cbUserStatus = cbUserStatus;
		}
	}
}

bool CGameBase::OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	ASSERT(wMainCmdID==IPC_MAIN_SOCKET);
	switch (wSubCmdID)
	{
	case IPC_SUB_SOCKET_RECV:	//���ݽ���
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_Command));
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
							ASSERT(wPacketSize==sizeof(CMD_GF_Option));
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
					//case SUB_GF_BANK:
					//	{
					//		return true;
					//	}
					case SUB_GF_USER_CHAT:		//������Ϣ
						{
							return true;
						}
					//case SUB_GF_INTEREST:
					//	{
					//		return true;
					//	}
					case SUB_GF_MESSAGE:		//ϵͳ��Ϣ
						{
							return true;
						}
					//case SUB_GF_LOTTERY:
					//	{
					//		return true;
					//	}
					}
				}
			}
		}
	}
	return false;
}
