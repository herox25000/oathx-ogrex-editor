// GamePlazaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "GamePlazaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGamePlazaDlg 对话框
//屏幕限制
#define LESS_SCREEN_CY				740									//最小高度
#define LESS_SCREEN_CX				1024								//最小宽度
#define MAX_SCREEN_CX               1024                                //最大分辨率
#define MAX_SCREEN_CY               768                                 //最小分辨率  


CGamePlazaDlg::CGamePlazaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGamePlazaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGamePlazaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGamePlazaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CGamePlazaDlg 消息处理程序

BOOL CGamePlazaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	//设置分辨率
	m_ScreenMetrics.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	m_ScreenMetrics.cy = ::GetSystemMetrics(SM_CYSCREEN);

	//设置位置
	CSize SizeRestrict;
	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);

	//窗口位置
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//位置调整
	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);

	//移动窗口
	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
	m_rcNormalSize.right=(rcArce.Width()+SizeRestrict.cx)/2;
	m_rcNormalSize.bottom=(rcArce.Height()+SizeRestrict.cy)/2;
	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGamePlazaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,RGB(0,255,0));  //设置为绿色背景

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CGamePlazaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
