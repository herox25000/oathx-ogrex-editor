#include "StdAfx.h"
#include ".\matchservice.h"
#include "DataBasePacket.h"

//////////////////////////////////////////////////////////////////////////
//��������
#define IDI_MATCH_TIME_PULSE				200							//��������
#define IDI_MATCH_GAME_START				201							//������ʼ
#define IDI_MATCH_GAME_OVER					202							//��������
#define IDI_DISTRIBUTE_TIMER				203							//��ʱ����

BEGIN_MESSAGE_MAP(CDlgAddMatchDate, CDialog)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgAddMatchInfo, CDialog)
END_MESSAGE_MAP()
//���캯��
CTimeRankingsMatch::CTimeRankingsMatch(WORD wMatchID):m_wMatchID(wMatchID)
{
	m_dwMatchFee=100;
	m_pIMainServiceFrame=NULL;
	m_pIKernelDataBaseEngine=NULL;
	ZeroMemory(&m_MatchInfo,sizeof(m_MatchInfo));
	m_cbMatchStatus=MATCH_STATUS_NOT_STARTED;
	m_cbCurMatch=0xFF;
	ZeroMemory(m_szMatchName,sizeof(m_szMatchName));
    m_pMatchRank=NULL;
	m_wRankCount=0;
	m_pParameterDlg=new CMatchParameterDlg(m_MatchInfo,m_uiMatchDate,m_cbMatchTime,m_szMatchName,m_dwMatchFee,m_lInitScore,m_wMatchGameCount,m_wMatchID);
}

//��������
CTimeRankingsMatch::~CTimeRankingsMatch(void)
{
	m_DistributeManage.RemoveAll();
	m_ServerUserItemMap.RemoveAll();

	for(INT_PTR i=0; i<m_MatchInfo.GetCount();i++)
	{
		SafeDelete(m_MatchInfo.GetAt(i));
	}

	if(m_pParameterDlg!=NULL)
		SafeDelete(m_pParameterDlg);

	if(m_pMatchRank!=NULL)
		SafeDeleteArray(m_pMatchRank);

	m_MatchInfo.RemoveAll();
}

//�����¼�
bool CTimeRankingsMatch::OnAttemperEngineStart(IUnknownEx * pIUnknownEx)
{
	StartNextMatch();
	m_pITimerEngine->SetTimer(IDI_MATCH_TIME_PULSE,1000,-1,0);
	m_pITimerEngine->SetTimer(IDI_DISTRIBUTE_TIMER,15000,-1,0);
	return true;
}

//ֹͣ�¼�
bool CTimeRankingsMatch::OnAttemperEngineConclude(IUnknownEx * pIUnknownEx)
{
	m_DistributeManage.RemoveAll();
	m_ServerUserItemMap.RemoveAll();

	for(INT_PTR i=0; i<m_MatchInfo.GetCount();i++)
	{
		SafeDelete(m_MatchInfo.GetAt(i));
	}

	m_MatchInfo.RemoveAll();

	m_dwMatchFee=0;
	m_pIMainServiceFrame=NULL;
	m_pIKernelDataBaseEngine=NULL;
	ZeroMemory(&m_MatchInfo,sizeof(m_MatchInfo));
	return true;
}

//�ӿڲ�ѯ
VOID * CTimeRankingsMatch::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IMatchService,Guid,dwQueryVer);
	QUERYINTERFACE(IMatchTableFrameNotify,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IMatchService,Guid,dwQueryVer);
	return NULL;
}

//�û�����
bool CTimeRankingsMatch::OnUserJoinMatch(IServerUserItem * pIServerUserItem)
{
	TCHAR szDescribe[128]=TEXT("");
	if(m_cbMatchStatus==MATCH_STATUS_NOT_STARTED)
	{
		SYSTEMTIME stBegin = {};
		m_TimeMatchStart.GetAsSystemTime(stBegin);
		_sntprintf( szDescribe,CountArray(szDescribe),TEXT("%s �� [ %ld ] ��������ʼʱ��Ϊ %s�������ĵȺ�"),m_szMatchName,m_cbCurMatch+1,GetTimeString(stBegin));
		m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,szDescribe,SMT_EJECT);
		return true;

	}
	else if(m_cbMatchStatus==MATCH_STATUS_WAIT_FINISH || m_cbMatchStatus==MATCH_STATUS_FINISH)
	{
		if(m_cbCurMatch==m_cbMatchTime-1)
			_sntprintf( szDescribe,CountArray(szDescribe),TEXT("��Ǹ�������Ѿ�ȫ����������ӭ�´βμӱ�����"));
		else
		{
			FILETIME ftBegin = {};
			SYSTEMTIME stBegin = {};
			if(m_cbMatchStatus==MATCH_STATUS_WAIT_FINISH)
				CopyMemory( &ftBegin,&m_uiMatchDate[(m_cbCurMatch+1)*2],sizeof(ftBegin));
			else if(m_cbMatchStatus==MATCH_STATUS_FINISH)
				CopyMemory( &ftBegin,&m_uiMatchDate[(m_cbCurMatch)*2],sizeof(ftBegin));
			CTime tStart(ftBegin);
			tStart.GetAsSystemTime(stBegin);
			_sntprintf( szDescribe,CountArray(szDescribe),TEXT("�������������������³�������ʼʱ��Ϊ%s, �����ĵȴ���"),GetTimeString(stBegin));
		}

		m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,szDescribe,SMT_CHAT);
		return true;
	}

	if(m_wMatchGameCount>0)
	{
		tagUserInfo * pUserInfo=pIServerUserItem->GetUserInfo();
		if(pUserInfo->dwWinCount+pUserInfo->dwLostCount+pUserInfo->dwDrawCount+pUserInfo->dwFleeCount>=m_wMatchGameCount)
		{
			TCHAR szMess[128]=TEXT("\0");
			_sntprintf(szMess, CountArray(szMess), TEXT("��ϲ���Ѿ���ɱ����涨����%d�֣��ȴ�������Ҽ�����Ϸ�󽫹��������ɼ��������ע��"),m_wMatchGameCount);
			m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem, szMess,SMT_EJECT);
			return true;
		}
	}
	if(!CUserRight::IsGameMatchUser(pIServerUserItem->GetUserRight()) && m_dwMatchFee>0)
	{
		ASSERT(m_pIMainServiceFrame!=NULL);
		if(m_pIMainServiceFrame==NULL) return false;

		m_pIMainServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_FEE,&m_dwMatchFee, sizeof(DWORD));
		return false;
	}
	else
	{
		if(pIServerUserItem->GetTableID()==INVALID_TABLE)
			m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,TEXT("��ϲ�������ɹ�����ȴ�ϵͳΪ��������λ��"),SMT_EJECT);
		InsertDistribute(pIServerUserItem);
	}
	return true;
}

//�û�����
bool CTimeRankingsMatch::OnUserQuitMatch(IServerUserItem * pIServerUserItem)
{
	//����Ч��
	ASSERT(pIServerUserItem!=NULL);
	if(pIServerUserItem==NULL) return false;

	if(pIServerUserItem->GetUserStatus()>=US_PLAYING) return true;

	m_DistributeManage.RemoveDistributeNode(pIServerUserItem);
	m_ServerUserItemMap.RemoveKey(pIServerUserItem->GetUserID());

	CMD_GR_Match_Num MatchNum;
	MatchNum.dwWaitting=m_DistributeManage.GetCount();
	MatchNum.dwTotal=(DWORD)m_ServerUserItemMap.GetCount();
	m_pIMainServiceFrame->SendData(BG_COMPUTER,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));
	return true;
}

//�û�׼��
bool CTimeRankingsMatch::OnUserReay(IServerUserItem * pIServerUserItem,WORD wTableID,WORD wChairID)
{
	if(m_cbMatchStatus!=MATCH_STATUS_MATCHING)
	{
		m_pIMainServiceFrame->SendGameMessage(pIServerUserItem,TEXT("��Ǹ���������������������ĵȴ��³�������"),SMT_EJECT|SMT_CLOSE_GAME);
	}
	return true;
}

//���ýӿ�
bool CTimeRankingsMatch::InitMatchService(IMainServiceFrame *pIMainServiceFrame, IDataBaseEngine *pIKernelDataBaseEngine,ITimerEngine *pITimerEngine,
							  tagGameServiceAttrib *pGameServiceAttrib,tagGameServiceOption *pGameServiceOption,CTableFrameArray &TableFrameArray)
{
	//����Ч��
	ASSERT(pIMainServiceFrame!=NULL && pIKernelDataBaseEngine!=NULL && pGameServiceOption!=NULL && pGameServiceAttrib!=NULL && pITimerEngine!=NULL);
	if(pIMainServiceFrame==NULL || pIKernelDataBaseEngine==NULL || pGameServiceOption==NULL || pGameServiceAttrib==NULL || pITimerEngine==NULL) return false;

	m_pIMainServiceFrame=pIMainServiceFrame;
	m_pIKernelDataBaseEngine=pIKernelDataBaseEngine;
	m_pGameServiceOption=pGameServiceOption;
	m_pGameServiceAttrib=pGameServiceAttrib;
	m_TableFrameArray.Append(TableFrameArray);
	for(INT_PTR i=0; i<m_TableFrameArray.GetCount(); i++)
		m_TableFrameArray.GetAt(i)->SetMatchInterface((IUnknownEx*)QueryInterface(IID_IMatchTableFrameNotify,VER_IMatchTableFrameNotify));
	m_pITimerEngine=pITimerEngine;
	return true;
}

//������Ϣ
bool CTimeRankingsMatch::OnEventSocketMatch(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem, DWORD dwSocketID)
{
	switch (wSubCmdID)
	{
	case SUB_GR_MATCH_FEE:	//��������
		{
			//����Ч��
			ASSERT(wDataSize==sizeof(DWORD));
			if(wDataSize!=sizeof(DWORD)) return false;

			DWORD dwMatchFee=*(DWORD*)pData;
			if(dwMatchFee!=m_dwMatchFee)return false;

			DBR_GR_MatchFee MatchFee;
			MatchFee.dwUserID=pIServerUserItem->GetUserID();
			MatchFee.dwMatchFee=m_dwMatchFee;
			MatchFee.dwInoutIndex=pIServerUserItem->GetInoutIndex();
			MatchFee.dwClientAddr=pIServerUserItem->GetClientAddr();
			lstrcpyn(MatchFee.szMachineID,pIServerUserItem->GetMachineID(),CountArray(MatchFee.szMachineID));

			//Ͷ������
			m_pIKernelDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_FEE,dwSocketID,&MatchFee,sizeof(MatchFee));
			return true;
		}
	case SUB_GR_LEAVE_MATCH:	//�˳�����
		{
			//����Ч��
			ASSERT(pIServerUserItem!=NULL);
			if(pIServerUserItem==NULL) return false;

			if(pIServerUserItem->GetUserStatus()>=US_PLAYING) return true;

			m_DistributeManage.RemoveDistributeNode(pIServerUserItem);
			m_ServerUserItemMap.RemoveKey(pIServerUserItem->GetUserID());

			CMD_GR_Match_Num MatchNum;
			MatchNum.dwWaitting=m_DistributeManage.GetCount();
			MatchNum.dwTotal=(DWORD)m_ServerUserItemMap.GetCount();
			m_pIMainServiceFrame->SendData(BG_COMPUTER,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));
			
            return true;
		}
	}
	return true;
}

//�������
bool CTimeRankingsMatch::InsertDistribute(IServerUserItem * pIServerUserItem)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//״̬�ж�
	ASSERT(pIServerUserItem->GetUserStatus()<US_PLAYING);
	if (pIServerUserItem->GetUserStatus()>=US_PLAYING) return false;

	//��������
	tagDistributeInfo DistributeInfo;
	ZeroMemory(&DistributeInfo,sizeof(DistributeInfo));

	//���ñ���
	DistributeInfo.pIServerUserItem=pIServerUserItem;
	DistributeInfo.wLastTableID=pIServerUserItem->GetTableID();
	DistributeInfo.dwClientAddr=pIServerUserItem->GetClientAddr();
	DistributeInfo.pPertainNode=NULL;

	//��������
	m_DistributeManage.InsertDistributeNode(DistributeInfo);

	m_ServerUserItemMap[pIServerUserItem->GetUserID()]=pIServerUserItem;

	//�û�����
	if (pIServerUserItem->GetTableID()!=INVALID_TABLE)
	{
		WORD wTableID=pIServerUserItem->GetTableID();
		//m_TableFrameArray[wTableID]->PerformStandUpAction(pIServerUserItem);
	}

	//�����ж�
// 	bool bDistribute=false;
// 	if (m_pGameServiceOption->cbDistributeRule&DISTRIBUTE_IMMEDIATE) bDistribute=true;
// 	if ((m_pGameServiceOption->wMaxDistributeUser!=0)&&(m_DistributeManage.GetCount()>=m_pGameServiceOption->wMaxDistributeUser)) bDistribute=true;
// 
// 	//ִ�з���
// 	if (bDistribute==true)
// 	{
// 		PerformDistribute();
// 	}

 	CMD_GR_Match_Num MatchNum;
 	MatchNum.dwWaitting=m_DistributeManage.GetCount();
 	MatchNum.dwTotal=(DWORD)m_ServerUserItemMap.GetCount();
 		m_pIMainServiceFrame->SendData(BG_COMPUTER,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));

	return true;
}


//�����û�
bool CTimeRankingsMatch::PerformDistribute()
{
	//����У��
//	if(m_DistributeManage.GetCount()<m_pGameServiceOption->wMinDistributeUser) return false;

	//�����û�
	while(true)
	{
		//����У��
		//ASSERT(m_DistributeManage.GetCount()>=m_pGameServiceOption->wMinGameUser);
		//if(m_DistributeManage.GetCount()<m_pGameServiceOption->wMinGameUser) return false;
		if(m_DistributeManage.GetRealCount()==0) return false;

		//��������
		CDistributeInfoArray DistributeInfoArray;

		//��ȡ�û�
		//WORD wRandCount = __max(m_pGameServiceOption->wMaxGameUser-m_pGameServiceOption->wMinGameUser+1,1);
		//WORD wChairCount = m_pGameServiceOption->wMinGameUser+rand()%wRandCount;
		WORD wDistributeCount = m_DistributeManage.PerformDistribute(DistributeInfoArray,m_pGameServiceAttrib->wChairCount);
		if(wDistributeCount < m_pGameServiceAttrib->wChairCount) break;

		//Ѱ��λ��
		CTableFrame * pCurrTableFrame=NULL;
		for (WORD i=0;i<m_TableFrameArray.GetCount();i++)
		{
			//��ȡ����
			ASSERT(m_TableFrameArray[i]!=NULL);
			CTableFrame * pTableFrame=m_TableFrameArray[i];

			//״̬�ж�
			if (pTableFrame->GetSitUserCount()==0)
			{
				pCurrTableFrame=pTableFrame;
				break;
			}
		}

		//�����ж�
		if(pCurrTableFrame==NULL) break;

		//�������
		bool bSitSuccess=true;
		INT_PTR nSitFailedIndex=INVALID_CHAIR;
		for(INT_PTR nIndex=0;nIndex<DistributeInfoArray.GetCount();nIndex++)
		{
			//��������
			WORD wChairID=pCurrTableFrame->GetNullChairID();

			//�����û�
			if (wChairID!=INVALID_CHAIR)
			{
				//��ȡ�û�
				IServerUserItem * pIServerUserItem=DistributeInfoArray[nIndex].pIServerUserItem;

				//�û�����
				if(pIServerUserItem->GetTableID()!=INVALID_TABLE)
				{
					WORD wTableID=pIServerUserItem->GetTableID();
					m_TableFrameArray[wTableID]->PerformStandUpAction(pIServerUserItem);
				}

				//�û�����
				if(pCurrTableFrame->PerformSitDownAction(wChairID,pIServerUserItem)==false)
				{
					bSitSuccess=false;
					nSitFailedIndex=nIndex;
					break;
				}
			}
		}

		//���´���
		if(bSitSuccess)
		{
			//�Ƴ����
			while(DistributeInfoArray.GetCount()>0)
			{
				m_DistributeManage.RemoveDistributeNode((tagDistributeNode *)DistributeInfoArray[0].pPertainNode);
				DistributeInfoArray.RemoveAt(0);
			}
		}
		else
		{
			for(INT_PTR nIndex=0;nIndex<DistributeInfoArray.GetCount();nIndex++)
			{
				if(nSitFailedIndex==nIndex)
					m_DistributeManage.RemoveDistributeNode((tagDistributeNode *)DistributeInfoArray[nIndex].pPertainNode);
				else
				{
					//�û�����
					if (DistributeInfoArray[nIndex].pIServerUserItem->GetTableID()!=INVALID_TABLE)
					{
						WORD wTableID=DistributeInfoArray[nIndex].pIServerUserItem->GetTableID();
						m_TableFrameArray[wTableID]->PerformStandUpAction(DistributeInfoArray[nIndex].pIServerUserItem);
					}
				}
			}
		}		
	}


	for(WORD i=0; i<m_pGameServiceOption->wTableCount; i++)
	{
		//��ȡ����
		CTableFrame * pTableFrame=m_TableFrameArray[i];
		if(pTableFrame==NULL)continue;

		//״̬�ж�
		WORD wSitUserCount=pTableFrame->GetSitUserCount();
		if(pTableFrame->IsGameStarted() || wSitUserCount==m_pGameServiceAttrib->wChairCount || wSitUserCount==0) continue;

		if(m_pGameServiceAttrib->wChairCount-wSitUserCount>m_pGameServiceAttrib->wChairCount/2)
		{
//			for(WORD j=0; j)
		}
	}

	return true;
}

//������Ϣ
bool CTimeRankingsMatch::SendMatchInfo(IServerUserItem * pIServerUserItem)
{
	CMD_GR_Match_Num MatchNum;
	MatchNum.dwWaitting=m_DistributeManage.GetCount();
	MatchNum.dwTotal=(DWORD)m_ServerUserItemMap.GetCount();
	m_pIMainServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_NUM,&MatchNum, sizeof(MatchNum));


	if(m_MatchInfo.GetCount()>0)
	{
		CMD_GR_Match_Info *pMatchInfo=new CMD_GR_Match_Info[m_MatchInfo.GetCount()];
		for(INT_PTR i=0; i<m_MatchInfo.GetCount();i++)
		{
			CopyMemory(&pMatchInfo[i],m_MatchInfo.GetAt(i),sizeof(CMD_GR_Match_Info));
		}
		m_pIMainServiceFrame->SendData(pIServerUserItem,MDM_GR_MATCH,SUB_GR_MATCH_INFO,pMatchInfo,(WORD)(sizeof(CMD_GR_Match_Info)*m_MatchInfo.GetCount()));
		delete [] pMatchInfo;
	}
	return true;
}

//���ݿ��¼�
bool CTimeRankingsMatch::OnEventDataBase(WORD wRequestID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)
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
				pIServerUserItem->ModifyUserRight(UR_GAME_MATCH_USER,0);
				InsertDistribute(pIServerUserItem);
				m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,TEXT("��ϲ�������ɹ�����ȴ�ϵͳΪ��������λ��"),SMT_EJECT);
			}
			else if(lReturnValue==1)
			{
				TCHAR szDescribe[128]=TEXT("");
				_sntprintf(szDescribe,CountArray(szDescribe),TEXT("����Ϸ�Ҳ��������ܼ��������"));
				m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,szDescribe,SMT_EJECT);
			}
			break;
		}
	case DBO_GR_MATCH_RANK:			//��������
		{
            //����Ч��
			ASSERT(wDataSize%sizeof(DBO_GR_MatchRank)==0);
			if(wDataSize%sizeof(DBO_GR_MatchRank)!=0) return false;

			DBO_GR_MatchRank *pMatchRank=(DBO_GR_MatchRank *)pData;
			m_wRankCount=wDataSize/sizeof(DBO_GR_MatchRank);
			m_pMatchRank=new CMD_GR_MatchRank[m_wRankCount];
			
			for(WORD i=0; i<m_wRankCount; i++)
			{
				m_pMatchRank[i].cbRank=pMatchRank[i].cbRank;
				m_pMatchRank[i].lMatchScore=pMatchRank[i].lMatchScore;
				lstrcpyn(m_pMatchRank[i].szNickName, pMatchRank[i].szNickName, LEN_NICKNAME);		
			}
            
			m_pIMainServiceFrame->SendData(BG_COMPUTER, MDM_GR_MATCH, SUB_GR_MATCH_RANK, m_pMatchRank,sizeof(CMD_GR_MatchRank)*m_wRankCount);
		}
		break;
	}
	return true;
}

//���ò���
bool CTimeRankingsMatch::ModifyMatchParameter()
{
	m_pParameterDlg->DoModal();
	
	return true;
}

//ʱ���¼�
bool CTimeRankingsMatch::OnEventTimer(DWORD dwTimerID, WPARAM dwBindParameter)
{
	if(dwTimerID==IDI_MATCH_TIME_PULSE)
	{
		if(m_cbCurMatch==0xFF || m_cbMatchStatus== MATCH_STATUS_FINISH) return true;
		CTime CurTime=CTime::GetCurrentTime();

		if(m_cbMatchStatus==MATCH_STATUS_NOT_STARTED)
		{
			if((m_TimeMatchStart==CurTime))
			{
				m_cbMatchStatus=MATCH_STATUS_MATCHING;
				CString strMsg;
				strMsg.Format(TEXT("%s ������[ %d ]����ʼ�ˣ�"),m_szMatchName,m_cbCurMatch+1);
				m_pIMainServiceFrame->SendRoomMessage(strMsg,SMT_CHAT);
				CTraceService::TraceString(strMsg,TraceLevel_Normal);

				//֪ͨ����
				if(m_pIMainServiceFrame!=NULL) m_pIMainServiceFrame->OnEventMatchStart(m_lInitScore);

				//��������
				DBR_GR_MatchStart MatchStart;
				MatchStart.wMatchID=m_wMatchID;
				MatchStart.wMatchNo=(WORD)m_cbCurMatch;
				MatchStart.wMatchCount=(WORD)m_cbMatchTime;
				MatchStart.lInitScore=m_lInitScore;

				m_pIKernelDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_START,0,&MatchStart,sizeof(MatchStart));
			}
		}
		else if(m_cbMatchStatus==MATCH_STATUS_MATCHING)
		{
			CTimeSpan span=m_TimeMatchOver-CurTime;
			if(span.GetTotalMinutes()<=5)
			{
				TCHAR szMess[128] = {};
				_sntprintf(szMess,CountArray(szMess),TEXT("��λ���ע�⣬�� [ %ld ] ������5�����ڼ������������Ҽӽ�ʱ�䣡"),m_cbCurMatch+1);
				m_pIMainServiceFrame->SendGameMessage(szMess,SMT_CHAT);
				m_pIMainServiceFrame->SendRoomMessage(szMess,SMT_CHAT);
				m_cbMatchStatus=MATCH_STATUS_WAIT_FINISH;
				CTraceService::TraceString(szMess,TraceLevel_Normal);
			}
		}
		else if(m_cbMatchStatus==MATCH_STATUS_WAIT_FINISH)
		{
			CTimeSpan span=m_TimeMatchOver-CurTime;
			if(span.GetTotalSeconds()<=30)
			{
				for(INT_PTR i=0; i<m_TableFrameArray.GetCount(); i++)
				{
					if(m_TableFrameArray.GetAt(i)->IsGameStarted())
						m_TableFrameArray.GetAt(i)->DismissGame();
				}
			}
			for(INT_PTR i=0; i<m_TableFrameArray.GetCount(); i++)
			{
				if(m_TableFrameArray.GetAt(i)->IsGameStarted())
					return true;
			}

			m_DistributeManage.RemoveAll();
			POSITION pos=m_ServerUserItemMap.GetStartPosition();
			DWORD dwUserID;
			IServerUserItem *pIServerUserItem=NULL;
			while(pos!=NULL)
			{
				m_ServerUserItemMap.GetNextAssoc(pos,dwUserID, pIServerUserItem);
				if(pIServerUserItem!=NULL)
					m_pIMainServiceFrame->SendRoomMessage(pIServerUserItem,TEXT(""),SMT_CLOSE_GAME);
			}
			m_ServerUserItemMap.RemoveAll();
			if(abs((int)span.GetTotalSeconds())<=1)
			{
				TCHAR szMess[128] = {};
				_sntprintf(szMess,CountArray(szMess),TEXT("�� [ %ld ] ����������"),m_cbCurMatch+1);
				CTraceService::TraceString(szMess,TraceLevel_Normal);

				m_cbMatchStatus=MATCH_STATUS_FINISH;
				DBR_GR_MatchOver MatchOver;
				MatchOver.wMatchID=m_wMatchID;
				MatchOver.wMatchNo=(WORD)m_cbCurMatch;
				MatchOver.wMatchCount=(WORD)m_cbMatchTime;

				m_pIKernelDataBaseEngine->PostDataBaseRequest(DBR_GR_MATCH_OVER,0,&MatchOver,sizeof(MatchOver));

				if(m_cbCurMatch<m_cbMatchTime-1)
					StartNextMatch();
			}
		}

	}
	else if(dwTimerID==IDI_DISTRIBUTE_TIMER)
	{
		PerformDistribute();
	}
	return true;
}

//��ʼ��һ������
VOID CTimeRankingsMatch::StartNextMatch()
{
	//�������ʱ��
	CTime CurTime = CTime::GetCurrentTime();
	BYTE i=0;
	for(i=0; i<m_cbMatchTime; i++)
	{
		FILETIME ftBegin = {};
		FILETIME ftEnd = {};
		CopyMemory( &ftBegin,&m_uiMatchDate[i*2],sizeof(ftBegin) );
		CopyMemory( &ftEnd,&m_uiMatchDate[i*2+1],sizeof(ftEnd) );
		CTime TimeBegin(ftBegin);
		CTime TimeEnd(ftEnd);

		if(CurTime< TimeBegin)
		{
			m_TimeMatchStart = TimeBegin;
			m_TimeMatchOver = TimeEnd;
			m_cbCurMatch=i;
			m_cbMatchStatus=MATCH_STATUS_NOT_STARTED;
			break;
		}
		if( TimeBegin <= CurTime && TimeEnd > CurTime)
		{
			m_TimeMatchStart = TimeBegin;
			m_TimeMatchOver = TimeEnd;
			m_cbCurMatch=i;
			m_cbMatchStatus=MATCH_STATUS_MATCHING;
			CTimeSpan span;
			span=TimeEnd-CurTime;
			if(span.GetTotalMinutes()<=5)
				m_cbMatchStatus=MATCH_STATUS_WAIT_FINISH;
			break;
		}
	}

	//���ñ���
	if(i==m_cbMatchTime) 
	{
		m_cbMatchStatus=MATCH_STATUS_FINISH;
		m_cbCurMatch=m_cbMatchTime-1;
	}
	
	if( m_cbMatchStatus==MATCH_STATUS_NOT_STARTED || m_cbMatchStatus==MATCH_STATUS_MATCHING)
	{
		//��ʾ��Ϣ
		TCHAR szMess[256] = TEXT("");
		TCHAR szStart[32] = TEXT("");
		TCHAR szOver[32] = TEXT("");
		SYSTEMTIME stBegin = {};
		m_TimeMatchStart.GetAsSystemTime(stBegin);

		SYSTEMTIME stEnd = {};
		m_TimeMatchOver.GetAsSystemTime(stEnd);
		lstrcpyn( szStart,GetTimeString(stBegin),CountArray(szStart) );
		lstrcpyn( szOver,GetTimeString(stEnd),CountArray(szOver) );
		_sntprintf( szMess,CountArray(szMess),TEXT("%s �� [ %ld ] ���������� %s �� %s ���С�"),m_szMatchName,m_cbCurMatch+1,szStart,szOver );
		m_pIMainServiceFrame->SendRoomMessage(szMess,SMT_CHAT);
		CTraceService::TraceString(szMess,TraceLevel_Normal);
	}
	else if(m_cbMatchStatus==MATCH_STATUS_FINISH)
	{
		//��ʾ��Ϣ
		CTraceService::TraceString(TEXT("����ȫ��������"),TraceLevel_Normal);
	}

	return;
}

//��Ϸ����
bool CTimeRankingsMatch::OnEventGameEnd(WORD wTableID)
{
	if(m_wMatchGameCount>0)
	{
		//����Ч��
		if(wTableID>=m_TableFrameArray.GetCount()) return false;

		//��������
		CTableFrame * pTableFrame=m_TableFrameArray[wTableID];
		if(pTableFrame==NULL) return false;

		for(WORD i=0; i<m_pGameServiceAttrib->wChairCount; i++)
		{
			IServerUserItem *pIServerUserItem=pTableFrame->GetTableUserItem(i);
			if(pIServerUserItem==NULL) continue;

			//��������
			tagUserInfo * pUserInfo=pIServerUserItem->GetUserInfo();
			DWORD dwGameCount=pUserInfo->dwWinCount+pUserInfo->dwLostCount+pUserInfo->dwDrawCount+pUserInfo->dwFleeCount;
			if(dwGameCount>=m_wMatchGameCount)
			{
				TCHAR szMess[128]=TEXT("\0");
				_sntprintf(szMess, CountArray(szMess), TEXT("��ϲ���Ѿ���ɱȽϹ涨����%d�֣��ȴ�������Ҽ�����Ϸ�󽫹��������ɼ��������ע��"),m_wMatchGameCount);
                m_pIMainServiceFrame->SendGameMessage(pIServerUserItem, szMess,SMT_EJECT|SMT_CLOSE_GAME);
			}
			else
			{
				TCHAR szMess[128] = TEXT("");
				_sntprintf( szMess,CountArray(szMess),TEXT("���Ѿ����%d�֣���%d�֡�"),dwGameCount,m_wMatchGameCount);
				m_pIMainServiceFrame->SendGameMessage(pIServerUserItem,szMess,SMT_CHAT);
			}
		}
	}
	if(m_cbMatchStatus!=MATCH_STATUS_WAIT_FINISH) return true;
	for(INT_PTR i=0; i<m_TableFrameArray.GetCount(); i++)
	{
		if(m_TableFrameArray.GetAt(i)->IsGameStarted())
			return true;
	}

	return true;
}

//��ȡʱ���ַ���
LPCTSTR CTimeRankingsMatch::GetTimeString( SYSTEMTIME &st )
{
	//��������
	static TCHAR szTime[32] = TEXT("");

	_sntprintf(szTime,CountArray(szTime),TEXT("%4d��%02d��%02d�� %02dʱ%02d��%02d��"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	return szTime;
}

//////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMatchParameterDlg, CDialog)
	ON_BN_CLICKED(IDC_BT_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BT_MODIFY, OnBnClickedModify)
	ON_BN_CLICKED(IDC_BT_DELETE, OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BT_ADD_INFO, OnBnClickedAddInfo)
	ON_BN_CLICKED(IDC_BT_MODIFY_INFO, OnBnClickedModifyInfo)
	ON_BN_CLICKED(IDC_BT_DELETE_INFO, OnBnClickedDeleteInfo)
END_MESSAGE_MAP()

CMatchParameterDlg::CMatchParameterDlg(CMatchInfoArray &MatchInfo,ULARGE_INTEGER *puiMatchDate,BYTE &cbMatchTime, TCHAR *pszMatchRoom,DWORD &dwMatchFee,\
									   LONG &lInitScore, WORD &wMatchGameCount,WORD wMatchID):
					CDialog(IDD),m_MatchInfo(MatchInfo),m_puiMatchDate(puiMatchDate),m_cbMatchTime(cbMatchTime),m_pszMatchRoom(pszMatchRoom),m_dwMatchFee(dwMatchFee),
						m_lInitScore(lInitScore),m_wMatchGameCount(wMatchGameCount), m_wMatchID(wMatchID)
{
	//���ñ���
	m_cbMatchTime = 0;
	ZeroMemory( m_puiMatchDate,sizeof(m_puiMatchDate) );

	//��ȡĿ¼
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);

	//��ȡ����
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_sntprintf(szFileName,sizeof(szFileName),TEXT("%s\\MatchOption.ini"),szPath);

	//��Ϣ����
	CString strTemp,strAppName,strValue;
	strAppName.Format(TEXT("%dTimeRankings"),m_wMatchID);
	UINT uItemCount=GetPrivateProfileInt(strAppName,TEXT("InfoItemCount"),0,szFileName);
	
	//��ȡ����
	m_cbMatchTime=(BYTE)GetPrivateProfileInt(strAppName,TEXT("MatchCount"),0,szFileName);
	ASSERT(m_cbMatchTime<MAX_MATCH_COUNT);
	if(m_cbMatchTime>=MAX_MATCH_COUNT)return ;

	//��ȡ����
	m_dwMatchFee=(UINT)GetPrivateProfileInt(strAppName,TEXT("MatchFee"),0,szFileName);

	//��ȡ����
	GetPrivateProfileString(strAppName,TEXT("MatchRoom"),TEXT(""), m_pszMatchRoom,32,szFileName);

	//��ʼ����
	m_lInitScore=(LONG)GetPrivateProfileInt(strAppName,TEXT("InitScore"),0,szFileName);

	//��������
	m_wMatchGameCount=(WORD)GetPrivateProfileInt(strAppName,TEXT("MatchGameCount"),0,szFileName);

	//��ȡ��Ϣ
	for(UINT i=0; i<uItemCount; i++)
	{
		CMD_GR_Match_Info *pMatchInfo=new CMD_GR_Match_Info;
		strAppName.Format(TEXT("%dItem%d"),m_wMatchID,i);
		GetPrivateProfileString(strAppName,TEXT("InfoTitle"),TEXT(""),pMatchInfo->szTitle,CountArray(pMatchInfo->szTitle),szFileName);
		GetPrivateProfileString(strAppName,TEXT("InfoDescribe"),TEXT(""),pMatchInfo->szDescribe,CountArray(pMatchInfo->szDescribe),szFileName);
		strValue.Format(TEXT("%d"),pMatchInfo->wTitleLen);
		pMatchInfo->wTitleLen=(WORD)GetPrivateProfileInt(strAppName,TEXT("InfoTitleLen"),0,szFileName);
		pMatchInfo->wDescribeLen=(WORD)GetPrivateProfileInt(strAppName,TEXT("InfoDescribeLen"),0,szFileName);
		m_MatchInfo.Add(pMatchInfo);
	}

	//������Ϣ
	TCHAR szValue[32]=TEXT("");
	for(BYTE i=0; i<m_cbMatchTime; i++)
	{
		strAppName.Format(TEXT("%dMatchDate%d"),m_wMatchID,i);
		GetPrivateProfileString(strAppName,TEXT("TimeStart"),TEXT(""),szValue,15,szFileName);
		//��ȡʱ��
		SYSTEMTIME stTime;
		CString strValue(szValue);
		stTime.wYear=_ttoi(strValue.Left(4));
		stTime.wMonth=_ttoi(strValue.Mid(4,2));
		stTime.wDay=_ttoi(strValue.Mid(6,2));
		stTime.wHour=_ttoi(strValue.Mid(8,2));
		stTime.wMinute=_ttoi(strValue.Mid(10,2));
		stTime.wSecond=_ttoi(strValue.Mid(12,2));

		SYSTEMTIME st = {};
		CTime TimeBegin(stTime);		
		TimeBegin.GetAsSystemTime(st);
		FILETIME ft = {}, ftUTC = {};
		::SystemTimeToFileTime(&st,&ft);
		::LocalFileTimeToFileTime(&ft,&ftUTC);
		CopyMemory( &m_puiMatchDate[i*2],&ftUTC,sizeof(ftUTC) );

		GetPrivateProfileString(strAppName,TEXT("TimeEnd"),TEXT(""),szValue,15,szFileName);
		//��ȡʱ��
		strValue=CString(szValue);
		stTime.wYear=_ttoi(strValue.Left(4));
		stTime.wMonth=_ttoi(strValue.Mid(4,2));
		stTime.wDay=_ttoi(strValue.Mid(6,2));
		stTime.wHour=_ttoi(strValue.Mid(8,2));
		stTime.wMinute=_ttoi(strValue.Mid(10,2));
		stTime.wSecond=_ttoi(strValue.Mid(12,2));

		CTime TimeEnd(stTime);		
		TimeEnd.GetAsSystemTime(st);
		::SystemTimeToFileTime(&st,&ft);
		::LocalFileTimeToFileTime(&ft,&ftUTC);
		CopyMemory( &m_puiMatchDate[i*2+1],&ftUTC,sizeof(ftUTC) );
	}
		
}
CMatchParameterDlg::~CMatchParameterDlg()
{

}

//���ʱ��
VOID CMatchParameterDlg::OnBnClickedAdd()
{
	if( m_cbMatchTime == MAX_MATCH_COUNT )
	{
		AfxMessageBox( TEXT("�������δﵽ��������ˣ����������"),MB_ICONINFORMATION );
		return;
	}

	CDlgAddMatchDate Dlg;
	if( IDOK == Dlg.DoModal() )
	{
		//��ӿ�ʼʱ��
		SYSTEMTIME st = {};
		Dlg.m_TimeBegin.GetAsSystemTime(st);
		FILETIME ft = {}, ftUTC = {};
		::SystemTimeToFileTime(&st,&ft);
		::LocalFileTimeToFileTime(&ft,&ftUTC);
		CopyMemory( &m_puiMatchDate[m_cbMatchTime*2],&ftUTC,sizeof(ftUTC) );

		//��ӽ���ʱ��
		Dlg.m_TimeEnd.GetAsSystemTime(st);
		::SystemTimeToFileTime(&st,&ft);
		::LocalFileTimeToFileTime(&ft,&ftUTC);
		CopyMemory( &m_puiMatchDate[m_cbMatchTime*2+1],&ftUTC,sizeof(ftUTC) );

		m_cbMatchTime++;

		UpdateMatchList();
	}

	return;
}

//�޸�ʱ��
VOID CMatchParameterDlg::OnBnClickedModify()
{
	POSITION pos = m_ListMatch.GetFirstSelectedItemPosition();
	if( pos == NULL )
	{
		AfxMessageBox( TEXT("��ѡ��Ҫ�޸ĵĳ���"),MB_ICONINFORMATION );
		return;
	}

	//��ȡѡ����
	int nItem = m_ListMatch.GetNextSelectedItem(pos);

	//��ȡ����
	DWORD_PTR dwMatchIndex = m_ListMatch.GetItemData(nItem);

	//��ȡʱ��
	FILETIME ftBegin = {};
	CopyMemory( &ftBegin,&m_puiMatchDate[dwMatchIndex*2],sizeof(ftBegin) );
	FILETIME ftEnd = {};
	CopyMemory( &ftEnd,&m_puiMatchDate[dwMatchIndex*2+1],sizeof(ftEnd) );

	CTime TimeBegin(ftBegin);
	CTime TimeEnd(ftEnd);

	//����Ի���
	CDlgAddMatchDate Dlg;
	Dlg.m_TimeBegin = TimeBegin;
	Dlg.m_TimeEnd = TimeEnd;

	//��ʾ�Ի���
	if( IDOK == Dlg.DoModal() )
	{
		if( Dlg.m_TimeBegin != TimeBegin || Dlg.m_TimeEnd != TimeEnd )
		{
			//��ӿ�ʼʱ��
			SYSTEMTIME st = {};
			Dlg.m_TimeBegin.GetAsSystemTime(st);
			FILETIME ft = {},ftUTC = {};
			::SystemTimeToFileTime(&st,&ft);
			::LocalFileTimeToFileTime(&ft,&ftUTC);
			CopyMemory( &m_puiMatchDate[dwMatchIndex*2],&ftUTC,sizeof(ftUTC) );

			//��ӽ���ʱ��
			Dlg.m_TimeEnd.GetAsSystemTime(st);
			::SystemTimeToFileTime(&st,&ft);
			::LocalFileTimeToFileTime(&ft,&ftUTC);
			CopyMemory( &m_puiMatchDate[dwMatchIndex*2+1],&ftUTC,sizeof(ftUTC) );

			UpdateMatchList();
		}
	}

	return;
}

//ɾ��ʱ��
VOID CMatchParameterDlg::OnBnClickedDelete()
{
	POSITION pos = m_ListMatch.GetFirstSelectedItemPosition();
	if( pos == NULL )
	{
		AfxMessageBox( TEXT("��ѡ��Ҫɾ���ĳ���"),MB_ICONINFORMATION );
		return;
	}

	//����ѡ����
	while( pos )
	{
		int nItem = m_ListMatch.GetNextSelectedItem(pos);
		DWORD_PTR dwMatchIndex = m_ListMatch.GetItemData(nItem);

		m_puiMatchDate[dwMatchIndex*2].QuadPart = 0L;
		m_puiMatchDate[dwMatchIndex*2+1].QuadPart = 0L;
	}

	//ɾ��
	BYTE cbMatchTime = m_cbMatchTime;
	m_cbMatchTime = 0;
	for( BYTE i = 0; i < cbMatchTime; i++ )
	{
		if( m_puiMatchDate[i*2].QuadPart != 0L )
		{
			m_puiMatchDate[m_cbMatchTime*2].QuadPart = m_puiMatchDate[i*2].QuadPart;
			m_puiMatchDate[m_cbMatchTime*2+1].QuadPart = m_puiMatchDate[i*2+1].QuadPart;
			m_cbMatchTime++;
		}
	}

	//�����б�
	UpdateMatchList();

	return;
}


//���ʱ��
VOID CMatchParameterDlg::OnBnClickedAddInfo()
{
	if( m_cbMatchTime == MAX_MATCH_COUNT )
	{
		AfxMessageBox( TEXT("�������δﵽ��������ˣ����������"),MB_ICONINFORMATION );
		return;
	}

	CDlgAddMatchInfo AddMatchInfo;
	if(AddMatchInfo.DoModal()==IDOK)
	{
		int nItem = m_ListMatchInfo.GetItemCount();
		CString strDesc;
		m_ListMatchInfo.InsertItem(nItem, AddMatchInfo.m_strInfoTitle);
		strDesc.Format(TEXT("%d"),AddMatchInfo.m_nInfoTitleLen);
		m_ListMatchInfo.SetItem(nItem,1,LVIF_TEXT,strDesc,0,0,0,0,0);
		m_ListMatchInfo.SetItem(nItem,2,LVIF_TEXT,AddMatchInfo.m_strInfoDesc,0,0,0,0,0);
		strDesc.Format(TEXT("%d"),AddMatchInfo.m_nInfoDescLen);
		m_ListMatchInfo.SetItem(nItem,3,LVIF_TEXT,strDesc,0,0,0,0,0);

		CMD_GR_Match_Info *pMatchInfo=new CMD_GR_Match_Info;
		ZeroMemory(pMatchInfo,sizeof(CMD_GR_Match_Info));
		lstrcpyn(pMatchInfo->szTitle,AddMatchInfo.m_strInfoTitle,CountArray(pMatchInfo->szTitle));
		lstrcpyn(pMatchInfo->szDescribe,AddMatchInfo.m_strInfoDesc,CountArray(pMatchInfo->szDescribe));
		pMatchInfo->wDescribeLen=(WORD)AddMatchInfo.m_nInfoDescLen;
        pMatchInfo->wTitleLen=(WORD)AddMatchInfo.m_nInfoTitleLen;

		m_MatchInfo.Add(pMatchInfo);
	}
	return;
}

//�޸�ʱ��
VOID CMatchParameterDlg::OnBnClickedModifyInfo()
{
	POSITION pos = m_ListMatchInfo.GetFirstSelectedItemPosition();
	if( pos == NULL )
	{
		AfxMessageBox( TEXT("��ѡ��Ҫ�޸ĵ���Ϣ"),MB_ICONINFORMATION );
		return;
	}

	//��ȡѡ����
	int nItem = m_ListMatchInfo.GetNextSelectedItem(pos);

	//��ȡ����
	DWORD_PTR dwMatchIndex = m_ListMatchInfo.GetItemData(nItem);

	//����Ի���
	CDlgAddMatchInfo Dlg;
	CMD_GR_Match_Info *pMatchInfo=m_MatchInfo.GetAt(nItem);
	Dlg.m_strInfoTitle=pMatchInfo->szTitle;
	Dlg.m_strInfoDesc=pMatchInfo->szDescribe;
	Dlg.m_nInfoDescLen=(int)pMatchInfo->wDescribeLen;
	Dlg.m_nInfoTitleLen=(int)pMatchInfo->wTitleLen;

 	//��ʾ�Ի���
 	if( IDOK == Dlg.DoModal() )
 	{
		lstrcpyn(pMatchInfo->szDescribe,(LPCTSTR)Dlg.m_strInfoDesc.GetBuffer(),	CountArray(pMatchInfo->szDescribe));
		lstrcpyn(pMatchInfo->szTitle,	(LPCTSTR)Dlg.m_strInfoTitle.GetBuffer(),	CountArray(pMatchInfo->szTitle));
		pMatchInfo->wDescribeLen=(WORD)Dlg.m_nInfoDescLen;
		pMatchInfo->wTitleLen=(WORD)Dlg.m_nInfoTitleLen;

		UpdateMatchInfoList();
 	}

	return;
}

//ɾ��ʱ��
VOID CMatchParameterDlg::OnBnClickedDeleteInfo()
{
	POSITION pos = m_ListMatchInfo.GetFirstSelectedItemPosition();
	if( pos == NULL )
	{
		AfxMessageBox( TEXT("��ѡ��Ҫɾ���ĳ���"),MB_ICONINFORMATION );
		return;
	}

	//����ѡ����
	while( pos )
	{
		int nItem = m_ListMatchInfo.GetNextSelectedItem(pos);
		DWORD_PTR dwMatchIndex = m_ListMatchInfo.GetItemData(nItem);

		m_MatchInfo.RemoveAt(nItem);
	}

	//�����б�
	UpdateMatchInfoList();

	return;
}

//���¿ؼ�
VOID CMatchParameterDlg::UpdateMatchList()
{
	//����б�
	m_ListMatch.DeleteAllItems();

	for( BYTE i = 0; i < m_cbMatchTime; i++ )
	{
		FILETIME ftBegin = {}, ftLocalBegin = {};
		FILETIME ftEnd = {}, ftLocalEnd = {};
		CopyMemory( &ftBegin,&m_puiMatchDate[i*2],sizeof(ftBegin) );
		CopyMemory( &ftEnd,&m_puiMatchDate[i*2+1],sizeof(ftEnd) );
		FileTimeToLocalFileTime(&ftBegin,&ftLocalBegin);
		FileTimeToLocalFileTime(&ftEnd,&ftLocalEnd);

		SYSTEMTIME stBegin = {}, stEnd = {};
		FileTimeToSystemTime(&ftLocalBegin,&stBegin);
		FileTimeToSystemTime(&ftLocalEnd,&stEnd);

		//��ӵ��б�
		int nItem = m_ListMatch.GetItemCount();
		CString str;
		str.Format( TEXT("��%ld��"),nItem+1 );
		m_ListMatch.InsertItem( nItem,str );

		//��ʼʱ��
		m_ListMatch.SetItem( nItem,1,LVIF_TEXT,GetTimeString(stBegin),0,0,0,0,0 );
		//����ʱ��
		m_ListMatch.SetItem( nItem,2,LVIF_TEXT,GetTimeString(stEnd),0,0,0,0,0 );

		m_ListMatch.SetItemData(nItem,i);
	}
}

//���¿ؼ�
VOID CMatchParameterDlg::UpdateMatchInfoList()
{
	//����б�
	m_ListMatchInfo.DeleteAllItems();

	for(INT_PTR i = 0; i<m_MatchInfo.GetCount(); i++ )
	{
		//��ӵ��б�
		CMD_GR_Match_Info *pMatchInfo=m_MatchInfo.GetAt(i);
		int nItem = m_ListMatchInfo.GetItemCount();
		CString strDesc;
		m_ListMatchInfo.InsertItem(nItem, pMatchInfo->szTitle);
		strDesc.Format(TEXT("%d"),pMatchInfo->wTitleLen);
		m_ListMatchInfo.SetItem(nItem,1,LVIF_TEXT,strDesc,0,0,0,0,0);
		m_ListMatchInfo.SetItem(nItem,2,LVIF_TEXT,pMatchInfo->szDescribe,0,0,0,0,0);
		strDesc.Format(TEXT("%d"),pMatchInfo->wDescribeLen);
		m_ListMatchInfo.SetItem(nItem,3,LVIF_TEXT,strDesc,0,0,0,0,0);
	}
}
//��ȡʱ���ַ���
LPCTSTR CMatchParameterDlg::GetTimeString( SYSTEMTIME &st )
{
	//��������
	static TCHAR szTime[32] = TEXT("");

	_sntprintf(szTime,CountArray(szTime),TEXT("%4d��%02d��%02d�� %02dʱ%02d��%02d��"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	return szTime;
}

//���ݽ���
void CMatchParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control( pDX,IDC_LIST_MATCH,m_ListMatch );
	DDX_Control( pDX,IDC_LIST_MATCH_INFO,m_ListMatchInfo);
	
}

//��ʼ������
BOOL CMatchParameterDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//��ʼ���б�
	m_ListMatch.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListMatch.InsertColumn( 0,TEXT("����"),LVCFMT_LEFT,62 );
	m_ListMatch.InsertColumn( 1,TEXT("��ʼʱ��"),LVCFMT_LEFT,200 );
	m_ListMatch.InsertColumn( 2,TEXT("����ʱ��"),LVCFMT_LEFT,200 );

	m_ListMatchInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListMatchInfo.InsertColumn( 0,TEXT("��Ϣ����"),LVCFMT_LEFT,60 );
	m_ListMatchInfo.InsertColumn( 1,TEXT("���ⳤ��"),LVCFMT_LEFT,60 );
	m_ListMatchInfo.InsertColumn( 2,TEXT("��Ϣ����"),LVCFMT_LEFT,200 );
	m_ListMatchInfo.InsertColumn( 3,TEXT("���ݳ���"),LVCFMT_LEFT,60 );

	//��������
	UpdateMatchInfoList();
	UpdateMatchList();

	//��������
	CString strTemp;
	GetDlgItem(IDC_EDIT_MATCH_NAME)->SetWindowText(m_pszMatchRoom);
	strTemp.Format(TEXT("%d"),m_dwMatchFee);
	GetDlgItem(IDC_EDIT_FEE)->SetWindowText(strTemp);
	strTemp.Format(TEXT("%d"),m_lInitScore);
	GetDlgItem(IDC_EDIT_INIT_SCORE)->SetWindowText(strTemp);
	strTemp.Format(TEXT("%d"),m_wMatchGameCount);
	GetDlgItem(IDC_EDIT_MATCH_GAME_COUNT)->SetWindowText(strTemp);

	return FALSE;
}

void CMatchParameterDlg::OnOK()
{
	//��ȡĿ¼
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);

	//��ȡ����
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_sntprintf(szFileName,sizeof(szFileName),TEXT("%s\\MatchOption.ini"),szPath);

	//��������
	CString strTemp,strAppName,strValue;

	//д������
	strAppName.Format(TEXT("%dTimeRankings"),m_wMatchID);
	strTemp.Format(TEXT("%d"),m_MatchInfo.GetCount());
	WritePrivateProfileString(strAppName,TEXT("InfoItemCount"),strTemp,szFileName);

	//д�볡��
	strTemp.Format(TEXT("%d"),m_cbMatchTime);
	WritePrivateProfileString(strAppName,TEXT("MatchCount"),strTemp,szFileName);

	//д�����
	GetDlgItem(IDC_EDIT_FEE)->GetWindowText(strTemp);
	CT2CA strNum(strTemp);
	m_dwMatchFee=atoi(strNum);
	WritePrivateProfileString(strAppName,TEXT("MatchFee"),strTemp,szFileName);

	//д������
	GetDlgItem(IDC_EDIT_MATCH_NAME)->GetWindowText(strTemp);
	lstrcpyn(m_pszMatchRoom, strTemp, 32);
	WritePrivateProfileString(strAppName,TEXT("MatchRoom"), m_pszMatchRoom,szFileName);

	//��ʼ����
	GetDlgItem(IDC_EDIT_INIT_SCORE)->GetWindowText(strTemp);
	CT2CA strScore(strTemp);
	m_lInitScore=atoi(strScore);
	WritePrivateProfileString(strAppName,TEXT("InitScore"), strTemp,szFileName);

	//��������
	GetDlgItem(IDC_EDIT_MATCH_GAME_COUNT)->GetWindowText(strTemp);
	CT2CA strGameCount(strTemp);
	m_wMatchGameCount=atoi(strGameCount);
	WritePrivateProfileString(strAppName,TEXT("MatchGameCount"), strTemp,szFileName);

	//д����Ϣ
	for(INT_PTR i=0; i<m_MatchInfo.GetCount(); i++)
	{
		CMD_GR_Match_Info *pMatchInfo=m_MatchInfo.GetAt(i);
		strAppName.Format(TEXT("%dItem%d"),m_wMatchID,i);
		WritePrivateProfileString(strAppName,TEXT("InfoTitle"),pMatchInfo->szTitle,szFileName);
		WritePrivateProfileString(strAppName,TEXT("InfoDescribe"),pMatchInfo->szDescribe,szFileName);
		strValue.Format(TEXT("%d"),pMatchInfo->wTitleLen);
		WritePrivateProfileString(strAppName,TEXT("InfoTitleLen"),strValue,szFileName);
		strValue.Format(TEXT("%d"),pMatchInfo->wDescribeLen);
		WritePrivateProfileString(strAppName,TEXT("InfoDescribeLen"),strValue,szFileName);
	}

	//д��ʱ��
 	for(BYTE i=0; i<m_cbMatchTime; i++)
 	{
 		//��ȡʱ��
		FILETIME ftBegin = {};
		CopyMemory( &ftBegin,&m_puiMatchDate[i*2],sizeof(ftBegin) );
		FILETIME ftEnd = {};
		CopyMemory( &ftEnd,&m_puiMatchDate[i*2+1],sizeof(ftEnd) );

		CTime TimeBegin(ftBegin);
		CTime TimeEnd(ftEnd);

 		strAppName.Format(TEXT("%dMatchDate%d"),m_wMatchID,i);
 		WritePrivateProfileString(strAppName,TEXT("TimeStart"),TimeBegin.Format("%Y%m%d%H%M%S"),szFileName); 	
 		WritePrivateProfileString(strAppName,TEXT("TimeEnd"),TimeEnd.Format("%Y%m%d%H%M%S"),szFileName);		
 	}

	

	CDialog::OnOK();
}
//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgAddMatchDate::CDlgAddMatchDate(): CDialog(IDD_DATETIME_MATCH)
{
	m_TimeBegin = CTime::GetCurrentTime();
	m_TimeEnd = CTime::GetCurrentTime();
}

//��������
CDlgAddMatchDate::~CDlgAddMatchDate()
{
}

//���ݽ���
void CDlgAddMatchDate::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control( pDX,IDC_DATE_BEGIN,m_CtrlDateBegin );
	DDX_Control( pDX,IDC_TIME_BEGIN,m_CtrlTimeBegin );
	DDX_Control( pDX,IDC_DATE_END,m_CtrlDateEnd );
	DDX_Control( pDX,IDC_TIME_END,m_CtrlTimeEnd );
}

//��ʼ��
BOOL CDlgAddMatchDate::OnInitDialog()
{
	__super::OnInitDialog();

	//���¿ؼ�
	m_CtrlDateBegin.SetTime( &m_TimeBegin );
	m_CtrlTimeBegin.SetTime( &m_TimeBegin );
	m_CtrlDateEnd.SetTime( &m_TimeEnd );
	m_CtrlTimeEnd.SetTime( &m_TimeEnd );

	return TRUE;  
}

//ȷ������
VOID CDlgAddMatchDate::OnOK()
{
	UpdateData();

	//��ȡ��ʼʱ��
	CTime DateBegin;
	m_CtrlDateBegin.GetTime( DateBegin );
	CTime TimeBegin;
	m_CtrlTimeBegin.GetTime( TimeBegin );
	CTime Time1( DateBegin.GetYear(),DateBegin.GetMonth(),DateBegin.GetDay(),TimeBegin.GetHour(),TimeBegin.GetMinute(),TimeBegin.GetSecond() );
	m_TimeBegin = Time1;

	//��ȡ����ʱ��
	CTime DateEnd;
	m_CtrlDateEnd.GetTime( DateEnd );
	CTime TimeEnd;
	m_CtrlTimeEnd.GetTime( TimeEnd );
	CTime Time2( DateEnd.GetYear(),DateEnd.GetMonth(),DateEnd.GetDay(),TimeEnd.GetHour(),TimeEnd.GetMinute(),TimeEnd.GetSecond() );
	m_TimeEnd = Time2;

	//Ч��
	if( m_TimeBegin >= m_TimeEnd )
	{
		AfxMessageBox( TEXT("����ʱ�������ڿ�ʼʱ��,����������"),MB_ICONERROR );
		return;
	}

	__super::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgAddMatchInfo::CDlgAddMatchInfo(): CDialog(IDD)
, m_strInfoTitle(_T(""))
, m_strInfoDesc(_T(""))
, m_nInfoTitleLen(0)
, m_nInfoDescLen(0)
{

}

//��������
CDlgAddMatchInfo::~CDlgAddMatchInfo()
{
}

//���ݽ���
void CDlgAddMatchInfo::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}

//��ʼ��
BOOL CDlgAddMatchInfo::OnInitDialog()
{
	__super::OnInitDialog();
	GetDlgItem(IDC_EDIT_DESC)->SetWindowText(m_strInfoDesc);
	GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(m_strInfoTitle);
	CString strTemp;
	strTemp.Format(TEXT("%d"),m_nInfoDescLen);
	GetDlgItem(IDC_EDIT_DESC_LEN)->SetWindowText(strTemp);
	strTemp.Format(TEXT("%d"),m_nInfoTitleLen);
	GetDlgItem(IDC_EDIT_TITLE_LEN)->SetWindowText(strTemp);

	return TRUE;  
}

//ȷ������
VOID CDlgAddMatchInfo::OnOK()
{
	GetDlgItem(IDC_EDIT_DESC)->GetWindowText(m_strInfoDesc);
	GetDlgItem(IDC_EDIT_TITLE)->GetWindowText(m_strInfoTitle);
	CString strTemp;
	GetDlgItem(IDC_EDIT_DESC_LEN)->GetWindowText(strTemp);
	CT2CA strNum(strTemp);
	m_nInfoDescLen=atoi(strNum);
	GetDlgItem(IDC_EDIT_TITLE_LEN)->GetWindowText(strTemp);
	CT2CA strNum1(strTemp);
	m_nInfoTitleLen=atoi(strNum1);

	__super::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////

