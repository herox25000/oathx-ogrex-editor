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
	////判断状态
	//tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//if (GlobalUserData.dwUserID==0L)
	//{
	//	ShowMessageBox(TEXT("你还没有登录，请先登录游戏广场！"),MB_ICONQUESTION);
	//	return NULL;
	//}

	////效验参数
	//ASSERT(pListServer!=NULL);
	//CListKind * pListKind=pListServer->GetListKind();
	//tagGameKind * pGameKind=pListKind->GetItemInfo();
	//tagGameServer * pGameServer=pListServer->GetItemInfo();

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

	////获取版本
	//CWinFileInfo WinFileInfo;
	//if (WinFileInfo.OpenWinFile(pGameKind->szProcessName)==false)
	//{
	//	TCHAR szBuffer[512]=TEXT("");
	//	_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】还没有安装，现在是否下载？"),pGameKind->szKindName);
	//	int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
	//	if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
	//	return NULL;
	//}

	////获取版本
	//DWORD dwFileVerMS=0L,dwFileVerLS=0L;
	//WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);

	////版本分析
	//BYTE cbFileVer1=(BYTE)(HIWORD(dwFileVerMS));
	//BYTE cbFileVer2=(BYTE)(LOWORD(dwFileVerMS));
	//BYTE cbFileVer3=(BYTE)(HIWORD(dwFileVerLS));
	//BYTE cbFileVer4=(BYTE)(LOWORD(dwFileVerLS));
	//BYTE cbListVer1=(BYTE)(LOWORD(LOWORD(pGameKind->dwMaxVersion)));
	//BYTE cbListVer2=(BYTE)(HIBYTE(LOWORD(pGameKind->dwMaxVersion)));
	//BYTE cbListVer3=(BYTE)(LOBYTE(HIWORD(pGameKind->dwMaxVersion)));
	//BYTE cbListVer4=(BYTE)(HIBYTE(HIWORD(pGameKind->dwMaxVersion)));

	////判断版本
	//if ((cbFileVer1!=cbListVer1)||(cbFileVer2!=cbListVer2)||(cbFileVer3!=cbListVer3))
	//{
	//	TCHAR szBuffer[512]=TEXT("");
	//	_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】已经更新为 %ld.%ld.%ld.%ld 版本，你的版本不能继续使用，现在是否下载？"),pGameKind->szKindName,
	//		cbListVer1,cbListVer2,cbListVer3,cbListVer4);
	//	int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
	//	if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
	//	return NULL;
	//}

	////兼容版本
	//if (cbFileVer4!=cbListVer4)
	//{
	//	TCHAR szBuffer[512]=TEXT("");
	//	_snprintf(szBuffer,sizeof(szBuffer),TEXT("【%s】已经更新为 %ld.%ld.%ld.%ld 版本，现在是否下载升级？"),pGameKind->szKindName,
	//		cbListVer1,cbListVer2,cbListVer3,cbListVer4);
	//	int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
	//	if (nResult==IDYES) 
	//	{
	//		g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
	//		return NULL;
	//	}
	//}

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

	////连接游戏
	//bool bSuccess=pRoomViewItem->ConnectGameServer();
	//if (bSuccess==false)
	//{
	//	pRoomViewItem->DestroyWindow();
	//	SafeDelete(pRoomViewItem);
	//	return NULL;
	//}

	////设置变量
	//m_pRoomViewItemCreate=pRoomViewItem;

	////设置提示
	//CString strBuffer;
	//strBuffer.Format(TEXT("正在连接房间，请稍候..."));
	//g_GlobalAttemper.ShowStatusMessage(strBuffer,pRoomViewItem);

	m_RoomSocket.InitGameRoom(pListServer,this);
}

//退出房间
void CGameRoomManager::QuitRoom()
{

}

//创建游戏桌子
bool CGameRoomManager::CreateGameTable(int lTableCount,CListServer* ListServer)
{
	RemoveAllTable();
	TableInfo*	pTableInfo = NULL;
	for (int i = 0; i < lTableCount; i++)
	{
		pTableInfo = new TableInfo;
		m_PtrArrayTable.Add(pTableInfo);
	}
	g_UIPageManager.m_pRoomPage->VisibleWidget(false);
	g_UIPageManager.m_pTablePage->VisibleWidget(true);
	g_UIPageManager.m_pTablePage->SetListServer(ListServer);
	g_UIPageManager.m_pTablePage->ShowFirstPage();
	return true;
}

//申请入座
void CGameRoomManager::RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass)
{
	m_RoomSocket.SendSitDownPacket(wTableID,wChairID,pszTablePass);
}

//设置桌子是否加锁
void CGameRoomManager::SetPassFlag(WORD wTableID, bool bPass)
{

}

//设置桌子是否游戏状态
void CGameRoomManager::SetPlayFlag(WORD wTableID, bool bPlay)
{

}

//查询桌子游戏状态
bool CGameRoomManager::QueryPlayFlag(WORD wTableID)
{
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