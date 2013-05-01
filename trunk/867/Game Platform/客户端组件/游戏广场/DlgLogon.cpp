#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"
//圆角大小
#define ROUND_CX					12									//圆角宽度
#define ROUND_CY					12									//圆角高度
//屏幕位置
#define LAYERED_SIZE				4									//分层大小
#define CAPTION_SIZE				50									//标题大小

//密码等级
#define PASSWORD_LEVEL_0			0									//没有等级
#define PASSWORD_LEVEL_1			1									//没有等级
#define PASSWORD_LEVEL_2			2									//没有等级
#define PASSWORD_LEVEL_3			3									//没有等级

static BOOL GetOptionItem(LPCTSTR lpAppName, LPCTSTR lpKey, LPSTR lpText, int iLen)
{
	char szPath[MAX_PATH];
	::GetModulePath(szPath, sizeof(szPath));
	SafeStrCat(szPath, "\\LogonServer.ini", sizeof(szPath));

	lpText[0]=0;
	return ::GetPrivateProfileString(lpAppName, lpKey, NULL, lpText, iLen, szPath);
}

//登录方式
#define LOGON_BY_ACCOUNTS				0						//帐号登录
#define LOGON_BY_USERID					1						//ID 登录

//屏幕限制
#define LESS_SCREEN_W					1024					//最小宽度
#define LESS_SCREEN_H					720						//最小高度
//////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
	//取消按钮
	ON_BN_CLICKED(IDC_BT_QUIT, OnCancel)
	ON_EN_CHANGE(IDC_PASSWORD, OnEnChangeLogonPass)
	ON_EN_CHANGE(IDC_BANKPASS, OnEnChangeInsurePass)
	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////////////////////

CDlgRegister::CDlgRegister() : CDialog(IDD_REGISTER)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_szSpreader[0]=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	//创建画刷
	m_brBrush.CreateSolidBrush(RGB(215,223,228));

	m_cbLogonPassLevel = PASSWORD_LEVEL_0;		//密码等级
	m_cbInsurePassLevel = PASSWORD_LEVEL_0;		//密码等级
	return;
}

//析构函数
CDlgRegister::~CDlgRegister()
{
}

//控件绑定
void CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDC_BT_QUIT, m_btCancel);
	DDX_Control(pDX, IDCANCEL, m_btClose);
	DDX_Control(pDX, IDC_USER_FACE, m_FaceSelect);
}

//初始化函数
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("帐号注册"));
	//加载资源
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));
	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//限制输入
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD2)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_BANKPASS)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_BANKPASS2)))->LimitText(PASS_LEN-1);

	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btClose.SetButtonImage(IDB_BT_REGISTER_CLOSE,hInstance,false,false);
	m_btLogon.SetButtonImage(IDB_BT_REGISTER_ENTER,hInstance,false,false);
	m_btCancel.SetButtonImage(IDB_BT_REGISTER_QUIT,hInstance,false,false);

	//加载头像
	g_GlobalUnits.m_UserFaceRes->FillImageList(m_ImageList);
	m_FaceSelect.SetImageList(&m_ImageList);

	//插入头像
	COMBOBOXEXITEM Item;
	ZeroMemory(&Item,sizeof(Item));
	Item.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	for (int i=g_GlobalUnits.m_UserFaceRes->GetFaceCount()-1;i>=0;i--) 
	{
		Item.lParam=i;
		Item.iImage=i;
		Item.iSelectedImage=i;
		m_FaceSelect.InsertItem(&Item);
	}

	//用户性别
	BYTE cbGender[]={/*GENDER_NULL,*/GENDER_BOY,GENDER_GIRL};
	LPCTSTR pszGender[]={/*TEXT("保密"),*/TEXT("男性"),TEXT("女性")};
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(IDC_GENDER);

	//用户性别
	for (int i=0;i<CountArray(cbGender);i++)
	{
		int nItem=pComboBox->InsertString(i,pszGender[i]);
		pComboBox->SetItemData(nItem,cbGender[i]);
	}
	pComboBox->SetCurSel(0);

	//设置头像
	m_wFaceID=rand()%g_GlobalUnits.m_UserFaceRes->GetFaceCount();
	m_FaceSelect.SetCurSel(m_wFaceID);

	//获取目录
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);

	//读取配置
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_snprintf(szFileName,sizeof(szFileName),TEXT("%s\\Spreader.ini"),szPath);

	//读取推荐人
	TCHAR szSpreader[NAME_LEN]=TEXT("");
	GetPrivateProfileString(TEXT("SpreaderInfo"),TEXT("SpreaderName"),TEXT(""),szSpreader,CountArray(szSpreader),szFileName);

	//设置名字
	if (szSpreader[0]!=0)
	{
		SetDlgItemText(IDC_SPREADER,szSpreader);
		((CEdit *)GetDlgItem(IDC_SPREADER))->SetReadOnly();
	}

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;
	//分层窗口
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);

	//居中窗口
	CenterWindow(this);
	SetActiveWindow();
	BringWindowToTop();
	SetForegroundWindow();

	return TRUE;
}

//确定函数
void CDlgRegister::OnOK()
{
	CString strBuffer;

	//用户帐号
	GetDlgItemText(IDC_ACCOUNTS,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.GetLength()<6 || strBuffer.GetLength() > 26)
	{
		ShowInformation(TEXT("帐号名字的长度最短4个字符,最长13个字符,请重新输入注册帐号！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		return;
	}
	lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));

	//用户密码
	GetDlgItemText(IDC_PASSWORD,strBuffer);
	if (strBuffer.GetLength()<6)
	{
		ShowInformation(TEXT("游戏密码长度最短为 6 位字符，请重新输入游戏密码！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		return;
	}

	//确认密码
	GetDlgItemText(IDC_PASSWORD2,m_szPassword,CountArray(m_szPassword));
	if (lstrcmp(m_szPassword,strBuffer)!=0)
	{
		ShowInformation(TEXT("游戏密码与确认密码不一致，请重新输入确认密码！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD2)->SetFocus();
		return;
	}

	//银行密码
	GetDlgItemText(IDC_BANKPASS,strBuffer);
	if (strBuffer.GetLength()<6)
	{
		ShowInformation(TEXT("银行密码长度最短为 6 位字符，请重新输入！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_BANKPASS)->SetFocus();
		return;
	}

	//确认银行密码
	GetDlgItemText(IDC_BANKPASS2,m_szBankPassword,CountArray(m_szBankPassword));
	if (lstrcmp(m_szBankPassword,strBuffer)!=0)
	{
		ShowInformation(TEXT("两次输入的银行密码不一致，请确认后重新输入！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_BANKPASS2)->SetFocus();
		return;
	}

	//身份证
	GetDlgItemText(IDC_EDIT_SFZ,strBuffer);
	if (strBuffer.GetLength()!=18)
	{
		ShowInformation(TEXT("请输入正确的身份证号码！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_SFZ)->SetFocus();
		return;
	}
	lstrcpyn(m_szSFZ,strBuffer,CountArray(m_szSFZ));

	//电话号码
	GetDlgItemText(IDC_EDIT_PHONE,strBuffer);
	if (strBuffer.GetLength()<8)
	{
		ShowInformation(TEXT("请输入正确的电话号码！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
		return;
	}
	lstrcpyn(m_szPhone,strBuffer,CountArray(m_szPhone));


	//推广员名
	GetDlgItemText(IDC_SPREADER,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	lstrcpyn(m_szSpreader,strBuffer,CountArray(m_szSpreader));

	//用户性别
	int nCurSel=((CComboBox *)GetDlgItem(IDC_GENDER))->GetCurSel();
	m_cbGender=(BYTE)((CComboBox *)GetDlgItem(IDC_GENDER))->GetItemData(nCurSel);

	//用户头像
	m_wFaceID=m_FaceSelect.GetCurSel();

	__super::OnOK();
}

//取消消息
void CDlgRegister::OnCancel()
{
	__super::OnCancel();
}

//绘画背景
BOOL CDlgRegister::OnEraseBkgnd(CDC * pDC)
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

	//设置缓冲
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//加载资源
	CPngImage ImageBack;
	//CPngImage ImageTitle;
	//ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("REGISTER_TITLE"));
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));

	////加载图标
	//CPngImage ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	//ImageLogo.DrawImage(pBufferDC,11,6);
	//ImageTitle.DrawImage(pBufferDC,40,6);

	//绘制密码等级
	//加载资源
	CPngImage ImagePassword;
	ImagePassword.LoadImage(AfxGetInstanceHandle(),TEXT("PASSWORD_LEVEL"));
	//获取大小
	CSize SizePassword;
	SizePassword.SetSize(ImagePassword.GetWidth()/3,ImagePassword.GetHeight()/2);
	//绘画等级
	ImagePassword.DrawImage(pBufferDC,225,190,SizePassword.cx*3,SizePassword.cy,0,0);
	ImagePassword.DrawImage(pBufferDC,225,255,SizePassword.cx*3,SizePassword.cy,0,0);
	//绘画叠加
	if (m_cbLogonPassLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,225+nImagePos,190,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}
	//绘画叠加
	if (m_cbInsurePassLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbInsurePassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,225+nImagePos,255,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);
	return TRUE;
}

//显示消息
VOID CDlgRegister::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//位置改变
VOID CDlgRegister::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//鼠标消息
VOID CDlgRegister::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟标题
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//控件颜色
HBRUSH CDlgRegister::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(10,10,10));
			return m_brBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//密码等级
BYTE CDlgRegister::GetPasswordLevel(LPCTSTR pszPassword)
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


//登陆密码输入
VOID CDlgRegister::OnEnChangeLogonPass()
{
	//获取密码
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_PASSWORD,szPassword,CountArray(szPassword));
	//等级判断
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//更新窗口
	if (m_cbLogonPassLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbLogonPassLevel=cbPasswordLevel;
		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
}

//银行密码输入
VOID CDlgRegister::OnEnChangeInsurePass()
{
	//获取密码
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_BANKPASS,szPassword,CountArray(szPassword));
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//更新窗口
	if (m_cbInsurePassLevel!=cbPasswordLevel)
	{
		//设置变量
		m_cbInsurePassLevel=cbPasswordLevel;
		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
}


//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)
	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//功能
	ON_EN_CHANGE(IDC_PASSWORD, OnEnChangePassword)
	ON_CBN_SELCHANGE(IDC_USER_ID, OnSelchangeUserID)
	ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_BN_CLICKED(IDC_REGISTER, OnRegisterAccounts)
	ON_BN_CLICKED(IDC_DELETE_RECORD, OnDeleteAccounts)
	ON_BN_CLICKED(IDC_NET_OPTION, OnBnClickedNetOption)
	ON_BN_CLICKED(IDC_BT_QUIT, OnCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_LOGON_TYPE, OnTcnSelchangeLogonType)

	ON_WM_PAINT()
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLogon::CDlgLogon() : CDialog(IDD_LOGON)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_dwUserID=0;
	m_szSpreader[0]=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_LogonMode=LogonMode_Accounts;

	//辅助信息
	m_bRegister=false;
	m_bChangePassWord=false;

	//位置信息
	m_nFullWidth=0;
	m_nFullHeight=0;
	m_bNetOption=false;
	//创建画刷
	m_brBrush.CreateSolidBrush(RGB(0,0,255));
	return;
}

//析构函数
CDlgLogon::~CDlgLogon()
{
	//销毁资源
	if (m_brBrush.GetSafeHandle()!=NULL)
	{
		m_brBrush.DeleteObject();
	}
}

//控件绑定
void CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	//关闭
	DDX_Control(pDX, IDCANCEL, m_btCancel);

	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDC_REGISTER, m_btRegister);
	DDX_Control(pDX, IDC_DELETE_RECORD, m_btDelete);
	DDX_Control(pDX, IDC_LOGON_TYPE, m_TabLogonMode);
	DDX_Control(pDX, IDC_NET_OPTION, m_btNetOption);
	DDX_Control(pDX, IDC_BT_QUIT, m_btQuit);
}

//初始化函数
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("游戏登录"));
	//加载资源
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	////广告控件
	//m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	//m_BrowerAD.Navigate(TEXT("http://www.game541.com/images/login_Ad.jpg"),NULL,NULL,NULL,NULL);
	//m_BrowerAD.SetWindowPos(NULL,LAYERED_SIZE,37,SizeWindow.cx-2*LAYERED_SIZE,84,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
	//m_BrowerAD.ShowWindow(SW_HIDE);


	//加入标签
	m_TabLogonMode.SetItemSize(CSize(100,25));
	m_TabLogonMode.InsertItem(LOGON_BY_ACCOUNTS,TEXT("帐号登录"));
	m_TabLogonMode.InsertItem(LOGON_BY_USERID,TEXT("ＩＤ登录"));
	//设置控件
	m_TabLogonMode.SetRenderImage(true);
	m_TabLogonMode.SetTabCtrlColor(RGB(53,181,255),RGB(145,168,183));

	//限制输入
	((CComboBox *)(GetDlgItem(IDC_USER_ID)))->LimitText(11);
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);

	//登录模式
	m_LogonMode=(enLogonMode)AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("LogonMode"),LogonMode_Accounts);
	if ((m_LogonMode!=LogonMode_Accounts)&&(m_LogonMode!=LogonMode_UserID)) m_LogonMode=LogonMode_Accounts;
	SetLogonMode(m_LogonMode);

	//记录密码
	if (g_GlobalOption.m_enAcountsRule==enAcountsRule_AccountsAndPass)
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_CHECKED);

	//加载信息
	LoadLogonServer();
	LoadAccountsInfo();

	//设置焦点
	UINT uControlID=IDC_ACCOUNTS;
	if (m_LogonMode==LogonMode_UserID) uControlID=IDC_USER_ID;
	if (GetDlgItem(uControlID)->GetWindowTextLength()==0)
	{
		GetDlgItem(uControlID)->SetFocus();
		((CComboBox *)GetDlgItem(uControlID))->SetEditSel(0,-1);
	}
	else 
	{
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		((CEdit *)GetDlgItem(IDC_PASSWORD))->SetSel(0,-1);
	}

	////设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btCancel.SetButtonImage(IDB_BT_Close,hInstance,false,false);
	m_btLogon.SetButtonImage(IDB_BT_LOGON,hInstance,false,false);
	m_btRegister.SetButtonImage(IDB_BT_Register,hInstance,false,false);
	m_btDelete.SetButtonImage(IDB_BT_Delete,hInstance,false,false);
	m_btNetOption.SetButtonImage(IDB_BT_NetOption,hInstance,false,false);
	m_btQuit.SetButtonImage(IDB_BT_QUIT,hInstance,false,false);

	//居中窗口
	CenterWindow(this);
	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE+1,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE,SizeWindow.cy-LAYERED_SIZE,ROUND_CX,ROUND_CY);
	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	////分层窗口
// 	CRect rcWindow;
// 	GetWindowRect(&rcWindow);
// 	CRect rcUnLayered;
// 	rcUnLayered.top=LAYERED_SIZE;
// 	rcUnLayered.left=LAYERED_SIZE;
// 	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
// 	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;
// 	m_SkinLayered.CreateLayered(this,rcWindow);
// 	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);

	return TRUE;
}

//消息解释
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}

//确定函数
void CDlgLogon::OnOK()
{
	//效验输入
	if (CheckLogonInput(true)==false) return;

	//设置变量
	m_bRegister=false;

	//登录广场
	ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();

	return;
}

//取消消息
void CDlgLogon::OnCancel()
{
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	return;
}

//发送登录包
bool CDlgLogon::SendLogonPacket(ITCPSocket * pIClientSocke)
{
	//变量定义
	TCHAR szPassword[33];
	BYTE cbBuffer[SOCKET_PACKET];
	CMD5Encrypt::EncryptData(m_szPassword,szPassword);

	//发送数据
	switch (m_LogonMode)
	{
	case LogonMode_Accounts:		//帐号登录
		{
			if (m_bRegister==false)
			{
				//构造数据
				CMD_GP_LogonByAccounts * pLogonByAccounts=(CMD_GP_LogonByAccounts *)cbBuffer;
				memset(pLogonByAccounts,0,sizeof(CMD_GP_LogonByAccounts));
				pLogonByAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				CopyMemory(pLogonByAccounts->szPassWord,szPassword,sizeof(pLogonByAccounts->szPassWord));
				lstrcpyn(pLogonByAccounts->szAccounts,m_szAccounts,CountArray(pLogonByAccounts->szAccounts));

				//机器序列号
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//发送数据包
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonByAccounts)+Packet.GetDataSize());
			}
			else
			{
				TCHAR szBankPassword[33];
				CMD5Encrypt::EncryptData(m_szBankPassword,szBankPassword);
				//构造数据
				CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;
				memset(pRegisterAccounts,0,sizeof(CMD_GP_RegisterAccounts));
				pRegisterAccounts->wFaceID=m_wFaceID;
				pRegisterAccounts->cbGender=m_cbGender;
				pRegisterAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				lstrcpyn(pRegisterAccounts->szPassWord,szPassword,CountArray(pRegisterAccounts->szPassWord));
				lstrcpyn(pRegisterAccounts->szBankPassWord,szBankPassword,CountArray(pRegisterAccounts->szBankPassWord));
				lstrcpyn(pRegisterAccounts->szSpreader,m_szSpreader,CountArray(pRegisterAccounts->szSpreader));
				lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));
				lstrcpyn(pRegisterAccounts->szSFZ,m_szSFZ,CountArray(pRegisterAccounts->szSFZ));
				lstrcpyn(pRegisterAccounts->szPhone,m_szPhone,CountArray(pRegisterAccounts->szPhone));

				//机器序列号
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//发送数据包
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_RegisterAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_RegisterAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_REGISTER_ACCOUNTS,cbBuffer,sizeof(CMD_GP_RegisterAccounts)+Packet.GetDataSize());
			}

			break;
		}
	case LogonMode_UserID:			//I D 登录
		{
			//构造数据
			CMD_GP_LogonByUserID * pLogonByUserID=(CMD_GP_LogonByUserID *)cbBuffer;
			memset(pLogonByUserID,0,sizeof(CMD_GP_LogonByUserID));
			pLogonByUserID->dwUserID=m_dwUserID;
			pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
			CopyMemory(pLogonByUserID->szPassWord,szPassword,sizeof(pLogonByUserID->szPassWord));
			
			//机器序列号
			tagClientSerial ClientSerial;
			g_GlobalUnits.GetClientSerial(ClientSerial);

			//发送数据包
			CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByUserID));
			Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
			pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_USERID,cbBuffer,sizeof(CMD_GP_LogonByUserID)+Packet.GetDataSize());

			break;
		}
	}

	return true;
}

//登录成功处理
bool CDlgLogon::OnLogonSuccess()
{
	//登录配置
	BOOL bRemPassword=(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);
	AfxGetApp()->WriteProfileInt(REG_OPTION_LOGON,TEXT("LogonMode"),m_LogonMode);
	AfxGetApp()->WriteProfileString(REG_OPTION_LOGON,TEXT("LogonServer"),m_strLogonServer);

	//配置信息
	if (bRemPassword==FALSE)
	{
		if (g_GlobalOption.m_enAcountsRule==enAcountsRule_AccountsAndPass)
		{
			g_GlobalOption.m_enAcountsRule=enAcountsRule_Accounts;
		}
	}
	else 
		g_GlobalOption.m_enAcountsRule=enAcountsRule_AccountsAndPass;

	//用户信息
	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
	AfxGetApp()->WriteProfileInt(REG_OPTION_LOGON,TEXT("LastUserID"),UserData.dwUserID);

	//写入用户记录
	if (g_GlobalOption.m_enAcountsRule!=enAcountsRule_None)
	{
		//构造信息
		TCHAR szBuffer[256];
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s\\%ld"),REG_USER_INFO,UserData.dwUserID);

		//写入信息
		CRegKey RegUserInfo;
		if (RegUserInfo.Create(HKEY_CURRENT_USER,szBuffer)==ERROR_SUCCESS)
		{
			TCHAR szPassBuffer[256]=TEXT("");
			if (bRemPassword)
				CXOREncrypt::EncryptData(m_szPassword,szPassBuffer,CountArray(szPassBuffer));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szAccounts,TEXT("UserAccount"));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szPassWord,TEXT("UserPassToken"));
			RegUserInfo.SetKeyValue(TEXT(""),szPassBuffer,TEXT("UserPassword"));
			if (UserData.dwGameID!=0L) 
				RegUserInfo.SetDWORDValue(TEXT("GameID"),UserData.dwGameID);
		}
	}
	else
	{
		//构造信息
		TCHAR szBuffer[256];
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),UserData.dwUserID);

		//写入信息
		CRegKey RegUserID;
		if (RegUserID.Open(HKEY_CURRENT_USER,REG_USER_INFO)==ERROR_SUCCESS)
			RegUserID.RecurseDeleteKey(szBuffer);
	}
	CComboBox * pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
	//读取最近登录服务器
	for( int i=0; i<pComBoxServer->GetCount(); i++)
	{
		SERVER_ITEM* pSI=(SERVER_ITEM*)pComBoxServer->GetItemData(i);
	}

	//关闭窗口
	DestroyWindow();

	return true;
}

//读取帐号
void CDlgLogon::LoadAccountsInfo()
{
	//变量定义
	CComboBox * pComBoxAccounts=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);
	CComboBox * pComBoxUserID=(CComboBox *)GetDlgItem(IDC_USER_ID);

	//读取信息
	CRegKey RegUserInfo;
	RegUserInfo.Open(HKEY_CURRENT_USER,REG_USER_INFO,KEY_READ);
	if (RegUserInfo!=NULL)
	{
		int iInsertItem=CB_ERR;
		LONG lErrorCode=ERROR_SUCCESS;
		DWORD dwType=REG_SZ,dwIndex=0,dwUserDBID=0;
		TCHAR szUserIDBuffer[32]=TEXT(""),szTempBuffer[256]=TEXT("");
		do
		{
			//设置变量
			dwUserDBID=0;
			szTempBuffer[0]=0;
			szUserIDBuffer[0]=0;

			//读取游戏 ID
			DWORD dwBufferSize=sizeof(szUserIDBuffer);
			if (RegUserInfo.EnumKey(dwIndex++,szUserIDBuffer,&dwBufferSize,NULL)!=ERROR_SUCCESS) break;
			dwUserDBID=atol(szUserIDBuffer);
			if (dwUserDBID==0) continue;

			//加载其他信息
			CRegKey RegUserAccount;
			_snprintf(szTempBuffer,sizeof(szTempBuffer),TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);
			RegUserAccount.Open(HKEY_CURRENT_USER,szTempBuffer,KEY_READ);
			if (RegUserAccount!=NULL)
			{
				//游戏帐号
				dwBufferSize=sizeof(szTempBuffer);
				lErrorCode=RegUserAccount.QueryValue(TEXT("UserAccount"),&dwType,szTempBuffer,&dwBufferSize);
				if ((lErrorCode==ERROR_SUCCESS)&&(szTempBuffer[0]!=0)&&(ComboBoxFindString(pComBoxAccounts,szTempBuffer)==LB_ERR))
				{
					iInsertItem=pComBoxAccounts->AddString(szTempBuffer);
					pComBoxAccounts->SetItemData(iInsertItem,dwUserDBID);
				}

				//游戏 ID
				DWORD dwGameID=0L;
				dwBufferSize=sizeof(dwGameID);
				if ((RegUserAccount.QueryValue(TEXT("GameID"),&dwType,&dwGameID,&dwBufferSize)==ERROR_SUCCESS)&&(dwGameID!=0L))
				{
					_sntprintf(szTempBuffer,CountArray(szTempBuffer),TEXT("%ld"),dwGameID);
					iInsertItem=pComBoxUserID->AddString(szTempBuffer);
					pComBoxUserID->SetItemData(iInsertItem,dwUserDBID);
				}
			}
		} while (true);
	}

	//最近用户
	DWORD dwLastUserID=AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("LastUserID"),0L);
	if (dwLastUserID!=0L)
	{
		for (int i=0;i<pComBoxUserID->GetCount();i++)
		{
			DWORD dwComboBoxID=(DWORD)pComBoxUserID->GetItemData(i);
			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwLastUserID))
			{
				pComBoxUserID->SetCurSel(i);
				UpdateUserComboBox(IDC_USER_ID);
				break;
			}
		}
	}

	//设置选择
	if ((pComBoxUserID->GetCurSel()==LB_ERR)&&(pComBoxUserID->GetCount()>0))
	{
		pComBoxUserID->SetCurSel(0);
		UpdateUserComboBox(IDC_USER_ID);
	}

	//设置选择
	if ((pComBoxAccounts->GetCurSel()==LB_ERR)&&(pComBoxAccounts->GetCount()>0))
	{
		pComBoxAccounts->SetCurSel(0);
		UpdateUserComboBox(IDC_ACCOUNTS);
	}

	return;
}

//加载服务器
void CDlgLogon::LoadLogonServer()
{
	//读取最近登录服务器
	CComboBox * pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
	char szAppName[256];
	char szName[256];
	char szIPAddress[256];
	for ( int i=0; i<5; i++ )
	{
		_snprintf(szAppName, sizeof(szAppName), "Server%d", i);
		GetOptionItem(szAppName, "Name",  szName, 256);
		GetOptionItem(szAppName, "IPAddress",  szIPAddress, 256);
		if ( strlen(szName)>0 && strlen(szIPAddress)>0 )
		{
			SERVER_ITEM* pSI=new SERVER_ITEM;
			memset(pSI, 0, sizeof(SERVER_ITEM));
			lstrcpyn(pSI->szName, szName, sizeof(pSI->szName));
			lstrcpyn(pSI->szIPAddress, szIPAddress, sizeof(pSI->szIPAddress));
			int iAdd=pComBoxServer->AddString(szName);
			pComBoxServer->SetItemData(iAdd, (DWORD)pSI);
		}
	}

	pComBoxServer->SetCurSel(0);

	int iLogonServer=AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("LogonServer"), 0);
	if ( iLogonServer>=0 )
		pComBoxServer->SetCurSel(iLogonServer);
	return;
}


//查找数据
int CDlgLogon::ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString)
{
	CString strBuffer;
	int iItemHandle=LB_ERR,iItemFind=LB_ERR;
	int nStringLen=lstrlen(pszFindString);
	do 
	{
		iItemFind=pComboBox->FindString((iItemHandle==LB_ERR)?0:(iItemHandle+1),pszFindString);
		if ((iItemFind==LB_ERR)||(iItemHandle==iItemFind)||(iItemFind<iItemHandle)) return LB_ERR;
		iItemHandle=iItemFind;
		pComboBox->GetLBText(iItemHandle,strBuffer);
		if (pComboBox->GetLBTextLen(iItemHandle)==nStringLen) return iItemHandle;
	} while (true);
	return LB_ERR;
}

//效验输入
bool CDlgLogon::CheckLogonInput(bool bShowError)
{
	//定义变量
	UINT uControlID=0;
	CString strBuffer;

	try
	{
		//屏幕像素
		RECT reWindowSize;
		GetDesktopWindow()->GetWindowRect(&reWindowSize);
		INT nHeight =reWindowSize.bottom-reWindowSize.top;
		INT nWidth =reWindowSize.right-reWindowSize.left;
		
		//判断像素
		if(nWidth<LESS_SCREEN_W || nHeight<LESS_SCREEN_H)
		{
			TCHAR szInfo[255]=TEXT("");
			_sntprintf(szInfo,CountArray(szInfo),TEXT("屏幕像素需要在%d*%d或以上才可以正常游戏!"),LESS_SCREEN_W,LESS_SCREEN_H);
			throw szInfo;
		}

		//登录服务器
		CComboBox * pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
		int iCur=pComBoxServer->GetCurSel();
		SERVER_ITEM* pSI=(SERVER_ITEM*)pComBoxServer->GetItemData(iCur);
		if (pSI==0)
		{
			uControlID=IDC_SERVER;
			throw TEXT("登录服务器不能为空，请重新选择或者输入登录服务器！");
		}

		m_strLogonServer=pSI->szIPAddress;
		//登录帐号
		switch (m_LogonMode)
		{
		case LogonMode_Accounts:		//帐号登录
			{
				GetDlgItemText(IDC_ACCOUNTS,strBuffer);
				strBuffer.TrimLeft();
				strBuffer.TrimRight();
				if (strBuffer.IsEmpty())
				{
					uControlID=IDC_ACCOUNTS;
					throw TEXT("用户登录帐号不能为空，请重新输入登录帐号！");
				}
				lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));
				break;
			}
		case LogonMode_UserID:			//ID 登录
			{
				GetDlgItemText(IDC_USER_ID,strBuffer);
				strBuffer.TrimLeft();
				strBuffer.TrimRight();
				m_dwUserID=atoi(strBuffer);
				if (m_dwUserID==0L)
				{
					uControlID=IDC_USER_ID;
					throw TEXT("用户登录 ID 不能为空，请重新输入登录 ID ！");
				}
				break;
			}
		}

		//用户密码
		if (m_bChangePassWord==true)
		{
			m_bChangePassWord=false;
			GetDlgItemText(IDC_PASSWORD,m_szPassword,CountArray(m_szPassword));
		}
		if (m_szPassword[0]==0)
		{
			uControlID=IDC_PASSWORD;
			throw TEXT("登录密码不能为空，请重新输入登录密码！");
		}

		//代理类型
		enProxyServerType ProxyServerType=ProxyType_None;
		//代理信息
		tagProxyServerInfo ProxyServerInfo;
		ZeroMemory(&ProxyServerInfo,sizeof(ProxyServerInfo));
		//保存配置
		g_GlobalOption.m_ProxyServerType=ProxyServerType;
		g_GlobalOption.m_ProxyServerInfo=ProxyServerInfo;
		return true;
	}
	catch (LPCTSTR pszError)
	{
		if (bShowError)
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
			ShowInformation(pszError,20,MB_ICONQUESTION);
			if (uControlID!=0) GetDlgItem(uControlID)->SetFocus();
		}

	}
	return false;
}

//更新选择
void CDlgLogon::UpdateUserComboBox(UINT uComboBoxID)
{
	//获取 ID
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);
	DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(pComboBox->GetCurSel());

	//更新信息
	UpdateUserPassWord(dwUserDBID);
	UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
	for (int i=0;i<CountArray(uComboBoxIDs);i++)
	{
		pComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
		for (int j=0;j<pComboBox->GetCount();j++)
		{
			DWORD dwComboBoxID=(DWORD)pComboBox->GetItemData(j);
			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwUserDBID))
			{
				pComboBox->SetCurSel(j);
				break;
			}
		}
	}

	return;
}

//更新密码
void CDlgLogon::UpdateUserPassWord(DWORD dwUserDBID)
{
	if (dwUserDBID!=0L)
	{
		//注册表字符
		CString strRegKey;
		strRegKey.Format(TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);

		//打开注册表
		CRegKey RegPassWord;
		RegPassWord.Open(HKEY_CURRENT_USER,strRegKey,KEY_READ);
		if (RegPassWord!=NULL)
		{
			DWORD dwType=REG_SZ;
			TCHAR szPassBuffer[256]=TEXT("");
			DWORD dwBufferLength=sizeof(szPassBuffer);
			if (RegPassWord.QueryValue(TEXT("UserPassword"),&dwType,szPassBuffer,&dwBufferLength)==ERROR_SUCCESS)
			{
				m_szPassword[0]=0;
				CXOREncrypt::CrevasseData(szPassBuffer,m_szPassword,CountArray(m_szPassword));
				if (m_szPassword[0]==0)
					SetDlgItemText(IDC_PASSWORD,TEXT(""));
				else 
					SetDlgItemText(IDC_PASSWORD,TEXT("**********"));
				m_bChangePassWord=false;
				return;
			}
		}
	}

	//设置信息
	m_szPassword[0]=0;
	SetDlgItemText(IDC_PASSWORD,TEXT(""));
	m_bChangePassWord=false;
	
	return;
}

//代理模式
void CDlgLogon::SwitchNetOption(bool bNetOption)
{
	////设置变量
	//m_bNetOption=bNetOption;
	////控件设置
	//GetDlgItem(IDC_PROXY_TYPE)->EnableWindow(m_bNetOption);
	//GetDlgItem(IDC_PROXY_PORT)->EnableWindow(m_bNetOption);
	//GetDlgItem(IDC_PROXY_USER)->EnableWindow(m_bNetOption);
	//GetDlgItem(IDC_PROXY_PASS)->EnableWindow(m_bNetOption);
	//GetDlgItem(IDC_PROXY_TEST)->EnableWindow(m_bNetOption);
	//GetDlgItem(IDC_PROXY_SERVER)->EnableWindow(m_bNetOption);
	////移动位置
	//INT nHeight=m_bNetOption?m_nFullHeight:m_rcNormalFrame.Height();
	//SetWindowPos(NULL,0,0,m_nFullWidth,nHeight,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);

	return;
}

//设置模式
void CDlgLogon::SetLogonMode(enLogonMode LogonMode)
{
	m_LogonMode=LogonMode;
	switch (m_LogonMode)
	{
	case LogonMode_Accounts:	//帐号登录
		{
			m_TabLogonMode.SetCurSel(LOGON_BY_ACCOUNTS);
			SetDlgItemText(IDC_TYPE_NAME,TEXT("游戏帐号："));
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_USER_ID)->ShowWindow(SW_HIDE);
			break;
		}
	case LogonMode_UserID:		//I D 登录
		{
			m_TabLogonMode.SetCurSel(LOGON_BY_USERID);
			SetDlgItemText(IDC_TYPE_NAME,TEXT("游戏 I D："));
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_USER_ID)->ShowWindow(SW_SHOW);
			break;
		}
	}
	return;
}

//密码改变
void CDlgLogon::OnEnChangePassword()
{
	m_bChangePassWord=true;
}

//选择改变
void CDlgLogon::OnSelchangeAccounts()
{
	UpdateUserComboBox(IDC_ACCOUNTS);
	return;
}

//选择改变
void CDlgLogon::OnSelchangeUserID()
{
	UpdateUserComboBox(IDC_USER_ID);
	return;
}

//类型改变
void CDlgLogon::OnTcnSelchangeLogonType(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabLogonMode.GetCurSel())
	{
	case LOGON_BY_ACCOUNTS:{ SetLogonMode(LogonMode_Accounts); break; }
	case LOGON_BY_USERID:{ SetLogonMode(LogonMode_UserID); break; }
	default: ASSERT(FALSE);
	}
	return;
}

//注册帐号
void CDlgLogon::OnRegisterAccounts()
{
	CDlgRegister DlgRegister;
	ShowWindow(SW_HIDE);
	if (DlgRegister.DoModal()!=IDOK) 
	{
		ShowWindow(SW_SHOW);
		return;
	}

	//设置变量
	m_bRegister=true;
	m_wFaceID=DlgRegister.m_wFaceID;
	m_cbGender=DlgRegister.m_cbGender;
	lstrcpy(m_szSpreader,DlgRegister.m_szSpreader);
	lstrcpy(m_szAccounts,DlgRegister.m_szAccounts);
	lstrcpy(m_szPassword,DlgRegister.m_szPassword);
	lstrcpy(m_szBankPassword,DlgRegister.m_szBankPassword);
	lstrcpy(m_szSFZ,DlgRegister.m_szSFZ);
	lstrcpy(m_szPhone,DlgRegister.m_szPhone);


	//服务器
	CComboBox* pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
	int iCur=pComBoxServer->GetCurSel();
	SERVER_ITEM* pSI=(SERVER_ITEM*)pComBoxServer->GetItemData(iCur);
	if ( pSI==0 )
		return;

	m_strLogonServer=pSI->szIPAddress;
	//登录广场
	ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();

	return;
}

//删除用户
void CDlgLogon::OnDeleteAccounts() 
{
	//获取窗口
	UINT uComboBoxID=0;
	switch (m_LogonMode)
	{
	case LogonMode_Accounts: { uComboBoxID=IDC_ACCOUNTS; break;	}
	case LogonMode_UserID: { uComboBoxID=IDC_USER_ID; break; }
	default: ASSERT(FALSE);
	}
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);

	//删除信息
	CString strBuffer;
	pComboBox->GetWindowText(strBuffer);
	pComboBox->SetWindowText(TEXT(""));
	if (strBuffer.IsEmpty()) return;
	int iSelectItem=ComboBoxFindString(pComboBox,strBuffer);
	if (iSelectItem!=LB_ERR)
	{
		CRegKey RegUserID;
		CString strUserID;
		DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(iSelectItem);
		strUserID.Format(TEXT("%ld"),dwUserDBID);
		RegUserID.Open(HKEY_CURRENT_USER,REG_USER_INFO);
		if (RegUserID!=NULL) RegUserID.RecurseDeleteKey(strUserID);

		//删除选择信息
		CComboBox * pOtherComboBox=NULL;
		UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
		for (int i=0;i<CountArray(uComboBoxIDs);i++)
		{
			pOtherComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
			for (int j=0;j<pOtherComboBox->GetCount();j++)
			{
				DWORD dwUserIDRead=(DWORD)pOtherComboBox->GetItemData(j);
				if (dwUserIDRead==dwUserDBID)
				{
					if (pOtherComboBox->GetCurSel()==j) pOtherComboBox->SetWindowText(TEXT(""));
					pOtherComboBox->DeleteString(j);
					break;
				}
			}
		}
	}

	//更新选择
	pComboBox->SetFocus();
	if (pComboBox->GetCount()>0)
	{
		pComboBox->SetCurSel(0);
		DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(0);
		UpdateUserPassWord(dwUserDBID);
		UpdateUserComboBox(uComboBoxID);
	}
	else
		UpdateUserPassWord(0L);

	return;
}

//网络设置
void CDlgLogon::OnBnClickedNetOption()
{
	//设置模式
	//SwitchNetOption(!m_bNetOption);
	return;
}

//鼠标消息
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟标题
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//绘画背景
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//__super::OnEraseBkgnd(pDC);
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//设置缓冲
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//加载资源
	CPngImage ImageBack;
		//CPngImage ImageTitle;
		//ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("LOGON_TITILE"));
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));

	////加载图标
	//CPngImage ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	//ImageLogo.DrawImage(pBufferDC,11,6);
	//ImageTitle.DrawImage(pBufferDC,40,6);

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}


//重画消息
void CDlgLogon::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);

	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//加载资源
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	//绘画背景
	ImageBack.DrawImage(pBufferDC,0,0);
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);
	return;
}


//显示消息
VOID CDlgLogon::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	////显示分层
	//if (m_SkinLayered.m_hWnd!=NULL)
	//{
	//	m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	//}

	return;
}


//位置改变
VOID CDlgLogon::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	////移动分层
	//if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	//{
	//	m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	//}

	return;
}

//控件颜色
HBRUSH CDlgLogon::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0,10,255));
			return m_brBrush;
		}
	}
	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//主页
void CDlgLogon::OnMainPage()
{
	//构造地址
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("www.game541.com"));
	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}
//新手
void CDlgLogon::OnNewUser()
{
	//构造地址
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("www.game541.com"));
	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}
//服务器条款
void CDlgLogon::OnServer()
{
	//构造地址
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("www.game541.com"));
	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}
//找回密码
void CDlgLogon::OnFindPassWord()
{
	//构造地址
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("www.game541.com"));
	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);
}

