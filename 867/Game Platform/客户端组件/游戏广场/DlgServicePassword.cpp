#include "StdAfx.h"
#include "GlobalUnits.h"
#include "DlgServicePassword.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgServicePassword, CDlgServiceItem)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_LOGON_PASSWORD2, OnEnChangeLogonPassword)
	ON_EN_CHANGE(IDC_INSURE_PASSWORD2, OnEnChangeInserePassword)
	ON_BN_CLICKED(IDC_MODIFY_LOGON_PASSWORD, OnBnClickedLogonPassword)
	ON_BN_CLICKED(IDC_MODIFY_INSURE_PASSWORD, OnBnClickedInsurePassword)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgServicePassword::CDlgServicePassword() : CDlgServiceItem(IDD_DLG_SERVICE_PASSWORD)
{
	//设置图标
	m_cbImageIndex=1;

	//设置变量
	m_cbLogonPasswordLevel=PASSWORD_LEVEL_0;
	m_cbInsurePasswordLevel=PASSWORD_LEVEL_0;

	//设置变量
	m_bLogonMission=false;
	ZeroMemory(m_szSrcPassword,sizeof(m_szSrcPassword));
	ZeroMemory(m_szDesPassword,sizeof(m_szDesPassword));

	return;
}

//析构函数
CDlgServicePassword::~CDlgServicePassword()
{;
}

//控件绑定
VOID CDlgServicePassword::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//帐号密码
	DDX_Control(pDX, IDC_LOGON_PASSWORD1, m_edLogonPassword1);
	DDX_Control(pDX, IDC_LOGON_PASSWORD2, m_edLogonPassword2);
	DDX_Control(pDX, IDC_LOGON_PASSWORD3, m_edLogonPassword3);

	//二级密码
	DDX_Control(pDX, IDC_INSURE_PASSWORD1, m_edInsurePassword1);
	DDX_Control(pDX, IDC_INSURE_PASSWORD2, m_edInsurePassword2);
	DDX_Control(pDX, IDC_INSURE_PASSWORD3, m_edInsurePassword3);

	//按钮变量
	DDX_Control(pDX, IDC_MODIFY_LOGON_PASSWORD, m_btLogonPassword);
	DDX_Control(pDX, IDC_MODIFY_INSURE_PASSWORD, m_btInsurePassword);
}

//接口查询
void * __cdecl CDlgServicePassword::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//取消
VOID CDlgServicePassword::OnDestroy()
{
	__super::OnDestroy();
	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
}

//消息解释
BOOL CDlgServicePassword::PreTranslateMessage(MSG * pMsg)
{
	//按键过虑
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		//变量定义
		CWnd * pWndFouns=GetFocus();
		TCHAR szPassword[PASS_LEN]=TEXT("");

		//焦点判断
		if (m_edLogonPassword1.IsChild(pWndFouns))
		{
			m_edLogonPassword1.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edLogonPassword2.SetFocus();

			return TRUE;
		}

		//焦点判断
		if (m_edLogonPassword2.IsChild(pWndFouns))
		{
			m_edLogonPassword2.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edLogonPassword3.SetFocus();

			return TRUE;
		}

		//焦点判断
		if (m_edLogonPassword3.IsChild(pWndFouns))
		{
			m_edLogonPassword3.GetUserPassword(szPassword);
			if (szPassword[0]!=0) OnBnClickedLogonPassword();

			return TRUE;
		}

		//焦点判断
		if (m_edInsurePassword1.IsChild(pWndFouns))
		{
			m_edInsurePassword1.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edInsurePassword2.SetFocus();

			return TRUE;
		}

		//焦点判断
		if (m_edInsurePassword2.IsChild(pWndFouns))
		{
			m_edInsurePassword2.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edInsurePassword3.SetFocus();

			return TRUE;
		}

		//焦点判断
		if (m_edInsurePassword3.IsChild(pWndFouns))
		{
			m_edInsurePassword3.GetUserPassword(szPassword);
			if (szPassword[0]!=0) OnBnClickedInsurePassword();

			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}


//连接事件
bool CDlgServicePassword::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//连接结果
	if (nErrorCode!=0)
	{
		//提示消息
		ShowInformationEx(TEXT("连接服务器超时，密码修改失败！"),0,MB_ICONQUESTION,TEXT("用户中心"));
		return true;
	}

	//变量定义
	tagGlobalUserData & pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//加密密码
	TCHAR szSrcPassword[PASS_LEN]=TEXT("");
	TCHAR szDesPassword[PASS_LEN]=TEXT("");
	CMD5Encrypt::EncryptData(m_szSrcPassword,szSrcPassword);
	CMD5Encrypt::EncryptData(m_szDesPassword,szDesPassword);
	//构造数据
	CMD_GP_ModifyPassword Modofiy;
	Modofiy.lUserID = pGlobalUserData.dwUserID;
	Modofiy.lType = m_bLogonMission==true?1:2;
	lstrcpyn(Modofiy.szOLDPassword,szSrcPassword,CountArray(Modofiy.szOLDPassword));
	lstrcpyn(Modofiy.szNEWPassword,szDesPassword,CountArray(Modofiy.szNEWPassword));
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_MODIFYPASSWORD,&Modofiy,sizeof(Modofiy));	

	return true;
}

//关闭事件
bool CDlgServicePassword::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//提示消息
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//提示消息
		ShowInformationEx(TEXT("与服务器的连接异常断开了，用户密码修改失败！"),30,MB_ICONERROR,TEXT("用户中心"));
	}
	OnMissionConclude();
	return true;
}

//读取事件
bool CDlgServicePassword::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	//命令处理
	if (Command.wMainCmdID==MDM_GP_USER)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_MODIFYPASSWORD_RESULT:	//操作失败
			{
				if(pData == NULL || sizeof(CMD_GP_ModifyPassword_Ret) != wDataSize)
				{
					ASSERT(FALSE);
					return true;
				}
				CMD_GP_ModifyPassword_Ret* pRet = (CMD_GP_ModifyPassword_Ret*)pData;

				//成功
				if(pRet->lResultCode == 0)
				{
					ShowInformationEx(TEXT("修改成功,请重新登录,以免对个别功能造成影响！"),60,MB_ICONERROR,TEXT("用户中心"));
				}
				else
				{
					ShowInformationEx(pRet->szDescribeString,60,MB_ICONERROR,TEXT("用户中心"));
				}
				OnMissionConclude();

				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();
				return true;
			}
		}
	}
	//错误断言
	ASSERT(FALSE);
	return true;
}

//开始任务
VOID CDlgServicePassword::OnMissionStart()
{
	//功能按钮
	m_btLogonPassword.EnableWindow(FALSE);
	m_btInsurePassword.EnableWindow(FALSE);
	return;
}

//终止任务
VOID CDlgServicePassword::OnMissionConclude()
{
	//功能按钮
	m_btLogonPassword.EnableWindow(TRUE);
	m_btInsurePassword.EnableWindow(TRUE);
	//设置控件
	m_edLogonPassword1.SetUserPassword(TEXT(""));
	m_edLogonPassword2.SetUserPassword(TEXT(""));
	m_edLogonPassword3.SetUserPassword(TEXT(""));
	//设置控件
	m_edInsurePassword1.SetUserPassword(TEXT(""));
	m_edInsurePassword2.SetUserPassword(TEXT(""));
	m_edInsurePassword3.SetUserPassword(TEXT(""));
	return;
}

//绘画背景
BOOL CDlgServicePassword::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//加载资源
	CPngImage ImagePassword;
	ImagePassword.LoadImage(AfxGetInstanceHandle(),TEXT("PASSWORD_LEVEL"));

	//获取大小
	CSize SizePassword;
	SizePassword.SetSize(ImagePassword.GetWidth()/3,ImagePassword.GetHeight()/2);

	//填充背景
	pBufferDC->FillSolidRect(&rcClient,CSkinPngDialog::m_SkinAttribute.m_crBackGround);

	//绘画等级
	ImagePassword.DrawImage(pBufferDC,230,76,SizePassword.cx*3,SizePassword.cy,0,0);
	ImagePassword.DrawImage(pBufferDC,230,256,SizePassword.cx*3,SizePassword.cy,0,0);

	//绘画叠加
	if (m_cbLogonPasswordLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPasswordLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,230+nImagePos,76,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//绘画叠加
	if (m_cbInsurePasswordLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbInsurePasswordLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,230+nImagePos,256,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//密码输入
VOID CDlgServicePassword::OnEnChangeLogonPassword()
{
	//获取密码
	TCHAR szPassword[PASS_LEN]=TEXT("");
	m_edLogonPassword2.GetUserPassword(szPassword);
	//等级判断
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//更新窗口
	if (m_cbLogonPasswordLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbLogonPasswordLevel=cbPasswordLevel;
		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
	return;
}

//密码输入
VOID CDlgServicePassword::OnEnChangeInserePassword()
{
	//获取密码
	TCHAR szPassword[PASS_LEN]=TEXT("");
	m_edInsurePassword2.GetUserPassword(szPassword);
	//等级判断
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//更新窗口
	if (m_cbInsurePasswordLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbInsurePasswordLevel=cbPasswordLevel;
		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
	return;
}

//修改登陆密码
VOID CDlgServicePassword::OnBnClickedLogonPassword()
{
	//变量定义
	TCHAR szSrcPassword[ PASS_LEN];
	TCHAR szDesPassword[2][PASS_LEN];
	//获取信息
	m_edLogonPassword1.GetUserPassword(szSrcPassword);
	m_edLogonPassword2.GetUserPassword(szDesPassword[0]);
	m_edLogonPassword3.GetUserPassword(szDesPassword[1]);
	//密码判断
	if (szSrcPassword[0]==0)
	{
		//提示信息
		ShowInformationEx(TEXT("原帐号密码错误，请重新输入！"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edLogonPassword1.SetFocus();
		return;
	}

	//密码判断
	if (lstrcmp(szDesPassword[0],szDesPassword[1])!=0)
	{
		//提示信息
		ShowInformationEx(TEXT("两次输入的新帐号密码不一致，请重新输入！"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edLogonPassword2.SetFocus();

		return;
	}
	//变量定义
	INT nCharLength=lstrlen(szDesPassword[0]);
	INT nDataLength=nCharLength*sizeof(TCHAR);
	if(nDataLength  < 6)
	{
		//提示消息
		ShowInformationEx(TEXT("密码至少要6位，请重新输入"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edLogonPassword2.SetFocus();
		return;
	}
	//一致判断
	if (lstrcmp(szSrcPassword,szDesPassword[0])==0)
	{
		//提示信息
		ShowInformationEx(TEXT("您所输入的新密码与原密码一致，请重新输入新密码！"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edLogonPassword2.SetFocus();
		//设置密码
		m_edLogonPassword2.SetUserPassword(TEXT(""));
		m_edLogonPassword3.SetUserPassword(TEXT(""));
		return;
	}
	//设置变量
	m_bLogonMission=true;
	lstrcpyn(m_szSrcPassword,szSrcPassword,CountArray(m_szSrcPassword));
	lstrcpyn(m_szDesPassword,szDesPassword[0],CountArray(m_szDesPassword));
	//事件处理
	OnMissionStart();
	//发起连接
	if (ConnetToServer()==false) 
	{
		OnMissionConclude();
		return;
	}
	return;
}

//修改银行密码
VOID CDlgServicePassword::OnBnClickedInsurePassword()
{
	//变量定义
	TCHAR szSrcPassword[PASS_LEN];
	TCHAR szDesPassword[2][PASS_LEN];

	//获取信息
	m_edInsurePassword1.GetUserPassword(szSrcPassword);
	m_edInsurePassword2.GetUserPassword(szDesPassword[0]);
	m_edInsurePassword3.GetUserPassword(szDesPassword[1]);

	//密码判断
	if (szSrcPassword[0]==0)
	{
		//提示消息
		ShowInformationEx(TEXT("原银行密码错误，请重新输入！"),0,MB_ICONERROR,TEXT("用户中心"));
		m_edLogonPassword1.SetFocus();
		return;
	}

	//密码判断
	if (lstrcmp(szDesPassword[0],szDesPassword[1])!=0)
	{
		ShowInformationEx(TEXT("两次输入的新银行不一致，请重新输入！"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edInsurePassword2.SetFocus();
		return;
	}

	//变量定义
	INT nCharLength=lstrlen(szDesPassword[0]);
	INT nDataLength=nCharLength*sizeof(TCHAR);
	if(nDataLength  < 6)
	{
		//提示消息
		ShowInformationEx(TEXT("密码至少要6位，请重新输入"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edInsurePassword2.SetFocus();
		return;
	}
	//一致判断
	if (lstrcmp(szSrcPassword,szDesPassword[0])==0)
	{
		//提示信息
		ShowInformationEx(TEXT("您所输入的新密码与原密码一致，请重新输入新密码！"),0,MB_ICONERROR,TEXT("用户中心"));
		//设置焦点
		m_edInsurePassword2.SetFocus();
		//设置密码
		m_edInsurePassword2.SetUserPassword(TEXT(""));
		m_edInsurePassword3.SetUserPassword(TEXT(""));
		return;
	}

	//设置变量
	m_bLogonMission=false;
	lstrcpyn(m_szSrcPassword,szSrcPassword,CountArray(m_szSrcPassword));
	lstrcpyn(m_szDesPassword,szDesPassword[0],CountArray(m_szDesPassword));

	//事件处理
	OnMissionStart();

	//发起连接
	if (ConnetToServer()==false) 
	{
		OnMissionConclude();
		return;
	}

	return;
}

//密码等级
BYTE CDlgServicePassword::GetPasswordLevel(LPCTSTR pszPassword)
{
	//变量定义
	BYTE cbPasswordInfo[4]={0,0,0,0};
	UINT uPasswordLength=lstrlen(pszPassword);

	//长度判断
	if (lstrlen(pszPassword)<6)
	{
		return PASSWORD_LEVEL_0;
	}

	//小写字母
	for (UINT i=0;i<uPasswordLength;i++)
	{
		//小写字母
		if ((pszPassword[i]>=TEXT('a'))&&((pszPassword[i]<=TEXT('z'))))
		{
			cbPasswordInfo[0]=1;
			continue;
		}

		//大写字母
		if ((pszPassword[i]>=TEXT('A'))&&((pszPassword[i]<=TEXT('Z'))))
		{
			cbPasswordInfo[1]=1;
			continue;
		}

		//数字字符
		if ((pszPassword[i]>=TEXT('0'))&&((pszPassword[i]<=TEXT('9'))))
		{
			cbPasswordInfo[2]=1;
			continue;
		}

		//其他字符
		cbPasswordInfo[3]=1;
	}

	//判断等级
	BYTE cbLevelCount=0;
	for (BYTE i=0;i<CountArray(cbPasswordInfo);i++)
	{
		if (cbPasswordInfo[i]>0)
		{
			cbLevelCount++;
		}
	}
	return PASSWORD_LEVEL_0+__min(cbLevelCount,(PASSWORD_LEVEL_3-PASSWORD_LEVEL_0));
}

//连接到服务器
bool CDlgServicePassword::ConnetToServer()
{
	//创建组件
	if (m_SocketHelper.GetInterface()==NULL)
	{
		//初始化内核
		IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
		try 
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_SocketHelper.CreateInstance()==false) 
			{
				throw TEXT("网络连接失败1，抱歉！");
			}
			if (m_SocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("网络连接失败2，抱歉！");
			}
		}
		catch (...)
		{
			ShowInformationEx(TEXT("网络连接失败3，抱歉！"),0,MB_ICONQUESTION,TEXT("修改密码"));
			return false;
		}
	}
	if (m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
	if(m_SocketHelper->Connect( g_GlobalUnits.m_LogonServerIP, g_GlobalUnits.m_LogonServerPort) != CONNECT_SUCCESS)
	{
		ShowInformationEx(TEXT("网络连接失败4，抱歉"),0,MB_ICONQUESTION,TEXT("修改密码"));
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
