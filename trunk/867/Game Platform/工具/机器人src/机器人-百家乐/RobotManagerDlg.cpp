// RobotManagerDlg.cpp : ʵ���ļ�
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
// RobotManagerDlg.cpp : ʵ���ļ�
//

// CRobotManagerDlg �Ի���

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


// CRobotManagerDlg ��Ϣ�������

BOOL CRobotManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//if (m_EventService.CreateInstance()==true)
	//{
	//	m_pIUnknownEx=(IUnknownEx *)m_EventService->QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
	//	m_EventService->SetRichEditHwnd(m_RichEditCtrl.GetSafeHwnd());
	//}

	//	m_RichEditCtrl.SetBackgroundColor(FALSE,RGB(220,220,220));

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CRobotManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRobotManagerDlg::OnPaint() 
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
HCURSOR CRobotManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRobotManagerDlg::OnBnClickedOk()
{
	//m_EventService->ShowEventNotify("�����������С�����",Level_Normal);
	CTraceService::TraceString("������������........��",TraceLevel_Normal);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		m_strIP.GetBuffer(255), 255, CString(path)+"\\RM-Baccarat.ini");
	m_strIP.ReleaseBuffer();

	if(m_strIP.IsEmpty())
	{
		MessageBox("�����ļ�:RM-Baccarat.ini��ʧ���޷�������");
		return;
	}

	m_nPort = ::GetPrivateProfileInt("config", "port", 0, 
		CString(path)+"\\RM-Baccarat.ini");

	::GetPrivateProfileString("config", "psw", "", 
		m_strPsw.GetBuffer(255), 255, CString(path)+"\\RM-Baccarat.ini");
	m_strPsw.ReleaseBuffer();

	CString strName;
	strName.Format("group%i", m_nGroupID);
	m_nStartID = ::GetPrivateProfileInt(strName, "startID", 0, 
		CString(path)+"\\RM-Baccarat.ini");

	m_nEndID = ::GetPrivateProfileInt(strName, "endID", 0, 
		CString(path)+"\\RM-Baccarat.ini");

	m_BaMap.clear();

	Login();	
	SetTimer(LOGIN, rand()%3000+5000, NULL);
}

void CRobotManagerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ر�����
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
			CBaccarat *pGame = new CBaccarat(dwUserID);
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
					//	m_EventService->ShowEventNotify("�������Ѿ�ȫ���˳���",Level_Normal);
					CTraceService::TraceString("�������Ѿ�ȫ���˳���",TraceLevel_Normal);
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
						strMsg.Format("%i �޷�������Ϸ��", nIDEvent);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//m_EventService->ShowEventNotify("�������Ѿ�ȫ���˳���",Level_Normal);
	CTraceService::TraceString("�������Ѿ�ȫ���˳���",TraceLevel_Normal);
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
		//	m_EventService->ShowEventNotify("�������Ѿ�ȫ���˳���",Level_Normal);

		CTraceService::TraceString("�������Ѿ�ȫ���˳���",TraceLevel_Normal);
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
	// TODO: �ڴ����ר�ô����/����û���
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE)) return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CRobotManagerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Logout();
	SetTimer(LOGOUT, rand()%12000+180000, NULL);
}
