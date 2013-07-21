#include "StdAfx.h"
#include "serverlistmanager.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
IServerListSink		* CListItem::m_pIServerListSink=NULL;		//�ص��ӿ�	

//��������
CListItem::~CListItem()
{
	m_dwData=0;
	m_pParentItem=NULL;
}

//ö������
CListItem * CListItem::EnumChildItem(INT_PTR nIndex)
{
	if (nIndex>=m_ListItemArray.GetCount()) return NULL;
	return m_ListItemArray[nIndex];
}

//��������
CListType * CListItem::SearchTypeItem(WORD wTypeID)
{
	for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
	{
		CListItem * pListItem=m_ListItemArray[i];
		if (pListItem->GetItemGenre()==ItemGenre_Type)
		{
			CListType * pListType=(CListType *)pListItem;
			tagGameType * pGameType=pListType->GetItemInfo();
			if (pGameType->wTypeID==wTypeID) return pListType;
		}
	}

	return NULL;
}

//��������
CListKind * CListItem::SearchKindItem(WORD wKindID)
{
	for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
	{
		CListItem * pListItem=m_ListItemArray[i];
		if (pListItem->GetItemGenre()==ItemGenre_Kind)
		{
			CListKind * pListKind=(CListKind *)pListItem;
			const tagGameKind * pGameKind=pListKind->GetItemInfo();
			if (pGameKind->wKindID==wKindID) return pListKind;
		}
	}

	return NULL;
}

//��������
CListStation * CListItem::SearchStationItem(WORD wKindID, WORD wStationID, bool bDeepSearch)
{
	//��������
	for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
	{
		CListItem * pListItem=m_ListItemArray[i];
		if (pListItem->GetItemGenre()==ItemGenre_Station)
		{
			CListStation * pListStation=(CListStation *)pListItem;
			const tagGameStation * pGameStation=pListStation->GetItemInfo();
			if ((pGameStation->wStationID==wStationID)&&(pGameStation->wKindID==wKindID)) return pListStation;
		}
	}

	//�������
	if (bDeepSearch)
	{
		for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
		{
			CListItem * pItemBase=m_ListItemArray[i];
			CListStation * pListStation=pItemBase->SearchStationItem(wKindID,wStationID,bDeepSearch);
			if (pListStation!=NULL) return pListStation;
		}
	}

	return NULL;
}

//��������
CListServer * CListItem::SearchServerItem(WORD wKindID, WORD wServerID, bool bDeepSearch)
{
	//��������
	for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
	{
		CListItem * pListItem=m_ListItemArray[i];
		if (pListItem->GetItemGenre()==ItemGenre_Server)
		{
			CListServer * pListServer=(CListServer *)pListItem;
			const tagGameServer * pGameServer=pListServer->GetItemInfo();
			if ((pGameServer->wServerID==wServerID)&&(pGameServer->wKindID==wKindID)) return pListServer;
		}
	}

	//�������
	if (bDeepSearch)
	{
		for (INT_PTR i=0;i<m_ListItemArray.GetCount();i++)
		{
			CListItem * pItemBase=m_ListItemArray[i];
			CListServer * pListServer=pItemBase->SearchServerItem(wKindID,wServerID,bDeepSearch);
			if (pListServer!=NULL) return pListServer;
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CServerListManager::CServerListManager()
{
	m_pIServerListSink=NULL;
}

//��������
CServerListManager::~CServerListManager()
{
	INT_PTR nCount=m_PtrArrayType.GetCount();
	for (int i=0;i<nCount;i++) delete m_PtrArrayType[i];
	m_PtrArrayType.RemoveAll();

	nCount=m_PtrArrayKind.GetCount();
	for (i=0;i<nCount;i++) delete m_PtrArrayKind[i];
	m_PtrArrayKind.RemoveAll();

	nCount=m_PtrArrayStation.GetCount();
	for (i=0;i<nCount;i++) delete m_PtrArrayStation[i];
	m_PtrArrayStation.RemoveAll();

	nCount=m_PtrArrayServer.GetCount();
	for (i=0;i<nCount;i++) delete m_PtrArrayServer[i];
	m_PtrArrayServer.RemoveAll();

	return;
}

//��ʼ������
bool CServerListManager::InitServerListManager(IServerListSink * pIServerListSink)
{
	//���ñ���
	m_pIServerListSink=pIServerListSink;
	CListItem::m_pIServerListSink=pIServerListSink;

	//��������
	tagGameInside GameInside;
	memset(&GameInside,0,sizeof(GameInside));
	lstrcpyn(GameInside.szDisplayName,szProductName,sizeof(GameInside.szDisplayName));
	InsertInsideItem(&GameInside,1);

	return true;
}

//չ���б�
bool CServerListManager::ExpandListItem(CListItem * pListItem)
{
		
	ASSERT(m_pIServerListSink!=NULL);
	if(m_pIServerListSink == NULL)
		return false;
	return m_pIServerListSink->ExpandListItem(pListItem);
}

//ö������
CListType * CServerListManager::EnumTypeItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayType.GetCount()) return NULL;
	return m_PtrArrayType[nIndex];
}

//ö����Ϸ
CListKind * CServerListManager::EnumKindItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayKind.GetCount()) return NULL;
	return m_PtrArrayKind[nIndex];
}

//ö��վ��
CListStation * CServerListManager::EnumStationItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayStation.GetCount()) return NULL;
	return m_PtrArrayStation[nIndex];
}

//ö�ٷ���
CListServer * CServerListManager::EnumServerItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayServer.GetCount()) return NULL;
	return m_PtrArrayServer[nIndex];
}

//ö���ڲ���
CListInside * CServerListManager::EnumInsideItem(INT_PTR nIndex)
{
	if (nIndex>=m_PtrArrayInside.GetCount()) return NULL;
	return m_PtrArrayInside[nIndex];
}

//��������
bool CServerListManager::InsertTypeItem(tagGameType GameType[], WORD wCount)
{
	//Ч�����
	ASSERT(m_PtrArrayInside.GetCount()>0);
	if (wCount==0) return false;

	//��������
	CListType * pListType=NULL;
	CListInside * pRootListInside=m_PtrArrayInside[0];

	try
	{
		//��������
		CListType * pListTypeTemp=NULL;

		for (WORD i=0;i<wCount;i++)
		{
			//���Ҵ���
			pListTypeTemp=pRootListInside->SearchTypeItem(GameType[i].wTypeID);
			if (pListTypeTemp!=NULL) continue;

			//�������
			pListType=new CListType(pRootListInside);
			CopyMemory(pListType->GetItemInfo(),&GameType[i],sizeof(tagGameType));
			m_PtrArrayType.Add(pListType);
			if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemInserted(pListType);
		}
		return true;
	}
	catch (...) { SafeDelete(pListType); }

	return false;
}

//��������
bool CServerListManager::InsertKindItem(tagGameKind GameKind[], WORD wCount)
{
	CListKind * pListKind=NULL;
	try
	{
		//��������
		WORD wTypeID=0;
		CListType * pListType=NULL;
		CListKind * pListKindTemp=NULL;

		for (WORD i=0;i<wCount;i++)
		{
			//Ѱ�Ҹ���
			if ((pListType==NULL)||(GameKind[i].wTypeID!=wTypeID))
			{
				wTypeID=GameKind[i].wTypeID;
				pListType=SearchTypeItem(wTypeID);
				ASSERT(pListType!=NULL);
				if (pListType==NULL) continue;
			}

			//���Ҵ���
			pListKindTemp=pListType->SearchKindItem(GameKind[i].wKindID);
			if (pListKindTemp!=NULL) continue;

			//�������
			CWinFileInfo WinFileInfo;
			pListKind=new CListKind(pListType);
			CopyMemory(pListKind->GetItemInfo(),&GameKind[i],sizeof(tagGameKind));
			pListKind->m_bInstall=WinFileInfo.OpenWinFile(GameKind[i].szProcessName);
			m_PtrArrayKind.Add(pListKind);
			if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemInserted(pListKind);
		}
		return true;
	}
	catch (...) { SafeDelete(pListKind); }

	return false;
}

//��������
bool CServerListManager::InsertStationItem(tagGameStation GameStation[], WORD wCount)
{
	CListStation * pListStation=NULL;
	try
	{
		//��������
		WORD wKindID=0,wStationID=0;
		CListKind * pListKind=NULL;
		CListItem * pListParent=NULL;
		CListStation * pListStationJoin=NULL;
		CListStation * pListStationTemp=NULL;

		for (WORD i=0;i<wCount;i++)
		{
			//Ѱ������
			if ((pListKind==NULL)||(GameStation[i].wKindID!=wKindID))
			{
				pListKind=SearchKindItem(GameStation[i].wKindID);
				ASSERT(pListKind!=NULL);
				if (pListKind==NULL) continue;
				wKindID=GameStation[i].wKindID;
				pListParent=pListKind;
			}

			//���Ҵ���
			pListStationTemp=pListKind->SearchStationItem(GameStation[i].wKindID,GameStation[i].wStationID,true);
			if (pListStationTemp!=NULL) continue;

			//Ѱ��վ��
			if (GameStation[i].wJoinID!=0)
			{
				if ((pListStationJoin==NULL)||(GameStation[i].wJoinID!=wStationID))
				{
					pListStationJoin=pListKind->SearchStationItem(GameStation[i].wKindID,GameStation[i].wJoinID,true);
					ASSERT(pListStationJoin!=NULL);
					if (pListStationJoin==NULL) continue;
					wStationID=GameStation[i].wJoinID;
				}
				pListParent=pListStationJoin;
			}

			//�������
			pListStation=new CListStation(pListParent,pListKind);
			CopyMemory(pListStation->GetItemInfo(),&GameStation[i],sizeof(tagGameStation));
			m_PtrArrayStation.Add(pListStation);
			if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemInserted(pListStation);
		}
		return true;
	}
	catch (...) { SafeDelete(pListStation); }

	return false;
}

//��������
bool CServerListManager::InsertServerItem(tagGameServer GameServer[], WORD wCount)
{
	CListServer * pListServer=NULL;
	try
	{
		//��������
		WORD wKindID=0,wStationID=0;
		CListKind * pListKind=NULL;
		CListItem * pListParent=NULL;
		CListStation * pListStation=NULL;
		CListServer * pListServerTemp=NULL;

		for (WORD i=0;i<wCount;i++)
		{
			//Ѱ������
			if ((pListKind==NULL)||(GameServer[i].wKindID!=wKindID))
			{
				pListKind=SearchKindItem(GameServer[i].wKindID);
				ASSERT(pListKind!=NULL);
				if (pListKind==NULL) continue;
				wKindID=GameServer[i].wKindID;
				pListParent=pListKind;
			}

			//���Ҵ���
			pListServerTemp=pListKind->SearchServerItem(GameServer[i].wKindID,GameServer[i].wServerID,true);
			if (pListServerTemp!=NULL) continue;

			//Ѱ��վ��
			if (GameServer[i].wStationID!=0)
			{
				if ((pListStation==NULL)||(GameServer[i].wStationID!=wStationID))
				{
					pListStation=pListKind->SearchStationItem(GameServer[i].wKindID,GameServer[i].wStationID,true);
					if (pListStation==NULL) continue;
					wStationID=GameServer[i].wStationID;
				}
				pListParent=pListStation;
			}

			//�������
			pListServer=new CListServer(pListParent,pListKind);
			CopyMemory(pListServer->GetItemInfo(),&GameServer[i],sizeof(tagGameServer));
			m_PtrArrayServer.Add(pListServer);
			if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemInserted(pListServer);
		}
		return true;
	}
	catch (...) { SafeDelete(pListServer); }

	return false;
}

//��������
bool CServerListManager::InsertInsideItem(tagGameInside GameInside[], WORD wCount)
{
	CListInside * pListInside=NULL;
	try
	{
		for (WORD i=0;i<wCount;i++)
		{
			pListInside=new CListInside(NULL);
			CopyMemory(pListInside->GetItemInfo(),&GameInside[i],sizeof(tagGameInside));
			m_PtrArrayInside.Add(pListInside);
			if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemInserted(pListInside);
		}
		return true;
	}
	catch (...) { SafeDelete(pListInside); }

	return false;
}

//��������
CListType * CServerListManager::SearchTypeItem(WORD wTypeID)
{
	for (INT_PTR i=0;i<m_PtrArrayType.GetCount();i++)
	{
		CListType * pListType=m_PtrArrayType[i];
		tagGameType * pGameType=pListType->GetItemInfo();
		if (pGameType->wTypeID==wTypeID) return pListType;
	}
	return NULL;
}

//��������
CListKind * CServerListManager::SearchKindItem(WORD wKindID)
{
	for (INT_PTR i=0;i<m_PtrArrayKind.GetCount();i++)
	{
		CListKind * pListKind=m_PtrArrayKind[i];
		tagGameKind * pGameKind=pListKind->GetItemInfo();
		if (pGameKind->wKindID==wKindID) return pListKind;
	}
	return NULL;
}

//��������
CListStation * CServerListManager::SearchStationItem(WORD wKindID, WORD wStationID)
{
	for (INT_PTR i=0;i<m_PtrArrayStation.GetCount();i++)
	{
		CListStation * pListStation=m_PtrArrayStation[i];
		tagGameStation * pGameStation=pListStation->GetItemInfo();
		if ((pGameStation->wStationID==wStationID)&&(pGameStation->wKindID==wKindID)) return pListStation;
	}
	return NULL;
}

//��������
CListServer * CServerListManager::SearchServerItem(WORD wKindID, WORD wServerID)
{
	for (INT_PTR i=0;i<m_PtrArrayServer.GetCount();i++)
	{
		CListServer * pListServer=m_PtrArrayServer[i];
		tagGameServer * pGameServer=pListServer->GetItemInfo();
		if ((pGameServer->wServerID==wServerID)&&(pGameServer->wKindID==wKindID)) return pListServer;
	}
	return NULL;
}

//��������
bool CServerListManager::UpdateGameKind(WORD wKindID)
{
	CListKind * pListKind=SearchKindItem(wKindID);
	if (pListKind!=NULL)
	{
		CWinFileInfo WinFileInfo;
		tagGameKind * pGameKind=pListKind->GetItemInfo();
		pListKind->m_bInstall=WinFileInfo.OpenWinFile(pGameKind->szProcessName);
		if(m_pIServerListSink != NULL)
			m_pIServerListSink->OnListItemUpdate(pListKind);
		return true;
	}

	return false;
}

//��������
bool CServerListManager::UpdateGameOnLineCount(DWORD dwOnLineCount)
{
	if (m_PtrArrayInside.GetCount()>0)
	{
		CListInside * pListInside=m_PtrArrayInside[0];
		tagGameInside * pGameInside=pListInside->GetItemInfo();
		_snprintf(pGameInside->szDisplayName,sizeof(pGameInside->szDisplayName),TEXT("%s [ %ld ��]"),szProductName,dwOnLineCount);
		if(m_pIServerListSink != NULL)
		m_pIServerListSink->OnListItemUpdate(pListInside);
		return true;
	}

	return false;
}

//��������
bool CServerListManager::UpdateGameKindOnLine(WORD wKindID, DWORD dwOnLineCount)
{
	//Ѱ������
	CListKind * pListKind=SearchKindItem(wKindID);
	if (pListKind!=NULL)
	{
		tagGameKind * pGameKind=pListKind->GetItemInfo();
		pGameKind->dwOnLineCount=dwOnLineCount;
		if(m_pIServerListSink != NULL)
		m_pIServerListSink->OnListItemUpdate(pListKind);
		return true;
	}

	return false;
}

//��������
bool CServerListManager::UpdateGameServerOnLine(CListServer * pListServer, DWORD dwOnLineCount)
{
	//Ч�����
	ASSERT(pListServer!=NULL);
	if (pListServer==NULL) return false;

	//������Ϣ
	tagGameServer * pGameServer=pListServer->GetItemInfo();
	pGameServer->dwOnLineCount=dwOnLineCount;
	if(m_pIServerListSink != NULL)
	m_pIServerListSink->OnListItemUpdate(pListServer);

	return true;
}
