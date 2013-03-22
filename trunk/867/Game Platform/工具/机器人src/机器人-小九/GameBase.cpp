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
//网卡地址
WORD CGameBase::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
{
	//变量定义
	WORD wMacSize=0;
	HINSTANCE hInstance=NULL;
	typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

	try
	{
		//加载 DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) throw TEXT("加载 NetApi32.dll 失败");

		//获取函数
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) throw TEXT("无法找到 NetBios 函数");

		//变量定义
		NCB Ncb;
		LANA_ENUM LanaEnum;
		ZeroMemory(&Ncb,sizeof(Ncb));
		ZeroMemory(&LanaEnum,sizeof(LanaEnum));

		//枚举网卡
		Ncb.ncb_command=NCBENUM;
		Ncb.ncb_length=sizeof(LanaEnum);
		Ncb.ncb_buffer=(BYTE *)&LanaEnum;
		if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("枚举网卡失败");
		if (LanaEnum.length==0) throw TEXT("找不到任何网卡");

		//获取地址
		tagAstatInfo Adapter;
		for (BYTE i=0;i<LanaEnum.length;i++)
		{
			//重置网卡
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("重置网卡失败");

			//获取状态
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("获取网卡状态失败");

			//获取地址
			if (wMacSize<wBufferSize)
			{
				//拷贝地址
				WORD wCopySize=__min((wBufferSize-wMacSize),sizeof(BYTE)*6);
				CopyMemory(cbMacBuffer,Adapter.AdapterStatus.adapter_address,wCopySize);

				//完成判断
				wMacSize+=wCopySize;
				if (wMacSize==wBufferSize) break;
			}
		}

		//释放资源
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}

		return wMacSize;
	}
	catch (...) 
	{ 
		//释放资源
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}
	}

	return wMacSize;
}


//获取序列
void CGameBase::GetClientSerial(tagClientSerial & ClientSerial)
{
	//获取版本
	OSVERSIONINFO OSVerInfo;
	OSVerInfo.dwOSVersionInfoSize=sizeof(OSVerInfo);
	GetVersionEx(&OSVerInfo);
	ClientSerial.dwSystemVer=MAKELONG(OSVerInfo.dwMajorVersion,OSVerInfo.dwMinorVersion);

	//网卡标识
	ZeroMemory(ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));
	WORD wMacSize=GetMACAddress((BYTE *)ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));

	//硬盘标识
	WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
	LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
	for (WORD i=wIndex;i<CountArray(ClientSerial.dwComputerID);i++)
	{
		ASSERT(CountArray(pszHardDisk)>(i-wIndex));
		GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,&ClientSerial.dwComputerID[i],NULL,NULL,0,NULL);
	}

	return;
}


////设置事件
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
	//设置组件
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

//设置定时器
bool CGameBase::SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat)
{
	if(m_pTimerEngine)
	{
		return m_pTimerEngine->SetTimer(this, wTimerID, dwElapse, dwRepeat);
	}
	return false;
}

//删除定时器
bool CGameBase::KillTimer(WORD wTimerID)
{
	if(m_pTimerEngine)
	{
		return m_pTimerEngine->KillTimer(this, wTimerID);
	}
	return false;
}

//删除定时器
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
	return 0;//MessageBox(NULL, strMsg, "机器人管理器", MB_OK);
}

void CGameBase::SendChatMessage(CString strMsg)
{
	CMD_GF_UserChat UserChat;
	UserChat.crFontColor=0;
	UserChat.dwTargetUserID=0L;
	UserChat.dwSendUserID= m_MeUserInfo.dwUserID;
	lstrcpyn(UserChat.szChatMessage,strMsg,CountArray(UserChat.szChatMessage));
	UserChat.wChatLength=CountStringBuffer(UserChat.szChatMessage);

	//发送命令
	WORD wSendSize=sizeof(UserChat)-sizeof(UserChat.szChatMessage)+UserChat.wChatLength;
	m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_USER_CHAT,&UserChat,wSendSize);
}

//网络连接消息
bool __cdecl CGameBase::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0)
	{
		CString str;
		str.Format("连接房间失败，错误ID%d",nErrorCode);
		ShowMessageBox(str);
		return false;
	}

	//获取信息
	BYTE cbBuffer[SOCKET_PACKET];
	//登录数据包
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=m_MeUserInfo.dwUserID;
	pLogonByUserID->dwPlazaVersion=VER_PLAZA_FRAME;
	lstrcpyn(pLogonByUserID->szPassWord,m_strPsw,sizeof(pLogonByUserID->szPassWord));

	//机器序列号
	tagClientSerial ClientSerial;
	GetClientSerial(ClientSerial);

	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());



	CString strMsg;
	strMsg.Format("机器人用户(UserID)[%i], 开始连接到游戏！", (int)m_MeUserInfo.dwUserID);
	ShowMessageBox(strMsg);

	return true;
}

//网络读取消息
bool __cdecl CGameBase::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//登录消息
		{
			return OnSocketMainLogon(Command,pBuffer,wDataSize);
		}
	case MDM_GR_USER:			//用户消息
		{
			return OnSocketMainUser(Command, pBuffer, wDataSize);
		}
	case MDM_GR_INFO:			//配置信息
		{
			return true;
		}
	case MDM_GR_STATUS:			//状态信息
		{
			return true;
		}
	case MDM_GR_SYSTEM:			//系统消息
		{
			return true;
		}
	case MDM_GR_SERVER_INFO:	//房间信息
		{
			return true;
		}
	case MDM_GF_GAME:			//游戏消息
	case MDM_GF_FRAME:			//框架消息
		{
			return OnSocketMainGameFrame(Command,pBuffer,wDataSize);
		}
	}

	return true;
}

//网络关闭消息
//关闭事件
bool __cdecl CGameBase::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	ShowMessageBox("网络连接断口！！！！！！！！！！");
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			ShowMessageBox("由于网络问题，您已经与服务器断开连接，请重新连接");
		}
		else
		{
			ShowMessageBox("由于网络数据包处理失败，网络中断了");
		}
	}
	return true;
}

bool CGameBase::SitDown()
{
	//构造数据包
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=0;
	UserSitReq.wChairID=rand()%50;

	//发送数据包
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	//获取场景
	CMD_GF_Info Info;
	ZeroMemory(&Info,sizeof(Info));
	Info.bAllowLookon=true;

	//发送消息
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
			strMsg.Format("机器人用户(UserID)[%i], 成功连接到游戏，准备进入游戏桌子！", (int)m_MeUserInfo.dwUserID);
			ShowMessageBox(strMsg);

			this->SitDown();
			return true;
		}
	case SUB_GR_LOGON_ERROR:
		{
			//效验参数
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//关闭连接
			m_ClientSocket->CloseSocket();

			//显示消息
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe);
			}

			return true;
		}
	case SUB_GR_LOGON_FINISH:		//登录完成
		{
			//构造数据包
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

			//发送数据包
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
	
			//读取基本信息
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
				//判断是否是机器人
				pUserInfo->bIsRobot = FALSE;

				//读取扩展信息
				void * pDataBuffer=NULL;
				tagDataDescribe DataDescribe;
				CRecvPacketHelper RecvPacket(pUserInfoHead+1,wDataSize-sizeof(tagUserInfoHead));
				while (true)
				{
					pDataBuffer=RecvPacket.GetData(DataDescribe);
					if (DataDescribe.wDataDescribe==DTP_NULL) break;
					switch (DataDescribe.wDataDescribe)
					{
					case DTP_USER_ACCOUNTS:		//用户帐户
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
			
			//处理数据
			CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pBuffer;
			tagUserInfo * pUserInfo=m_RoomUserManager.SearchUserByUserID(pUserStatus->dwUserID);
			//ASSERT(pUserInfo!=NULL);
			if (pUserInfo==NULL) return true;

			WORD wNowTableID=pUserStatus->wTableID,wLastTableID=pUserInfo->wTableID;
			WORD wNowChairID=pUserStatus->wChairID,wLastChairID=pUserInfo->wChairID;
			BYTE cbNowStatus=pUserStatus->cbUserStatus,cbLastStatus=pUserInfo->cbUserStatus;

			//用户离开
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
					strMsg.Format("%i 离开游戏！", 
						(int)m_MeUserInfo.dwUserID);
					ShowMessageBox(strMsg);
				}
				break;
			}

			//更新状态
			pUserInfo->wTableID = wNowTableID;
			pUserInfo->wChairID = wNowChairID;
			pUserInfo->cbUserStatus = cbNowStatus;

			//设置新状态
			if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
			{
				//发送用户
				if ((pUserInfo->dwUserID != m_MeUserInfo.dwUserID)&&(m_MeUserInfo.wTableID==wNowTableID))
				{
					this->InsertTableUser(pUserInfo);
				}
			}

			//判断发送
			bool bNotifyGame=false;
			if (pUserInfo->dwUserID == m_MeUserInfo.dwUserID) bNotifyGame=true;
			else if ((m_MeUserInfo.wTableID!=INVALID_TABLE)&&(m_MeUserInfo.wTableID==wNowTableID)) bNotifyGame=true;
			else if ((m_MeUserInfo.wTableID!=INVALID_TABLE)&&(m_MeUserInfo.wTableID==wLastTableID)) bNotifyGame=true;

			//发送状态
			if (bNotifyGame==true)
			{
				OnUserStatus(pUserInfo->dwUserID, pUserInfo->cbUserStatus);
			}

			if(pUserStatus->dwUserID == m_MeUserInfo.dwUserID)
			{
 				m_MeUserInfo = *pUserInfo;
				//启动游戏
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
					strMsg.Format("机器人用户(UserID)[%i], 进入游戏桌子成功！开始进行游戏操作！", 
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

			//处理数据
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
			//消息处理
 			CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pBuffer;
 
			CString strMsg;
			strMsg.Format("%i 进入游戏桌子失败：%s, 5秒后自动重试！", (int)m_MeUserInfo.dwUserID, pSitFailed->szFailedDescribe);
			ShowMessageBox(strMsg);
			break;
		}
	}

	return true;
}

bool CGameBase::OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//效验数据
	ASSERT(wDataSize<=SOCKET_PACKET);
	if (wDataSize>SOCKET_PACKET) return false;

	//构造数据
	IPC_SocketPackage SocketPackage;
	memset(&SocketPackage,0,sizeof(SocketPackage));
	SocketPackage.Command=Command;
	if (wDataSize>0)
	{
		ASSERT(pBuffer!=NULL);
		CopyMemory(SocketPackage.cbBuffer,pBuffer,wDataSize);
	}

	//发送数据
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
	case IPC_SUB_SOCKET_RECV:	//数据接收
		{
			//效验数据
			ASSERT(wDataSize>=sizeof(CMD_Command));
			if (wDataSize<sizeof(CMD_Command)) return false;

			//提取数据
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
					case SUB_GF_OPTION:			//游戏配置
						{
							//效验参数
							ASSERT(wPacketSize==sizeof(CMD_GF_Option));
							if (wPacketSize!=sizeof(CMD_GF_Option)) return false;

							//消息处理
							CMD_GF_Option * pOption=(CMD_GF_Option *)pSocketPackage->cbBuffer;
							m_bGameStatus=pOption->bGameStatus;

							return true;
						}
					case SUB_GF_SCENE:			//游戏场景
						{
							return OnGameSceneMessage(m_bGameStatus,pSocketPackage->cbBuffer,wPacketSize);
						}
					case SUB_GF_LOOKON_CONTROL:	//旁观控制
						{
							return true;
						}
					//case SUB_GF_BANK:
					//	{
					//		return true;
					//	}
					case SUB_GF_USER_CHAT:		//聊天信息
						{
							return true;
						}
					//case SUB_GF_INTEREST:
					//	{
					//		return true;
					//	}
					case SUB_GF_MESSAGE:		//系统消息
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
