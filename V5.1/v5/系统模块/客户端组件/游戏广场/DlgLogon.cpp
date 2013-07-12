#include "Stdafx.h"
#include "DlgLogon.h"
#include "GamePlaza.h"
#include "MissionLogon.h"
#include ".\dlglogon.h"

//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					7									//圆角宽度
#define ROUND_CY					7									//圆角高度

//屏幕位置
#define LAYERED_SIZE				5									//分层大小
#define CAPTION_SIZE				35									//标题大小

//按钮数目
#define BUTTON_COUNT_CX				5									//横向数目
#define BUTTON_COUNT_CY				4									//竖向数目
#define BUTTON_ITEM_UNDER			0									//按钮底部
#define BUTTON_ITEM_START			12									//按钮开始
#define BUTTON_ITEM_SPACE			16									//按钮间距

//控件标识
#define IDC_WEB_PUBLICIZE			300									//浏览控件
#define IDC_WND_LOGON_BUTTON		301									//按钮控件

//按钮标识
#define INDEX_REGISTER				0									//注册按钮
#define INDEX_USER_HELP				1									//新手帮助
#define INDEX_BUY_SCORE				2									//立即充值
#define INDEX_HOME_PAGE				3									//官方网页

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)

	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//按钮消息
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
	ON_CBN_EDITCHANGE(IDC_ACCOUNTS, OnCbnEditchangeAccounts)

	ON_EN_CHANGE(IDC_ACCOUNTS, OnEnChangeAccounts)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWndLogonButton, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CWndLogonButton::CWndLogonButton()
{
	//活动信息
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//子项信息
	m_SizeButton.SetSize(0,0);

	//加载资源
	CPngImage ImageButton;
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_BUTTON"));
	m_SizeButton.SetSize(ImageButton.GetWidth()/BUTTON_COUNT_CX,ImageButton.GetHeight()/BUTTON_COUNT_CY);

	return;
}

//析构函数
CWndLogonButton::~CWndLogonButton()
{
}

//索引切换
WORD CWndLogonButton::SwitchToButtonIndex(CPoint MousePoint)
{
	//窗口位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//边界判断
	if (MousePoint.x<BUTTON_ITEM_START) return INVALID_WORD;
	if (MousePoint.y>(rcClient.Height()-BUTTON_ITEM_UNDER)) return INVALID_WORD;
	if (MousePoint.y<(rcClient.Height()-m_SizeButton.cy-BUTTON_ITEM_UNDER)) return INVALID_WORD;
	if (MousePoint.x>BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*BUTTON_COUNT_CY) return INVALID_WORD;

	//计算子项
	for (WORD i=0;i<BUTTON_COUNT_CY;i++)
	{
		//位置计算
		CRect rcButton;
		rcButton.bottom=rcClient.Height()-BUTTON_ITEM_UNDER;
		rcButton.top=rcClient.Height()-m_SizeButton.cy-BUTTON_ITEM_UNDER;
		rcButton.left=BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i;
		rcButton.right=BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i+m_SizeButton.cx;

		//区域判断
		if (rcButton.PtInRect(MousePoint)) return i;
	}

	return INVALID_WORD;
}

//重画消息
VOID CWndLogonButton::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建设备
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//加载资源
	//CPngImage ImageLine;
	CPngImage ImageButton;
	CBitImage ImageWndBack;
	//ImageLine.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_LINE"));
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_BUTTON"));
	ImageWndBack.LoadFromResource(AfxGetInstanceHandle(),IDB_WND_LOGON_BACK);

	//绘画背景
	pBufferDC->FillSolidRect(&rcClient,RGB(255,255,255));
	ImageWndBack.BitBlt(BufferDC,(rcClient.Width()-ImageWndBack.GetWidth())/2,(rcClient.Height()-ImageWndBack.GetHeight())/2);

	//绘画横线
	//ImageLine.DrawImage(pBufferDC,(rcClient.Width()-ImageLine.GetWidth())/2,rcClient.Height()-ImageLine.GetHeight());

	//绘画按钮
	for (INT i=0;i<BUTTON_COUNT_CY;i++)
	{
		//变量定义
		INT nXButtomPos=0;
		INT nYButtomPos=i*m_SizeButton.cy;

		//横行计算
		if ((m_wItemHover==i)&&(m_wItemDown!=i)) nXButtomPos=m_SizeButton.cx*2;
		if ((m_wItemActive==i)||(m_wItemDown==i)) nXButtomPos=m_SizeButton.cx;

		//绘画按钮
		INT nYDrawPos=(rcClient.Height()-m_SizeButton.cy)/2;
		INT nXDrawPos=(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i+BUTTON_ITEM_START;
		ImageButton.DrawImage(pBufferDC,nXDrawPos,nYDrawPos,m_SizeButton.cx,m_SizeButton.cy,nXButtomPos,nYButtomPos);
	}

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return;
}

//建立消息
INT CWndLogonButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置变量
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//调整大小
	CBitImage ImageWndBack;
	ImageWndBack.LoadFromResource(AfxGetInstanceHandle(),IDB_WND_LOGON_BACK);
	SetWindowPos(NULL,0,0,ImageWndBack.GetWidth(),ImageWndBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE);

	return 0;
}

//鼠标消息
VOID CWndLogonButton::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//窗口位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//位置计算
	WORD wCollocateHover=SwitchToButtonIndex(Point);

	//盘旋变量
	if (wCollocateHover!=m_wItemHover)
	{
		//设置变量
		m_wItemHover=wCollocateHover;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//进入判断
	if (m_bHovering==false)
	{
		//设置变量
		m_bHovering=true;

		//变量定义
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//注册消息
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//注册事件
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//鼠标消息
VOID CWndLogonButton::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//激活子项
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover==m_wItemDown))
	{
		switch (m_wItemHover)
		{
		case INDEX_REGISTER:	//注册按钮
			{
				//获取窗口
				CWnd * pParentWnd=GetParent();
				pParentWnd->PostMessage(WM_COMMAND,IDC_REGISTER,0);

				break;
			}
		case INDEX_USER_HELP:	//帮助中心
			{
				//构造地址
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/LogonLink1.aspx"),szPlatformLink);

				//打开页面
				ShellExecute(NULL,TEXT("OPEN"),szBrowseUrl,NULL,NULL,SW_NORMAL);

				break;
			}
		case INDEX_BUY_SCORE:	//立即充值
			{
				//构造地址
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/LogonLink2.aspx"),szPlatformLink);

				//打开页面
				ShellExecute(NULL,TEXT("OPEN"),szBrowseUrl,NULL,NULL,SW_NORMAL);

				break;
			}
		case INDEX_HOME_PAGE:	//进入官网
			{
				//打开页面
				ShellExecute(NULL,TEXT("OPEN"),szPlatformLink,NULL,NULL,SW_NORMAL);

				break;
			}
		}
	}

	//按起处理
	if (m_wItemDown!=INVALID_WORD)
	{
		//释放鼠标
		ReleaseCapture();

		//设置变量
		m_wItemDown=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//鼠标消息
VOID CWndLogonButton::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//设置焦点
	SetFocus();

	//按下处理
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover!=m_wItemActive))
	{
		//鼠标扑获
		SetCapture();

		//设置变量
		m_wItemDown=m_wItemHover;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//鼠标消息
LRESULT CWndLogonButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (m_bHovering==true)
	{
		//设置变量
		m_bHovering=false;
		m_wItemHover=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//光标消息
BOOL CWndLogonButton::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//设置光标
	if (m_wItemHover!=INVALID_WORD)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CControlCheckButton::CControlCheckButton()
{
	//设置变量
	m_cbChecked=FALSE;
	m_pParentSink=NULL;

	//加载资源
	m_ImageBtnBack.LoadFromResource(AfxGetResourceHandle(),IDB_CHECK_BUTTON_BACK);
}

//析构函数
CControlCheckButton::~CControlCheckButton()
{
}

//控件区域
CRect CControlCheckButton::GetControlRect()
{
	CRect rcClient(m_ptControlBenchmark.x,m_ptControlBenchmark.y,m_ptControlBenchmark.x+m_ImageBtnBack.GetWidth()/2,m_ptControlBenchmark.y+m_ImageBtnBack.GetHeight());

	return rcClient;
}

//设置状态
VOID  CControlCheckButton::SetButtonChecked(BYTE cbChecked) 
{ 
	//设置变量
	m_cbChecked=cbChecked;

	//定义变量
	CRect rcClient = GetControlRect();

	//重绘界面
	if(m_pParentSink!=NULL) m_pParentSink->InvalidateRect(&rcClient);
};

//绘制控件
VOID  CControlCheckButton::OnDrawControl(CDC * pDC)
{
	//参数校验
	if(pDC==NULL) return;

	//定义变量
	INT nImageWidth = m_ImageBtnBack.GetWidth()/2;
	INT nImageHeight = m_ImageBtnBack.GetHeight();
    
    //绘制背景
	m_ImageBtnBack.BitBlt(*pDC,m_ptControlBenchmark.x,m_ptControlBenchmark.y,nImageWidth,nImageHeight,m_cbChecked==TRUE?nImageWidth:0,0);
}

//点击事件
VOID  CControlCheckButton::OnClickControl(CPoint Point)
{
	//定义变量
	CRect rcClient = GetControlRect();

	//选中判断
	if(rcClient.PtInRect(Point))
	{
		//设置变量
		m_cbChecked=m_cbChecked==FALSE?TRUE:FALSE;

		//重绘界面
		if(m_pParentSink!=NULL)	m_pParentSink->InvalidateRect(&rcClient);
	}
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLogon::CDlgLogon() : CDialog(IDD_DLG_LOGON)
{
	//登录信息
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLogonServer[0]=0;

	//创建画刷
	m_brBrush.CreateSolidBrush(RGB(215,223,228));

	return;
}

//析构函数
CDlgLogon::~CDlgLogon()
{
	//销毁资源
	if (m_brBrush.GetSafeHandle()!=NULL)
	{
		m_brBrush.DeleteObject();
	}

	return;
}

//控件绑定
VOID CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//绑定控件
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDCANCEL, m_btQuit);

	//绑定控件
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_LOGON_SERVER, m_ServerControl);
}

//创建函数
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("用户登录 -- Version 6603"));
	
	//加载资源
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));

	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//边框设置
	m_ServerControl.SetDrawBorad(false);
	m_PasswordControl.SetDrawBorad(false);
	m_PasswordControl.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btQuit.SetButtonImage(IDB_BT_LOGON_QUIT,hInstance,false,false);
	m_btEnter.SetButtonImage(IDB_BT_LOGON,TEXT("BT_LOGON_ENTER"),hInstance,false,false);

	//创建控件
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	//创建控件
	CRect rcWndButton(20,273,411,305);
	m_WndLogonButton.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcWndButton,this,IDC_WND_LOGON_BUTTON);

	//变量定义
	CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
	ASSERT(pGlobalUnits!=NULL);

	//记住密码
	m_RemPwdControl.SetControlBenchmark(107,246);
	m_RemPwdControl.SetParentWndSink(this);

	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//构造地址
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s\\Web\\LobbyTopNotice.htm"),szDirectory);

	//设置广告
	if(pGlobalUnits!=NULL && pGlobalUnits->LocalFileExist(szBillUrl))
	{
		m_PlatformPublicize.Navigate(szBillUrl);
		m_PlatformPublicize.SetWindowPos(NULL,36,9,SizeWindow.cx-71,18,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
	}
	else
		m_PlatformPublicize.SetWindowPos(NULL,36,9,SizeWindow.cx-71,18,SWP_HIDEWINDOW|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);


	//配置信息
	LoadAccountsInfo();
	LoadLogonServerInfo();

	//居中窗口
	CenterWindow(this);

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//分层窗口
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);

	return FALSE;
}

//消息解释
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//确定函数
VOID CDlgLogon::OnOK()
{
	//获取信息
	if (GetInformation()==false) return;

	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//隐藏窗口
	ShowWindow(SW_HIDE);

	//执行登录
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_RemPwdControl.GetButtonChecked()==TRUE);

	return;
}

//取消消息
VOID CDlgLogon::OnCancel()
{
	//关闭窗口
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

	return;
}

//构造数据
WORD CDlgLogon::ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize)
{
	//变量定义
	CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts *)cbBuffer;

	//其他信息
	CWHService::GetMachineIDEx(pLogonAccounts->szMachineID);
	CWHEncrypt::MD5Encrypt(m_szPassword,pLogonAccounts->szPassword);

	//登录信息
	pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;
	lstrcpyn(pLogonAccounts->szAccounts,m_szAccounts,CountArray(pLogonAccounts->szAccounts));

	//保存密码
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	lstrcpyn(pGlobalUserData->szPassword,pLogonAccounts->szPassword,CountArray(pGlobalUserData->szPassword));

	return sizeof(CMD_GP_LogonAccounts);
}

//加载账号
VOID CDlgLogon::LoadAccountsInfo()
{
	//读取信息
	CWHRegKey RegUserInfo;
	if (RegUserInfo.OpenRegKey(REG_USER_INFO,false)==false) return;

	//变量定义
	DWORD dwLastUserID=RegUserInfo.GetValue(TEXT("LastUserID"),0L);

	//读取信息
	if (dwLastUserID!=0L)
	{
		//读取键项
		TCHAR szKeyItemName[16]=TEXT("");
		_sntprintf(szKeyItemName,CountArray(szKeyItemName),TEXT("%s\\%ld"),REG_USER_INFO,dwLastUserID);

		//打开子键
		CWHRegKey RegUserItem;
		if (RegUserItem.OpenRegKey(szKeyItemName,false)==true)
		{
			//帐户信息
			TCHAR szAccounts[LEN_ACCOUNTS]=TEXT("");
			RegUserItem.GetString(TEXT("UserAccount"),szAccounts,CountArray(szAccounts));

			//读取密码
			TCHAR szPasswordDes[LEN_PASSWORD]=TEXT("");
			TCHAR szPasswordSrc[MAX_ENCRYPT_LEN]=TEXT("");
			RegUserItem.GetString(TEXT("UserPassword"),szPasswordSrc,CountArray(szPasswordSrc));

			//解开密码
			if (szPasswordSrc[0]!=0)
			{
				CWHEncrypt::XorCrevasse(szPasswordSrc,szPasswordDes,CountArray(szPasswordDes));
			}

			//设置控件
			m_edAccounts.SetWindowText(szAccounts);
			m_PasswordControl.SetUserPassword(szPasswordDes);

			//记住密码
			if (szPasswordDes[0]!=0)
			{
				m_RemPwdControl.SetButtonChecked(TRUE);
			}
		}
	}

	return;
}

//地址信息
VOID CDlgLogon::LoadLogonServerInfo()
{
	//读取数目
	CGlobalServer GlobalServer;
	WORD wItemCount=GlobalServer.GetItemCount();
	INT nIndex=0;

	//上次登录
	TCHAR szLastServer[LEN_SERVER]=TEXT("");
	GlobalServer.GetLastServerName(szLastServer);

	//读取信息
	for (WORD i=0;i<wItemCount;i++)
	{
		//读取信息
		TCHAR szServerItem[LEN_SERVER]=TEXT("");
		GlobalServer.GetServerItemName(i,szServerItem);

		//插入信息
		if (szServerItem[0]!=0)
		{
			//插入信息
			INT nItem=m_ServerControl.AddString(szServerItem);

			//最近登录
			if ((szLastServer[0]!=0)&&(lstrcmp(szLastServer,szServerItem)==0))
			{
				szLastServer[0]=0;
				m_ServerControl.SetCurSel(nItem);
			}
		}
	}

	//最近登录
	if (szLastServer[0]!=0)
	{
		m_ServerControl.SetCurSel(m_ServerControl.AddString(szLastServer));
	}

	//设置选择
	if (m_ServerControl.GetCurSel()==LB_ERR)
	{
		if (m_ServerControl.GetCount()==0L)
		{
			m_ServerControl.SetCurSel(m_ServerControl.AddString(szLogonServer));
		}
		else
		{
			m_ServerControl.SetCurSel(0);
		}
	}

	return;
}

//获取信息
bool CDlgLogon::GetInformation()
{
	//获取密码
	m_PasswordControl.GetUserPassword(m_szPassword);

	//获取信息
	GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	GetDlgItemText(IDC_LOGON_SERVER,m_szLogonServer,CountArray(m_szLogonServer));

	//地址判断
	if (m_szLogonServer[0]==0L)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请选择“登录服务器”后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_ServerControl.SetFocus();

		return false;
	}

	//帐号判断
	if (m_szAccounts[0]==0L)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请您输入帐号后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_edAccounts.SetFocus();

		return false;
	}

	//密码判断
	if (m_szPassword[0]==0)
	{
		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("请您输入密码后再登录，若有困难请点击“新手指南”获取帮助！"),MB_ICONERROR,0);

		//显示窗口
		ShowWindow(SW_SHOW);

		//设置焦点
		m_PasswordControl.SetFocus();

		return false;
	}

	return true;
}

//注册帐号
VOID CDlgLogon::OnBnClickedRegister()
{
	//隐藏窗口
	ShowWindow(SW_HIDE);

	//获取地址
	CString strLogonServer;
	GetDlgItemText(IDC_LOGON_SERVER,strLogonServer);

	//构造地址
	strLogonServer.TrimLeft();
	strLogonServer.TrimRight();
	lstrcpyn(m_szLogonServer,(strLogonServer.IsEmpty()==true)?szLogonServer:strLogonServer,CountArray(m_szLogonServer));

	//显示注册
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowRegister();

	return;
}

//编辑改变
VOID CDlgLogon::OnCbnEditchangeAccounts()
{
	//安全设置
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);

	//密码重置
	if (m_PasswordControl.IsFalsityPassword()==true) m_PasswordControl.SetUserPassword(NULL);

	return;
}

//绘画背景
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//设置缓冲
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//加载资源
	CPngImage ImageBack;
	CBitImage ImageNotice;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	ImageNotice.LoadFromResource(AfxGetInstanceHandle(),IDB_LOGON_NOTICE);

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	ImageNotice.BitBlt(*pBufferDC,10,35,410,100,0,0,SRCCOPY);

	//绘制控件
	m_RemPwdControl.OnDrawControl(pBufferDC);

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//显示消息
VOID CDlgLogon::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//鼠标消息
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟标题
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//位置改变
VOID CDlgLogon::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//控件颜色
HBRUSH CDlgLogon::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(10,10,10));
			return m_brBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//控件改变
void CDlgLogon::OnEnChangeAccounts()
{
	//虚假密码
	if(m_PasswordControl.m_hWnd!=NULL && m_PasswordControl.IsFalsityPassword()==true)
	{
		//密码设置
		m_PasswordControl.SetUserPassword(TEXT(""));

        //安全设置
		m_RemPwdControl.SetButtonChecked(FALSE);
	}
}

//鼠标弹起
void CDlgLogon::OnLButtonUp(UINT nFlags, CPoint point)
{
	//选中事件
	m_RemPwdControl.OnClickControl(point);

	CDialog::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////////////



