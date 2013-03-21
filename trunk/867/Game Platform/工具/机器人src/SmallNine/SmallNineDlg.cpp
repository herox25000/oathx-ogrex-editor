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
	m_fCrateTime	= RobotTimer::rdft(1, 3);
	m_fElapsed		= 0;

	RobotManager::GetSingleton().RegisterRobotFactory( 
		new SmallNineMachineFactory(SMALLNINE_NAME)
		);
}

void CSmallNineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSmallNineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
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

	SetTimer(IDT_TIMER_UPDATE,  30, NULL);

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
	case IDT_TIMER_UPDATE:
		{
			double fCurrentTime = RobotTimer::GetSingleton().GetElapsed();
			double fElapsed		= fCurrentTime - m_fLostTime;

			m_fElapsed			+= fElapsed;

			int nCount = RobotManager::GetSingleton().GetRobotCount();
			if ( nCount < 5)
			{
				if ( m_fElapsed >= m_fCrateTime)
				{
					DWORD dwUserID = 0;
					do 
					{
						dwUserID = rand() % 100 + 105;
						if (NULL == RobotManager::GetSingleton().Search(dwUserID) )
						{
							break;
						}
						else
						{
							dwUserID = 0;
						}

					} while (TRUE);

					if (dwUserID)
					{
						IRobotFactory* pFactory = RobotManager::GetSingleton().GetRobotFactory(SMALLNINE_NAME);
						if (pFactory)
						{
							SmallNineMachine* pMachine = static_cast<SmallNineMachine*>(
								pFactory->Create(dwUserID)
								);
							if (pMachine)
							{
								if (pMachine->Start("222.186.36.78", 11021, "e10adc3949ba59abbe56e057f20f883e"))
								{
									RobotManager::GetSingleton().AddRobot(pMachine);
								}
								else
								{
									delete pMachine;
									pMachine = NULL;
								}
							}
						}
					}
				}
			}
			else
			{

			}

			m_fLostTime = RobotTimer::GetSingleton().GetElapsed();
		}
	}

	CDialog::OnTimer(nIDEvent);
}
