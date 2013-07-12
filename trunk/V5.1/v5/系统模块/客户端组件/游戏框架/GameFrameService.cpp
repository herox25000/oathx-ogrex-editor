#include "StdAfx.h"
#include "GlobalUnits.h"
#include "GameFrameService.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameService::CGameFrameService()
{
	//����ӿ�
	m_pIGameFrameWnd=NULL;
	m_pIGameFrameControl=NULL;

	//���ñ���
	m_pIClientKernel=NULL;
	m_pGameFrameView=NULL;
	m_pGameFrameEngine=NULL;

	//ע�����
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	pGlobalUnits->RegisterGlobalModule(MODULE_GAME_FRAME_SERVICE,QUERY_ME_INTERFACE(IUnknownEx));

	return;
}

//��������
CGameFrameService::~CGameFrameService()
{
}

//�ӿڲ�ѯ
VOID * CGameFrameService::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IUserEventSink,Guid,dwQueryVer);
	QUERYINTERFACE(IGameFrameService,Guid,dwQueryVer);
	QUERYINTERFACE(IClientKernelSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameFrameService,Guid,dwQueryVer);
	return NULL;
}

//������Ϸ
VOID CGameFrameService::ResetGameClient()
{
	//���ÿؼ�
	if (m_pIGameFrameControl!=NULL)
	{
		m_pIGameFrameControl->ResetControl();
	}

	//���ý���
	ASSERT(m_pGameFrameView!=NULL);
	if (m_pGameFrameView!=NULL) m_pGameFrameView->SwitchToReadyStatus();

	//���ÿ��
	ASSERT(m_pGameFrameEngine!=NULL);
	if (m_pGameFrameEngine!=NULL) m_pGameFrameEngine->ResetGameFrameEngine();

	return;
}

//�ر���Ϸ
VOID CGameFrameService::CloseGameClient()
{
	//���͹ر�
	AfxGetMainWnd()->PostMessage(WM_CLOSE);

	return;
}

//�������
bool CGameFrameService::OnSchemeFinish()
{
	//���ӹ��
	if (m_pIGameFrameControl!=NULL)
	{
		tagGameAttribute * pGameAttribute=m_pIClientKernel->GetGameAttribute();
		tagServerAttribute * pServerAttribute=m_pIClientKernel->GetServerAttribute();
		m_pIGameFrameControl->SetGameBillInfo(pServerAttribute->wKindID,pServerAttribute->wServerID);
	}

	return true;
}

//�б�����
bool CGameFrameService::SchemeColumnItem(tagColumnItem ColumnItem[], BYTE cbColumnCount)
{
	//�����б�
	if (m_pIGameFrameControl!=NULL)
	{
		m_pIGameFrameControl->SetColumnDescribe(ColumnItem,cbColumnCount);
	}

	return true;
}

//��������
bool CGameFrameService::SchemePropertyInfo(tagPropertyInfo PropertyInfo[], BYTE cbPropertyCount)
{
	//���õ���
	if (m_pIGameFrameControl!=NULL)
	{
		m_pIGameFrameControl->SetPropertyDescribe(PropertyInfo,cbPropertyCount);
	}

	return true;
}

//��Ϸ��Ϣ
bool CGameFrameService::OnEventSocket(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	//��Ϸ��Ϣ
	if (wMainCmdID==MDM_GF_GAME)
	{
		//Ч��״̬
		ASSERT(m_pGameFrameEngine!=NULL);
		if (m_pGameFrameEngine==NULL) return false;

		return m_pGameFrameEngine->OnEventGameMessage(wSubCmdID,pData,wDataSize);
	}

	//��Ϸ��Ϣ
	if (wMainCmdID==MDM_GR_INSURE)
	{
		//��Ϣ֪ͨ
		//if (m_pGameFrameEngine)m_pGameFrameEngine->OnEventInsureMessage(wSubCmdID,pData,wDataSize);
		if(m_pGameFrameView)m_pGameFrameView->OnEventInsureMessage(wSubCmdID,pData,wDataSize);

		return true;
	}

	//ϵͳ��Ϣ
	if(wMainCmdID==MDM_GF_FRAME)
	{
		switch(wSubCmdID)
		{
		case SUB_GF_SYSTEM_MESSAGE:				//������Ϣ
			{
				//��������
				CMD_CM_SystemMessage * pSystemMessage=(CMD_CM_SystemMessage *)pData;
				WORD wHeadSize=sizeof(CMD_CM_SystemMessage)-sizeof(pSystemMessage->szString);

				//Ч�����
				ASSERT((wDataSize>wHeadSize)&&(wDataSize==(wHeadSize+pSystemMessage->wLength*sizeof(TCHAR))));
				if ((wDataSize<=wHeadSize)||(wDataSize!=(wHeadSize+pSystemMessage->wLength*sizeof(TCHAR)))) return false;

				if((pSystemMessage->wType&SMT_TABLE_ROLL)==0) return false;

				m_pGameFrameView->AddGameTableMessage(pSystemMessage->szString,(WORD)_tcslen(pSystemMessage->szString),pSystemMessage->wType);

				if((pSystemMessage->wType|~SMT_TABLE_ROLL)==0)
					return true;
				else
					return false;
			}
		case SUB_GR_MATCH_INFO:				//������Ϣ
			{
				//����Ч��
				ASSERT(wDataSize==sizeof(CMD_GR_Match_Info));
				if(wDataSize!=sizeof(CMD_GR_Match_Info)) return false;

				//��������
				CMD_GR_Match_Info *pMatchInfo=(CMD_GR_Match_Info*)pData;
				
				m_pGameFrameView->SetMatchInfo(pMatchInfo);
				m_pGameFrameView->SetMatchWaitTip(NULL);
				return true;
			}
		case SUB_GR_MATCH_WAIT_TIP:			//�ȴ���ʾ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_Match_Wait_Tip) || wDataSize==0);
				if(wDataSize!=sizeof(CMD_GR_Match_Wait_Tip) && wDataSize!=0) return false;

				//���ò���
				if(wDataSize!=0)
					m_pGameFrameView->SetMatchWaitTip((CMD_GR_Match_Wait_Tip*)pData);
				else
					m_pGameFrameView->SetMatchWaitTip(NULL);
				return true;
			}
		case SUB_GR_MATCH_RESULT:			//�������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_MatchResult));
				if(wDataSize!=sizeof(CMD_GR_MatchResult)) return false;

				//���ò���
				m_pGameFrameView->SetMatchResult((CMD_GR_MatchResult*)pData);
				m_pGameFrameView->SetMatchWaitTip(NULL);

				return true;
			}
		}

	}

	return false;
}

//������Ϣ
bool CGameFrameService::OnEventProcess(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	return false;
}

//�Թ���Ϣ
bool CGameFrameService::OnEventLookonMode(VOID * pData, WORD wDataSize)
{
	//Ч��״̬
	ASSERT(m_pGameFrameEngine!=NULL);
	if (m_pGameFrameEngine==NULL) return false;

	return m_pGameFrameEngine->OnEventLookonMode(pData,wDataSize);
}

//������Ϣ
bool CGameFrameService::OnEventSceneMessage(BYTE cbGameStatus, bool bLookonUser, VOID * pData, WORD wDataSize)
{
	//Ч��״̬
	ASSERT(m_pGameFrameEngine!=NULL);
	if (m_pGameFrameEngine==NULL) return false;

	return m_pGameFrameEngine->OnEventSceneMessage(cbGameStatus,bLookonUser,pData,wDataSize);
}

//ʱ��ɾ��
bool CGameFrameService::OnEventGameClockKill(WORD wChairID)
{
	//Ч��״̬
	ASSERT(m_pGameFrameEngine!=NULL);
	if (m_pGameFrameEngine==NULL) return false;

	//����ʱ��
	if (wChairID!=INVALID_CHAIR)
	{
		ASSERT(m_pGameFrameView!=NULL);
		m_pGameFrameView->SetUserClock(m_pIClientKernel->SwitchViewChairID(wChairID),0L);
	}
	else
	{
		ASSERT(m_pGameFrameView!=NULL);
		m_pGameFrameView->SetUserClock(INVALID_CHAIR,0L);
	}

	//ʱ�䴦��
	return m_pGameFrameEngine->OnEventGameClockKill(wChairID);
}

//ʱ����Ϣ
bool CGameFrameService::OnEventGameClockInfo(WORD wChairID, UINT nElapse, WORD wClockID)
{
	//Ч��״̬
	ASSERT(m_pGameFrameEngine!=NULL);
	if (m_pGameFrameEngine==NULL) return false;

	//����ʱ��
	WORD wViewChairID=m_pIClientKernel->SwitchViewChairID(wChairID);
	if (m_pGameFrameView!=NULL) m_pGameFrameView->SetUserClock(wViewChairID,nElapse);

	//ʱ�䴦��
	return m_pGameFrameEngine->OnEventGameClockInfo(wChairID,nElapse,wClockID);
}

//�û�����
VOID CGameFrameService::OnEventUserEnter(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//��ͼ�û�
	if (bLookonUser==false)
	{
		//��ȡ����
		WORD wChairID=pIClientUserItem->GetChairID();
		WORD wViewChairID=m_pIClientKernel->SwitchViewChairID(wChairID);

		//�����û�
		m_pGameFrameView->SetClientUserItem(wViewChairID,pIClientUserItem);
	}

	//�߼�֪ͨ
	m_pGameFrameEngine->OnEventUserEnter(pIClientUserItem, bLookonUser);

	return;
}

//�û��뿪
VOID CGameFrameService::OnEventUserLeave(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//��ͼ�û�
	if (bLookonUser==false)
	{
		//��ȡ����
		WORD wChairID=pIClientUserItem->GetChairID();
		WORD wViewChairID=m_pIClientKernel->SwitchViewChairID(wChairID);

		//�����û�
		m_pGameFrameView->SetClientUserItem(wViewChairID,NULL);
	}

	//�߼�֪ͨ
	m_pGameFrameEngine->OnEventUserLeave(pIClientUserItem, bLookonUser);

	return;
}

//�û�����
VOID CGameFrameService::OnEventUserScore(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//���½���
	CRect rcClient;
	m_pGameFrameView->GetClientRect(&rcClient);
	m_pGameFrameView->InvalidGameView(0,0,rcClient.Width(),rcClient.Height());

	//�߼�֪ͨ
	m_pGameFrameEngine->OnEventUserScore(pIClientUserItem, bLookonUser);

	return;
}

//�û�״̬
VOID CGameFrameService::OnEventUserStatus(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//���½���
	CRect rcClient;
	m_pGameFrameView->GetClientRect(&rcClient);
	m_pGameFrameView->InvalidGameView(0,0,rcClient.Width(),rcClient.Height());

	//�߼�֪ͨ
	m_pGameFrameEngine->OnEventUserStatus(pIClientUserItem, bLookonUser);

	return;
}

//�û�����
VOID CGameFrameService::OnEventUserAttrib(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//���½���
	CRect rcClient;
	m_pGameFrameView->GetClientRect(&rcClient);
	m_pGameFrameView->InvalidGameView(0,0,rcClient.Width(),rcClient.Height());

	return;
}

//�û�ͷ��
VOID CGameFrameService::OnEventCustomFace(IClientUserItem * pIClientUserItem, bool bLookonUser)
{
	//���½���
	CRect rcClient;
	m_pGameFrameView->GetClientRect(&rcClient);
	m_pGameFrameView->InvalidGameView(0,0,rcClient.Width(),rcClient.Height());

	return;
}

//��������
bool CGameFrameService::CreateGameFrameService()
{
	//Ч��״̬
	ASSERT((CGameFrameView::GetInstance()!=NULL)&&(CGameFrameEngine::GetInstance()!=NULL));
	if ((CGameFrameView::GetInstance()==NULL)||(CGameFrameEngine::GetInstance()==NULL)) return false;

	//��������
	ASSERT(CGlobalUnits::GetInstance()!=NULL);
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();

	//���ñ���
	m_pGameFrameView=CGameFrameView::GetInstance();
	m_pGameFrameEngine=CGameFrameEngine::GetInstance();

	//��ѯ�ӿ�
	m_pIClientKernel=(IClientKernel *)pGlobalUnits->QueryGlobalModule(MODULE_CLIENT_KERNEL,IID_IClientKernel,VER_IClientKernel);
	m_pIGameFrameWnd=(IGameFrameWnd *)pGlobalUnits->QueryGlobalModule(MODULE_GAME_FRAME_WND,IID_IGameFrameWnd,VER_IGameFrameWnd);
	m_pIGameFrameControl=(IGameFrameControl *)pGlobalUnits->QueryGlobalModule(MODULE_GAME_FRAME_CONTROL,IID_IGameFrameControl,VER_IGameFrameControl);

	//ע��ӿ�
	m_pIClientKernel->SetUserEventSink(QUERY_ME_INTERFACE(IUserEventSink));
	m_pIClientKernel->SetClientKernelSink(QUERY_ME_INTERFACE(IClientKernelSink));

	//������Ϸ
	if ((m_pGameFrameEngine==NULL)||(m_pGameFrameEngine->CreateGameFrameEngine()==false))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//�����¼�
bool CGameFrameService::OnGameOptionChange()
{
	if(m_pGameFrameEngine)
	{
		m_pGameFrameEngine->OnGameOptionChange();
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
