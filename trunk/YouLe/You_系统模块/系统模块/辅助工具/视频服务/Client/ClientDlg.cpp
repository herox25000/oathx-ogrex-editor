// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include ".\clientdlg.h"

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


// CClientDlg �Ի���



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC1, m_Static_Pic1);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_ComboBox_Server);
	DDX_Control(pDX, IDC_COMBO_ROOM, m_ComboBox_Room);
	DDX_Control(pDX, IDC_COMBO_DESK, m_ComboBox_Desk);
	DDX_Control(pDX, IDC_EDIT_PORT, m_Edit_Port);
	DDX_Control(pDX, IDC_STATIC_PIC2, m_Static_Pic2);
	DDX_Control(pDX, IDC_STATIC_PIC3, m_Static_Pic3);
	DDX_Control(pDX, IDC_STATIC_PIC4, m_Static_Pic4);
	DDX_Control(pDX, IDC_STATIC_PIC5, m_Static_Pic5);
	DDX_Control(pDX, IDC_STATIC_PIC6, m_Static_Pic6);
	DDX_Control(pDX, IDC_STATIC_PIC7, m_Static_Pic7);
	DDX_Control(pDX, IDC_STATIC_PIC8, m_Static_Pic8);
	DDX_Control(pDX, IDC_STATIC_PIC9, m_Static_Pic9);
	DDX_Control(pDX, IDC_STATIC_PIC10, m_Static_Pic10);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox_Pos);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Disconnect, OnBnClickedButtonDisconnect)
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
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
	CString s;
	for( int i=1;i<=10;i++ )
	{
		s.Format( "%d", i );
		m_ComboBox_Room.AddString( s );
		m_ComboBox_Desk.AddString( s );
		m_ComboBox_Pos.AddString( s );
	}
	m_ComboBox_Server.AddString("61.139.126.101");
	m_ComboBox_Server.AddString("125.46.60.20");
	m_ComboBox_Server.AddString("127.0.0.1");
	m_ComboBox_Server.SetCurSel(0);
	m_ComboBox_Room.SetCurSel(0);
	m_ComboBox_Desk.SetCurSel(0);
	m_ComboBox_Pos.SetCurSel(0);
	m_Edit_Port.SetWindowText( "8001" );

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_VideoClient.Release();

	CDialog::OnClose();
}
void CClientDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Server, Port, Room, Desk, Pos;
	m_ComboBox_Server.GetWindowText( Server );
	if( Server=="" )
	{
		AfxMessageBox( "�������������ַ" );
		return;
	}

	m_Edit_Port.GetWindowText( Port );
	if( Port=="" )
	{
		AfxMessageBox( "����˿ں�" );
		return;
	}

	m_ComboBox_Room.GetWindowText( Room );
	m_ComboBox_Desk.GetWindowText( Desk );
	m_ComboBox_Pos.GetWindowText( Pos );

	m_VideoClient.Init();
	m_VideoClient.m_VideoWindow[0].SetHwnd( m_Static_Pic1.m_hWnd );
	m_VideoClient.m_VideoWindow[1].SetHwnd( m_Static_Pic2.m_hWnd );
	m_VideoClient.m_VideoWindow[2].SetHwnd( m_Static_Pic3.m_hWnd );
	m_VideoClient.m_VideoWindow[3].SetHwnd( m_Static_Pic4.m_hWnd );
	m_VideoClient.m_VideoWindow[4].SetHwnd( m_Static_Pic5.m_hWnd );
	m_VideoClient.m_VideoWindow[5].SetHwnd( m_Static_Pic6.m_hWnd );
	m_VideoClient.m_VideoWindow[6].SetHwnd( m_Static_Pic7.m_hWnd );
	m_VideoClient.m_VideoWindow[7].SetHwnd( m_Static_Pic8.m_hWnd );
	m_VideoClient.m_VideoWindow[8].SetHwnd( m_Static_Pic9.m_hWnd );
	m_VideoClient.m_VideoWindow[9].SetHwnd( m_Static_Pic10.m_hWnd );

	m_VideoClient.Login( Server.GetBuffer(), atoi(Port), atoi(Room), atoi(Desk), atoi(Pos) );
}

void CClientDlg::OnBnClickedButtonDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_VideoClient.Release();
}
