// ServerConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerConfig.h"
#include "ServerConfigDlg.h"
#include ".\serverconfigdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CServerConfigDlg 对话框



CServerConfigDlg::CServerConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerConfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CServerConfigDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CServerConfigDlg 消息处理程序

BOOL CServerConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	m_Tab.InsertItem(CFG_SMALLNINE, "小九");
	m_Tab.InsertItem(CFG_PUKNINE, "牌九");
	m_Tab.InsertItem(CFG_30MINI, "30秒");
	m_Tab.SetCurSel(CFG_SMALLNINE);
	OnTcnSelchangeTab1(NULL,NULL);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CServerConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerConfigDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CServerConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerConfigDlg::OnBnClickedOk()
{
	
}

void CServerConfigDlg::OnSaveConfig()
{
	switch(m_Tab.GetCurSel())
	{
	case CFG_SMALLNINE:
		{
			CString buffer;
			GetDlgItemText(IDC_EDIT1, buffer);
			WritePrivateProfileString("Option", "WinRate", buffer.GetBuffer(), ".\\XiaoJiu.ini");

			GetDlgItemText(IDC_EDIT2, buffer);
			WritePrivateProfileString("Option", "MaxLose", buffer.GetBuffer(), ".\\XiaoJiu.ini");

			GetDlgItemText(IDC_EDIT3, buffer);
			WritePrivateProfileString("Option", "PlayMaxWin", buffer.GetBuffer(), ".\\XiaoJiu.ini");

		}
		break;
	case CFG_PUKNINE:
		{
			CString buffer;
			GetDlgItemText(IDC_EDIT1, buffer);
			WritePrivateProfileString("Option", "WinRate", buffer.GetBuffer(), ".\\PaiJiu.ini");

			GetDlgItemText(IDC_EDIT2, buffer);
			WritePrivateProfileString("Option", "MaxLose", buffer.GetBuffer(), ".\\PaiJiu.ini");

			GetDlgItemText(IDC_EDIT3, buffer);
			WritePrivateProfileString("Option", "PlayMaxWin", buffer.GetBuffer(), ".\\PaiJiu.ini");

		}
		break;
	case CFG_30MINI:
		{
			CString buffer;
			GetDlgItemText(IDC_EDIT1, buffer);
			WritePrivateProfileString("Option", "WinRate", buffer.GetBuffer(), ".\\Baccarat.ini");

			GetDlgItemText(IDC_EDIT2, buffer);
			WritePrivateProfileString("Option", "MaxLose", buffer.GetBuffer(), ".\\Baccarat.ini");

			GetDlgItemText(IDC_EDIT3, buffer);
			WritePrivateProfileString("Option", "PlayMaxWin", buffer.GetBuffer(), ".\\Baccarat.ini");
		}
		break;
	}
}

void CServerConfigDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(m_Tab.GetCurSel())
	{
	case CFG_SMALLNINE:
		{
			m_Tab.SetCurSel(CFG_SMALLNINE);

			UINT nWinRate		= GetPrivateProfileInt("Option", "WinRate", 0, ".\\XiaoJiu.ini");
			UINT nMaxLose		= GetPrivateProfileInt("Option", "MaxLose", 0, ".\\XiaoJiu.ini");
			UINT nPlayMaxWin	= GetPrivateProfileInt("Option", "PlayMaxWin", 0, ".\\XiaoJiu.ini");
			
			char szText[MAX_PATH];
			sprintf(szText, "%d", nWinRate);
			SetDlgItemText(IDC_EDIT1, szText);

			sprintf(szText, "%d", nMaxLose);
			SetDlgItemText(IDC_EDIT2, szText);

			sprintf(szText, "%d", nPlayMaxWin);
			SetDlgItemText(IDC_EDIT3, szText);
		}
		break;
	case CFG_PUKNINE:
		{
			m_Tab.SetCurSel(CFG_PUKNINE);

			UINT nWinRate		= GetPrivateProfileInt("Option", "WinRate", 0, ".\\PaiJiu.ini");
			UINT nMaxLose		= GetPrivateProfileInt("Option", "MaxLose", 0, ".\\PaiJiu.ini");
			UINT nPlayMaxWin	= GetPrivateProfileInt("Option", "PlayMaxWin", 0, ".\\PaiJiu.ini");

			char szText[MAX_PATH];
			sprintf(szText, "%d", nWinRate);
			SetDlgItemText(IDC_EDIT1, szText);

			sprintf(szText, "%d", nMaxLose);
			SetDlgItemText(IDC_EDIT2, szText);

			sprintf(szText, "%d", nPlayMaxWin);
			SetDlgItemText(IDC_EDIT3, szText);
		}
		break;
	case CFG_30MINI:
		{
			m_Tab.SetCurSel(CFG_30MINI);

			UINT nWinRate		= GetPrivateProfileInt("Option", "WinRate", 0, ".\\Baccarat.ini");
			UINT nMaxLose		= GetPrivateProfileInt("Option", "MaxLose", 0, ".\\Baccarat.ini");
			UINT nPlayMaxWin	= GetPrivateProfileInt("Option", "PlayMaxWin", 0, ".\\Baccarat.ini");

			char szText[MAX_PATH];
			sprintf(szText, "%d", nWinRate);
			SetDlgItemText(IDC_EDIT1, szText);

			sprintf(szText, "%d", nMaxLose);
			SetDlgItemText(IDC_EDIT2, szText);

			sprintf(szText, "%d", nPlayMaxWin);
			SetDlgItemText(IDC_EDIT3, szText);
		}
		break;
	}
}

void CServerConfigDlg::OnBnClickedButtonSave()
{
	if (IDYES == MessageBox("你确定要保持最新修改吗", NULL, MB_YESNO))
	{
		OnSaveConfig();
	}
}
