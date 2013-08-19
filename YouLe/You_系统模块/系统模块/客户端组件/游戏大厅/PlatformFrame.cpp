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

//资源句柄
HINSTANCE CPlatformFrame::GetResInstanceHandle()
{
	return g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
}

//获取资源
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
	
	//启动登陆窗口
	m_DlgLogon.SetPlatFormPointer(this);
	m_PlatformSocket.SetDlgLogonPointer(&m_DlgLogon);
	m_PlatformSocket.SetPlatFormPointer(this);
	OnCommandLogon();
	g_GlobalUnits.m_ServerListManager.InitServerListManager(NULL);
	
	m_FrameSheet.Create(0, rcClient, this, NULL, NULL);

	return 0;
}

//控件绑定
void CPlatformFrame::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}
//消息解释
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);;
}


//启动登陆窗口
void CPlatformFrame::OnCommandLogon()
{
	m_PlatformSocket.m_bLogonPlaza = false;
	ShowWindow(SW_HIDE);
	//创建登录框
	if (m_DlgLogon.m_hWnd==NULL) 
	{
		m_DlgLogon.Create(IDD_LOGON,GetDesktopWindow());
	}
	//显示登录框
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.BringWindowToTop();
	m_DlgLogon.SetForegroundWindow();
	return;
}

//IPC 消息
BOOL CPlatformFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT * pCopyDataStruct)
{
	if(TRUE == g_GlobalUnits.m_GameRoomManager.m_RoomSocket.OnCopyData(pWnd,pCopyDataStruct))
		return TRUE;
	return __super::OnCopyData(pWnd, pCopyDataStruct);
}

//连接服务器
void CPlatformFrame::OnCommandConnect()
{
	m_PlatformSocket.ConnectToServer(m_DlgLogon.GetLogonServer(),PORT_LOGON_SERVER);
}

//取消连接
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
	//调整判断
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX, SHADOW_CY, nWidth - SHADOW_CX, nHeight - SHADOW_CY);

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left, rcFrame.top, rcFrame.right + 1, rcFrame.bottom + 1, ROUND_CX,ROUND_CY);

		//设置区域
		SetWindowRgn(RegionWindow, FALSE);
	}
	return TRUE;
}

//加载图片资源
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
	//变量定义
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
			//删除记录
			g_GlobalUnits.DeleteUserCookie();
			tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
			memset(&GlobalUserData,0,sizeof(GlobalUserData));
			OnCommandLogon();
			return TRUE;
		}
	case IDM_LOGON_PLAZA:			//启动登陆窗口
		{
			OnCommandLogon();
			return TRUE;
		}	
	case IDM_CONNECT_SERVER:		//连接到服务器
		{
			OnCommandConnect();
			return TRUE;
		}
	case IDM_CANCEL_CONNECT:		//取消服务器连接，重现登陆窗口
		{
			OnCommandCancelConnect();
			return TRUE;
		}
	case WM_SHOW_USERSET:
		{
			m_FrameSheet.ProcessCommand(WM_SHOW_USERSET);
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

//鼠标消息
void CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	m_FrameSheet.InjectLeftDown(Point);

	//模拟按标题
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

