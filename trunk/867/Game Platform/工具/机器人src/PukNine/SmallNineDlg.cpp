#include "stdafx.h"
#include "SmallNine.h"
#include "SmallNineDlg.h"
#include ".\smallninedlg.h"
#include "SmallNineMachineFactory.h"

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

#define SMALLNINE_NAME			"SmallNineMachineFactory"

CSmallNineDlg::CSmallNineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmallNineDlg::IDD, pParent)
{
	m_hIcon			= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_fLostTime		= 0;
	m_fCrateTime	= RobotTimer::rdft(1, 5);
	m_fElapsed		= 0;
	m_dwStartID		= 0;
	m_dwEndID		= 0;
	m_wPort			= 0;
	
	memset(&m_AppConfig, 0, sizeof(SBankerConfig));

	RobotManager::GetSingleton().RegisterRobotFactory( 
		new SmallNineMachineFactory(SMALLNINE_NAME)
		);
}

void CSmallNineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditTrace);
}

BEGIN_MESSAGE_MAP(CSmallNineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT6, OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT5, OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT17, OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnEnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, OnEnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, OnEnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT28, OnEnChangeEdit28)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
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

	m_RobotDialog.Create(IDD_DIALOG_ROBOT, this);

	SetDlgItemText(IDC_EDIT1,	"125.90.64.21");
	SetDlgItemText(IDC_EDIT2,	"11011");
	SetDlgItemText(IDC_EDIT3,	"d746e3733dff946b0db30eb3fb0069c4");
	SetDlgItemText(IDC_EDIT4,	"241");
	SetDlgItemText(IDC_EDIT5,	"440");
	SetDlgItemText(IDC_EDIT6,	"80000000");
	SetDlgItemText(IDC_EDIT7,	"1");
	SetDlgItemText(IDC_EDIT8,	"1");

	SetDlgItemText(IDC_EDIT9,	"5");
	SetDlgItemText(IDC_EDIT10,	"1");
	SetDlgItemText(IDC_EDIT11,	"30000000");
	SetDlgItemText(IDC_EDIT12,	"100000");

	SetDlgItemText(IDC_EDIT13,	"20000000");
	SetDlgItemText(IDC_EDIT14,	"10000000");
	SetDlgItemText(IDC_EDIT15,	"20000000");
	SetDlgItemText(IDC_EDIT16,	"10000000");
	SetDlgItemText(IDC_EDIT17,	"10");
	SetDlgItemText(IDC_EDIT18,	"10");
	SetDlgItemText(IDC_EDIT19,	"20");

	SetDlgItemText(IDC_EDIT20,	"1");
	SetDlgItemText(IDC_EDIT21,	"3");

	SetDlgItemText(IDC_EDIT22,  "10");
	SetDlgItemText(IDC_EDIT23,  "10");
	SetDlgItemText(IDC_EDIT24,  "10");
	SetDlgItemText(IDC_EDIT25,  "5");
	SetDlgItemText(IDC_EDIT26,  "5");
	SetDlgItemText(IDC_EDIT27,  "2");

	SetDlgItemText(IDC_EDIT28,  "50000000");

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

void	CSmallNineDlg::OnTimer(UINT nIDEvent)
{
	switch( nIDEvent )
	{
	case IDT_TIMER_RECONNECT:
		{
			 RobotManager::GetSingleton().Reconnect(m_ipAddress, m_wPort, m_md5);
		}
		break;

	case IDT_TIMER_UPDATE:
		{
			double fCurrentTime = RobotTimer::GetSingleton().GetElapsed();
			double fElapsed		= fCurrentTime - m_fLostTime;

			m_fElapsed			+= fElapsed;

			int nCount = RobotManager::GetSingleton().GetRobotCount();
			if ( nCount < m_dwMaxCount)
			{
				if ( m_fElapsed >= m_fCrateTime)
				{
					// 随机机器人ID
					DWORD dwUserID	= RobotTimer::rdit(m_dwStartID, m_dwEndID);

					// 如果该机器人不存在，那么创建该机器人
					if (NULL == RobotManager::GetSingleton().Search(dwUserID))
					{
						IRobotFactory* pFactory = RobotManager::GetSingleton().GetRobotFactory(SMALLNINE_NAME);
						if (pFactory)
						{
							SmallNineMachine* pMachine = static_cast<SmallNineMachine*>(
								pFactory->Create(dwUserID)
								);
							if (pMachine)
							{
								pMachine->SetOnlineTime(RobotTimer::rdit(m_AppConfig.fMinOnlineTime, 
									m_AppConfig.fMaxOnlineTime));

								if (pMachine->Start(m_ipAddress, m_wPort, m_md5))
								{
									RobotManager::GetSingleton().AddRobot(pMachine);
								}
								else
								{
									delete pMachine;
									pMachine = NULL;
								}

								m_fCrateTime = RobotTimer::rdft(1, 20);
							}
						}
					}

					m_fElapsed = 0;
				}
			}
			
			if (nCount)
			{
				CString szMessage;
				szMessage.Format("%d", nCount);
				SetDlgItemText(IDC_STATIC_COUNT, szMessage);

				RobotManager::GetSingleton().Update(fElapsed);
			}

			m_fLostTime = RobotTimer::GetSingleton().GetElapsed();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CSmallNineDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT1, m_ipAddress);

	CString buffer;
	GetDlgItemText(IDC_EDIT2, buffer);
	m_wPort	= atoi(buffer.GetBuffer());

	GetDlgItemText(IDC_EDIT3, m_md5);

	if (!m_ipAddress.IsEmpty() && !buffer.IsEmpty() && !m_md5.IsEmpty())
	{
		GetDlgItemText(IDC_EDIT4, buffer);
		m_dwStartID = atoi(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT5, buffer);
		m_dwEndID	= atoi(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT19, buffer);
		m_dwMaxCount= atoi(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT6, buffer);
		m_AppConfig.nUpBankerScore	= atol(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT7, buffer);
		m_AppConfig.wUpBankerCount	= atoi(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT8, buffer);
		m_AppConfig.wUpBankerDeque	= atoi(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT9, buffer);
		m_AppConfig.fMaxPlaceTime	= atof(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT10, buffer);
		m_AppConfig.fMinPlaceTime	= atof(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT11, buffer);
		m_AppConfig.nMaxWinScore	= _atoi64(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT12, buffer);
		m_AppConfig.nMinScore		= _atoi64(buffer.GetBuffer());

		GetDlgItemText(IDC_EDIT13, buffer);
		m_AppConfig.nSaveMax		= _atoi64(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT14, buffer);
		m_AppConfig.nSaveScore		= _atoi64(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT15, buffer);
		m_AppConfig.nGetMax			= _atoi64(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT16, buffer);
		m_AppConfig.nGetScore		= _atoi64(buffer.GetBuffer());
		GetDlgItemText(IDC_EDIT17, buffer);
		m_AppConfig.nTenLakhRate	= atoi(buffer.GetBuffer());	
		GetDlgItemText(IDC_EDIT18, buffer);
		m_AppConfig.nPlaceMaxRate	= atoi(buffer.GetBuffer());	

		GetDlgItemText(IDC_EDIT20, buffer);
		m_AppConfig.fMinOnlineTime	= atof(buffer.GetBuffer());	
		GetDlgItemText(IDC_EDIT21, buffer);
		m_AppConfig.fMaxOnlineTime	= atof(buffer.GetBuffer());	

		RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);

		SetTimer(IDT_TIMER_UPDATE, 30,		NULL);
		SetTimer(IDT_TIMER_RECONNECT, 5000, NULL);

		CTraceService::TraceString("SmallNine Starup",
			TraceLevel_Normal);

		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
	else
	{
		AfxMessageBox("error, please set ip and port and password");
	}
}

void CSmallNineDlg::OnBnClickedCancel()
{
	KillTimer(IDT_TIMER_UPDATE);

	OnCancel();
}

void CSmallNineDlg::OnEnChangeEdit4()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT4, buffer);
	m_dwStartID = atoi(buffer.GetBuffer());
}

void CSmallNineDlg::OnEnChangeEdit5()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT5, buffer);
	m_dwEndID = atoi(buffer.GetBuffer());
}

void CSmallNineDlg::OnEnChangeEdit6()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT6, buffer);
	m_AppConfig.nUpBankerScore	= atol(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);

}

void CSmallNineDlg::OnEnChangeEdit7()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT7, buffer);
	m_AppConfig.wUpBankerCount	= atoi(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit8()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT8, buffer);
	m_AppConfig.wUpBankerDeque	= atoi(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit9()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT9, buffer);
	m_AppConfig.fMaxPlaceTime	= atof(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit10()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT10, buffer);
	m_AppConfig.fMinPlaceTime	= atof(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit11()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT11, buffer);
	m_AppConfig.nMaxWinScore	= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit12()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT12, buffer);
	m_AppConfig.nMinScore		= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit13()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT13, buffer);
	m_AppConfig.nSaveMax		= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit14()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT14, buffer);
	m_AppConfig.nGetScore		= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit15()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT15, buffer);
	m_AppConfig.nGetMax			= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit16()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT16, buffer);
	m_AppConfig.nGetScore		= _atoi64(buffer.GetBuffer());
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit17()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT17, buffer);
	m_AppConfig.nTenLakhRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit18()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT18, buffer);
	m_AppConfig.nPlaceMaxRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit19()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT19, buffer);
	m_dwMaxCount= atoi(buffer.GetBuffer());
}

void CSmallNineDlg::OnEnChangeEdit20()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT20, buffer);
	m_AppConfig.fMinPlaceTime	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit21()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT21, buffer);
	m_AppConfig.fMaxOnlineTime	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit22()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT22, buffer);
	m_AppConfig.nShunMenRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit23()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT23, buffer);
	m_AppConfig.nTianMenRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit24()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT24, buffer);
	m_AppConfig.nDaoMenRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit25()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT25, buffer);
	m_AppConfig.nZuoJiaoRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);
}

void CSmallNineDlg::OnEnChangeEdit26()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT26, buffer);
	m_AppConfig.nYouJiaoRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);

}

void CSmallNineDlg::OnEnChangeEdit27()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT27, buffer);
	m_AppConfig.nQiaoRate	= atoi(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);

}

void CSmallNineDlg::OnEnChangeEdit28()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT28, buffer);
	m_AppConfig.nUpBankerLoseScore	= atol(buffer.GetBuffer());	
	RobotManager::GetSingleton().SetBankerConfig(m_AppConfig);

}

void CSmallNineDlg::OnBnClickedButton1()
{
	m_RobotDialog.CenterWindow();
	m_RobotDialog.ShowWindow(SW_SHOW);
}
