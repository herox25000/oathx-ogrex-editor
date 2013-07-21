#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

//���ư�ť
#define IDC_BT_FRAME_MIN					100							//��С��ť
#define IDC_BT_FRAME_CLOSE					101							//�رհ�ť

#define IDC_BT_GAME							102							//��Ϸר��
#define IDC_BT_MATCH						103							//����ר��
#define IDC_BT_PROPERTY						104							//�����̳�
#define IDC_BT_PRIZE						105							//��Ʒ����
#define IDC_BT_RECHARGE						106							//��ֵ����

#define IDC_BT_REFLASH						107							//��Ϣˢ��
#define IDC_BT_USERINFOSET					108							//��������
#define IDC_BT_RETURN						109							//����
#define IDC_BT_LOBBYSET						110							//��������

#define IDC_BT_USERBAG						111							//��ɫ����
#define IDC_BT_SQUARE						112							
#define IDC_BT_TILL							113
#define IDC_BT_IM							114

//��Ӱ����
#define SHADOW_CX							0							//��Ӱ���
#define SHADOW_CY							0							//��Ӱ�߶�

#define CAPTION_SIZE						35							//�����С

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
	m_bLogonPlaza = false;
}

CPlatformFrame::~CPlatformFrame()
{
}


BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

END_MESSAGE_MAP()


//�ӿڲ�ѯ
void * __cdecl CPlatformFrame::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}
//�����¼�
bool __cdecl CPlatformFrame::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if (nErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(this);
		ShowMessageBox(TEXT("��¼����������ʧ�ܣ����Ժ����Ի�������վ���棡"),MB_ICONINFORMATION);
		OnCommandLogon();
		return true;
	}

	//���͵�¼��
	if (m_bLogonPlaza==false)
	{
		m_DlgLogon.SendLogonPacket(m_ClientSocket.GetInterface());
		g_GlobalAttemper.ShowStatusMessage(TEXT("������֤�û���¼��Ϣ..."),this);
	}
	return true;
}
//�ر��¼�
bool __cdecl CPlatformFrame::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if (m_bLogonPlaza==false)
	{
		if (cbShutReason!=SHUT_REASON_NORMAL)
		{
			g_GlobalAttemper.DestroyStatusWnd(this);
			ShowMessageBox(TEXT("��¼����������ʧ�ܣ����Ժ����Ի�������վ���棡"),MB_ICONINFORMATION);
			OnCommandLogon();
		}
	}

	return true;
}
//��ȡ�¼�
bool __cdecl CPlatformFrame::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
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


//��ʾ��Ϣ
int CPlatformFrame::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{				
	int nResult=ShowInformationEx(pszMessage,0,nType,TEXT("��ʾ"));
	return nResult;
}

//������Ϣ
void CPlatformFrame::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_ClientSocket->SendData(wMainCmdID, wSubCmdID, pData, wDataSize);
	return;
}

//��¼��Ϣ
bool CPlatformFrame::OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize)
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
				default: { ASSERT(FALSE); }
				}
			}

			//������ʾ
			g_GlobalAttemper.ShowStatusMessage(TEXT("���ڶ�ȡ�������б���Ϣ..."),this);

			return true;
		}
	case SUB_GP_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GP_LogonError *pLogonError = (CMD_GP_LogonError *)pData;
			ASSERT(wDataSize>=(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			g_GlobalAttemper.DestroyStatusWnd(this);
			m_ClientSocket->CloseSocket();

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}
			//���͵�¼
			OnCommandLogon();
			return true;
		}
	case SUB_GP_LOGON_FINISH:		//��¼���
		{
			//�ر���ʾ
			g_GlobalAttemper.DestroyStatusWnd(this);

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

			//��¼��Ϣ
			ShowWindow(SW_SHOW);
			SetActiveWindow();
			BringWindowToTop();
			SetForegroundWindow();


			m_bLogonPlaza=true;
			m_DlgLogon.OnLogonSuccess();
			//��¼��Ϣ
			g_GlobalUnits.WriteUserCookie();

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
bool CPlatformFrame::OnSocketMainServerList(CMD_Command Command, void * pData, WORD wDataSize)
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
bool CPlatformFrame::OnSocketMainSystem(CMD_Command Command, void * pData, WORD wDataSize)
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
					g_GlobalAttemper.DestroyStatusWnd(this);
					m_ClientSocket->CloseSocket();
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					g_GlobalAttemper.DownLoadClient(TEXT("��Ϸ����"),0,true);
				}
			}
			else
			{
				g_GlobalAttemper.DestroyStatusWnd(this);
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
bool CPlatformFrame::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize)
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




int CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

	SetFrameSize(LESS_SCREEN_CX, LESS_SCREEN_CY);
	LoadImages();
	LoadButtons();
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(), rcClient.Height());
	
	//������½����
	m_DlgLogon.SetPlatFormPointer(this);
	OnCommandLogon();
	g_GlobalUnits.m_ServerListManager.InitServerListManager(NULL);
	//m_GamePage.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(250, 260, 250+176*3, 260+140*3), this, 10001);
	//m_GamePage.Create(3, 3, NULL, CRect(250, 260, 250+176*3, 260+140*3), this, 0);
	m_ZonePage.Create(0, CRect(250, 206, 250+176*3, 260+140*3), this);
	return 0;
}

//�ؼ���
void CPlatformFrame::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}
//��Ϣ����
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);;
}


//������½����
void CPlatformFrame::OnCommandLogon()
{
	//������¼��
	if (m_DlgLogon.m_hWnd==NULL) 
	{
		m_DlgLogon.Create(IDD_LOGON,this);
	}
	//��ʾ��¼��
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.BringWindowToTop();
	m_DlgLogon.SetForegroundWindow();
	return;
}

//�򿪴�������
void CPlatformFrame::OnOpenFrameSet()
{
	//������¼��
	if (m_DlgFrameSet.m_hWnd == NULL) 
	{
		m_DlgFrameSet.Create(IDD_FRAMESET, this);
	}
	//��ʾ��¼��
	m_DlgFrameSet.ShowWindow(SW_SHOW);
	m_DlgFrameSet.SetActiveWindow();
	m_DlgFrameSet.SetForegroundWindow();
	return;
}

//���ӷ�����
void CPlatformFrame::OnCommandConnect()
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
			OnCommandLogon();
			return;
		}
	}

	//���ӷ�����
	try
	{
		//���ӷ�����
		m_ClientSocket->CloseSocket();
		if (m_ClientSocket->Connect(m_DlgLogon.GetLogonServer(),PORT_LOGON_SERVER)!=CONNECT_SUCCESS)
		{
			throw TEXT("���������Ӵ��󣬿��������ϵͳ��û�гɹ����������磡");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessageBox(pszError,MB_ICONINFORMATION);
		OnCommandLogon();
		return;
	}

	//��ʾ��ʾ��
	CString strMessage=TEXT("�������ӷ����������Ժ�...");
	g_GlobalAttemper.ShowStatusMessage(strMessage,this);
	return;
}

//ȡ������
void CPlatformFrame::OnCommandCancelConnect()
{
	g_GlobalAttemper.DestroyStatusWnd(this);
	m_ClientSocket->CloseSocket();
	OnCommandLogon();
	return;
}

void CPlatformFrame::SetFrameSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
	CenterWindow();
}

BOOL CPlatformFrame::RectifyResource(int nWidth, int nHeight)
{
	//�����ж�
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//���λ��
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX, SHADOW_CY, nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//��������
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//��������
		SetWindowRgn(RegionWindow,TRUE);
	}

	return TRUE;
}

//���ذ�ť
void CPlatformFrame::LoadButtons()
{
	m_LobbySet.CreateButton(this, "PNG_LOBBY_SET", _T("PNG"), LESS_SCREEN_CX - 112, 3, IDC_BT_LOBBYSET, 4);
	m_btMin.CreateButton(this, "PNG_BT_FRAME_MIN", _T("PNG"), LESS_SCREEN_CX - 77, 3, IDC_BT_FRAME_MIN, 4);
	m_btClose.CreateButton(this, "PNG_BT_FRAME_CLOSE", _T("PNG"), LESS_SCREEN_CX - 42, 3, IDC_BT_FRAME_CLOSE, 4);

	m_btGame.CreateButton(this, "PNG_BT_GAME", _T("PNG"), LESS_SCREEN_CX / 2 - 264, 154, IDC_BT_GAME, 4);
	m_btMatch.CreateButton(this, "PNG_BT_MATCH", _T("PNG"), LESS_SCREEN_CX / 2 - 264 + 108, 154, IDC_BT_MATCH, 4);
	m_btProperty.CreateButton(this, "PNG_BT_PROPERTY", _T("PNG"), LESS_SCREEN_CX / 2 - 264 + 216, 154, IDC_BT_PROPERTY, 4);
	m_btPrize.CreateButton(this, "PNG_BT_PRIZE", _T("PNG"), LESS_SCREEN_CX / 2 + 60, 154, IDC_BT_PRIZE, 4);
	m_btRecharge.CreateButton(this, "PNG_BT_RECHARGE", _T("PNG"), LESS_SCREEN_CX / 2 + 168, 154, IDC_BT_RECHARGE, 4);

	m_btReflash.CreateButton(this, "PNG_YOU_RENEW", _T("PNG"), 178, 322, IDC_BT_REFLASH, 4);
	m_btUserInfoSet.CreateButton(this, "PNG_INFO_MODIFY", _T("PNG"), 26, 290, IDC_BT_USERINFOSET, 4);
	m_btReturn.CreateButton(this, "PNG_GL_BACK", _T("PNG"), LESS_SCREEN_CX / 2 + 210, 210, IDC_BT_RETURN, 4);

	m_btSquare.CreateButton(this, "PNG_BT_GL_SQUARE", _T("PNG"), 26, 490, IDC_BT_SQUARE, 4);
	m_btTill.CreateButton(this, "PNG_BT_GL_TILL", _T("PNG"), 72, 490, IDC_BT_TILL, 4);
	m_btUserBag.CreateButton(this, "PNG_BT_GL_BAGPACK", _T("PNG"), 122, 490, IDC_BT_USERBAG, 4);
	m_btIm.CreateButton(this, "PNG_BT_GL_IM", _T("PNG"), 172, 490, IDC_BT_IM, 4);
}

//����ͼƬ��Դ
void CPlatformFrame::LoadImages()
{
	m_ImageHead.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_HEAD"));
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_PLAZA"));
	m_ImageUserInfo.LoadImage(AfxGetInstanceHandle(), TEXT("BACKGROUND_USERINFO"));
	m_ImageGamePublic.LoadImage(AfxGetInstanceHandle(), TEXT("BACKGROUND_GAMEPUBLIC"));

	m_UserHead.LoadImage(AfxGetInstanceHandle(), TEXT("PNG_SEX_HEAD"));
}

BOOL CPlatformFrame::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	pDevC->SetBkMode(TRANSPARENT);
	m_ImageHead.DrawImage(pDevC, 0, 0);
	int nHight = m_ImageHead.GetHeight();
	m_ImageUserInfo.DrawImage(pDevC, 0, nHight);
	m_ImageBack.DrawImage(pDevC,m_ImageUserInfo.GetWidth(), nHight);
	m_ImageGamePublic.DrawImage(pDevC, m_ImageUserInfo.GetWidth() + m_ImageBack.GetWidth(), nHight);
	SetButtonBackGrounds(pDevC);
	DrawUserInfo(pDevC);
	m_ZonePage.EraseBkgnd(pDevC);
	return TRUE;
}

//��ť��������
void CPlatformFrame::SetButtonBackGrounds(CDC *pDC)
{
	m_btMin.SetBkGnd(pDC);
	m_btClose.SetBkGnd(pDC);
	m_LobbySet.SetBkGnd(pDC);

	m_btGame.SetBkGnd(pDC);
	m_btMatch.SetBkGnd(pDC);
	m_btProperty.SetBkGnd(pDC);
	m_btPrize.SetBkGnd(pDC);
	m_btRecharge.SetBkGnd(pDC);

	m_btReflash.SetBkGnd(pDC);
	m_btUserInfoSet.SetBkGnd(pDC);
	m_btReturn.SetBkGnd(pDC);

	m_btUserBag.SetBkGnd(pDC);
	m_btIm.SetBkGnd(pDC);
	m_btSquare.SetBkGnd(pDC);
	m_btTill.SetBkGnd(pDC);
}

//���ƽ�ɫ��Ϣ
void CPlatformFrame::DrawUserInfo( CDC *pDC )
{
	tagGlobalUserData& UserData = g_GlobalUnits.GetGolbalUserData();
	if (UserData.dwUserID!=0L)
	{
		int nHeadNumberWidth	= m_UserHead.GetWidth() / 2;
		int nHeadNumberHeight	= m_UserHead.GetHeight(); 
		//���ͷ��
		if (UserData.cbGender)
		{
			m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, 0, 0);
		}
		else
		{
			m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, nHeadNumberWidth, 0);
		}

		//����ʺ�
		CRect rcAccounts;
		rcAccounts.SetRect(66, 344, 166,360);
		pDC->DrawText(UserData.szAccounts,lstrlen(UserData.szAccounts),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}
}

//�����Ϣ
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

BOOL CPlatformFrame::OnCommand( WPARAM wParam, LPARAM lParam )
{
	//��������
	UINT nCommandID=LOWORD(wParam);
	switch (nCommandID)
	{
	case IDC_BT_FRAME_MIN:				//��С��ť
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_BT_FRAME_CLOSE:				//�رհ�ť
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_BT_LOBBYSET:				//�򿪴�������
		{
			OnOpenFrameSet();
			return TRUE;
		}
	case IDM_LOGON_PLAZA:			//������½����	
		{
			OnCommandLogon();
			return TRUE;
		}	
	case IDM_CONNECT_SERVER:		//���ӵ�������
		{
			OnCommandConnect();
			return TRUE;
		}
	case IDM_CANCEL_CONNECT:		//ȡ�����������ӣ����ֵ�½����
		{
			OnCommandCancelConnect();
			return TRUE;
		}
	}

	return FALSE;

}

VOID CPlatformFrame::OnClose()
{
	__super::OnClose();
}
