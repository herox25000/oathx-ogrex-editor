// ServerConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerConfig.h"
#include "ServerConfigDlg.h"
#include ".\serverconfigdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CServerConfigDlg �Ի���



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


// CServerConfigDlg ��Ϣ�������

BOOL CServerConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_Tab.InsertItem(CFG_SMALLNINE, "С��");
	m_Tab.InsertItem(CFG_PUKNINE, "�ƾ�");
	m_Tab.InsertItem(CFG_30MINI, "30��");
	m_Tab.SetCurSel(CFG_SMALLNINE);
	OnTcnSelchangeTab1(NULL,NULL);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
	if (IDYES == MessageBox("��ȷ��Ҫ���������޸���", NULL, MB_YESNO))
	{
		OnSaveConfig();
	}
}
