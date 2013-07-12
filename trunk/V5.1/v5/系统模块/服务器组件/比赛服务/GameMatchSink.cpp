#include "StdAfx.h"
#include "GameMatchSink.h"


//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CGameMatchSink::m_wPlayerCount=MAX_CHAIR;			//��Ϸ����

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameMatchSink::CGameMatchSink()
{
	//��Ϸ����
	
	//������Ϣ
	
	
	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;
	m_pGameEventSink=NULL;

	return;
}

//��������
CGameMatchSink::~CGameMatchSink(void)
{
	SafeRelease(m_pGameEventSink);
	SafeRelease(m_pITableFrame);
}

//�ӿڲ�ѯ
void *  CGameMatchSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameMatchSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	//QUERYINTERFACE(ITableFrame,Guid,dwQueryVer);
	//QUERYINTERFACE(IMainServiceFrame,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameMatchSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool  CGameMatchSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	return true;
}

//��Ϸ��ʼ
bool CGameMatchSink::OnEventGameStart(ITableFrame *pITableFrame, WORD wChairCount)
{
	if(m_pGameEventSink!=NULL)
		m_pGameEventSink->OnEventGameStart(pITableFrame, wChairCount);
	return true;
}

//��Ϸ����
bool  CGameMatchSink::OnEventGameEnd(ITableFrame *pITableFrame, WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason )
{
	if(m_pGameEventSink!=NULL)
		m_pGameEventSink->OnEventGameEnd(pITableFrame,wChairID,pIServerUserItem,cbReason);
	return false;
}

//���ͳ���
bool  CGameMatchSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	return true;
}

bool CGameMatchSink::SetGameEventSink(IUnknownEx * pIUnknownEx)
{
	m_pGameEventSink=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IGameEventSink);
	return true;
}

//����Ƿ�������� 
bool CGameMatchSink::IsCanStanUp(IServerUserItem *pUserItem)
{
	if(m_pGameEventSink==NULL)
		return true;
	return m_pGameEventSink->IsCanStanUp(pUserItem);
}

//��Ҷ��߻����� 
void CGameMatchSink::SetUserOffline(WORD wChairID, bool bOffline)
{
	if(m_pGameEventSink==NULL)
		return ;	
	m_pGameEventSink->SetUserOffline(m_pITableFrame->GetTableID(),m_pITableFrame->GetTableUserItem(wChairID),bOffline);
}

//�û�����
bool CGameMatchSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	if(m_pGameEventSink!=NULL)  
		return m_pGameEventSink->OnActionUserSitDown(m_pITableFrame->GetTableID(),wChairID, pIServerUserItem, bLookonUser);
	else
	{
		CTraceService::TraceString(TEXT("����������ӷǱ�������"),TraceLevel_Exception);
	}

	return false;
}

//�û�����
bool CGameMatchSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	if(m_pGameEventSink!=NULL) 
		return m_pGameEventSink->OnActionUserStandUp(m_pITableFrame->GetTableID(),wChairID, pIServerUserItem, bLookonUser);

	return false;
}

//�û�ͬ��
bool CGameMatchSink::OnActionUserOnReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)
{
	if(m_pGameEventSink!=NULL)
		return m_pGameEventSink->OnActionUserOnReady(m_pITableFrame->GetTableID(),wChairID, pIServerUserItem ,pData ,wDataSize);

	return false;
}

//////////////////////////////////////////////////////////////////////////
