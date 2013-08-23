#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"
#include ".\platformframe.h"

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
	m_bUseBoss = false;
	m_bHandCur = false;
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
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_HOTKEY,OnHotKeyMessage)
//	ON_WM_SYSKEYDOWN()
//	ON_WM_KEYDOWN()
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

	//注册热键
	if (CSystemParameter::GetInstance().m_bUseBoss)
		g_GlobalUnits.RegisterHotKey(m_hWnd, IDI_HOT_KEY_BOSS, CSystemParameter::GetInstance().m_wBossHotKey);
	
	//启动登陆窗口
	m_PlatformSocket.SetDlgLogonPointer(&m_DlgLogon);
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
	case IDM_SETHANDCUR:			//将鼠标设置为小手
		{
			UINT Param = LOWORD(lParam);
			m_bHandCur = Param==0?false:true;
			Invalidate(TRUE);
			return TRUE;
		}
	case WM_SHOW_USERSET:
		{
			m_FrameSheet.ProcessCommand(WM_SHOW_USERSET);
			return TRUE;
		}
	case WM_SHOW_GAMEPAGE:
		{
			m_FrameSheet.ProcessCommand(WM_SHOW_GAMEPAGE);
			return TRUE;
		}
	case WM_START_KEYBOSS:		//设置老板键
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
	//保存配置
	CSystemParameter::GetInstance().SaveOptionParameter();

	__super::OnClose();
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

//光标消息
BOOL CPlatformFrame::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//设置光标
	if (m_bHandCur)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

LRESULT CPlatformFrame::OnHotKeyMessage( WPARAM wParam, LPARAM lParam )
{
	switch (wParam)
	{
	case IDI_HOT_KEY_BOSS:		//老板热键
		{
			//变量定义
			bool bBossCome=(IsWindowVisible()==FALSE)?false:true;

			//隐藏窗口
			if (bBossCome==false)
			{
				//还原窗口
				ShowWindow(SW_RESTORE);
				ShowWindow(SW_SHOW);

				//置顶窗口
				SetActiveWindow();
				BringWindowToTop();
				SetForegroundWindow();
			}
			else
			{
				//隐藏窗口
				ShowWindow(SW_MINIMIZE);
				ShowWindow(SW_HIDE);
			}
			return 0;
		}
	}

	return 0;
}
