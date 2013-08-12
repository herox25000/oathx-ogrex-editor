#include "StdAfx.h"
#include "gameroomsocket.h"
#include "GameRoomManager.h"

CGameRoomSocket::CGameRoomSocket(void)
{
	m_pGameRoomMgr = NULL;
	m_pListServer = NULL;
}

CGameRoomSocket::~CGameRoomSocket(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CGameRoomSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE(IChannelMessageSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//�����¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if (nErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());
		ShowInformationEx(TEXT("��Ϸ��������ʧ�ܣ�����ʱ���ܽ������Ϸ���䣡"),0,MB_ICONINFORMATION,"����");
		m_pGameRoomMgr->QuitRoom();
		return true;
	}

	//���͵�¼��Ϣ
	SendLogonPacket();
	m_ServiceStatus=ServiceStatus_EfficacyUser;

	return true;
}
//�ر��¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//�жϹر�
	bool bCloseRoomView=(m_ServiceStatus!=ServiceStatus_Serviceing && cbShutReason != SHUT_REASON_NORMAL);

	//�رմ���
	CloseGameClient();
	g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());
	m_ServiceStatus=ServiceStatus_NetShutDown;
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			ShowMessageBox("�����������⣬���Ѿ���������Ͽ����ӣ�����������",MB_ICONINFORMATION);
		}
		else
		{
			ShowMessageBox("�����������ݰ�����ʧ�ܣ������ж���",MB_ICONINFORMATION);
		}
	}

	//�رշ���
	if (bCloseRoomView==true)
		m_pGameRoomMgr->QuitRoom();
	return true;
}
//��ȡ�¼�
bool __cdecl CGameRoomSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
		{
			return OnSocketMainLogon(Command,pData,wDataSize);
		}
	case MDM_GR_USER:			//�û���Ϣ
		{
			return OnSocketMainUser(Command,pData,wDataSize);
		}
	case MDM_GR_INFO:			//������Ϣ
		{
			return OnSocketMainInfo(Command,pData,wDataSize);
		}
	case MDM_GR_STATUS:			//״̬��Ϣ
		{
			return OnSocketMainStatus(Command,pData,wDataSize);
		}
	case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
		{
			return OnSocketMainSystem(Command,pData,wDataSize);
		}
	case MDM_GR_SERVER_INFO:	//������Ϣ
		{
			return OnSocketMainServerInfo(Command,pData,wDataSize);
		}
	case MDM_GF_GAME:			//��Ϸ��Ϣ
	case MDM_GF_FRAME:			//�����Ϣ
	case MDM_GF_VIDEO:			//��Ƶ��Ϣ
	case MDM_GF_PRESENT:		//������Ϣ
		{
			return OnSocketMainGameFrame(Command,pData,wDataSize);
		}
	}

	return true;
}
//�ŵ����ݴ���
bool __cdecl CGameRoomSocket::OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	switch (pHead->wMainCmdID)
	{
	case IPC_MIAN_IPC_KERNEL:		//�ں���Ϣ
		{
			return OnIPCKernel(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_SOCKET:			//�����¼�
		{
			return OnIPCSocket(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_CONCTROL:			//������Ϣ
		{
			return true;
		}
	}
	return false;
}

//��¼��Ϣ
bool CGameRoomSocket::OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//��¼�ɹ�
		{
			//���ñ���
			m_ServiceStatus=ServiceStatus_RecvConfigInfo;
			return true;
		}
	case SUB_GR_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pData;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());
			m_ClientSocket->CloseSocket();
			m_ServiceStatus=ServiceStatus_NetShutDown;

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}

			//�رշ���
			m_pGameRoomMgr->QuitRoom();

			return true;
		}
	case SUB_GR_LOGON_FINISH:		//��¼���
		{
			//���ý���
			g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());
			//���ñ���
			m_ServiceStatus=ServiceStatus_Serviceing;

			//���͹���
			//SendUserRulePacket();

			//�����ж�
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

//�û���Ϣ
bool CGameRoomSocket::OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//�û�����
		{
			return OnSocketSubUserCome(Command,pData,wDataSize);
		}
	case SUB_GR_USER_STATUS:		//�û�״̬
		{
			return OnSocketSubStatus(Command,pData,wDataSize);
		}
	case SUB_GR_USER_SCORE:			//�û�����
		{
			return OnSocketSubScore(Command,pData,wDataSize);
		}
	case SUB_GR_USER_RIGHT:			//�û�Ȩ��
		{
			return OnSocketSubRight(Command,pData,wDataSize);
		}
	case SUB_GR_MEMBER_ORDER:		//��Ա�ȼ�
		{
			return OnSocketSubMemberOrder(Command,pData,wDataSize);
		}
	case SUB_GR_SIT_FAILED:			//����ʧ��
		{
			return OnSocketSubSitFailed(Command,pData,wDataSize);
		}
	case SUB_GR_USER_CHAT:			//�û�����
		{
			return OnSocketSubChat(Command,pData,wDataSize);
		}
	case SUB_GR_USER_WISPER:		//�û�˽��
		{
			return OnSocketSubWisper(Command,pData,wDataSize);
		}
	case SUB_GR_USER_INVITE:		//�������
		{
			return OnSocketSubUserInvite(Command,pData,wDataSize);
		}
	}

	return true;
}


//������Ϣ
bool CGameRoomSocket::OnSocketMainInfo(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_SERVER_INFO:	//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_GR_ServerInfo));
			if (wDataSize<sizeof(CMD_GR_ServerInfo)) return false;

			//��Ϣ����
			CMD_GR_ServerInfo * pServerInfo=(CMD_GR_ServerInfo *)pData;

			//���ñ���
			m_wKindID=pServerInfo->wKindID;
			m_wTableCount = pServerInfo->wTableCount;
			m_wChairCount = pServerInfo->wChairCount;
			m_wGameGenre=pServerInfo->wGameGenre;
			m_dwVideoAddr=pServerInfo->dwVideoAddr;
			m_cbHideUserInfo=pServerInfo->cbHideUserInfo;

			//��ȡ��Ϣ
			CListKind * pListKind=m_pListServer->GetListKind();
			tagGameKind * pGameKind=pListKind->GetItemInfo();
			IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);


			//��������
			try
			{
				m_pGameRoomMgr->CreateGameTable(m_wTableCount,m_wChairCount,m_pListServer);
			}
			catch (...)
			{
				//�ر�����
				m_ClientSocket->CloseSocket();
				g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());

				//��ʾ��Ϣ
				int nResult=ShowMessageBox(TEXT("��Ϸ������Դ����ʧ�ܣ��������ذ�װ���ܻ������⣬�Ƿ��������أ�"),MB_ICONQUESTION|MB_YESNO);
				if (nResult==IDYES) 
				{
					CListKind * pListKind=m_pListServer->GetListKind();
					tagGameKind * pGameKind=pListKind->GetItemInfo();
					g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
				}

				////�رշ���
				//IRoomViewItem * pIRoomViewItem=QUERY_ME_INTERFACE(IRoomViewItem);
				//((CGameFrame*)AfxGetMainWnd())->CloseRoomViewItem(pIRoomViewItem);

				return false;
			}

			return true;
		}
	case SUB_GR_COLUMN_INFO:	//�б����
		{
			//��������
			CMD_GR_ColumnInfo * pColumnInfo=(CMD_GR_ColumnInfo *)pData;
			WORD wHeadSize=sizeof(CMD_GR_ColumnInfo)-sizeof(pColumnInfo->ColumnItem);

			//Ч�����
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))!=wDataSize) return false;

			////�����б�
			//CopyMemory(&m_ListColumnInfo,pColumnInfo,__min(wDataSize,sizeof(m_ListColumnInfo)));
			//m_UserListView.SetColumnDescribe(pColumnInfo->ColumnItem,pColumnInfo->wColumnCount);

			return true;
		}
	case SUB_GR_CONFIG_FINISH:	//�������
		{
			//��ԴĿ¼
			TCHAR szResDirectory[128]=TEXT("");
			WORD wStringIndex=0,wBufferCount=CountArray(szResDirectory);

			//����Ŀ¼
			const tagGameKind * pGameKind = GetKindInfo();
			ZeroMemory(szResDirectory,wBufferCount*sizeof(TCHAR));
			lstrcpyn(szResDirectory,(LPCTSTR)pGameKind->szProcessName,wBufferCount);
			while ((szResDirectory[wStringIndex]!=0)&&(szResDirectory[wStringIndex]!=TEXT('.'))) 
				wStringIndex++;

			//�ַ���ֹ
			szResDirectory[wStringIndex]=0;

			////��Ϸ�ȼ�
			//ASSERT(m_UserListView.m_GameRankManager.GetInterface()!=NULL);
			///*bool bSuccess=*/m_UserListView.m_GameRankManager->LoadGameLevel(szResDirectory,m_wGameGenre);

			////��ʾ����
			//ShowWindow(SW_SHOW);
			//((CGameFrame*)AfxGetMainWnd())->ActiveRoomViewItem(this);

			//���ñ���
			m_ServiceStatus=ServiceStatus_RecvRoomInfo;

			return true;
		}
	}

	return true;
}

//״̬��Ϣ
bool CGameRoomSocket::OnSocketMainStatus(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_STATUS);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_TABLE_INFO:		//������Ϣ
		{
			//��������
			CMD_GR_TableInfo * pTableInfo=(CMD_GR_TableInfo *)pData;
			const WORD wHeadSize=sizeof(CMD_GR_TableInfo)-sizeof(pTableInfo->TableStatus);

			//Ч������
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))!=wDataSize) return false;

			//��Ϣ����
			for (WORD i=0;i<pTableInfo->wTableCount;i++)
			{
				m_pGameRoomMgr->SetPassFlag(i,pTableInfo->TableStatus[i].bTableLock?true:false);
				m_pGameRoomMgr->SetPlayFlag(i,pTableInfo->TableStatus[i].bPlayStatus?true:false);
			}

			return true;
		}
	case SUB_GR_TABLE_STATUS:	//����״̬
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_GR_TableStatus));
			if (wDataSize<sizeof(CMD_GR_TableStatus)) return false;

			//��Ϣ����
			CMD_GR_TableStatus * pTableStatus=(CMD_GR_TableStatus *)pData;
			ASSERT(pTableStatus->wTableID<m_wTableCount);
			if (pTableStatus->wTableID<m_wTableCount)
			{
				//��������
				IUserItem * pIUserItem=NULL;
				tagUserData * pUserData=NULL;
				BYTE bPlayStatus=m_pGameRoomMgr->QueryPlayFlag(pTableStatus->wTableID);

				//�����û�
				if (bPlayStatus!=pTableStatus->bPlayStatus)
				{
					BYTE cbUserStatus=pTableStatus->bPlayStatus?US_PLAY:US_SIT;
					//��Ϸ�û�
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

				//��������
				m_pGameRoomMgr->SetPassFlag(pTableStatus->wTableID,pTableStatus->bTableLock?true:false);
				m_pGameRoomMgr->SetPlayFlag(pTableStatus->wTableID,pTableStatus->bPlayStatus?true:false);

				//֪ͨ��Ϸ
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

//ϵͳ��Ϣ
bool CGameRoomSocket::OnSocketMainSystem(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//ϵͳ��Ϣ
		{
			//Ч�����
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pData;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//��Ϣ����
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;

			//�ر�����
			bool bIntermet=false;
			if (pMessage->wMessageType&SMT_INTERMIT_LINE) bIntermet=true;
			else if (pMessage->wMessageType&SMT_CLOSE_ROOM) bIntermet=true;
			if (bIntermet==true) 
			{
				g_GlobalAttemper.DestroyStatusWnd(AfxGetMainWnd());
				m_ClientSocket->CloseSocket();
				CloseGameClient();
			}

			////��ʾ��Ϣ
			//if (pMessage->wMessageType&SMT_INFO) 
			//	m_MessageProxyHelper->InsertSystemString(pMessage->szContent,MS_NORMAL);
			if (pMessage->wMessageType&SMT_EJECT) 
				ShowMessageBox(pMessage->szContent,MB_ICONINFORMATION);

			//�رշ���
			if (pMessage->wMessageType&SMT_CLOSE_ROOM) 
			{
				IRoomViewItem * pIRoomViewItem=QUERY_ME_INTERFACE(IRoomViewItem);
				m_pGameRoomMgr->QuitRoom();
			}

			return true;
		}
	}

	return true;
}

//������Ϣ
bool CGameRoomSocket::OnSocketMainServerInfo(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SERVER_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_ONLINE_COUNT_INFO:		//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize%sizeof(tagOnLineCountInfo)==0);
			if (wDataSize%sizeof(tagOnLineCountInfo)!=0) return false;

			//��Ϣ����
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

			//��������
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);

			return true;
		}
	}

	return true;
}

//��Ϸ��Ϣ
bool CGameRoomSocket::OnSocketMainGameFrame(CMD_Command Command, void * pData, WORD wDataSize)
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
		ASSERT(pData!=NULL);
		CopyMemory(SocketPackage.cbBuffer,pData,wDataSize);
	}

	//���ݻ���
	if (m_hWndChannel==NULL)
	{
		//״̬�ж�
		ASSERT(m_pMeUserItem!=NULL);
		if (m_pMeUserItem==NULL) return false;

		//��ȡ�û�
		tagUserData * pUserData=m_pMeUserItem->GetUserData();

		//���ݻ���
		if ((pUserData->wTableID!=INVALID_TABLE)&&(pUserData->wChairID!=INVALID_CHAIR))
		{
			//���ñ���
			m_wPacketTableID=pUserData->wTableID;
			m_wPacketChairID=pUserData->wChairID;

			//��������
			BYTE cbBuffer[SOCKET_BUFFER];
			CopyMemory(cbBuffer,&Command,sizeof(Command));
			CopyMemory(&cbBuffer[sizeof(Command)],pData,wDataSize);

			//��������
			m_PacketDataStorage.InsertData(0,cbBuffer,sizeof(Command)+wDataSize);
		}
	}
	else
	{
		//��������
		WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;
		SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize);
	}

	////������Ŀ
	//if ( Command.wSubCmdID == SUB_GF_RESIDUAL_PROPERTY )
	//{
	//	//Ч�����
	//	ASSERT(wDataSize==sizeof(CMD_GF_ResidualProperty));
	//	if (wDataSize!=sizeof(CMD_GF_ResidualProperty)) return false;
	//	//��������
	//	CMD_GF_ResidualProperty * ResidualProperty=(CMD_GF_ResidualProperty *)pData;
	//	//��ȡ���
	//	tagUserData *pMeUserData = m_pMeUserItem->GetUserData();
	//	//���õ���
	//	for ( WORD wPropID = 0; wPropID < PROPERTY_COUNT; ++wPropID )
	//	{
	//		pMeUserData->dwPropResidualTime[wPropID] = ResidualProperty->dwResidualTime[wPropID];
	//	}
	//}
	////������Ϣ
	//else if ( Command.wSubCmdID == SUB_GF_PROP_ATTRIBUTE )
	//{
	//	//У�����
	//	ASSERT( wDataSize % sizeof(tagPropertyInfo) == 0 );
	//	if ( wDataSize % sizeof(tagPropertyInfo) != 0 ) return true;
	//	//����ת��
	//	int nInfoCount = wDataSize / sizeof(tagPropertyInfo);
	//	tagPropertyInfo *pPropertyInfo = (tagPropertyInfo*)pData;
	//	//��������
	//	for ( INT_PTR nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//		m_PropertyAttributeArrary.Add(pPropertyInfo[nIndex]);
	//	//��ȡ����
	//	CPropertyBar *pPropertyBar = CPropertyBar::GetInstance();
	//	ASSERT( pPropertyBar != NULL );
	//	if ( pPropertyBar == NULL ) return false;
	//	//��ʼ�ṹ
	//	for ( int nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//	{
	//		pPropertyBar->SetPropertyInfo((pPropertyInfo+nIndex)->nPropertyID, *(pPropertyInfo+nIndex));
	//	}
	//}
	//�ʻ�����
	//else if ( Command.wSubCmdID == SUB_GF_FLOWER_ATTRIBUTE )
	//{
	//	//У�����
	//	ASSERT( wDataSize % sizeof(tagFlowerInfo) == 0 );
	//	if ( wDataSize % sizeof(tagFlowerInfo) != 0 ) return true;
	//	//����ת��
	//	int nInfoCount = wDataSize / sizeof(tagFlowerInfo);
	//	tagFlowerInfo *pFlowerInfo= (tagFlowerInfo*)pData;
	//	//��������
	//	for ( INT_PTR nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//		m_FlowerAttributeArrary.Add(pFlowerInfo[nIndex]);
	//	//��ȡ����
	//	CPropertyBar *pPropertyBar = CPropertyBar::GetInstance();
	//	ASSERT( pPropertyBar != NULL );
	//	if ( pPropertyBar == NULL ) return false;
	//	//��ʼ�ṹ
	//	for ( int nIndex = 0; nIndex < nInfoCount; ++nIndex )
	//	{
	//		pPropertyBar->SetFlowerInfo((pFlowerInfo+nIndex)->nFlowerID, *(pFlowerInfo+nIndex));
	//	}
	//}
	////������Ϣ
	//else if ( Command.wSubCmdID == SUB_GF_PROP_BUGLE )
	//{
	//	ASSERT( sizeof(CMD_GF_BugleProperty) == wDataSize );
	//	if ( sizeof(CMD_GF_BugleProperty) != wDataSize ) return false;

	//	//����ת��
	//	CMD_GF_BugleProperty *pBugleProperty = (CMD_GF_BugleProperty*)pData;

	//	//����ͼƬ
	//	CBitmap Bitmap;
	//	AfxSetResourceHandle(GetResInstanceHandle());
	//	if ( Bitmap.LoadBitmap(g_GlobalUnits.m_ChatExpViewImage.uChatBugle) )
	//	{
	//		m_MessageProxyHelper->InsertImage(&Bitmap);
	//		Bitmap.DeleteObject();
	//	}
	//	AfxSetResourceHandle(GetModuleHandle(NULL));

	//	//��������
	//	m_MessageProxyHelper->InsertUserChat(pBugleProperty->szUserName,pBugleProperty->szContext,pBugleProperty->crText,MS_NORMAL);

	//	//��������
	//	HINSTANCE hInstance = AfxGetInstanceHandle();
	//	HRSRC hResour=FindResource(hInstance,TEXT("BUGLE"),TEXT("WAVE"));
	//	if (hResour!=NULL)
	//	{
	//		HGLOBAL hGlobal=LoadResource(hInstance,hResour);
	//		if (hGlobal!=NULL) 
	//		{
	//			//��������
	//			LPCTSTR pszMemory=(LPCTSTR)LockResource(hGlobal);
	//			BOOL bResult = ::PlaySound(pszMemory,hInstance,SND_ASYNC|SND_MEMORY|SND_NODEFAULT);

	//			//������Դ
	//			UnlockResource(hGlobal);
	//		}
	//		FreeResource(hGlobal);
	//	}
	//}
	////��������
	//else if( Command.wSubCmdID == SUB_GF_FLOWER )
	//{
	//	//Ч�����
	//	ASSERT( sizeof(CMD_GF_GiftNotify) == wDataSize );
	//	if ( sizeof(CMD_GF_GiftNotify) != wDataSize ) return false;

	//	//��������
	//	CMD_GF_GiftNotify * pGiftNotify=(CMD_GF_GiftNotify *)pData;

	//	//��������
	//	if(pGiftNotify->cbSendLocation==LOCATION_PLAZA_ROOM)
	//	{
	//		//��ȡ���
	//		IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pGiftNotify->dwSendUserID);
	//		IUserItem * pIRcvUserItem=m_ClientUserManager.SearchUserByUserID(pGiftNotify->dwRcvUserID);

	//		ASSERT( pISendUserItem != NULL && pIRcvUserItem != NULL );
	//		if ( pISendUserItem == NULL || pIRcvUserItem == NULL ) return true;

	//		tagUserData const *pSendUserData = pISendUserItem->GetUserData();
	//		tagUserData const *pRcvUserData = pIRcvUserItem->GetUserData();

	//		//����ж�
	//		ASSERT( pSendUserData != NULL && pRcvUserData != NULL );
	//		if ( pSendUserData == NULL || pRcvUserData == NULL ) return true;
	//		ASSERT( pGiftNotify->wGiftID < FLOWER_COUNT ) ;
	//		if ( pGiftNotify->wGiftID >= FLOWER_COUNT ) return true;

	//		//������Ϣ
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

	//		//����ͼƬ
	//		CBitmap Bitmap;
	//		AfxSetResourceHandle(GetResInstanceHandle());
	//		if ( Bitmap.LoadBitmap(g_GlobalUnits.m_ChatExpViewImage.uChatGift[nFlowerID]) )
	//		{
	//			m_MessageProxyHelper->InsertImage(&Bitmap);
	//			Bitmap.DeleteObject();
	//		}
	//		AfxSetResourceHandle(GetModuleHandle(NULL));

	//		WORD wFlowerCount = pGiftNotify->wFlowerCount;
	//		strGiftMsg.Format(TEXT("����%d%s%s[ %s ]"), pGiftNotify->wFlowerCount, g_FlowerDescribe[nFlowerID].szQuantifier2,
	//			g_FlowerDescribe[nFlowerID].szResult, pRcvUserData->szName);
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), false);	

	//		strGiftMsg.Format(g_FlowerDescribe[nFlowerID].szCharmResult, wFlowerCount * abs(CPropertyBar::m_FlowerInfo[nFlowerID].lRcvUserCharm));
	//		m_MessageProxyHelper->InsertShtickString(strGiftMsg,RGB(255,0,255), strGiftMsg.GetLength(), true);	
	//	}
	//}

	return true;
}

//�û�����
bool CGameRoomSocket::OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;

	//��ȡ������Ϣ
	tagUserData UserData;
	memset(&UserData,0,sizeof(UserData));
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pData;

	//��ȡ��Ϣ
	UserData.dwUserID=pUserInfoHead->dwUserID;
	UserData.wTableID=pUserInfoHead->wTableID;
	UserData.wChairID=pUserInfoHead->wChairID;
	UserData.cbUserStatus=pUserInfoHead->cbUserStatus;
	UserData.dwUserRight=pUserInfoHead->dwUserRight;
	UserData.dwMasterRight=pUserInfoHead->dwMasterRight;
	//UserData.lInsureScore = pUserInfoHead->lInsureScore;

	//�����ж�
	if ((pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID)&&(pUserInfoHead->cbMasterOrder>=2))
	{
		m_cbHideUserInfo=FALSE;
	}

	//��ȡ��Ϣ
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
					lstrcpyn(UserData.szName,TEXT("��Ϸ�û�"),CountArray(UserData.szName));
				}
				break;
			}
		case DTP_UNDER_WRITE:		//����ǩ��
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
		case DTP_USER_GROUP_NAME:	//�û�����
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

	//�����û�
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

	//�����û���Ϣ
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem!=NULL)
	{
		//�ж��Լ�
		if (m_pMeUserItem==NULL)
			m_pMeUserItem=pIUserItem;

		//���ý���
		BYTE cbUserStatus=UserData.cbUserStatus;
		if ((cbUserStatus>=US_SIT)&&(cbUserStatus!=US_LOOKON))
			m_pGameRoomMgr->SetUserInfo(UserData.wTableID,UserData.wChairID,pIUserItem);

		////��ʾ��Ϣ
		//if ((m_cbHideUserInfo==FALSE)&&(m_ServiceStatus==ServiceStatus_Serviceing))
		//{
		//	if ((UserData.cbCompanion==enCompanion_Friend)||(UserData.dwMasterRight!=0L))
		//	{
		//		TCHAR szMessage[256]=TEXT("");
		//		_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] ������"),UserData.szName);
		//		m_MessageProxyHelper->InsertSystemString(szMessage,0);
		//	}
		//	else if (g_GlobalOption.m_bShowInOutMessage==true)
		//	{
		//		TCHAR szMessage[256]=TEXT("");
		//		_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] ������"),UserData.szName);
		//		m_MessageProxyHelper->InsertGeneralString(szMessage,0,0,true);
		//	}
		//}
	}

	////�Զ�ͷ��
	//if(UserData.dwCustomFaceVer!=0)
	//{
	//	//ͷ������
	//	CString strDirName = CString(g_GlobalUnits.GetWorkDirectory()) + TEXT("\\CustomFace");
	//	CString strFileName;
	//	strFileName.Format(TEXT("\\%ld_%d.bmp"), pUserInfoHead->dwUserID, pUserInfoHead->dwCustomFaceVer);

	//	//��ȡ�ļ�
	//	CImage FaceImage;
	//	HRESULT hResult = FaceImage.Load(strDirName + strFileName);
	//	if (SUCCEEDED(hResult))
	//	{
	//		FaceImage.Destroy();
	//	}
	//	//����ͷ��
	//	else
	//	{
	//		//Ͷ����Ϣ
	//		CPlazaViewItem *pPlazaViewItem = ((CGameFrame *)AfxGetMainWnd())->GetPlazaViewItem();
	//		pPlazaViewItem->PostMessage(WM_DOWN_LOAD_FACE, LPARAM(pUserInfoHead->dwCustomFaceVer), WPARAM(pUserInfoHead->dwUserID));
	//	}
	//}

	//��������
	DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
	g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);

	return true;
}

//�û�״̬
bool CGameRoomSocket::OnSocketSubStatus(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_STATUS);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserStatus));
	if (wDataSize<sizeof(CMD_GR_UserStatus)) return false;

	//��������
	CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pData;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserStatus->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//�������
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	WORD wNowTableID=pUserStatus->wTableID,wLastTableID=pUserData->wTableID;
	WORD wNowChairID=pUserStatus->wChairID,wLastChairID=pUserData->wChairID;
	BYTE cbNowStatus=pUserStatus->cbUserStatus,cbLastStatus=pUserData->cbUserStatus;

	//�����״̬
	if ((wLastTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		ASSERT(wLastChairID!=INVALID_CHAIR);
		IUserItem * pITableUserItem = m_pGameRoomMgr->GetUserInfo(wLastTableID,wLastChairID);
		if (pITableUserItem==pIUserItem) 
			m_pGameRoomMgr->SetUserInfo(wLastTableID,wLastChairID,NULL);
	}

	//�û��뿪
	if (cbNowStatus==US_NULL)
	{
		//֪ͨ��Ϸ
		if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID))
		{
			IPC_UserStatus UserStatus;
			memset(&UserStatus,0,sizeof(UserStatus));
			UserStatus.dwUserID=pUserData->dwUserID;
			UserStatus.cbUserStatus=pUserData->cbUserStatus;
			SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
		}

		//ɾ���û�
		m_ClientUserManager.DeleteUserItem(pIUserItem);

		//��������
		DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
		g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);

		return true;
	}

	//����״̬
	tagUserStatus UserStatus;
	UserStatus.wTableID=wNowTableID;
	UserStatus.wChairID=wNowChairID;
	UserStatus.cbUserStatus=cbNowStatus;
	m_ClientUserManager.UpdateUserItemStatus(pIUserItem,&UserStatus);

	//������״̬
	if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//��������
		if (cbNowStatus!=US_LOOKON)
		{
			ASSERT(wNowChairID!=INVALID_CHAIR);
			m_pGameRoomMgr->SetUserInfo(wNowTableID,wNowChairID,pIUserItem);
		}

		//�����û�
		if ((m_pMeUserItem!=pIUserItem)&&(pMeUserData->wTableID==wNowTableID))
		{
			CIPCSendCopyData SendCopyData(m_hWndChannel,AfxGetMainWnd()->m_hWnd);
			SendTableUser(pIUserItem,&SendCopyData);
		}
	}

	//���½���
	if ((wNowTableID!=INVALID_TABLE)&&(cbNowStatus!=US_LOOKON)
		&&(wNowTableID==wLastTableID)&&(wNowChairID==wLastChairID))
	{
		ASSERT(wNowChairID!=INVALID_CHAIR);
		//m_TableFrame.UpdateTableView(wNowTableID,false);
	}

	//�жϷ���
	bool bNotifyGame=false;
	if (pIUserItem==m_pMeUserItem) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wNowTableID)) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID)) bNotifyGame=true;

	//����״̬
	if (bNotifyGame==true)
	{
		IPC_UserStatus UserStatus;
		memset(&UserStatus,0,sizeof(UserStatus));
		UserStatus.dwUserID=pUserData->dwUserID;
		UserStatus.cbUserStatus=pUserData->cbUserStatus;
		SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
	}

	//�ж��Լ�
	if (pIUserItem==m_pMeUserItem)
	{
		//���ñ���
		if ((wNowTableID==m_wReqTableID)&&(wNowChairID==m_wReqChairID))
		{
			m_wReqTableID=INVALID_TABLE;
			m_wReqChairID=INVALID_CHAIR;
		}

		//��������
		if ((m_wPacketTableID!=INVALID_TABLE)&&((m_wPacketTableID!=wNowTableID)||(m_wPacketChairID!=wNowChairID)))
		{
			m_wPacketTableID=INVALID_TABLE;
			m_wPacketChairID=INVALID_CHAIR;
			m_PacketDataStorage.RemoveData(false);
		}

		//������Ϸ
		if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
		{
			int iResult=StartGameClient();
		}
	}

	return true;
}

//�û�����
bool CGameRoomSocket::OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;

	//��������
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pData;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserScore->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//�����ж�
	if ((m_cbHideUserInfo==FALSE)||(pIUserItem==m_pMeUserItem))
	{
		//���·���
		tagUserData * pUserData=pIUserItem->GetUserData();
		pUserData->lLoveliness = pUserScore->lLoveliness;
		pUserData->lGameGold = pUserScore->UserScore.lGameGold;
		pUserData->lInsureScore = pUserScore->UserScore.lInsureScore;
		m_ClientUserManager.UpdateUserItemScore(pIUserItem,&pUserScore->UserScore);

		//������Ϸ
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

//�û�Ȩ��
bool CGameRoomSocket::OnSocketSubRight(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_RIGHT);
	ASSERT(wDataSize==sizeof(CMD_GR_UserRight));
	if (wDataSize!=sizeof(CMD_GR_UserRight)) return false;

	//��Ϣ����
	CMD_GR_UserRight * pUserRight=(CMD_GR_UserRight *)pData;

	//�û�Ȩ��
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserRight->dwUserID);
	pIUserItem->GetUserData()->dwUserRight = pUserRight->dwUserRight;

	return true;
}

//��Ա�ȼ�
bool CGameRoomSocket::OnSocketSubMemberOrder(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_MEMBER_ORDER);
	ASSERT(wDataSize==sizeof(CMD_GR_MemberOrder));
	if (wDataSize!=sizeof(CMD_GR_MemberOrder)) return false;

	//��Ϣ����
	CMD_GR_MemberOrder * pMemberOrder=(CMD_GR_MemberOrder *)pData;

	//��Ա�ȼ�
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pMemberOrder->dwUserID);
	tagUserData * pUserData=pIUserItem->GetUserData();
	pUserData->cbMemberOrder = pMemberOrder->cbMemberOrder;
	tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();
	GlobalUserInfo.cbMember = pMemberOrder->cbMemberOrder;

	//������Ϸ
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

//����ʧ��
bool CGameRoomSocket::OnSocketSubSitFailed(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_SIT_FAILED);

	//��Ϣ����
	CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pData;
	IUserItem * pISendUserItem = m_pGameRoomMgr->GetUserInfo(m_wReqTableID,m_wReqChairID);
	if (pISendUserItem == m_pMeUserItem) 
		m_pGameRoomMgr->SetUserInfo(m_wReqTableID,m_wReqChairID,NULL);

	//���ñ���
	m_wReqTableID=INVALID_TABLE;
	m_wReqChairID=INVALID_CHAIR;

	//��ʾ��Ϣ
	ShowMessageBox(pSitFailed->szFailedDescribe,MB_ICONINFORMATION);

	return true;
}

//�û�����
bool CGameRoomSocket::OnSocketSubChat(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_CHAT);

	//Ч�����
	CMD_GR_UserChat * pUserChat=(CMD_GR_UserChat *)pData;
	ASSERT(wDataSize>=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)));
	ASSERT(wDataSize==(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength));
	if (wDataSize<(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage))) return false;
	if (wDataSize!=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength)) return false;

	//Ѱ���û�
	IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pUserChat->dwSendUserID);
	if (pISendUserItem==NULL) return true;
	tagUserData * pSendUserData=pISendUserItem->GetUserData();

	//��Ϣ����
	if ((pISendUserItem!=m_pMeUserItem)&&(pSendUserData->cbCompanion==enCompanion_Detest)) return true;

	//��ʾ��Ϣ
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

//�û�˽��
bool CGameRoomSocket::OnSocketSubWisper(CMD_Command Command, void * pData, WORD wDataSize)
{
	////Ч�����
	//ASSERT(Command.wMainCmdID==MDM_GR_USER);
	//ASSERT(Command.wSubCmdID==SUB_GR_USER_WISPER);

	////Ч�����
	//CMD_GR_Wisper * pWisper=(CMD_GR_Wisper *)pData;
	//ASSERT(wDataSize>=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)));
	//ASSERT(wDataSize==(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength));
	//if (wDataSize<(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage))) return false;
	//if (wDataSize!=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength)) return false;

	////Ѱ���û�
	//IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByUserID(pWisper->dwSendUserID);
	//IUserItem * pIRecvUserItem=m_ClientUserManager.SearchUserByUserID(pWisper->dwTargetUserID);
	//if ((pISendUserItem==NULL)||(pIRecvUserItem==NULL)) return true;
	//tagUserData * pUserDataSend=pISendUserItem->GetUserData();
	//tagUserData * pUserDataRecv=pIRecvUserItem->GetUserData();

	////��Ϣ����
	//if ((pUserDataSend->cbMasterOrder==0) && (pISendUserItem!=m_pMeUserItem)&&(pUserDataSend->cbCompanion==enCompanion_Detest)) return true;

	////��ʾ��Ϣ
	//CShortMessage * pShortMessageWnd=NULL;
	//if (pWisper->dwSendUserID==m_pMeUserItem->GetUserID())
	//{
	//	//�Լ����͵���Ϣ
	//	pShortMessageWnd=ActiveShortWnd(pWisper->dwTargetUserID,pIRecvUserItem,true);
	//	if (pShortMessageWnd!=NULL) pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,true);
	//}
	//else	//������Ϸ�߷�����Ϣ
	//{
	//	pShortMessageWnd=ActiveShortWnd(pWisper->dwSendUserID,pISendUserItem,true);
	//	if (pShortMessageWnd!=NULL)	
	//		pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,false);
	//}

	return true;
}

//�û�����
bool CGameRoomSocket::OnSocketSubUserInvite(CMD_Command Command, void * pData, WORD wDataSize)
{
	////Ч�����
	//ASSERT(Command.wMainCmdID==MDM_GR_USER);
	//ASSERT(Command.wSubCmdID==SUB_GR_USER_INVITE);

	////Ч�����
	//ASSERT(wDataSize==sizeof(CMD_GR_UserInvite));
	//if (wDataSize!=sizeof(CMD_GR_UserInvite)) return false;

	////��Ϣ����
	//CMD_GR_UserInvite * pUserInvite=(CMD_GR_UserInvite *)pData;
	//ASSERT(pUserInvite->wTableID<m_TableFrame.GetTableCount());
	//if (m_TableFrame.QueryPlayFlag(pUserInvite->wTableID)==true) return true;

	////Ѱ���û�
	//IUserItem * pIUserItem=m_ClientUserManager.SearchUserByUserID(pUserInvite->dwUserID);
	//if (pIUserItem==NULL) return true;
	//tagUserData * pUserData=pIUserItem->GetUserData();
	//if (pUserData->wTableID==INVALID_TABLE) return true;

	////�û�����
	//if (pUserData->cbCompanion==enCompanion_Detest) return true;
	//if (g_GlobalOption.m_InviteMode==enInviteMode_None) return true;
	//if ((g_GlobalOption.m_InviteMode==enInviteMode_Friend)&&(pUserData->cbCompanion!=enCompanion_Friend)) return true;

	////��ʾ��Ϣ
	//TCHAR szMessage[256]=TEXT("");
	//_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] ���������� [ %ld ] ��Ϸ��������Ϸ���Ƿ�ͬ�⣿"),pUserData->szName,pUserInvite->wTableID+1);
	//if (ShowMessageBox(szMessage,MB_ICONINFORMATION|MB_YESNO)==IDYES)
	//{
	//	WORD wChairID=INVALID_CHAIR;
	//	WORD wNullCount=m_TableFrame.GetNullChairCount(pUserInvite->wTableID,wChairID);
	//	if (wNullCount==0) 
	//	{
	//		ShowMessageBox(TEXT("����Ϸ���Ѿ�û�п�λ���ˣ�"),MB_ICONINFORMATION);
	//		return true;
	//	}
	//	PerformSitDownAction(pUserInvite->wTableID,wChairID);
	//}

	return true;
}


//IPC �ں�����
bool CGameRoomSocket::OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MIAN_IPC_KERNEL);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_IPC_CLIENT_CONNECT:	//������Ϣ
		{
			//�ж�����
			if (::IsChild(m_pShareMemory->hWndGameFrame,hWndSend)) return false;

			//���ñ���
			ASSERT(m_hWndChannel==NULL);
			m_hWndChannel=hWndSend;

			//������Ϣ
			CIPCSendCopyData SendCopyData(m_hWndChannel,AfxGetMainWnd()->m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			//��������
			if ((m_wPacketTableID!=INVALID_TABLE)&&(m_wPacketChairID!=INVALID_CHAIR))
			{
				//��������
				tagDataHead DataHead;
				ZeroMemory(&DataHead,sizeof(DataHead));

				//��������
				BYTE cbBuffer[SOCKET_BUFFER];
				IPC_SocketPackage SocketPackage;
				ZeroMemory(cbBuffer,sizeof(cbBuffer));
				ZeroMemory(&SocketPackage,sizeof(SocketPackage));

				//��ȡ����
				do
				{
					//��ȡ����
					tagBurthenInfo BurthenInfo;
					m_PacketDataStorage.GetBurthenInfo(BurthenInfo);

					//��ȡ����
					if (BurthenInfo.dwDataPacketCount==0L) break;
					if (m_PacketDataStorage.DistillData(DataHead,cbBuffer,sizeof(cbBuffer))==false) break;

					//��������
					CopyMemory(&SocketPackage.Command,cbBuffer,sizeof(CMD_Command));
					CopyMemory(SocketPackage.cbBuffer,&cbBuffer[sizeof(CMD_Command)],DataHead.wDataSize-sizeof(CMD_Command));

					//���ݴ���
					SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,DataHead.wDataSize);

				} while (true);

				//���ñ���
				m_wPacketTableID=INVALID_TABLE;
				m_wPacketChairID=INVALID_CHAIR;
			}

			////��������
			//IPC_SocketPackage SocketPackage;
			//ZeroMemory(&SocketPackage,sizeof(SocketPackage));
			//WORD wSendSize=0;

			////������Ϣ
			//SocketPackage.Command.wMainCmdID = MDM_GF_PRESENT;
			//SocketPackage.Command.wSubCmdID = SUB_GF_PROP_ATTRIBUTE;

			////��������
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

			////������Ϣ
			//SocketPackage.Command.wSubCmdID = SUB_GF_FLOWER_ATTRIBUTE;

			////�ʻ�����
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
	case IPC_SUB_IPC_CLIENT_CLOSE:		//�ر���Ϣ
		{
			//�ж�����
			if (hWndSend!=m_hWndChannel) return false;

			//������Ϣ
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->wTableID!=WORD(INVALID_TABLE))
			{
				if (pUserData->cbUserStatus==US_PLAY)
					SendLeftGamePacket();
				SendStandUpPacket();
			}

			//���ñ���
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

//IPC ��������
bool CGameRoomSocket::OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_SOCKET);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_SOCKET_SEND:	//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_Command));
			if (wDataSize<sizeof(CMD_Command)) 
			{
				return false;
			}

			//��������
			IPC_SocketPackage * pSocketPackage=(IPC_SocketPackage *)pIPCBuffer;
			CMD_Command *pCommand= &pSocketPackage->Command;
			WORD wSendSize=wDataSize-sizeof(CMD_Command);
			if (wSendSize==0) 
			{
				m_ClientSocket->SendData(pCommand->wMainCmdID,pCommand->wSubCmdID);
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



bool CGameRoomSocket::InitGameRoom(CListServer * pListServer,CGameRoomManager* pMgr)
{
	//���ñ���
	if(pListServer == NULL || pMgr == NULL )
	{
		ASSERT(FALSE);
		return false;
	}
	m_pListServer=pListServer;
	m_pGameRoomMgr = pMgr;

	//�������
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false) return false;
	if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) return false;
	if (m_IPCRecvCopyData.SetChannelMessageSink(pIUnknownEx)==false) return false;

	//���������ڴ�
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	_snprintf(m_szShareName,sizeof(m_szShareName),TEXT("0x8%ld%ld%ld%ld"),pGameServer->dwServerAddr,pGameServer->wServerPort,time(NULL),rand()%100);
	m_hShareMemory=(HANDLE)CreateFileMapping((HANDLE)0xFFFFFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(tagShareMemory),m_szShareName);
	if ((m_hShareMemory==NULL)||(GetLastError()==ERROR_ALREADY_EXISTS)) return false;
	m_pShareMemory=(tagShareMemory *)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,0,0,0);

	//���ù����ڴ�
	memset(m_pShareMemory,0,sizeof(tagShareMemory));
	m_pShareMemory->wDataSize=sizeof(tagShareMemory);
	m_pShareMemory->hWndGameServer=AfxGetMainWnd()->m_hWnd;
	m_pShareMemory->hWndGamePlaza=AfxGetMainWnd()->m_hWnd;

	return true;
}


//���ӷ�����
bool CGameRoomSocket::ConnectGameServer()
{
	m_ServiceStatus=ServiceStatus_Connecting;
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	return (m_ClientSocket->Connect(pGameServer->dwServerAddr,pGameServer->wServerPort)==CONNECT_SUCCESS);
}

//������Ϣ
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

//������Ϣ
void CGameRoomSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}


//������Ϣ
bool CGameRoomSocket::SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//������Ϣ
	CIPCSendCopyData IPCSendCopyData(m_hWndChannel,AfxGetMainWnd()->m_hWnd);
	return IPCSendCopyData.SendData(wMainCmdID,wSubCmdID,pData,wDataSize);
}

//IPC ��Ϣ
BOOL CGameRoomSocket::OnCopyData(CWnd *pWnd, COPYDATASTRUCT *pCopyDataStruct)
{
	if (m_IPCRecvCopyData.OnCopyData(pWnd->GetSafeHwnd(), pCopyDataStruct)==true)
		return TRUE;
	return FALSE;
}


//���͵�¼��
bool CGameRoomSocket::SendLogonPacket()
{
	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKET];
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();

	//��¼���ݰ�
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=GlobalUserData.dwUserID;
	pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
	lstrcpyn(pLogonByUserID->szPassWord,GlobalUserData.szPassWord,sizeof(pLogonByUserID->szPassWord));

	//�������к�
	tagClientSerial ClientSerial;
	g_GlobalUnits.GetClientSerial(ClientSerial);

	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

	return true;
}

//������������
bool CGameRoomSocket::SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//�������ݰ�
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=wTableID;
	UserSitReq.wChairID=wChairID;
	lstrcpyn(UserSitReq.szTablePass,pszTablePass,sizeof(UserSitReq.szTablePass));
	UserSitReq.cbPassLen=CountStringBuffer(UserSitReq.szTablePass);

	//�������ݰ�
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	return true;
}

//�����Թ�����
bool CGameRoomSocket::SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//�������ݰ�
	CMD_GR_UserSitReq UserUserSitReq;
	memset(&UserUserSitReq,0,sizeof(UserUserSitReq));
	UserUserSitReq.wTableID=wTableID;
	UserUserSitReq.wChairID=wChairID;
	lstrcpyn(UserUserSitReq.szTablePass,pszTablePass,sizeof(UserUserSitReq.szTablePass));
	UserUserSitReq.cbPassLen=CountStringBuffer(UserUserSitReq.szTablePass);

	//�������ݰ�
	WORD wSendSize=sizeof(UserUserSitReq)-sizeof(UserUserSitReq.szTablePass)+UserUserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LOOKON_REQ,&UserUserSitReq,wSendSize);

	return true;
}

//������������
bool CGameRoomSocket::SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor)
{
	//��ȡ�û�
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pUserData=m_pMeUserItem->GetUserData();

	//��������
	CMD_GR_UserChat UserChat;
	UserChat.crFontColor=crFontColor;
	UserChat.dwTargetUserID=dwTargetUserID;
	UserChat.dwSendUserID=pUserData->dwUserID;
	lstrcpyn(UserChat.szChatMessage,pszChatMessage,CountArray(UserChat.szChatMessage));
	UserChat.wChatLength=CountStringBuffer(UserChat.szChatMessage);

	//��������
	WORD wSendSize=sizeof(UserChat)-sizeof(UserChat.szChatMessage)+UserChat.wChatLength;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_CHAT,&UserChat,wSendSize);

	return true;
}

//������������
bool CGameRoomSocket::SendStandUpPacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);

	return true;
}

//����ǿ������
bool CGameRoomSocket::SendLeftGamePacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);

	return true;
}

//������Ϸ��Ϣ
bool CGameRoomSocket::IPCSendGameInfo(CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pSendCopyData!=NULL);
	ASSERT(m_pMeUserItem!=NULL);

	//�������
	tagUserData * pUserData=m_pMeUserItem->GetUserData();
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();

	//��������
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

	//��������
	pSendCopyData->SendData(IPC_MAIN_CONFIG,IPC_SUB_SERVER_INFO,&ServerInfo,sizeof(ServerInfo));

	return true;
}

//�����û�
bool CGameRoomSocket::IPCSendTableUsers(CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pSendCopyData!=NULL);

	//�����Լ���Ϣ
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	ASSERT(pMeUserData->wTableID!=(WORD)INVALID_TABLE);
	if (pMeUserData->wTableID==(WORD)INVALID_TABLE) return false;
	SendTableUser(m_pMeUserItem,pSendCopyData);

	//���������û�
	IUserItem * pIUserItem=NULL;
	tagUserData * pUserData=NULL;

	//��Ϸ�û�
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

	//�Թ��û�
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
//�����û�
bool CGameRoomSocket::SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pIUserItem!=NULL);
	ASSERT(pSendCopyData!=NULL);

	//�������
	BYTE cbBuffer[IPC_PACKAGE];
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)cbBuffer;

	//��������
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

	//��������
	WORD wHeadSize=sizeof(tagUserInfoHead);
	CSendPacketHelper SendPacketHelper(cbBuffer+wHeadSize,sizeof(cbBuffer)-wHeadSize);
	SendPacketHelper.AddPacket(pUserData->szName,CountStringBuffer(pUserData->szName),DTP_USER_ACCOUNTS);
	SendPacketHelper.AddPacket(&pUserData->cbCompanion,sizeof(pUserData->cbCompanion),DTP_USER_COMPANION);
	SendPacketHelper.AddPacket(pUserData->szUnderWrite,CountStringBuffer(pUserData->szUnderWrite),DTP_UNDER_WRITE);
	SendPacketHelper.AddPacket(pUserData->szGroupName,CountStringBuffer(pUserData->szGroupName),DTP_USER_GROUP_NAME);

	//��������
	WORD wSendSize=wHeadSize+SendPacketHelper.GetDataSize();
	pSendCopyData->SendData(IPC_MAIN_USER,IPC_SUB_USER_COME,cbBuffer,wSendSize);

	return true;
}

//������Ϸ
int CGameRoomSocket::StartGameClient()
{
	//�ж��Ƿ��Ѿ�����
	ASSERT(m_pShareMemory!=NULL);
	if ((m_GameProcessInfo.hProcess!=NULL)&&(WaitForSingleObject(m_GameProcessInfo.hProcess,0)==WAIT_TIMEOUT))
	{
		if (m_pShareMemory->hWndGameFrame!=NULL)
		{
			//��ʾ����
			::ShowWindow(m_pShareMemory->hWndGameFrame,SW_SHOW);
			::SetForegroundWindow(m_pShareMemory->hWndGameFrame);

			//������Ϣ
			CIPCSendCopyData SendCopyData(m_hWndChannel,AfxGetMainWnd()->m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			return SR_ALREADY_EXIST;
		}
		else
		{
			::TerminateProcess(m_GameProcessInfo.hProcess,0);
		}
	}

	//��������
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(m_GameProcessInfo.hThread);
	CloseHandle(m_GameProcessInfo.hProcess);
	memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));

	//����������
	CString strCommonLine;
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	strCommonLine.Format(TEXT("%s /RoomToken:%s /ServerType:%ld /HideUserInfo:%d"),
		pGameKind->szProcessName,m_szShareName,m_wGameGenre,m_cbHideUserInfo);

	//������Ϸ�ͻ���
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

//�ر���Ϸ
void CGameRoomSocket::CloseGameClient()
{
	//������Ϣ
	if (m_GameProcessInfo.hProcess!=NULL)
	{
		SendProcessData(IPC_MAIN_CONCTROL,IPC_SUB_CLOSE_FRAME,NULL,0);
		DWORD dwResult=::WaitForSingleObject(m_GameProcessInfo.hProcess,1000);
		if (dwResult==WAIT_TIMEOUT) 
			::TerminateProcess(m_GameProcessInfo.hProcess,0);
	}

	//��������
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(m_GameProcessInfo.hThread);
	CloseHandle(m_GameProcessInfo.hProcess);
	memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));

	return;
}

