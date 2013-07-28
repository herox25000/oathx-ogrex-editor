#include "StdAfx.h"
#include "gameroomsocket.h"
#include "GlobalUnits.h"
#include "GameRoomManager.h"

CGameRoomSocket::CGameRoomSocket(void)
{
	m_pGameRoomMgr = NULL;
	m_pListServer = NULL;
}

CGameRoomSocket::~CGameRoomSocket(void)
{
}

//接口查询
void * __cdecl CGameRoomSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE(IChannelMessageSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//连接事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(m_pWnd);
		ShowMessageBox(TEXT("游戏房间连接失败，您暂时不能进入此游戏房间！"),MB_ICONINFORMATION);
		m_pGameRoomMgr->CloserRoomFram();
		return true;
	}

	//发送登录信息
	SendLogonPacket();
	m_ServiceStatus=ServiceStatus_EfficacyUser;

	return true;
}
//关闭事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//判断关闭
	bool bCloseRoomView=(m_ServiceStatus!=ServiceStatus_Serviceing && cbShutReason != SHUT_REASON_NORMAL);

	//关闭处理
	CloseGameClient();
	g_GlobalAttemper.DestroyStatusWnd(m_pWnd);
	m_ServiceStatus=ServiceStatus_NetShutDown;
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			ShowMessageBox("由于网络问题，您已经与服务器断开连接，请重新连接",MB_ICONINFORMATION);
		}
		else
		{
			ShowMessageBox("由于网络数据包处理失败，网络中断了",MB_ICONINFORMATION);
		}
	}

	//关闭房间
	if (bCloseRoomView==true)
		m_pGameRoomMgr->CloserRoomFram();
	return true;
}
//读取事件
bool __cdecl CGameRoomSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//登录消息
		{
			return OnSocketMainLogon(Command,pData,wDataSize);
		}
	case MDM_GR_USER:			//用户消息
		{
			return OnSocketMainUser(Command,pData,wDataSize);
		}
	case MDM_GR_INFO:			//配置信息
		{
			return OnSocketMainInfo(Command,pData,wDataSize);
		}
	case MDM_GR_STATUS:			//状态信息
		{
			return OnSocketMainStatus(Command,pData,wDataSize);
		}
	case MDM_GR_SYSTEM:			//系统消息
		{
			return OnSocketMainSystem(Command,pData,wDataSize);
		}
	case MDM_GR_SERVER_INFO:	//房间信息
		{
			return OnSocketMainServerInfo(Command,pData,wDataSize);
		}
	case MDM_GF_GAME:			//游戏消息
	case MDM_GF_FRAME:			//框架消息
	case MDM_GF_VIDEO:			//视频消息
	case MDM_GF_PRESENT:		//礼物消息
		{
			return OnSocketMainGameFrame(Command,pData,wDataSize);
		}
	}

	return true;
}
//信道数据处理
bool __cdecl CGameRoomSocket::OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	switch (pHead->wMainCmdID)
	{
	case IPC_MIAN_IPC_KERNEL:		//内核消息
		{
			return OnIPCKernel(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_SOCKET:			//网络事件
		{
			return OnIPCSocket(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_CONCTROL:			//控制消息
		{
			return true;
		}
	}
	return false;
}

//登录消息
bool CGameRoomSocket::OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//登录成功
		{
			//设置变量
			m_ServiceStatus=ServiceStatus_RecvConfigInfo;
			return true;
		}
	case SUB_GR_LOGON_ERROR:		//登录失败
		{
			//效验参数
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pData;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//关闭连接
			g_GlobalAttemper.DestroyStatusWnd(m_pWnd);
			m_ClientSocket->CloseSocket();
			m_ServiceStatus=ServiceStatus_NetShutDown;

			//显示消息
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}

			//关闭房间
			m_pGameRoomMgr->CloserRoomFram();

			return true;
		}
	case SUB_GR_LOGON_FINISH:		//登录完成
		{
			//设置界面
			//m_TableFrame.ShowUserInfo(true);
			g_GlobalAttemper.DestroyStatusWnd(m_pWnd);
			//((CGameFrame*)AfxGetMainWnd())->ActiveRoomViewItem(this);

			//设置变量
			m_ServiceStatus=ServiceStatus_Serviceing;

			//发送规则
			//SendUserRulePacket();

			//重入判断
			ASSERT(m_pMeUserItem!=NULL);
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->wTableID!=INVALID_TABLE)
			{
				int iResult=StartGameClient();
			}

			return true;
		}
	}

	return true;
}

//用户消息
bool CGameRoomSocket::OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//用户进入
		{
			return OnSocketSubUserCome(Command,pData,wDataSize);
		}
	case SUB_GR_USER_STATUS:		//用户状态
		{
			return OnSocketSubStatus(Command,pData,wDataSize);
		}
	case SUB_GR_USER_SCORE:			//用户分数
		{
			return OnSocketSubScore(Command,pData,wDataSize);
		}
	case SUB_GR_USER_RIGHT:			//用户权限
		{
			return OnSocketSubRight(Command,pData,wDataSize);
		}
	case SUB_GR_MEMBER_ORDER:		//会员等级
		{
			return OnSocketSubMemberOrder(Command,pData,wDataSize);
		}
	case SUB_GR_SIT_FAILED:			//坐下失败
		{
			return OnSocketSubSitFailed(Command,pData,wDataSize);
		}
	case SUB_GR_USER_CHAT:			//用户聊天
		{
			return OnSocketSubChat(Command,pData,wDataSize);
		}
	case SUB_GR_USER_WISPER:		//用户私语
		{
			return OnSocketSubWisper(Command,pData,wDataSize);
		}
	case SUB_GR_USER_INVITE:		//邀请玩家
		{
			return OnSocketSubUserInvite(Command,pData,wDataSize);
		}
	}

	return true;
}


//配置消息
bool CGameRoomSocket::OnSocketMainInfo(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_SERVER_INFO:	//房间信息
		{
			//效验数据
			ASSERT(wDataSize>=sizeof(CMD_GR_ServerInfo));
			if (wDataSize<sizeof(CMD_GR_ServerInfo)) return false;

			//消息处理
			CMD_GR_ServerInfo * pServerInfo=(CMD_GR_ServerInfo *)pData;

			//设置变量
			m_wKindID=pServerInfo->wKindID;
			m_wTableCount = pServerInfo->wTableCount;
			m_wChairCount = pServerInfo->wChairCount;
			m_wGameGenre=pServerInfo->wGameGenre;
			m_dwVideoAddr=pServerInfo->dwVideoAddr;
			m_cbHideUserInfo=pServerInfo->cbHideUserInfo;

			//获取信息
			CListKind * pListKind=m_pListServer->GetListKind();
			tagGameKind * pGameKind=pListKind->GetItemInfo();
			IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);


			//创建桌子
			try
			{
				m_pGameRoomMgr->CreateGameTable();
			}
			catch (...)
			{
				//关闭网络
				m_ClientSocket->CloseSocket();
				g_GlobalAttemper.DestroyStatusWnd(m_pWnd);

				//提示消息
				int nResult=ShowMessageBox(TEXT("游戏房间资源加载失败，重新下载安装可能会解决问题，是否立即下载？"),MB_ICONQUESTION|MB_YESNO);
				if (nResult==IDYES) 
				{
					CListKind * pListKind=m_pListServer->GetListKind();
					tagGameKind * pGameKind=pListKind->GetItemInfo();
					g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
				}

				////关闭房间
				//IRoomViewItem * pIRoomViewItem=QUERY_ME_INTERFACE(IRoomViewItem);
				//((CGameFrame*)AfxGetMainWnd())->CloseRoomViewItem(pIRoomViewItem);

				return false;
			}

			return true;
		}
	case SUB_GR_COLUMN_INFO:	//列表解释
		{
			//变量定义
			CMD_GR_ColumnInfo * pColumnInfo=(CMD_GR_ColumnInfo *)pData;
			WORD wHeadSize=sizeof(CMD_GR_ColumnInfo)-sizeof(pColumnInfo->ColumnItem);

			//效验参数
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))!=wDataSize) return false;

			////设置列表
			//CopyMemory(&m_ListColumnInfo,pColumnInfo,__min(wDataSize,sizeof(m_ListColumnInfo)));
			//m_UserListView.SetColumnDescribe(pColumnInfo->ColumnItem,pColumnInfo->wColumnCount);

			return true;
		}
	case SUB_GR_CONFIG_FINISH:	//配置完成
		{
			//资源目录
			TCHAR szResDirectory[128]=TEXT("");
			WORD wStringIndex=0,wBufferCount=CountArray(szResDirectory);

			//构造目录
			const tagGameKind * pGameKind = GetKindInfo();
			ZeroMemory(szResDirectory,wBufferCount*sizeof(TCHAR));
			lstrcpyn(szResDirectory,(LPCTSTR)pGameKind->szProcessName,wBufferCount);
			while ((szResDirectory[wStringIndex]!=0)&&(szResDirectory[wStringIndex]!=TEXT('.'))) wStringIndex++;

			//字符终止
			szResDirectory[wStringIndex]=0;

			////游戏等级
			//ASSERT(m_UserListView.m_GameRankManager.GetInterface()!=NULL);
			///*bool bSuccess=*/m_UserListView.m_GameRankManager->LoadGameLevel(szResDirectory,m_wGameGenre);

			////显示房间
			//ShowWindow(SW_SHOW);
			//((CGameFrame*)AfxGetMainWnd())->ActiveRoomViewItem(this);

			//设置变量
			m_ServiceStatus=ServiceStatus_RecvRoomInfo;

			return true;
		}
	}

	return true;
}

//状态消息
bool CGameRoomSocket::OnSocketMainStatus(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_STATUS);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_TABLE_INFO:		//桌子信息
		{
			//变量定义
			CMD_GR_TableInfo * pTableInfo=(CMD_GR_TableInfo *)pData;
			const WORD wHeadSize=sizeof(CMD_GR_TableInfo)-sizeof(pTableInfo->TableStatus);

			//效验数据
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))!=wDataSize) return false;

			//消息处理
			for (WORD i=0;i<pTableInfo->wTableCount;i++)
			{
				m_pGameRoomMgr->SetPassFlag(i,pTableInfo->TableStatus[i].bTableLock?true:false);
				m_pGameRoomMgr->SetPlayFlag(i,pTableInfo->TableStatus[i].bPlayStatus?true:false);
			}

			return true;
		}
	case SUB_GR_TABLE_STATUS:	//桌子状态
		{
			//效验数据
			ASSERT(wDataSize>=sizeof(CMD_GR_TableStatus));
			if (wDataSize<sizeof(CMD_GR_TableStatus)) return false;

			//消息处理
			CMD_GR_TableStatus * pTableStatus=(CMD_GR_TableStatus *)pData;
			ASSERT(pTableStatus->wTableID<m_wTableCount);
			if (pTableStatus->wTableID<m_wTableCount)
			{
				//变量定义
				IUserItem * pIUserItem=NULL;
				tagUserData * pUserData=NULL;
				BYTE bPlayStatus=m_pGameRoomMgr->QueryPlayFlag(pTableStatus->wTableID);

				//设置用户
				if (bPlayStatus!=pTableStatus->bPlayStatus)
				{
					BYTE cbUserStatus=pTableStatus->bPlayStatus?US_PLAY:US_SIT;
					//游戏用户
					WORD wEnumIndex=0;
					while (true)
					{
						pIUserItem=m_ClientUserManager.EnumUserItem(wEnumIndex++);
						if (pIUserItem==NULL)
							break;
						pUserData=pIUserItem->GetUserData();
						if(pTableStatus->wTableID == pUserData->wTableID)
						{
							if (pUserData->cbUserStatus!=US_OFFLINE) 
							{
								pUserData->cbUserStatus=cbUserStatus;
							}	
						}
					}
				}

				//设置桌子
				m_pGameRoomMgr->SetPassFlag(pTableStatus->wTableID,pTableStatus->bTableLock?true:false);
				m_pGameRoomMgr->SetPlayFlag(pTableStatus->wTableID,pTableStatus->bPlayStatus?true:false);

				//通知游戏
				if (bPlayStatus!=pTableStatus->bPlayStatus)
				{
					tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
					if (pMeUserData->wTableID==pTableStatus->wTableID)
					{
						WORD wSubCmdID=pTableStatus->bPlayStatus?IPC_SUB_GAME_START:IPC_SUB_GAME_FINISH;
						SendProcessData(IPC_MAIN_USER,wSubCmdID,NULL,0);
					}
				}
			}

			return true;
		}
	}

	return true;
}

//系统消息
bool CGameRoomSocket::OnSocketMainSystem(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//系统消息
		{
			//效验参数
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pData;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//消息处理
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;

			//关闭连接
			bool bIntermet=false;
			if (pMessage->wMessageType&SMT_INTERMIT_LINE) bIntermet=true;
			else if (pMessage->wMessageType&SMT_CLOSE_ROOM) bIntermet=true;
			if (bIntermet==true) 
			{
				g_GlobalAttemper.DestroyStatusWnd(m_pWnd);
				m_ClientSocket->CloseSocket();
				CloseGameClient();
			}

			////显示消息
			//if (pMessage->wMessageType&SMT_INFO) 
			//	m_MessageProxyHelper->InsertSystemString(pMessage->szContent,MS_NORMAL);
			if (pMessage->wMessageType&SMT_EJECT) 
				ShowMessageBox(pMessage->szContent,MB_ICONINFORMATION);

			//关闭房间
			if (pMessage->wMessageType&SMT_CLOSE_ROOM) 
			{
				IRoomViewItem * pIRoomViewItem=QUERY_ME_INTERFACE(IRoomViewItem);
				m_pGameRoomMgr->CloserRoomFram();
			}

			return true;
		}
	}

	return true;
}

//房间消息
bool CGameRoomSocket::OnSocketMainServerInfo(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SERVER_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_ONLINE_COUNT_INFO:		//在线信息
		{
			//效验数据
			ASSERT(wDataSize%sizeof(tagOnLineCountInfo)==0);
			if (wDataSize%sizeof(tagOnLineCountInfo)!=0) return false;

			//消息处理
			WORD wKindID=0;
			DWORD dwKindOnLineCount=0,dwAllOnLineCount=0L;
			WORD wInfoCount=wDataSize/sizeof(tagOnLineCountInfo);
			tagOnLineCountInfo * pOnLineCountInfo=(tagOnLineCountInfo *)pData;
			for (int i=0;i<wInfoCount;i++)
			{
				wKindID=(pOnLineCountInfo+i)->wKindID;
				dwKindOnLineCount=(pOnLineCountInfo+i)->dwOnLineCount;
				dwAllOnLineCount+=dwKindOnLineCount;
				g_GlobalUnits.m_ServerListManager.UpdateGameKindOnLine(wKindID,dwKindOnLineCount);
			}

			//更新总数
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);

			return true;
		}
	}

	return true;
}

//游戏消息
bool CGameRoomSocket::OnSocketMainGameFrame(CMD_Command Command, void * pData, WORD wDataSize)
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
		ASSERT(pData!=NULL);
		CopyMemory(SocketPackage.cbBuffer,pData,wDataSize);
	}

	//数据缓冲
	if (m_hWndChannel==NULL)
	{
		//状态判断
		ASSERT(m_pMeUserItem!=NULL);
		if (m_pMeUserItem==NULL) return false;

		//获取用户
		tagUserData * pUserData=m_pMeUserItem->GetUserData();

		//数据缓冲
		if ((pUserData->wTableID!=INVALID_TABLE)&&(pUserData->wChairID!=INVALID_CHAIR))
		{
			//设置变量
			m_wPacketTableID=pUserData->wTableID;
			m_wPacketChairID=pUserData->wChairID;

			//构造数据
			BYTE cbBuffer[SOCKET_BUFFER];
			CopyMemory(cbBuffer,&Command,sizeof(Command));
			CopyMemory(&cbBuffer[sizeof(Command)],pData,wDataSize);

			//插入数据
			m_PacketDataStorage.InsertData(0,cbBuffer,sizeof(Command)+wDataSize);
		}
	}
	else
	{
		//发送数据
		WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;
		SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize);
	}

	////道具数目
	//if ( Command.wSubCmdID == SUB_GF_RESIDUAL_PROPERTY )
	//{
	//	//效验参数
	//	ASSERT(wDataSize==sizeof(CMD_GF_ResidualProperty));
	//	if (wDataSize!=sizeof(CMD_GF_ResidualProperty)) return false;

	//	//变量定义
	//	CMD_GF_ResidualProperty * ResidualProperty=(CMD_GF_ResidualProperty *)pData;

	//	//获取玩家
	//	tagUserData *pMeUserData = m_pMeUserItem->GetUserData();

	//	//设置道具
	//	for ( WORD wPropID = 0; wPropID < PROPERTY_COUNT; ++wPropID )
	//	{
	//		pMeUserData->dwPropResidualTime[wPropID] = ResidualProperty->dwResidualTime[wPropID];
	//	}
	//}
	////道具消息
	//else if ( Command.wSubCmdID == SUB_GF_PROP_ATTRIBUTE )
	//{
	//	//校验参数
	//	ASSERT( wDataSize % sizeof(tagPropertyInfo) == 0 );
	//	if ( wDataSize % sizeof(tagPropertyInfo) != 0 ) return true;

	//	//类型转换
	//	int nInfoCount = wDataSize / sizeof(tagPropertyInfo);
	//	tagPropertyInfo *pPropertyInfo = (tagPropertyInfo*)pData;

	//	//保存属性
	//	for ( INT_PTR nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//		m_PropertyAttributeArrary.Add(pPropertyInfo[nIndex]);

	//	//获取对象
	//	CPropertyBar *pPropertyBar = CPropertyBar::GetInstance();
	//	ASSERT( pPropertyBar != NULL );
	//	if ( pPropertyBar == NULL ) return false;

	//	//初始结构
	//	for ( int nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//	{
	//		pPropertyBar->SetPropertyInfo((pPropertyInfo+nIndex)->nPropertyID, *(pPropertyInfo+nIndex));
	//	}
	//}
	////鲜花属性
	//else if ( Command.wSubCmdID == SUB_GF_FLOWER_ATTRIBUTE )
	//{
	//	//校验参数
	//	ASSERT( wDataSize % sizeof(tagFlowerInfo) == 0 );
	//	if ( wDataSize % sizeof(tagFlowerInfo) != 0 ) return true;

	//	//类型转换
	//	int nInfoCount = wDataSize / sizeof(tagFlowerInfo);
	//	tagFlowerInfo *pFlowerInfo= (tagFlowerInfo*)pData;

	//	//保存属性
	//	for ( INT_PTR nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//		m_FlowerAttributeArrary.Add(pFlowerInfo[nIndex]);

	//	//获取对象
	//	CPropertyBar *pPropertyBar = CPropertyBar::GetInstance();
	//	ASSERT( pPropertyBar != NULL );
	//	if ( pPropertyBar == NULL ) return false;

	//	//初始结构
	//	for ( int nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//	{
	//		pPropertyBar->SetFlowerInfo((pFlowerInfo+nIndex)->nFlowerID, *(pFlowerInfo+nIndex));
	//	}

	//}
	////喇叭消息
	//else if ( Command.wSubCmdID == SUB_GF_PROP_BUGLE )
	//{
	//	ASSERT( sizeof(CMD_GF_BugleProperty) == wDataSize );
	//	if ( sizeof(CMD_GF_BugleProperty) != wDataSize ) return false;

	//	//类型转换
	//	CMD_GF_BugleProperty *pBugleProperty = (CMD_GF_BugleProperty*)pData;

	//	//喇叭图片
	//	CBitmap Bitmap;
	//	AfxSetResourceHandle(GetResInstanceHandle());
	//	if ( Bitmap.LoadBitmap(g_GlobalUnits.m_ChatExpViewImage.uChatBugle) )
	//	{
	//		m_MessageProxyHelper->InsertImage(&Bitmap);
	//		Bitmap.DeleteObject();
	//	}
	//	AfxSetResourceHandle(GetModuleHandle(NULL));

	//	//喇叭内容
	//	m_MessageProxyHelper->InsertUserChat(pBugleProperty->szUserName,pBugleProperty->szContext,pBugleProperty->crText,MS_NORMAL);

	//	//播放声音
	//	HINSTANCE hInstance = AfxGetInstanceHandle();
	//	HRSRC hResour=FindResource(hInstance,TEXT("BUGLE"),TEXT("WAVE"));
	//	if (hResour!=NULL)
	//	{
	//		HGLOBAL hGlobal=LoadResource(hInstance,hResour);
	//		if (hGlobal!=NULL) 
	//		{
	//			//播放声音
	//			LPCTSTR pszMemory=(LPCTSTR)LockResource(hGlobal);
	//			BOOL bResult = ::PlaySound(pszMemory,hInstance,SND_ASYNC|SND_MEMORY|SND_NODEFAULT);

	//			//清理资源
	//			UnlockResource(hGlobal);
	//		}
	//		FreeResource(hGlobal);
	//	}
	//}
	////赠送礼物
	//else if( Command.wSubCmdID == SUB_GF_FLOWER )
	//{
	//	//效验参数
	//	ASSERT( sizeof(CMD_GF_GiftNotify) == wDataSize );
	//	if ( sizeof(CMD_GF_GiftNotify) != wDataSize ) return false;

	//	//变量定义
	//	CMD_GF_GiftNotify * pGiftNotify=(CMD_GF_GiftNotify *)pData;

	//	//大厅房间
	//	if(pGiftNotify->cbSendLocation==LOCATION_PLAZA_ROOM)
	//	{
	//		//获取玩家
	//		IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pGiftNotify->dwSendUserID);
	//		IUserItem * pIRcvUserItem=m_ClientUserManager.SearchUserByUserID(pGiftNotify->dwRcvUserID);

	//		ASSERT( pISendUserItem != NULL && pIRcvUserItem != NULL );
	//		if ( pISendUserItem == NULL || pIRcvUserItem == NULL ) return true;

	//		tagUserData const *pSendUserData = pISendUserItem->GetUserData();
	//		tagUserData const *pRcvUserData = pIRcvUserItem->GetUserData();

	//		//结果判断
	//		ASSERT( pSendUserData != NULL && pRcvUserData != NULL );
	//		if ( pSendUserData == NULL || pRcvUserData == NULL ) return true;
	//		ASSERT( pGiftNotify->wGiftID < FLOWER_COUNT ) ;
	//		if ( pGiftNotify->wGiftID >= FLOWER_COUNT ) return true;

	//		//构造消息
	//		CString strGiftMsg;
	//		int nFlowerID = pGiftNotify->wGiftID;

	//		strGiftMsg.Format(TEXT("[%s]"),pSendUserData->szName);
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(0,0,255), strGiftMsg.GetLength(), false);

	//		strGiftMsg = g_FlowerDescribe[nFlowerID].szAction;
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), false);

	//		strGiftMsg.Format(TEXT("[%s]"),pRcvUserData->szName);
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(0,0,255),strGiftMsg.GetLength(),false);

	//		strGiftMsg = g_FlowerDescribe[nFlowerID].szQuantifier1;
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), false);

	//		//插入图片
	//		CBitmap Bitmap;
	//		AfxSetResourceHandle(GetResInstanceHandle());
	//		if ( Bitmap.LoadBitmap(g_GlobalUnits.m_ChatExpViewImage.uChatGift[nFlowerID]) )
	//		{
	//			m_MessageProxyHelper->InsertImage(&Bitmap);
	//			Bitmap.DeleteObject();
	//		}
	//		AfxSetResourceHandle(GetModuleHandle(NULL));

	//		WORD wFlowerCount = pGiftNotify->wFlowerCount;
	//		strGiftMsg.Format(TEXT("，共%d%s%s[ %s ]"), pGiftNotify->wFlowerCount, g_FlowerDescribe[nFlowerID].szQuantifier2,
	//			g_FlowerDescribe[nFlowerID].szResult, pRcvUserData->szName);
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), false);	

	//		strGiftMsg.Format(g_FlowerDescribe[nFlowerID].szCharmResult, wFlowerCount * abs(CPropertyBar::m_FlowerInfo[nFlowerID].lRcvUserCharm));
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), true);	
	//	}

	//}

	return true;
}

//用户进入
bool CGameRoomSocket::OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;

	//读取基本信息
	tagUserData UserData;
	memset(&UserData,0,sizeof(UserData));
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pData;

	//读取信息
	UserData.dwUserID=pUserInfoHead->dwUserID;
	UserData.wTableID=pUserInfoHead->wTableID;
	UserData.wChairID=pUserInfoHead->wChairID;
	UserData.cbUserStatus=pUserInfoHead->cbUserStatus;
	UserData.dwUserRight=pUserInfoHead->dwUserRight;
	UserData.dwMasterRight=pUserInfoHead->dwMasterRight;
	//UserData.lInsureScore = pUserInfoHead->lInsureScore;

	//管理判断
	if ((pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID)&&(pUserInfoHead->cbMasterOrder>=2))
	{
		m_cbHideUserInfo=FALSE;
	}

	//读取信息
	if ((m_cbHideUserInfo==FALSE)||(pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID))
	{
		UserData.wFaceID=pUserInfoHead->wFaceID;
		UserData.dwCustomFaceVer=pUserInfoHead->dwCustomFaceVer;
		UserData.cbGender=pUserInfoHead->cbGender;
		UserData.cbMemberOrder=pUserInfoHead->cbMemberOrder;
		UserData.cbMasterOrder=pUserInfoHead->cbMasterOrder;
		UserData.dwGameID=pUserInfoHead->dwGameID;
		UserData.dwGroupID=pUserInfoHead->dwGroupID;
		UserData.lLoveliness=pUserInfoHead->lLoveliness;
		UserData.lScore=pUserInfoHead->UserScoreInfo.lScore;
		UserData.lGameGold=pUserInfoHead->UserScoreInfo.lGameGold;
		UserData.lInsureScore=pUserInfoHead->UserScoreInfo.lInsureScore;
		UserData.lWinCount=pUserInfoHead->UserScoreInfo.lWinCount;
		UserData.lLostCount=pUserInfoHead->UserScoreInfo.lLostCount;
		UserData.lDrawCount=pUserInfoHead->UserScoreInfo.lDrawCount;
		UserData.lFleeCount=pUserInfoHead->UserScoreInfo.lFleeCount;
		UserData.lExperience=pUserInfoHead->UserScoreInfo.lExperience;
	}

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
				if ((m_cbHideUserInfo==FALSE)||(pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID))
				{
					ASSERT(pDataBuffer!=NULL);
					ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szName));
					if (DataDescribe.wDataSize<=sizeof(UserData.szName))
					{
						CopyMemory(&UserData.szName,pDataBuffer,DataDescribe.wDataSize);
						UserData.szName[CountArray(UserData.szName)-1]=0;
					}
				}
				else
				{
					lstrcpyn(UserData.szName,TEXT("游戏用户"),CountArray(UserData.szName));
				}
				break;
			}
		case DTP_UNDER_WRITE:		//个性签名
			{
				if ((m_cbHideUserInfo==FALSE)||(pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID))
				{
					ASSERT(pDataBuffer!=NULL);
					ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite));
					if (DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite))
					{
						CopyMemory(&UserData.szUnderWrite,pDataBuffer,DataDescribe.wDataSize);
						UserData.szUnderWrite[CountArray(UserData.szUnderWrite)-1]=0;
					}
				}
				break;
			}
		case DTP_USER_GROUP_NAME:	//用户社团
			{
				if ((m_cbHideUserInfo==FALSE)||(pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID))
				{
					ASSERT(pDataBuffer!=NULL);
					ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szGroupName));
					if (DataDescribe.wDataSize<=sizeof(UserData.szGroupName))
					{
						CopyMemory(&UserData.szGroupName,pDataBuffer,DataDescribe.wDataSize);
						UserData.szGroupName[CountArray(UserData.szGroupName)-1]=0;
					}
				}
				break;
			}
		}
	}

	//查找用户
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(UserData.dwUserID);
	if (pIUserItem==NULL) 
	{
		const tagCompanionItem * pCompanionItem=NULL;
		pCompanionItem=g_GlobalUnits.m_CompanionManager->SearchCompanionItem(UserData.dwUserID);
		if (pCompanionItem!=NULL) UserData.cbCompanion=pCompanionItem->Companion;
		pIUserItem=m_ClientUserManager.ActiveUserItem(UserData);
	}
	//else
	//	OnUserItemUpdate(pIUserItem);

	//加入用户信息
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem!=NULL)
	{
		//判断自己
		if (m_pMeUserItem==NULL)
			m_pMeUserItem=pIUserItem;

		//设置界面
		BYTE cbUserStatus=UserData.cbUserStatus;
		//if ((cbUserStatus>=US_SIT)&&(cbUserStatus!=US_LOOKON))
		//	m_TableFrame.SetUserInfo(UserData.wTableID,UserData.wChairID,pIUserItem);

		////提示信息
		//if ((m_cbHideUserInfo==FALSE)&&(m_ServiceStatus==ServiceStatus_Serviceing))
		//{
		//	if ((UserData.cbCompanion==enCompanion_Friend)||(UserData.dwMasterRight!=0L))
		//	{
		//		TCHAR szMessage[256]=TEXT("");
		//		_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] 进来了"),UserData.szName);
		//		m_MessageProxyHelper->InsertSystemString(szMessage,0);
		//	}
		//	else if (g_GlobalOption.m_bShowInOutMessage==true)
		//	{
		//		TCHAR szMessage[256]=TEXT("");
		//		_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] 进来了"),UserData.szName);
		//		m_MessageProxyHelper->InsertGeneralString(szMessage,0,0,true);
		//	}
		//}
	}

	////自定头像
	//if(UserData.dwCustomFaceVer!=0)
	//{
	//	//头像名称
	//	CString strDirName = CString(g_GlobalUnits.GetWorkDirectory()) + TEXT("\\CustomFace");
	//	CString strFileName;
	//	strFileName.Format(TEXT("\\%ld_%d.bmp"), pUserInfoHead->dwUserID, pUserInfoHead->dwCustomFaceVer);

	//	//读取文件
	//	CImage FaceImage;
	//	HRESULT hResult = FaceImage.Load(strDirName + strFileName);
	//	if (SUCCEEDED(hResult))
	//	{
	//		FaceImage.Destroy();
	//	}
	//	//下载头像
	//	else
	//	{
	//		//投递消息
	//		CPlazaViewItem *pPlazaViewItem = ((CGameFrame *)AfxGetMainWnd())->GetPlazaViewItem();
	//		pPlazaViewItem->PostMessage(WM_DOWN_LOAD_FACE, LPARAM(pUserInfoHead->dwCustomFaceVer), WPARAM(pUserInfoHead->dwUserID));
	//	}
	//}

	//更新人数
	DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
	g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);

	return true;
}

//用户状态
bool CGameRoomSocket::OnSocketSubStatus(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_STATUS);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserStatus));
	if (wDataSize<sizeof(CMD_GR_UserStatus)) return false;

	//处理数据
	CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pData;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserStatus->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//定义变量
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	WORD wNowTableID=pUserStatus->wTableID,wLastTableID=pUserData->wTableID;
	WORD wNowChairID=pUserStatus->wChairID,wLastChairID=pUserData->wChairID;
	BYTE cbNowStatus=pUserStatus->cbUserStatus,cbLastStatus=pUserData->cbUserStatus;

	//清理旧状态
	if ((wLastTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		ASSERT(wLastChairID!=INVALID_CHAIR);
		//IUserItem * pITableUserItem=m_TableFrame.GetUserInfo(wLastTableID,wLastChairID);
		//if (pITableUserItem==pIUserItem) m_TableFrame.SetUserInfo(wLastTableID,wLastChairID,NULL);
	}

	//用户离开
	if (cbNowStatus==US_NULL)
	{
		//通知游戏
		if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID))
		{
			IPC_UserStatus UserStatus;
			memset(&UserStatus,0,sizeof(UserStatus));
			UserStatus.dwUserID=pUserData->dwUserID;
			UserStatus.cbUserStatus=pUserData->cbUserStatus;
			SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
		}

		//删除用户
		m_ClientUserManager.DeleteUserItem(pIUserItem);

		//更新人数
		DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
		g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);

		return true;
	}

	//更新状态
	tagUserStatus UserStatus;
	UserStatus.wTableID=wNowTableID;
	UserStatus.wChairID=wNowChairID;
	UserStatus.cbUserStatus=cbNowStatus;
	m_ClientUserManager.UpdateUserItemStatus(pIUserItem,&UserStatus);

	//设置新状态
	if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//设置桌子
		if (cbNowStatus!=US_LOOKON)
		{
			ASSERT(wNowChairID!=INVALID_CHAIR);
		//	m_TableFrame.SetUserInfo(wNowTableID,wNowChairID,pIUserItem);
		}

		//发送用户
		if ((m_pMeUserItem!=pIUserItem)&&(pMeUserData->wTableID==wNowTableID))
		{
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_pWnd->m_hWnd);
			SendTableUser(pIUserItem,&SendCopyData);
		}
	}

	//更新界面
	if ((wNowTableID!=INVALID_TABLE)&&(cbNowStatus!=US_LOOKON)
		&&(wNowTableID==wLastTableID)&&(wNowChairID==wLastChairID))
	{
		ASSERT(wNowChairID!=INVALID_CHAIR);
		//m_TableFrame.UpdateTableView(wNowTableID,false);
	}

	//判断发送
	bool bNotifyGame=false;
	if (pIUserItem==m_pMeUserItem) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wNowTableID)) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID)) bNotifyGame=true;

	//发送状态
	if (bNotifyGame==true)
	{
		IPC_UserStatus UserStatus;
		memset(&UserStatus,0,sizeof(UserStatus));
		UserStatus.dwUserID=pUserData->dwUserID;
		UserStatus.cbUserStatus=pUserData->cbUserStatus;
		SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
	}

	//判断自己
	if (pIUserItem==m_pMeUserItem)
	{
		//设置变量
		if ((wNowTableID==m_wReqTableID)&&(wNowChairID==m_wReqChairID))
		{
			m_wReqTableID=INVALID_TABLE;
			m_wReqChairID=INVALID_CHAIR;
		}

		//缓冲清理
		if ((m_wPacketTableID!=INVALID_TABLE)&&((m_wPacketTableID!=wNowTableID)||(m_wPacketChairID!=wNowChairID)))
		{
			m_wPacketTableID=INVALID_TABLE;
			m_wPacketChairID=INVALID_CHAIR;
			m_PacketDataStorage.RemoveData(false);
		}

		//启动游戏
		if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
		{
			int iResult=StartGameClient();
		}
	}

	return true;
}

//用户分数
bool CGameRoomSocket::OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;

	//处理数据
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pData;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserScore->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//更新判断
	if ((m_cbHideUserInfo==FALSE)||(pIUserItem==m_pMeUserItem))
	{
		//更新分数
		tagUserData * pUserData=pIUserItem->GetUserData();
		pUserData->lLoveliness = pUserScore->lLoveliness;
		pUserData->lGameGold = pUserScore->UserScore.lGameGold;
		pUserData->lInsureScore = pUserScore->UserScore.lInsureScore;
		m_ClientUserManager.UpdateUserItemScore(pIUserItem,&pUserScore->UserScore);

		//更新游戏
		tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
		if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==pUserData->wTableID))
		{
			IPC_UserScore UserScore;
			memset(&UserScore,0,sizeof(UserScore));
			UserScore.dwUserID=pUserScore->dwUserID;
			UserScore.UserScore=pUserScore->UserScore;
			UserScore.lLoveliness = pUserScore->lLoveliness;
			SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_SCORE,&UserScore,sizeof(UserScore));
		}
	}

	return true;
}

//用户权限
bool CGameRoomSocket::OnSocketSubRight(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_RIGHT);
	ASSERT(wDataSize==sizeof(CMD_GR_UserRight));
	if (wDataSize!=sizeof(CMD_GR_UserRight)) return false;

	//消息处理
	CMD_GR_UserRight * pUserRight=(CMD_GR_UserRight *)pData;

	//用户权限
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserRight->dwUserID);
	pIUserItem->GetUserData()->dwUserRight = pUserRight->dwUserRight;

	return true;
}

//会员等级
bool CGameRoomSocket::OnSocketSubMemberOrder(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_MEMBER_ORDER);
	ASSERT(wDataSize==sizeof(CMD_GR_MemberOrder));
	if (wDataSize!=sizeof(CMD_GR_MemberOrder)) return false;

	//消息处理
	CMD_GR_MemberOrder * pMemberOrder=(CMD_GR_MemberOrder *)pData;

	//会员等级
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pMemberOrder->dwUserID);
	tagUserData * pUserData=pIUserItem->GetUserData();
	pUserData->cbMemberOrder = pMemberOrder->cbMemberOrder;
	tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();
	GlobalUserInfo.cbMember = pMemberOrder->cbMemberOrder;

	//更新游戏
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==pUserData->wTableID))
	{
		IPC_MemberOrder MemberOrder;
		memset(&MemberOrder,0,sizeof(MemberOrder));
		MemberOrder.dwUserID=pUserData->dwUserID;
		MemberOrder.cbMemberOrder=pUserData->cbMemberOrder;
		SendProcessData(IPC_MAIN_USER,IPC_SUB_MEMBERORDER,&MemberOrder,sizeof(MemberOrder));
	}

	return true;
}

//坐下失败
bool CGameRoomSocket::OnSocketSubSitFailed(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_SIT_FAILED);

	//消息处理
	CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pData;
	//IUserItem * pISendUserItem=m_TableFrame.GetUserInfo(m_wReqTableID,m_wReqChairID);
	//if (pISendUserItem==m_pMeUserItem) m_TableFrame.SetUserInfo(m_wReqTableID,m_wReqChairID,NULL);

	//设置变量
	m_wReqTableID=INVALID_TABLE;
	m_wReqChairID=INVALID_CHAIR;

	//显示消息
	ShowMessageBox(pSitFailed->szFailedDescribe,MB_ICONINFORMATION);

	return true;
}

//用户聊天
bool CGameRoomSocket::OnSocketSubChat(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_CHAT);

	//效验参数
	CMD_GR_UserChat * pUserChat=(CMD_GR_UserChat *)pData;
	ASSERT(wDataSize>=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)));
	ASSERT(wDataSize==(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength));
	if (wDataSize<(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage))) return false;
	if (wDataSize!=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength)) return false;

	//寻找用户
	IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pUserChat->dwSendUserID);
	if (pISendUserItem==NULL) return true;
	tagUserData * pSendUserData=pISendUserItem->GetUserData();

	//消息过滤
	if ((pISendUserItem!=m_pMeUserItem)&&(pSendUserData->cbCompanion==enCompanion_Detest)) return true;

	//显示消息
	//if (pUserChat->dwTargetUserID!=0L)
	//{
	//	IUserItem * pIRecvUserItem=m_ClientUserManager.SearchUserByUserID(pUserChat->dwTargetUserID);
	//	if (pIRecvUserItem==NULL) return true;
	//	tagUserData * pRecvUserData=pIRecvUserItem->GetUserData();
	//	m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pRecvUserData->szName,pUserChat->szChatMessage,pUserChat->crFontColor,MS_NORMAL);
	//}
	//else m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pUserChat->szChatMessage,pUserChat->crFontColor,MS_NORMAL);

	return true;
}

//用户私语
bool CGameRoomSocket::OnSocketSubWisper(CMD_Command Command, void * pData, WORD wDataSize)
{
	////效验参数
	//ASSERT(Command.wMainCmdID==MDM_GR_USER);
	//ASSERT(Command.wSubCmdID==SUB_GR_USER_WISPER);

	////效验参数
	//CMD_GR_Wisper * pWisper=(CMD_GR_Wisper *)pData;
	//ASSERT(wDataSize>=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)));
	//ASSERT(wDataSize==(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength));
	//if (wDataSize<(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage))) return false;
	//if (wDataSize!=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength)) return false;

	////寻找用户
	//IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pWisper->dwSendUserID);
	//IUserItem * pIRecvUserItem=m_ClientUserManager.SearchUserByUserID(pWisper->dwTargetUserID);
	//if ((pISendUserItem==NULL)||(pIRecvUserItem==NULL)) return true;
	//tagUserData * pUserDataSend=pISendUserItem->GetUserData();
	//tagUserData * pUserDataRecv=pIRecvUserItem->GetUserData();

	////消息过滤
	//if ((pUserDataSend->cbMasterOrder==0) && (pISendUserItem!=m_pMeUserItem)&&(pUserDataSend->cbCompanion==enCompanion_Detest)) return true;

	////显示信息
	//CShortMessage * pShortMessageWnd=NULL;
	//if (pWisper->dwSendUserID==m_pMeUserItem->GetUserID())
	//{
	//	//自己发送的消息
	//	pShortMessageWnd=ActiveShortWnd(pWisper->dwTargetUserID,pIRecvUserItem,true);
	//	if (pShortMessageWnd!=NULL) pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,true);
	//}
	//else	//其他游戏者发送信息
	//{
	//	pShortMessageWnd=ActiveShortWnd(pWisper->dwSendUserID,pISendUserItem,true);
	//	if (pShortMessageWnd!=NULL)	
	//		pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,false);
	//}

	return true;
}

//用户邀请
bool CGameRoomSocket::OnSocketSubUserInvite(CMD_Command Command, void * pData, WORD wDataSize)
{
	////效验参数
	//ASSERT(Command.wMainCmdID==MDM_GR_USER);
	//ASSERT(Command.wSubCmdID==SUB_GR_USER_INVITE);

	////效验参数
	//ASSERT(wDataSize==sizeof(CMD_GR_UserInvite));
	//if (wDataSize!=sizeof(CMD_GR_UserInvite)) return false;

	////消息处理
	//CMD_GR_UserInvite * pUserInvite=(CMD_GR_UserInvite *)pData;
	//ASSERT(pUserInvite->wTableID<m_TableFrame.GetTableCount());
	//if (m_TableFrame.QueryPlayFlag(pUserInvite->wTableID)==true) return true;

	////寻找用户
	//IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserInvite->dwUserID);
	//if (pIUserItem==NULL) return true;
	//tagUserData * pUserData=pIUserItem->GetUserData();
	//if (pUserData->wTableID==INVALID_TABLE) return true;

	////用户过虑
	//if (pUserData->cbCompanion==enCompanion_Detest) return true;
	//if (g_GlobalOption.m_InviteMode==enInviteMode_None) return true;
	//if ((g_GlobalOption.m_InviteMode==enInviteMode_Friend)&&(pUserData->cbCompanion!=enCompanion_Friend)) return true;

	////提示消息
	//TCHAR szMessage[256]=TEXT("");
	//_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] 邀请你加入第 [ %ld ] 游戏桌进行游戏，是否同意？"),pUserData->szName,pUserInvite->wTableID+1);
	//if (ShowMessageBox(szMessage,MB_ICONINFORMATION|MB_YESNO)==IDYES)
	//{
	//	WORD wChairID=INVALID_CHAIR;
	//	WORD wNullCount=m_TableFrame.GetNullChairCount(pUserInvite->wTableID,wChairID);
	//	if (wNullCount==0) 
	//	{
	//		ShowMessageBox(TEXT("此游戏桌已经没有空位置了！"),MB_ICONINFORMATION);
	//		return true;
	//	}
	//	PerformSitDownAction(pUserInvite->wTableID,wChairID);
	//}

	return true;
}


//IPC 内核命令
bool CGameRoomSocket::OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MIAN_IPC_KERNEL);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_IPC_CLIENT_CONNECT:	//连接消息
		{
			//判断连接
			if (::IsChild(m_pShareMemory->hWndGameFrame,hWndSend)) return false;

			//设置变量
			ASSERT(m_hWndChannel==NULL);
			m_hWndChannel=hWndSend;

			//发送信息
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_pWnd->m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			//缓冲数据
			if ((m_wPacketTableID!=INVALID_TABLE)&&(m_wPacketChairID!=INVALID_CHAIR))
			{
				//变量定义
				tagDataHead DataHead;
				ZeroMemory(&DataHead,sizeof(DataHead));

				//变量定义
				BYTE cbBuffer[SOCKET_BUFFER];
				IPC_SocketPackage SocketPackage;
				ZeroMemory(cbBuffer,sizeof(cbBuffer));
				ZeroMemory(&SocketPackage,sizeof(SocketPackage));

				//提取数据
				do
				{
					//获取负荷
					tagBurthenInfo BurthenInfo;
					m_PacketDataStorage.GetBurthenInfo(BurthenInfo);

					//提取数据
					if (BurthenInfo.dwDataPacketCount==0L) break;
					if (m_PacketDataStorage.DistillData(DataHead,cbBuffer,sizeof(cbBuffer))==false) break;

					//构造数据
					CopyMemory(&SocketPackage.Command,cbBuffer,sizeof(CMD_Command));
					CopyMemory(SocketPackage.cbBuffer,&cbBuffer[sizeof(CMD_Command)],DataHead.wDataSize-sizeof(CMD_Command));

					//数据处理
					SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,DataHead.wDataSize);

				} while (true);

				//设置变量
				m_wPacketTableID=INVALID_TABLE;
				m_wPacketChairID=INVALID_CHAIR;
			}

			////属性数据
			//IPC_SocketPackage SocketPackage;
			//ZeroMemory(&SocketPackage,sizeof(SocketPackage));
			//WORD wSendSize=0;

			////设置消息
			//SocketPackage.Command.wMainCmdID = MDM_GF_PRESENT;
			//SocketPackage.Command.wSubCmdID = SUB_GF_PROP_ATTRIBUTE;

			////道具属性
			//for (INT_PTR nIndex =0; nIndex < m_PropertyAttributeArrary.GetCount(); ++nIndex)
			//{
			//	if ((wSendSize+sizeof(tagPropertyInfo))>SOCKET_PACKET)
			//	{
			//		SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize+sizeof(CMD_Command));
			//		wSendSize=0;
			//	}
			//	tagPropertyInfo &PropertyInfo = m_PropertyAttributeArrary[nIndex];
			//	CopyMemory(SocketPackage.cbBuffer+wSendSize,&PropertyInfo,sizeof(PropertyInfo));
			//	wSendSize+=sizeof(PropertyInfo);
			//}
			//if (wSendSize>0) 
			//	SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize+sizeof(CMD_Command));

			////设置消息
			//SocketPackage.Command.wSubCmdID = SUB_GF_FLOWER_ATTRIBUTE;

			////鲜花属性
			//wSendSize=0L;
			//for (INT_PTR nIndex =0; nIndex < m_FlowerAttributeArrary.GetCount(); ++nIndex)
			//{
			//	if ((wSendSize+sizeof(tagFlowerInfo))>SOCKET_PACKET)
			//	{
			//		SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize+sizeof(CMD_Command));
			//		wSendSize=0;
			//	}
			//	tagFlowerInfo &FlowerInfo = m_FlowerAttributeArrary[nIndex];
			//	CopyMemory(SocketPackage.cbBuffer+wSendSize,&FlowerInfo,sizeof(FlowerInfo));
			//	wSendSize+=sizeof(FlowerInfo);
			//}
			//if (wSendSize>0) 
			//	SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize+sizeof(CMD_Command));

			return true;
		}
	case IPC_SUB_IPC_CLIENT_CLOSE:		//关闭消息
		{
			//判断连接
			if (hWndSend!=m_hWndChannel) return false;

			//发送消息
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->wTableID!=WORD(INVALID_TABLE))
			{
				if (pUserData->cbUserStatus==US_PLAY)
					SendLeftGamePacket();
				SendStandUpPacket();
			}

			//设置变量
			m_hWndChannel=NULL;
			m_pShareMemory->hWndGameFrame=NULL;
			CloseHandle(m_GameProcessInfo.hThread);
			CloseHandle(m_GameProcessInfo.hProcess);
			memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));

			return true;
		}
	}

	return false;
}

//IPC 发包命令
bool CGameRoomSocket::OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_SOCKET);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_SOCKET_SEND:	//发包消息
		{
			//效验数据
			ASSERT(wDataSize>=sizeof(CMD_Command));
			if (wDataSize<sizeof(CMD_Command)) 
			{
				return false;
			}

			//处理数据
			IPC_SocketPackage * pSocketPackage=(IPC_SocketPackage *)pIPCBuffer;
			CMD_Command *pCommand= &pSocketPackage->Command;
			WORD wSendSize=wDataSize-sizeof(CMD_Command);
			if (wSendSize==0) 
			{
				m_ClientSocket->SendData(pCommand->wMainCmdID,
					pCommand->wSubCmdID);
			}
			else 
			{
				m_ClientSocket->SendData(pCommand->wMainCmdID,pCommand->wSubCmdID,pSocketPackage->cbBuffer,wSendSize);
			}

			return true;
		}
	}

	return false;
}



bool CGameRoomSocket::InitGameRoom(CListServer * pListServer,CGameRoomManager* pMgr,CWnd* pPointer)
{
	//设置变量
	if(pListServer == NULL || pMgr == NULL ||pPointer == NULL)
	{
		ASSERT(FALSE);
		return false;
	}

	m_pListServer=pListServer;
	m_pGameRoomMgr = pMgr;
	m_pWnd = pPointer;

	//设置组件
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false) return false;
	if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) return false;
	if (m_IPCRecvCopyData.SetChannelMessageSink(pIUnknownEx)==false) return false;

	//创建共享内存
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	_snprintf(m_szShareName,sizeof(m_szShareName),TEXT("0x8%ld%ld%ld%ld"),pGameServer->dwServerAddr,pGameServer->wServerPort,time(NULL),rand()%100);
	m_hShareMemory=(HANDLE)CreateFileMapping((HANDLE)0xFFFFFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(tagShareMemory),m_szShareName);
	if ((m_hShareMemory==NULL)||(GetLastError()==ERROR_ALREADY_EXISTS)) return false;
	m_pShareMemory=(tagShareMemory *)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,0,0,0);

	//设置共享内存
	memset(m_pShareMemory,0,sizeof(tagShareMemory));
	m_pShareMemory->wDataSize=sizeof(tagShareMemory);
	m_pShareMemory->hWndGameServer=m_pWnd->m_hWnd;
	m_pShareMemory->hWndGamePlaza=AfxGetMainWnd()->m_hWnd;

	return true;
}


//连接服务器
bool CGameRoomSocket::ConnectGameServer()
{
	m_ServiceStatus=ServiceStatus_Connecting;
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	return (m_ClientSocket->Connect(pGameServer->dwServerAddr,pGameServer->wServerPort)==CONNECT_SUCCESS);
}

//类型信息
tagGameKind * __cdecl CGameRoomSocket::GetKindInfo()
{
	if (m_pListServer!=NULL)
	{
		CListKind * pListKind=m_pListServer->GetListKind();
		ASSERT(pListKind!=NULL);
		if (pListKind!=NULL)
		{
			return pListKind->GetItemInfo();
		}
	}
	return NULL;
}

//显示消息
int CGameRoomSocket::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	int nResult=ShowInformationEx(pszMessage,0,nType,"游戏房间");
	return nResult;
}

//发送信息
void CGameRoomSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}


//发送消息
bool CGameRoomSocket::SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//发送消息
	CIPCSendCopyData IPCSendCopyData(m_hWndChannel,m_pWnd->m_hWnd);
	return IPCSendCopyData.SendData(wMainCmdID,wSubCmdID,pData,wDataSize);
}

//发送登录包
bool CGameRoomSocket::SendLogonPacket()
{
	//获取信息
	BYTE cbBuffer[SOCKET_PACKET];
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();

	//登录数据包
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=GlobalUserData.dwUserID;
	pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
	lstrcpyn(pLogonByUserID->szPassWord,GlobalUserData.szPassWord,sizeof(pLogonByUserID->szPassWord));

	//机器序列号
	tagClientSerial ClientSerial;
	g_GlobalUnits.GetClientSerial(ClientSerial);

	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

	return true;
}

//发送坐下命令
bool CGameRoomSocket::SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//构造数据包
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=wTableID;
	UserSitReq.wChairID=wChairID;
	lstrcpyn(UserSitReq.szTablePass,pszTablePass,sizeof(UserSitReq.szTablePass));
	UserSitReq.cbPassLen=CountStringBuffer(UserSitReq.szTablePass);

	//发送数据包
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	return true;
}

//发送旁观命令
bool CGameRoomSocket::SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//构造数据包
	CMD_GR_UserSitReq UserUserSitReq;
	memset(&UserUserSitReq,0,sizeof(UserUserSitReq));
	UserUserSitReq.wTableID=wTableID;
	UserUserSitReq.wChairID=wChairID;
	lstrcpyn(UserUserSitReq.szTablePass,pszTablePass,sizeof(UserUserSitReq.szTablePass));
	UserUserSitReq.cbPassLen=CountStringBuffer(UserUserSitReq.szTablePass);

	//发送数据包
	WORD wSendSize=sizeof(UserUserSitReq)-sizeof(UserUserSitReq.szTablePass)+UserUserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LOOKON_REQ,&UserUserSitReq,wSendSize);

	return true;
}

//发送聊天命令
bool CGameRoomSocket::SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor)
{
	//获取用户
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pUserData=m_pMeUserItem->GetUserData();

	//构造数据
	CMD_GR_UserChat UserChat;
	UserChat.crFontColor=crFontColor;
	UserChat.dwTargetUserID=dwTargetUserID;
	UserChat.dwSendUserID=pUserData->dwUserID;
	lstrcpyn(UserChat.szChatMessage,pszChatMessage,CountArray(UserChat.szChatMessage));
	UserChat.wChatLength=CountStringBuffer(UserChat.szChatMessage);

	//发送命令
	WORD wSendSize=sizeof(UserChat)-sizeof(UserChat.szChatMessage)+UserChat.wChatLength;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_CHAT,&UserChat,wSendSize);

	return true;
}

//发送起来命令
bool CGameRoomSocket::SendStandUpPacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);

	return true;
}

//发送强退命令
bool CGameRoomSocket::SendLeftGamePacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);

	return true;
}

//发送游戏信息
bool CGameRoomSocket::IPCSendGameInfo(CIPCSendCopyData * pSendCopyData)
{
	//效益参数
	ASSERT(pSendCopyData!=NULL);
	ASSERT(m_pMeUserItem!=NULL);

	//定义变量
	tagUserData * pUserData=m_pMeUserItem->GetUserData();
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();

	//构造数据
	IPC_GF_ServerInfo ServerInfo;
	memset(&ServerInfo,0,sizeof(ServerInfo));
	ServerInfo.dwUserID=pUserData->dwUserID;
	ServerInfo.wTableID=pUserData->wTableID;
	ServerInfo.wChairID=pUserData->wChairID;
	ServerInfo.wKindID=pGameKind->wKindID;
	ServerInfo.wServerID=pGameServer->wServerID;
	ServerInfo.wGameGenre=m_wGameGenre;
	ServerInfo.dwVideoAddr=m_dwVideoAddr;
	ServerInfo.cbHideUserInfo=m_cbHideUserInfo;
	ServerInfo.wChairCount=m_wChairCount;
	lstrcpyn(ServerInfo.szKindName,pGameKind->szKindName,CountArray(ServerInfo.szKindName));
	lstrcpyn(ServerInfo.szServerName,pGameServer->szServerName,CountArray(ServerInfo.szServerName));

	//发送数据
	pSendCopyData->SendData(IPC_MAIN_CONFIG,IPC_SUB_SERVER_INFO,&ServerInfo,sizeof(ServerInfo));

	return true;
}

//发送用户
bool CGameRoomSocket::IPCSendTableUsers(CIPCSendCopyData * pSendCopyData)
{
	//效益参数
	ASSERT(pSendCopyData!=NULL);

	//发送自己信息
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	ASSERT(pMeUserData->wTableID!=(WORD)INVALID_TABLE);
	if (pMeUserData->wTableID==(WORD)INVALID_TABLE) return false;
	SendTableUser(m_pMeUserItem,pSendCopyData);

	//发送其他用户
	IUserItem * pIUserItem=NULL;
	tagUserData * pUserData=NULL;

	//游戏用户
	WORD wEnumIndex=0;
	while (true)
	{
		pIUserItem=m_ClientUserManager.EnumUserItem(wEnumIndex++);
		if (pIUserItem==NULL) break;
		if (pIUserItem==m_pMeUserItem) continue;
		pUserData=pIUserItem->GetUserData();
		if ((pUserData->wTableID==pMeUserData->wTableID)&&(pUserData->cbUserStatus!=US_LOOKON))
			SendTableUser(pIUserItem,pSendCopyData);
	};

	//旁观用户
	wEnumIndex=0;
	while (true)
	{
		pIUserItem=m_ClientUserManager.EnumUserItem(wEnumIndex++);
		if (pIUserItem==NULL) break;
		if (pIUserItem==m_pMeUserItem) continue;
		pUserData=pIUserItem->GetUserData();
		if ((pUserData->wTableID==pMeUserData->wTableID)&&(pUserData->cbUserStatus==US_LOOKON))
			SendTableUser(pIUserItem,pSendCopyData);
	};

	return true;
}
//发送用户
bool CGameRoomSocket::SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData)
{
	//效验参数
	ASSERT(pIUserItem!=NULL);
	ASSERT(pSendCopyData!=NULL);

	//定义变量
	BYTE cbBuffer[IPC_PACKAGE];
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)cbBuffer;

	//构造数据
	memset(cbBuffer,0,sizeof(cbBuffer));
	pUserInfoHead->dwUserID=pUserData->dwUserID;
	pUserInfoHead->dwGameID=pUserData->dwGameID;
	pUserInfoHead->dwGroupID=pUserData->dwGroupID;
	pUserInfoHead->dwUserRight=pUserData->dwUserRight;
	pUserInfoHead->lLoveliness=pUserData->lLoveliness;
	pUserInfoHead->dwMasterRight=pUserData->dwMasterRight;
	pUserInfoHead->wFaceID=pUserData->wFaceID;
	pUserInfoHead->dwCustomFaceVer=pUserData->dwCustomFaceVer;
	pUserInfoHead->wTableID=pUserData->wTableID;
	pUserInfoHead->wChairID=pUserData->wChairID;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbUserStatus=pUserData->cbUserStatus;
	pUserInfoHead->cbMemberOrder=pUserData->cbMemberOrder;
	pUserInfoHead->cbMasterOrder=pUserData->cbMasterOrder;
	pUserInfoHead->UserScoreInfo.lScore=pUserData->lScore;
	pUserInfoHead->UserScoreInfo.lGameGold=pUserData->lGameGold;
	pUserInfoHead->UserScoreInfo.lInsureScore=pUserData->lInsureScore;
	pUserInfoHead->UserScoreInfo.lWinCount=pUserData->lWinCount;
	pUserInfoHead->UserScoreInfo.lLostCount=pUserData->lLostCount;
	pUserInfoHead->UserScoreInfo.lDrawCount=pUserData->lDrawCount;
	pUserInfoHead->UserScoreInfo.lFleeCount=pUserData->lFleeCount;
	pUserInfoHead->UserScoreInfo.lExperience=pUserData->lExperience;
	//pUserInfoHead->lInsureScore = pUserData->lInsureScore;
	for ( WORD wPropID = 0; wPropID < PROPERTY_COUNT; ++wPropID )
	{
		pUserInfoHead->dwPropResidualTime[wPropID] = pUserData->dwPropResidualTime[wPropID];
	}

	//叠加数据
	WORD wHeadSize=sizeof(tagUserInfoHead);
	CSendPacketHelper SendPacketHelper(cbBuffer+wHeadSize,sizeof(cbBuffer)-wHeadSize);
	SendPacketHelper.AddPacket(pUserData->szName,CountStringBuffer(pUserData->szName),DTP_USER_ACCOUNTS);
	SendPacketHelper.AddPacket(&pUserData->cbCompanion,sizeof(pUserData->cbCompanion),DTP_USER_COMPANION);
	SendPacketHelper.AddPacket(pUserData->szUnderWrite,CountStringBuffer(pUserData->szUnderWrite),DTP_UNDER_WRITE);
	SendPacketHelper.AddPacket(pUserData->szGroupName,CountStringBuffer(pUserData->szGroupName),DTP_USER_GROUP_NAME);

	//发送数据
	WORD wSendSize=wHeadSize+SendPacketHelper.GetDataSize();
	pSendCopyData->SendData(IPC_MAIN_USER,IPC_SUB_USER_COME,cbBuffer,wSendSize);

	return true;
}

//启动游戏
int CGameRoomSocket::StartGameClient()
{
	//判断是否已经启动
	ASSERT(m_pShareMemory!=NULL);
	if ((m_GameProcessInfo.hProcess!=NULL)&&(WaitForSingleObject(m_GameProcessInfo.hProcess,0)==WAIT_TIMEOUT))
	{
		if (m_pShareMemory->hWndGameFrame!=NULL)
		{
			//显示窗口
			::ShowWindow(m_pShareMemory->hWndGameFrame,SW_SHOW);
			::SetForegroundWindow(m_pShareMemory->hWndGameFrame);

			//发送信息
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_pWnd->m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			return SR_ALREADY_EXIST;
		}
		else ::TerminateProcess(m_GameProcessInfo.hProcess,0);
	}

	//清理数据
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(m_GameProcessInfo.hThread);
	CloseHandle(m_GameProcessInfo.hProcess);
	memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));

	//构造命令行
	CString strCommonLine;
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	strCommonLine.Format(TEXT("%s /RoomToken:%s /ServerType:%ld /HideUserInfo:%d"),pGameKind->szProcessName,m_szShareName,m_wGameGenre,m_cbHideUserInfo);

	//启动游戏客户端
	STARTUPINFO StartInfo;
	memset(&StartInfo,0,sizeof(StartInfo));
	StartInfo.cb=sizeof(StartInfo);
	StartInfo.wShowWindow=SW_SHOWMAXIMIZED;
	BOOL bSuccess=CreateProcess(NULL,strCommonLine.GetBuffer(),NULL,NULL,FALSE,CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&StartInfo,&m_GameProcessInfo);
	strCommonLine.ReleaseBuffer();
	if (bSuccess==FALSE)
	{
		memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));
		return SR_CREATE_ERROR;
	}

	return SR_CREATE_SUCCESS;
}

//关闭游戏
void CGameRoomSocket::CloseGameClient()
{
	//发送消息
	if (m_GameProcessInfo.hProcess!=NULL)
	{
		SendProcessData(IPC_MAIN_CONCTROL,IPC_SUB_CLOSE_FRAME,NULL,0);
		DWORD dwResult=::WaitForSingleObject(m_GameProcessInfo.hProcess,1000);
		if (dwResult==WAIT_TIMEOUT) ::TerminateProcess(m_GameProcessInfo.hProcess,0);
	}

	//清理数据
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(m_GameProcessInfo.hThread);
	CloseHandle(m_GameProcessInfo.hProcess);
	memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));

	return;
}

