#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

//控制按钮
#define IDC_BT_FRAME_MIN					100									//最小按钮
#define IDC_BT_FRAME_CLOSE					101									//关闭按钮

//圆角大小
#define ROUND_CX					7									//圆角宽度
#define ROUND_CY					7									//圆角高度

//阴影定义
#define SHADOW_CX					0									//阴影宽度
#define SHADOW_CY					0									//阴影高度

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
	//显示窗口
	ShowWindow(SW_SHOW);
	SetForegroundWindow();
	//启动登陆窗口
	//SendLogonMessage();
	m_pGamePage.Create(0, CRect(250, 260, 500, 500), this);
	m_pGamePage.ShowWindow(SW_SHOW);
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
bool __cdecl CPlatformFrame::SendLogonMessage()
{
	PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
	return true;
}

//连接消息
bool __cdecl CPlatformFrame::SendConnectMessage()
{
	PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return true;
}

//启动登陆窗口
void CPlatformFrame::OnCommandLogon()
{
	//创建登录框
	if (m_DlgLogon.m_hWnd==NULL) 
	{
		m_DlgLogon.Create(IDD_LOGON,this);
	}
	//显示登录框
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.SetForegroundWindow();

	return;
}

//连接服务器
void CPlatformFrame::OnCommandConnect()
{
	////创建组件
	//if (m_ClientSocket.GetInterface()==NULL)
	//{
	//	try
	//	{
	//		IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
	//		if (m_ClientSocket.CreateInstance()==false) 
	//		{
	//			throw TEXT("网络组件创建失败");
	//		}
	//		if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) 
	//		{
	//			throw TEXT("网络组件回调接口设置失败");
	//		}
	//	}
	//	catch (...)
	//	{
	//		ShowMessageBox(TEXT("网络组件创建失败，请重新下载游戏大厅！"),MB_ICONSTOP);
	//		PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
	//		return;
	//	}
	//}

	////地址解释
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

	////连接服务器
	//try
	//{
	//	//连接服务器
	//	m_ClientSocket->CloseSocket();

	//	//代理判断
	//	if ( m_DlgLogon.EnableProxy() == true )
	//	{
	//		//获取代理
	//		enProxyServerType ProxyServerType;
	//		tagProxyServerInfo ProxyServerInfo;
	//		m_DlgLogon.GetProxyInfo(ProxyServerType, ProxyServerInfo);	

	//		//设置代理
	//		m_ClientSocket->SetProxyServerInfo(ProxyServerType,ProxyServerInfo);
	//	}

	//	if (m_ClientSocket->Connect(pszServerIP,PORT_LOGON_SERVER)!=CONNECT_SUCCESS)
	//	{
	//		throw TEXT("服务器连接错误，可能是你的系统还没有成功连接上网络！");
	//	}
	//}
	//catch (LPCTSTR pszError)
	//{
	//	ShowMessageBox(pszError,MB_ICONINFORMATION);
	//	SendLogonMessage();
	//	return;
	//}

	////显示提示框
	//CString strMessage=TEXT("正在连接服务器，请稍候...");
	//g_GlobalAttemper.ShowStatusMessage(strMessage,this);

	return;
}

//取消连接
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
	//调整判断
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX, SHADOW_CY, nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//设置区域
		SetWindowRgn(RegionWindow,TRUE);
	}

	return TRUE;
}

//加载按钮
void CPlatformFrame::LoadButtons()
{
	m_btMin.CreateButton(this, "PNG_BT_FRAME_MIN", _T("PNG"), LESS_SCREEN_CX-86, 3, IDC_BT_FRAME_MIN, 5);
	m_btClose.CreateButton(this, "PNG_BT_FRAME_CLOSE", _T("PNG"), LESS_SCREEN_CX-38, 3, IDC_BT_FRAME_CLOSE, 5);
}

//加载图片资源
void CPlatformFrame::LoadImages()
{
	m_ImageHead.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_HEAD"));
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_PLAZA"));
}

BOOL CPlatformFrame::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	m_ImageHead.DrawImage(pDevC, 0, 0);
	m_ImageBack.DrawImage(pDevC,0,147);
	SetButtonBackGrounds(pDevC);
	return TRUE;
}

//按钮背景绘制
void CPlatformFrame::SetButtonBackGrounds(CDC *pDC)
{
	m_btMin.SetBkGnd(pDC);
	m_btClose.SetBkGnd(pDC);
}

//鼠标消息
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟按标题
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

BOOL CPlatformFrame::OnCommand( WPARAM wParam, LPARAM lParam )
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);
	switch (nCommandID)
	{
	case IDC_BT_FRAME_MIN:				//最小按钮
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_BT_FRAME_CLOSE:				//关闭按钮
		{
			PostMessage(WM_CLOSE,0,0);
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
	}

	return FALSE;

}

VOID CPlatformFrame::OnClose()
{
	__super::OnClose();
}
