#include "StdAfx.h"
#include "ServiceUnits.h"
#include "DataBaseEngineSink.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDataBaseEngineSink::CDataBaseEngineSink()
{
	//���ñ���
	m_pGameParameter=NULL;
	m_pInitParameter=NULL;
	m_pDataBaseParameter=NULL;
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;

	//�������
	m_pIDataBaseEngine=NULL;
	m_pIGameServiceManager=NULL;
	m_pIDataBaseEngineEvent=NULL;
	m_pIGameDataBaseEngineSink=NULL;
	m_pIDBCorrespondManager=NULL;

	//��������
	ZeroMemory(&m_LogonFailure,sizeof(m_LogonFailure));
	ZeroMemory(&m_LogonSuccess,sizeof(m_LogonSuccess));

	return;
}

//��������
CDataBaseEngineSink::~CDataBaseEngineSink()
{
	//�ͷŶ���
	SafeRelease(m_pIGameDataBaseEngineSink);

	return;
}

//�ӿڲ�ѯ
VOID * CDataBaseEngineSink::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IDataBaseEngineSink,Guid,dwQueryVer);
	QUERYINTERFACE(IGameDataBaseEngine,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IDataBaseEngineSink,Guid,dwQueryVer);
	return NULL;
}

//��ȡ����
VOID * CDataBaseEngineSink::GetDataBase(REFGUID Guid, DWORD dwQueryVer)
{
	//Ч��״̬
	ASSERT(m_GameDBModule.GetInterface()!=NULL);
	if (m_GameDBModule.GetInterface()==NULL) return NULL;

	//��ѯ����
	IDataBase * pIDataBase=m_GameDBModule.GetInterface();
	VOID * pIQueryObject=pIDataBase->QueryInterface(Guid,dwQueryVer);

	return pIQueryObject;
}

//��ȡ����
VOID * CDataBaseEngineSink::GetDataBaseEngine(REFGUID Guid, DWORD dwQueryVer)
{
	//Ч��״̬
	ASSERT(m_pIDataBaseEngine!=NULL);
	if (m_pIDataBaseEngine==NULL) return NULL;

	//��ѯ����
	VOID * pIQueryObject=m_pIDataBaseEngine->QueryInterface(Guid,dwQueryVer);

	return pIQueryObject;
}

//Ͷ�ݽ��
bool CDataBaseEngineSink::PostGameDataBaseResult(WORD wRequestID, VOID * pData, WORD wDataSize)
{
	return true;
}

//�����¼�
bool CDataBaseEngineSink::OnDataBaseEngineStart(IUnknownEx * pIUnknownEx)
{
	//��ѯ����
	ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IDataBaseEngine)!=NULL);
	m_pIDataBaseEngine=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IDataBaseEngine);

	//��������
	if ((m_GameDBModule.GetInterface()==NULL)&&(m_GameDBModule.CreateInstance()==false))
	{
		ASSERT(FALSE);
		return false;
	}

	//��������
	if ((m_TreasureDBModule.GetInterface()==NULL)&&(m_TreasureDBModule.CreateInstance()==false))
	{
		ASSERT(FALSE);
		return false;
	}

	//������Ϸ
	try
	{
		//������Ϣ
		tagDataBaseParameter * pTreasureDBParameter=&m_pInitParameter->m_TreasureDBParameter;

		//��������
		m_GameDBModule->SetConnectionInfo(m_pDataBaseParameter->szDataBaseAddr,m_pDataBaseParameter->wDataBasePort,
			m_pDataBaseParameter->szDataBaseName,m_pDataBaseParameter->szDataBaseUser,m_pDataBaseParameter->szDataBasePass);

		//��������
		m_TreasureDBModule->SetConnectionInfo(pTreasureDBParameter->szDataBaseAddr,pTreasureDBParameter->wDataBasePort,
			pTreasureDBParameter->szDataBaseName,pTreasureDBParameter->szDataBaseUser,pTreasureDBParameter->szDataBasePass);

		//��������
		m_GameDBModule->OpenConnection();
		m_GameDBAide.SetDataBase(m_GameDBModule.GetInterface());

		//��������
		m_TreasureDBModule->OpenConnection();
		m_TreasureDBAide.SetDataBase(m_TreasureDBModule.GetInterface());

		//���ݹ���
		ASSERT(m_pIGameServiceManager!=NULL);
		m_pIGameDataBaseEngineSink=(IGameDataBaseEngineSink *)m_pIGameServiceManager->CreateGameDataBaseEngineSink(IID_IGameDataBaseEngineSink,VER_IGameDataBaseEngineSink);

		//���ö���
		if ((m_pIGameDataBaseEngineSink!=NULL)&&(m_pIGameDataBaseEngineSink->InitializeSink(QUERY_ME_INTERFACE(IUnknownEx))==false))
		{
			//�������
			ASSERT(FALSE);

			//�����Ϣ
			CTraceService::TraceString(TEXT("��Ϸ���ݿ���չ���������������ʧ��"),TraceLevel_Exception);

			return false;
		}

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		return false;
	}

	return true;
}

//ֹͣ�¼�
bool CDataBaseEngineSink::OnDataBaseEngineConclude(IUnknownEx * pIUnknownEx)
{
	//���ñ���
	m_pInitParameter=NULL;
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;

	//�������
	m_pIGameServiceManager=NULL;
	m_pIDataBaseEngineEvent=NULL;

	//���ö���
	m_GameDBAide.SetDataBase(NULL);

	//�ͷŶ���
	SafeRelease(m_pIGameDataBaseEngineSink);

	//�ر�����
	if (m_GameDBModule.GetInterface()!=NULL)
	{
		m_GameDBModule->CloseConnection();
		m_GameDBModule.CloseInstance();
	}

	//�ر�����
	if (m_TreasureDBModule.GetInterface()!=NULL)
	{
		m_TreasureDBModule->CloseConnection();
		m_TreasureDBModule.CloseInstance();
	}

	return true;
}

//ʱ���¼�
bool CDataBaseEngineSink::OnDataBaseEngineTimer(DWORD dwTimerID, WPARAM dwBindParameter)
{
	return false;
}

//�����¼�
bool CDataBaseEngineSink::OnDataBaseEngineControl(WORD wControlID, VOID * pData, WORD wDataSize)
{
	return false;
}

//�����¼�
bool CDataBaseEngineSink::OnDataBaseEngineRequest(WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//��������
	bool bSucceed = false;
	DWORD dwUserID = 0L;

	//������
	switch (wRequestID)
	{
	case DBR_GR_LOGON_USERID:			//I D ��¼
		{
			bSucceed = OnRequestLogonUserID(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOGON_MOBILE:			//�ֻ���¼
		{
			bSucceed = OnRequestLogonMobile(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOGON_ACCOUNTS:			//�ʺŵ�¼
		{
			bSucceed = OnRequestLogonAccounts(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_WRITE_GAME_SCORE:		//��Ϸд��
		{
			bSucceed = OnRequestWriteGameScore(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LEAVE_GAME_SERVER:		//�뿪����
		{
			bSucceed = OnRequestLeaveGameServer(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_GAME_SCORE_RECORD:		//��Ϸ��¼
		{
			bSucceed = OnRequestGameScoreRecord(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOAD_PARAMETER:			//���ز���
		{
			bSucceed = OnRequestLoadParameter(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOAD_GAME_COLUMN:		//�����б�
		{
			bSucceed = OnRequestLoadGameColumn(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOAD_ANDROID_USER:		//���ػ���
		{
			bSucceed = OnRequestLoadAndroidUser(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOAD_GAME_PROPERTY:		//���ص���
		{
			bSucceed = OnRequestLoadGameProperty(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_USER_SAVE_SCORE:		//������Ϸ��
		{
			bSucceed = OnRequestUserSaveScore(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_USER_TAKE_SCORE:		//��ȡ��Ϸ��
		{
			bSucceed = OnRequestUserTakeScore(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_USER_TRANSFER_SCORE:	//ת����Ϸ��
		{
			bSucceed = OnRequestUserTransferScore(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_QUERY_INSURE_INFO:		//��ѯ����
		{
			bSucceed = OnRequestQueryInsureInfo(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_QUERY_TRANSFER_USER_INFO:		//��ѯ�û�
		{
			bSucceed = OnRequestQueryTransferUserInfo(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_PROPERTY_REQUEST:		//��������
		{
			bSucceed = OnRequestPropertyRequest(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MANAGE_USER_RIGHT:		//�û�Ȩ��
		{
			bSucceed = OnRequestManageUserRight(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_LOAD_SYSTEM_MESSAGE:   //ϵͳ��Ϣ
		{
			bSucceed = OnRequestLoadSystemMessage(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MATCH_FEE:				//��������
		{
			bSucceed = OnRequestMatchFee(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MATCH_START:			//������ʼ
		{
			bSucceed = OnRequestMatchStart(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MATCH_OVER:				//��������
		{
			bSucceed = OnRequestMatchOver(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MATCH_REWARD:			//��������
		{
			bSucceed = OnRequestMatchReward(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	case DBR_GR_MATCH_QUIT:				//�˳�����
		{
			bSucceed = OnRequestMatchQuit(dwContextID,pData,wDataSize,dwUserID);
		}
		break;
	}

	//Э��֪ͨ
	if(m_pIDBCorrespondManager) m_pIDBCorrespondManager->OnPostRequestComplete(dwUserID, bSucceed);

	return bSucceed;
}

//I D ��¼
bool CDataBaseEngineSink::OnRequestLogonUserID(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//ִ�в�ѯ
	DBR_GR_LogonUserID * pLogonUserID=(DBR_GR_LogonUserID *)pData;
	dwUserID = pLogonUserID->dwUserID;

	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_LogonUserID));
	if (wDataSize!=sizeof(DBR_GR_LogonUserID)) return false;

	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pLogonUserID->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pLogonUserID->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@strPassword"),pLogonUserID->szPassword);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pLogonUserID->szMachineID);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),m_LogonFailure.szDescribeString,sizeof(m_LogonFailure.szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_EfficacyUserID"),true);

		//�û���Ϣ
		lstrcpyn(m_LogonSuccess.szPassword,pLogonUserID->szPassword,CountArray(m_LogonSuccess.szPassword));
		lstrcpyn(m_LogonSuccess.szMachineID,pLogonUserID->szMachineID,CountArray(m_LogonSuccess.szMachineID));
	
		//�������
		CDBVarValue DBVarValue;
		m_GameDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnLogonDisposeResult(dwContextID,lResultCode,CW2CT(DBVarValue.bstrVal),false);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnLogonDisposeResult(dwContextID,DB_ERROR,TEXT("�������ݿ�����쳣�������Ժ����Ի�ѡ����һ��������¼��"),false);

		return false;
	}

	return true;
}

//I D ��¼
bool CDataBaseEngineSink::OnRequestLogonMobile(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//ִ�в�ѯ
	DBR_GR_LogonMobile * pLogonMobile=(DBR_GR_LogonMobile *)pData;
	dwUserID = pLogonMobile->dwUserID;

	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_LogonMobile));
		if (wDataSize!=sizeof(DBR_GR_LogonMobile)) return false;

		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pLogonMobile->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pLogonMobile->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@strPassword"),pLogonMobile->szPassword);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pLogonMobile->szMachineID);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),m_LogonFailure.szDescribeString,sizeof(m_LogonFailure.szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_EfficacyMobile"),true);

		//�û���Ϣ
		lstrcpyn(m_LogonSuccess.szPassword,pLogonMobile->szPassword,CountArray(m_LogonSuccess.szPassword));
		lstrcpyn(m_LogonSuccess.szMachineID,pLogonMobile->szMachineID,CountArray(m_LogonSuccess.szMachineID));
		m_LogonSuccess.cbDeviceType=pLogonMobile->cbDeviceType;
		m_LogonSuccess.wBehaviorFlags=pLogonMobile->wBehaviorFlags;
		m_LogonSuccess.wPageTableCount=pLogonMobile->wPageTableCount;
	
		//�������
		CDBVarValue DBVarValue;
		m_GameDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnLogonDisposeResult(dwContextID,lResultCode,CW2CT(DBVarValue.bstrVal),true,pLogonMobile->cbDeviceType,pLogonMobile->wBehaviorFlags,pLogonMobile->wPageTableCount);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnLogonDisposeResult(dwContextID,DB_ERROR,TEXT("�������ݿ�����쳣�������Ժ����Ի�ѡ����һ��������¼��"),true);

		return false;
	}

	return true;
}

//�ʺŵ�¼
bool CDataBaseEngineSink::OnRequestLogonAccounts(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_LogonAccounts));
		if (wDataSize!=sizeof(DBR_GR_LogonAccounts)) return false;

		//������
		DBR_GR_LogonAccounts * pLogonAccounts=(DBR_GR_LogonAccounts *)pData;

		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pLogonAccounts->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@strAccounts"),pLogonAccounts->szAccounts);
		m_GameDBAide.AddParameter(TEXT("@strPassword"),pLogonAccounts->szPassword);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pLogonAccounts->szMachineID);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),m_LogonFailure.szDescribeString,sizeof(m_LogonFailure.szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_EfficacyAccounts"),true);

		//�û���Ϣ
		lstrcpyn(m_LogonSuccess.szPassword,pLogonAccounts->szPassword,CountArray(m_LogonSuccess.szPassword));
		lstrcpyn(m_LogonSuccess.szMachineID,pLogonAccounts->szMachineID,CountArray(m_LogonSuccess.szMachineID));

		//�������
		CDBVarValue DBVarValue;
		m_GameDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnLogonDisposeResult(dwContextID,lResultCode,CW2CT(DBVarValue.bstrVal),false);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnLogonDisposeResult(dwContextID,DB_ERROR,TEXT("�������ݿ�����쳣�������Ժ����Ի�ѡ����һ��������¼��"),false);

		return false;
	}

	return true;
}

//��Ϸд��
bool CDataBaseEngineSink::OnRequestWriteGameScore(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//������
	DBR_GR_WriteGameScore * pWriteGameScore=(DBR_GR_WriteGameScore *)pData;
	dwUserID=pWriteGameScore->dwUserID;

	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_WriteGameScore));
		if (wDataSize!=sizeof(DBR_GR_WriteGameScore)) return false;

		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pWriteGameScore->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();

		//�û���Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pWriteGameScore->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwDBQuestID"),pWriteGameScore->dwDBQuestID);
		m_GameDBAide.AddParameter(TEXT("@dwInoutIndex"),pWriteGameScore->dwInoutIndex);

		//����ɼ�
		m_GameDBAide.AddParameter(TEXT("@lScore"),pWriteGameScore->VariationInfo.lScore);
		m_GameDBAide.AddParameter(TEXT("@lGrade"),pWriteGameScore->VariationInfo.lGrade);
		m_GameDBAide.AddParameter(TEXT("@lInsure"),pWriteGameScore->VariationInfo.lInsure);
		m_GameDBAide.AddParameter(TEXT("@lRevenue"),pWriteGameScore->VariationInfo.lRevenue);
		m_GameDBAide.AddParameter(TEXT("@lWinCount"),pWriteGameScore->VariationInfo.dwWinCount);
		m_GameDBAide.AddParameter(TEXT("@lLostCount"),pWriteGameScore->VariationInfo.dwLostCount);
		m_GameDBAide.AddParameter(TEXT("@lDrawCount"),pWriteGameScore->VariationInfo.dwDrawCount);
		m_GameDBAide.AddParameter(TEXT("@lFleeCount"),pWriteGameScore->VariationInfo.dwFleeCount);
		m_GameDBAide.AddParameter(TEXT("@lUserMedal"),pWriteGameScore->VariationInfo.dwUserMedal);
		m_GameDBAide.AddParameter(TEXT("@lExperience"),pWriteGameScore->VariationInfo.dwExperience);
		m_GameDBAide.AddParameter(TEXT("@lLoveLiness"),pWriteGameScore->VariationInfo.lLoveLiness);
		m_GameDBAide.AddParameter(TEXT("@dwPlayTimeCount"),pWriteGameScore->VariationInfo.dwPlayTimeCount);

		//������Ϣ
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_WriteGameScore"),false);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		return false;
	}

	return true;
}

//�뿪����
bool CDataBaseEngineSink::OnRequestLeaveGameServer(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//������
	DBR_GR_LeaveGameServer * pLeaveGameServer=(DBR_GR_LeaveGameServer *)pData;
	dwUserID=pLeaveGameServer->dwUserID;

	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_LeaveGameServer));
		if (wDataSize!=sizeof(DBR_GR_LeaveGameServer)) return false;

		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pLeaveGameServer->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();

		//�û���Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pLeaveGameServer->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwOnLineTimeCount"),pLeaveGameServer->dwOnLineTimeCount);

		//ϵͳ��Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwInoutIndex"),pLeaveGameServer->dwInoutIndex);
		m_GameDBAide.AddParameter(TEXT("@dwLeaveReason"),pLeaveGameServer->dwLeaveReason);

		//��¼�ɼ�
		m_GameDBAide.AddParameter(TEXT("@lRecordScore"),pLeaveGameServer->RecordInfo.lScore);
		m_GameDBAide.AddParameter(TEXT("@lRecordGrade"),pLeaveGameServer->RecordInfo.lGrade);
		m_GameDBAide.AddParameter(TEXT("@lRecordInsure"),pLeaveGameServer->RecordInfo.lInsure);
		m_GameDBAide.AddParameter(TEXT("@lRecordRevenue"),pLeaveGameServer->RecordInfo.lRevenue);
		m_GameDBAide.AddParameter(TEXT("@lRecordWinCount"),pLeaveGameServer->RecordInfo.dwWinCount);
		m_GameDBAide.AddParameter(TEXT("@lRecordLostCount"),pLeaveGameServer->RecordInfo.dwLostCount);
		m_GameDBAide.AddParameter(TEXT("@lRecordDrawCount"),pLeaveGameServer->RecordInfo.dwDrawCount);
		m_GameDBAide.AddParameter(TEXT("@lRecordFleeCount"),pLeaveGameServer->RecordInfo.dwFleeCount);
		m_GameDBAide.AddParameter(TEXT("@lRecordUserMedal"),pLeaveGameServer->RecordInfo.dwUserMedal);
		m_GameDBAide.AddParameter(TEXT("@lRecordExperience"),pLeaveGameServer->RecordInfo.dwExperience);
		m_GameDBAide.AddParameter(TEXT("@lRecordLoveLiness"),pLeaveGameServer->RecordInfo.lLoveLiness);
		m_GameDBAide.AddParameter(TEXT("@dwRecordPlayTimeCount"),pLeaveGameServer->RecordInfo.dwPlayTimeCount);

		//����ɼ�
		m_GameDBAide.AddParameter(TEXT("@lVariationScore"),pLeaveGameServer->VariationInfo.lScore);
		m_GameDBAide.AddParameter(TEXT("@lVariationGrade"),pLeaveGameServer->VariationInfo.lGrade);
		m_GameDBAide.AddParameter(TEXT("@lVariationInsure"),pLeaveGameServer->VariationInfo.lInsure);
		m_GameDBAide.AddParameter(TEXT("@lVariationRevenue"),pLeaveGameServer->VariationInfo.lRevenue);
		m_GameDBAide.AddParameter(TEXT("@lVariationWinCount"),pLeaveGameServer->VariationInfo.dwWinCount);
		m_GameDBAide.AddParameter(TEXT("@lVariationLostCount"),pLeaveGameServer->VariationInfo.dwLostCount);
		m_GameDBAide.AddParameter(TEXT("@lVariationDrawCount"),pLeaveGameServer->VariationInfo.dwDrawCount);
		m_GameDBAide.AddParameter(TEXT("@lVariationFleeCount"),pLeaveGameServer->VariationInfo.dwFleeCount);
		m_GameDBAide.AddParameter(TEXT("@lVariationUserMedal"),pLeaveGameServer->VariationInfo.dwUserMedal);
		m_GameDBAide.AddParameter(TEXT("@lVariationExperience"),pLeaveGameServer->VariationInfo.dwExperience);
		m_GameDBAide.AddParameter(TEXT("@lVariationLoveLiness"),pLeaveGameServer->VariationInfo.lLoveLiness);
		m_GameDBAide.AddParameter(TEXT("@dwVariationPlayTimeCount"),pLeaveGameServer->VariationInfo.dwPlayTimeCount);

		//��������
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pLeaveGameServer->szMachineID);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_LeaveGameServer"),false);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		return false;
	}

	return true;
}

//��Ϸ��¼
bool CDataBaseEngineSink::OnRequestGameScoreRecord(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//��������
		DBR_GR_GameScoreRecord * pGameScoreRecord=(DBR_GR_GameScoreRecord *)pData;
		dwUserID=INVALID_DWORD;

		//Ч�����
		ASSERT(wDataSize<=sizeof(DBR_GR_GameScoreRecord));
		ASSERT(wDataSize>=(sizeof(DBR_GR_GameScoreRecord)-sizeof(pGameScoreRecord->GameScoreRecord)));
		ASSERT(wDataSize==(sizeof(DBR_GR_GameScoreRecord)-sizeof(pGameScoreRecord->GameScoreRecord)+pGameScoreRecord->wRecordCount*sizeof(pGameScoreRecord->GameScoreRecord[0])));

		//Ч�����
		if (wDataSize>sizeof(DBR_GR_GameScoreRecord)) return false;
		if (wDataSize<(sizeof(DBR_GR_GameScoreRecord)-sizeof(pGameScoreRecord->GameScoreRecord))) return false;
		if (wDataSize!=(sizeof(DBR_GR_GameScoreRecord)-sizeof(pGameScoreRecord->GameScoreRecord)+pGameScoreRecord->wRecordCount*sizeof(pGameScoreRecord->GameScoreRecord[0]))) return false;

		//������Ϣ
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//������Ϣ
		m_GameDBAide.AddParameter(TEXT("@wTableID"),pGameScoreRecord->wTableID);
		m_GameDBAide.AddParameter(TEXT("@wUserCount"),pGameScoreRecord->wUserCount);
		m_GameDBAide.AddParameter(TEXT("@wAndroidCount"),pGameScoreRecord->wAndroidCount);

		//˰�����
		m_GameDBAide.AddParameter(TEXT("@lWasteCount"),pGameScoreRecord->lWasteCount);
		m_GameDBAide.AddParameter(TEXT("@lRevenueCount"),pGameScoreRecord->lRevenueCount);

		//ͳ����Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwUserMemal"),pGameScoreRecord->dwUserMemal);
		m_GameDBAide.AddParameter(TEXT("@dwPlayTimeCount"),pGameScoreRecord->dwPlayTimeCount);

		//ʱ����Ϣ
		m_GameDBAide.AddParameter(TEXT("@SystemTimeStart"),pGameScoreRecord->SystemTimeStart);
		m_GameDBAide.AddParameter(TEXT("@SystemTimeConclude"),pGameScoreRecord->SystemTimeConclude);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_RecordDrawInfo"),true);

		//д���¼
		if (lResultCode==DB_SUCCESS)
		{
			//��ȡ��ʶ
			DWORD dwDrawID=m_GameDBAide.GetValue_DWORD(TEXT("DrawID"));

			//д���¼
			for (WORD i=0;i<pGameScoreRecord->wRecordCount;i++)
			{
				//���ò���
				m_GameDBAide.ResetParameter();
				
				//������Ϣ
				m_GameDBAide.AddParameter(TEXT("@dwDrawID"),dwDrawID);
				m_GameDBAide.AddParameter(TEXT("@dwUserID"),pGameScoreRecord->GameScoreRecord[i].dwUserID);
				m_GameDBAide.AddParameter(TEXT("@wChairID"),pGameScoreRecord->GameScoreRecord[i].wChairID);

				//�û���Ϣ
				m_GameDBAide.AddParameter(TEXT("@dwDBQuestID"),pGameScoreRecord->GameScoreRecord[i].dwDBQuestID);
				m_GameDBAide.AddParameter(TEXT("@dwInoutIndex"),pGameScoreRecord->GameScoreRecord[i].dwInoutIndex);

				//�ɼ���Ϣ
				m_GameDBAide.AddParameter(TEXT("@lScore"),pGameScoreRecord->GameScoreRecord[i].lScore);
				m_GameDBAide.AddParameter(TEXT("@lGrade"),pGameScoreRecord->GameScoreRecord[i].lGrade);
				m_GameDBAide.AddParameter(TEXT("@lRevenue"),pGameScoreRecord->GameScoreRecord[i].lRevenue);
				m_GameDBAide.AddParameter(TEXT("@dwUserMedal"),pGameScoreRecord->GameScoreRecord[i].dwUserMemal);
				m_GameDBAide.AddParameter(TEXT("@dwPlayTimeCount"),pGameScoreRecord->GameScoreRecord[i].dwPlayTimeCount);

				//ִ�в�ѯ
				m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_RecordDrawScore"),false);
			}
		}
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		return false;
	}

	return true;
}

//���ز���
bool CDataBaseEngineSink::OnRequestLoadParameter(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//��������
		DBO_GR_GameParameter GameParameter;
		ZeroMemory(&GameParameter,sizeof(GameParameter));

		//ִ�в�ѯ
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//ִ�в�ѯ
		LONG lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_LoadParameter"),true);

		//��ȡ��Ϣ
		if (lResultCode==DB_SUCCESS)
		{
			//������Ϣ
			GameParameter.wMedalRate=m_GameDBAide.GetValue_WORD(TEXT("MedalRate"));
			GameParameter.wRevenueRate=m_GameDBAide.GetValue_WORD(TEXT("RevenueRate"));

			//�汾��Ϣ
			GameParameter.dwClientVersion=m_GameDBAide.GetValue_DWORD(TEXT("ClientVersion"));
			GameParameter.dwServerVersion=m_GameDBAide.GetValue_DWORD(TEXT("ServerVersion"));
		
			//������Ϣ
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_GAME_PARAMETER,dwContextID,&GameParameter,sizeof(GameParameter));
		}

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		return false;
	}

	return true;
}

//�����б�
bool CDataBaseEngineSink::OnRequestLoadGameColumn(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//��������
		DBO_GR_GameColumnInfo GameColumnInfo;
		ZeroMemory(&GameColumnInfo,sizeof(GameColumnInfo));

		//ִ�в�ѯ
		m_GameDBAide.ResetParameter();
		GameColumnInfo.lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_GameColumnItem"),true);

		//��ȡ��Ϣ
		for (WORD i=0;i<CountArray(GameColumnInfo.ColumnItemInfo);i++)
		{
			//�����ж�
			if (m_GameDBModule->IsRecordsetEnd()==true) break;

			//���Ч��
			ASSERT(GameColumnInfo.cbColumnCount<CountArray(GameColumnInfo.ColumnItemInfo));
			if (GameColumnInfo.cbColumnCount>=CountArray(GameColumnInfo.ColumnItemInfo)) break;

			//��ȡ����
			GameColumnInfo.cbColumnCount++;
			GameColumnInfo.ColumnItemInfo[i].cbColumnWidth=m_GameDBAide.GetValue_BYTE(TEXT("ColumnWidth"));
			GameColumnInfo.ColumnItemInfo[i].cbDataDescribe=m_GameDBAide.GetValue_BYTE(TEXT("DataDescribe"));
			m_GameDBAide.GetValue_String(TEXT("ColumnName"),GameColumnInfo.ColumnItemInfo[i].szColumnName,CountArray(GameColumnInfo.ColumnItemInfo[i].szColumnName));

			//�ƶ���¼
			m_GameDBModule->MoveToNext();
		}

		//������Ϣ
		WORD wHeadSize=sizeof(GameColumnInfo)-sizeof(GameColumnInfo.ColumnItemInfo);
		WORD wPacketSize=wHeadSize+GameColumnInfo.cbColumnCount*sizeof(GameColumnInfo.ColumnItemInfo[0]);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_GAME_COLUMN_INFO,dwContextID,&GameColumnInfo,wPacketSize);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//��������
		DBO_GR_GameColumnInfo GameColumnInfo;
		ZeroMemory(&GameColumnInfo,sizeof(GameColumnInfo));

		//�������
		GameColumnInfo.cbColumnCount=0L;
		GameColumnInfo.lResultCode=pIException->GetExceptionResult();

		//������Ϣ
		WORD wPacketSize=sizeof(GameColumnInfo)-sizeof(GameColumnInfo.ColumnItemInfo);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_GAME_COLUMN_INFO,dwContextID,&GameColumnInfo,wPacketSize);

		return false;
	}

	return true;
}

//���ػ���
bool CDataBaseEngineSink::OnRequestLoadAndroidUser(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//��������
		DBO_GR_GameAndroidInfo GameAndroidInfo;
		ZeroMemory(&GameAndroidInfo,sizeof(GameAndroidInfo));

		//�û��ʻ�
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//ִ�в�ѯ
		GameAndroidInfo.lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_LoadAndroidUser"),true);

		//��ȡ��Ϣ
		for (WORD i=0;i<CountArray(GameAndroidInfo.AndroidParameter);i++)
		{
			//�����ж�
			if (m_GameDBModule->IsRecordsetEnd()==true) break;

			//���Ч��
			ASSERT(GameAndroidInfo.wAndroidCount<CountArray(GameAndroidInfo.AndroidParameter));
			if (GameAndroidInfo.wAndroidCount>=CountArray(GameAndroidInfo.AndroidParameter)) break;

			//��ȡ����
			GameAndroidInfo.wAndroidCount++;
			GameAndroidInfo.AndroidParameter[i].dwUserID=m_GameDBAide.GetValue_DWORD(TEXT("UserID"));
			GameAndroidInfo.AndroidParameter[i].dwServiceTime=m_GameDBAide.GetValue_DWORD(TEXT("ServiceTime"));
			GameAndroidInfo.AndroidParameter[i].dwMinPlayDraw=m_GameDBAide.GetValue_DWORD(TEXT("MinPlayDraw"));
			GameAndroidInfo.AndroidParameter[i].dwMaxPlayDraw=m_GameDBAide.GetValue_DWORD(TEXT("MaxPlayDraw"));
			GameAndroidInfo.AndroidParameter[i].dwMinReposeTime=m_GameDBAide.GetValue_DWORD(TEXT("MinReposeTime"));
			GameAndroidInfo.AndroidParameter[i].dwMaxReposeTime=m_GameDBAide.GetValue_DWORD(TEXT("MaxReposeTime"));
			GameAndroidInfo.AndroidParameter[i].dwServiceGender=m_GameDBAide.GetValue_DWORD(TEXT("ServiceGender"));
			GameAndroidInfo.AndroidParameter[i].lMinTakeScore=m_GameDBAide.GetValue_LONGLONG(TEXT("MinTakeScore"));
			GameAndroidInfo.AndroidParameter[i].lMaxTakeScore=m_GameDBAide.GetValue_LONGLONG(TEXT("MaxTakeScore"));

			//�ƶ���¼
			m_GameDBModule->MoveToNext();
		}

		//������Ϣ
		WORD wHeadSize=sizeof(GameAndroidInfo)-sizeof(GameAndroidInfo.AndroidParameter);
		WORD wDataSize=GameAndroidInfo.wAndroidCount*sizeof(GameAndroidInfo.AndroidParameter[0]);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_GAME_ANDROID_INFO,dwContextID,&GameAndroidInfo,wHeadSize+wDataSize);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//��������
		DBO_GR_GameAndroidInfo GameAndroidInfo;
		ZeroMemory(&GameAndroidInfo,sizeof(GameAndroidInfo));

		//�������
		GameAndroidInfo.wAndroidCount=0L;
		GameAndroidInfo.lResultCode=DB_ERROR;

		//������Ϣ
		WORD wHeadSize=sizeof(GameAndroidInfo)-sizeof(GameAndroidInfo.AndroidParameter);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_GAME_ANDROID_INFO,dwContextID,&GameAndroidInfo,wHeadSize);
	}

	return false;
}

//���ص���
bool CDataBaseEngineSink::OnRequestLoadGameProperty(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//��������
		DBO_GR_GamePropertyInfo GamePropertyInfo;
		ZeroMemory(&GamePropertyInfo,sizeof(GamePropertyInfo));

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//ִ�в�ѯ
		GamePropertyInfo.lResultCode=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_LoadGameProperty"),true);

		//��ȡ��Ϣ
		for (WORD i=0;i<CountArray(GamePropertyInfo.PropertyInfo);i++)
		{
			//�����ж�
			if (m_GameDBModule->IsRecordsetEnd()==true) break;

			//���Ч��
			ASSERT(GamePropertyInfo.cbPropertyCount<CountArray(GamePropertyInfo.PropertyInfo));
			if (GamePropertyInfo.cbPropertyCount>=CountArray(GamePropertyInfo.PropertyInfo)) break;

			//��ȡ����
			GamePropertyInfo.cbPropertyCount++;
			GamePropertyInfo.PropertyInfo[i].wIndex=m_GameDBAide.GetValue_WORD(TEXT("ID"));
			GamePropertyInfo.PropertyInfo[i].wDiscount=m_GameDBAide.GetValue_WORD(TEXT("Discount"));
			GamePropertyInfo.PropertyInfo[i].wIssueArea=m_GameDBAide.GetValue_WORD(TEXT("IssueArea"));
			GamePropertyInfo.PropertyInfo[i].dPropertyCash=m_GameDBAide.GetValue_DOUBLE(TEXT("Cash"));
			GamePropertyInfo.PropertyInfo[i].lPropertyGold=m_GameDBAide.GetValue_LONGLONG(TEXT("Gold"));
			GamePropertyInfo.PropertyInfo[i].lSendLoveLiness=m_GameDBAide.GetValue_LONGLONG(TEXT("SendLoveLiness"));
			GamePropertyInfo.PropertyInfo[i].lRecvLoveLiness=m_GameDBAide.GetValue_LONGLONG(TEXT("RecvLoveLiness"));

			//�ƶ���¼
			m_GameDBModule->MoveToNext();
		}

		//������Ϣ
		WORD wHeadSize=sizeof(GamePropertyInfo)-sizeof(GamePropertyInfo.PropertyInfo);
		WORD wDataSize=GamePropertyInfo.cbPropertyCount*sizeof(GamePropertyInfo.PropertyInfo[0]);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_GAME_PROPERTY_INFO,dwContextID,&GamePropertyInfo,wHeadSize+wDataSize);
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//��������
		DBO_GR_GamePropertyInfo GamePropertyInfo;
		ZeroMemory(&GamePropertyInfo,sizeof(GamePropertyInfo));

		//�������
		GamePropertyInfo.cbPropertyCount=0L;
		GamePropertyInfo.lResultCode=DB_ERROR;

		//������Ϣ
		WORD wHeadSize=sizeof(GamePropertyInfo)-sizeof(GamePropertyInfo.PropertyInfo);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_GAME_PROPERTY_INFO,dwContextID,&GamePropertyInfo,wHeadSize);

		return false;
	}

	return true;
}

//������Ϸ��
bool CDataBaseEngineSink::OnRequestUserSaveScore(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_UserSaveScore));
	if (wDataSize!=sizeof(DBR_GR_UserSaveScore)) return false;

	//��������
	DBR_GR_UserSaveScore * pUserSaveScore=(DBR_GR_UserSaveScore *)pData;
	dwUserID=pUserSaveScore->dwUserID;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pUserSaveScore->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_TreasureDBAide.ResetParameter();
		m_TreasureDBAide.AddParameter(TEXT("@dwUserID"),pUserSaveScore->dwUserID);
		m_TreasureDBAide.AddParameter(TEXT("@lSaveScore"),pUserSaveScore->lSaveScore);
		m_TreasureDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_TreasureDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_TreasureDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_TreasureDBAide.AddParameter(TEXT("@strMachineID"),pUserSaveScore->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_TreasureDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_TreasureDBAide.ExecuteProcess(TEXT("GSP_GR_UserSaveScore"),true);

		//�������
		CDBVarValue DBVarValue;
		m_TreasureDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnInsureDisposeResult(dwContextID,lResultCode,pUserSaveScore->lSaveScore,CW2CT(DBVarValue.bstrVal),false,pUserSaveScore->cbActivityGame);
	
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,pUserSaveScore->lSaveScore,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false,pUserSaveScore->cbActivityGame);

		return false;
	}

	return true;
}

//��ȡ��Ϸ��
bool CDataBaseEngineSink::OnRequestUserTakeScore(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_UserTakeScore));
	if (wDataSize!=sizeof(DBR_GR_UserTakeScore)) return false;

	//��������
	DBR_GR_UserTakeScore * pUserTakeScore=(DBR_GR_UserTakeScore *)pData;
	dwUserID=pUserTakeScore->dwUserID;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pUserTakeScore->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_TreasureDBAide.ResetParameter();
		m_TreasureDBAide.AddParameter(TEXT("@dwUserID"),pUserTakeScore->dwUserID);
		m_TreasureDBAide.AddParameter(TEXT("@lTakeScore"),pUserTakeScore->lTakeScore);
		m_TreasureDBAide.AddParameter(TEXT("@strPassword"),pUserTakeScore->szPassword);
		m_TreasureDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_TreasureDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_TreasureDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_TreasureDBAide.AddParameter(TEXT("@strMachineID"),pUserTakeScore->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_TreasureDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_TreasureDBAide.ExecuteProcess(TEXT("GSP_GR_UserTakeScore"),true);

		//�������
		CDBVarValue DBVarValue;
		m_TreasureDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnInsureDisposeResult(dwContextID,lResultCode,0L,CW2CT(DBVarValue.bstrVal),false,pUserTakeScore->cbActivityGame);
	
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false,pUserTakeScore->cbActivityGame);

		return false;
	}

	return true;
}

//ת����Ϸ��
bool CDataBaseEngineSink::OnRequestUserTransferScore(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_UserTransferScore));
	if (wDataSize!=sizeof(DBR_GR_UserTransferScore)) return false;

	//��������
	DBR_GR_UserTransferScore * pUserTransferScore=(DBR_GR_UserTransferScore *)pData;
	dwUserID=pUserTransferScore->dwUserID;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pUserTransferScore->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_TreasureDBAide.ResetParameter();
		m_TreasureDBAide.AddParameter(TEXT("@dwUserID"),pUserTransferScore->dwUserID);
		m_TreasureDBAide.AddParameter(TEXT("@cbByNickName"),pUserTransferScore->cbByNickName);
		m_TreasureDBAide.AddParameter(TEXT("@lTransferScore"),pUserTransferScore->lTransferScore);
		m_TreasureDBAide.AddParameter(TEXT("@strPassword"),pUserTransferScore->szPassword);
		m_TreasureDBAide.AddParameter(TEXT("@strNickName"),pUserTransferScore->szNickName);
		m_TreasureDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_TreasureDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_TreasureDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_TreasureDBAide.AddParameter(TEXT("@strMachineID"),pUserTransferScore->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_TreasureDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//ִ�в�ѯ
		LONG lResultCode=m_TreasureDBAide.ExecuteProcess(TEXT("GSP_GR_UserTransferScore"),true);

		//�������
		CDBVarValue DBVarValue;
		m_TreasureDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);
		OnInsureDisposeResult(dwContextID,lResultCode,0L,CW2CT(DBVarValue.bstrVal),false,pUserTransferScore->cbActivityGame);
	
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false,pUserTransferScore->cbActivityGame);

		return false;
	}

	return true;
}

//��ѯ����
bool CDataBaseEngineSink::OnRequestQueryInsureInfo(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_QueryInsureInfo));
	if (wDataSize!=sizeof(DBR_GR_QueryInsureInfo)) return false;

	//������
	DBR_GR_QueryInsureInfo * pQueryInsureInfo=(DBR_GR_QueryInsureInfo *)pData;
	dwUserID=pQueryInsureInfo->dwUserID;

	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pQueryInsureInfo->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_TreasureDBAide.ResetParameter();
		m_TreasureDBAide.AddParameter(TEXT("@dwUserID"),pQueryInsureInfo->dwUserID);
		m_TreasureDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_TreasureDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		if (m_TreasureDBAide.ExecuteProcess(TEXT("GSP_GR_QueryUserInsureInfo"),true)==DB_SUCCESS)
		{
			//��������
			DBO_GR_UserInsureInfo UserInsureInfo;
			ZeroMemory(&UserInsureInfo,sizeof(UserInsureInfo));

			//������Ϣ
			UserInsureInfo.cbActivityGame=pQueryInsureInfo->cbActivityGame;
			UserInsureInfo.wRevenueTake=m_TreasureDBAide.GetValue_WORD(TEXT("RevenueTake"));
			UserInsureInfo.wRevenueTransfer=m_TreasureDBAide.GetValue_WORD(TEXT("RevenueTransfer"));
			UserInsureInfo.wServerID=m_TreasureDBAide.GetValue_WORD(TEXT("ServerID"));
			UserInsureInfo.lUserScore=m_TreasureDBAide.GetValue_LONGLONG(TEXT("Score"));
			UserInsureInfo.lUserInsure=m_TreasureDBAide.GetValue_LONGLONG(TEXT("Insure"));
			UserInsureInfo.lTransferPrerequisite=m_TreasureDBAide.GetValue_LONGLONG(TEXT("TransferPrerequisite"));

			//���ͽ��
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_USER_INSURE_INFO,dwContextID,&UserInsureInfo,sizeof(UserInsureInfo));
		}
		else
		{
			//��ȡ����
			CDBVarValue DBVarValue;
			m_TreasureDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);

			//������
			OnInsureDisposeResult(dwContextID,m_TreasureDBAide.GetReturnValue(),0L,CW2CT(DBVarValue.bstrVal),false,pQueryInsureInfo->cbActivityGame);
		}

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//�������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false,pQueryInsureInfo->cbActivityGame);

		return false;
	}

	return true;
}

//��ѯ�û�
bool CDataBaseEngineSink::OnRequestQueryTransferUserInfo(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_QueryTransferUserInfo));
	if (wDataSize!=sizeof(DBR_GR_QueryTransferUserInfo)) return false;

	//������
	DBR_GR_QueryTransferUserInfo * pQueryTransferUserInfo=(DBR_GR_QueryTransferUserInfo *)pData;

	try
	{
		//�������
		m_TreasureDBAide.ResetParameter();
		m_TreasureDBAide.AddParameter(TEXT("@cbByNickName"),pQueryTransferUserInfo->cbByNickName);
		m_TreasureDBAide.AddParameter(TEXT("@strNickName"),pQueryTransferUserInfo->szNickName);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_TreasureDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		if (m_TreasureDBAide.ExecuteProcess(TEXT("GSP_GR_QueryTransferUserInfo"),true)==DB_SUCCESS)
		{
			//��������
			DBO_GR_UserTransferUserInfo TransferUserInfo;
			ZeroMemory(&TransferUserInfo,sizeof(TransferUserInfo));

			//������Ϣ
			TransferUserInfo.cbActivityGame=pQueryTransferUserInfo->cbActivityGame;
			TransferUserInfo.dwGameID=m_TreasureDBAide.GetValue_DWORD(TEXT("GameID"));
			m_TreasureDBAide.GetValue_String(TEXT("NickName"), TransferUserInfo.szNickName, CountArray(TransferUserInfo.szNickName));

			//���ͽ��
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_USER_INSURE_USER_INFO,dwContextID,&TransferUserInfo,sizeof(TransferUserInfo));
		}
		else
		{
			//��ȡ����
			CDBVarValue DBVarValue;
			m_TreasureDBModule->GetParameter(TEXT("@strErrorDescribe"),DBVarValue);

			//������
			OnInsureDisposeResult(dwContextID,m_TreasureDBAide.GetReturnValue(),0L,CW2CT(DBVarValue.bstrVal),false,pQueryTransferUserInfo->cbActivityGame);
		}

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//�������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false,pQueryTransferUserInfo->cbActivityGame);

		return false;
	}

	return true;
}

//��������
bool CDataBaseEngineSink::OnRequestPropertyRequest(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_PropertyRequest));
		if (wDataSize!=sizeof(DBR_GR_PropertyRequest)) return false;

		//������
		DBR_GR_PropertyRequest * pPropertyRequest=(DBR_GR_PropertyRequest *)pData;
		dwUserID=pPropertyRequest->dwSourceUserID;

		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pPropertyRequest->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();

		//������Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwSourceUserID"),pPropertyRequest->dwSourceUserID);
		m_GameDBAide.AddParameter(TEXT("@dwTargetUserID"),pPropertyRequest->dwTargetUserID);
		m_GameDBAide.AddParameter(TEXT("@wPropertyID"),pPropertyRequest->wPropertyIndex);
		m_GameDBAide.AddParameter(TEXT("@wPropertyCount"),pPropertyRequest->wItemCount);

		//��������
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@wTableID"),pPropertyRequest->wTableID);

		//����ʽ
		m_GameDBAide.AddParameter(TEXT("@cbConsumeScore"),pPropertyRequest->cbConsumeScore);
		m_GameDBAide.AddParameter(TEXT("@lFrozenedScore"),pPropertyRequest->lFrozenedScore);

		//ϵͳ��Ϣ
		m_GameDBAide.AddParameter(TEXT("@dwEnterID"),pPropertyRequest->dwInoutIndex);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pPropertyRequest->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		if (m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_ConsumeProperty"),true)==DB_SUCCESS)
		{
			//��������
			DBO_GR_S_PropertySuccess PresentSuccess;
			ZeroMemory(&PresentSuccess,sizeof(PresentSuccess));

			//������Ϣ
			PresentSuccess.cbRequestArea=pPropertyRequest->cbRequestArea;
			PresentSuccess.wItemCount=pPropertyRequest->wItemCount;
			PresentSuccess.wPropertyIndex=pPropertyRequest->wPropertyIndex;
			PresentSuccess.dwSourceUserID=pPropertyRequest->dwSourceUserID;
			PresentSuccess.dwTargetUserID=pPropertyRequest->dwTargetUserID;

			//����ģʽ
			PresentSuccess.cbConsumeScore=pPropertyRequest->cbConsumeScore;
			PresentSuccess.lFrozenedScore=pPropertyRequest->lFrozenedScore;

			//�û�Ȩ��
			PresentSuccess.dwUserRight=pPropertyRequest->dwUserRight;

			//�����Ϣ
			PresentSuccess.lConsumeGold=m_GameDBAide.GetValue_LONGLONG(TEXT("ConsumeGold"));
			PresentSuccess.lSendLoveLiness=m_GameDBAide.GetValue_LONG(TEXT("SendLoveLiness"));
			PresentSuccess.lRecvLoveLiness=m_GameDBAide.GetValue_LONG(TEXT("RecvLoveLiness"));
			PresentSuccess.cbMemberOrder=m_GameDBAide.GetValue_BYTE(TEXT("MemberOrder"));

			//���ͽ��
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_PROPERTY_SUCCESS,dwContextID,&PresentSuccess,sizeof(PresentSuccess));
		}
		else
		{
			//��ȡ����
			CDBVarValue DBVarValue;
			m_GameDBAide.GetParameter(TEXT("@strErrorDescribe"),DBVarValue);

			//��������
			DBO_GR_PropertyFailure PropertyFailure;
			ZeroMemory(&PropertyFailure,sizeof(PropertyFailure));

			//���ñ���
			PropertyFailure.lResultCode=m_GameDBAide.GetReturnValue();
			PropertyFailure.lFrozenedScore=pPropertyRequest->lFrozenedScore;
			PropertyFailure.cbRequestArea=pPropertyRequest->cbRequestArea;
			lstrcpyn(PropertyFailure.szDescribeString,CW2CT(DBVarValue.bstrVal),CountArray(PropertyFailure.szDescribeString));

			//���ͽ��
			WORD wDataSize=CountStringBuffer(PropertyFailure.szDescribeString);
			WORD wHeadSize=sizeof(PropertyFailure)-sizeof(PropertyFailure.szDescribeString);
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_PROPERTY_FAILURE,dwContextID,&PropertyFailure,wHeadSize+wDataSize);
		}
	}
	catch (IDataBaseException * pIException)
	{
		//�������
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//��������
		DBO_GR_PropertyFailure PropertyFailure;
		ZeroMemory(&PropertyFailure,sizeof(PropertyFailure));

		//��������
		DBR_GR_PropertyRequest * pPropertyRequest=(DBR_GR_PropertyRequest *)pData;

		//���ñ���
		PropertyFailure.lResultCode=DB_ERROR;
		PropertyFailure.lFrozenedScore=pPropertyRequest->lFrozenedScore;
		PropertyFailure.cbRequestArea=pPropertyRequest->cbRequestArea;
		lstrcpyn(PropertyFailure.szDescribeString,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),CountArray(PropertyFailure.szDescribeString));

		//���ͽ��
		WORD wDataSize=CountStringBuffer(PropertyFailure.szDescribeString);
		WORD wHeadSize=sizeof(PropertyFailure)-sizeof(PropertyFailure.szDescribeString);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_PROPERTY_FAILURE,dwContextID,&PropertyFailure,wHeadSize+wDataSize);

		return false;
	}

	return true;
}

//��������
bool CDataBaseEngineSink::OnRequestMatchFee(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_MatchFee));
	if (wDataSize!=sizeof(DBR_GR_MatchFee)) return false;

	//��������
	DBR_GR_MatchFee * pMatchFee=(DBR_GR_MatchFee *)pData;
	dwUserID=INVALID_DWORD;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pMatchFee->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pMatchFee->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchFee"),pMatchFee->dwMatchFee);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@dwMatchID"),pMatchFee->dwMatchID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchNO"),pMatchFee->dwMatchNO);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pMatchFee->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_UserMatchFee"),true);

		//���ͽ��
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_MATCH_FEE_RESULT,dwContextID,&lReturnValue,sizeof(lReturnValue));

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//������ʼ
bool CDataBaseEngineSink::OnRequestMatchStart(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_MatchStart));
	if (wDataSize!=sizeof(DBR_GR_MatchStart)) return false;

	//��������
	DBR_GR_MatchStart * pMatchStart=(DBR_GR_MatchStart *)pData;
	dwUserID=INVALID_DWORD;

	//������
	try
	{
		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wMatchID"),pMatchStart->dwMatchID);
		m_GameDBAide.AddParameter(TEXT("@wMatchNo"),pMatchStart->dwMatchNo);
		m_GameDBAide.AddParameter(TEXT("@wMatchCount"),pMatchStart->wMatchCount);	
		m_GameDBAide.AddParameter(TEXT("@lInitScore"),pMatchStart->lInitScore);	

// 		//�������
// 		TCHAR szDescribeString[128]=TEXT("");
// 		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_MatchStart"),true);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//��������
bool CDataBaseEngineSink::OnRequestMatchOver(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_MatchOver));
	if (wDataSize!=sizeof(DBR_GR_MatchOver)) return false;

	//��������
	DBR_GR_MatchOver * pMatchOver=(DBR_GR_MatchOver *)pData;
	dwUserID=INVALID_DWORD;

	//������
	try
	{
		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wMatchID"),pMatchOver->dwMatchID);
		m_GameDBAide.AddParameter(TEXT("@wMatchNo"),pMatchOver->dwMatchNo);
		m_GameDBAide.AddParameter(TEXT("@wMatchCount"),pMatchOver->wMatchCount);		

// 		//�������
// 		TCHAR szDescribeString[128]=TEXT("");
// 		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_MatchOver"),true);

		if(lReturnValue==DB_SUCCESS)
		{
			LONG lCount=0;
			if(m_GameDBModule.GetInterface()!=NULL)
				lCount=m_GameDBModule->GetRecordCount();
			DBO_GR_MatchRank *pMatchRank=new DBO_GR_MatchRank[lCount];
			for(LONG i=0; i<lCount; i++)
			{
				pMatchRank[i].cbRank=(BYTE)i;
				m_GameDBAide.GetValue_String(TEXT("NickName"),pMatchRank[i].szNickName,CountArray(pMatchRank[i].szNickName));
				pMatchRank[i].lMatchScore=m_GameDBAide.GetValue_LONG(TEXT("HScore"));
				m_GameDBModule->MoveToNext();
				if(m_GameDBModule->IsRecordsetEnd()) break;
			}
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_MATCH_RANK,dwContextID,pMatchRank,(WORD)(sizeof(DBO_GR_MatchRank)*lCount));
			if(pMatchRank!=NULL)
				SafeDeleteArray(pMatchRank);
		}
	
		
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//��������
bool CDataBaseEngineSink::OnRequestMatchReward(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_MatchReward));
	if (wDataSize!=sizeof(DBR_GR_MatchReward)) return false;

	//��������
	DBR_GR_MatchReward * pMatchReward=(DBR_GR_MatchReward *)pData;
	dwUserID=INVALID_DWORD;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pMatchReward->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pMatchReward->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchID"),pMatchReward->dwMatchID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchNO"),pMatchReward->dwMatchNO);
		m_GameDBAide.AddParameter(TEXT("@wRank"),pMatchReward->wRank);
		m_GameDBAide.AddParameter(TEXT("@lMatchScore"),pMatchReward->lMatchScore);
		m_GameDBAide.AddParameter(TEXT("@dwExperience"),pMatchReward->dwExperience);
		m_GameDBAide.AddParameter(TEXT("@dwGold"),pMatchReward->dwGold);
		m_GameDBAide.AddParameter(TEXT("@dwMedal"),pMatchReward->dwMedal);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);

		//�������
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_MatchReward"),true);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//�˳�����
bool CDataBaseEngineSink::OnRequestMatchQuit(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_MatchFee));
	if (wDataSize!=sizeof(DBR_GR_MatchFee)) return false;

	//��������
	DBR_GR_MatchFee * pMatchFee=(DBR_GR_MatchFee *)pData;
	dwUserID=INVALID_DWORD;

	//������
	try
	{
		//ת����ַ
		TCHAR szClientAddr[16]=TEXT("");
		BYTE * pClientAddr=(BYTE *)&pMatchFee->dwClientAddr;
		_sntprintf(szClientAddr,CountArray(szClientAddr),TEXT("%d.%d.%d.%d"),pClientAddr[0],pClientAddr[1],pClientAddr[2],pClientAddr[3]);

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pMatchFee->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchFee"),pMatchFee->dwMatchFee);
		m_GameDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceOption->wKindID);
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameDBAide.AddParameter(TEXT("@strClientIP"),szClientAddr);
		m_GameDBAide.AddParameter(TEXT("@dwMatchID"),pMatchFee->dwMatchID);
		m_GameDBAide.AddParameter(TEXT("@dwMatchNO"),pMatchFee->dwMatchNO);
		m_GameDBAide.AddParameter(TEXT("@strMachineID"),pMatchFee->szMachineID);

		//�������
		TCHAR szDescribeString[128]=TEXT("");
		m_GameDBAide.AddParameterOutput(TEXT("@strErrorDescribe"),szDescribeString,sizeof(szDescribeString),adParamOutput);

		//�������
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_UserMatchQuit"),true);

		//���ͽ��
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_MATCH_QUIT_RESULT,dwContextID,&lReturnValue,sizeof(lReturnValue));

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}
}

//�û�Ȩ��
bool CDataBaseEngineSink::OnRequestManageUserRight(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_ManageUserRight));
		if (wDataSize!=sizeof(DBR_GR_ManageUserRight)) return false;

		//������
		DBR_GR_ManageUserRight * pManageUserRight=(DBR_GR_ManageUserRight *)pData;
		dwUserID=pManageUserRight->dwUserID;

		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@dwUserID"),pManageUserRight->dwUserID);
		m_GameDBAide.AddParameter(TEXT("@dwAddRight"),pManageUserRight->dwAddRight);
		m_GameDBAide.AddParameter(TEXT("@dwRemoveRight"),pManageUserRight->dwRemoveRight);

		//ִ�в�ѯ
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_ManageUserRight"),false);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//ϵͳ��Ϣ
bool CDataBaseEngineSink::OnRequestLoadSystemMessage(DWORD dwContextID, VOID * pData, WORD wDataSize, DWORD &dwUserID)
{
	try
	{
		//�������
		m_GameDBAide.ResetParameter();
		m_GameDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//ִ�в�ѯ
		LONG lReturnValue=m_GameDBAide.ExecuteProcess(TEXT("GSP_GR_LoadSystemMessage"),true);

		//�������
		if(lReturnValue==0)
		{
			TCHAR szServerID[32]={0};
			_sntprintf(szServerID, CountArray(szServerID), TEXT("%d"), m_pGameServiceOption->wServerID);

			while(true)
			{
				//�����ж�
				if (m_GameDBModule->IsRecordsetEnd()==true) break;

				//�������
				TCHAR szServerRange[1024]={0};
				CString strServerRange;
				bool bSendMessage=false;
				bool bAllRoom=false;

				//��ȡ��Χ
				m_GameDBAide.GetValue_String(TEXT("ServerRange"), szServerRange, CountArray(szServerRange));
				szServerRange[1023]=0;
				strServerRange.Format(TEXT("%s"), szServerRange);

				//��Χ�ж�
				while(true)
				{
					int nfind=strServerRange.Find(TEXT(','));
					if(nfind!=-1 && nfind>0)
					{
						CString strID=strServerRange.Left(nfind);
						WORD wServerID=StrToInt(strID);
						bSendMessage=(wServerID==0 || wServerID==m_pGameServiceOption->wServerID);
						if(wServerID==0)bAllRoom=true;

						if(bSendMessage) break;

						strServerRange=strServerRange.Right(strServerRange.GetLength()-nfind-1);
					}
					else
					{
						WORD wServerID=StrToInt(szServerRange);
						bSendMessage=(wServerID==0 || wServerID==m_pGameServiceOption->wServerID);
						if(wServerID==0)bAllRoom=true;

						break;
					}
				}

				//������Ϣ
				if(bSendMessage)
				{
					//�������
					DBR_GR_SystemMessage SystemMessage;
					ZeroMemory(&SystemMessage, sizeof(SystemMessage));

					//��ȡ��Ϣ
					SystemMessage.cbMessageID=m_GameDBAide.GetValue_BYTE(TEXT("ID"));
					SystemMessage.cbMessageType=m_GameDBAide.GetValue_BYTE(TEXT("MessageType"));
					SystemMessage.dwTimeRate=m_GameDBAide.GetValue_DWORD(TEXT("TimeRate"));
					SystemMessage.cbAllRoom=bAllRoom?TRUE:FALSE;
					m_GameDBAide.GetValue_String(TEXT("MessageString"),SystemMessage.szSystemMessage,CountArray(SystemMessage.szSystemMessage));

					//���ͽ��
					m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_SYSTEM_MESSAGE_RESULT,dwContextID,&SystemMessage,sizeof(SystemMessage));
				}

				//��һ��
				m_GameDBModule->MoveToNext();
			}
		}

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		CTraceService::TraceString(pIException->GetExceptionDescribe(),TraceLevel_Exception);

		//������
		OnInsureDisposeResult(dwContextID,DB_ERROR,0L,TEXT("�������ݿ�����쳣�������Ժ����ԣ�"),false);

		return false;
	}

	return true;
}

//��¼���
VOID CDataBaseEngineSink::OnLogonDisposeResult(DWORD dwContextID, DWORD dwErrorCode, LPCTSTR pszErrorString, bool bMobileClient,BYTE cbDeviceType,WORD wBehaviorFlags,WORD wPageTableCount)
{
	if (dwErrorCode==DB_SUCCESS)
	{
		//��������
		m_LogonSuccess.wFaceID=m_GameDBAide.GetValue_WORD(TEXT("FaceID"));
		m_LogonSuccess.dwUserID=m_GameDBAide.GetValue_DWORD(TEXT("UserID"));
		m_LogonSuccess.dwGameID=m_GameDBAide.GetValue_DWORD(TEXT("GameID"));
		m_LogonSuccess.dwGroupID=m_GameDBAide.GetValue_DWORD(TEXT("GroupID"));
		m_LogonSuccess.dwCustomID=m_GameDBAide.GetValue_DWORD(TEXT("CustomID"));
		m_GameDBAide.GetValue_String(TEXT("NickName"),m_LogonSuccess.szNickName,CountArray(m_LogonSuccess.szNickName));
		m_GameDBAide.GetValue_String(TEXT("GroupName"),m_LogonSuccess.szGroupName,CountArray(m_LogonSuccess.szGroupName));

		//�û�����
		m_LogonSuccess.cbGender=m_GameDBAide.GetValue_BYTE(TEXT("Gender"));
		m_LogonSuccess.cbMemberOrder=m_GameDBAide.GetValue_BYTE(TEXT("MemberOrder"));
		m_LogonSuccess.cbMasterOrder=m_GameDBAide.GetValue_BYTE(TEXT("MasterOrder"));
		m_GameDBAide.GetValue_String(TEXT("UnderWrite"),m_LogonSuccess.szUnderWrite,CountArray(m_LogonSuccess.szUnderWrite));

		//������Ϣ
		m_LogonSuccess.lScore=m_GameDBAide.GetValue_LONGLONG(TEXT("Score"));
		m_LogonSuccess.lGrade=m_GameDBAide.GetValue_LONGLONG(TEXT("Grade"));
		m_LogonSuccess.lInsure=m_GameDBAide.GetValue_LONGLONG(TEXT("Insure"));

		//������Ϣ
		m_LogonSuccess.dwWinCount=m_GameDBAide.GetValue_LONG(TEXT("WinCount"));
		m_LogonSuccess.dwLostCount=m_GameDBAide.GetValue_LONG(TEXT("LostCount"));
		m_LogonSuccess.dwDrawCount=m_GameDBAide.GetValue_LONG(TEXT("DrawCount"));
		m_LogonSuccess.dwFleeCount=m_GameDBAide.GetValue_LONG(TEXT("FleeCount"));
		m_LogonSuccess.dwUserMedal=m_GameDBAide.GetValue_LONG(TEXT("UserMedal"));
		m_LogonSuccess.dwExperience=m_GameDBAide.GetValue_LONG(TEXT("Experience"));
		m_LogonSuccess.lLoveLiness=m_GameDBAide.GetValue_LONG(TEXT("LoveLiness"));

		//������Ϣ
		m_LogonSuccess.dwUserRight=m_GameDBAide.GetValue_DWORD(TEXT("UserRight"));
		m_LogonSuccess.dwMasterRight=m_GameDBAide.GetValue_DWORD(TEXT("MasterRight"));
		m_LogonSuccess.cbDeviceType=cbDeviceType;
		m_LogonSuccess.wBehaviorFlags=wBehaviorFlags;
		m_LogonSuccess.wPageTableCount=wPageTableCount;

		//��������
		m_LogonSuccess.dwInoutIndex=m_GameDBAide.GetValue_DWORD(TEXT("InoutIndex"));

		//��ȡ��Ϣ
		if(pszErrorString!=NULL)lstrcpyn(m_LogonSuccess.szDescribeString,pszErrorString,CountArray(m_LogonSuccess.szDescribeString));

		//���ͽ��
		WORD wDataSize=CountStringBuffer(m_LogonSuccess.szDescribeString);
		WORD wHeadSize=sizeof(m_LogonSuccess)-sizeof(m_LogonSuccess.szDescribeString);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_LOGON_SUCCESS,dwContextID,&m_LogonSuccess,wHeadSize+wDataSize);
	}
	else
	{
		//��������
		DBO_GR_LogonFailure LogonFailure;
		ZeroMemory(&LogonFailure,sizeof(LogonFailure));

		//��������
		LogonFailure.lResultCode=dwErrorCode;
		lstrcpyn(LogonFailure.szDescribeString,pszErrorString,CountArray(LogonFailure.szDescribeString));

		//���ͽ��
		WORD wDataSize=CountStringBuffer(LogonFailure.szDescribeString);
		WORD wHeadSize=sizeof(LogonFailure)-sizeof(LogonFailure.szDescribeString);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_LOGON_FAILURE,dwContextID,&LogonFailure,wHeadSize+wDataSize);
	}

	return;
}

//���н��
VOID CDataBaseEngineSink::OnInsureDisposeResult(DWORD dwContextID, DWORD dwErrorCode, SCORE lFrozenedScore, LPCTSTR pszErrorString, bool bMobileClient,BYTE cbActivityGame)
{
	if (dwErrorCode==DB_SUCCESS)
	{
		//��������
		DBO_GR_UserInsureSuccess UserInsureSuccess;
		ZeroMemory(&UserInsureSuccess,sizeof(UserInsureSuccess));

		//�������
		UserInsureSuccess.cbActivityGame=cbActivityGame;
		UserInsureSuccess.lFrozenedScore=lFrozenedScore;
		UserInsureSuccess.dwUserID=m_TreasureDBAide.GetValue_DWORD(TEXT("UserID"));
		UserInsureSuccess.lSourceScore=m_TreasureDBAide.GetValue_LONGLONG(TEXT("SourceScore"));
		UserInsureSuccess.lSourceInsure=m_TreasureDBAide.GetValue_LONGLONG(TEXT("SourceInsure"));
		UserInsureSuccess.lInsureRevenue=m_TreasureDBAide.GetValue_LONGLONG(TEXT("InsureRevenue"));
		UserInsureSuccess.lVariationScore=m_TreasureDBAide.GetValue_LONGLONG(TEXT("VariationScore"));
		UserInsureSuccess.lVariationInsure=m_TreasureDBAide.GetValue_LONGLONG(TEXT("VariationInsure"));
		lstrcpyn(UserInsureSuccess.szDescribeString,pszErrorString,CountArray(UserInsureSuccess.szDescribeString));

		//���ͽ��
		WORD wDataSize=CountStringBuffer(UserInsureSuccess.szDescribeString);
		WORD wHeadSize=sizeof(UserInsureSuccess)-sizeof(UserInsureSuccess.szDescribeString);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_USER_INSURE_SUCCESS,dwContextID,&UserInsureSuccess,wHeadSize+wDataSize);
	}
	else
	{
		//��������
		DBO_GR_UserInsureFailure UserInsureFailure;
		ZeroMemory(&UserInsureFailure,sizeof(UserInsureFailure));

		//�������
		UserInsureFailure.cbActivityGame=cbActivityGame;
		UserInsureFailure.lResultCode=dwErrorCode;
		UserInsureFailure.lFrozenedScore=lFrozenedScore;
		lstrcpyn(UserInsureFailure.szDescribeString,pszErrorString,CountArray(UserInsureFailure.szDescribeString));

		//���ͽ��
		WORD wDataSize=CountStringBuffer(UserInsureFailure.szDescribeString);
		WORD wHeadSize=sizeof(UserInsureFailure)-sizeof(UserInsureFailure.szDescribeString);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBO_GR_USER_INSURE_FAILURE,dwContextID,&UserInsureFailure,wHeadSize+wDataSize);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////
