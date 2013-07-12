#include "StdAfx.h"
#include "AfxTempl.h"
#include "GameMatchSink.h"
#include "GameMatchServiceManager.h"

#include "..\��Ϸ������\DataBasePacket.h"

//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameMatchServiceManager::CGameMatchServiceManager(void)
{
	m_pIGameServiceFrame=NULL;
	m_pITCPNetworkEngineEvent=NULL;
	m_pIDataBaseEngine=NULL;
	m_pITimerEngine=NULL;
	m_pIServerUserManager=NULL;
	m_pGameServiceOption=NULL;
	m_pGameServiceAttrib=NULL;
	m_ppITableFrame=NULL;
	m_pAndroidUserManager=NULL;
	m_bTableUsed=NULL;
	m_RewardArr.RemoveAll();
	m_wMatchIDCount=0;
	m_pCurMatch=NULL;
	m_dwStartTimeID=0;
	ZeroMemory(&m_MatchDesc,sizeof(m_MatchDesc));
	return;
}

//��������
CGameMatchServiceManager::~CGameMatchServiceManager(void)
{
	//�������
	//SafeDelete(m_pGameMatchSink);
	SafeDeleteArray(m_ppITableFrame);
	SafeDeleteArray(m_bTableUsed);
	INT_PTR nCount=m_TimerItemFree.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
		SafeDelete(m_TimerItemFree.GetAt(i));
	m_TimerItemFree.RemoveAll();

	nCount=m_TimerItemActive.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
		SafeDelete(m_TimerItemActive.GetAt(i));
	m_TimerItemActive.RemoveAll();
	m_UnRecovery.RemoveAll();
	
}
//ֹͣ����
bool  CGameMatchServiceManager::StopService()
{
	m_OnMatchUserItem.RemoveAll();

	for(INT_PTR i=0; i<m_RewardArr.GetCount();i++)
	{
		SafeDelete(m_RewardArr.GetAt(i));
	}
	m_RewardArr.RemoveAll();

	SafeDeleteArray(m_ppITableFrame);
	SafeDeleteArray(m_bTableUsed);
	INT_PTR nCount=m_TimerItemFree.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
		SafeDelete(m_TimerItemFree.GetAt(i));
	m_TimerItemFree.RemoveAll();

	nCount=m_TimerItemActive.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
		SafeDelete(m_TimerItemActive.GetAt(i));
	m_TimerItemActive.RemoveAll();

	for(INT_PTR i=0; i<m_MatchGroup.GetCount();i++)
		SafeDelete(m_MatchGroup.GetAt(i));
	m_MatchGroup.RemoveAll();

	SafeDelete(m_pCurMatch);
	return true;
}
//��������
bool  CGameMatchServiceManager::StartService()
{
	//����ʱ��
	m_pITimerEngine->SetTimer(IDI_TURN_MATCH_START,60000L,TIMES_INFINITY,0);
	m_pITimerEngine->SetTimer(IDI_CHECK_MATCH_GROUP,5000L,TIMES_INFINITY,0);
	m_pITimerEngine->SetTimer(IDI_DELETE_OVER_MATCH, 6000,TIMES_INFINITY,0);
	m_pITimerEngine->SetTimer(IDI_STAR_NEXT_ROUND, 3000,TIMES_INFINITY,0);
	if(m_MatchRule.enFirstRule==FirstRoundRule_Time)
		m_pITimerEngine->SetTimer(IDI_NORMAL_TIMER, 60000,TIMES_INFINITY,0);
#ifdef _DEBUG
	m_pITimerEngine->SetTimer(IDI_HALF_MINUTE,100,TIMES_INFINITY,0);
#else
	m_pITimerEngine->SetTimer(IDI_HALF_MINUTE,3000,TIMES_INFINITY,0);
#endif

 	for (DWORD i=0;i<30;i++)
 	{
 		tagMatchTimerItem *pTimeItem=new tagMatchTimerItem;
 		pTimeItem->dwTimerID=IDI_GROUP_START+i;
 		m_TimerItemFree.Add(pTimeItem);
 	}

    WORD wTableCount=m_MatchRule.wUserCount/m_pGameServiceAttrib->wChairCount;	
    AssignTable(m_pCurMatch, wTableCount);
	return true;
}
//�ӿڲ�ѯ
void *  CGameMatchServiceManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameMatchServiceManager,Guid,dwQueryVer);
	QUERYINTERFACE(IChampionshipMatchSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameMatchServiceManager,Guid,dwQueryVer);
	return NULL;
}

//��ʼ���ӿ�
bool  CGameMatchServiceManager::InitMatchInterface(ITCPNetworkEngineEvent *pTCPNetworkEngine,IDataBaseEngine *pIDataBaseEngine, IServerUserManager *pIServerUserManager,
								 IMainServiceFrame *pIMainServiceFrame,ITimerEngine *pITimerEngine,IAndroidUserManager *pAndroidUserManager)
{
	ASSERT(pTCPNetworkEngine!=NULL && pIDataBaseEngine!=NULL && pIServerUserManager!=NULL && pIMainServiceFrame!=NULL && pITimerEngine!=NULL);
	if(pTCPNetworkEngine==NULL || pIDataBaseEngine==NULL || pIServerUserManager==NULL || pIMainServiceFrame==NULL || pITimerEngine==NULL) return false;

	m_pITCPNetworkEngineEvent=pTCPNetworkEngine;
	m_pIDataBaseEngine=pIDataBaseEngine;
	m_pIServerUserManager=pIServerUserManager;
	m_pIGameServiceFrame=pIMainServiceFrame;
	m_pITimerEngine=pITimerEngine;
	m_pAndroidUserManager=pAndroidUserManager;

	return true;
}

//�û��μӱ���
bool  CGameMatchServiceManager::OnUserJoinGame(IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem == NULL) return false;

	if(m_pCurMatch==NULL || m_pCurMatch->m_bAssignTable==false)
	{
		SendRoomMessage(pIServerUserItem, TEXT("��Ǹ���÷�������������������Ժ��ٱ������߽�����һ���������"),SMT_CHAT);
		return true;;
	}

	if(CServerRule::IsForfendRoomEnter(m_pGameServiceOption->dwServerRule))
	{
		SendRoomMessage(pIServerUserItem, TEXT("��Ǹ������ϵͳά�����÷����ֹ�û�������������"),SMT_CHAT|SMT_EJECT);
		return true;
	}
	INT_PTR dwUserCount=m_OnMatchUserItem.GetCount();
	for (INT_PTR i=0;i<dwUserCount;i++)
	{
		if(m_OnMatchUserItem.GetAt(i)==pIServerUserItem)
		{
			SendRoomMessage(pIServerUserItem, TEXT("���Ѿ��ɹ������������ظ�������"),SMT_CHAT);
			return true;;
		}
	}
	
	INT_PTR nCount=m_OutUserItem.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
	{
		IServerUserItem *pUserItem=m_OutUserItem.GetAt(i);

		if(pUserItem==pIServerUserItem)
		{
			if(pUserItem->GetTableID()!=INVALID_TABLE)
			{
				m_ppITableFrame[pUserItem->GetTableID()]->PerformStandUpAction(pUserItem);
				
				if(pUserItem->GetTableID()!=INVALID_TABLE)
				{
					CString strTace;
					strTace.Format(TEXT("����ʧ�ܣ�%d��"),__LINE__);
					CTraceService::TraceString(strTace,TraceLevel_Exception);
					return false;
				}
			}
			m_OutUserItem.RemoveAt(i);
			break;
		}
	}

	if(pIServerUserItem->GetUserStatus()!=US_FREE || pIServerUserItem->GetTableID()!=INVALID_TABLE)
	{
		SendRoomMessage(pIServerUserItem, TEXT("�Բ�������ǰ��״̬������μӱ�����"),SMT_CHAT);
		return false;
	}

	if(m_MatchRule.dwFee>0 && !pIServerUserItem->IsAndroidUser())
	{
		ASSERT(m_pIGameServiceFrame!=NULL);
		if(m_pIGameServiceFrame==NULL) return false;

		m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_FEE,&m_MatchRule.dwFee, sizeof(DWORD));
		return false;
	}
	
	if(!m_pCurMatch->OnUserSignUp(pIServerUserItem))
	{
		SendRoomMessage(pIServerUserItem, TEXT("����ʧ��"),SMT_CHAT);
		return true;
	}
	else
	{
		m_OnMatchUserItem.Add(pIServerUserItem);
		SendMatchInfo(NULL);
	}
	
	if(m_pIGameServiceFrame!=NULL)
	{
		m_pIGameServiceFrame->SendRoomMessage(pIServerUserItem,TEXT("��ϲ�������ɹ�����ȴ�ϵͳΪ��������λ��"),SMT_EJECT);
	}

	return true;
}

//�û��˳�����
bool  CGameMatchServiceManager::OnUserQuitGame(IServerUserItem * pIServerUserItem, BYTE cbReason,WORD *pBestRank, DWORD dwContextID)
{	
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem == NULL) return false;
        
	bool bJoin=false;
	for (INT_PTR i=0;i<m_OnMatchUserItem.GetCount();i++)
	{
		//��ȡ�û�
		IServerUserItem * pOnLineUserItem=m_OnMatchUserItem[i];

		//�û��ж�
		if (pOnLineUserItem==pIServerUserItem)
		{
			ASSERT(pOnLineUserItem->GetUserID()==pIServerUserItem->GetUserID());
			m_OnMatchUserItem.RemoveAt(i);
			bJoin=true;
			break;
		}
	}
	
	if(bJoin)
	{
		if(m_pCurMatch->OnUserQuitMatch(pIServerUserItem,true))
		{
			if(m_MatchRule.dwFee>0 && !pIServerUserItem->IsAndroidUser())
			{
				DBR_GR_MatchFee MatchFee;
				MatchFee.dwUserID=pIServerUserItem->GetUserID();
				MatchFee.dwMatchFee=m_MatchRule.dwFee;
				MatchFee.dwInoutIndex=pIServerUserItem->GetInoutIndex();
				MatchFee.dwClientAddr=pIServerUserItem->GetClientAddr();
				MatchFee.dwMatchID=m_MatchRule.dwMatchID;
				MatchFee.dwMatchNO=m_pCurMatch->m_dwMatchNO;
				lstrcpyn(MatchFee.szMachineID,pIServerUserItem->GetMachineID(),CountArray(MatchFee.szMachineID));

				m_pIDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_QUIT,dwContextID,&MatchFee,sizeof(MatchFee));
			}
			SendMatchInfo(NULL);
			return true;
		}
		INT_PTR nGroupCount=m_MatchGroup.GetCount();
		for (INT_PTR i=0;i<nGroupCount;i++)
		{
			CChampionshipMatch *pMatch=m_MatchGroup.GetAt(i);
			if(pMatch->OnUserQuitMatch(pIServerUserItem,true))
				return true;
		}

		SendMatchInfo(NULL);
	}
	return false;;
}

//ʱ���¼�
bool  CGameMatchServiceManager::OnEventTimer(DWORD dwTimerID, WPARAM dwBindParameter)
{
	if(dwTimerID>=IDI_GROUP_START)
	{
		INT_PTR nCount=m_TimerItemActive.GetCount();
		tagMatchTimerItem *pTimerItem=NULL;
		for (INT_PTR i=0;i<nCount;i++)
		{
			pTimerItem=m_TimerItemActive.GetAt(i);
			if(pTimerItem->dwTimerID==dwTimerID)
			{
				CChampionshipMatch *pMatch=(CChampionshipMatch*)pTimerItem->wBindParam;
				if(pMatch!=NULL)
				{
					pMatch->OnTimeMessage(pTimerItem->dwRealID,dwBindParameter);					
				}

				else
				{
					INT_PTR wCount=m_MatchGroup.GetCount();
					for (INT_PTR i=0;i<wCount;i++)
					{
						m_MatchGroup.GetAt(i)->OnTimeMessage(dwTimerID,dwBindParameter);
					}
					m_pCurMatch->OnTimeMessage(dwTimerID,dwBindParameter);
				}
				//���ô���
				if (pTimerItem->dwRepeatTimes!=TIMES_INFINITY)
				{
					ASSERT(pTimerItem->dwRepeatTimes>0);
					if (pTimerItem->dwRepeatTimes==1L)
					{
						m_TimerItemActive.RemoveAt(i);
						m_TimerItemFree.Add(pTimerItem);
					}
					else pTimerItem->dwRepeatTimes--;
				}
				return true;
			}
		}
		INT_PTR wCount=m_MatchGroup.GetCount();
		for (INT_PTR i=0;i<wCount;i++)
		{
			m_MatchGroup.GetAt(i)->OnTimeMessage(dwTimerID,dwBindParameter);
		}
		m_pCurMatch->OnTimeMessage(dwTimerID,dwBindParameter);
		return true;
	}

	switch (dwTimerID)
	{
	case IDI_TURN_MATCH_START:
		{
		}
		return true;
	case IDI_START_MATCH_START:
	case IDI_START_MATCH_START+1:
	case IDI_START_MATCH_START+2:
		{
			CChampionshipMatch *pMatch=(CChampionshipMatch*)dwBindParameter;
			if(pMatch->m_enMatchStatus==MS_NULL_STATUS) return true;

			pMatch->StartMatch();
			
			CString str;
			str.Format(TEXT("%s��ʼ��"),m_pGameServiceOption->szServerName);
			//�������ݰ�
			CMD_CM_SystemMessage Message;
			Message.wType=SMT_CHAT;

			lstrcpyn(Message.szString,str,CountArray(Message.szString));
			Message.wLength=CountStringBuffer(Message.szString);

			//��������
			WORD wSendSize=sizeof(Message)-sizeof(Message.szString)+Message.wLength*sizeof(TCHAR);
			SendGroupData(MDM_GF_FRAME,SUB_GF_SYSTEM_MESSAGE,&Message,wSendSize,pMatch);
			
			return true;
		}
	case IDI_DELETE_OUT_USER:
		{
			INT_PTR nCount=m_OutUserItem.GetCount();
			for (INT_PTR i=0;i<nCount;i++)
			{
				IServerUserItem *pUserItem=m_OutUserItem.GetAt(i);
				if(pUserItem!=NULL)
				{
					if(pUserItem->GetTableID()!=INVALID_TABLE)
					{
						m_ppITableFrame[pUserItem->GetTableID()]->PerformStandUpAction(pUserItem);
 						if(pUserItem->GetTableID()!=INVALID_TABLE)
						{
							CString strTace;
							strTace.Format(TEXT("����ʧ�ܣ�%d��"),__LINE__);
							CTraceService::TraceString(strTace,TraceLevel_Exception);
						}
					}		
				}
				
			}
			m_OutUserItem.RemoveAll();			
			
			return true;
		}		
	case IDI_DELETE_OVER_MATCH:
		{
			CChampionshipMatch *pOverMatch=NULL;
			INT_PTR nCount=m_MatchGroup.GetCount();
			for(INT_PTR nOverCount=0;nOverCount<m_OverGroup.GetCount();nOverCount++)
			{
				pOverMatch=m_OverGroup.GetAt(nOverCount);
				for (INT_PTR i=0;i<nCount;i++)
				{
					CChampionshipMatch *pTempMatch=m_MatchGroup.GetAt(i);
					if(pTempMatch==pOverMatch)
					{
						for (WORD j=0;j<pOverMatch->m_wTableCount;j++)
						{
							WORD wTableID=pOverMatch->m_pAssignTable[j].pTableFrame->GetTableID();
							if(wTableID==INVALID_TABLE || wTableID>=m_pGameServiceOption->wTableCount)
								continue;
							bool bSuccess=true;
							for(WORD k=0; k<CChampionshipMatch::m_wChairCount; k++)
							{
								IServerUserItem *pUserTemp=pOverMatch->m_pAssignTable[j].pTableFrame->GetTableUserItem(k);
								if(pUserTemp!=NULL)
								{
									pOverMatch->m_pAssignTable[j].pTableFrame->PerformStandUpAction(pUserTemp);

									if(pOverMatch->m_pAssignTable[j].pTableFrame->GetTableUserItem(k)!=NULL)
									{
										CString str;
										str.Format(TEXT("�����������û���%s����ʧ��,���Ӻţ�%d"),pUserTemp->GetNickName(),wTableID);
										CTraceService::TraceString(str,TraceLevel_Exception);
										bSuccess=false;
										break;
									}
								}
							}
							if(!bSuccess)
							{
								m_UnRecovery.Add(wTableID);
								continue;
							}
							m_bTableUsed[wTableID]=false;
							IGameMatchSink *pSink=m_ppITableFrame[wTableID]->GetGameMatchSink();
							pSink->SetGameEventSink(NULL);
						}
						SafeDelete(pOverMatch);
						m_MatchGroup.RemoveAt(i);
						m_OverGroup.RemoveAt(nOverCount);

						if(m_pCurMatch->m_bAssignTable==false)
						{
							WORD wTableCount=m_MatchRule.wUserCount/m_pGameServiceAttrib->wChairCount;
							AssignTable(m_pCurMatch,wTableCount);
						}
						return true;
					}
				}
			}
			while(m_UnRecovery.GetCount()>0)
			{
				WORD wTableID=m_UnRecovery.GetAt(0);
				bool bSuccess=true;
				for (WORD i=0; i<CChampionshipMatch::m_wChairCount;i++)
				{
					IServerUserItem *pUserItem=m_ppITableFrame[wTableID]->GetTableUserItem(i);
					if(pUserItem!=NULL)
					{
						m_ppITableFrame[wTableID]->PerformStandUpAction(pUserItem);
						if(m_ppITableFrame[wTableID]->GetTableUserItem(i)!=NULL)
						{
							bSuccess=false;
							break;
						}
					}
				}
				if(bSuccess)
				{
					m_UnRecovery.RemoveAt(0);
					m_bTableUsed[wTableID]=false;
					IGameMatchSink *pSink=m_ppITableFrame[wTableID]->GetGameMatchSink();
					pSink->SetGameEventSink(NULL);
					CString str;
					str.Format(TEXT("%d���ӻ��ճɹ�"),wTableID+1);
					CTraceService::TraceString(str,TraceLevel_Normal);
				}
			}

			if(m_pCurMatch->m_bAssignTable==false)
			{
				WORD wTableCount=m_MatchRule.wUserCount/m_pGameServiceAttrib->wChairCount;	
				if(AssignTable(m_pCurMatch, wTableCount))
				{
					SendMatchInfo(NULL);
				}
			}
			return true;
		}
	case IDI_HALF_MINUTE:
		{			
			IAndroidUserItem *pAndroidUserItem=GetFreeAndroidUserItem();
			if(pAndroidUserItem!=NULL)
				OnUserJoinGame(pAndroidUserItem->GetMeUserItem(),0);
		
			return true;
		}
	default:
		ASSERT(false);
		break;
	}

	return true;
}

//�����޸�
bool  CGameMatchServiceManager::RectifyServiceOption(tagGameServiceOption * pGameServiceOption,tagGameServiceAttrib *pGameServiceAttrib)
{
	//Ч�����
	ASSERT(pGameServiceOption!=NULL);
	if (pGameServiceOption==NULL) return false;
	m_pGameServiceOption = pGameServiceOption;
	m_pGameServiceAttrib = pGameServiceAttrib;

	CChampionshipMatch::m_wChairCount=m_pGameServiceAttrib->wChairCount;
	if (m_ppITableFrame==NULL)
	{
		m_ppITableFrame=new ITableFrame*[pGameServiceOption->wTableCount];
		m_bTableUsed=new bool[pGameServiceOption->wTableCount];
	}
	
	//��ȡĿ¼
	TCHAR szPath[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szPath,CountArray(szPath));

	//����·��
	CString szFileName;
	szFileName.Format(TEXT("%s\\MatchOption%d.ini"),szPath,m_pGameServiceOption->wServerID);

	try
	{
		ReadMatchOption(szFileName);
	}
	catch(LPCTSTR pszString)
	{
		CTraceService::TraceString(pszString,TraceLevel_Exception);
		return false;
	}

	if (m_pCurMatch==NULL)
	{
		m_pCurMatch=new CChampionshipMatch(&m_MatchRule, (DWORD)time(NULL), this);
	}

	return true;
}

//��������ģʽ
void *  CGameMatchServiceManager::CreateGameMatchSink(const IID & Guid, DWORD dwQueryVer)
{
	//��������
	CGameMatchSink *pGameMatchSink=NULL;
	//��������
	try
	{
		pGameMatchSink=new CGameMatchSink();
		if (pGameMatchSink==NULL) throw TEXT("����ʧ��");
		void * pObject=pGameMatchSink->QueryInterface(Guid,dwQueryVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		
		return pObject;
	}
	catch (...) {}

	return NULL;
}

//��������
bool  CGameMatchServiceManager::SendDataToServer(DWORD dwUserIndex, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	ASSERT(FALSE);
	return true;
	//��������
	TCP_Command Command;
	Command.wSubCmdID=wSubCmdID;
	Command.wMainCmdID=wMainCmdID;

	//��Ϣ����
	try
	{
		if (m_pITCPNetworkEngineEvent == NULL)
		{
			throw 0;
		}
		if (dwUserIndex>=INDEX_ANDROID)
		{
		
		}
		else
			if (m_pITCPNetworkEngineEvent->OnEventTCPNetworkRead(dwUserIndex,Command,pData,wDataSize)==false)
			{
				throw 0;
			}
	}
	catch (...) 
	{
		ASSERT(FALSE);
		DeleteUserItem(dwUserIndex);
		return false;
	}

	return true;
}

//������������ʼ����
bool CGameMatchServiceManager::OnMatchStart(CChampionshipMatch *pMatch)
{
	try
	{
		ASSERT(pMatch==m_pCurMatch);
		m_pITimerEngine->SetTimer(IDI_START_MATCH_START+(m_dwStartTimeID++)%3,3000L,1,(WPARAM)pMatch);
		m_MatchGroup.Add(pMatch);
		m_pCurMatch=new CChampionshipMatch(&m_MatchRule, (DWORD)time(NULL), this);

		WORD wTableCount=m_MatchRule.wUserCount/m_pGameServiceAttrib->wChairCount;	
		AssignTable(m_pCurMatch, wTableCount);			

		SendMatchInfo(NULL);
		BYTE cbMatchStatus=MS_MATCHING;
		SendGroupData( MDM_GR_MATCH, SUB_GR_MATCH_STATUS, &cbMatchStatus, sizeof(cbMatchStatus),pMatch);

		CMD_GR_Match_Num MatchNum;
		MatchNum.dwWaitting=(DWORD)pMatch->m_OnMatchUserMap.GetCount();
		MatchNum.dwTotal=m_MatchRule.wUserCount;
		MatchNum.dwMatchTotal=(DWORD)m_OnMatchUserItem.GetCount();

		SendGroupData(MDM_GR_MATCH,SUB_GR_MATCH_USER_COUNT,&MatchNum, sizeof(MatchNum),pMatch);
	}
	catch(...)
	{
		CTraceService::TraceString(TEXT("OnMatchStart Exception!"),TraceLevel_Exception);
	}

	return true;
}

//�ȴ���ʱ
bool CGameMatchServiceManager::OnWaitTimeOut(DWORD dwMatchNO)
{
	return true;
}

//�û���̭
bool CGameMatchServiceManager::OnUserOut(IServerUserItem *pUserItem,LPCTSTR szReason,WORD wLen,WORD wRank,CChampionshipMatch *pMatch)
{
	if(pUserItem==NULL)
		return false;
	
	if(wLen>0 && szReason!=NULL)
	{
		CString str(szReason, wLen);
		SendGameMessage(pUserItem,str,SMT_EJECT|SMT_CHAT|SMT_CLOSE_GAME);
	}

	for (INT_PTR i=0;i<m_OnMatchUserItem.GetCount();i++)
	{
		//��ȡ�û�
		IServerUserItem * pOnLineUserItem=m_OnMatchUserItem[i];

		//�û��ж�
		if (pOnLineUserItem==pUserItem)
		{
			m_OnMatchUserItem.RemoveAt(i);
			break;
		}
	}

	m_OutUserItem.Add(pUserItem);
	m_pITimerEngine->SetTimer(IDI_DELETE_OUT_USER, 3000,1,0);
	BYTE cbMatchStatus=MS_NULL;
	m_pIGameServiceFrame->SendData(pUserItem, MDM_GR_MATCH, SUB_GR_MATCH_STATUS, &cbMatchStatus, sizeof(cbMatchStatus));

	if(pMatch==m_pCurMatch)
	{
		if(pUserItem!=NULL && !pUserItem->IsAndroidUser())
		{
			if(m_MatchRule.dwFee>0)
			{
				DBR_GR_MatchFee MatchFee;
				MatchFee.dwUserID=pUserItem->GetUserID();
				MatchFee.dwMatchFee=m_MatchRule.dwFee;
				MatchFee.dwInoutIndex=pUserItem->GetInoutIndex();
				MatchFee.dwClientAddr=pUserItem->GetClientAddr();
				MatchFee.dwMatchID=m_MatchRule.dwMatchID;
				MatchFee.dwMatchNO=m_pCurMatch->m_dwMatchNO;
				lstrcpyn(MatchFee.szMachineID,pUserItem->GetMachineID(),CountArray(MatchFee.szMachineID));

				m_pIDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_QUIT,0,&MatchFee,sizeof(MatchFee));

				CString str;
				str.Format(TEXT("�÷��伴���رգ��뵽�������䱨���������˻�������%d��ҡ�"),m_MatchRule.dwFee);
				m_pIGameServiceFrame->SendRoomMessage(pUserItem,str,SMT_EJECT|SMT_CHAT|SMT_CLOSE_ROOM);
			}
		}
		CServerRule::SetForfendRoomEnter(static_cast<DWORD>(m_pGameServiceOption->dwServerRule),true);
	}
	else if(m_pIDataBaseEngine!=NULL && wRank >=m_RewardArr.GetCount())
	{
		IServerUserItem *pReplaceItem=NULL;
		if(!m_ReplaceUserItem.Lookup(pUserItem->GetUserID(),pReplaceItem))
		{
			DBR_GR_MatchReward MatchReward;
			ZeroMemory(&MatchReward,sizeof(MatchReward));
			MatchReward.dwMatchID=m_MatchRule.dwMatchID;
			MatchReward.dwUserID=pUserItem->GetUserID();
			MatchReward.dwMatchNO=pMatch->m_dwMatchNO;;
			MatchReward.wRank=wRank+1;
			MatchReward.lMatchScore=pUserItem->GetUserScore();
			MatchReward.dwClientAddr=pUserItem->GetClientAddr();

			m_pIDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_REWARD, 0, &MatchReward, sizeof(MatchReward));
		}
		else
			m_ReplaceUserItem.RemoveKey(pUserItem->GetUserID());
	}	

	if(pMatch!=NULL)
	{
		CMD_GR_Match_Num MatchNum;
		MatchNum.dwWaitting=(DWORD)pMatch->m_OnMatchUserMap.GetCount();
		MatchNum.dwTotal=m_MatchRule.wUserCount;
		MatchNum.dwMatchTotal=(DWORD)m_OnMatchUserItem.GetCount();
		
		SendGroupData(MDM_GR_MATCH,SUB_GR_MATCH_USER_COUNT,&MatchNum, sizeof(MatchNum),pMatch);		
	}
	return true;
}

//ɾ���û�
bool CGameMatchServiceManager::DeleteUserItem(DWORD dwUserIndex)
{
	try
	{
		if (m_pITCPNetworkEngineEvent == NULL)
		{
			throw 0;
		}
		m_pITCPNetworkEngineEvent->OnEventTCPNetworkShut(dwUserIndex,0,0L);
	}
	catch (...)
	{
		//�������
		ASSERT(FALSE);
		return false;
	}
	return true;
}

//������Ϣ
bool CGameMatchServiceManager::SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	if(pIServerUserItem==NULL)
		return false;
	//�������ݰ�
	CMD_CM_SystemMessage Message;
	Message.wType=wMessageType;

	lstrcpyn(Message.szString,lpszMessage,CountArray(Message.szString));
	Message.wLength=CountStringBuffer(Message.szString);

	//��������
	WORD wSendSize=sizeof(Message)-sizeof(Message.szString)+Message.wLength*sizeof(TCHAR);
	return m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_CM_SYSTEM,SUB_CM_SYSTEM_MESSAGE,&Message,wSendSize);
}

//������Ϸ��Ϣ
bool CGameMatchServiceManager::SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	if (!pIServerUserItem->IsClientReady())
	{
		return false;
	}
	//�������ݰ�
	CMD_CM_SystemMessage Message;
	Message.wType=wMessageType;
	lstrcpyn(Message.szString,lpszMessage,CountArray(Message.szString));
	Message.wLength=CountStringBuffer(Message.szString);

	//��������
	WORD wSendSize=sizeof(Message)-sizeof(Message.szString)+Message.wLength*sizeof(TCHAR);
	return m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GF_FRAME,SUB_GF_SYSTEM_MESSAGE,&Message,wSendSize);

}

//��ʼ�����ӿ��
bool CGameMatchServiceManager::InitTableFrame(ITableFrame * pTableFrame,WORD wChairID)
{
	if(pTableFrame==NULL || m_ppITableFrame==NULL ||
		wChairID>m_pGameServiceOption->wTableCount)
	{
		ASSERT(false);
		return false;
	}
	m_ppITableFrame[wChairID]=pTableFrame;
	m_bTableUsed[wChairID]=false;
	return true;
}

//��������
bool CGameMatchServiceManager::AssignTable(CChampionshipMatch *pMatch, WORD wTableCount)
{
	ITableFrame **pTable=new ITableFrame*[wTableCount];
	ZeroMemory(pTable,sizeof(ITableFrame*)*wTableCount);
	WORD n=0,wCount=0;
	while((wCount<wTableCount)&&n<m_pGameServiceOption->wTableCount)
	{
		if(!m_bTableUsed[n])
		{
			bool bEmpty=true;
			for(WORD i=0; i<m_pGameServiceAttrib->wChairCount; i++)
			{
				IServerUserItem *pTableUserItem=m_ppITableFrame[n]->GetTableUserItem(i);
				if(pTableUserItem!=NULL)
				{
					try
					{
						CString str;
						str.Format(TEXT("���%s��%s)���ڵ�%d��%d��"),pTableUserItem->GetNickName(),pTableUserItem->IsAndroidUser()?TEXT("������"):TEXT("����"),n+1,i+1);
						CTraceService::TraceString(str,TraceLevel_Exception);
					}
					catch(...)
					{
						CTraceService::TraceString(TEXT("�������Ӵ��󣬻�ȡ�û�ָ�벻Ϊ��Ҳ������Чָ�롣"),TraceLevel_Exception);
					}
					bEmpty=false;
					m_bTableUsed[n]=true;
					m_UnRecovery.Add(m_ppITableFrame[n]->GetTableID());
					n++;
					break;
				}
			}

			if(!bEmpty) continue;

			pTable[wCount]=m_ppITableFrame[n];
			pTable[wCount]->SetCellScore(m_MatchRule.dwInitalBase);
 			IGameMatchSink *pSink=m_ppITableFrame[n]->GetGameMatchSink();
 			pSink->SetGameEventSink(QUERY_OBJECT_PTR_INTERFACE(m_pCurMatch,IUnknownEx));
			m_bTableUsed[n]=true;
			wCount++;
		}
		n++;
	}
	if(n>m_pGameServiceOption->wTableCount || wCount<wTableCount)
	{
		for(WORD i=0;i<wCount;i++)
		{
			if(pTable[i]!=NULL)
			m_bTableUsed[pTable[i]->GetTableID()]=false;
		}
		SafeDeleteArray(pTable);
		return false;
	}
	m_pCurMatch->SetMatchTable(pTable, wTableCount);
	m_pCurMatch->m_bAssignTable=true;
	SafeDeleteArray(pTable);
	return true;
}

//��������
bool CGameMatchServiceManager::SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	if(pIServerUserItem!=NULL)
		return m_pIGameServiceFrame->SendData(pIServerUserItem,wMainCmdID,wSubCmdID,pData,wDataSize);
	else
		return m_pIGameServiceFrame->SendData(BG_COMPUTER, wMainCmdID,wSubCmdID, pData, wDataSize);
    
	return true;
}

//��ȡ��������
bool CGameMatchServiceManager::ReadMatchOption(LPCTSTR lpFileName)
{
	m_MatchRule.dwMatchID=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("MatchID"), (DWORD)-1, lpFileName);
	if(m_MatchRule.dwMatchID==(DWORD)-1)
		throw TEXT("MatchID���ô��󡭡�");
	GetPrivateProfileString(TEXT("MatchOption"), TEXT("MatchName"),TEXT(""), m_MatchRule.szMatchName, LEN_SERVER, lpFileName);
	m_MatchRule.wUserCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("UserCount"), 0, lpFileName);
	if(m_MatchRule.wUserCount==0 || m_MatchRule.wUserCount%CChampionshipMatch::m_wChairCount!=0)
		throw TEXT("����UserCount���󣬿�����������Ϊ0�����ҿ������������ǵ����������ı�����");
	m_MatchRule.wAndroidUserCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("AndroidUserCount"), 0, lpFileName);
	m_MatchRule.wWaitTime=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("WaitTime"), 3, lpFileName);
	m_MatchRule.dwInitalBase=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("InitalBase"), 0, lpFileName);
	if(m_MatchRule.dwInitalBase==0)
		throw TEXT("����InitalBase���󣬳�ʼ���ֱ������0��");
	m_MatchRule.wRemainUserCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("RemainUserCount"), 0, lpFileName);
	m_MatchRule.dwGrowthTime=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("GrowthTime"), 0, lpFileName);
	m_MatchRule.cbGrowthRange=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("GrowthRange"), 0, lpFileName);
	m_MatchRule.dwFee=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("Fee"), 0, lpFileName);
	m_MatchRule.dwInitalScore=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("InitalScore"), 0, lpFileName);
	m_MatchRule.dwSecRoundUserCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("SecRoundUserCount"), 0, lpFileName);
	m_MatchRule.cbLeastScore=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("LeastScore"), 25, lpFileName);
	if(m_MatchRule.cbLeastScore<25)
		m_MatchRule.cbLeastScore=25;
	else if(m_MatchRule.cbLeastScore>200)
		m_MatchRule.cbLeastScore=200;
	m_MatchRule.cbFirScoreRule=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("FirScoreRule"), 0, lpFileName);
	m_MatchRule.cbFirGameCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("FirGameCount"), 0, lpFileName);
	m_MatchRule.cbSecGameCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("SecGameCount"), 0, lpFileName);
	if(m_MatchRule.cbFirGameCount==0 || m_MatchRule.cbSecGameCount==0)
		throw TEXT("����FirGameCount����SecGameCount������Ϸ��������Ϊ0");
	m_MatchRule.cbSecScoreRule=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("SecScoreRule"), 0, lpFileName);
	m_MatchRule.cbSecRoundCount=GetPrivateProfileInt(TEXT("MatchOption"), TEXT("SecRoundCount"), 0, lpFileName);
	if(m_MatchRule.cbSecRoundCount==0 || m_MatchRule.cbSecRoundCount>CountArray(m_MatchRule.arrSecRoundUserCount))
		throw TEXT("����SecRoundCount������Ϸ���������Ǵ���0С��16");

	m_MatchRule.enFirstRule=(enFirstRoundRule)GetPrivateProfileInt(TEXT("MatchOption"), TEXT("FirstRoundRule"), 0, lpFileName);
	if(m_MatchRule.enFirstRule==FirstRoundRule_Time)
	{
		m_MatchRule.dwFirstRoundTime=(DWORD)GetPrivateProfileInt(TEXT("MatchOption"), TEXT("FirstRoundTime"), 0, lpFileName);
		m_MatchRule.dwAheadStatistics=(DWORD)GetPrivateProfileInt(TEXT("MatchOption"), TEXT("AheadStatistics"), 180, lpFileName);
	}
	CString strKey;
	for(BYTE i=0;i<m_MatchRule.cbSecRoundCount;i++)
	{
		strKey.Format(TEXT("Round%d"),i+1);
		WORD wUserCount=GetPrivateProfileInt(TEXT("MatchOption"), strKey, 0, lpFileName);
		m_MatchRule.arrSecRoundUserCount[i]=wUserCount;
	}

	UINT nCount=GetPrivateProfileInt(TEXT("Award"), TEXT("Count"), 0, lpFileName);
	for (BYTE i=0;i<nCount;i++)
	{
		tagMatchReward *pMatchReward=new tagMatchReward;
		strKey.Format(TEXT("Rank%dGold"),i+1);
		pMatchReward->dwGold=GetPrivateProfileInt(TEXT("Award"), strKey, 0, lpFileName);
		strKey.Format(TEXT("Rank%dMedal"),i+1);
		pMatchReward->dwMedal=GetPrivateProfileInt(TEXT("Award"), strKey, 0, lpFileName);
		strKey.Format(TEXT("Rank%dExp"),i+1);
		pMatchReward->dwExperience=GetPrivateProfileInt(TEXT("Award"), strKey, 0, lpFileName);
		m_RewardArr.Add(pMatchReward);
	}

	for(BYTE i=0; i<MAX_MATCH_DESC; i++)
	{
		strKey.Format(TEXT("Title%d"), i+1);
		GetPrivateProfileString(TEXT("MatchDesc"), strKey, TEXT(""), m_MatchDesc.szTitle[i], CountArray(m_MatchDesc.szTitle[i]), lpFileName);
		strKey.Format(TEXT("Describe%d"), i+1);
		GetPrivateProfileString(TEXT("MatchDesc"), strKey, TEXT(""), m_MatchDesc.szDescribe[i], CountArray(m_MatchDesc.szDescribe[i]), lpFileName);
	}

	CWHIniData IniData;
	IniData.SetIniFilePath(lpFileName);
	IniData.ReadColor(m_MatchDesc.crTitleColor, TEXT("MatchDesc"), TEXT("TitleColor"));
	IniData.ReadColor(m_MatchDesc.crDescribeColor, TEXT("MatchDesc"), TEXT("DescribeColor"));
	return true;
}

//��ʱ��
bool CGameMatchServiceManager::SetGameTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM dwBindParameter,CChampionshipMatch *pMatch)
{
	tagMatchTimerItem * pTimerItem=NULL;
	INT_PTR nFreeCount=m_TimerItemFree.GetCount();
	if (nFreeCount>0)
	{
		pTimerItem=m_TimerItemFree[nFreeCount-1];
		ASSERT(pTimerItem!=NULL);
		m_TimerItemFree.RemoveAt(nFreeCount-1);
	}
	else 
	{
		ASSERT(false);
	}
	pTimerItem->dwRealID=dwTimerID;
	pTimerItem->wBindParam=(WPARAM)pMatch;
	pTimerItem->dwRepeatTimes=dwRepeat;
	m_TimerItemActive.Add(pTimerItem);
	return m_pITimerEngine->SetTimer(pTimerItem->dwTimerID,dwElapse,dwRepeat,dwBindParameter);
}

//д�뽱��
bool CGameMatchServiceManager::WriteUserAward(IServerUserItem *pIServerUserItem, WORD wRank,DWORD dwMatchNO,LPCTSTR szDescribe,CChampionshipMatch *pMatch)
{
	//����Ч��
	ASSERT(pIServerUserItem!=NULL);
	if(pIServerUserItem==NULL) return false; 

	OnUserOut(pIServerUserItem, NULL, 0,wRank,pMatch);

	if(wRank<m_RewardArr.GetCount())
	{
		if(pIServerUserItem!=NULL)
		{
			tagMatchReward *pMatchReward=m_RewardArr.GetAt(wRank);
			if(pMatchReward==NULL)
				return false;
			//��������
			CMD_GR_MatchResult MatchResult;
			ZeroMemory(&MatchResult,sizeof(MatchResult));

			//��������
			_sntprintf(MatchResult.szDescribe,CountArray(MatchResult.szDescribe),TEXT("%s, ��ϲ����%s�л�õ�%d��,�������£�"),
				pIServerUserItem->GetNickName(), m_MatchRule.szMatchName, wRank+1);
			MatchResult.dwExperience=pMatchReward->dwExperience;
			MatchResult.dwGold=pMatchReward->dwGold;
			MatchResult.dwMedal=pMatchReward->dwMedal;

			tagUserInfo * pUserInfo=pIServerUserItem->GetUserInfo();
			pUserInfo->dwUserMedal+=pMatchReward->dwMedal;
			pUserInfo->lScore+=(SCORE)pMatchReward->dwGold;
			pUserInfo->dwExperience+=pMatchReward->dwExperience;

			SendGroupUserScore(pIServerUserItem, NULL);

			//��������
			m_pIGameServiceFrame->SendData(pIServerUserItem, MDM_GF_FRAME, SUB_GR_MATCH_RESULT, &MatchResult, sizeof(MatchResult));

			if(m_pIDataBaseEngine!=NULL)
			{
				IServerUserItem *pReplaceItem=NULL;
				if(!m_ReplaceUserItem.Lookup(pIServerUserItem->GetUserID(),pReplaceItem))
				{
					DBR_GR_MatchReward MatchReward;
					ZeroMemory(&MatchReward,sizeof(MatchReward));
					MatchReward.dwMatchID=m_MatchRule.dwMatchID;
					MatchReward.dwUserID=pIServerUserItem->GetUserID();
					MatchReward.dwMatchNO=dwMatchNO;
					MatchReward.wRank=wRank+1;
					MatchReward.dwExperience=pMatchReward->dwExperience;
					MatchReward.dwGold=pMatchReward->dwGold;
					MatchReward.lMatchScore=pIServerUserItem->GetUserScore();
					MatchReward.dwMedal=pMatchReward->dwMedal;
					MatchReward.dwClientAddr=pIServerUserItem->GetClientAddr();

					m_pIDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_REWARD, 0, &MatchReward, sizeof(MatchReward));
				}
				else
					m_ReplaceUserItem.RemoveKey(pIServerUserItem->GetUserID());
			}	
		}
	}
	else
	{
		if(szDescribe==NULL)
		{
			CString str;
			str.Format(TEXT("�����ѽ�������ϲ�����%d����лл���Ĳ��롣�����԰�ȫ�رձ����ͻ��ˣ����������μ�����������"),
				wRank+1);
			SendGameMessage(pIServerUserItem, str,SMT_CHAT|SMT_EJECT|SMT_CLOSE_GAME);
		}
		else
		{
			SendGameMessage(pIServerUserItem, szDescribe, SMT_CHAT|SMT_EJECT|SMT_CLOSE_GAME);
		}
	}
	return true;
}

//��������
bool CGameMatchServiceManager::OnEventMatchOver(CChampionshipMatch *pMatch)
{
	if(pMatch==m_pCurMatch)
	{
		m_MatchGroup.Add(pMatch);

		m_pCurMatch=new CChampionshipMatch(&m_MatchRule, (DWORD)time(NULL), this);

		WORD wTableCount=m_MatchRule.wUserCount/m_pGameServiceAttrib->wChairCount;	
		if(AssignTable(m_pCurMatch, wTableCount))
		{
			SendMatchInfo(NULL);
			BYTE cbMatchStatus=MS_MATCHING;
			SendGroupData( MDM_GR_MATCH, SUB_GR_MATCH_STATUS, &cbMatchStatus, sizeof(cbMatchStatus),pMatch);
		}

		CMD_GR_Match_Num MatchNum;
		MatchNum.dwWaitting=(DWORD)pMatch->m_OnMatchUserMap.GetCount();
		MatchNum.dwTotal=m_MatchRule.wUserCount;
		MatchNum.dwMatchTotal=(DWORD)m_OnMatchUserItem.GetCount();

		m_pIGameServiceFrame->SendData(BG_COMPUTER,MDM_GR_MATCH,SUB_GR_MATCH_USER_COUNT,&MatchNum, sizeof(MatchNum));
	}

	m_OverGroup.Add(pMatch);
	return true;
}

//�����û�����
bool CGameMatchServiceManager::SendGroupUserScore(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch)
{

	//��������
	CMD_GR_UserScore UserScore;
	
	tagUserInfo * pUserInfo=pIServerUserItem->GetUserInfo();

	//��������
	UserScore.dwUserID=pUserInfo->dwUserID;
	UserScore.UserScore.dwWinCount=pUserInfo->dwWinCount;
	UserScore.UserScore.dwLostCount=pUserInfo->dwLostCount;
	UserScore.UserScore.dwDrawCount=pUserInfo->dwDrawCount;
	UserScore.UserScore.dwFleeCount=pUserInfo->dwFleeCount;
	UserScore.UserScore.dwUserMedal=pUserInfo->dwUserMedal;
	UserScore.UserScore.dwExperience=pUserInfo->dwExperience;
	UserScore.UserScore.lLoveLiness=pUserInfo->lLoveLiness;

	//�������
	UserScore.UserScore.lGrade=pUserInfo->lGrade;
	UserScore.UserScore.lInsure=pUserInfo->lInsure;

	//�������
	UserScore.UserScore.lScore=pUserInfo->lScore;

	if(pMatch!=NULL)
	{
		POSITION pos=pMatch->m_OnMatchUserMap.GetStartPosition();
		IServerUserItem *pUserItem=NULL;
		DWORD dwUserID=0;
		while(pos!=NULL)
		{
			pMatch->m_OnMatchUserMap.GetNextAssoc(pos,dwUserID, pUserItem);
			m_pIGameServiceFrame->SendData(pUserItem,MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));	
		}
		INT_PTR nCount=pMatch->m_MaybeOutUser.GetCount();
		for (INT_PTR i=0;i<nCount;i++)
		{
			pUserItem=pMatch->m_MaybeOutUser.GetAt(i);
			m_pIGameServiceFrame->SendData(pUserItem,MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));	
		}
	}
	else
		m_pIGameServiceFrame->SendData(BG_COMPUTER,MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));
	

	return true;
}

//����״̬
bool  CGameMatchServiceManager::SendGroupUserStatus(IServerUserItem * pIServerUserItem,CChampionshipMatch *pMatch)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsClientReady()==true);
	if (pIServerUserItem->IsClientReady()==false) return false;

	//��������
	CMD_GR_UserStatus UserStatus;
	memset(&UserStatus,0,sizeof(UserStatus));
	tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();

	//��������
	UserStatus.dwUserID=pUserData->dwUserID;
	UserStatus.UserStatus.wTableID=pUserData->wTableID;
	UserStatus.UserStatus.wChairID=pUserData->wChairID;
	UserStatus.UserStatus.cbUserStatus=pUserData->cbUserStatus;

	POSITION pos=pMatch->m_OnMatchUserMap.GetStartPosition();
	IServerUserItem *pUserItem=NULL;
	DWORD dwUserID=0;
	while(pos!=NULL)
	{
		pMatch->m_OnMatchUserMap.GetNextAssoc(pos,dwUserID, pUserItem);
		if(pUserItem->IsClientReady())
			m_pIGameServiceFrame->SendData(pUserItem,MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));	
	}

	return true;
}
//�û������ɼ�
bool CGameMatchServiceManager::OnUserMatchResult(DWORD dwUserID, WORD wKindID, WORD wServerID, WORD wSortID)
{
	return true;
}

//�����û�
void CGameMatchServiceManager::UserSort(WORD wTeamID)
{

}

//�������ݵ�������
bool CGameMatchServiceManager::SendDataToGameServer(DWORD dwAndroidID, WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	return SendDataToServer(dwAndroidID,wMainCmdID,wSubCmdID,pData,wDataSize);
}

//�������ݵ�һ���û�
bool CGameMatchServiceManager::SendGroupData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize,CChampionshipMatch *pMatch)
{
	POSITION pos=pMatch->m_OnMatchUserMap.GetStartPosition();
	IServerUserItem *pUserItem=NULL;
	DWORD dwUserID=0;
	while(pos!=NULL)
	{
		pMatch->m_OnMatchUserMap.GetNextAssoc(pos,dwUserID, pUserItem);
		m_pIGameServiceFrame->SendData(pUserItem,wMainCmdID,wSubCmdID,pData,wDataSize);	
	}
	INT_PTR nCount=pMatch->m_MaybeOutUser.GetCount();
	for (INT_PTR i=0;i<nCount;i++)
	{
		pUserItem=pMatch->m_MaybeOutUser.GetAt(i);
		m_pIGameServiceFrame->SendData(pUserItem,wMainCmdID,wSubCmdID,pData,wDataSize);	
	}
    return true;
}

//��ȡһ�����еĻ�����
IAndroidUserItem * CGameMatchServiceManager::GetFreeAndroidUserItem()
{
	if(m_pAndroidUserManager->GetAndroidCount()==0) return NULL;

	//����״̬
	tagAndroidUserInfo AndroidSimulate;
	m_pAndroidUserManager->GetAndroidUserInfo(AndroidSimulate,ANDROID_SIMULATE|ANDROID_PASSIVITY|ANDROID_INITIATIVE);

	if(AndroidSimulate.wFreeUserCount==0) 
		return NULL;
	else
	{
		//�����ѱ����Ļ������ظ�����
		for(WORD i=0; i<AndroidSimulate.wFreeUserCount;i++)
		{
			bool bInMatch=false;
			INT_PTR dwUserCount=m_OnMatchUserItem.GetCount();
			for (INT_PTR j=0;j<dwUserCount;j++)
			{
				if(m_OnMatchUserItem.GetAt(j)==AndroidSimulate.pIAndroidUserFree[i]->GetMeUserItem())
				{
					bInMatch=true;
					break;
				}
			}
			if(!bInMatch)
			{
				ASSERT(AndroidSimulate.pIAndroidUserFree[i]->GetUserID()==AndroidSimulate.pIAndroidUserFree[i]->GetMeUserItem()->GetUserID());
				return AndroidSimulate.pIAndroidUserFree[i];
			}
		}
	}
    
	return NULL;
}

//�����油������
bool CGameMatchServiceManager::SetReplaceAndroidItem(IServerUserItem *pIServerUserItem)
{
	//����Ч��
	ASSERT(pIServerUserItem!=NULL);
	if(pIServerUserItem==NULL) return false;

	INT_PTR dwUserCount=m_OnMatchUserItem.GetCount();
	for (INT_PTR i=0;i<dwUserCount;i++)
	{
		if(m_OnMatchUserItem.GetAt(i)==pIServerUserItem)
			return false;
	}

	m_OnMatchUserItem.Add(pIServerUserItem);
	m_ReplaceUserItem[pIServerUserItem->GetUserID()]=pIServerUserItem;
	return true;
}

//��������
bool CGameMatchServiceManager::SendMatchInfo(IServerUserItem * pIServerUserItem)
{
	CMD_GR_Match_Num MatchNum;
	MatchNum.dwWaitting=(DWORD)m_pCurMatch->m_OnMatchUserMap.GetCount();
	MatchNum.dwTotal=m_MatchRule.wUserCount;
	MatchNum.dwMatchTotal=(DWORD)m_OnMatchUserItem.GetCount();
	if(pIServerUserItem==NULL)
		m_pIGameServiceFrame->SendData(BG_COMPUTER,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));
	else
	{
		m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));

		m_pIGameServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_DESC, &m_MatchDesc, sizeof(m_MatchDesc));

		INT_PTR dwUserCount=m_OnMatchUserItem.GetCount();
		for (INT_PTR i=0;i<dwUserCount;i++)
		{
			if(m_OnMatchUserItem.GetAt(i)==pIServerUserItem)
			{
				BYTE cbMatchStatus=MS_MATCHING;
				m_pIGameServiceFrame->SendData(pIServerUserItem, MDM_GR_MATCH, SUB_GR_MATCH_STATUS, &cbMatchStatus, sizeof(cbMatchStatus));
				return true;;
			}
		}

		tagUserInfo *pUserScore=pIServerUserItem->GetUserInfo();
		pUserScore->lScore=(LONG)m_MatchRule.dwInitalScore;
		pUserScore->dwWinCount=pUserScore->dwLostCount=pUserScore->dwFleeCount=pUserScore->dwDrawCount=0;
		SendGroupUserScore(pIServerUserItem, NULL);
	}

	return true;
}

//���ݿ��¼�
bool CGameMatchServiceManager::OnEventDataBase(WORD wRequestID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)
{
	switch (wRequestID)
	{
	case DBO_GR_MATCH_FEE_RESULT:		//�������
		{
			//����Ч��
			if(pIServerUserItem==NULL) return true;
			if(wDataSize!=sizeof(LONG)) return false;

			//��������
			LONG lReturnValue=*(LONG*)pData;

			if(lReturnValue==0)
			{
				if(!m_pCurMatch->OnUserSignUp(pIServerUserItem))
				{
					SendRoomMessage(pIServerUserItem, TEXT("����ʧ��"),SMT_CHAT);
					return false;
				}
				 m_OnMatchUserItem.Add(pIServerUserItem);
				SendMatchInfo(NULL);
				m_pIGameServiceFrame->SendRoomMessage(pIServerUserItem,TEXT("��ϲ�������ɹ�����ȴ�ϵͳΪ��������λ��"),SMT_EJECT);
				
			}
			else if(lReturnValue==1)
			{
				TCHAR szDescribe[128]=TEXT("");
				_sntprintf(szDescribe,CountArray(szDescribe),TEXT("����Ϸ�Ҳ��������ܼ��������"));
				m_pIGameServiceFrame->SendRoomMessage(pIServerUserItem,szDescribe,SMT_EJECT);
			}
			break;
		}
	case DBO_GR_MATCH_QUIT_RESULT:		//�������
		{
			//����Ч��
			if(pIServerUserItem==NULL) return true;
			if(wDataSize!=sizeof(LONG)) return false;

			//��������
			LONG lReturnValue=*(LONG*)pData;

			if(lReturnValue==0)
			{
				TCHAR szDescribe[128]=TEXT("");
				_sntprintf(szDescribe,CountArray(szDescribe),TEXT("�����ɹ����˻�������%d��Ϸ�ң�"),m_MatchRule.dwFee);
				m_pIGameServiceFrame->SendRoomMessage(pIServerUserItem,szDescribe,SMT_EJECT);				
			}
			break;
		}	
	}
	return true;
}

//������Ϣ
bool CGameMatchServiceManager::OnEventSocketMatch(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem, DWORD dwSocketID)
{
	switch (wSubCmdID)
	{
	case SUB_GR_MATCH_FEE:	//��������
		{
			//����Ч��
			ASSERT(wDataSize==sizeof(DWORD));
			if(wDataSize!=sizeof(DWORD)) return false;

			DWORD dwMatchFee=*(DWORD*)pData;
			if(dwMatchFee!=m_MatchRule.dwFee)return false;

			DBR_GR_MatchFee MatchFee;
			MatchFee.dwUserID=pIServerUserItem->GetUserID();
			MatchFee.dwMatchFee=m_MatchRule.dwFee;
			MatchFee.dwInoutIndex=pIServerUserItem->GetInoutIndex();
			MatchFee.dwClientAddr=pIServerUserItem->GetClientAddr();
			MatchFee.dwMatchID=m_MatchRule.dwMatchID;
			MatchFee.dwMatchNO=m_pCurMatch->m_dwMatchNO;
			lstrcpyn(MatchFee.szMachineID,pIServerUserItem->GetMachineID(),CountArray(MatchFee.szMachineID));

			//Ͷ������
			m_pIDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_FEE,dwSocketID,&MatchFee,sizeof(MatchFee));

			return true;
		}
	case SUB_GR_LEAVE_MATCH:	//�˳�����
		{
			//����Ч��
			ASSERT(pIServerUserItem!=NULL);
			if(pIServerUserItem==NULL) return false;

			if (pIServerUserItem->GetUserStatus()>=US_PLAYING) return true;

			OnUserQuitGame(pIServerUserItem,0,0,dwSocketID);

			return true;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//�����������
DECLARE_CREATE_MODULE(GameMatchServiceManager);

//////////////////////////////////////////////////////////////////////////
