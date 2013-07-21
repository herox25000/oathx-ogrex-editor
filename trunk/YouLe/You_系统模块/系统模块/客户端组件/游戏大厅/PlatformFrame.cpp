#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

//���ư�ť
#define IDC_BT_FRAME_MIN					100									//��С��ť
#define IDC_BT_FRAME_CLOSE					101									//�رհ�ť

//Բ�Ǵ�С
#define ROUND_CX					7									//Բ�ǿ��
#define ROUND_CY					7									//Բ�Ǹ߶�

//��Ӱ����
#define SHADOW_CX					0									//��Ӱ���
#define SHADOW_CY					0									//��Ӱ�߶�

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
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


int CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

// 	m_pGamePlazaDlg = new CGamePlazaDlg();
// 	m_pGamePlazaDlg->Create(IDD_GAMEPLAZA_DIALOG, this);
// 	m_pGamePlazaDlg->ShowWindow(SW_SHOW);
	SetFrameSize(LESS_SCREEN_CX, LESS_SCREEN_CY);
	LoadImages();
	LoadButtons();
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(), rcClient.Height());
	//��ʾ����
	ShowWindow(SW_SHOW);
	SetForegroundWindow();
	//������½����
	//SendLogonMessage();
	m_pGamePage.Create(0, CRect(250, 260, 500, 500), this);
	m_pGamePage.ShowWindow(SW_SHOW);
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
bool __cdecl CPlatformFrame::SendLogonMessage()
{
	PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
	return true;
}

//������Ϣ
bool __cdecl CPlatformFrame::SendConnectMessage()
{
	PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return true;
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
	m_DlgLogon.SetForegroundWindow();

	return;
}

//���ӷ�����
void CPlatformFrame::OnCommandConnect()
{
	////�������
	//if (m_ClientSocket.GetInterface()==NULL)
	//{
	//	try
	//	{
	//		IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
	//		if (m_ClientSocket.CreateInstance()==false) 
	//		{
	//			throw TEXT("�����������ʧ��");
	//		}
	//		if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) 
	//		{
	//			throw TEXT("��������ص��ӿ�����ʧ��");
	//		}
	//	}
	//	catch (...)
	//	{
	//		ShowMessageBox(TEXT("�����������ʧ�ܣ�������������Ϸ������"),MB_ICONSTOP);
	//		PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
	//		return;
	//	}
	//}

	////��ַ����
	//CRegKey RegServer;
	//LPCTSTR pszServerIP=m_DlgLogon.GetLogonServer();
	//TCHAR szRegServer[256]=TEXT(""),szServerAddr[64]=TEXT("");
	//_snprintf(szRegServer,sizeof(szRegServer),TEXT("%s\\%s"),REG_LOGON_SERVER,pszServerIP);

	//if (RegServer.Open(HKEY_CURRENT_USER,szRegServer,KEY_READ)==ERROR_SUCCESS)
	//{
	//	TCHAR szReadData[1024]=TEXT("");
	//	DWORD dwReadData=0L,dwDataType=0L,dwDataSize=sizeof(szReadData);
	//	LONG lErrorCode=RegServer.QueryValue(TEXT("ServerAddr"),&dwDataType,szReadData,&dwDataSize);
	//	if (lErrorCode==ERROR_SUCCESS) 
	//	{
	//		CXOREncrypt::CrevasseData(szReadData,szServerAddr,sizeof(szServerAddr));
	//		pszServerIP=szServerAddr;
	//	}
	//}

	////���ӷ�����
	//try
	//{
	//	//���ӷ�����
	//	m_ClientSocket->CloseSocket();

	//	//�����ж�
	//	if ( m_DlgLogon.EnableProxy() == true )
	//	{
	//		//��ȡ����
	//		enProxyServerType ProxyServerType;
	//		tagProxyServerInfo ProxyServerInfo;
	//		m_DlgLogon.GetProxyInfo(ProxyServerType, ProxyServerInfo);	

	//		//���ô���
	//		m_ClientSocket->SetProxyServerInfo(ProxyServerType,ProxyServerInfo);
	//	}

	//	if (m_ClientSocket->Connect(pszServerIP,PORT_LOGON_SERVER)!=CONNECT_SUCCESS)
	//	{
	//		throw TEXT("���������Ӵ��󣬿��������ϵͳ��û�гɹ����������磡");
	//	}
	//}
	//catch (LPCTSTR pszError)
	//{
	//	ShowMessageBox(pszError,MB_ICONINFORMATION);
	//	SendLogonMessage();
	//	return;
	//}

	////��ʾ��ʾ��
	//CString strMessage=TEXT("�������ӷ����������Ժ�...");
	//g_GlobalAttemper.ShowStatusMessage(strMessage,this);

	return;
}

//ȡ������
void CPlatformFrame::OnCommandCancelConnect()
{
	//g_GlobalAttemper.DestroyStatusWnd(this);
	//m_ClientSocket->CloseSocket();
	SendLogonMessage();
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
	m_btMin.CreateButton(this, "PNG_BT_FRAME_MIN", _T("PNG"), LESS_SCREEN_CX-86, 3, IDC_BT_FRAME_MIN, 5);
	m_btClose.CreateButton(this, "PNG_BT_FRAME_CLOSE", _T("PNG"), LESS_SCREEN_CX-38, 3, IDC_BT_FRAME_CLOSE, 5);
}

//����ͼƬ��Դ
void CPlatformFrame::LoadImages()
{
	m_ImageHead.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_HEAD"));
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_PLAZA"));
	m_ImageUserInfo.LoadImage(AfxGetInstanceHandle(), TEXT("BACKGROUND_USERINFO"));
	m_ImageGamePublic.LoadImage(AfxGetInstanceHandle(), TEXT("BACKGROUND_GAMEPUBLIC"));
}

BOOL CPlatformFrame::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	m_ImageHead.DrawImage(pDevC, 0, 0);
	int nHight = m_ImageHead.GetHeight();
	m_ImageUserInfo.DrawImage(pDevC, 0, nHight);
	m_ImageBack.DrawImage(pDevC,m_ImageUserInfo.GetWidth(), nHight);
	m_ImageGamePublic.DrawImage(pDevC, m_ImageUserInfo.GetWidth() + m_ImageBack.GetWidth(), nHight);
	SetButtonBackGrounds(pDevC);
	return TRUE;
}

//��ť��������
void CPlatformFrame::SetButtonBackGrounds(CDC *pDC)
{
	m_btMin.SetBkGnd(pDC);
	m_btClose.SetBkGnd(pDC);
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
