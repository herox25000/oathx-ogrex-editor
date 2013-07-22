#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"

#include "dlglogon.h"

//登录方式
#define LOGON_BY_ACCOUNTS				0						//帐号登录
#define LOGON_BY_USERID					1						//ID 登录

//颜色定义
#define SELECT_COLOR		RGB(37,56,220)						//选择颜色

//屏幕限制
#define LESS_SCREEN_W					1024					//最小宽度
#define LESS_SCREEN_H					720						//最小高度

//圆角大小
#define ROUND_CX					7									//圆角宽度
#define ROUND_CY					7									//圆角高度

//屏幕位置
#define LAYERED_SIZE				5									//分层大小
//////////////////////////////////////////////////////////////////////////
//注册框按钮ID
#define		WM_BT_REGISTERCLOSE		200
#define		WM_BT_REGISTEROK		201
#define		WM_BT_REGISTERMAN		202
#define		WM_BT_REGISTERWOMAN		203

//登陆框按钮ID
#define		WM_BT_REGISTER		100
#define		WM_BT_WEBHOME		101
#define		WM_BT_CHONGZHI		102
#define		WM_BT_BANBEN		103

//软件键盘
#define		WM_BT_KEYBOARD_MIN	120
#define		WM_BT_KEYBOARD_MAX	WM_BT_KEYBOARD_MIN+38

BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(WM_BT_REGISTERCLOSE,OnCancel)
	ON_BN_CLICKED(WM_BT_REGISTEROK,OnOK)
	ON_EN_CHANGE(IDC_PASSWORD, OnEnChangeLogonPass)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)
	//系统消息
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGED()

	//ON_EN_CHANGE(IDC_PASSWORD, OnEnChangePassword)
	//ON_CBN_SELCHANGE(IDC_USER_ID, OnSelchangeUserID)
	//ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_BN_CLICKED(WM_BT_REGISTER, OnRegisterAccounts)
	ON_BN_CLICKED(WM_BT_WEBHOME, OnWebhome)
	ON_BN_CLICKED(WM_BT_CHONGZHI, OnChongzhi)
	ON_BN_CLICKED(WM_BT_BANBEN, OnBanben)
	ON_CONTROL_RANGE( BN_CLICKED, WM_BT_KEYBOARD_MIN, WM_BT_KEYBOARD_MAX, OnKeyBoard)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
static BOOL GetOptionItem(LPCTSTR lpAppName, LPCTSTR lpKey, LPSTR lpText, int iLen)
{
	char szPath[MAX_PATH];
	::GetModulePath(szPath, sizeof(szPath));
	SafeStrCat(szPath, "\\LogonServer.ini", sizeof(szPath));

	lpText[0]=0;
	return ::GetPrivateProfileString(lpAppName, lpKey, NULL, lpText, iLen, szPath);
}

////////////////////////////////////////////////////////////////////////////


//构造函数
CControlCheckButton::CControlCheckButton()
{
	//设置变量
	m_cbChecked=false;
	m_pParentSink=NULL;
}

//析构函数
CControlCheckButton::~CControlCheckButton()
{
}

//创建(只能添加PNG资源)
void CControlCheckButton::CreatCheckButton(CWnd* pParentWnd,HINSTANCE hInstance, LPCTSTR pszResourceName,INT nXPos,INT nYPos)
{
	m_pParentSink = pParentWnd;
	m_ptControlBenchmark.SetPoint(nXPos,nYPos);	
	m_ImageBack.LoadImage(hInstance,pszResourceName);
}

//控件区域
CRect CControlCheckButton::GetControlRect()
{
	int width = m_ImageBack.GetWidth();
	int wHeight = m_ImageBack.GetHeight();
	CRect rcClient(m_ptControlBenchmark.x,m_ptControlBenchmark.y,
	m_ptControlBenchmark.x+width/2,m_ptControlBenchmark.y+wHeight);

	return rcClient;
}

//设置状态
VOID  CControlCheckButton::SetButtonChecked(bool cbChecked) 
{ 
	//设置变量
	m_cbChecked=cbChecked;
	//定义变量
	CRect rcClient = GetControlRect();
	//重绘界面
	if(m_pParentSink!=NULL) 
		m_pParentSink->InvalidateRect(&rcClient);
};

//绘制控件
VOID  CControlCheckButton::OnDrawControl(CDC * pDC)
{
	//参数校验
	if(pDC==NULL)
		return;
	//定义变量
	INT nImageWidth = m_ImageBack.GetWidth()/2;
	INT nImageHeight = m_ImageBack->GetHeight();
	m_ImageBack.DrawImage(pDC,m_ptControlBenchmark.x, m_ptControlBenchmark.y,
		nImageWidth, nImageHeight,m_cbChecked?nImageWidth:0, 0);
}

//点击事件
bool  CControlCheckButton::OnClickControl(CPoint Point)
{
	//定义变量
	CRect rcClient = GetControlRect();
	//选中判断
	if(rcClient.PtInRect(Point))
	{
		//设置变量
		m_cbChecked=m_cbChecked==false?true:false;
		//重绘界面
		if(m_pParentSink!=NULL)	
			m_pParentSink->InvalidateRect(&rcClient);
		return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////

//构造函数
CDlgRegister::CDlgRegister() : CDialog(IDD_REGISTER)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLikeName[0]=0;
	m_szName[0]=0;
	m_szSFZ[0] = 0;
	m_szAddress[0]=0;
	m_cbLogonPassLevel = PASSWORD_LEVEL_0;
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
}

//初始化函数
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();
 
	//加载资源
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));
	int With = m_ImageBack->GetWidth();
	int Height = m_ImageBack->GetHeight();
	//设置大小
	CSize SizeWindow(With,Height);
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	m_ImagePasswordLevel.LoadImage(AfxGetInstanceHandle(),TEXT("PASSWORD_LEVEL"));

	m_btEixt.CreateButton(this,TEXT("PNG_BT_REGISTERCLOSE") ,_T("PNG"),With-50,5,WM_BT_REGISTERCLOSE,5);
	m_btRegisterOk.CreateButton(this,TEXT("PNG_BT_REGISTEROK") ,_T("PNG"),With/2-30,Height-30,WM_BT_REGISTEROK,5);
	m_btMan.CreatCheckButton(this,AfxGetInstanceHandle(),TEXT("PNG_BT_CHOSE"),110,277);
	m_btWoman.CreatCheckButton(this,AfxGetInstanceHandle(),TEXT("PNG_BT_CHOSE"),170,277);
	m_btMan.SetButtonChecked(true);
	
	//居中窗口
	CenterWindow(this);
	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;
	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);
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
		ShowInformation(TEXT("帐号名字的长度最短6个字符,最长13个字符,请重新输入注册帐号！"),10,MB_ICONQUESTION);
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

	//昵称
	GetDlgItemText(IDC_LIKENAME,strBuffer);
	if (strBuffer.GetLength()<4)
	{
		ShowInformation(TEXT("昵称必须4个字节或以上！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_LIKENAME)->SetFocus();
		return;
	}
	lstrcpyn(m_szLikeName,strBuffer,CountArray(m_szLikeName));

	//地址
	GetDlgItemText(IDC_Address1,strBuffer);
	if (strBuffer.GetLength()<4)
	{
		ShowInformation(TEXT("请输入地址！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_Address1)->SetFocus();
		return;
	}
	lstrcpyn(m_szAddress,strBuffer,CountArray(m_szAddress));


	//名字
	GetDlgItemText(IDC_EDIT_NAME,strBuffer);
	if (strBuffer.GetLength()<1)
	{
		ShowInformation(TEXT("请输入姓名！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}
	lstrcpyn(m_szName,strBuffer,CountArray(m_szName));

	//身份证
	GetDlgItemText(IDC_EDIT_SFZ,strBuffer);
	if (strBuffer.GetLength()!=18)
	{
		ShowInformation(TEXT("请输入正确的身份证号码！"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_SFZ)->SetFocus();
		return;
	}
	lstrcpyn(m_szSFZ,strBuffer,CountArray(m_szSFZ));

	m_wFaceID = 1;
	m_cbGender = 0;
	if(m_btMan.GetButtonChecked())
		m_cbGender = 1;
	else
		m_cbGender = 2;

	__super::OnOK();
}

//取消消息
void CDlgRegister::OnCancel()
{
	__super::OnCancel();
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


//鼠标弹起
void CDlgRegister::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bClick = false;
	if(!bClick)
	{
		if(!m_btWoman.GetButtonChecked())
		{
			bClick = m_btWoman.OnClickControl(point);
			if(bClick)
				m_btMan.SetButtonChecked(false);
		}
	}
	if(!bClick)
	{
		if( !m_btMan.GetButtonChecked())
		{
			bClick = m_btMan.OnClickControl(point);
			if(bClick)
				m_btWoman.SetButtonChecked(false);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}


//绘画背景
BOOL CDlgRegister::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	//绘制背景
	m_ImageBack.DrawImage(pDevC,0,0);
	m_btMan.OnDrawControl(pDevC);
	m_btWoman.OnDrawControl(pDevC);
	//绘制密码等级
	CSize SizePassword;
	SizePassword.SetSize(m_ImagePasswordLevel.GetWidth()/3,m_ImagePasswordLevel.GetHeight()/2);
	m_ImagePasswordLevel.DrawImage(pDevC,100,173,SizePassword.cx*3,SizePassword.cy,0,0);
	if (m_cbLogonPassLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		m_ImagePasswordLevel.DrawImage(pDevC,100+nImagePos,173,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	SetButtonBackGrounds(pDevC);

	return TRUE;
}

//按钮函数
void CDlgRegister::SetButtonBackGrounds(CDC *pDC)
{
	m_btEixt.SetBkGnd(pDC);
	m_btRegisterOk.SetBkGnd(pDC);
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

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLogon::CDlgLogon() : CDialog(IDD_LOGON)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLikeName[0]=0;
	m_szName[0]=0;
	m_szSFZ[0] = 0;
	m_szAddress[0]=0;
	m_LogonMode=LogonMode_Accounts;
	//辅助信息
	m_bRegister=false;
	//位置信息
	m_nFullWidth=0;
	m_nFullHeight=0;
	m_bNetOption=false;
	//设置键值
	lstrcpyn(m_szKeyboradNumber[0],TEXT("0123456789"),CountArray(m_szKeyboradNumber[0]));
	lstrcpyn(m_szKeyboradNumber[1],TEXT(")!@#$%^&*("),CountArray(m_szKeyboradNumber[1]));
	lstrcpyn(m_szKeyboradChar[0],TEXT("abcdefghijklmnopqrstyvwxyz"),CountArray(m_szKeyboradChar[0]));
	lstrcpyn(m_szKeyboradChar[1],TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),CountArray(m_szKeyboradChar[1]));
	m_bCaps = false;
	return;
}

//析构函数
CDlgLogon::~CDlgLogon()
{
	m_pPlatformFrame = NULL;
}

//控件绑定
void CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
}

//初始化函数
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();
	//加载资源
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	//设置大小
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_PasswordControl.SetDrawBorad(false);
	m_PasswordControl.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));

	//记住密码
	m_RemPwdControl.CreatCheckButton(this,AfxGetInstanceHandle(),TEXT("CHECK_BUTTON_BACK"),165,225);
	

	m_btCancel.LoadStdImage(TEXT("PNG_BT_LOGON_QUIT") ,_T("PNG"),5);
	m_btLogon.LoadStdImage(TEXT("PNG_BT_LOGON") ,_T("PNG"),5);
	m_btWebhome.CreateButton(this,TEXT("PNG_BT_WEBHOME"),_T("PNG"),175,75,WM_BT_WEBHOME,5);
	m_btRegister.CreateButton(this,TEXT("PNG_BT_REGISTER"),_T("PNG"),260,75,WM_BT_REGISTER,5);
	m_btChongzhi.CreateButton(this,TEXT("PNG_BT_CHONGZHI"),_T("PNG"),350,75,WM_BT_CHONGZHI,5);
	m_btBanben.CreateButton(this,TEXT("PNG_BT_BANBEN"),_T("PNG"),440,75,WM_BT_BANBEN,5);

	//创建软键盘
	m_btOther[0].CreateButton(this,TEXT("PNG_BT_KEYBOARD2"),_T("PNG"),414,312,WM_BT_KEYBOARD_MIN,3);
	m_btOther[1].CreateButton(this,TEXT("PNG_BT_KEYBOARD3"),_T("PNG"),414,349,WM_BT_KEYBOARD_MIN+1,3);
	TCHAR TempName[32];
	UINT windowsID = 0;
	int i=0;
	for (i=0;i<10;i++)
	{
		sprintf(TempName,TEXT("PNG_BT_KEYBOARD%d"),i+4);
		windowsID = WM_BT_KEYBOARD_MIN+2+i; 
		m_btNumber[i].CreateButton(this,TempName,_T("PNG"),30+(46+2)*i,275,windowsID,3);
	}
	for(i=0;i<26;i++)
	{
		sprintf(TempName,TEXT("PNG_BT_KEYBOARD%d"),i+14);
		windowsID = WM_BT_KEYBOARD_MIN+12+i; 
		if(i<8)
			m_btAlphabet[i].CreateButton(this,TempName,_T("PNG"),30+(46+2)*i,312,windowsID,3);
		else if(i<16)
			m_btAlphabet[i].CreateButton(this,TempName,_T("PNG"),30+(46+2)*(i-8),349,windowsID,3);
		else
			m_btAlphabet[i].CreateButton(this,TempName,_T("PNG"),30+(46+2)*(i-16),387,windowsID,3);
	}

	//居中窗口
	CenterWindow(this);
	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;
	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	LoadLogonServer();
	LoadAccountsInfo();

	return FALSE;
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
	if (CheckLogonInput(true)==false)
		return;

	//设置变量
	m_bRegister=false;

	//登录广场
	ShowWindow(SW_HIDE);
	//IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	//ASSERT(pIPlazaViewItem!=NULL);
	//pIPlazaViewItem->SendConnectMessage();

	if(m_pPlatformFrame != NULL)
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
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
				//构造数据
				CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;
				memset(pRegisterAccounts,0,sizeof(CMD_GP_RegisterAccounts));
				pRegisterAccounts->wFaceID=m_wFaceID;
				pRegisterAccounts->cbGender=m_cbGender;
				pRegisterAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				lstrcpyn(pRegisterAccounts->szPassWord,szPassword,CountArray(pRegisterAccounts->szPassWord));
				lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));
				
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
	//用户信息
	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
	//构造信息
	TCHAR szBuffer[256];
	_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s"),REG_USER_INFO);
	//写入信息
	CRegKey RegUserInfo;
	if (RegUserInfo.Create(HKEY_CURRENT_USER,szBuffer)==ERROR_SUCCESS)
	{
		RegUserInfo.SetKeyValue(TEXT(""),UserData.szAccounts,TEXT("UserAccount"));
		if (m_RemPwdControl.GetButtonChecked()==TRUE) 
		{
			TCHAR szPassBuffer[256]=TEXT("");
			CXOREncrypt::EncryptData(m_szPassword,szPassBuffer,CountArray(szPassBuffer));
			RegUserInfo.SetKeyValue(TEXT(""),szPassBuffer,TEXT("UserPassword"));
		}
		else
		{
			RegUserInfo.SetKeyValue(TEXT(""),TEXT(""),TEXT("UserPassword"));
		}
	}
	//关闭窗口
	DestroyWindow();

	return true;
}

//读取帐号
void CDlgLogon::LoadAccountsInfo()
{
	//加载其他信息
	CRegKey RegUserAccount;
	RegUserAccount.Open(HKEY_CURRENT_USER,REG_USER_INFO,KEY_READ);
	if (RegUserAccount!=NULL)
	{
		TCHAR szPassWord[256]=TEXT(""),szAccount[256]=TEXT("");
		DWORD dwType=REG_SZ;
		LONG lErrorCode=ERROR_SUCCESS;
		//游戏帐号
		DWORD dwSize=sizeof(szAccount);
		lErrorCode=RegUserAccount.QueryValue(TEXT("UserAccount"),&dwType,szAccount,&dwSize);
		if ((lErrorCode==ERROR_SUCCESS) && szAccount[0]!=0)
		{
			m_edAccounts.SetWindowText(szAccount);
		}
		//游戏密码
		dwSize=sizeof(szPassWord);
		lErrorCode=RegUserAccount.QueryValue(TEXT("UserPassword"),&dwType,szPassWord,&dwSize);
		if ((lErrorCode==ERROR_SUCCESS)&&(szPassWord[0]!=0))
		{
			TCHAR szPassBuffer[256]=TEXT("");
			CXOREncrypt::CrevasseData(szPassWord,szPassBuffer,CountArray(szPassWord));
			m_PasswordControl.SetUserPassword(szPassBuffer);
			if(szPassWord[0]!=0)
			{
				m_RemPwdControl.SetButtonChecked(true);
			}
		}
	}
}

//加载服务器
void CDlgLogon::LoadLogonServer()
{
	//读取最近登录服务器
	char szAppName[256];
	char szName[256];
	char szIP[32];
	_snprintf(szAppName, sizeof(szAppName), "Server0");
	GetOptionItem(szAppName, "Name",  szName, 256);
	GetOptionItem(szAppName, "IPAddress",  szIP, 32);
	m_strLogonServer.Format("%s",szIP);
	return;
}

////代理信息
//void CDlgLogon::LoadProxyServerInfo()
//{
//	//变量定义
//	LPCTSTR szProxyType[]={TEXT("不使用代理"),TEXT("HTTP 代理"),TEXT("SOCKS 4"),TEXT("SOCKS 5")};
//	enProxyServerType ProxyServerType[]={ProxyType_None,ProxyType_Http,ProxyType_Socks4,ProxyType_Socks5};
//
//	//获取信息
//	enProxyServerType CurrentProxyType=g_GlobalOption.m_ProxyServerType;
//	const tagProxyServerInfo & ProxyServerInfo=g_GlobalOption.m_ProxyServerInfo;
//
//	//加载类型
//	for (INT i=0;i<CountArray(szProxyType);i++)
//	{
//		ASSERT(i<CountArray(ProxyServerType));
//		INT nItem=m_cmProxyServerType.AddString(szProxyType[i]);
//		m_cmProxyServerType.SetItemData(nItem,ProxyServerType[i]);
//		if (CurrentProxyType==ProxyServerType[i]) m_cmProxyServerType.SetCurSel(nItem);
//	}
//
//	//设置信息
//	SetDlgItemText(IDC_PROXY_USER,ProxyServerInfo.szUserName);
//	SetDlgItemText(IDC_PROXY_PASS,ProxyServerInfo.szPassword);
//	SetDlgItemText(IDC_PROXY_SERVER,ProxyServerInfo.szProxyServer);
//	if (ProxyServerInfo.wProxyPort!=0) SetDlgItemInt(IDC_PROXY_PORT,ProxyServerInfo.wProxyPort);
//
//	//设置选择
//	if (m_cmProxyServerType.GetCurSel()==CB_ERR) m_cmProxyServerType.SetCurSel(0);
//
//	return;
//}

////查找数据
//int CDlgLogon::ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString)
//{
//	CString strBuffer;
//	int iItemHandle=LB_ERR,iItemFind=LB_ERR;
//	int nStringLen=lstrlen(pszFindString);
//	do 
//	{
//		iItemFind=pComboBox->FindString((iItemHandle==LB_ERR)?0:(iItemHandle+1),pszFindString);
//		if ((iItemFind==LB_ERR)||(iItemHandle==iItemFind)||(iItemFind<iItemHandle)) return LB_ERR;
//		iItemHandle=iItemFind;
//		pComboBox->GetLBText(iItemHandle,strBuffer);
//		if (pComboBox->GetLBTextLen(iItemHandle)==nStringLen) return iItemHandle;
//	} while (true);
//	return LB_ERR;
//}

//效验输入
bool CDlgLogon::CheckLogonInput(bool bShowError)
{
	UINT uControlID=0;
	try
	{
		//获取信息
		GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
		if (m_szAccounts[0] == 0)
		{
			uControlID=IDC_ACCOUNTS;
			throw TEXT("用户登录帐号不能为空，请重新输入登录帐号！");
		}

		//获取密码
		m_PasswordControl.GetUserPassword(m_szPassword);
		if (m_szPassword[0] == 0)
		{
			uControlID=IDC_PASSWORD;
			throw TEXT("登录密码不能为空，请重新输入登录密码！");
		}
		return true;
	}
	catch (LPCTSTR pszError)
	{
		if (bShowError)
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
			ShowInformation(pszError,0,MB_ICONQUESTION);
			if (uControlID!=0) 
				GetDlgItem(uControlID)->SetFocus();
		}

	}
	return false;
}
//
////更新选择
//void CDlgLogon::UpdateUserComboBox(UINT uComboBoxID)
//{
//	//获取 ID
//	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);
//	DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(pComboBox->GetCurSel());
//
//	//更新信息
//	UpdateUserPassWord(dwUserDBID);
//	UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
//	for (int i=0;i<CountArray(uComboBoxIDs);i++)
//	{
//		pComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
//		for (int j=0;j<pComboBox->GetCount();j++)
//		{
//			DWORD dwComboBoxID=(DWORD)pComboBox->GetItemData(j);
//			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwUserDBID))
//			{
//				pComboBox->SetCurSel(j);
//				break;
//			}
//		}
//	}
//
//	return;
//}
//
////更新密码
//void CDlgLogon::UpdateUserPassWord(DWORD dwUserDBID)
//{
//	if (dwUserDBID!=0L)
//	{
//		//注册表字符
//		CString strRegKey;
//		strRegKey.Format(TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);
//
//		//打开注册表
//		CRegKey RegPassWord;
//		RegPassWord.Open(HKEY_CURRENT_USER,strRegKey,KEY_READ);
//		if (RegPassWord!=NULL)
//		{
//			DWORD dwType=REG_SZ;
//			TCHAR szPassBuffer[256]=TEXT("");
//			DWORD dwBufferLength=sizeof(szPassBuffer);
//			if (RegPassWord.QueryValue(TEXT("UserPassword"),&dwType,szPassBuffer,&dwBufferLength)==ERROR_SUCCESS)
//			{
//				m_szPassword[0]=0;
//				CXOREncrypt::CrevasseData(szPassBuffer,m_szPassword,CountArray(m_szPassword));
//				if (m_szPassword[0]==0) 
//					SetDlgItemText(IDC_PASSWORD,TEXT(""));
//				else 
//					SetDlgItemText(IDC_PASSWORD,TEXT("**********"));
//				m_bChangePassWord=false;
//				return;
//			}
//		}
//	}
//
//	//设置信息
//	m_szPassword[0]=0;
//	SetDlgItemText(IDC_PASSWORD,TEXT(""));
//	m_bChangePassWord=false;
//	
//	return;
//}

////代理模式
//void CDlgLogon::SwitchNetOption(bool bNetOption)
//{
//	//设置变量
//	m_bNetOption=bNetOption;
//
//	//控件设置
//	GetDlgItem(IDC_PROXY_TYPE)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_PORT)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_USER)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_PASS)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_TEST)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_SERVER)->EnableWindow(m_bNetOption);
//
//	//移动位置
//	INT nHeight=m_bNetOption?m_nFullHeight:m_rcNormalFrame.Height();
//	SetWindowPos(NULL,0,0,m_nFullWidth,nHeight,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);
//
//	return;
//}
//
////密码改变
//void CDlgLogon::OnEnChangePassword()
//{
//	m_bChangePassWord=true;
//}
//
////选择改变
//void CDlgLogon::OnSelchangeAccounts()
//{
//	UpdateUserComboBox(IDC_ACCOUNTS);
//	return;
//}
//
////选择改变
//void CDlgLogon::OnSelchangeUserID()
//{
//	UpdateUserComboBox(IDC_USER_ID);
//	return;
//}


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
	lstrcpy(m_szAccounts,DlgRegister.m_szAccounts);
	lstrcpy(m_szPassword,DlgRegister.m_szPassword);
	lstrcpy(m_szSFZ,DlgRegister.m_szSFZ);
	lstrcpy(m_szName,DlgRegister.m_szName);
	lstrcpy(m_szAddress,DlgRegister.m_szAddress);
	lstrcpy(m_szLikeName,DlgRegister.m_szLikeName);

	//登录广场
	ShowWindow(SW_HIDE);
	//IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	//ASSERT(pIPlazaViewItem!=NULL);
	//pIPlazaViewItem->SendConnectMessage();
	if(m_pPlatformFrame != NULL)
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return;
}

void CDlgLogon::OnWebhome()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}

void CDlgLogon::OnChongzhi()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}

void CDlgLogon::OnBanben()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}


//重画消息
void CDlgLogon::OnPaint()
{
	return;
}

//绘画背景
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	m_ImageBack.DrawImage(pDevC,0,0);
	m_RemPwdControl.OnDrawControl(pDevC);
	SetButtonBackGrounds(pDevC);
	return TRUE;
}

	//按钮函数
void CDlgLogon::SetButtonBackGrounds(CDC *pDC)
{
	m_btLogon.SetBkGnd(pDC);
	m_btCancel.SetBkGnd(pDC);
	m_btWebhome.SetBkGnd(pDC);
	m_btRegister.SetBkGnd(pDC);
	m_btChongzhi.SetBkGnd(pDC);
	m_btBanben.SetBkGnd(pDC);
	//key board
	m_btOther[0].SetBkGnd(pDC);
	m_btOther[1].SetBkGnd(pDC);
	for (int i=0;i<10;i++)
	{
		m_btNumber[i].SetBkGnd(pDC);
	}
	for (int i=0;i<26;i++)
	{
		m_btAlphabet[i].SetBkGnd(pDC);
	}
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


//鼠标弹起
void CDlgLogon::OnLButtonUp(UINT nFlags, CPoint point)
{
	//选中事件
	m_RemPwdControl.OnClickControl(point);

	CDialog::OnLButtonUp(nFlags, point);
}

////控件改变
//void CDlgLogon::OnEnChangeAccounts()
//{
//	//虚假密码
//	if(m_PasswordControl.m_hWnd!=NULL && m_PasswordControl.IsFalsityPassword()==true)
//	{
//		//密码设置
//		m_PasswordControl.SetUserPassword(TEXT(""));
//
//		//安全设置
//		m_RemPwdControl.SetButtonChecked(FALSE);
//	}
//}
//
////获取代理
//void CDlgLogon::GetProxyInfo(enProxyServerType &ProxyServerType, tagProxyServerInfo &ProxyServerInfo)
//{
//	//代理类型
//	CComboBox * pComProxyType=(CComboBox *)GetDlgItem(IDC_PROXY_TYPE);
//	ProxyServerType=(enProxyServerType)pComProxyType->GetItemData(pComProxyType->GetCurSel());
//
//	//代理信息
//	ZeroMemory(&ProxyServerInfo,sizeof(ProxyServerInfo));
//	ProxyServerInfo.wProxyPort=GetDlgItemInt(IDC_PROXY_PORT);
//	GetDlgItemText(IDC_PROXY_USER,ProxyServerInfo.szUserName,CountArray(ProxyServerInfo.szUserName));
//	GetDlgItemText(IDC_PROXY_PASS,ProxyServerInfo.szPassword,CountArray(ProxyServerInfo.szPassword));
//	GetDlgItemText(IDC_PROXY_SERVER,ProxyServerInfo.szProxyServer,CountArray(ProxyServerInfo.szProxyServer));
//
//	//效验代理
//	if (ProxyServerType!=ProxyType_None)
//	{
//		//代理地址
//		if (ProxyServerInfo.szProxyServer[0]==0)
//		{
//			if (m_bNetOption==false) SwitchNetOption(true);
//			m_edProxyServer.SetFocus();
//			throw TEXT("代理服务器地址不能为空，请重新输入！");
//		}
//
//		//代理端口
//		if (ProxyServerInfo.wProxyPort==0)
//		{
//
//			if (m_bNetOption==false) SwitchNetOption(true);
//			m_edProxyPort.SetFocus();
//			throw TEXT("请输入代理服务器端口号，例如：1080！");
//		}
//	}
//}

//响应软键盘
void CDlgLogon::OnKeyBoard(UINT uID)
{
	int nInx = uID - WM_BT_KEYBOARD_MIN;
	switch(nInx)
	{
	case 0: //删除按钮
		{
			m_PasswordControl.m_edPassword.SetFocus();
			m_PasswordControl.m_edPassword.SendMessage(WM_CHAR,VK_BACK,0L);
			break;
		}
	case 1: //大写
		{
			OutputDebugString("大写 \r\n");\
			m_PasswordControl.m_edPassword.SetFocus();
			m_bCaps = !m_bCaps;
			SwitchChar(m_bCaps);
			CRect FramRect;
			GetClientRect(FramRect);
			CRect rect(0,FramRect.bottom/2,FramRect.right,FramRect.bottom);
			InvalidateRect(rect,TRUE);
			break;
		}
	default:
		{
			m_PasswordControl.m_edPassword.SetFocus();
			//数字键
			WORD wViraulCode = 0;
			if((nInx >= 2) && (nInx < 12))
			{
				OutputDebugString("点击了数字键 \r\n");

				if((GetKeyState(VK_SHIFT)&0xF0)>0)
					wViraulCode = (WORD)m_szKeyboradNumber[1][nInx-2];
				else
					wViraulCode = (WORD)m_szKeyboradNumber[0][nInx-2];
			}
			else//字母键
			{
				OutputDebugString("点击了字母 \r\n");
				
				if(m_bCaps)
					wViraulCode = (WORD)m_szKeyboradChar[1][nInx-12];
				else
					wViraulCode = (WORD)m_szKeyboradChar[0][nInx-12];
			}
			m_PasswordControl.m_edPassword.SendMessage(WM_CHAR,wViraulCode,0L);
			break;
		}
	}
}

//大小写切换
void CDlgLogon::SwitchChar(bool bCaps)
{
	int i = 0;
	TCHAR TempName[256] = TEXT("");
	if(bCaps)
	{
		for(i=0;i<26;i++)
		{
			sprintf(TempName,TEXT("PNG_BT_KEYBOARD%d"),i+40);
			m_btAlphabet[i].ResetAltImage(TempName,_T("PNG"));
		}
	}
	else
	{
		for(i=0;i<26;i++)
		{
			sprintf(TempName,TEXT("PNG_BT_KEYBOARD%d"),i+14);
			m_btAlphabet[i].ResetAltImage(TempName,_T("PNG"));
		}
	}
}

//////////////////////////////////////////////////////////////////////////

