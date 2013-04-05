// SmallNineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallNine.h"
#include "SmallNineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

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


CSmallNineDlg::CSmallNineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmallNineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmallNineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_AndroidListView);
	DDX_Control(pDX, IDC_RICHEDIT21, m_AndroidLog);
}

BEGIN_MESSAGE_MAP(CSmallNineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSmallNineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


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

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	static const char*	chColumnName[] = 
	{
		"UserID",
		"GameID",
		"当前金钱",
		"输赢金钱",
		"做庄次数",
		"工作状态",
		"登录时间",
		"已在线时间",
	};

	for (int i=0; i<8; i++)
	{
		m_AndroidListView.InsertColumn(i, chColumnName[i],	LVCFMT_CENTER,	100 );
	}

	return TRUE; 
}

void CSmallNineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSmallNineDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CSmallNineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
