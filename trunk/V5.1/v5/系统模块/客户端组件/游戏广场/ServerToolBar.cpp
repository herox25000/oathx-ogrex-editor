#include "StdAfx.h"
#include "Resource.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "ServerToolBar.h"
#include "CollocateRoom.h"
#include "DlgTablePassword.h"
#include "DlgSearchTable.h"

//////////////////////////////////////////////////////////////////////////////////
//�궨��
#define BUTTON_H_SPACE                   8                   //������

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CServerToolBar, CDialog)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()

	//�Զ���Ϣ
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CServerToolBar::CServerToolBar() : CDialog(IDD_DLG_SERVER_TOOL_BAR)
{	
	//���ñ���
	m_bCreateFlag = false;

	return;
}

//��������
CServerToolBar::~CServerToolBar()
{
	return;
}

//�ӿڲ�ѯ
VOID * CServerToolBar::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//��������
BOOL CServerToolBar::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	m_bCreateFlag = true;
	
	//���Ӱ�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btQuitServer.SetButtonImage(IDB_BT_QUIT_SERVER,TEXT("BT_QUIT_SERVER"),hInstance,true,false);
	m_btTableButton1.SetButtonImage(IDB_BT_TABLE_BUTTON_1,TEXT("BT_TABLE_BUTTON_1"),hInstance,true,false);
	m_btTableButton2.SetButtonImage(IDB_BT_TABLE_BUTTON_2,TEXT("BT_TABLE_BUTTON_2"),hInstance,true,false);
	m_btTableButton3.SetButtonImage(IDB_BT_TABLE_BUTTON_3,TEXT("BT_TABLE_BUTTON_3"),hInstance,true,false);
	m_btTableButton4.SetButtonImage(IDB_BT_TABLE_BUTTON_4,TEXT("BT_TABLE_BUTTON_4"),hInstance,true,false);
	m_btTableButton5.SetButtonImage(IDB_BT_TABLE_BUTTON_5,TEXT("BT_TABLE_BUTTON_5"),hInstance,true,false);

	//��������
	CRect rcButton;
	m_btTableButton1.GetWindowRect(rcButton);

	//���ô���
	SetWindowPos(NULL,0,0,(rcButton.Width()+BUTTON_H_SPACE)*6,rcButton.Height(),SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);

	//ע���¼�
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	return TRUE;
}

//�ؼ���
VOID CServerToolBar::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	//���Ӱ�ť
	DDX_Control(pDX, IDC_BT_QUIT_SERVER, m_btQuitServer);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_1, m_btTableButton1);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_2, m_btTableButton2);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_3, m_btTableButton3);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_4, m_btTableButton4);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_5, m_btTableButton5);

	return;
}

//λ����Ϣ
VOID CServerToolBar::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//�����
BOOL CServerToolBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//�������
	CPlatformFrame * pPlatformFrame = CPlatformFrame::GetInstance();
	ASSERT(pPlatformFrame!=NULL);
	if(pPlatformFrame==NULL) return TRUE;

	//������ͼ
	CServerViewItem * pServerViewItem = pPlatformFrame->m_pServerViewItem;
	ASSERT(pServerViewItem != NULL);
	if(pServerViewItem == NULL) return TRUE;

	//��������
	WORD wCommandID = LOWORD(wParam);
	switch(wCommandID)
	{
	case IDC_BT_QUIT_SERVER:		//�˳�����
		{
			//��������
			pServerViewItem->PostMessage(WM_COMMAND,IDM_DELETE_SERVER_ITEM,0L);

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_1:		//���밴ť
		{
			//��������
			if (pServerViewItem->m_ServiceStatus!=ServiceStatus_ServiceIng) return TRUE;
			if ((pServerViewItem->m_wReqTableID!=INVALID_TABLE)&&(pServerViewItem->m_wReqChairID!=INVALID_CHAIR)) return TRUE;

			//״̬�ж�
			if (pServerViewItem->m_pIMySelfUserItem->GetUserStatus()>=US_PLAYING)
			{
				CInformation Information(this);
				Information.ShowMessageBox(TEXT("��������Ϸ�У���ʱ�����뿪�����Ƚ�����ǰ��Ϸ��"),MB_ICONINFORMATION,30L);
				return TRUE;
			}

			//�����λ
			if (CServerRule::IsAllowAvertCheatMode(pServerViewItem->m_dwServerRule)==true)
			{
				pServerViewItem->PerformSitDownAction(INVALID_TABLE,INVALID_CHAIR,false);
				return TRUE;
			}

			//��������
			ASSERT(CParameterGlobal::GetInstance()!=NULL);
			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

			//ִ�ж���
			switch (pParameterGlobal->m_cbActionHitAutoJoin)
			{
			case ACTION_SEARCH_TABLE:		//����λ��
				{
					//��������
					tagSearchTable SearchTable;
					ZeroMemory(&SearchTable,sizeof(SearchTable));

					//��������
					SearchTable.bNotFull=true;
					SearchTable.bOneNull=true;
					SearchTable.bAllNull=false;
					SearchTable.bFilterPass=true;
					SearchTable.bTwoNull=(pServerViewItem->m_TableViewFrame.GetChairCount()!=2);

					//�������
					SearchTable.wResultTableID=INVALID_TABLE;
					SearchTable.wResultChairID=INVALID_CHAIR;
					SearchTable.wStartTableID=pServerViewItem->m_wFindTableID+1;

					//��������
					pServerViewItem->SearchGameTable(SearchTable);
					pServerViewItem->m_wFindTableID=SearchTable.wResultTableID;

					//��������
					if (pServerViewItem->m_wFindTableID==INVALID_CHAIR)
					{
						//��������
						SearchTable.bAllNull=true;
						SearchTable.bNotFull=true;
						SearchTable.bOneNull=true;
						SearchTable.bFilterPass=true;
						SearchTable.bTwoNull=(pServerViewItem->m_TableViewFrame.GetChairCount()!=2);

						//�������
						SearchTable.wResultTableID=INVALID_TABLE;
						SearchTable.wResultChairID=INVALID_CHAIR;
						SearchTable.wStartTableID=pServerViewItem->m_wFindTableID+1;

						//��������
						pServerViewItem->SearchGameTable(SearchTable);
						pServerViewItem->m_wFindTableID=SearchTable.wResultTableID;
					}

					//����ж�
					if (pServerViewItem->m_wFindTableID!=INVALID_CHAIR)
					{
						//Ч������
						ASSERT(SearchTable.wResultTableID!=INVALID_TABLE);
						ASSERT(SearchTable.wResultChairID!=INVALID_CHAIR);

						//��������
						WORD wChairID=SearchTable.wResultChairID;
						pServerViewItem->m_TableViewFrame.VisibleTable(pServerViewItem->m_wFindTableID);
						pServerViewItem->m_TableViewFrame.FlashGameChair(pServerViewItem->m_wFindTableID,wChairID);

						//�Զ�����
						CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
						if (pParameterGlobal->m_bAutoSitDown==true) pServerViewItem->PerformSitDownAction(pServerViewItem->m_wFindTableID,wChairID,true);
					}
					else
					{
						//��ʾ��Ϣ
						CInformation Information(this);
						Information.ShowMessageBox(TEXT("��Ǹ��������ʱû�п��Լ������Ϸ�������Ժ��ٴγ��ԣ�"),MB_ICONINFORMATION,30L);
					}

					break;
				}
			case ACTION_SHOW_SEARCH_DLG:	//��������
				{
					//��������
					PostMessage(WM_COMMAND,IDC_BT_TABLE_BUTTON_2,0L);

					break;
				}
			}

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_2:		//��������
		{
			//��������
			if (pServerViewItem->m_pDlgSearchTable==NULL)
			{
				//��������
				try
				{
					pServerViewItem->m_pDlgSearchTable=new CDlgSearchTable;
					if (pServerViewItem->m_pDlgSearchTable==NULL) return TRUE;
				}
				catch (...)
				{
					ASSERT(FALSE);
					return TRUE;
				}

				//���ö���
				pServerViewItem->m_pDlgSearchTable->SetServerViewItem(pServerViewItem);
				pServerViewItem->m_pDlgSearchTable->SetTableViewFrame(&pServerViewItem->m_TableViewFrame);
			}

			//��������
			if (pServerViewItem->m_pDlgSearchTable->m_hWnd==NULL)
			{
				pServerViewItem->m_pDlgSearchTable->Create(IDD_DLG_SEARCH_TABLE,pServerViewItem);
			}

			//��ʾ����
			pServerViewItem->m_pDlgSearchTable->ShowWindow(SW_SHOW);
			pServerViewItem->m_pDlgSearchTable->SetForegroundWindow();

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_3:		//������ť
		{
			//��������
			CDlgTablePassword DlgTablePassword;

			//������ʾ
			if(pServerViewItem->m_pParameterServer->m_bTakePassword)
			{
				lstrcpyn(DlgTablePassword.m_szPassword,pServerViewItem->m_pParameterServer->m_szPassword,CountArray(DlgTablePassword.m_szPassword));
				DlgTablePassword.SetPromptString(TEXT("���������ý������룬��Ҫ���ģ����������룡��Ҫ��������������롣"));
			}
			else
			{
				DlgTablePassword.SetPromptString(TEXT("���������ӽ������롣"));
			}

			//��ʾ����
			if (DlgTablePassword.DoModal()==IDOK)
			{
				CString strTablePass = DlgTablePassword.m_szPassword;
				if(strTablePass.GetLength() > 0)
				{
					//��������
					pServerViewItem->m_pParameterServer->m_bTakePassword=true;
					lstrcpyn(pServerViewItem->m_pParameterServer->m_szPassword,DlgTablePassword.m_szPassword,CountArray(pServerViewItem->m_pParameterServer->m_szPassword));
				}
				else
				{
					//��������
					pServerViewItem->m_pParameterServer->m_bTakePassword=false;
					ZeroMemory(pServerViewItem->m_pParameterServer->m_szPassword,CountArray(pServerViewItem->m_pParameterServer->m_szPassword));
				}

				//���͹���
				pServerViewItem->SendUserRulePacket();
			}

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_4:		//��Ϸ����
		{
			//�������
			CCollocateRoom DlgCollocate;
			DlgCollocate.InitCollocate(pServerViewItem->GetParameterGame(),pServerViewItem->GetParameterServer());

			//��ʾ����
			if (DlgCollocate.DoModal()==IDOK)
			{
				//���͹���
				pServerViewItem->SendUserRulePacket();
			}
			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_5:		//���ఴť
		{
			//����˵�
			CSkinMenu FunctionMenu;
			FunctionMenu.CreateMenu();

			//����˵�
			FunctionMenu.AppendMenu(IDM_GAME_RULE,TEXT("�������"));

			//����˵�
			if (pServerViewItem->m_pIMySelfUserItem->GetMasterOrder()>0)
			{
				//����ָ�
				FunctionMenu.AppendSeparator();

				//����˵�
				FunctionMenu.AppendMenu(IDM_MANAGER_USER,TEXT("��Ϸ��ҹ���..."),MF_ENABLED);
				FunctionMenu.AppendMenu(IDM_MANAGER_SERVER,TEXT("��Ϸ�������..."),MF_DISABLED);
				FunctionMenu.AppendMenu(IDM_MANAGER_MESSAGE,TEXT("ϵͳ��Ϣ����..."),MF_DISABLED);

				//���ò˵�
				if (CMasterRight::CanManagerServer(pServerViewItem->m_dwMasterRight)==true)
				{
					FunctionMenu.EnableMenuItem(IDM_MANAGER_SERVER,MF_ENABLED);
				}

				//���ò˵�
				if (CMasterRight::CanIssueMessage(pServerViewItem->m_dwMasterRight)==true)
				{
					FunctionMenu.EnableMenuItem(IDM_MANAGER_MESSAGE,MF_ENABLED);
				}
			}

			//�����˵�
			CRect rcButton;
			m_btTableButton5.GetWindowRect(&rcButton);
			FunctionMenu.TrackPopupMenu(rcButton.left,rcButton.bottom,this);

			return TRUE;
		}
	}

	//��������
	return pServerViewItem->PostMessage(WM_COMMAND,wCommandID,lParam);
}

//�滭����
BOOL CServerToolBar::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�����豸
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//�滭����
	CBitImage ImageGround;
	ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_TOOL_BAR_BACK);

	//ͼ��ߴ�
	CSize SizeImageGournd(ImageGround.GetWidth(),ImageGround.GetHeight());

	//�滭����
	for(INT nImageWidth=0;nImageWidth<rcClient.Width();nImageWidth +=SizeImageGournd.cx)
	{
		ImageGround.BitBlt(*pBufferDC,nImageWidth,0);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//�����ؼ�
VOID CServerToolBar::RectifyControl(INT nWidth, INT nHeight)
{
	//״̬�ж�
	if( m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//��������
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;

	//�رհ�ť
	CRect rcQuitServer;
	m_btQuitServer.GetWindowRect(&rcQuitServer);
	DeferWindowPos(hDwp,m_btQuitServer,NULL,nWidth-rcQuitServer.Width(),0,0,0,uFlags|SWP_NOSIZE);

	//���Ӱ�ť
	INT nXPosTable=nWidth-rcQuitServer.Width();
	CSkinButton * TableButtonArray[]={&m_btTableButton5,&m_btTableButton4,&m_btTableButton3,&m_btTableButton2,&m_btTableButton1};

	//���Ӱ�ť
	for (INT i=0;i<CountArray(TableButtonArray);i++)
	{
		//��ȡλ��
		CRect rcTableButton;
		TableButtonArray[i]->GetWindowRect(&rcTableButton);

		//�ƶ���ť
		nXPosTable-=(rcTableButton.Width()+BUTTON_H_SPACE);
		DeferWindowPos(hDwp,TableButtonArray[i]->m_hWnd,NULL,nXPosTable,0,0,0,uFlags|SWP_NOSIZE);
	}

	//��������
	EndDeferWindowPos(hDwp);

	return;
}


//�¼���Ϣ
LRESULT CServerToolBar::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//�¼�����
	switch (wParam)
	{
	case EVENT_SERVER_LOGON_FINIDH:			//�����¼
		{
			//�������
			CPlatformFrame * pPlatformFrame = CPlatformFrame::GetInstance();
			ASSERT(pPlatformFrame!=NULL);
			if(pPlatformFrame==NULL) return 0L;

			//������ͼ
			CServerViewItem * pServerViewItem = pPlatformFrame->m_pServerViewItem;
			ASSERT(pServerViewItem!=NULL);
			if(pServerViewItem==NULL) return 0L;

			//�����ж�
			if (CServerRule::IsForfendGameRule(pServerViewItem->m_dwServerRule)==false)
			{
				//���͹���
				pServerViewItem->SendUserRulePacket();

				//���ð�ť
				m_btTableButton4.EnableWindow(TRUE);
			}

			//�����ж�
			if (CServerRule::IsForfendLockTable(pServerViewItem->m_dwServerRule)==false)
			{
				//���ð�ť
				m_btTableButton3.EnableWindow(TRUE);
			}

			//���Ұ�ť
			if (CServerRule::IsAllowAvertCheatMode(pServerViewItem->m_dwServerRule)==false)
			{
				m_btTableButton2.EnableWindow(TRUE);
			}

			return 0L;
		}
	}

	return 0L;
}
//////////////////////////////////////////////////////////////////////////////////
