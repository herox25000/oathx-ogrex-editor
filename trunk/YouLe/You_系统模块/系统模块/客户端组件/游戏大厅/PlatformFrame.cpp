#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{

}

CPlatformFrame::~CPlatformFrame()
{

}


BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)
	ON_WM_COPYDATA()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//��Դ���
HINSTANCE CPlatformFrame::GetResInstanceHandle()
{
	return g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
}

//��ȡ��Դ
tagPlatformFrameImageNew CPlatformFrame::GetPlatformRes()
{
	return g_GlobalUnits.m_PlatformFrameImage;
}

int CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

	SetFrameSize(LESS_SCREEN_CX, LESS_SCREEN_CY);
	LoadImages();
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(LESS_SCREEN_CX, LESS_SCREEN_CY);
	
	//������½����
	m_DlgLogon.SetPlatFormPointer(this);
	m_PlatformSocket.SetDlgLogonPointer(&m_DlgLogon);
	m_PlatformSocket.SetPlatFormPointer(this);
	OnCommandLogon();
	g_GlobalUnits.m_ServerListManager.InitServerListManager(NULL);
	
	m_FrameSheet.Create(0, rcClient, this, NULL, NULL);

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
	m_PlatformSocket.m_bLogonPlaza = false;
	ShowWindow(SW_HIDE);
	//������¼��
	if (m_DlgLogon.m_hWnd==NULL) 
	{
		m_DlgLogon.Create(IDD_LOGON,GetDesktopWindow());
	}
	//��ʾ��¼��
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.BringWindowToTop();
	m_DlgLogon.SetForegroundWindow();
	return;
}

//IPC ��Ϣ
BOOL CPlatformFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT * pCopyDataStruct)
{
	if(TRUE == g_GlobalUnits.m_GameRoomManager.m_RoomSocket.OnCopyData(pWnd,pCopyDataStruct))
		return TRUE;
	return __super::OnCopyData(pWnd, pCopyDataStruct);
}

//���ӷ�����
void CPlatformFrame::OnCommandConnect()
{
	m_PlatformSocket.ConnectToServer(m_DlgLogon.GetLogonServer(),PORT_LOGON_SERVER);
}

//ȡ������
void CPlatformFrame::OnCommandCancelConnect()
{
	g_GlobalAttemper.DestroyStatusWnd(this);
	m_PlatformSocket.m_ClientSocket->CloseSocket();
	OnCommandLogon();
	return;
}

void CPlatformFrame::SetFrameSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	CenterWindow();
}

BOOL CPlatformFrame::RectifyResource(int nWidth, int nHeight)
{
	//�����ж�
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//���λ��
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX, SHADOW_CY, nWidth - SHADOW_CX, nHeight - SHADOW_CY);

		//��������
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left, rcFrame.top, rcFrame.right + 1, rcFrame.bottom + 1, ROUND_CX,ROUND_CY);

		//��������
		SetWindowRgn(RegionWindow, FALSE);
	}
	return TRUE;
}

//����ͼƬ��Դ
void CPlatformFrame::LoadImages()
{
	m_ImageHead.LoadImage(GetResInstanceHandle(), GetPlatformRes().pszImageHead);
	m_ImageBack.LoadImage(GetResInstanceHandle(), GetPlatformRes().pszImageMiddle);
	m_ImageUserInfo.LoadImage(GetResInstanceHandle(), GetPlatformRes().pszImageLeft);
	m_ImageGamePublic.LoadImage(GetResInstanceHandle(), GetPlatformRes().pszImageRight);
}

BOOL CPlatformFrame::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	pDevC->SetBkMode(TRANSPARENT);

	int xPos = 0;
	int yPos = 0;
	m_ImageHead.DrawImage(pDevC, xPos, yPos);
	int nHight = m_ImageHead.GetHeight();
	m_ImageUserInfo.DrawImage(pDevC, xPos, nHight + yPos);
	m_ImageBack.DrawImage(pDevC, m_ImageUserInfo.GetWidth() + xPos, nHight + yPos);
	m_ImageGamePublic.DrawImage(pDevC, m_ImageUserInfo.GetWidth() + m_ImageBack.GetWidth() + xPos, nHight + yPos);

	m_FrameSheet.Draw(pDevC);
	return TRUE;
}

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
	m_DlgFrameSet.BringWindowToTop();
	m_DlgFrameSet.SetForegroundWindow();
}

BOOL CPlatformFrame::OnCommand( WPARAM wParam, LPARAM lParam )
{
	//��������
	UINT nCommandID=LOWORD(wParam);
	switch (nCommandID)
	{
	case WM_CLOSE_FRAME:
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case WM_SWITCH_ACCOUNT:
		{
			//ɾ����¼
			g_GlobalUnits.DeleteUserCookie();
			tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
			memset(&GlobalUserData,0,sizeof(GlobalUserData));
			OnCommandLogon();
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
	case WM_SHOW_USERSET:
		{
			m_FrameSheet.ProcessCommand(WM_SHOW_USERSET);
			return TRUE;
		}
	case WM_SHOW_FRAMESET:			//�򿪴�������
		{
//			OnOpenFrameSet();
			return TRUE;
		}
	}

	return FALSE;

}

VOID CPlatformFrame::OnClose()
{
	__super::OnClose();
}

void CPlatformFrame::SaveBossKey( int nCtrlKey, int nHelpKey )
{
	
}

//�����Ϣ
void CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	m_FrameSheet.InjectLeftDown(Point);

	//ģ�ⰴ����
	CRect client;
	GetClientRect(&client);
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE) && (Point.x <= (client.Width() - 120)))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}
	
	CFrameWnd::OnLButtonDown(nFlags,Point);
}

void CPlatformFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_FrameSheet.InjectLeftUp(point);

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CPlatformFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	m_FrameSheet.InjectMouseMove(point);
	CFrameWnd::OnMouseMove(nFlags, point);

}

