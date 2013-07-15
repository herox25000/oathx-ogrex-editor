// AiToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AiTool.h"
#include "AiToolDlg.h"
#include ".\aitooldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAiToolDlg 对话框

TableInfo      mTableInfo[TABLE_NUM];
BOOL bIsHaveMannage;

CAiToolDlg::CAiToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiToolDlg::IDD, pParent)
	, m_EditID(0)
	, m_Table(0)
	, m_Chair(0)
	, m_EditPort(0)
	, m_NumPlay(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAiToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EditID);
	DDX_Text(pDX, IDC_EDIT3, m_Table);
	DDX_Text(pDX, IDC_EDIT2, m_Chair);
	DDX_Control(pDX, IDC_COMBO1, m_List);
	DDX_Text(pDX, IDC_EDIT4, m_EditPort);
	DDX_Text(pDX, IDC_EDIT5, m_NumPlay);
}

BEGIN_MESSAGE_MAP(CAiToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// CAiToolDlg 消息处理程序

BOOL CAiToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	CIPAddressCtrl * pIP=(CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1);

	bIsHaveMannage=TRUE;
	m_EditID=50;
	pIP->SetAddress(60,190,18,28);
	m_EditPort=4701;
	m_NumPlay=240;
	UpdateData(FALSE);
	m_IsPlay=FALSE;
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAiToolDlg::OnPaint() 
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
HCURSOR CAiToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CAiToolDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 100:
		{
			try
			{
				if(m_UserManage[m_ConnectCount++]->Connect(dwIP,wPort))
				{
					if(m_ConnectCount==1)
					{
						m_UserManage[m_ConnectCount-1].bIsMannageTableInfo=TRUE;
						bIsHaveMannage=TRUE;
					}
				}
			}
			catch (LPCTSTR pszError)
			{
				AfxMessageBox(pszError,MB_ICONINFORMATION);
				return;
			}
			if (m_ConnectCount>=m_NumPlay) KillTimer(nIDEvent);
			break;
		}
	case 101:
		{
			if(!bIsHaveMannage)
			{
				ReSelManage();
			}
			for(int i=0;i<m_NumPlay;i++)
			{
				m_UserManage[i].SubDelayTime();
			}
			break;
		}
	}
	__super::OnTimer(nIDEvent);
}
void CAiToolDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_IsPlay=TRUE;
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	CIPAddressCtrl * pIP=(CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1);
	UpdateData(TRUE);
	pIP->GetAddress(dwIP);
	dwIP=ntohl(dwIP);
	dwBeginID=m_EditID;
	wPort=m_EditPort;
	for (int i=0;i<m_NumPlay;i++)
	{
		m_UserManage[i].CreateSocketInstance();
	}
	for(int i=0;i<m_NumPlay;i++)
	{
		m_UserManage[i].SetUserID(dwBeginID+i);
		m_UserManage[i].SetUserPass("123456");
		m_UserManage[i].SetDealyTime(0);
		m_UserManage[i].SetConnectInfo(dwIP,wPort);
		m_UserManage[i].SetUserStatus(NOCONNECT);
		
	}
	/*i=0;
	CStdioFile m_File;
	CString strReadID;
	CString strFileName;
	strFileName.Format("%d",wPort);
	strFileName+=".txt";
	if(m_File.Open(strFileName,CFile::modeReadWrite))
	{
		while(m_File.ReadString(strReadID)&&i<m_NumPlay)
		{
			if(strReadID.GetLength()>0)
			{
				dwBeginID=StrToLong(strReadID);
				m_UserManage[i].SetUserID(dwBeginID);
				m_UserManage[i].SetUserPass("3112546");
				m_UserManage[i].SetDealyTime(0);
				m_UserManage[i].SetConnectInfo(dwIP,wPort);
				m_UserManage[i++].SetUserStatus(NOCONNECT);
			}
			strReadID.Empty();
		}	
		m_NumPlay=i;
	}
	m_File.Close();*/

	m_ConnectCount=0;  //登陆个数清零
	mLogUserNum=0;  //登陆用户个数清零
	m_OffLineUserNum=0;  //掉线用户个数清零
	SetTimer(100,200,NULL);   //设置登陆
	SetTimer(101,100,NULL);   //设置登陆

}
bool	CAiToolDlg::ReSelManage()
{
	for(int i=0;i<m_NumPlay;i++)
	{
		if(m_UserManage[i].GetInterface()->GetConnectState()==SocketState_Connected)
		{
			m_UserManage[i].bIsMannageTableInfo=TRUE;
			bIsHaveMannage=TRUE;
			return  true;
		}
		else
		{
			for(int n=0;n<TABLE_NUM;n++)
			{
				for(int m=0;m<CHAIR_NUM;m++)
				{
					mTableInfo[n].ChairStatus[m]=US_FREE;
				}
				mTableInfo[n].TableStatus=TABLEFREE;
			}
		}
	}
	return false;
}

void CAiToolDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	if(m_IsPlay)
	{
		KillTimer(101);
		for(int i=0;i<m_NumPlay;i++)
		{
			m_UserManage[i]->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);
		}
	}
	OnCancel();
}

void CAiToolDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	str.Format("%d",mTableInfo[m_Table].TableStatus);
	MessageBox(str,NULL,MB_OK);
}

void CAiToolDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	str.Format("%d",mTableInfo[m_Table].ChairStatus[m_Chair]);
	MessageBox(str,NULL,MB_OK);
}

void CAiToolDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	for(int i=0;i<m_NumPlay;i++)
	{
		m_UserManage[i].SetDealyTime(0);
		m_UserManage[i].SetUserStatus(CLOSECONNECT);
		m_UserManage[i].bIsExitByUser=true;
		
	}
}
