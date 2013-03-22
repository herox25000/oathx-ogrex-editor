// RobotManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RobotManager.h"
#include "RobotManagerDlg.h"
#include ".\robotmanagerdlg.h"

#include <Shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  CHANGE_ROBOT		1
#define  LOGIN				2
#define  LOGOUT				3

// CRobotManagerDlg 对话框

CRobotManagerDlg::CRobotManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRobotManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	srand((unsigned)time(NULL)); 
	m_nGroupID = 1;
}

void CRobotManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditTrace);
}

BEGIN_MESSAGE_MAP(CRobotManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAN, OnBnClickedClean)
	ON_BN_CLICKED(IDC_END_SERVER, OnBnClickedEndServer)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CRobotManagerDlg 消息处理程序

BOOL CRobotManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//// TODO: 在此添加额外的初始化代码
	//if (m_EventService.CreateInstance()==true)
	//{
	//	m_pIUnknownEx=(IUnknownEx *)m_EventService->QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
	//	m_EventService->SetRichEditHwnd(m_RichEditCtrl.GetSafeHwnd());
	//}

//	m_RichEditCtrl.SetBackgroundColor(FALSE,RGB(220,220,220));

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CRobotManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRobotManagerDlg::OnPaint() 
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
HCURSOR CRobotManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRobotManagerDlg::OnBnClickedOk()
{
	//m_EventService->ShowEventNotify("机器人启动中。。。",Level_Normal);
	CTraceService::TraceString("机器人启动中........！",TraceLevel_Normal);
	// TODO: 在此添加控件通知处理程序代码
	ChangeRobot();

	SetTimer(CHANGE_ROBOT, 21600000, NULL);

	GetDlgItem(IDC_END_SERVER)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CRobotManagerDlg::ChangeRobot()
{
	if(!m_BaVec.empty())
	{
		for(CGameVec::iterator iter = m_BaVec.begin(); iter != m_BaVec.end();++iter)
		{
			(*iter)->EndServer();
			delete *iter;
		}
		m_TimerEngine.EndService();
	}
	m_BaVec.clear();

	char path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	PathRemoveFileSpec(path);

	::GetPrivateProfileString("config", "ip", "", 
		m_strIP.GetBuffer(255), 255, CString(path)+"\\RM-PaiJiu.ini");
	m_strIP.ReleaseBuffer();

	if(m_strIP.IsEmpty())
	{
		MessageBox("配置文件:RM-PaiJiu.ini丢失，无法启动！");
		return;
	}

	m_nPort = ::GetPrivateProfileInt("config", "port", 0, 
		CString(path)+"\\RM-PaiJiu.ini");

	::GetPrivateProfileString("config", "psw", "", 
		m_strPsw.GetBuffer(255), 255, CString(path)+"\\RM-PaiJiu.ini");
	m_strPsw.ReleaseBuffer();

	CString strName;
	strName.Format("group%i", m_nGroupID);
	m_nStartID = ::GetPrivateProfileInt(strName, "startID", 0, 
		CString(path)+"\\RM-PaiJiu.ini");

	m_nEndID = ::GetPrivateProfileInt(strName, "endID", 0, 
		CString(path)+"\\RM-PaiJiu.ini");

	m_nRoomMaxRobot = ::GetPrivateProfileInt("RoomOption", "MaxRobotNum", 30, 
		CString(path)+"\\RM-PaiJiu.ini");

	m_BaMap.clear();

	Login();	
	SetTimer(LOGIN, rand()%3000+5000, NULL);
}

void CRobotManagerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//关闭连接
	if(!m_BaVec.empty())
	{
		for(CGameVec::iterator iter = m_BaVec.begin(); iter != m_BaVec.end();++iter)
		{
			(*iter)->EndServer();
			delete *iter;
		}
		m_TimerEngine.EndService();
	}
	
	OnCancel();
}

BOOL CRobotManagerDlg::Find(DWORD dwID)
{
	for (int i=0; i<m_BaVec.size(); i++)
	{
		if ( m_BaVec[i]->GetUserID() == dwID)
			return TRUE;
	}

	return FALSE;
}

void CRobotManagerDlg::Login()
{
	if (m_nRoomMaxRobot <= m_BaVec.size())
		return;
	if(m_nStartID>0 && m_nEndID>0 && m_nEndID>=m_nStartID)
	{
		m_TimerEngine.BeginService();

		DWORD dwUserID = 0;
		do 
		{
			dwUserID = rand() % ( m_nEndID - m_nStartID) + m_nStartID;
			if ( FALSE == Find(dwUserID) )
			{
				break;
			}
			else
			{
				dwUserID = 0;
			}
			
		} while (m_BaVec.size() < m_nEndID - m_nStartID);

		if (dwUserID)
		{
			CPaiJiu *pGame = new CPaiJiu(dwUserID);
			pGame->BeginServer(m_strIP, m_nPort, m_strPsw);

			m_BaVec.push_back(pGame);
			//pGame->SetEventService(m_pIUnknownEx);
			pGame->SetTimerEngine(&m_TimerEngine);

			m_BaMap.insert(CGameMap::value_type(dwUserID, CGame(pGame, 0)));
			SetTimer(dwUserID, 5000, NULL);

			m_BaVec[0]->SetSmall();
		}
	}
}

void CRobotManagerDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == CHANGE_ROBOT)
	{
		m_nGroupID++;
		if(m_nGroupID>10)
		{
			m_nGroupID = 1;
		}
		ChangeRobot();
	}
	else
	if(nIDEvent == LOGIN)
	{
		if(m_nStartID<=m_nEndID)
		{
			Login();
		}
		else
		{
			KillTimer(LOGIN);
		}
	}
	else
	if(nIDEvent == LOGOUT)
	{
		if(!m_BaVec.empty())
		{
			Logout();
		}
		else
		{
		//	m_EventService->ShowEventNotify("机器人已经全部退出！",Level_Normal);
			CTraceService::TraceString("机器人已经全部退出！",TraceLevel_Normal);
			KillTimer(CHANGE_ROBOT);

			GetDlgItem(IDC_END_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			KillTimer(LOGOUT);
		}
	}
	else
	{
		CGameMap::iterator iter = m_BaMap.find(nIDEvent);

		if(iter != m_BaMap.end())
		{
			if(iter->second._nTimes > 10)
			{
				iter->second._pGame->EndServer();

				CString strMsg;
				strMsg.Format("%i 无法进入游戏！", nIDEvent);
				//m_EventService->ShowEventNotify(strMsg, Level_Normal);

				CTraceService::TraceString(strMsg,TraceLevel_Normal);
				KillTimer(nIDEvent);
			}
			else
			{
				if(iter->second._pGame->IsSitOk() == false)
				{
					iter->second._pGame->EndServer();
					iter->second._nTimes++;
					iter->second._pGame->BeginServer(m_strIP, m_nPort, m_strPsw);
				}
				else
				{
					KillTimer(nIDEvent);
				}
			}
		}
	
	}
	CDialog::OnTimer(nIDEvent);
}

void CRobotManagerDlg::OnBnClickedEndServer()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(LOGOUT);
	if(!m_BaVec.empty())
	{
		for(CGameVec::iterator iter = m_BaVec.begin(); iter != m_BaVec.end();)
		{
			(*iter)->EndServer();
			delete *iter;
			iter = m_BaVec.erase(iter);
		}
		m_TimerEngine.EndService();
	}
	m_BaVec.clear();

	//m_EventService->ShowEventNotify("机器人已经全部退出！",Level_Normal);
	CTraceService::TraceString("机器人已经全部退出！",TraceLevel_Normal);
	KillTimer(CHANGE_ROBOT);

	GetDlgItem(IDC_END_SERVER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CRobotManagerDlg::Logout()
{
	if(!m_BaVec.empty())
	{
		CGameVec::iterator iter = m_BaVec.begin();
		(*iter)->EndServer();
		delete *iter;
		m_BaVec.erase(iter);
	}
	if(m_BaVec.empty())
	{
	//	m_EventService->ShowEventNotify("机器人已经全部退出！",Level_Normal);

		CTraceService::TraceString("机器人已经全部退出！",TraceLevel_Normal);
		KillTimer(CHANGE_ROBOT);

		GetDlgItem(IDC_END_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		KillTimer(LOGOUT);
	}
}	

void CRobotManagerDlg::OnBnClickedClean()
{
	//if (m_EventService.GetInterface()) m_EventService->ClearRichEdit();
}

BOOL CRobotManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE)) return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CRobotManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Logout();
	SetTimer(LOGOUT, rand()%12000+180000, NULL);
}
