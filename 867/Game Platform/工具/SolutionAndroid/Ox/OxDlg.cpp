#include "stdafx.h"
#include "Ox.h"
#include "OxDlg.h"
#include "AndroidTimer.h"

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

#define IDT_UPDATE		0x01
#define IDT_LISTVIEW	0x02

OxDlg::OxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(OxDlg::IDD, pParent)
{
	m_hIcon			= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_fLostTime		= 0;
	m_nSelectItem	= -1;
	m_pManager		= NULL;
	m_pFactory		= NULL;
}

void OxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1,			m_ListView);
	DDX_Control(pDX, IDC_RICHEDIT21,	m_AndroidLog);
}

BEGIN_MESSAGE_MAP(OxDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_CONFIG, OnBnClickedConfig)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_UPDATE, OnBnClickedUpdate)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnNMRclickListUserView)
	ON_COMMAND(ID__32773, OnOffline)
	ON_COMMAND(ID__32776, OnParticulars)
	ON_COMMAND(ID__32774, OnSaveScore)
	ON_COMMAND(ID__, OnGetScore)
END_MESSAGE_MAP()

BOOL OxDlg::OnInitDialog()
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

	// 创建配置对话框
	m_ConfigDlg.Create(IDD_DIALOG_CONFIG);
	m_BankerDialog.Create(IDD_DIALOG_BANKER);
	
	m_ListView.SetExtendedStyle(
		m_ListView.GetExtendedStyle()|0x00010000|LVS_EX_FULLROWSELECT
		);
	static const char*	chColumnName[] = 
	{
		"UserID",
		"GameID",
		"用户名",
		"当前金钱",
		"输赢金钱",
		"存入总金额",
		"取出总金额",
		"银行结余",
		"工作状态",
		"登录时间",
		"剩余时间",
	};

	for (int i=0; i<11; i++)
	{
		m_ListView.InsertColumn(i, chColumnName[i],	LVCFMT_CENTER,	100 );
	}

	return TRUE; 
}

void OxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void OxDlg::OnPaint() 
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

HCURSOR OxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void OxDlg::OnBnClickedConfig()
{
	m_ConfigDlg.CenterWindow();
	m_ConfigDlg.ShowWindow(SW_SHOW);
}

void OxDlg::OnBnClickedOk()
{
	O2::SAppConfig* pConfig = O2::ConfigFile::GetSingleton().GetAppConfig();
	if (pConfig)
	{
		m_pFactory = new O2::OxFactory(0);
		m_pManager = new O2::AndroidManager(m_pFactory);
		
		SetTimer(IDT_UPDATE,	30,		NULL);
		SetTimer(IDT_LISTVIEW, 3000,	NULL);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		CTraceService::TraceString("牛牛机器人已启动",
			TraceLevel_Debug);
	}
	else
	{
		AfxMessageBox("请先应用配置后再次尝试启动");
	}
}

BOOL OxDlg::OnUpdateListView()
{
	if (m_pManager == NULL)
		return FALSE;

	m_ListView.SetRedraw(FALSE);
	
	int nCount = m_pManager->GetAndroidCount();
	// 添加用户到列表中
	for (int i=0; i<nCount; i++)
	{
		O2::IAndroid* pAndroid = m_pManager->GetAndroid( i );
		if (pAndroid)
		{
			// 获取用户完整信息
			O2::SUser* pUser = pAndroid->GetUserInfo();
			if (pUser)
			{
				//查找用户
				LVFINDINFO fd;
				memset(&fd, 0, sizeof(fd));
				fd.flags	= LVFI_PARAM;
				fd.lParam	= (LPARAM)pUser;

				char szText[MAX_PATH];
				sprintf(szText, "%d", pUser->dwUserID);

				int iItem	= m_ListView.FindItem(&fd);
				if (iItem == -1)
				{
					iItem = m_ListView.InsertItem(m_ListView.GetItemCount(), szText);
					m_ListView.SetItemData(iItem, (DWORD_PTR)pUser);
				}

				m_ListView.SetItemText(iItem, 0, szText);
				sprintf(szText, "%d", pUser->dwGameID);
				m_ListView.SetItemText(iItem, 1, szText);

				sprintf(szText, "%s", pUser->szName);
				m_ListView.SetItemText(iItem, 2, szText);

				sprintf(szText, "%I64d", pUser->nScore);
				m_ListView.SetItemText(iItem, 3, szText);

				sprintf(szText, "%I64d", pUser->nWinScore);
				m_ListView.SetItemText(iItem, 4, szText);

				sprintf(szText, "%I64d", pUser->nSaveScore);
				m_ListView.SetItemText(iItem, 5, szText);

				sprintf(szText, "%I64d", pUser->nGetScore);
				m_ListView.SetItemText(iItem, 6, szText);

				sprintf(szText, "%I64d", pUser->nSaveScore - pUser->nGetScore);
				m_ListView.SetItemText(iItem, 7, szText);

				static const char* chStatusText[] = 
				{
					"没有",
					"站立",
					"坐下",
					"同意",
					"旁观",
					"游戏",
					"断线",
				};

				sprintf(szText, "%s",	chStatusText[pUser->cbUserStatus]);
				m_ListView.SetItemText(iItem, 8, szText);

				sprintf(szText, "%s",	pUser->chLoginTime);
				m_ListView.SetItemText(iItem, 9, szText);

				sprintf(szText, "%d",	pAndroid->GetRemaindTime());
				m_ListView.SetItemText(iItem, 10, szText);
			}
		}
	
	}

	m_ListView.SetRedraw(TRUE);
	m_ListView.Invalidate();

	return TRUE;
}

void OxDlg::OnNMRclickListUserView(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		m_nSelectItem = pNMListView->iItem;

		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_ANDROID ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}

	*pResult = 0;
}

DWORD OxDlg::GetUserID()
{
	char	szText[MAX_PATH];

	LVITEM lvi;
	lvi.iItem		= m_nSelectItem;
	lvi.iSubItem	= 0;
	lvi.mask		= LVIF_TEXT;
	lvi.pszText		= szText;
	lvi.cchTextMax	= MAX_PATH;

	if (m_ListView.GetItem(&lvi))
	{
		if (lvi.pszText != NULL && strlen(lvi.pszText) > 0)
			return atol(lvi.pszText);
	}

	return 0;
}

void OxDlg::OnOffline()
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid != NULL)
	{
		CString szMessage;
		szMessage.Format("你确定要让[%d] [%d] 机器人下线吗", pAndroid->GetUserID(), pAndroid->GetGameID());
		if (IDYES == AfxMessageBox(szMessage, MB_YESNO))
		{
			if (pAndroid->CanOffline())
			{
				pAndroid->SetStatus(US_OFFLINE);
			}
			else
			{
				szMessage.Format("该机器人不能下线，正在游戏中，下线会导致强制扣分", 
					pAndroid->GetUserID(), pAndroid->GetGameID());
				AfxMessageBox(szMessage);
			}

			OnBnClickedUpdate();
		}
	}
	
}

void OxDlg::OnParticulars()
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid)
	{
		O2::SUser* pUser = pAndroid->GetUserInfo();
		if (pUser)
		{
			CString szMessage;
			szMessage.Format("游戏ID:		%d\n游戏名称:	%s\n当前金钱:	%I64d\n输赢金额:	%I64d\n存入银行总额:	%I64d\n银行取出总额:	%I64d\n银行结余:	%I64d\n总计坐庄次数:	%d\n坐庄总成绩:	%I64d",
				pUser->dwGameID, pUser->szName, pUser->nScore, pUser->nWinScore, pUser->nSaveScore, 
				pUser->nGetScore, pUser->nSaveScore-pUser->nGetScore, pUser->wBankerCount, pUser->nBankerAllWin);
			AfxMessageBox(szMessage);
		}
	}
}

void OxDlg::SaveScore(INT64 nScore)
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid)
	{
		O2::SUser* pUser = pAndroid->GetUserInfo();
		if (pUser->nScore < nScore)
		{
			AfxMessageBox("存入金钱大于当前金钱，非法操作");
		}
		else
		{
			pAndroid->SaveScoreToBanker(nScore);
		}
	}
}

void OxDlg::GetScore(INT64 nScore)
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid)
	{
		pAndroid->GetScoreFromBanker(nScore);
	}
}

void OxDlg::OnSaveScore()
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid)
	{
		O2::SUser* pUser = pAndroid->GetUserInfo();
		if (pUser)
		{
			m_BankerDialog.CenterWindow();
			m_BankerDialog.SetType(true);
			m_BankerDialog.SetText("存入金额：");
			m_BankerDialog.ShowWindow(SW_SHOW);
		}
	}
}

void OxDlg::OnGetScore()
{
	DWORD dwUserID			= GetUserID();

	O2::IAndroid* pAndroid	= m_pManager->Search(dwUserID);
	if (pAndroid)
	{
		O2::SUser* pUser = pAndroid->GetUserInfo();
		if (pUser)
		{
			m_BankerDialog.CenterWindow();
			m_BankerDialog.SetType(false);
			m_BankerDialog.SetText("取出金额：");
			m_BankerDialog.ShowWindow(SW_SHOW);
		}
	}
}


void OxDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case IDT_UPDATE:
		{
			double fCurrentTime = O2::AndroidTimer::GetSingleton().GetElapsed();
			double fElapsed		= fCurrentTime - m_fLostTime;

			m_pManager->Update(fElapsed);
			
			m_fLostTime = fCurrentTime;
		}
		break;

	case IDT_LISTVIEW:
		{
			OnUpdateListView();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void OxDlg::OnBnClickedUpdate()
{
	m_ListView.DeleteAllItems();
	OnUpdateListView();
}

void OxDlg::OnBnClickedCancel()
{
	if (IDYES == AfxMessageBox("你确定要退出机器人系统吗", MB_YESNO))
	{
		OnCancel();
	}
}

void OxDlg::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(IDT_UPDATE);
	KillTimer(IDT_LISTVIEW);

	delete m_pFactory;
	delete m_pManager;
	
}

