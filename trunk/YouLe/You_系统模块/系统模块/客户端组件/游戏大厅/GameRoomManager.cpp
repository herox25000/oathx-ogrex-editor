#include "StdAfx.h"
#include ".\gameroommanager.h"

CGameRoomManager::CGameRoomManager(void)
{
	
}

CGameRoomManager::~CGameRoomManager(void)
{
	RemoveAllTable();
}

//进入房间
void CGameRoomManager::EnterRoom(CListServer * pListServer)
{
	//判断状态
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	if (GlobalUserData.dwUserID == 0L)
	{
		ShowMessageBox(_T("你还没有登录，请先登录游戏广场！"),MB_ICONQUESTION);
		return ;
	}

	//效验参数
	ASSERT(pListServer!=NULL);
	CListKind * pListKind=pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=pListServer->GetItemInfo();

	////判断连接
	//if (m_pRoomViewItemCreate!=NULL)
	//{
	//	tagGameServer * pGameServerCreate=m_pRoomViewItemCreate->GetServerInfo();
	//	if ((pGameServer->wKindID==pGameServerCreate->wKindID)&&
	//		(pGameServer->wServerID==pGameServerCreate->wServerID))
	//		return NULL;
	//}

	////寻找房间
	//CRoomViewItem * pRoomViewItem=SearchRoomViewItem(pGameServer->wKindID,pGameServer->wServerID);
	//if (pRoomViewItem!=NULL) 
	//{
	//	ActiveRoomViewItem(pRoomViewItem);
	//	return pRoomViewItem;
	//}

	////进入房间数目
	//if (m_pRoomViewItem[CountArray(m_pRoomViewItem)-1]!=NULL)
	//{
	//	ShowMessageBox(TEXT("进入的游戏房间太多了，请关闭部分游戏房间再试！"),MB_ICONINFORMATION);
	//	return NULL;
	//}

	//获取版本
	CWinFileInfo WinFileInfo;
	if (WinFileInfo.OpenWinFile(pGameKind->szProcessName)==false)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】还没有安装，现在是否下载？"),pGameKind->szKindName);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return ;
	}

	//获取版本
	DWORD dwFileVerMS=0L,dwFileVerLS=0L;
	WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);

	//版本分析
	BYTE cbFileVer1=(BYTE)(HIWORD(dwFileVerMS));
	BYTE cbFileVer2=(BYTE)(LOWORD(dwFileVerMS));
	BYTE cbFileVer3=(BYTE)(HIWORD(dwFileVerLS));
	BYTE cbFileVer4=(BYTE)(LOWORD(dwFileVerLS));
	BYTE cbListVer1=(BYTE)(LOWORD(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer2=(BYTE)(HIBYTE(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer3=(BYTE)(LOBYTE(HIWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer4=(BYTE)(HIBYTE(HIWORD(pGameKind->dwMaxVersion)));

	//判断版本
	if ((cbFileVer1!=cbListVer1)||(cbFileVer2!=cbListVer2)||(cbFileVer3!=cbListVer3))
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】已经更新为 %ld.%ld.%ld.%ld 版本，你的版本不能继续使用，现在是否下载？"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return ;
	}

	//兼容版本
	if (cbFileVer4!=cbListVer4)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】已经更新为 %ld.%ld.%ld.%ld 版本，现在是否下载升级？"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) 
		{
			g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
			return ;
		}
	}

	////创建房间
	//try
	//{
	//	pRoomViewItem=new CRoomViewItem;
	//	if (pRoomViewItem==NULL) return NULL;
	//	pRoomViewItem->Create(IDD_GAME_ROOM,AfxGetMainWnd());
	//	if (pRoomViewItem->InitRoomViewItem(pListServer)==false) throw TEXT("游戏房间初始化失败！");
	//}
	//catch (...) { SafeDelete(pRoomViewItem); }
	//if (pRoomViewItem==NULL)
	//{
	//	ShowMessageBox(TEXT("游戏房间创建失败"),MB_ICONQUESTION);
	//	return NULL;
	//}

	m_RoomSocket.InitGameRoom(pListServer,this);

	//连接游戏
	bool bSuccess=m_RoomSocket.ConnectGameServer();
	if (bSuccess==false)
	{
		return ;
	}

	////设置变量
	//m_pRoomViewItemCreate=pRoomViewItem;

	//设置提示
	CString strBuffer;
	strBuffer.Format(TEXT("正在连接房间，请稍候..."));
	g_GlobalAttemper.ShowStatusMessage(strBuffer,AfxGetMainWnd());
}

//退出房间
void CGameRoomManager::QuitRoom()
{
	m_RoomSocket.CloseGameRoom();
	//显示游戏界面
	AfxGetMainWnd()->PostMessage(WM_COMMAND,WM_SHOW_GAMEPAGE);
}

//创建游戏桌子
bool CGameRoomManager::CreateGameTable(WORD wTableCount, WORD wChairCount, CListServer* ListServer)
{
	RemoveAllTable();
	TableInfo*	pTableInfo = NULL;
	for (int i = 0; i < wTableCount; i++)
	{
		pTableInfo = new TableInfo;
		if(pTableInfo)
		{
			pTableInfo->wTableID = i;
			pTableInfo->wChairCount = wChairCount;
			pTableInfo->lPlayerCount = 0;
			memset(pTableInfo->pIUserItem,NULL,sizeof(pTableInfo->pIUserItem));
			m_PtrArrayTable.Add(pTableInfo);
		}
	}

	m_pListServer = ListServer;
	m_wTableCount = wTableCount;
	m_wChairCount = wChairCount;
	AfxGetMainWnd()->PostMessage(WM_COMMAND,WM_SHOW_GAMEPAGE);
	return true;
}

//申请入座
void CGameRoomManager::RequestSitdown(WORD wTableID,WORD wChairID)
{
	m_RoomSocket.SendSitDownPacket(wTableID,wChairID,"");
}

//快速入座
bool  CGameRoomManager::OnFastJoin()
{
	TableInfo* pTableInfo = NULL;
	int nIndex = 0;
	while(true)
	{
		pTableInfo = EnumTableItem(nIndex++);
		if(pTableInfo == NULL)
			return false;
		if(!pTableInfo->bPlayStatus)
		{
			if(pTableInfo->lPlayerCount < pTableInfo->wChairCount)
			{
				for(int i = 0; i < pTableInfo->wChairCount; i++)
				{
					if(pTableInfo->pIUserItem[i] == NULL)
					{
						RequestSitdown(pTableInfo->wTableID,i);
						return true;
					}
				}
				ShowMessageBox("没有找到合适的位置！",MB_ICONQUESTION,5);
				return true;
			}
		}
	}
	return false;
}

//设置用户信息
bool CGameRoomManager::SetUserInfo(WORD wTableID, WORD wChairID, IUserItem * pIUserItem)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo == NULL)
	{
		ASSERT(FALSE);
		return false;
	}
	if(wChairID >= pTableInfo->wChairCount)
	{
		ASSERT(FALSE);
		return false;
	}

	if (pIUserItem == NULL)
	{
		pTableInfo->lPlayerCount--;
		if(pTableInfo->lPlayerCount < 0)
			pTableInfo->lPlayerCount = 0;
	}
	else
	{
		pTableInfo->lPlayerCount++;
		if(pTableInfo->lPlayerCount > pTableInfo->wChairCount)
			pTableInfo->lPlayerCount = pTableInfo->wChairCount;
	}
	pTableInfo->pIUserItem[wChairID] = pIUserItem;
	AfxGetMainWnd()->Invalidate(TRUE);
	return true;
}

//获取用户信息
IUserItem * CGameRoomManager::GetUserInfo(WORD wTableID, WORD wChairID)
{	
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}
	if (wChairID>=CountArray(pTableInfo->pIUserItem)) 
		return NULL;
	return pTableInfo->pIUserItem[wChairID];
}

//设置桌子是否加锁
void CGameRoomManager::SetPassFlag(WORD wTableID, bool bPass)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		pTableInfo->bTableLock = bPass;
	AfxGetMainWnd()->Invalidate(TRUE);
}

//设置桌子是否游戏状态
void CGameRoomManager::SetPlayFlag(WORD wTableID, bool bPlay)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		pTableInfo->bPlayStatus = bPlay;
	AfxGetMainWnd()->Invalidate(TRUE);
}

//查询桌子游戏状态
bool CGameRoomManager::QueryPlayFlag(WORD wTableID)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		return pTableInfo->bPlayStatus;
	return false;
}

//删除所有桌子
void CGameRoomManager::RemoveAllTable()
{
	INT_PTR nCount=m_PtrArrayTable.GetCount();
	for (int i=0;i<nCount;i++)
		delete m_PtrArrayTable[i];
	m_PtrArrayTable.RemoveAll();
}

//枚举桌子
TableInfo* CGameRoomManager::EnumTableItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayTable.GetCount())
		return NULL;
	return m_PtrArrayTable[nIndex];
}