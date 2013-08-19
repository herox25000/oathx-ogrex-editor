#include "StdAfx.h"
#include "platformsocket.h"

CPlatformSocket::CPlatformSocket(void)
{
	m_bLogonPlaza = false;
}

CPlatformSocket::~CPlatformSocket(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CPlatformSocket::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}
//�����¼�
bool __cdecl CPlatformSocket::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if (nErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
		ShowMessageBox(TEXT("��¼����������ʧ�ܣ����Ժ����Ի�������վ���棡"),MB_ICONINFORMATION);
		if(m_pPlatformFrame != NULL)
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
		return true;
	}

	//���͵�¼��
	if (m_bLogonPlaza==false)
	{
		if(m_pDlgLogon != NULL)
			m_pDlgLogon->SendLogonPacket(m_ClientSocket.GetInterface());
		g_GlobalAttemper.ShowStatusMessage(TEXT("������֤�û���¼��Ϣ..."),m_pPlatformFrame);
	}
	return true;
}
//�ر��¼�
bool __cdecl CPlatformSocket::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if (m_bLogonPlaza==false)
	{
		if (cbShutReason!=SHUT_REASON_NORMAL)
		{
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
			ShowMessageBox(TEXT("��¼����������ʧ�ܣ����Ժ����Ի�������վ���棡"),MB_ICONINFORMATION);
			if(m_pPlatformFrame != NULL)
				m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
		}
	}

	return true;
}
//��ȡ�¼�
bool __cdecl CPlatformSocket::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GP_LOGON:				//��¼��Ϣ
		{
			return OnSocketMainLogon(Command,pData,wDataSize);
		}
	case MDM_GP_SERVER_LIST:		//�б���Ϣ
		{
			return OnSocketMainServerList(Command,pData,wDataSize);
		}
	case MDM_GP_SYSTEM:				//ϵͳ��Ϣ
		{
			return OnSocketMainSystem(Command,pData,wDataSize);
		}
	case MDM_GP_USER:				//�û���Ϣ
		{
			return OnSocketMainUser(Command,pData,wDataSize);
		}
	}
	return true;
}


//���ӵ�������
void CPlatformSocket::ConnectToServer(LPCTSTR ServerIP,WORD wPort)
{
	//�������
	if (m_ClientSocket.GetInterface()==NULL)
	{
		try
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_ClientSocket.CreateInstance()==false) 
			{
				throw TEXT("�����������ʧ��");
			}
			if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("��������ص��ӿ�����ʧ��");
			}
		}
		catch (...)
		{
			ShowMessageBox(TEXT("�����������ʧ�ܣ�������������Ϸ������"),MB_ICONSTOP);
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA);
			return;
		}
	}

	//���ӷ�����
	try
	{
		//���ӷ�����
		m_ClientSocket->CloseSocket();
		if (m_ClientSocket->Connect(ServerIP,wPort )!=CONNECT_SUCCESS)
		{
			throw TEXT("���������Ӵ��󣬿��������ϵͳ��û�гɹ����������磡");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessageBox(pszError,MB_ICONINFORMATION);
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA);
		return;
	}

	//��ʾ��ʾ��
	CString strMessage=TEXT("�������ӷ����������Ժ�...");
	g_GlobalAttemper.ShowStatusMessage(strMessage,m_pPlatformFrame);
}

//������Ϣ
void CPlatformSocket::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}


//��¼��Ϣ
bool CPlatformSocket::OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GP_LOGON_SUCCESS:		//��¼�ɹ�
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_LogonSuccess));
			if (wDataSize<sizeof(CMD_GP_LogonSuccess)) return false;

			//������Ϣ
			tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
			CMD_GP_LogonSuccess * pLogonSuccess=(CMD_GP_LogonSuccess *)pData;
			UserData.wFaceID=pLogonSuccess->wFaceID;
			UserData.cbGender=pLogonSuccess->cbGender;
			UserData.cbMember=pLogonSuccess->cbMember;
			UserData.dwUserID=pLogonSuccess->dwUserID;
			UserData.dwGameID=pLogonSuccess->dwGameID;
			UserData.dwExperience=pLogonSuccess->dwExperience;
			UserData.dwCustomFaceVer=pLogonSuccess->dwCustomFaceVer;
			UserData.wLevel = pLogonSuccess->wLevel;
			UserData.lScore = pLogonSuccess->lScore;
			UserData.lBeans = pLogonSuccess->lBeans;
			UserData.lLottery = pLogonSuccess->lLottery;

			//��չ��Ϣ
			void * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonSuccess+1,wDataSize-sizeof(CMD_GP_LogonSuccess));
			while (true)
			{
				pDataBuffer=RecvPacket.GetData(DataDescribe);
				if (DataDescribe.wDataDescribe==DTP_NULL) break;
				switch (DataDescribe.wDataDescribe)
				{
				case DTP_USER_ACCOUNTS:		//�û��ʻ�
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szAccounts));
						if (DataDescribe.wDataSize<=sizeof(UserData.szAccounts))
						{
							CopyMemory(UserData.szAccounts,pDataBuffer,DataDescribe.wDataSize);
							UserData.szAccounts[CountArray(UserData.szAccounts)-1]=0;
						}
						break;
					}
				case DTP_USER_PASS:			//�û�����
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szPassWord));
						if (DataDescribe.wDataSize<=sizeof(UserData.szPassWord))
						{
							CopyMemory(UserData.szPassWord,pDataBuffer,DataDescribe.wDataSize);
							UserData.szPassWord[CountArray(UserData.szPassWord)-1]=0;
						}
						break;
					}
				case DTP_UNDER_WRITE:		//����ǩ��
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite));
						if (DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite))
						{
							CopyMemory(UserData.szUnderWrite,pDataBuffer,DataDescribe.wDataSize);
							UserData.szUnderWrite[CountArray(UserData.szUnderWrite)-1]=0;
						}
						break;
					}
				case DTP_USER_GROUP_NAME:	//��������
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szGroupName));
						if (DataDescribe.wDataSize<=sizeof(UserData.szGroupName))
						{
							CopyMemory(UserData.szGroupName,pDataBuffer,DataDescribe.wDataSize);
							UserData.szGroupName[CountArray(UserData.szGroupName)-1]=0;
						}
						break;
					}
				case DTP_STATION_PAGE:		//��Ϸ��վ
					{
						ASSERT(pDataBuffer!=NULL);
						if (pDataBuffer!=NULL) 
						{
							g_GlobalUnits.SetStationPage((LPCTSTR)pDataBuffer);
						}
						break;
					}
				case DTP_NICK_NAME:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szNickName)) 
						{
							CopyMemory(UserData.szNickName,pDataBuffer, DataDescribe.wDataSize);
							UserData.szNickName[CountArray(UserData.szNickName)-1]=0;
						}
						break;
					}
				case DTP_USER_NAME:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szUserName)) 
						{
							CopyMemory(UserData.szUserName,pDataBuffer, DataDescribe.wDataSize);
							UserData.szUserName[CountArray(UserData.szUserName)-1]=0;
						}
						break;
					}
				case DTP_USER_CEITIFICATE:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szCeitificate)) 
						{
							CopyMemory(UserData.szCeitificate,pDataBuffer, DataDescribe.wDataSize);
							UserData.szCeitificate[CountArray(UserData.szCeitificate)-1]=0;
						}
						break;
					}
				case DTP_USER_ADDRESS:
					{
						if (DataDescribe.wDataSize<=sizeof(UserData.szAddress)) 
						{
							CopyMemory(UserData.szAddress,pDataBuffer, DataDescribe.wDataSize);
							UserData.szAddress[CountArray(UserData.szAddress)-1]=0;
						}
						break;
					}
				default: { ASSERT(FALSE); }
				}
			}

			//������ʾ
			g_GlobalAttemper.ShowStatusMessage(TEXT("���ڶ�ȡ�������б���Ϣ..."),m_pPlatformFrame);

			return true;
		}
	case SUB_GP_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GP_LogonError *pLogonError = (CMD_GP_LogonError *)pData;
			ASSERT(wDataSize>=(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
			m_ClientSocket->CloseSocket();

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}
			//���͵�¼
			m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
			return true;
		}
	case SUB_GP_LOGON_FINISH:		//��¼���
		{
			//�ر���ʾ
			g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);

			////չ������
			//INT_PTR nIndex=0;
			//CListType * pListType=NULL;
			//do
			//{
			//	pListType=g_GlobalUnits.m_ServerListManager.EnumTypeItem(nIndex++);
			//	if (pListType==NULL) break;
			//	g_GlobalUnits.m_ServerListManager.ExpandListItem(pListType);
			//} while (true);

			////չ���б�
			//nIndex=0;
			//CListInside * pListInside=NULL;
			//do
			//{
			//	pListInside=g_GlobalUnits.m_ServerListManager.EnumInsideItem(nIndex++);
			//	if (pListInside==NULL) break;
			//	g_GlobalUnits.m_ServerListManager.ExpandListItem(pListInside);
			//} while (true);
			
			//��ʾ��Ϸ����
			if(g_UIPageManager.m_pGamePage)
			{
				if(g_UIPageManager.m_pGamePage->m_pGameView)
					g_UIPageManager.m_pGamePage->m_pGameView->ShowFirstPage();
			}
			

			m_bLogonPlaza=true;
			//��¼��Ϣ
			g_GlobalUnits.WriteUserCookie();
			if(m_pPlatformFrame != NULL)
			{
				m_pPlatformFrame->ShowWindow(SW_SHOW);
				m_pPlatformFrame->SetActiveWindow();
				m_pPlatformFrame->BringWindowToTop();
				m_pPlatformFrame->SetForegroundWindow();
			}
			if(m_pDlgLogon != NULL)
				m_pDlgLogon->OnLogonSuccess();
			////��ʾͷ��
			//((CGameFrame*)AfxGetMainWnd())->m_UserInfoView.ShowUserInfo(true);

			////�Զ����ж�
			//tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
			//if ( GlobalUserData.dwCustomFaceVer!=0)
			//{
			//	//ͷ������
			//	CString strDirName = CString(g_GlobalUnits.GetWorkDirectory()) + TEXT("\\CustomFace");
			//	CString strFileName;
			//	strFileName.Format(TEXT("\\%ld_%d.bmp"), GlobalUserData.dwUserID, GlobalUserData.dwCustomFaceVer);

			//	//��ȡ�ļ�
			//	CImage FaceImage;
			//	HRESULT hResult = FaceImage.Load(strDirName + strFileName);
			//	if (SUCCEEDED(hResult))
			//	{
			//		//�ر�����
			//		m_ClientSocket->CloseSocket();

			//		FaceImage.Destroy();
			//	}
			//	//����ͷ��
			//	else
			//	{
			//		PostMessage(WM_DOWN_LOAD_FACE, LPARAM(GlobalUserData.dwCustomFaceVer), WPARAM(GlobalUserData.dwUserID));
			//	}
			//}
			//else
			//{
			//	//�ر�����
			//	m_ClientSocket->CloseSocket();
			//}

			return true;
		}
	}

	return true;
}

//��Ϸ�б���Ϣ
bool CPlatformSocket::OnSocketMainServerList(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SERVER_LIST);

	switch (Command.wSubCmdID)
	{
	case SUB_GP_LIST_TYPE:			//������Ϣ
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameType)==0);
			if (wDataSize%sizeof(tagGameType)!=0) return false;

			//������Ϣ
			tagGameType * pGameType=(tagGameType *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameType);
			g_GlobalUnits.m_ServerListManager.InsertTypeItem(pGameType,wItemCount);

			return true;
		}
	case SUB_GP_LIST_KIND:			//������Ϣ
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameKind)==0);
			if (wDataSize%sizeof(tagGameKind)!=0) return false;

			//������Ϣ
			tagGameKind * pGameKind=(tagGameKind *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameKind);
			g_GlobalUnits.m_ServerListManager.InsertKindItem(pGameKind,wItemCount);

			return true;
		}
	case SUB_GP_LIST_STATION:		//վ����Ϣ
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameStation)==0);
			if (wDataSize%sizeof(tagGameStation)!=0) return false;

			//������Ϣ
			tagGameStation * pGameStation=(tagGameStation *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameStation);
			g_GlobalUnits.m_ServerListManager.InsertStationItem(pGameStation,wItemCount);
			return true;
		}
	case SUB_GP_LIST_SERVER:		//����������
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameServer)==0);
			if (wDataSize%sizeof(tagGameServer)!=0) return false;

			//������Ϣ
			tagGameServer * pGameServer=(tagGameServer *)pData;
			WORD wItemCount=wDataSize/sizeof(tagGameServer);
			g_GlobalUnits.m_ServerListManager.InsertServerItem(pGameServer,wItemCount);
			return true;
		}
	case SUB_GP_LIST_FINISH:		//�б������
		{
			//��������
			INT_PTR nIndex=0;
			DWORD dwAllOnLineCount=0L;
			CListKind * pListKind=NULL;
			do
			{
				pListKind=g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex++);
				if (pListKind==NULL) break;
				dwAllOnLineCount+=pListKind->GetItemInfo()->dwOnLineCount;
			} while (true);
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);
			return true;
		}
	case SUB_GP_LIST_CONFIG:		//�б�����
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(CMD_GP_ListConfig)==0);
			if (wDataSize%sizeof(CMD_GP_ListConfig)!=0) return false;

			//������Ϣ
			CMD_GP_ListConfig * pListConfig=(CMD_GP_ListConfig *)pData;
			bool bShowOnLineCount = pListConfig->bShowOnLineCount?true:false;

			return true;
		}
	}

	return true;
}

//ϵͳ��Ϣ
bool CPlatformSocket::OnSocketMainSystem(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GP_VERSION:			//�汾��Ϣ
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_Version));
			if (wDataSize<sizeof(CMD_GP_Version)) return false;

			//��Ϣ����
			CMD_GP_Version * pVersion=(CMD_GP_Version *)pData;
			if (pVersion->bAllowConnect)
			{
				TCHAR szMessage[]=TEXT("��Ϸ�����汾�Ѿ����������ڵİ汾�����Լ���ʹ�ã������Ƿ����������°汾��");
				int iResult=ShowInformationEx(szMessage,0,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1,TEXT("��Ϸ����"));
				if (iResult==IDYES)
				{
					g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
					m_ClientSocket->CloseSocket();
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					g_GlobalAttemper.DownLoadClient(TEXT("��Ϸ����"),0,true);
				}
			}
			else
			{
				g_GlobalAttemper.DestroyStatusWnd(m_pPlatformFrame);
				m_ClientSocket->CloseSocket();
				TCHAR szMessage[]=TEXT("��Ϸ�����汾�Ѿ����������ڵİ汾�����Լ���ʹ�ã������Ƿ����������°汾��");
				int iResult=ShowInformationEx(szMessage,0,MB_ICONSTOP|MB_YESNO|MB_DEFBUTTON1,TEXT("��Ϸ����"));
				if(iResult != IDYES)
				{
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					AfxGetMainWnd()->PostMessage(WM_CLOSE);
				}
				else 
				{
					g_GlobalAttemper.DownLoadClient(TEXT("��Ϸ����"),0,true);
				}
			}

			return true;
		}
	}
	return true;
}

//�û���Ϣ
bool CPlatformSocket::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID == MDM_GP_USER);
	switch(Command.wSubCmdID)
	{
	case SUB_GP_USER_DOWNLOAD_FACE:			//����ͷ��
	case SUB_GP_UPLOAD_FACE_RESULT:		//�ϴ����
	case SUB_GP_DELETE_FACE_RESULT:		//ɾ�����
	case SUB_GP_MODIFY_INDIVIDUAL_RESULT:	//�޸Ľ��
		{
			return true;
		}
	default:
		{
			ASSERT(FALSE);
			return false;
		}
	}
	return true;
}
