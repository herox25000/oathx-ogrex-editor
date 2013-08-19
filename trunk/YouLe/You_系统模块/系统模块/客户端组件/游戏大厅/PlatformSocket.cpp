#include "StdAfx.h"
#include "platformsocket.h"

CPlatformSocket::CPlatformSocket(void)
{
	m_bLogonPlaza = false;
}

CPlatformSocket::~CPlatformSocket(void)
{
}

//接口查询
void * __cdecl CPlatformSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}
//连接事件
bool __cdecl CPlatformSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
		ShowMessageBox(TEXT("登录服务器连接失败，请稍后再试或留意网站公告！"),MB_ICONINFORMATION);
		if(m_pPlatformFrame != NULL)
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
		return true;
	}

	//发送登录包
	if (m_bLogonPlaza==false)
	{
		if(m_pDlgLogon != NULL)
			m_pDlgLogon->SendLogonPacket(m_ClientSocket.GetInterface());
		g_GlobalAttemper.ShowStatusMessage(TEXT("正在验证用户登录信息..."),m_pPlatformFrame);
	}
	return true;
}
//关闭事件
bool __cdecl CPlatformSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if (m_bLogonPlaza==false)
	{
		if (cbShutReason!=SHUT_REASON_NORMAL)
		{
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
			ShowMessageBox(TEXT("登录服务器连接失败，请稍后再试或留意网站公告！"),MB_ICONINFORMATION);
			if(m_pPlatformFrame != NULL)
				m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
		}
	}

	return true;
}
//读取事件
bool __cdecl CPlatformSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GP_LOGON:				//登录消息
		{
			return OnSocketMainLogon(Command,pData,wDataSize);
		}
	case MDM_GP_SERVER_LIST:		//列表消息
		{
			return OnSocketMainServerList(Command,pData,wDataSize);
		}
	case MDM_GP_SYSTEM:				//系统消息
		{
			return OnSocketMainSystem(Command,pData,wDataSize);
		}
	case MDM_GP_USER:				//用户消息
		{
			return OnSocketMainUser(Command,pData,wDataSize);
		}
	}
	return true;
}


//连接到服务器
void CPlatformSocket::ConnectToServer(LPCTSTR ServerIP,WORD wPort)
{
	//创建组件
	if (m_ClientSocket.GetInterface()==NULL)
	{
		try
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_ClientSocket.CreateInstance()==false) 
			{
				throw TEXT("网络组件创建失败");
			}
			if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("网络组件回调接口设置失败");
			}
		}
		catch (...)
		{
			ShowMessageBox(TEXT("网络组件创建失败，请重新下载游戏大厅！"),MB_ICONSTOP);
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA);
			return;
		}
	}

	//连接服务器
	try
	{
		//连接服务器
		m_ClientSocket->CloseSocket();
		if (m_ClientSocket->Connect(ServerIP,wPort )!=CONNECT_SUCCESS)
		{
			throw TEXT("服务器连接错误，可能是你的系统还没有成功连接上网络！");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessageBox(pszError,MB_ICONINFORMATION);
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA);
		return;
	}

	//显示提示框
	CString strMessage=TEXT("正在连接服务器，请稍候...");
	g_GlobalAttemper.ShowStatusMessage(strMessage,m_pPlatformFrame);
}

//发送信息
void CPlatformSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}


//登录消息
bool CPlatformSocket::OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GP_LOGON_SUCCESS:		//登录成功
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(CMD_GP_LogonSuccess));
			if (wDataSize<sizeof(CMD_GP_LogonSuccess)) return false;

			//保存信息
			tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
			CMD_GP_LogonSuccess * pLogonSuccess=(CMD_GP_LogonSuccess *)pData;
			UserData.wFaceID=pLogonSuccess->wFaceID;
			UserData.cbGender=pLogonSuccess->cbGender;
			UserData.cbMember=pLogonSuccess->cbMember;
			UserData.dwUserID=pLogonSuccess->dwUserID;
			UserData.dwGameID=pLogonSuccess->dwGameID;
			UserData.dwExperience=pLogonSuccess->dwExperience;
			UserData.dwCustomFaceVer=pLogonSuccess->dwCustomFaceVer;
			UserData.wLevel = pLogonSuccess->wLevel;
			UserData.lScore = pLogonSuccess->lScore;
			UserData.lBeans = pLogonSuccess->lBeans;
			UserData.lLottery = pLogonSuccess->lLottery;

			//扩展信息
			void * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonSuccess+1,wDataSize-sizeof(CMD_GP_LogonSuccess));
			while (true)
			{
				pDataBuffer=RecvPacket.GetData(DataDescribe);
				if (DataDescribe.wDataDescribe==DTP_NULL) break;
				switch (DataDescribe.wDataDescribe)
				{
				case DTP_USER_ACCOUNTS:		//用户帐户
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szAccounts));
						if (DataDescribe.wDataSize<=sizeof(UserData.szAccounts))
						{
							CopyMemory(UserData.szAccounts,pDataBuffer,DataDescribe.wDataSize);
							UserData.szAccounts[CountArray(UserData.szAccounts)-1]=0;
						}
						break;
					}
				case DTP_USER_PASS:			//用户密码
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szPassWord));
						if (DataDescribe.wDataSize<=sizeof(UserData.szPassWord))
						{
							CopyMemory(UserData.szPassWord,pDataBuffer,DataDescribe.wDataSize);
							UserData.szPassWord[CountArray(UserData.szPassWord)-1]=0;
						}
						break;
					}
				case DTP_UNDER_WRITE:		//个性签名
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite));
						if (DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite))
						{
							CopyMemory(UserData.szUnderWrite,pDataBuffer,DataDescribe.wDataSize);
							UserData.szUnderWrite[CountArray(UserData.szUnderWrite)-1]=0;
						}
						break;
					}
				case DTP_USER_GROUP_NAME:	//社团名字
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szGroupName));
						if (DataDescribe.wDataSize<=sizeof(UserData.szGroupName))
						{
							CopyMemory(UserData.szGroupName,pDataBuffer,DataDescribe.wDataSize);
							UserData.szGroupName[CountArray(UserData.szGroupName)-1]=0;
						}
						break;
					}
				case DTP_STATION_PAGE:		//游戏主站
					{
						ASSERT(pDataBuffer!=NULL);
						if (pDataBuffer!=NULL) 
						{
							g_GlobalUnits.SetStationPage((LPCTSTR)pDataBuffer);
						}
						break;
					}
				case DTP_NICK_NAME:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szNickName)) 
						{
							CopyMemory(UserData.szNickName,pDataBuffer, DataDescribe.wDataSize);
							UserData.szNickName[CountArray(UserData.szNickName)-1]=0;
						}
						break;
					}
				case DTP_USER_NAME:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szUserName)) 
						{
							CopyMemory(UserData.szUserName,pDataBuffer, DataDescribe.wDataSize);
							UserData.szUserName[CountArray(UserData.szUserName)-1]=0;
						}
						break;
					}
				case DTP_USER_CEITIFICATE:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szCeitificate)) 
						{
							CopyMemory(UserData.szCeitificate,pDataBuffer, DataDescribe.wDataSize);
							UserData.szCeitificate[CountArray(UserData.szCeitificate)-1]=0;
						}
						break;
					}
				case DTP_USER_ADDRESS:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szAddress)) 
						{
							CopyMemory(UserData.szAddress,pDataBuffer, DataDescribe.wDataSize);
							UserData.szAddress[CountArray(UserData.szAddress)-1]=0;
						}
						break;
					}
				default: { ASSERT(FALSE); }
				}
			}

			//设置提示
			g_GlobalAttemper.ShowStatusMessage(TEXT("正在读取服务器列表信息..."),m_pPlatformFrame);

			return true;
		}
	case SUB_GP_LOGON_ERROR:		//登录失败
		{
			//效验参数
			CMD_GP_LogonError *pLogonError = (CMD_GP_LogonError *)pData;
			ASSERT(wDataSize>=(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//关闭连接
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
			m_ClientSocket->CloseSocket();

			//显示消息
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}
			//发送登录
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
			return true;
		}
	case SUB_GP_LOGON_FINISH:		//登录完成
		{
			//关闭提示
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);

			////展开类型
			//INT_PTR nIndex=0;
			//CListType * pListType=NULL;
			//do
			//{
			//	pListType=g_GlobalUnits.m_ServerListManager.EnumTypeItem(nIndex++);
			//	if (pListType==NULL) break;
			//	g_GlobalUnits.m_ServerListManager.ExpandListItem(pListType);
			//} while (true);

			////展开列表
			//nIndex=0;
			//CListInside * pListInside=NULL;
			//do
			//{
			//	pListInside=g_GlobalUnits.m_ServerListManager.EnumInsideItem(nIndex++);
			//	if (pListInside==NULL) break;
			//	g_GlobalUnits.m_ServerListManager.ExpandListItem(pListInside);
			//} while (true);
			
			//显示游戏界面
			if(g_UIPageManager.m_pGamePage)
			{
				if(g_UIPageManager.m_pGamePage->m_pGameView)
					g_UIPageManager.m_pGamePage->m_pGameView->ShowFirstPage();
			}
			

			m_bLogonPlaza=true;
			//记录信息
			g_GlobalUnits.WriteUserCookie();
			if(m_pPlatformFrame != NULL)
			{
				m_pPlatformFrame->ShowWindow(SW_SHOW);
				m_pPlatformFrame->SetActiveWindow();
				m_pPlatformFrame->BringWindowToTop();
				m_pPlatformFrame->SetForegroundWindow();
			}
			if(m_pDlgLogon != NULL)
				m_pDlgLogon->OnLogonSuccess();
			////显示头像
			//((CGameFrame*)AfxGetMainWnd())->m_UserInfoView.ShowUserInfo(true);

			////自定义判断
			//tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
			//if ( GlobalUserData.dwCustomFaceVer!=0)
			//{
			//	//头像名称
			//	CString strDirName = CString(g_GlobalUnits.GetWorkDirectory()) + TEXT("\\CustomFace");
			//	CString strFileName;
			//	strFileName.Format(TEXT("\\%ld_%d.bmp"), GlobalUserData.dwUserID, GlobalUserData.dwCustomFaceVer);

			//	//读取文件
			//	CImage FaceImage;
			//	HRESULT hResult = FaceImage.Load(strDirName + strFileName);
			//	if (SUCCEEDED(hResult))
			//	{
			//		//关闭连接
			//		m_ClientSocket->CloseSocket();

			//		FaceImage.Destroy();
			//	}
			//	//下载头像
			//	else
			//	{
			//		PostMessage(WM_DOWN_LOAD_FACE, LPARAM(GlobalUserData.dwCustomFaceVer), WPARAM(GlobalUserData.dwUserID));
			//	}
			//}
			//else
			//{
			//	//关闭连接
			//	m_ClientSocket->CloseSocket();
			//}

			return true;
		}
	}

	return true;
}

//游戏列表消息
bool CPlatformSocket::OnSocketMainServerList(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SERVER_LIST);

	switch (Command.wSubCmdID)
	{
	case SUB_GP_LIST_TYPE:			//类型信息
		{
			//效验参数
			ASSERT(wDataSize%sizeof(tagGameType)==0);
			if (wDataSize%sizeof(tagGameType)!=0) return false;

			//处理消息
			tagGameType * pGameType=(tagGameType *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameType);
			g_GlobalUnits.m_ServerListManager.InsertTypeItem(pGameType,wItemCount);

			return true;
		}
	case SUB_GP_LIST_KIND:			//种类消息
		{
			//效验参数
			ASSERT(wDataSize%sizeof(tagGameKind)==0);
			if (wDataSize%sizeof(tagGameKind)!=0) return false;

			//处理消息
			tagGameKind * pGameKind=(tagGameKind *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameKind);
			g_GlobalUnits.m_ServerListManager.InsertKindItem(pGameKind,wItemCount);

			return true;
		}
	case SUB_GP_LIST_STATION:		//站点消息
		{
			//效验参数
			ASSERT(wDataSize%sizeof(tagGameStation)==0);
			if (wDataSize%sizeof(tagGameStation)!=0) return false;

			//处理消息
			tagGameStation * pGameStation=(tagGameStation *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameStation);
			g_GlobalUnits.m_ServerListManager.InsertStationItem(pGameStation,wItemCount);
			return true;
		}
	case SUB_GP_LIST_SERVER:		//服务器房间
		{
			//效验参数
			ASSERT(wDataSize%sizeof(tagGameServer)==0);
			if (wDataSize%sizeof(tagGameServer)!=0) return false;

			//处理消息
			tagGameServer * pGameServer=(tagGameServer *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameServer);
			g_GlobalUnits.m_ServerListManager.InsertServerItem(pGameServer,wItemCount);
			return true;
		}
	case SUB_GP_LIST_FINISH:		//列表发送完成
		{
			//更新人数
			INT_PTR nIndex=0;
			DWORD dwAllOnLineCount=0L;
			CListKind * pListKind=NULL;
			do
			{
				pListKind=g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex++);
				if (pListKind==NULL) break;
				dwAllOnLineCount+=pListKind->GetItemInfo()->dwOnLineCount;
			} while (true);
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);
			return true;
		}
	case SUB_GP_LIST_CONFIG:		//列表配置
		{
			//效验参数
			ASSERT(wDataSize%sizeof(CMD_GP_ListConfig)==0);
			if (wDataSize%sizeof(CMD_GP_ListConfig)!=0) return false;

			//处理消息
			CMD_GP_ListConfig * pListConfig=(CMD_GP_ListConfig *)pData;
			bool bShowOnLineCount = pListConfig->bShowOnLineCount?true:false;

			return true;
		}
	}

	return true;
}

//系统消息
bool CPlatformSocket::OnSocketMainSystem(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GP_VERSION:			//版本信息
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(CMD_GP_Version));
			if (wDataSize<sizeof(CMD_GP_Version)) return false;

			//消息处理
			CMD_GP_Version * pVersion=(CMD_GP_Version *)pData;
			if (pVersion->bAllowConnect)
			{
				TCHAR szMessage[]=TEXT("游戏大厅版本已经升级，现在的版本还可以继续使用，现在是否马上下载新版本？");
				int iResult=ShowInformationEx(szMessage,0,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1,TEXT("游戏大厅"));
				if (iResult==IDYES)
				{
					g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
					m_ClientSocket->CloseSocket();
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					g_GlobalAttemper.DownLoadClient(TEXT("游戏大厅"),0,true);
				}
			}
			else
			{
				g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
				m_ClientSocket->CloseSocket();
				TCHAR szMessage[]=TEXT("游戏大厅版本已经升级，现在的版本不可以继续使用，现在是否马上下载新版本？");
				int iResult=ShowInformationEx(szMessage,0,MB_ICONSTOP|MB_YESNO|MB_DEFBUTTON1,TEXT("游戏大厅"));
				if(iResult != IDYES)
				{
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					AfxGetMainWnd()->PostMessage(WM_CLOSE);
				}
				else 
				{
					g_GlobalAttemper.DownLoadClient(TEXT("游戏大厅"),0,true);
				}
			}

			return true;
		}
	}
	return true;
}

//用户消息
bool CPlatformSocket::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID == MDM_GP_USER);
	switch(Command.wSubCmdID)
	{
	case SUB_GP_USER_DOWNLOAD_FACE:			//下载头像
	case SUB_GP_UPLOAD_FACE_RESULT:		//上传结果
	case SUB_GP_DELETE_FACE_RESULT:		//删除结果
	case SUB_GP_MODIFY_INDIVIDUAL_RESULT:	//修改结果
		{
			return true;
		}
	default:
		{
			ASSERT(FALSE);
			return false;
		}
	}
	return true;
}
