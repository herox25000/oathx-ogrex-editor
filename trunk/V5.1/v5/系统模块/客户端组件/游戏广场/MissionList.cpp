#include "StdAfx.h"
#include "MissionList.h"
#include "ServerListData.h"
#include "PlatformEvent.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
#define IDI_AVTIVE_MISSION				100								//��������
#define IDI_UPDATE_ONLINE               101                             //�������� 
#define TIME_AVTIVE_MISSION				600000L							//��������
#define TIME_UPDATE_ONLINE              15000L                          //�������� 


//////////////////////////////////////////////////////////////////////////////////
//��̬����

CMissionList * CMissionList::m_pMissionList=NULL;						//����ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMissionList, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CMissionList::CMissionList()
{
	//���ñ���
	m_bUpdateOnLine=false;

	//���ö���
	ASSERT(m_pMissionList==NULL);
	if (m_pMissionList==NULL) m_pMissionList=this;

	return;
}

//��������
CMissionList::~CMissionList()
{
	//�ͷŶ���
	ASSERT(m_pMissionList==this);
	if (m_pMissionList==this) m_pMissionList=NULL;
    
	//�ͷŴ���
	if(m_hWnd!=NULL) UpdateMissionStatus(false);

	return;
}

//�����¼�
bool CMissionList::OnEventMissionLink(INT nErrorCode)
{
	//�����ж�
	if (nErrorCode!=0L)
	{
		//״̬Ч��
		if (m_bUpdateOnLine==false)
		{
			ASSERT(FALSE);
			return false;
		}

		//��������
		if (m_hWnd==NULL)
		{
			CRect rcCreate(0,0,0,0);
			Create(NULL,NULL,WS_CHILD,rcCreate,GetDesktopWindow(),100);
		}

		//����ʱ��
		SetTimer(IDI_AVTIVE_MISSION,TIME_AVTIVE_MISSION,NULL);

		return true;
	}

	//��������
	if (m_bUpdateOnLine==true)
	{
		//���ñ���
		m_bUpdateOnLine=false;

		//��������
		CMD_GP_GetOnline GetOnline;
		ZeroMemory(&GetOnline,sizeof(GetOnline));

		//��������
		POSITION Position=NULL;
		CMissionManager * pMissionManager=GetMissionManager();
		CServerListData * pServerListData=CServerListData::GetInstance();

		do
		{
			//��ȡ����
			CGameServerItem * pGameServerItem=pServerListData->EmunGameServerItem(Position);

			//����ж�
			if (GetOnline.wServerCount>=CountArray(GetOnline.wOnLineServerID))
			{
				ASSERT(FALSE);
				break;
			}

			//���÷���
			if (pGameServerItem!=NULL)
			{
				tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
				GetOnline.wOnLineServerID[GetOnline.wServerCount++]=pGameServer->wServerID;
			}

		} while (Position!=NULL);

		//��������
		WORD wHeadSize=sizeof(GetOnline)-sizeof(GetOnline.wOnLineServerID);
		WORD wSendSize=wHeadSize+sizeof(GetOnline.wOnLineServerID[0])*GetOnline.wServerCount;
		pMissionManager->SendData(MDM_GP_SERVER_LIST,SUB_GP_GET_ONLINE,&GetOnline,wSendSize);
	}

	return true;
}

//�ر��¼�
bool CMissionList::OnEventMissionShut(BYTE cbShutReason)
{
	//��������
	if (m_bUpdateOnLine==true)
	{
		//��������
		if (m_hWnd==NULL)
		{
			CRect rcCreate(0,0,0,0);
			Create(NULL,NULL,WS_CHILD,rcCreate,GetDesktopWindow(),100);
		}

		//����ʱ��
		SetTimer(IDI_AVTIVE_MISSION,TIME_AVTIVE_MISSION,NULL);
	}

	return true;
}

//��ȡ�¼�
bool CMissionList::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	if (Command.wMainCmdID==MDM_GP_SERVER_LIST)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_LIST_TYPE:		//������Ϣ
			{
				//Ч�����
				ASSERT(wDataSize%sizeof(tagGameType)==0);
				if (wDataSize%sizeof(tagGameType)!=0) return false;

				//��������
				WORD wItemCount=wDataSize/sizeof(tagGameType);
				tagGameType * pGameType=(tagGameType *)(pData);

				//��ȡ����
				ASSERT(CServerListData::GetInstance()!=NULL);
				CServerListData * pServerListData=CServerListData::GetInstance();

				//��������
				for (WORD i=0;i<wItemCount;i++)
				{
					pServerListData->InsertGameType(pGameType++);
				}

				return true;
			}
		case SUB_GP_LIST_KIND:		//������Ϣ
			{
				//Ч�����
				ASSERT(wDataSize%sizeof(tagGameKind)==0);
				if (wDataSize%sizeof(tagGameKind)!=0) return false;

				//��������
				WORD wItemCount=wDataSize/sizeof(tagGameKind);
				tagGameKind * pGameKind=(tagGameKind *)(pData);

				//��ȡ����
				ASSERT(CServerListData::GetInstance()!=NULL);
				CServerListData * pServerListData=CServerListData::GetInstance();

				//��������
				for (WORD i=0;i<wItemCount;i++)
				{
					pServerListData->InsertGameKind(pGameKind++);
				}

				return true;
			}
		case SUB_GP_LIST_SERVER:	//������Ϣ
			{
				//Ч�����
				ASSERT(wDataSize%sizeof(tagGameServer)==0);
				if (wDataSize%sizeof(tagGameServer)!=0) return false;

				//��������
				WORD wItemCount=wDataSize/sizeof(tagGameServer);
				tagGameServer * pGameServer=(tagGameServer *)(pData);

				//��ȡ����
				CServerListData * pServerListData=CServerListData::GetInstance();

				//��������
				for (WORD i=0;i<wItemCount;i++)
				{
					pServerListData->InsertGameServer(pGameServer++);
				}

				return true;
			}
		case SUB_GP_LIST_FINISH:	//�б���Ϣ
			{
				//�б����
				ASSERT(CServerListData::GetInstance()!=NULL);
				if (CServerListData::GetInstance()!=NULL) CServerListData::GetInstance()->OnEventListFinish();

				return true;
			}
		case SUB_GR_KINE_ONLINE:	//��������
			{
				//��������
				CMD_GP_KindOnline * pKindOnline=(CMD_GP_KindOnline *)pData;
				WORD wHeadSize=(sizeof(CMD_GP_KindOnline)-sizeof(pKindOnline->OnLineInfoKind));

				//Ч������
				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+pKindOnline->wKindCount*sizeof(tagOnLineInfoKind))));
				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+pKindOnline->wKindCount*sizeof(tagOnLineInfoKind)))) return false;

				//��ȡ����
				CServerListData * pServerListData=CServerListData::GetInstance();

				//��������
				for (WORD i=0;i<pKindOnline->wKindCount;i++)
				{
					tagOnLineInfoKind * pOnLineInfoKind=&pKindOnline->OnLineInfoKind[i];
					pServerListData->SetKindOnLineCount(pOnLineInfoKind->wKindID,pOnLineInfoKind->dwOnLineCount);
				}

				return true;
			}
		case SUB_GR_SERVER_ONLINE:	//��������
			{
				//��������
				CMD_GP_ServerOnline * pServerOnline=(CMD_GP_ServerOnline *)pData;
				WORD wHeadSize=(sizeof(CMD_GP_ServerOnline)-sizeof(pServerOnline->OnLineInfoServer));

				//Ч������
				ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+pServerOnline->wServerCount*sizeof(tagOnLineInfoServer))));
				if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+pServerOnline->wServerCount*sizeof(tagOnLineInfoServer)))) return false;

				//��ȡ����
				CServerListData * pServerListData=CServerListData::GetInstance();

				//��������
				for (WORD i=0;i<pServerOnline->wServerCount;i++)
				{
					tagOnLineInfoServer * pOnLineInfoServer=&pServerOnline->OnLineInfoServer[i];
					pServerListData->SetServerOnLineCount(pOnLineInfoServer->wServerID,pOnLineInfoServer->dwOnLineCount);
				}

				//֪ͨ����
				CPlatformEvent * pPlatformEvent =  CPlatformEvent::GetInstance();
				pPlatformEvent->SendPlatformEvent(EVENT_UPDATE_ONLINE,0L);

				//��ֹ����
				if (m_bUpdateOnLine==false)
				{
					CMissionManager * pMissionManager=GetMissionManager();
					if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);
				}

				return true;
			}
		}
	}

	return true;
}

//��������
VOID CMissionList::UpdateOnLineInfo()
{
	//Ч��״̬
	ASSERT(m_bUpdateOnLine==false);
	if (m_bUpdateOnLine==true) return;

	//���ñ���
	m_bUpdateOnLine=true;

	//��������
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//���õ�ַ
	LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
	if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) pMissionManager->SetCustomServer(pszCurrentServer);

	//��������
	pMissionManager->AvtiveMissionItem(this,false);

	return;
}

//���״̬
VOID CMissionList::UpdateMissionStatus(bool bActive)
{
	if(bActive==true)
	{
		//��������
		if (m_hWnd==NULL)
		{
			CRect rcCreate(0,0,0,0);
			Create(NULL,NULL,WS_CHILD,rcCreate,GetDesktopWindow(),100);
		}

		//����ʱ��
		SetTimer(IDI_UPDATE_ONLINE,TIME_UPDATE_ONLINE,NULL);

		//��������
		UpdateOnLineInfo();
	}
	else
	{
		//����ʱ��
		KillTimer(IDI_UPDATE_ONLINE);

		//���ٴ���
		if (m_hWnd!=NULL) DestroyWindow();
	}

	return;
}

//ʱ����Ϣ
VOID CMissionList::OnTimer(UINT nIDEvent)
{
	//��������
	if (nIDEvent==IDI_AVTIVE_MISSION)
	{
		//��������
		ASSERT(GetMissionManager()!=NULL);
		CMissionManager * pMissionManager=GetMissionManager();

		//���õ�ַ
		LPCTSTR pszCurrentServer=pMissionManager->GetCurrentServer();
		if ((pszCurrentServer!=NULL)&&(pszCurrentServer[0]!=0)) pMissionManager->SetCustomServer(pszCurrentServer);

		//��������
		pMissionManager->AvtiveMissionItem(this,false);

		return;
	}

	//��������
	if(nIDEvent==IDI_UPDATE_ONLINE)
	{
		//��������
		UpdateOnLineInfo();

		return;
	}

	__super::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////////////
