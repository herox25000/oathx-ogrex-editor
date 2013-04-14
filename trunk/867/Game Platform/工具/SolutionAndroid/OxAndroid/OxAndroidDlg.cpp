#include "stdafx.h"
#include "OxAndroid.h"
#include "OxAndroidDlg.h"
#include "AndroidTimer.h"
#include ".\oxandroiddlg.h"


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


COxAndroidDlg::COxAndroidDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COxAndroidDlg::IDD, pParent)
{
	m_hIcon				= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_fElapsed			= 0;
	m_fLostTime			= 0;
	m_pAndroidManager	= NULL;
}

void COxAndroidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COxAndroidDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()

#define IDT_ANDROID_UPDATE	1

BOOL COxAndroidDlg::OnInitDialog()
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

	

	return TRUE;
}

void COxAndroidDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COxAndroidDlg::OnPaint() 
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

HCURSOR COxAndroidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COxAndroidDlg::OnBnClickedOk()
{
	if (m_pAndroidManager == NULL)
	{
		m_pOx4Factory		= new O2::Ox4Factory(0);
		m_pAndroidManager	= new O2::AndroidManager(100, 200, 10, "192.168.1.102", 12061, "d746e3733dff946b0db30eb3fb0069c4", m_pOx4Factory);
	}
	
	SetTimer(IDT_ANDROID_UPDATE, 30, NULL);
}

void COxAndroidDlg::OnTimer(UINT nIDEvent)
{
	switch( IDT_ANDROID_UPDATE )
	{
	case IDT_ANDROID_UPDATE:
		{
			double fCurrentTime = O2::AndroidTimer::GetSingleton().GetElapsed();
			double fElapsed		= fCurrentTime - m_fLostTime;

			O2::AndroidManager::GetSingleton()->Update(fElapsed);

			m_fLostTime = fCurrentTime;
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void COxAndroidDlg::OnCancel()
{
	delete m_pOx4Factory;
	delete m_pAndroidManager;

	CDialog::OnCancel();
}
