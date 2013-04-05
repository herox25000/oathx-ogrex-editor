#include "StdAfx.h"
#include "IAndroid.h"

namespace O2
{
	//状态信息
	struct tagAstatInfo
	{
		ADAPTER_STATUS			AdapterStatus;						//网卡状态
		NAME_BUFFER				NameBuff[16];						//名字缓冲
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	IAndroid::IAndroid(DWORD dwUserID, double fOnlineTime)
		: m_dwUserID(dwUserID), m_fOnlineTime(fOnlineTime), m_pUserManager(NULL), m_wStaus(STATUS_CREATED), m_wSitReqCount(0)
	{
		Reset();
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
		//变量定义
		WORD wMacSize=0;
		HINSTANCE hInstance=NULL;
		typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

		try
		{
			//加载 DLL
			hInstance=LoadLibrary(TEXT("NetApi32.dll"));
			if (hInstance==NULL) 
				throw TEXT("加载 NetApi32.dll 失败");

			//获取函数
			NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
			if (pNetBiosProc==NULL) 
				throw TEXT("无法找到 NetBios 函数");

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
			if (LanaEnum.length==0)
				throw TEXT("找不到任何网卡");

			//获取地址
			tagAstatInfo Adapter;
			for (BYTE i=0;i<LanaEnum.length;i++)
			{
				//重置网卡
				ZeroMemory(&Ncb,sizeof(Ncb));
				Ncb.ncb_command=NCBRESET;
				Ncb.ncb_lana_num=LanaEnum.lana[i];
				if (pNetBiosProc(&Ncb)!=NRC_GOODRET) 
					throw TEXT("重置网卡失败");

				//获取状态
				ZeroMemory(&Ncb,sizeof(Ncb));
				Ncb.ncb_command=NCBASTAT;
				Ncb.ncb_length=sizeof(Adapter);
				Ncb.ncb_buffer=(BYTE *)&Adapter;
				Ncb.ncb_lana_num=LanaEnum.lana[i];
				strcpy((char *)Ncb.ncb_callname,"*");
				if (pNetBiosProc(&Ncb)!=NRC_GOODRET)
					throw TEXT("获取网卡状态失败");

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

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::GetClientSerial(tagClientSerial & ClientSerial)
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

	//////////////////////////////////////////////////////////////////////////
	void			IAndroid::LogEvent(const CString& lpszText, enTraceLevel lv)
	{
		CTraceService::TraceString(lpszText, lv);
	}

	/*
	* 获取用户ID
	*/
	DWORD			IAndroid::GetID() const
	{
		return m_dwUserID;
	}

	/*
	* 设置用户在线时间
	*/
	void			IAndroid::SetOnlineTime(double fOnlineTime)
	{
		m_fOnlineTime = fOnlineTime;
	}

	/*
	* 获取用户在线时间
	*/
	double			IAndroid::GetOnlineTime() const
	{
		return m_fOnlineTime;
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
	BOOL			IAndroid::Startup(const CString& szIPAdress, WORD wPort, const CString& szPwd)
	{
		//设置组件
		IUnknownEx* pIUnknown = QUERY_ME_INTERFACE(IUnknownEx);
		if (!m_ClientSocket.CreateInstance())
			return FALSE;

		if (!m_ClientSocket->SetTCPSocketSink(pIUnknown))
			return false;

		DWORD dwResult = m_ClientSocket->Connect(szIPAdress, wPort);
		if (!dwResult)
		{
			CString szMessage;
			szMessage.Format("机器人[%d] 正在连接", m_dwUserID);
			CTraceService::TraceString(szMessage,
				TraceLevel_Normal);

			m_Password = szPwd;
		}

		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::Update(float fElapsed)
	{
		switch( m_wStaus )
		{
		case STATUS_IDLE:
			{
				m_fSitTime += fElapsed;
				if (m_fSitTime >= MAX_REQ_SITDOWNTIEM)
				{
					if (m_wSitReqCount <= MAX_REQ_SITDOWNCOUNT)
					{
						SitDwonRequest();
					}
					else
					{
						SetStatus(STATUS_INVALID);
					}

					m_fSitTime = 0;
				}
			}
			break;
		}

		return 0;
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
	void			IAndroid::Reset()
	{
		m_wStaus		= STATUS_IDLE;
		m_fSitTime		= 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::SwitchTable()
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, 
		WORD wDataSize)
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

	//////////////////////////////////////////////////////////////////////////
	/*
	* 用户连接
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
	{
		CString szError;

		if ( nErrorCode != 0)
		{
			szError.Format("[%d]连接失败, 错误代码%d",m_dwUserID, nErrorCode);
			CTraceService::TraceString(szError,
				TraceLevel_Warning);

			return 0;
		}

		//获取信息
		BYTE cbBuffer[SOCKET_PACKET];

		//登录数据包
		CMD_GR_LogonByUserID* pLogonByUserID = (CMD_GR_LogonByUserID *)cbBuffer;

		pLogonByUserID->dwUserID		= m_dwUserID;
		pLogonByUserID->dwPlazaVersion	= VER_PLAZA_FRAME;
		lstrcpyn(pLogonByUserID->szPassWord, m_Password, sizeof(pLogonByUserID->szPassWord));

		//机器序列号
		tagClientSerial ClientSerial;
		GetClientSerial(ClientSerial);

		//发送数据包
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID), 
			sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
		Packet.AddPacket(&ClientSerial, sizeof(ClientSerial), DTP_COMPUTER_ID);

		m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID, cbBuffer, sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

		szError.Format("[%i]网络连接已建立", (int)m_dwUserID);
		CTraceService::TraceString(szError,
			TraceLevel_Normal);
		
		SetStatus(STATUS_IDLE);

		return true;
	}
	
	/*
	* 用户断开
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
	{
		CString szMessage;
		szMessage.Format("[%d]网络连接已断开", m_dwUserID);
		LogEvent(szMessage, TraceLevel_Warning);
		
		// 设置机器人为无效的
		SetStatus(STATUS_INVALID);
		
		return true;
	}

	/*
	* 网络消息
	*/
	bool	__cdecl	IAndroid::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, 
		VOID* pBuffer, WORD wDataSize)
	{
		switch (Command.wMainCmdID)
		{
		case MDM_GR_LOGON:			//登录消息
			{
				return OnSocketMainLogon(wSocketID, Command, pBuffer,wDataSize);
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
				szMessage.Format("[%d]登录成功", m_dwUserID);
				LogEvent(szMessage, TraceLevel_Normal);

				// 请求加入游戏
				SwitchTable();
			}
			break;

		case SUB_GR_LOGON_ERROR:
			{
				//效验参数
				CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;

				if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) 
					return 0;

				//关闭连接
				m_ClientSocket->CloseSocket();

				//显示消息
				WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
				if (wDescribeSize>0)
				{
					pLogonError->szErrorDescribe[wDescribeSize-1]=0;
					LogEvent(pLogonError->szErrorDescribe, 
						TraceLevel_Warning);
				}

				SetStatus(STATUS_INVALID);
			}
			break;

		case SUB_GR_LOGON_FINISH:
			{
				//构造数据包
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

				//发送数据包
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

				//读取基本信息
				tagUserInfoHead* pUserInfoHead = (tagUserInfoHead *)(pBuffer);

				SUser* pUser = m_pUserManager->Search(pUserInfoHead->dwUserID);
				if (pUser)
				{
					pUser->nScore = pUserInfoHead->UserScoreInfo.lScore;
				}
				else
				{
					pUser = new SUser();
					pUser->dwUserID		= pUserInfoHead->dwUserID;
					pUser->nScore		= pUserInfoHead->UserScoreInfo.lScore;
					pUser->wTableID		= pUserInfoHead->wTableID;
					pUser->wChairID		= pUserInfoHead->wChairID;
					pUser->cbUserStatus	= pUserInfoHead->cbUserStatus;
					pUser->dwGameID		= pUserInfoHead->dwGameID;

					//读取扩展信息
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
						case DTP_USER_ACCOUNTS:		//用户帐户
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

					// 添加到用户管理器
					m_pUserManager->Add(pUser);
				}
			}
			break;

		case SUB_GR_USER_STATUS:
			{
				if (wDataSize<sizeof(CMD_GR_UserStatus)) 
					return 0;
				//处理数据
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
					// 移除该机器人
					m_pUserManager->Remove(pUserStatus->dwUserID);

					// 如果是自己
					if (pUserStatus->dwUserID == m_dwUserID)
					{
						SetStatus(STATUS_INVALID);
					}
				}
				else
				{
					//更新状态
					pUser->wTableID		= wNowTableID;
					pUser->wChairID		= wNowChairID;
					pUser->cbUserStatus = cbNowStatus;

					if (pUserStatus->cbUserStatus == US_SIT && pUserStatus->dwUserID == m_dwUserID 
						&& wNowTableID != INVALID_TABLE && ((wNowTableID!=wLastTableID) || (wNowChairID!=wLastChairID)))
					{
						// 设置为坐下状态
						SetStatus(STATUS_SITDOWN);

						CString szMessage;
						szMessage.Format("[%d]已坐下", m_dwUserID);
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

				//处理数据
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
				//消息处理
				CMD_GR_SitFailed* pSitFailed = (CMD_GR_SitFailed *)pBuffer;

				CString szMessage;
				szMessage.Format("[%d] %s, 5秒后重连", m_dwUserID, pSitFailed->szFailedDescribe);
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
			return 0;

		//构造数据
		IPC_SocketPackage SocketPackage;
		memset(&SocketPackage,0,sizeof(SocketPackage));
		SocketPackage.Command = Command;
		if (wDataSize>0)
		{
			ASSERT(pBuffer!=NULL);
			CopyMemory(SocketPackage.cbBuffer,pBuffer,wDataSize);
		}

		//发送数据
		WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;

		return OnSocket(IPC_MAIN_SOCKET, IPC_SUB_SOCKET_RECV,
			&SocketPackage, wSendSize);
	}

	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
	{
		switch (wSubCmdID)
		{
		case IPC_SUB_SOCKET_RECV:	//数据接收
			{
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
								if (wPacketSize!=sizeof(CMD_GF_Option)) 
									return 0;

								//消息处理
								CMD_GF_Option* pOption=(CMD_GF_Option *)pSocketPackage->cbBuffer;
								m_bGameStatus = pOption->bGameStatus;

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
						case SUB_GF_USER_CHAT:		//聊天信息
							{
								return true;
							}

						case SUB_GF_MESSAGE:		//系统消息
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


	bool			IAndroid::OnSocketToolBox(CMD_Command Command, void* pBuffer, WORD wDataSize)
	{
		switch(Command.wSubCmdID)
		{
		case SUB_TOOLBOX_BANKOPERATING: //银行操作完成
			{
				if (wDataSize<sizeof(CMD_TOOLBOX_BankTask_Ret))
					return 0;

				CMD_TOOLBOX_BankTask_Ret* pBankRet = (CMD_TOOLBOX_BankTask_Ret*)pBuffer;
				if (pBankRet->lErrorCode==0)
				{
					CString szMessage;
					szMessage.Format("[%d]%s金钱 %I64d", m_dwUserID, pBankRet->lBankTask == 1 ? "存入" : "取出", pBankRet->lMoneyNumber);
					LogEvent(szMessage, TraceLevel_Debug);
				}
				else
				{
					MessageBox(NULL, pBankRet->szErrorDescribe, NULL, NULL);
				}
			}
			break;
		case SUB_TOOLBOX_MESSAGE:
			{
				//效验参数
				CMD_GR_Message * pMessage=(CMD_GR_Message *)pBuffer;
				if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)))
					return 0;
				//消息处理
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
	bool			IAndroid::OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)
	{
		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			IAndroid::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
	{
		return 0;
	}
}
