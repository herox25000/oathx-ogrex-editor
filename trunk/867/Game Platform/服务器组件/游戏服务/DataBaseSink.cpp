#include "StdAfx.h"
#include "Afxinet.h"
#include "DataBaseSink.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CDataBaseSink::CDataBaseSink()
{
	//���ñ���
	m_pGameUserDBInfo=NULL;
	m_pGameScoreDBInfo=NULL;
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;
	m_pIDataBaseEngineEvent=NULL;

	return;
}

//��������
CDataBaseSink::~CDataBaseSink()
{
}

//�ӿڲ�ѯ
void * __cdecl CDataBaseSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IDataBaseEngineSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IDataBaseEngineSink,Guid,dwQueryVer);
	return NULL;
}

//����ģ������
bool __cdecl CDataBaseSink::OnDataBaseEngineStart(IUnknownEx * pIUnknownEx)
{
	//��������
	if ((m_AccountsDBModule.GetInterface()==NULL)&&(m_AccountsDBModule.CreateInstance()==false))
	{
		ASSERT(FALSE);
		return false;
	}

	//��������
	if ((m_GameScoreDBModule.GetInterface()==NULL)&&(m_GameScoreDBModule.CreateInstance()==false))
	{
		ASSERT(FALSE);
		return false;
	}

	try
	{
		//��������
		BYTE * pcbAddr=NULL;
		TCHAR szDataBaseAddr[16]=TEXT("");

		//�����û����ݿ�
		pcbAddr=(BYTE *)&m_pGameUserDBInfo->dwDataBaseAddr;
		_snprintf(szDataBaseAddr,sizeof(szDataBaseAddr),TEXT("%d.%d.%d.%d"),pcbAddr[0],pcbAddr[1],pcbAddr[2],pcbAddr[3]);
		m_AccountsDBModule->SetConnectionInfo(szDataBaseAddr,m_pGameUserDBInfo->wDataBasePort,m_pGameUserDBInfo->szDataBaseName,
			m_pGameUserDBInfo->szDataBaseUser,m_pGameUserDBInfo->szDataBasePass);

		//��������
		m_AccountsDBModule->OpenConnection();
		m_AccountsDBAide.SetDataBase(m_AccountsDBModule.GetInterface());

		//������Ϸ���ݿ�
		pcbAddr=(BYTE *)&m_pGameScoreDBInfo->dwDataBaseAddr;
		_snprintf(szDataBaseAddr,sizeof(szDataBaseAddr),TEXT("%d.%d.%d.%d"),pcbAddr[0],pcbAddr[1],pcbAddr[2],pcbAddr[3]);
		m_GameScoreDBModule->SetConnectionInfo(szDataBaseAddr,m_pGameScoreDBInfo->wDataBasePort,m_pGameScoreDBInfo->szDataBaseName,
			m_pGameScoreDBInfo->szDataBaseUser,m_pGameScoreDBInfo->szDataBasePass);

		//��������
		m_GameScoreDBModule->OpenConnection();
		m_GameScoreDBAide.SetDataBase(m_GameScoreDBModule.GetInterface());
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);

		return false;
	}

	return true;
}

//����ģ��ر�
bool __cdecl CDataBaseSink::OnDataBaseEngineStop(IUnknownEx * pIUnknownEx)
{
	try
	{
		//�ر�����
		if (m_AccountsDBModule.GetInterface()) m_AccountsDBModule->CloseConnection();
		if (m_GameScoreDBModule.GetInterface()) m_GameScoreDBModule->CloseConnection();

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);

		return false;
	}

	return false;
}

//���ݲ�������
bool __cdecl CDataBaseSink::OnDataBaseEngineRequest(WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	switch (wRequestID)
	{
	case DBR_GR_LOGON_BY_USERID:		//I D ��¼
		{
			return OnRequestLogon(dwContextID,pData,wDataSize);
		}
	case DBR_GR_WRITE_GAME_SCORE:		//д�ֲ���
		{
			return OnRequestWriteUserScore(dwContextID,pData,wDataSize);
		}
	case DBR_GR_LEAVE_GAME_SERVER:		//�뿪����
		{
			return OnRequestLeaveGameServer(dwContextID,pData,wDataSize);
		}
	case DBR_GR_LIMIT_ACCOUNTS:			//�����ʺ�
		{
			return OnRequestLimitAccounts(dwContextID,pData,wDataSize);
		}
	case DBR_GR_SET_USER_RIGHT:			//����Ȩ��
		{
			return OnRequestSetUserRight(dwContextID,pData,wDataSize);
		}
	case DBR_GR_LOAD_ANDROID:			//�����û�
		{
			return OnRequestLoadAndroid(dwContextID,pData,wDataSize);
		}
	case DBR_GR_SEND_GIFT:				//�����ʻ�
		{
			return OnRequestSendGift(dwContextID,pData,wDataSize);
		}
	case DBR_GR_BUY_PROPERTY:			//������Ϣ
		{
			return OnRequestProperty(dwContextID,pData,wDataSize);
		}
	case DBR_GR_WRITE_PROPERTY:			//д�����
		{
			return OnWriteProperty(dwContextID,pData,wDataSize);
		}
	case DBR_GR_LOAD_PROPERTY:			//���ص���
		{
			return OnLoadProperty(dwContextID,pData,wDataSize);
		}
	case DBR_GR_EXCHANGE_CHARM:			//�����һ�
		{
			return OnExchangeCharm(dwContextID,pData,wDataSize);
		}
	case DBR_GR_BANK_GET_GOLD:			//��ȡ���
		{
			return OnBankDrawoutGold(dwContextID,pData,wDataSize);
		}
	case DBR_GR_BANK_STORAGE_GOLD:		//�洢���
		{
			return OnBankStorageGold(dwContextID,pData,wDataSize);
		}
	case DBR_GR_CLEARSCORELOCKER:		//�������������û�
		{
			return OnClearScoreLocker(dwContextID,pData,wDataSize);
		}
	case DBR_GR_USER_ROUND_SCORE:			//ÿ�ּ�¼�洢
		{
			return OnRequestRoundScore(dwContextID,pData,wDataSize);
		}
	case DBR_GR_TRANSFER_MONEY:		//ת��
		{
			return OnRequestTransferMoney(dwContextID,pData,wDataSize);
		}
	case DBR_GR_QUERY_TRANSFER_LOG:	//��ѯ������־
		{
			return OnRequestQueryTransferLog(dwContextID,pData,wDataSize);
		}
	case DBR_GR_MODIFY_LOGIN_PASSWOR:		//�޸ĵ�½����
		{
			return OnRequestModifyLoginPassword(dwContextID,pData,wDataSize);
		}
	case DBR_GR_MODIFY_BANK_PASSWORD:	//�޸���������
		{
			return OnRequestModifyBankPassword(dwContextID,pData,wDataSize);
		}
	case DBR_GR_MODIFY_NICKNAME:		//�޸��ǳ�
		{
			return OnRequestModifyNickname(dwContextID,pData,wDataSize);
		}
	case DBR_GR_BANK_TASK:			//���в���
		{
			return OnRequestBankTask(dwContextID,pData,wDataSize);
		}
	case DBR_GR_QUERYUSERNAME:
		{
			return OnRequsetQueryUserName(dwContextID,pData,wDataSize);
		}
	}

	return false;
}

//��¼������
bool CDataBaseSink::OnRequestLogon(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_LogonByUserID));
	if (wDataSize!=sizeof(DBR_GR_LogonByUserID)) return false;

	//��½����
	try
	{
		//ִ�в�ѯ
		DBR_GR_LogonByUserID * pLogonByUserID=(DBR_GR_LogonByUserID *)pData;
		LONG lReturnValue=SPLogonByUserID(pLogonByUserID->dwUserID,pLogonByUserID->szPassWord,pLogonByUserID->dwClientIP,pLogonByUserID->szComputerID);

		//��¼ʧ��
		if (lReturnValue!=0L)
		{
			DBR_GR_LogonError LogonError;
			LogonError.lErrorCode=lReturnValue;
			m_GameScoreDBAide.GetValue_String(TEXT("ErrorDescribe"),LogonError.szErrorDescribe,CountArray(LogonError.szErrorDescribe));
			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_LOGON_ERROR,dwContextID,&LogonError,sizeof(LogonError));
			m_GameScoreDBModule->CloseRecordset();
			return true;
		}

		//��������
		DBR_GR_LogonSuccess LogonSuccess;
		memset(&LogonSuccess,0,sizeof(LogonSuccess));

		//��ȡ�û���Ϣ
		LogonSuccess.dwUserID=m_GameScoreDBAide.GetValue_DWORD(TEXT("UserID"));
		LogonSuccess.dwCustomFaceVer=m_GameScoreDBAide.GetValue_DWORD(TEXT("CustomFaceVer"));
		LogonSuccess.dwGameID=m_GameScoreDBAide.GetValue_DWORD(TEXT("GameID"));
		LogonSuccess.wFaceID=m_GameScoreDBAide.GetValue_WORD(TEXT("FaceID"));
		LogonSuccess.dwGroupID=m_GameScoreDBAide.GetValue_DWORD(TEXT("GroupID"));
		LogonSuccess.lExperience=m_GameScoreDBAide.GetValue_LONG(TEXT("Experience"));
		LogonSuccess.dwUserRight=m_GameScoreDBAide.GetValue_DWORD(TEXT("UserRight"));
		LogonSuccess.lLoveliness=m_GameScoreDBAide.GetValue_DWORD(TEXT("Loveliness"));
		LogonSuccess.dwMasterRight=m_GameScoreDBAide.GetValue_DWORD(TEXT("MasterRight"));
		m_GameScoreDBAide.GetValue_String(TEXT("Accounts"),LogonSuccess.szAccounts,CountArray(LogonSuccess.szAccounts));
		m_GameScoreDBAide.GetValue_String(TEXT("GroupName"),LogonSuccess.szGroupName,CountArray(LogonSuccess.szGroupName));
		m_GameScoreDBAide.GetValue_String(TEXT("UnderWrite"),LogonSuccess.szUnderWrite,CountArray(LogonSuccess.szUnderWrite));
		m_GameScoreDBAide.GetValue_String(TEXT("BankPassWord"),LogonSuccess.szBankPassWord,CountArray(LogonSuccess.szBankPassWord));

		//�û�����
		LogonSuccess.cbGender=m_GameScoreDBAide.GetValue_BYTE(TEXT("Gender"));
		LogonSuccess.cbMemberOrder=m_GameScoreDBAide.GetValue_BYTE(TEXT("MemberOrder"));
		LogonSuccess.cbMasterOrder=m_GameScoreDBAide.GetValue_BYTE(TEXT("MasterOrder"));

		//��ȡ��Ϸ��Ϣ
		LogonSuccess.lScore=m_GameScoreDBAide.GetValue_LONGLONG(TEXT("Score"));
		LogonSuccess.lInsureScore=m_GameScoreDBAide.GetValue_LONGLONG(TEXT("InsureScore"));
		LogonSuccess.lGameGold=m_GameScoreDBAide.GetValue_LONGLONG(TEXT("GameGold"));
		LogonSuccess.lWinCount=m_GameScoreDBAide.GetValue_LONG(TEXT("WinCount"));
		LogonSuccess.lLostCount=m_GameScoreDBAide.GetValue_LONG(TEXT("LostCount"));
		LogonSuccess.lDrawCount=m_GameScoreDBAide.GetValue_LONG(TEXT("DrawCount"));
		LogonSuccess.lFleeCount=m_GameScoreDBAide.GetValue_LONG(TEXT("FleeCount"));

		//������Ϣ
		CopyMemory(LogonSuccess.szPassWord,pLogonByUserID->szPassWord,sizeof(LogonSuccess.szPassWord));

		//Ͷ�ݵ���֪ͨ
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_LOGON_SUCCESS,dwContextID,&LogonSuccess,sizeof(LogonSuccess));

		//������Ŀ
		int nPropertyCount = 0;
		nPropertyCount=m_GameScoreDBAide.GetValue_INT(TEXT("PropCount"));

		//���ص���
		if ( 0 < nPropertyCount )
		{
			lReturnValue = SPLoadUserProperty(pLogonByUserID->dwUserID);

			if ( lReturnValue == 0 )
			{
				DBR_GR_UserProperty UserProperty;
				ZeroMemory(&UserProperty, sizeof(UserProperty));

				UserProperty.dwUserID = LogonSuccess.dwUserID;

				//��ȡ��¼
				m_GameScoreDBModule->MoveToFirst();
				while ( m_GameScoreDBModule->IsRecordsetEnd() == false )
				{
					UserProperty.nPropertyID=m_GameScoreDBAide.GetValue_INT(TEXT("CateID"));
					UserProperty.dwCurCount=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount"));

					//Ͷ�ݵ���֪ͨ
					m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_USER_PROPERTY,dwContextID, &UserProperty, sizeof(UserProperty));

					//�ƶ���¼
					m_GameScoreDBModule->MoveToNext();
				}

				//Ͷ�ݵ���֪ͨ
				m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_LOAD_PROP_FINISHI,dwContextID, 0, 0);
			}
		}
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe(); 
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);

		//����ʧ��
		DBR_GR_LogonError LogonError;
		LogonError.lErrorCode=-1;
		lstrcpyn(LogonError.szErrorDescribe,TEXT("�������ݿ�����쳣�������Ժ����Ի�ѡ����һ��Ϸ��������"),sizeof(LogonError.szErrorDescribe));
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_LOGON_ERROR,dwContextID,&LogonError,sizeof(LogonError));
	}

	//�رռ�¼��)
	m_GameScoreDBModule->CloseRecordset();

	return true;
}

//д������
bool CDataBaseSink::OnRequestWriteUserScore(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_WriteUserScore));
		if (wDataSize!=sizeof(DBR_GR_WriteUserScore)) return false;

		//ִ�в�ѯ
		DBR_GR_WriteUserScore * pWriteUserScore=(DBR_GR_WriteUserScore *)pData;
		LONG lReturnValue=SPWriteUserScore(pWriteUserScore->dwUserID,pWriteUserScore->dwPlayTimeCount,pWriteUserScore->dwOnlineTimeCount,
			pWriteUserScore->dwClientIP,pWriteUserScore->lRevenue,pWriteUserScore->ScoreModifyInfo);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//�뿪����
bool CDataBaseSink::OnRequestLeaveGameServer(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_LeaveGameServer));
		if (wDataSize!=sizeof(DBR_GR_LeaveGameServer)) return false;

		//ִ�в�ѯ
		DBR_GR_LeaveGameServer * pLeaveGameServer=(DBR_GR_LeaveGameServer *)pData;
		LONG lReturnValue=SPLeaveGameServer(pLeaveGameServer->dwUserID,pLeaveGameServer->dwPlayTimeCount,pLeaveGameServer->dwOnlineTimeCount,
			pLeaveGameServer->dwClientIP,pLeaveGameServer->lRevenue,pLeaveGameServer->lLoveliness,pLeaveGameServer->ScoreModifyInfo);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//�����ʻ�
bool CDataBaseSink::OnRequestLimitAccounts(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_LimitAccounts));
		if (wDataSize!=sizeof(DBR_GR_LimitAccounts)) return false;

		//ִ�в�ѯ
		DBR_GR_LimitAccounts * pLimitAccounts=(DBR_GR_LimitAccounts *)pData;
		LONG lReturnValue=SPCongealAccounts(pLimitAccounts->dwUserID,pLimitAccounts->dwMasterUserID,pLimitAccounts->dwMasterClientIP);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//����Ȩ��
bool CDataBaseSink::OnRequestSetUserRight(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_SetUserRight));
	if (wDataSize!=sizeof(DBR_GR_SetUserRight)) return false;

	//ִ�в�ѯ
	DBR_GR_SetUserRight * pSetUserRight=(DBR_GR_SetUserRight *)pData;
	LONG lGameFailed = TRUE,lAccountsFailed = TRUE;

	try
	{
		//��ϷȨ��
		if (pSetUserRight->cbGame==TRUE) 
		{
			lGameFailed = SPSetUserGameRight(pSetUserRight->dwUserID,pSetUserRight->dwUserRight,pSetUserRight->dwMasterUserID,pSetUserRight->dwMasterClientIP);
		}

		//�ʺ�Ȩ��
		if (pSetUserRight->cbAccounts==TRUE) 
		{
			lAccountsFailed = SPSetUserAccountsRight(pSetUserRight->dwUserID,pSetUserRight->dwUserRight,pSetUserRight->dwMasterUserID,pSetUserRight->dwMasterClientIP);
		}

		//������Ϣ
		DBR_GR_UserRightResult UserRightResult;
		ZeroMemory(&UserRightResult,sizeof(UserRightResult));

		UserRightResult.dwUserRight = pSetUserRight->dwUserRight;
		UserRightResult.dwUserID = pSetUserRight->dwUserID;
		UserRightResult.dwMasterUserID = pSetUserRight->dwMasterUserID;
		UserRightResult.bGameSuccess=((lGameFailed==FALSE)?true:false);
		UserRightResult.bAccountsSuccess=((lAccountsFailed==FALSE)?true:false);

		//������Ϣ
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_USER_RIGHT_RESULT,dwContextID,&UserRightResult,sizeof( UserRightResult ));

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);

		//������Ϣ
		DBR_GR_UserRightResult UserRightResult;
		ZeroMemory(&UserRightResult,sizeof(UserRightResult));

		UserRightResult.dwUserRight = pSetUserRight->dwUserRight;
		UserRightResult.dwUserID = pSetUserRight->dwUserID;
		UserRightResult.dwMasterUserID = pSetUserRight->dwMasterUserID;
		UserRightResult.bGameSuccess=((lGameFailed==FALSE)?true:false);
		UserRightResult.bAccountsSuccess=((lAccountsFailed==FALSE)?true:false);

		//������Ϣ
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_USER_RIGHT_RESULT,dwContextID,&UserRightResult,sizeof( UserRightResult ));
	}

	return true;
}

//�����û�
bool CDataBaseSink::OnRequestLoadAndroid(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//��������
		DBO_GR_AndroidUser AndroidUser;
		ZeroMemory(&AndroidUser,sizeof(AndroidUser));

		//�û��ʻ�
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		//ִ�в�ѯ
		AndroidUser.lResultCode=m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_LoadAndroidUser"),true);

		//��ȡ��Ϣ
		for (WORD i=0;i<CountArray(AndroidUser.dwAndroidID);i++)
		{
			//�����ж�
			if (m_GameScoreDBModule->IsRecordsetEnd()==true) break;

			//��ȡ����
			DWORD dwAndroidID=0L;
			dwAndroidID=m_GameScoreDBAide.GetValue_DWORD(TEXT("UserID"));
			AndroidUser.dwAndroidID[AndroidUser.wAndroidCount++]=dwAndroidID;

			//�ƶ���¼
			m_GameScoreDBModule->MoveToNext();
		}

		//������Ϣ
		WORD wHeadSize=sizeof(AndroidUser)-sizeof(AndroidUser.dwAndroidID);
		WORD wPacketSize=wHeadSize+AndroidUser.wAndroidCount*sizeof(AndroidUser.dwAndroidID[0]);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_ANDROID_USER,dwContextID,&AndroidUser,wPacketSize);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);

		//��������
		DBO_GR_AndroidUser AndroidUser;
		ZeroMemory(&AndroidUser,sizeof(AndroidUser));

		//�������
		AndroidUser.lResultCode=-1;
		AndroidUser.wAndroidCount=0L;

		//������Ϣ
		WORD wPacketSize=sizeof(AndroidUser)-sizeof(AndroidUser.dwAndroidID);
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_ANDROID_USER,dwContextID,&AndroidUser,wPacketSize);
	}

	return false;
}

//�����ʻ�
bool CDataBaseSink::OnRequestSendGift(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_SendGift));
	if (wDataSize!=sizeof(DBR_GR_SendGift)) return false;

	//����ת��
	DBR_GR_SendGift * pSendGift=(DBR_GR_SendGift *)pData;

	try
	{
		//��¼����
		LONG lRet = SPRecordGiftGrant(pSendGift->dwSendUserID, pSendGift->dwRcvUserID, pSendGift->wGiftID, pSendGift->dwClientIP,
			pSendGift->lSendUserCharm, pSendGift->lRcvUserCharm, pSendGift->lFlowerPrice, pSendGift->wFlowerCount);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//������Ϣ
bool CDataBaseSink::OnRequestProperty(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//����ת��
	DBR_GR_Property * pProperty=(DBR_GR_Property *)pData;

	try
	{
		//��¼����
		SPBuyProperty(pProperty->dwUserID, pProperty->dwTargetUserID, pProperty->nPropertyID, pProperty->dwCurCount, 
			pProperty->dwOnceCount, pProperty->dwPachurseCount, pProperty->lPrice, pProperty->dwClientIP);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//д�����
bool CDataBaseSink::OnWriteProperty(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_WriteProperty));
	if (wDataSize!=sizeof(DBR_GR_WriteProperty)) return false;

	//����ת��
	DBR_GR_WriteProperty * pWriteProperty=(DBR_GR_WriteProperty *)pData;

	try
	{
		//д�����
		SPWriteProperty(pWriteProperty->dwUserID, pWriteProperty->nPropertyID, pWriteProperty->lUseableTime, pWriteProperty->dwClientIP);

		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//���ص���
bool CDataBaseSink::OnLoadProperty(DWORD dwContextID, VOID * pData, WORD wDataSize)
{	
	try
	{
		LONG lReturn = -1;

		//���ص���
		lReturn = SPLoadPropertyAttribute();
		if ( lReturn > 0 )
		{
			DBR_GR_PropertyAttribute PropertyAttribute;
			ZeroMemory(&PropertyAttribute, sizeof(PropertyAttribute));

			//��ȡ��¼
			m_GameScoreDBModule->MoveToFirst();
			while ( m_GameScoreDBModule->IsRecordsetEnd() == false )
			{
				PropertyAttribute.wPropertyID=m_GameScoreDBAide.GetValue_WORD(TEXT("CateID"));
				PropertyAttribute.dwPropCount1=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount1"));
				PropertyAttribute.dwPropCount2=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount2"));
				PropertyAttribute.dwPropCount3=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount3"));
				PropertyAttribute.dwPropCount4=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount4"));
				PropertyAttribute.dwPropCount5=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount5"));
				PropertyAttribute.dwPropCount6=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount6"));
				PropertyAttribute.dwPropCount7=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount7"));
				PropertyAttribute.dwPropCount8=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount8"));
				PropertyAttribute.dwPropCount9=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount9"));
				PropertyAttribute.dwPropCount10=m_GameScoreDBAide.GetValue_DWORD(TEXT("PropCount10"));

				PropertyAttribute.lPrice1=m_GameScoreDBAide.GetValue_LONG(TEXT("Price1"));
				PropertyAttribute.lPrice2=m_GameScoreDBAide.GetValue_LONG(TEXT("Price2"));
				PropertyAttribute.lPrice3=m_GameScoreDBAide.GetValue_LONG(TEXT("Price3"));
				PropertyAttribute.lPrice4=m_GameScoreDBAide.GetValue_LONG(TEXT("Price4"));
				PropertyAttribute.lPrice5=m_GameScoreDBAide.GetValue_LONG(TEXT("Price5"));
				PropertyAttribute.lPrice6=m_GameScoreDBAide.GetValue_LONG(TEXT("Price6"));
				PropertyAttribute.lPrice7=m_GameScoreDBAide.GetValue_LONG(TEXT("Price7"));
				PropertyAttribute.lPrice8=m_GameScoreDBAide.GetValue_LONG(TEXT("Price8"));
				PropertyAttribute.lPrice9=m_GameScoreDBAide.GetValue_LONG(TEXT("Price9"));
				PropertyAttribute.lPrice10=m_GameScoreDBAide.GetValue_LONG(TEXT("Price10"));

				PropertyAttribute.cbDiscount=m_GameScoreDBAide.GetValue_BYTE(TEXT("Discount"));

				//Ͷ�ݵ���֪ͨ
				m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_PROPERTY_ATTRIBUTE,dwContextID,&PropertyAttribute, sizeof(PropertyAttribute));

				//�ƶ���¼
				m_GameScoreDBModule->MoveToNext();
			}
		}

		//�����ʻ�
		lReturn = SPLoadFlowerAttribute();
		if ( lReturn > 0 )
		{
			//��������
			DBR_GR_FlowerAttribute FlowerAttribute;
			ZeroMemory(&FlowerAttribute, sizeof(FlowerAttribute));

			//��ȡ��¼
			m_GameScoreDBModule->MoveToFirst();
			while ( m_GameScoreDBModule->IsRecordsetEnd() == false )
			{
				FlowerAttribute.nFlowerID=m_GameScoreDBAide.GetValue_INT(TEXT("ID"));
				FlowerAttribute.lSendUserCharm=m_GameScoreDBAide.GetValue_LONG(TEXT("SendUserCharm"));
				FlowerAttribute.lRcvUserCharm=m_GameScoreDBAide.GetValue_LONG(TEXT("RcvUserCharm"));
				FlowerAttribute.lPrice=m_GameScoreDBAide.GetValue_LONG(TEXT("Price"));
				FlowerAttribute.cbDiscount=m_GameScoreDBAide.GetValue_BYTE(TEXT("Discount"));

				//Ͷ�ݵ���֪ͨ
				m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_FLOWER_ATTRIBUTE,dwContextID,&FlowerAttribute, sizeof(FlowerAttribute));

				//�ƶ���¼
				m_GameScoreDBModule->MoveToNext();
			}
		}

	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//�����һ�
bool CDataBaseSink::OnExchangeCharm(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_ExchangeLoveliness));
	if (wDataSize!=sizeof(DBR_GR_ExchangeLoveliness)) return false;

	//����ת��
	DBR_GR_ExchangeLoveliness * pExchangeLoveliness=(DBR_GR_ExchangeLoveliness *)pData;

	LONG lReturnValue = -1;
	try
	{
		//�����һ�
		lReturnValue = SPExchangeCharm(pExchangeLoveliness->dwUserID, pExchangeLoveliness->lLoveliness, 
			pExchangeLoveliness->lGoldValue, pExchangeLoveliness->dwClientIP);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	////�������
	//DBR_GR_ExchangeCharmResult ExchangeCharmResult;
	//ZeroMemory(&ExchangeCharmResult, sizeof(ExchangeCharmResult));
	//ExchangeCharmResult.cbResultCode = BYTE(lReturnValue);
	//ExchangeCharmResult.dwUserID = pExchangeLoveliness->dwUserID;
	//ExchangeCharmResult.lLoveliness = pExchangeLoveliness->lLoveliness;
	//ExchangeCharmResult.lGoldValue = pExchangeLoveliness->lGoldValue;

	////Ͷ�ݵ���֪ͨ
	//m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_EXCHANGE_RESULT,dwContextID, &ExchangeCharmResult, sizeof(ExchangeCharmResult));

	return true;
}

//��ȡ���
bool CDataBaseSink::OnBankDrawoutGold(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_BankDrawoutGold));
	if (wDataSize!=sizeof(DBR_GR_BankDrawoutGold)) return false;

	//����ת��
	DBR_GR_BankDrawoutGold * pBankGet=(DBR_GR_BankDrawoutGold *)pData;

	LONG lReturnValue = -1;
	try
	{
		//��ȡ���
		lReturnValue = SPBankDrawoutGold(pBankGet->dwUserID,pBankGet->DrawoutGoldCount,pBankGet->dwClientIP);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//�洢���
bool CDataBaseSink::OnBankStorageGold(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==sizeof(DBR_GR_BankStorage));
	if (wDataSize!=sizeof(DBR_GR_BankStorage)) return false;

	//����ת��
	DBR_GR_BankStorage * pBankStorage=(DBR_GR_BankStorage *)pData;

	LONG lReturnValue = -1;
	try
	{
		//��ȡ���
		lReturnValue = SPBankStorageGold(pBankStorage->dwUserID,pBankStorage->lStorageCount,pBankStorage->dwClientIP);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}

	return true;
}

//I D �洢����
LONG CDataBaseSink::SPLogonByUserID(DWORD dwUserID, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID)
{
	LONG lReturnValue=-1;
	try
	{
		//Ч�����
		ASSERT(dwUserID!=0L);
		ASSERT(pszPassword!=NULL);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@strPassword"),pszPassword);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);
		m_GameScoreDBAide.AddParameter(TEXT("@strMachineSerial"),pszComputerID);
		m_GameScoreDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_EfficacyUserID"),true);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//д�ִ洢����
LONG CDataBaseSink::SPWriteUserScore(DWORD dwUserID, DWORD dwPlayTimeCount, 
									 DWORD dwOnLineTimeCount, DWORD dwClientIP, 
									 __int64 lRevenue, tagUserScore & UserScore)
{
	LONG lReturnValue=-1;
	try
	{
		//Ч�����
		ASSERT(dwUserID!=0L);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@lScore"),UserScore.lScore);
		m_GameScoreDBAide.AddParameter(TEXT("@lRevenue"),lRevenue);
		m_GameScoreDBAide.AddParameter(TEXT("@lWinCount"),UserScore.lWinCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lLostCount"),UserScore.lLostCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lDrawCount"),UserScore.lDrawCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lFleeCount"),UserScore.lFleeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lExperience"),UserScore.lExperience);
		m_GameScoreDBAide.AddParameter(TEXT("@dwPlayTimeCount"),dwPlayTimeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@dwOnLineTimeCount"),dwOnLineTimeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue =m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_WriteGameScore"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//�뿪�洢����
LONG CDataBaseSink::SPLeaveGameServer(DWORD dwUserID, DWORD dwPlayTimeCount,
									  DWORD dwOnLineTimeCount, DWORD dwClientIP,
									  __int64 lRevenue, LONG lLoveliness,
									  tagUserScore & UserScore)
{
	LONG lReturnValue=-1;
	try
	{

		//Ч�����
		ASSERT(dwUserID!=0L);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@lScore"),UserScore.lScore);
		m_GameScoreDBAide.AddParameter(TEXT("@lGameGold"),UserScore.lGameGold);
		m_GameScoreDBAide.AddParameter(TEXT("@lInsureScore"),UserScore.lInsureScore);
		m_GameScoreDBAide.AddParameter(TEXT("@lLoveliness"),lLoveliness);
		m_GameScoreDBAide.AddParameter(TEXT("@lRevenue"),lRevenue);
		m_GameScoreDBAide.AddParameter(TEXT("@lWinCount"),UserScore.lWinCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lLostCount"),UserScore.lLostCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lDrawCount"),UserScore.lDrawCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lFleeCount"),UserScore.lFleeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@lExperience"),UserScore.lExperience);
		m_GameScoreDBAide.AddParameter(TEXT("@dwPlayTimeCount"),dwPlayTimeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@dwOnLineTimeCount"),dwOnLineTimeCount);
		m_GameScoreDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_LeaveGameServer"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//���Ŵ洢����
LONG CDataBaseSink::SPCongealAccounts(DWORD dwUserID, DWORD dwMasterUserID, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		//Ч�����
		ASSERT(dwUserID!=0L);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_AccountsDBAide.ResetParameter();
		m_AccountsDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_AccountsDBAide.AddParameter(TEXT("@dwMasterUserID"),dwMasterUserID);
		m_AccountsDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_AccountsDBAide.ExecuteProcess(TEXT("GSP_GR_CongealAccounts"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//Ȩ�޴洢����
LONG CDataBaseSink::SPSetUserGameRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		//Ч�����
		ASSERT(dwUserID!=0L);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserRight"),dwUserRight);
		m_GameScoreDBAide.AddParameter(TEXT("@dwMasterUserID"),dwMasterUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_SetUserRight"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//Ȩ�޴洢����
LONG CDataBaseSink::SPSetUserAccountsRight(DWORD dwUserID, DWORD dwUserRight, DWORD dwMasterUserID, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{

		//Ч�����
		ASSERT(dwUserID!=0L);

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_AccountsDBAide.ResetParameter();
		m_AccountsDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_AccountsDBAide.AddParameter(TEXT("@dwUserRight"),dwUserRight);
		m_AccountsDBAide.AddParameter(TEXT("@dwMasterUserID"),dwMasterUserID);
		m_AccountsDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_AccountsDBAide.ExecuteProcess(TEXT("GSP_GR_SetUserRight"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//��¼����
LONG CDataBaseSink::SPRecordGiftGrant(DWORD dwSendUserID, DWORD dwRcvUserID, WORD wGiftID, DWORD dwClientIP, 
									  DWORD dwSendUserLoveliness, DWORD dwRcvUserLoveliness, LONG lValue, int nFlowerCount)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwSendUserID != 0 && dwRcvUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwSendUserID"),dwSendUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwRcvUserID"),dwRcvUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwSendUserLoveliness"),dwSendUserLoveliness);
		m_GameScoreDBAide.AddParameter(TEXT("@dwRcvUserLoveliness"),dwRcvUserLoveliness);
		m_GameScoreDBAide.AddParameter(TEXT("@dwFlowerCount"),(DWORD)nFlowerCount);
		m_GameScoreDBAide.AddParameter(TEXT("@strFlowerName"),g_FlowerDescribe[wGiftID].szName);
		m_GameScoreDBAide.AddParameter(TEXT("@lFlowerPay"),lValue);
		m_GameScoreDBAide.AddParameter(TEXT("@wKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_RecordFlowerGrant"),true);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//�������
LONG CDataBaseSink::SPBuyProperty(DWORD dwUserID, DWORD dwTargetUserID, int nPropertyID, DWORD dwCurCount, DWORD dwOnceCount, 
								  DWORD dwPachurCount, LONG lPrice, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwRcvUserID"),dwTargetUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),(DWORD)m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwCateID"),(DWORD)nPropertyID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwCurCount"),dwCurCount);	
		m_GameScoreDBAide.AddParameter(TEXT("@dwOnceCount"),dwOnceCount);	
		m_GameScoreDBAide.AddParameter(TEXT("@dwPachurseCount"),dwPachurCount);
		m_GameScoreDBAide.AddParameter(TEXT("@bwSpendScore"),lPrice);	
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_PurchaseProp"),true);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//д�����
LONG CDataBaseSink::SPWriteProperty(DWORD dwUserID, int nPropertyID, DWORD lUseableTime, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);

		//�����ж�
		if ( nPropertyID == PROP_BUGLE )
			m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),0);
		else
			m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),m_pGameServiceAttrib->wKindID);

		m_GameScoreDBAide.AddParameter(TEXT("@dwCateID"),nPropertyID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwPropCount"),lUseableTime);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_WriteUserProp"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//���ص���
LONG CDataBaseSink::SPLoadPropertyAttribute()
{
	LONG lReturnValue=-1;
	try
	{
		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_LoadGameShopCate"),true);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//�����ʻ�
LONG CDataBaseSink::SPLoadFlowerAttribute()
{
	LONG lReturnValue=-1;
	try
	{
		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_LoadFlowerCate"),true);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//���ص���
LONG CDataBaseSink::SPLoadUserProperty(DWORD dwUserID)
{
	LONG lReturnValue=-1;
	try
	{
		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),m_pGameServiceAttrib->wKindID);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_LoadUserProp"),true);

	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}
//�����һ�
LONG CDataBaseSink::SPExchangeCharm(DWORD dwUserID, LONG lLoveliness, LONG lGoldValue, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@lLoveliness"),lLoveliness);
		m_GameScoreDBAide.AddParameter(TEXT("@lInsureScore"),lGoldValue);
		m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@wServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);
	    lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_ExchangeLoveliness"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}

//��ȡ�洢����
LONG CDataBaseSink::SPBankDrawoutGold(DWORD dwUserID, DWORD lSwapScore, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@lSwapScore"),lSwapScore);
		m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_DrawoutGameGold"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}


//���洢����
LONG CDataBaseSink::SPBankStorageGold(DWORD dwUserID, DWORD lSwapScore, DWORD dwClientIP)
{
	LONG lReturnValue=-1;
	try
	{
		ASSERT( dwUserID != 0 );

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@lSwapScore"),lSwapScore);
		m_GameScoreDBAide.AddParameter(TEXT("@dwKindID"),m_pGameServiceAttrib->wKindID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.AddParameter(TEXT("@strClientIP"),szClientIP);

		lReturnValue= m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_SavingGameGold"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return lReturnValue;
}


//�������������û�
bool CDataBaseSink::OnClearScoreLocker(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(wDataSize==0);
	if (wDataSize!=0)
		return false;
	try
	{
		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwServerID"),m_pGameServiceOption->wServerID);
		m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_ClearScoreLocker"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//ÿ�ּ�¼�洢
bool CDataBaseSink::OnRequestRoundScore(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		ASSERT(wDataSize==sizeof(DBR_GR_User_Round_Score));
		if (wDataSize!=sizeof(DBR_GR_User_Round_Score)) return false;
		DBR_GR_User_Round_Score* pRoundScore=(DBR_GR_User_Round_Score*)pData;
		//ִ�д洢����
		m_GameScoreDBAide.ResetParameter();
		m_GameScoreDBAide.AddParameter(TEXT("@dwUserID"),pRoundScore->dwUserID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwGameID"),pRoundScore->wGameID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwTableID"),pRoundScore->wTableID);
		m_GameScoreDBAide.AddParameter(TEXT("@dwGameRound"),pRoundScore->dwGameRound);
		m_GameScoreDBAide.AddParameter(TEXT("@lScore"),pRoundScore->sfScore);
		m_GameScoreDBAide.AddParameter(TEXT("@lRevenue"),pRoundScore->sfRevenue);
		m_GameScoreDBAide.AddParameter(TEXT("@szQuitType"),pRoundScore->szQuitType);
		m_GameScoreDBAide.AddParameter(TEXT("@szJetton"),pRoundScore->szJetton);
		m_GameScoreDBAide.ExecuteProcess(TEXT("GSP_GR_Round_Score"),false);
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;

}
//ת��
bool CDataBaseSink::OnRequestTransferMoney(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		ASSERT(wDataSize==sizeof(DBR_GR_TransferMoney));
		if (wDataSize!=sizeof(DBR_GR_TransferMoney)) return false;

		//ִ�в�ѯ
		DBR_GR_TransferMoney * pTransferMoney=(DBR_GR_TransferMoney *)pData;

		//ת����ַ
		TCHAR szClientIP[16]=TEXT("");
		BYTE * pClientIP=(BYTE *)&pTransferMoney->dwClientIP;
		_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		//ִ�в�ѯ
		m_GameScoreDBModule->ClearParameters();
		m_GameScoreDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_GameScoreDBModule->AddParameter(TEXT("@dwUserID_Out"),adInteger,adParamInput,sizeof(long),_variant_t((long)pTransferMoney->dwUserID));
		m_GameScoreDBModule->AddParameter(TEXT("@dwGameID_In"),adInteger,adParamInput,sizeof(long),_variant_t((long)pTransferMoney->dwGameID_IN));
		m_GameScoreDBModule->AddParameter(TEXT("@Account_Out"),adVarChar, adParamInput,lstrlen(pTransferMoney->szAccount_Out),_variant_t(pTransferMoney->szAccount_Out));
		m_GameScoreDBModule->AddParameter(TEXT("@Account_In"),adVarChar,adParamInput, lstrlen(pTransferMoney->szAccount_In),_variant_t(pTransferMoney->szAccount_In));
		m_GameScoreDBModule->AddParameter(TEXT("@MoneyNumber"),adBigInt,adParamInput,sizeof(__int64),_variant_t(pTransferMoney->sfMoneyNumber));
		m_GameScoreDBModule->AddParameter(TEXT("@Tax"),adBigInt,adParamInput,sizeof(__int64),_variant_t(pTransferMoney->sfTax));
		m_GameScoreDBModule->AddParameter(TEXT("@strClientIP"),adVarChar,adParamInput,lstrlen(szClientIP),_variant_t(szClientIP));
		m_GameScoreDBModule->ExecuteProcess("GSP_GR_TransferMoney",true);

		//����ж�
		LONG lReturnCode=m_GameScoreDBModule->GetReturnValue();
		pTransferMoney->lErrorCode=lReturnCode;
		if ( lReturnCode!=0L )
		{
			TCHAR szErrorDescribe[256]=TEXT("");
			m_GameScoreDBModule->GetFieldValue(TEXT("ErrorDescribe"), szErrorDescribe, sizeof(szErrorDescribe));
			CTraceService::TraceString(szErrorDescribe,TraceLevel_Exception);
			lstrcpyn(pTransferMoney->szErrorDescribe, szErrorDescribe, CountArray(pTransferMoney->szErrorDescribe));
		}
		else
		{
			m_GameScoreDBModule->GetFieldValue(TEXT("MoneyNumber"), pTransferMoney->sfMoneyNumber);
			m_GameScoreDBModule->GetFieldValue(TEXT("Score_Out"), pTransferMoney->sfLeftMoney);
		}

		//������Ϣ
		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_TRANSFER_MONEY_OUT,dwContextID,
			pTransferMoney,sizeof( DBR_GR_TransferMoney ));
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//��ѯת�˼�¼
bool CDataBaseSink::OnRequestQueryTransferLog(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_Query_Transfer_Log));
		if (wDataSize!=sizeof(DBR_GR_Query_Transfer_Log)) return false;

		//ִ�в�ѯ
		DBR_GR_Query_Transfer_Log * dbr=(DBR_GR_Query_Transfer_Log *)pData;

		//ִ�в�ѯ
		m_GameScoreDBModule->ClearParameters();
		m_GameScoreDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_GameScoreDBModule->AddParameter(TEXT("@dwUserID"),adInteger,adParamInput,sizeof(long),_variant_t((long)dbr->dwUserID));
		m_GameScoreDBModule->ExecuteProcess("GSP_GR_Query_Transfer",true);

		while ( m_GameScoreDBModule->IsRecordsetEnd()==false)
		{
			CMD_GF_Transfer_Log_Item cmd;
			ZeroMemory(&cmd, sizeof(CMD_GF_Transfer_Log_Item));
			COleDateTime  temp;
			memset(&cmd, 0, sizeof(CMD_GF_Transfer_Log_Item));
			m_GameScoreDBModule->GetFieldValue(TEXT("Account_Out"),cmd.szOutAccount,sizeof(cmd.szOutAccount));
			m_GameScoreDBModule->GetFieldValue(TEXT("Account_In"),cmd.szInAccount,sizeof(cmd.szInAccount));
			m_GameScoreDBModule->GetFieldValue(TEXT("MoneyNumber"),cmd.sfMoney);
			m_GameScoreDBModule->GetFieldValue(TEXT("Tax"),cmd.sfTax);
			m_GameScoreDBModule->GetFieldValue(TEXT("CreateDate"), temp);
			m_GameScoreDBModule->GetFieldValue(TEXT("ClientIP"), cmd.szIP, sizeof(cmd.szIP));

			temp.GetAsSystemTime(cmd.TransTime);
			cmd.wTableID=dbr->wTableID;
			cmd.dwUserID=dbr->dwUserID;

			m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_QUERY_TRANSFER_ITEM,
				dwContextID, &cmd, sizeof(CMD_GF_Transfer_Log_Item));

			m_GameScoreDBModule->MoveToNext();
		}

		CMD_GF_Transfer_Log_Out LogOut;
		ZeroMemory(&LogOut, sizeof(CMD_GF_Transfer_Log_Out));
		LogOut.dwUserID=dbr->dwUserID;
		LogOut.wTableID=dbr->wTableID;

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_QUERY_TRANSFER_LOG_OUT,
			dwContextID, &LogOut, sizeof(CMD_GF_Transfer_Log_Out));
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//�޸ĵ�¼����
bool CDataBaseSink::OnRequestModifyLoginPassword(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_ModifyLoginPassword));
		if (wDataSize!=sizeof(DBR_GR_ModifyLoginPassword)) return false;

		//ִ�в�ѯ
		DBR_GR_ModifyLoginPassword * pDBR=(DBR_GR_ModifyLoginPassword *)pData;

		//ִ�в�ѯ
		m_AccountsDBModule->ClearParameters();
		m_AccountsDBModule->AddParameter(TEXT("RETURN_VALUE"), adInteger,adParamReturnValue,  sizeof(long), _variant_t((long)0) );
		m_AccountsDBModule->AddParameter(TEXT("@dwUserID"), adInteger,adParamInput,  sizeof(long), _variant_t((long)pDBR->dwUserID) );
		m_AccountsDBModule->AddParameter(TEXT("@OLDPassword"),  adChar,adParamInput, PASS_LEN, _variant_t(pDBR->szOLDPassword) );
		m_AccountsDBModule->AddParameter(TEXT("@NEWPassword"), adChar, adParamInput, PASS_LEN, _variant_t(pDBR->szNEWPassword) );
		m_AccountsDBModule->ExecuteProcess("GSP_GP_Modify_PassWord",true);

		//����ж�
		LONG lReturnCode=m_AccountsDBModule->GetReturnValue();
		if ( lReturnCode!=0L )
		{
			TCHAR szErrorDescribe[256]=TEXT("");
			m_AccountsDBModule->GetFieldValue(TEXT("ErrorDescribe"), szErrorDescribe, sizeof(szErrorDescribe));
			CTraceService::TraceString(szErrorDescribe,TraceLevel_Exception);
			lstrcpyn(pDBR->szErrorDescribe, szErrorDescribe, CountArray(pDBR->szErrorDescribe));
		}

		pDBR->lErrorCode=lReturnCode;

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_MODIFY_LOGIN_PASSWORD_OUT, 
			dwContextID, pDBR, sizeof(DBR_GR_ModifyLoginPassword));
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//�޸���������
bool CDataBaseSink::OnRequestModifyBankPassword(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_ModifyBankPassword));
		if (wDataSize!=sizeof(DBR_GR_ModifyBankPassword)) return false;

		//ִ�в�ѯ
		DBR_GR_ModifyBankPassword * pDBR=(DBR_GR_ModifyBankPassword *)pData;

		//ִ�в�ѯ
		m_AccountsDBModule->ClearParameters();
		m_AccountsDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_AccountsDBModule->AddParameter(TEXT("@dwUserID"),adInteger,adParamInput,sizeof(long),_variant_t((long)pDBR->dwUserID));
		m_AccountsDBModule->AddParameter(TEXT("@OLDPassword"),  adChar, adParamInput,PASS_LEN, _variant_t(pDBR->szOLDPassword));
		m_AccountsDBModule->AddParameter(TEXT("@NEWPassword"),  adChar, adParamInput,PASS_LEN, _variant_t(pDBR->szNEWPassword));
		m_AccountsDBModule->ExecuteProcess("GSP_GP_Modify_Bank_PassWord",true);

		//����ж�
		LONG lReturnCode=m_AccountsDBModule->GetReturnValue();
		if ( lReturnCode!=0L )
		{
			TCHAR szErrorDescribe[256]=TEXT("");
			m_AccountsDBModule->GetFieldValue(TEXT("ErrorDescribe"), szErrorDescribe, sizeof(szErrorDescribe));
			CTraceService::TraceString(szErrorDescribe,TraceLevel_Exception);
			lstrcpyn(pDBR->szErrorDescribe, szErrorDescribe, CountArray(pDBR->szErrorDescribe));
		}

		pDBR->lErrorCode=lReturnCode;

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_MODIFY_BANK_PASSWORD_OUT, 
			dwContextID, pDBR, sizeof(DBR_GR_ModifyBankPassword));
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//�޸��ǳ�
bool CDataBaseSink::OnRequestModifyNickname(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_Modify_Nickname));
		if (wDataSize!=sizeof(DBR_GR_Modify_Nickname)) return false;

		//ִ�в�ѯ
		DBR_GR_Modify_Nickname * pDBR=(DBR_GR_Modify_Nickname *)pData;

		//ִ�в�ѯ
		m_AccountsDBModule->ClearParameters();
		m_AccountsDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_AccountsDBModule->AddParameter(TEXT("@dwUserID"),adInteger,adParamInput,sizeof(long),_variant_t((long)pDBR->dwUserID));
		m_AccountsDBModule->AddParameter(TEXT("@NickName"),  adVarChar, adParamInput,lstrlen(pDBR->szNickname), _variant_t(pDBR->szNickname));
		m_AccountsDBModule->ExecuteProcess("GSP_GP_Modify_Nickname",true);

		//����ж�
		LONG lReturnCode=m_AccountsDBModule->GetReturnValue();
		if ( lReturnCode!=0L )
		{
			TCHAR szErrorDescribe[256]=TEXT("");
			m_AccountsDBModule->GetFieldValue(TEXT("ErrorDescribe"), szErrorDescribe, sizeof(szErrorDescribe));
			CTraceService::TraceString(szErrorDescribe,TraceLevel_Exception);
			lstrcpyn(pDBR->szErrorDescribe, szErrorDescribe, CountArray(pDBR->szErrorDescribe));
		}

		pDBR->lErrorCode=lReturnCode;

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_MODIFY_NICKNAME_OUT,
			dwContextID, pDBR, sizeof(DBR_GR_Modify_Nickname));
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//���в���
bool CDataBaseSink::OnRequestBankTask(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_BankTask));
		if (wDataSize!=sizeof(DBR_GR_BankTask)) return false;
		//ִ�в�ѯ
		DBR_GR_BankTask * pBankTask=(DBR_GR_BankTask *)pData;

		//ִ�д洢����
		m_GameScoreDBModule->ClearParameters();
		m_GameScoreDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_GameScoreDBModule->AddParameter(TEXT("@dwUserID"),adInteger,adParamInput,sizeof(long),_variant_t((long)pBankTask->dwUserID));
		m_GameScoreDBModule->AddParameter(TEXT("@Password"), adChar, adParamInput,PASS_LEN, _variant_t(pBankTask->szPassword));
		m_GameScoreDBModule->AddParameter(TEXT("@BankTask"),adInteger,adParamInput,sizeof(long),_variant_t((long)pBankTask->lBankTask));
		m_GameScoreDBModule->AddParameter(TEXT("@MoneyNumber"),adBigInt,adParamInput,sizeof(__int64),_variant_t(pBankTask->lMoneyNumber));
		m_GameScoreDBModule->ExecuteProcess("GSP_GR_Bank",true);

		LONG lReturn=m_GameScoreDBModule->GetReturnValue();
		pBankTask->lErrorCode=lReturn;
		if ( lReturn==0 )
		{
			m_GameScoreDBModule->GetFieldValue(TEXT("MoneyNumber"), pBankTask->lMoneyNumber);
			m_GameScoreDBModule->GetFieldValue(TEXT("NewScore"), pBankTask->lNewScore);
			m_GameScoreDBModule->GetFieldValue(TEXT("MoneyInBank"), pBankTask->lMoneyInBank);
		}
		else
		{
			m_GameScoreDBModule->GetFieldValue(TEXT("ErrorDescribe"), pBankTask->szErrorDescribe, sizeof(pBankTask->szErrorDescribe) );
		}

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_BANK_TASK_OUT,
			dwContextID , pBankTask, sizeof(DBR_GR_BankTask));
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}

//��ѯ�û���
bool CDataBaseSink::OnRequsetQueryUserName(DWORD dwContextID, VOID * pData, WORD wDataSize)
{
	try
	{
		//Ч�����
		ASSERT(wDataSize==sizeof(DBR_GR_Query_UserName));
		if (wDataSize!=sizeof(DBR_GR_Query_UserName)) return false;
		//ִ�в�ѯ
		DBR_GR_Query_UserName * QuserName=(DBR_GR_Query_UserName *)pData;

		//ִ�д洢����
		m_AccountsDBModule->ClearParameters();
		m_AccountsDBModule->AddParameter(TEXT("RETURN_VALUE"),adInteger,adParamReturnValue,sizeof(long),_variant_t((long)0));
		m_AccountsDBModule->AddParameter(TEXT("@dwGameID"),adInteger,adParamInput,sizeof(long),_variant_t((long)QuserName->lGameID));
		m_AccountsDBModule->ExecuteProcess("GSP_GP_QueryUserName",true);
		LONG lReturn=m_AccountsDBModule->GetReturnValue();
		QuserName->lErrorCode=lReturn;
		if ( lReturn==0 )
		{
			m_AccountsDBModule->GetFieldValue(TEXT("UserName"), QuserName->szUserName,sizeof(QuserName->szUserName));
		}
		else
		{
			m_AccountsDBModule->GetFieldValue(TEXT("@ErrorDescribe"), QuserName->szErrorDescribe, sizeof(QuserName->szErrorDescribe) );
		}

		m_pIDataBaseEngineEvent->OnEventDataBaseResult(DBR_GR_QUERYUSERNAME_OUT,
			dwContextID , QuserName, sizeof(DBR_GR_Query_UserName));
		return true;
	}
	catch (IDataBaseException * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		CTraceService::TraceString(pszDescribe,TraceLevel_Exception);
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
