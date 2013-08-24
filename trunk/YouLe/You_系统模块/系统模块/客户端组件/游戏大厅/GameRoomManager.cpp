#include "StdAfx.h"
#include ".\gameroommanager.h"

CGameRoomManager::CGameRoomManager(void)
{
	
}

CGameRoomManager::~CGameRoomManager(void)
{
	RemoveAllTable();
}

//���뷿��
void CGameRoomManager::EnterRoom(CListServer * pListServer)
{
	//�ж�״̬
	tagGlobalUserData & GlobalUserData=CGlobalUnits::GetSingleton()->GetGolbalUserData();
	if (GlobalUserData.dwUserID == 0L)
	{
		ShowMessageBox(_T("�㻹û�е�¼�����ȵ�¼��Ϸ�㳡��"),MB_ICONQUESTION);
		return ;
	}

	//Ч�����
	ASSERT(pListServer!=NULL);
	CListKind * pListKind=pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=pListServer->GetItemInfo();

	////�ж�����
	//if (m_pRoomViewItemCreate!=NULL)
	//{
	//	tagGameServer * pGameServerCreate=m_pRoomViewItemCreate->GetServerInfo();
	//	if ((pGameServer->wKindID==pGameServerCreate->wKindID)&&
	//		(pGameServer->wServerID==pGameServerCreate->wServerID))
	//		return NULL;
	//}

	////Ѱ�ҷ���
	//CRoomViewItem * pRoomViewItem=SearchRoomViewItem(pGameServer->wKindID,pGameServer->wServerID);
	//if (pRoomViewItem!=NULL) 
	//{
	//	ActiveRoomViewItem(pRoomViewItem);
	//	return pRoomViewItem;
	//}

	////���뷿����Ŀ
	//if (m_pRoomViewItem[CountArray(m_pRoomViewItem)-1]!=NULL)
	//{
	//	ShowMessageBox(TEXT("�������Ϸ����̫���ˣ���رղ�����Ϸ�������ԣ�"),MB_ICONINFORMATION);
	//	return NULL;
	//}

	//��ȡ�汾
	CWinFileInfo WinFileInfo;
	if (WinFileInfo.OpenWinFile(pGameKind->szProcessName)==false)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s����û�а�װ�������Ƿ����أ�"),pGameKind->szKindName);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return ;
	}

	//��ȡ�汾
	DWORD dwFileVerMS=0L,dwFileVerLS=0L;
	WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);

	//�汾����
	BYTE cbFileVer1=(BYTE)(HIWORD(dwFileVerMS));
	BYTE cbFileVer2=(BYTE)(LOWORD(dwFileVerMS));
	BYTE cbFileVer3=(BYTE)(HIWORD(dwFileVerLS));
	BYTE cbFileVer4=(BYTE)(LOWORD(dwFileVerLS));
	BYTE cbListVer1=(BYTE)(LOWORD(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer2=(BYTE)(HIBYTE(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer3=(BYTE)(LOBYTE(HIWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer4=(BYTE)(HIBYTE(HIWORD(pGameKind->dwMaxVersion)));

	//�жϰ汾
	if ((cbFileVer1!=cbListVer1)||(cbFileVer2!=cbListVer2)||(cbFileVer3!=cbListVer3))
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s���Ѿ�����Ϊ %ld.%ld.%ld.%ld �汾����İ汾���ܼ���ʹ�ã������Ƿ����أ�"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return ;
	}

	//���ݰ汾
	if (cbFileVer4!=cbListVer4)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s���Ѿ�����Ϊ %ld.%ld.%ld.%ld �汾�������Ƿ�����������"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) 
		{
			g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
			return ;
		}
	}

	////��������
	//try
	//{
	//	pRoomViewItem=new CRoomViewItem;
	//	if (pRoomViewItem==NULL) return NULL;
	//	pRoomViewItem->Create(IDD_GAME_ROOM,AfxGetMainWnd());
	//	if (pRoomViewItem->InitRoomViewItem(pListServer)==false) throw TEXT("��Ϸ�����ʼ��ʧ�ܣ�");
	//}
	//catch (...) { SafeDelete(pRoomViewItem); }
	//if (pRoomViewItem==NULL)
	//{
	//	ShowMessageBox(TEXT("��Ϸ���䴴��ʧ��"),MB_ICONQUESTION);
	//	return NULL;
	//}

	m_RoomSocket.InitGameRoom(pListServer,this);

	//������Ϸ
	bool bSuccess=m_RoomSocket.ConnectGameServer();
	if (bSuccess==false)
	{
		return ;
	}

	////���ñ���
	//m_pRoomViewItemCreate=pRoomViewItem;

	//������ʾ
	CString strBuffer;
	strBuffer.Format(TEXT("�������ӷ��䣬���Ժ�..."));
	g_GlobalAttemper.ShowStatusMessage(strBuffer,AfxGetMainWnd());
}

//�˳�����
void CGameRoomManager::QuitRoom()
{
	m_RoomSocket.CloseGameRoom();
	//��ʾ��Ϸ����
	AfxGetMainWnd()->PostMessage(WM_COMMAND,WM_SHOW_GAMEPAGE);
}

//������Ϸ����
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

//��������
void CGameRoomManager::RequestSitdown(WORD wTableID,WORD wChairID)
{
	m_RoomSocket.SendSitDownPacket(wTableID,wChairID,"");
}

//��������
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
				ShowMessageBox("û���ҵ����ʵ�λ�ã�",MB_ICONQUESTION,5);
				return true;
			}
		}
	}
	return false;
}

//�����û���Ϣ
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

//��ȡ�û���Ϣ
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

//���������Ƿ����
void CGameRoomManager::SetPassFlag(WORD wTableID, bool bPass)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		pTableInfo->bTableLock = bPass;
	AfxGetMainWnd()->Invalidate(TRUE);
}

//���������Ƿ���Ϸ״̬
void CGameRoomManager::SetPlayFlag(WORD wTableID, bool bPlay)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		pTableInfo->bPlayStatus = bPlay;
	AfxGetMainWnd()->Invalidate(TRUE);
}

//��ѯ������Ϸ״̬
bool CGameRoomManager::QueryPlayFlag(WORD wTableID)
{
	TableInfo* pTableInfo = EnumTableItem(wTableID);
	if(pTableInfo != NULL)
		return pTableInfo->bPlayStatus;
	return false;
}

//ɾ����������
void CGameRoomManager::RemoveAllTable()
{
	INT_PTR nCount=m_PtrArrayTable.GetCount();
	for (int i=0;i<nCount;i++)
		delete m_PtrArrayTable[i];
	m_PtrArrayTable.RemoveAll();
}

//ö������
TableInfo* CGameRoomManager::EnumTableItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayTable.GetCount())
		return NULL;
	return m_PtrArrayTable[nIndex];
}