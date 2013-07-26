#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

//控制按钮
#define IDC_BT_FRAME_MIN					100							//最小按钮
#define IDC_BT_FRAME_CLOSE					101							//关闭按钮

#define IDC_BT_GAME							102							//游戏专区
#define IDC_BT_MATCH						103							//比赛专区
#define IDC_BT_PROPERTY						104							//道具商城
#define IDC_BT_PRIZE						105							//奖品中心
#define IDC_BT_RECHARGE						106							//充值中心

#define IDC_BT_REFLASH						107							//信息刷新
#define IDC_BT_USERINFOSET					108							//个人设置
#define IDC_BT_RETURN						109							//返回
#define IDC_BT_LOBBYSET						110							//大厅设置

#define IDC_BT_USERBAG						111							//角色背包
#define IDC_BT_SQUARE						112							
#define IDC_BT_TILL							113
#define IDC_BT_IM							114

//阴影定义
#define SHADOW_CX							0							//阴影宽度
#define SHADOW_CY							0							//阴影高度

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

	SetFrameSize(LESS_SCREEN_CX, LESS_SCREEN_CY);
	LoadImages();
	LoadButtons();
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(), rcClient.Height());
	
	//启动登陆窗口
	m_DlgLogon.SetPlatFormPointer(this);
	m_PlatformSocket.SetDlgLogonPointer(&m_DlgLogon);
	m_PlatformSocket.SetPlatFormPointer(this);
	OnCommandLogon();
	g_GlobalUnits.m_ServerListManager.InitServerListManager(NULL);
	//m_GamePage.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(250, 260, 250+176*3, 260+140*3), this, 10001);
	//m_GamePage.Create(3, 3, NULL, CRect(250, 260, 250+176*3, 260+140*3), this, 0);
	m_ZonePage.Create(0, CRect(250, 206, 250+176*3, 260+140*3), this);
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
		m_DlgLogon.Create(IDD_LOGON,this);
	}
	//显示登录框
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.BringWindowToTop();
	m_DlgLogon.SetForegroundWindow();
	return;
}

//打开大厅设置
void CPlatformFrame::OnOpenFrameSet()
{
	//创建登录框
	if (m_DlgFrameSet.m_hWnd == NULL) 
	{
		m_DlgFrameSet.Create(IDD_FRAMESET, this);
	}
	//显示登录框
	m_DlgFrameSet.ShowWindow(SW_SHOW);
	m_DlgFrameSet.SetActiveWindow();
	m_DlgFrameSet.SetForegroundWindow();
	return;
}

//处理关闭大厅
void CPlatformFrame::OnClosePlatForm()
{
	//显示窗口
	CDlgEnquire DlgEnquire;
	INT_PTR nResult=DlgEnquire.DoModal();
	switch (nResult)
	{
	case WM_BT_CLOSE_PLAZA:
		{
			PostMessage(WM_CLOSE,0,0);
			break;
		}
	case WM_BT_SWITCH_ACCOUNTS:	//切换帐号
		{
			//删除记录
			g_GlobalUnits.DeleteUserCookie();
			tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
			memset(&GlobalUserData,0,sizeof(GlobalUserData));
			OnCommandLogon();
			break;
		}
	}
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
	m_LobbySet.CreateButton(this, "PNG_LOBBY_SET", _T("PNG"), LESS_SCREEN_CX - 116, 3, IDC_BT_LOBBYSET, 4);
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

	m_btSquare.EnableWindow(FALSE);
	m_btIm.EnableWindow(FALSE);
}

//加载图片资源
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

//按钮背景绘制
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

//绘制角色信息
void CPlatformFrame::DrawUserInfo( CDC *pDC )
{
	tagGlobalUserData& UserData = g_GlobalUnits.GetGolbalUserData();
	if (UserData.dwUserID!=0L)
	{
		int nHeadNumberWidth	= m_UserHead.GetWidth() / 2;
		int nHeadNumberHeight	= m_UserHead.GetHeight(); 
		//输出头像
		if (UserData.cbGender)
		{
			m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, 0, 0);
		}
		else
		{
			m_UserHead.DrawImage(pDC, 28, 190, nHeadNumberWidth, nHeadNumberHeight, nHeadNumberWidth, 0);
		}

		//输出帐号
		CRect rcAccounts;
		rcAccounts.SetRect(66, 344, 166,360);
		pDC->DrawText(UserData.szAccounts,lstrlen(UserData.szAccounts),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}
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
			OnClosePlatForm();
			return TRUE;
		}
	case IDC_BT_LOBBYSET:				//打开大厅设置
		{
			OnOpenFrameSet();
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

void CPlatformFrame::SaveBossKey( int nCtrlKey, int nHelpKey )
{
	
}
