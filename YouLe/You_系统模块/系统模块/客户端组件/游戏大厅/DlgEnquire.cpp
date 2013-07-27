#include "Stdafx.h"
#include "DlgEnquire.h"
#include "GlobalUnits.h"


//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					5									//圆角宽度
#define ROUND_CY					5									//圆角高度

//屏幕位置
#define LAYERED_SIZE				15									//分层大小


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgEnquire, CDialog)

	//系统消息
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//按钮消息
	ON_BN_CLICKED(WM_BT_CLOSE,OnCancel)
	ON_BN_CLICKED(WM_BT_QUITE,OnCancel)
	ON_BN_CLICKED(WM_BT_CLOSE_PLAZA, OnBnClickedClosePlaza)
	ON_BN_CLICKED(WM_BT_SWITCH_ACCOUNTS, OnBnClickedSwitchAccounts)

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
}

//配置函数
BOOL CDlgEnquire::OnInitDialog()
{
	__super::OnInitDialog();
	//加载资源
	tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
	HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszEnquireBack);
	//设置大小
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	m_btCancel.CreateButton(this, PlazaViewImage.pszEnquireCancel, _T("PNG"),m_ImageBack.GetWidth()-50,15,WM_BT_CLOSE,4, hInstance);
	m_btClosePlaza.CreateButton(this, PlazaViewImage.pszEnquirePlaza, _T("PNG"),
		m_ImageBack.GetWidth()-160,m_ImageBack.GetHeight()-70,WM_BT_CLOSE_PLAZA, 4, hInstance);
	m_btSwitchAccounts.CreateButton(this, PlazaViewImage.pszEnquireSwitch, _T("PNG"),
		30,m_ImageBack.GetHeight()-70,WM_BT_SWITCH_ACCOUNTS,4, hInstance);
	//m_btQuite.CreateButton(this,TEXT("BT_ENQUIRE_QUITE"),_T("PNG"),
	//	m_ImageBack.GetWidth()-50,m_ImageBack.GetHeight()-100,WM_BT_QUITE,4);
	//居中窗口
	CenterWindow(this);
	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	SetWindowRgn(RgnWindow,FALSE);

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
	CMemDC pDevDC(pDC,rcClient);
	//绘画背景
	m_ImageBack.DrawImage(pDevDC,0,0);

	m_btCancel.SetBkGnd(pDevDC);
	m_btClosePlaza.SetBkGnd(pDevDC);
	m_btSwitchAccounts.SetBkGnd(pDevDC);
	//m_btQuite.SetBkGnd(pDevDC);
	return TRUE;
}

//显示消息
VOID CDlgEnquire::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

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

	return;
}

//关闭大厅
VOID CDlgEnquire::OnBnClickedClosePlaza()
{
	EndDialog(WM_BT_CLOSE_PLAZA);

	return;
}

//关闭房间
VOID CDlgEnquire::OnBnClickedCloseServer()
{
	//EndDialog(IDC_CLOSE_SERVER);

	return;
}

//切换帐号
VOID CDlgEnquire::OnBnClickedSwitchAccounts()
{
	EndDialog(WM_BT_SWITCH_ACCOUNTS);

	return;
}

//////////////////////////////////////////////////////////////////////////////////
