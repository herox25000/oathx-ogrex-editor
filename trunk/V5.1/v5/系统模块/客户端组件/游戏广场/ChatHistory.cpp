#include "Stdafx.h"
#include "ChatHistory.h"

//////////////////////////////////////////////////////////////////////////
//��̬����

CChatMsgItemArray CChatHistory::m_ChatMsgItemStorge;					//��Ϣ���
CChatHistoryArray CChatHistoryManager::m_ChatHistoryStorge;				//��¼���

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CChatMsgItem, CObject, VERSIONABLE_SCHEMA|1 )
IMPLEMENT_SERIAL( CChatHistory, CObject, VERSIONABLE_SCHEMA|1 )

//////////////////////////////////////////////////////////////////////////
//��Ϣ��

//���캯��
CChatMsgItem::CChatMsgItem()
{
	ResetChatMsg();
}

//��������
CChatMsgItem::~CChatMsgItem()
{

}

//���л�
void CChatMsgItem::Serialize( CArchive& ar )
{
	__super::Serialize(ar);

	//д��
	if( ar.IsStoring() )
	{
		ar << m_strSendUser;
		ar << m_strMsg;
		ar << m_crChatColor;
		ar << m_bSelfMsg;
		ar << m_Time.wYear;
		ar << m_Time.wMonth;
		ar << m_Time.wDay;
		ar << m_Time.wHour;
		ar << m_Time.wMinute;
		ar << m_Time.wSecond;
		ar << m_Time.wMilliseconds;
		ar << m_Time.wDayOfWeek;
	}
	//��ȡ
	else
	{
		ar >> m_strSendUser;
		ar >> m_strMsg;
		ar >> m_crChatColor;
		ar >> m_bSelfMsg;
		ar >> m_Time.wYear;
		ar >> m_Time.wMonth;
		ar >> m_Time.wDay;
		ar >> m_Time.wHour;
		ar >> m_Time.wMinute;
		ar >> m_Time.wSecond;
		ar >> m_Time.wMilliseconds;
		ar >> m_Time.wDayOfWeek;
	}
}

//�ӿڲ�ѯ
VOID * CChatMsgItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IChatMsgItem,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IChatMsgItem,Guid,dwQueryVer);
	return NULL;
}

//������Ŀ
VOID __cdecl CChatMsgItem::ResetChatMsg()
{
	//���ñ���
	m_strSendUser = TEXT("");
	m_strMsg = TEXT("");
	m_crChatColor = RGB(0,0,0);
	m_bSelfMsg = FALSE;
	GetLocalTime(&m_Time);
}

//////////////////////////////////////////////////////////////////////////
//��Ϣ��¼��

//���캯��
CChatHistory::CChatHistory()
{
	ResetChatHistory();
}

//��������
CChatHistory::~CChatHistory()
{
	//ɾ������
	m_ChatMsgItemStorge.Append(m_ChatMsgItemActive);
	m_ChatMsgItemActive.RemoveAll();
}

//���л�
void CChatHistory::Serialize( CArchive& ar )
{
	__super::Serialize(ar);

	//д��
	if( ar.IsStoring() )
	{
		//��Ϣ��Ŀ
		ar << (INT)m_ChatMsgItemActive.GetCount();

		for( INT_PTR i = 0; i < m_ChatMsgItemActive.GetCount(); i++ )
		{
			CChatMsgItem *pChatMsgItem = m_ChatMsgItemActive[i];

			pChatMsgItem->Serialize(ar);
		}
	}
	//��ȡ
	else
	{
		//��Ϣ��Ŀ
		INT nItemCount = 0;
		ar >> nItemCount;

		for( INT i = 0; i < nItemCount; i++ )
		{
			CChatMsgItem *pChatMsgItem = ActiveChatMsgItem();
			ASSERT(pChatMsgItem);
			if( !pChatMsgItem ) break;

			pChatMsgItem->Serialize(ar);
		}
	}
}

//�ͷŶ���
VOID CChatHistory::Release()
{
	//�رռ�¼
	ASSERT(m_pIChatHistoryManager);
	if( m_pIChatHistoryManager )
		m_pIChatHistoryManager->CloseChatHistory(GetChatID());
}

//�ӿڲ�ѯ
VOID * CChatHistory::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IChatHistory,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IChatHistory,Guid,dwQueryVer);
	return NULL;
}

//���ü�¼
VOID __cdecl CChatHistory::ResetChatHistory()
{
	//���ñ���
	m_dwChatID = 0;
	m_pIChatHistoryManager = NULL;

	//ɾ������
	m_ChatMsgItemStorge.Append(m_ChatMsgItemActive);
	m_ChatMsgItemActive.RemoveAll();
}

//ö����Ϣ
IChatMsgItem* __cdecl CChatHistory::EnumChatMsgItem(INT_PTR nEnumIndex)
{
	if( nEnumIndex < 0 || nEnumIndex >= m_ChatMsgItemActive.GetCount() )
		return NULL;

	return m_ChatMsgItemActive[nEnumIndex];
}

//�����Ϣ
bool __cdecl CChatHistory::AddMsgItem(LPCTSTR lpszSendUser,LPCTSTR lpszMsg,COLORREF crColor,bool bMySelfString)
{
	//������Ŀ
	CChatMsgItem *pChatMsgItem = ActiveChatMsgItem();
	ASSERT(pChatMsgItem);
	if( !pChatMsgItem ) return false;

	//���ñ���
	GetLocalTime(&pChatMsgItem->m_Time);
	pChatMsgItem->m_strSendUser = lpszSendUser;
	pChatMsgItem->m_strMsg = lpszMsg;
	pChatMsgItem->m_crChatColor = crColor;
	pChatMsgItem->m_bSelfMsg = (bMySelfString?TRUE:FALSE);

	return true;
}

//�����¼
bool __cdecl CChatHistory::ClearHistory()
{
	//ɾ������
	m_ChatMsgItemStorge.Append(m_ChatMsgItemActive);
	m_ChatMsgItemActive.RemoveAll();

	return true;
}

//�����¼
bool __cdecl CChatHistory::Save()
{
	ASSERT(m_pIChatHistoryManager);
	if( !m_pIChatHistoryManager ) return false;

	return m_pIChatHistoryManager->SaveChatHistory(GetChatID());
}

//������Ϣ��
CChatMsgItem* CChatHistory::ActiveChatMsgItem()
{
	//��������
	CChatMsgItem *pChatMsgItem = NULL;

	//����
	if( m_ChatMsgItemStorge.GetCount() > 0 )
	{
		INT_PTR nIndex = m_ChatMsgItemStorge.GetCount()-1;

		pChatMsgItem = m_ChatMsgItemStorge[nIndex];
		m_ChatMsgItemStorge.RemoveAt(nIndex);
		m_ChatMsgItemActive.Add(pChatMsgItem);

		pChatMsgItem->ResetChatMsg();
		return pChatMsgItem;
	}

	//����
	try{ pChatMsgItem = new CChatMsgItem; }
	catch(...) { ASSERT(FALSE); }
	if( !pChatMsgItem ) return NULL;

	m_ChatMsgItemActive.Add(pChatMsgItem);

	return pChatMsgItem;
}

//////////////////////////////////////////////////////////////////////////
//��Ϣ������

//���캯��
CChatHistoryManager::CChatHistoryManager()
{
	//��ʼ��
	m_pIMyselfUserItem = NULL;

	m_MapChatHistory.InitHashTable(11);
}

//��������
CChatHistoryManager::~CChatHistoryManager()
{
	//ɾ����¼
	m_ChatHistoryStorge.Append(m_ChatHistoryActive);
	m_ChatHistoryActive.RemoveAll();

	//ɾ��ӳ��
	m_MapChatHistory.RemoveAll();
}

//�ӿڲ�ѯ
VOID * CChatHistoryManager::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IChatHistoryManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IChatHistoryManager,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
VOID CChatHistoryManager::SetMyselftUserItem(IClientUserItem *pIMyselfUserItem)
{
	m_pIMyselfUserItem = pIMyselfUserItem;
}

//�����¼
IChatHistory* __cdecl CChatHistoryManager::ActiveChatHistory(DWORD dwChatID)
{
	//Ч��
	ASSERT(m_pIMyselfUserItem);
	if( !m_pIMyselfUserItem ) return NULL;

	//��������
	CChatHistory *pChatHistory = NULL;

	//��������
	if( m_MapChatHistory.Lookup(dwChatID,pChatHistory) )
		return pChatHistory;
	
	//���ҿ��
	if( m_ChatHistoryStorge.GetCount() > 0 )
	{
		INT_PTR nIndex = m_ChatHistoryStorge.GetCount()-1;

		pChatHistory = m_ChatHistoryStorge[nIndex];
		m_ChatHistoryStorge.RemoveAt(nIndex);
	}
	else
	{
		//����
		try{ pChatHistory = new CChatHistory; }
		catch(...) { ASSERT(FALSE); }
		if( !pChatHistory ) return NULL;
	}

	//���ñ���
	pChatHistory->m_dwChatID = dwChatID;
	pChatHistory->m_pIChatHistoryManager = this;

	//��ȡ·��
	TCHAR szWorkDir[MAX_PATH] = {0}, szPath[MAX_PATH] = {0};
	CWHService::GetWorkDirectory(szWorkDir,CountArray(szWorkDir));
	_sntprintf( szPath,CountArray(szPath),TEXT("%s\\Users\\%ld\\%ld.whc"),szWorkDir,
		m_pIMyselfUserItem->GetGameID(),dwChatID );

	//�����ļ�
	try
	{
		CFile file;
		if( file.Open(szPath,CFile::modeRead) )
		{
			//��ȡ��¼
			CArchive ar(&file, CArchive::load);

			pChatHistory->Serialize(ar);

			//�ر�
			ar.Close();
		}
	}catch(...)
	{
		ASSERT(FALSE);
		pChatHistory->ResetChatHistory();
		m_ChatHistoryStorge.Add(pChatHistory);
		return NULL;
	}

	//����ӳ��
	m_MapChatHistory[dwChatID] = pChatHistory;

	//���
	m_ChatHistoryActive.Add(pChatHistory);
	
	return pChatHistory;
}

//�رռ�¼
bool __cdecl CChatHistoryManager::CloseChatHistory(DWORD dwChatID)
{
	//��������
	CChatHistory *pChatHistory = NULL;

	//����
	m_MapChatHistory.Lookup(dwChatID,pChatHistory);
	ASSERT(pChatHistory);
	if( !pChatHistory) return false;

	m_MapChatHistory.RemoveKey(dwChatID);

	//ɾ��
	for( INT_PTR i = 0; i < m_ChatHistoryActive.GetCount(); i++ )
	{
		CChatHistory *pTmp = m_ChatHistoryActive[i];
		if( pTmp == pChatHistory )
		{
			m_ChatHistoryActive.RemoveAt(i);
			pChatHistory->ResetChatHistory();
			break;
		}
	}

	//��ӵ����
	m_ChatHistoryStorge.Add(pChatHistory);

	return true;
}

//�����¼
bool __cdecl CChatHistoryManager::SaveChatHistory(DWORD dwChatID)
{
	//Ч��
	ASSERT(m_pIMyselfUserItem);
	if( !m_pIMyselfUserItem ) return false;

	//��������
	CChatHistory *pChatHistory = NULL;

	//����
	m_MapChatHistory.Lookup(dwChatID,pChatHistory);
	ASSERT(pChatHistory);
	if( !pChatHistory ) return false;

	//��ȡ·��
	TCHAR szWorkDir[MAX_PATH] = {0}, szPath[MAX_PATH] = {0};
	CWHService::GetWorkDirectory(szWorkDir,CountArray(szWorkDir));
	_sntprintf( szPath,CountArray(szPath),TEXT("%s\\Users\\%ld\\%ld.whc"),szWorkDir,
		m_pIMyselfUserItem->GetGameID(),dwChatID );
	
	//�����ļ�
	try
	{
		CFile file;
		CFileException ex;
		if( !file.Open(szPath,CFile::modeWrite|CFile::modeCreate,&ex) )
		{
			//�ļ���δ����
			if( ex.m_cause == ERROR_PATH_NOT_FOUND )
			{
				TCHAR szDir[MAX_PATH] = {0};
				_sntprintf(szDir,CountArray(szDir),TEXT("%s\\Users"),szWorkDir);
				if( CreateDirectory(szDir,NULL) || GetLastError() == ERROR_ALREADY_EXISTS )
				{
					_sntprintf(szDir,CountArray(szDir),TEXT("%s\\Users\\%ld"),szWorkDir,
						m_pIMyselfUserItem->GetGameID());
					CreateDirectory(szDir,NULL);
				}

				//���´�
				file.Open(szPath,CFile::modeWrite|CFile::modeCreate);
			}
		}
		
		if( file.m_hFile != CFile::hFileNull )
		{
			//�����¼
			CArchive ar(&file, CArchive::store);
			
			pChatHistory->Serialize(ar);

			//�ر�
			ar.Close();
		}
	}catch(...)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////