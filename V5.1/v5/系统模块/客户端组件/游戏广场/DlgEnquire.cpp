#include "Stdafx.h"
#include "DlgEnquire.h"
#include "GlobalUnits.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					5									//圆角宽度
#define ROUND_CY					5									//圆角高度

//屏幕位置
#define LAYERED_SIZE				5									//分层大小
#define CAPTION_SIZE				60									//标题大小

//控件标识
#define IDC_WEB_PUBLICIZE			300									//浏览控件

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgEnquire, CDialog)

	//系统消息
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//按钮消息
	ON_BN_CLICKED(IDC_CLOSE_PLAZA, OnBnClickedClosePlaza)
	ON_BN_CLICKED(IDC_CLOSE_SERVER, OnBnClickedCloseServer)
	ON_BN_CLICKED(IDC_SWITCH_ACCOUNTS, OnBnClickedSwitchAccounts)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgEnquire::CDlgEnquire() : CDialog(IDD_DLG_ENQUIRE)
{
}

//析构函数
CDlgEnquire::~CDlgEnquire()
{
}

//控件绑定
VOID CDlgEnquire::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//按钮控件
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_CLOSE_PLAZA, m_btClosePlaza);
	DDX_Control(pDX, IDC_CLOSE_SERVER, m_btCloseServer);
	DDX_Control(pDX, IDC_SWITCH_ACCOUNTS, m_btSwitchAccounts);
}

//配置函数
BOOL CDlgEnquire::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("温馨提示"));

	//加载资源
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_ENQUIRE_BACK"));

	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//控制按钮
	CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
	//m_btCloseServer.EnableWindow((pPlatformFrame->GetActiveItem()>=1)?TRUE:FALSE);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btCancel.SetButtonImage(IDB_BT_ENQUIRE_CANCEL,hInstance,false,false);
	m_btClosePlaza.SetButtonImage(IDB_BT_ENQUIRE_PLAZA,hInstance,false,false);
	m_btCloseServer.SetButtonImage(IDB_BT_ENQUIRE_SERVER,hInstance,false,false);
	m_btSwitchAccounts.SetButtonImage(IDB_BT_ENQUIRE_SWITCH,hInstance,false,false);

	//关闭按钮
	CRect rcCancel;
	m_btCancel.GetWindowRect(&rcCancel);
	m_btCancel.SetWindowPos(NULL,SizeWindow.cx-rcCancel.Width()-8,3,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);

	//按钮大小
	CRect rcButton;
	m_btClosePlaza.GetWindowRect(&rcButton);

	//功能按钮
	INT nButtonSpace=(SizeWindow.cx-rcButton.Width()*3-2*LAYERED_SIZE)/4;
	m_btClosePlaza.SetWindowPos(NULL,LAYERED_SIZE+nButtonSpace*3+rcButton.Width()*2,158,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);
	m_btCloseServer.SetWindowPos(NULL,LAYERED_SIZE+nButtonSpace*2+rcButton.Width()*1,158,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);
	m_btSwitchAccounts.SetWindowPos(NULL,LAYERED_SIZE+nButtonSpace*1+rcButton.Width()*0,158,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);

	//广告控件
	CRect rcCreate(0,0,0,0);
	//m_PlatformPublicize.SetBackColor(RGB(19,69,103));
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	//变量定义
	CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
	ASSERT(pGlobalUnits!=NULL);

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
		m_PlatformPublicize.SetWindowPos(NULL,50,9,SizeWindow.cx-100,18,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
	}
	else
		m_PlatformPublicize.SetWindowPos(NULL,50,9,SizeWindow.cx-100,18,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_HIDEWINDOW|SWP_NOACTIVATE);


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

//确定函数
VOID CDlgEnquire::OnOK()
{
	return;
}

//绘画背景
BOOL CDlgEnquire::OnEraseBkgnd(CDC * pDC)
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
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_ENQUIRE_BACK"));

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//显示消息
VOID CDlgEnquire::OnShowWindow(BOOL bShow, UINT nStatus)
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
VOID CDlgEnquire::OnLButtonDown(UINT nFlags, CPoint Point)
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
VOID CDlgEnquire::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//关闭大厅
VOID CDlgEnquire::OnBnClickedClosePlaza()
{
	EndDialog(IDC_CLOSE_PLAZA);

	return;
}

//关闭房间
VOID CDlgEnquire::OnBnClickedCloseServer()
{
	EndDialog(IDC_CLOSE_SERVER);

	return;
}

//切换帐号
VOID CDlgEnquire::OnBnClickedSwitchAccounts()
{
	EndDialog(IDC_SWITCH_ACCOUNTS);

	return;
}

//////////////////////////////////////////////////////////////////////////////////
