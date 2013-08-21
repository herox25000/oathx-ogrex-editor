#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"
#include ".\platformframe.h"

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
	m_bUseBoss = false;
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
	ON_MESSAGE(WM_HOTKEY,OnHotKeyMessage)
//	ON_WM_SYSKEYDOWN()
//	ON_WM_KEYDOWN()
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

	//ע���ȼ�
	if (CSystemParameter::GetInstance().m_bUseBoss)
		g_GlobalUnits.RegisterHotKey(m_hWnd, IDI_HOT_KEY_BOSS, CSystemParameter::GetInstance().m_wBossHotKey);
	
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
	if (m_bUseBoss)
	{
		if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_ESCAPE:
				break;
			case VK_RETURN:
				break;
			case VK_CONTROL:
				m_wModifiers = HOTKEYF_CONTROL;
				break;
			case VK_SHIFT:
				m_wModifiers = HOTKEYF_SHIFT;
				break;
			case VK_MENU:
				m_wModifiers = HOTKEYF_ALT;
				break;
			default:
				{
					m_wCode = LOBYTE(LOWORD(pMsg->wParam));
				}
				break;
			}
		}
		if (m_wModifiers != 0)
		{
			CSystemParameter::GetInstance().m_wBossHotKey = MAKEWORD(m_wCode, m_wModifiers);
			m_FrameSheet.Invalidate(TRUE);
		}
	}
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
	case WM_START_KEYBOSS:		//�����ϰ��
		{
			if( lParam > 0 )
			{
				m_bUseBoss = true;
				m_wOldCode = m_wCode = LOBYTE(LOWORD(CSystemParameter::GetInstance().m_wBossHotKey));
				m_wOldModifiers = m_wModifiers = HIBYTE(LOWORD(CSystemParameter::GetInstance().m_wBossHotKey));
			}
			else
			{
				m_bUseBoss = false;
				CSystemParameter::GetInstance().m_wBossHotKey = MAKEWORD(m_wOldCode, m_wOldModifiers);
			}
			return TRUE;
		}
	case WM_SAVE_KEYBOSS:
		{
			CSystemParameter::GetInstance().m_bUseBoss = m_bUseBoss;
			if (m_bUseBoss)
			{
				g_GlobalUnits.RegisterHotKey(m_hWnd, IDI_HOT_KEY_BOSS, CSystemParameter::GetInstance().m_wBossHotKey);
			}
			else
			{
				::UnregisterHotKey(m_hWnd,IDI_HOT_KEY_BOSS);
			}

			return TRUE;
		}
	}

	return FALSE;

}

VOID CPlatformFrame::OnClose()
{
	//��������
	CSystemParameter::GetInstance().SaveOptionParameter();

	__super::OnClose();
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

LRESULT CPlatformFrame::OnHotKeyMessage( WPARAM wParam, LPARAM lParam )
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//�ϰ��ȼ�
		{
			//��������
			bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

			//���ش���
			if (bBossCome==false)
			{
				//��ԭ����
				ShowWindow(SW_RESTORE);
				ShowWindow(SW_SHOW);

				//�ö�����
				SetActiveWindow();
				BringWindowToTop();
				SetForegroundWindow();
			}
			else
			{
				//���ش���
				ShowWindow(SW_MINIMIZE);
				ShowWindow(SW_HIDE);
			}
			return 0;
		}
	}

	return 0;
}
