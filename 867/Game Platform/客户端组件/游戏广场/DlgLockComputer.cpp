#include "stdafx.h"
#include"resource.h"
#include "DlgLockComputer.h"
#include "GameFrame.h"
#include "GlobalUnits.h"
#include "Zip.h"

////////////////////////////////////////////////////////////////////////////////////
//宏定义
#define DEF_INSIDEBORDER_COLOR	RGB(176,20,1)						//默认颜色

#define BGROUND_COLOR			RGB(254,250,221)					//背景颜色
#define FRAME_TL_COLOR1			RGB(128,128,128)					//边框颜色
#define FRAME_TL_COLOR2			RGB(64,64,64)						//边框颜色
#define FRAME_RB_COLOR2			RGB(212,208,200)					//边框颜色
#define FRAME_RB_COLOR1			RGB(212,208,200)					//边框颜色

#define SMALL_FACE_WIDTH		32									//图片大小
#define SMALL_FACE_HEIGHT		32									//图片大小

#define LARGE_FACE_WIDTH		100									//图片大小
#define LARGE_FACE_HEIGHT		100									//图片大小

#define SMALL_FRAME_LEFT		235									//边框位置
#define SMALL_FRAME_RIGHT		(SMALL_FRAME_LEFT+SMALL_FACE_WIDTH)	//边框位置
#define SMALL_FRAME_TOP			105									//边框位置
#define SMALL_FRAME_BOTTOM		(SMALL_FRAME_TOP+SMALL_FACE_HEIGHT)	//边框位置

#define LARGE_FRAME_LEFT		50									//边框位置
#define LARGE_FRAME_RIGHT		(LARGE_FRAME_LEFT+LARGE_FACE_WIDTH)	//边框位置
#define LARGE_FRAME_TOP			75									//边框位置
#define LARGE_FRAME_BOTTOM		(LARGE_FRAME_TOP+LARGE_FACE_HEIGHT)	//边框位置

#define FRAME_SPACE				2									//边框宽度

////////////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CDlgLockComputer, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK,OnBnClickedOK) 
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLockComputer::CDlgLockComputer(CWnd* pParent): CDialog(IDD_LOCKCOMPUTER, pParent), CSkinWndObject(this)
{
	//设置变量
	m_pIClientSocket = NULL;
	m_enOperateStatus=enOperateStatus_NULL;
	m_szLogonPws[0]=0;
}

//虚构函数
CDlgLockComputer::~CDlgLockComputer()
{
	//释放资源
	if (m_brBkground.m_hObject != NULL ) m_brBkground.DeleteObject();
}

//交换函数
void CDlgLockComputer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
}

//初始函数
BOOL CDlgLockComputer::OnInitDialog()
{
	__super::OnInitDialog();
	((CComboBox *)(GetDlgItem(IDC_LogonPws)))->LimitText(NAME_LEN-1);
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//创建刷子
	m_brBkground.CreateSolidBrush(BGROUND_COLOR);

	//设置标题
	SetWindowText(TEXT("锁机"));

	//更新控件
	UpdateControls();

	//初始化设置
	__super::InitSkinObject();

	return TRUE;  
}

//绘画函数
void CDlgLockComputer::OnPaint()
{
	CPaintDC dc(this);
	//绘画标题
	__super::DrawSkinView(&dc);
}

//确定
void CDlgLockComputer::OnBnClickedOK()
{
	CString strBuffer;
	GetDlgItemText(IDC_LogonPws,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.IsEmpty())
	{
		ShowMessage("请先输入登录密码");
		return;
	}
	lstrcpyn(m_szLogonPws,strBuffer,CountArray(m_szLogonPws));

	//设置状态
	m_enOperateStatus = enOperateStatus_Upload;
	//链接网络
	if ( ConnectServer() == false )
	{
		//设置状态
		m_enOperateStatus = enOperateStatus_NULL;
		return;
	}

	//更新控件
	UpdateControls();
	//更新界面
	InvalidateRect(NULL);
}

//显示消息
void CDlgLockComputer::ShowMessage(TCHAR *pMessage)
{
	ShowInformationEx(pMessage,0,MB_ICONQUESTION,TEXT("锁机"));

	return;
}

//网络链接
bool CDlgLockComputer::ConnectServer()
{
	if ( m_pIClientSocket != NULL && m_pIClientSocket->GetSocketStatus() == SOCKET_STATUS_CONNECT )//?GetSocketStatus
	{
		SendData();
		return true;
	}

	//获取大厅
	CGameFrame *pGameFrame = (CGameFrame *)AfxGetMainWnd() ;
	CPlazaViewItem * pPlazaViewItem = &(pGameFrame->m_DlgGamePlaza) ;
	if ( m_pIClientSocket == NULL )
	{

		//合法判断
		if ( pPlazaViewItem->m_ClientSocket.GetInterface() == NULL ) 
		{
			ShowMessage(TEXT("网络组件还没有创建，请重新登录！"));
			return false;
		}

		//设置变量
		m_pIClientSocket = (ITCPSocket*)pPlazaViewItem->m_ClientSocket.GetInterface();
	}

	//地址解释
	CRegKey RegServer;
	LPCTSTR pszServerIP=pPlazaViewItem->m_DlgLogon.GetLogonServer();
	TCHAR szRegServer[256]=TEXT(""),szServerAddr[64]=TEXT("");
	_snprintf(szRegServer,sizeof(szRegServer),TEXT("%s\\%s"),REG_LOGON_SERVER,pszServerIP);

	if (RegServer.Open(HKEY_CURRENT_USER,szRegServer,KEY_READ)==ERROR_SUCCESS)
	{
		TCHAR szReadData[1024]=TEXT("");
		DWORD dwReadData=0L,dwDataType=0L,dwDataSize=sizeof(szReadData);
		LONG lErrorCode=RegServer.QueryValue(TEXT("ServerAddr"),&dwDataType,szReadData,&dwDataSize);
		if (lErrorCode==ERROR_SUCCESS) 
		{
			CXOREncrypt::CrevasseData(szReadData,szServerAddr,sizeof(szServerAddr));
			pszServerIP=szServerAddr;
		}
	}

	//连接服务器
	try
	{
		//连接服务器
		m_pIClientSocket->CloseSocket();
		if (m_pIClientSocket->Connect(pszServerIP,PORT_LOGON_SERVER)!=ERROR_SUCCESS)
		{
			throw TEXT("服务器连接错误，可能是你的系统还没有成功连接上网络！");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessage((TCHAR*)pszError);
		return false;
	}

	return true;
}

//发送数据
bool CDlgLockComputer::SendData()
{
	//状态判断
	ASSERT(m_enOperateStatus != enOperateStatus_NULL);
	if ( m_enOperateStatus == enOperateStatus_NULL ) return false;

	if ( m_pIClientSocket == NULL || m_pIClientSocket->GetSocketStatus() != SOCKET_STATUS_CONNECT )
		return false;

	if ( m_enOperateStatus == enOperateStatus_Upload )
	{
		//变量定义
		TCHAR szPassword[33];
		BYTE cbBuffer[SOCKET_PACKET];
		CMD5Encrypt::EncryptData(m_szLogonPws,szPassword);

		tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
		CMD_GP_LockComputer * plock=(CMD_GP_LockComputer *)cbBuffer;
		memset(plock,0,sizeof(CMD_GP_LockComputer));
		plock->lUserID=GlobalUserData.dwUserID;
		CopyMemory(plock->szPassWord,szPassword,sizeof(plock->szPassWord));
		//机器序列号
		tagClientSerial ClientSerial;
		g_GlobalUnits.GetClientSerial(ClientSerial);
		//发送数据包
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LockComputer),sizeof(cbBuffer)-sizeof(CMD_GP_LockComputer));
		Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
		m_pIClientSocket->SendData(MDM_GP_USER,SUB_GP_LOCKCOMPUTER,cbBuffer,sizeof(CMD_GP_LockComputer)+Packet.GetDataSize());
	
	}
	//设置状态
	m_enOperateStatus = enOperateStatus_NULL ;
	return true;
}

//更新控件
void CDlgLockComputer::UpdateControls()
{
	tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
	//如果账号锁定
	if(GlobalUserData.cbMoorMachine != 0)
	{
		SetDlgItemText(IDC_LOCKTEXT,"本账号已经使用了锁定功能！！");
		SetDlgItemText(IDOK,"解除锁定");
	}
	else//没有锁定
	{
		SetDlgItemText(IDC_LOCKTEXT,"本账号还没有锁定！！");
		SetDlgItemText(IDOK,"锁定");
	}
	//更新界面
	InvalidateRect(NULL);
}

//颜色处理
HBRUSH CDlgLockComputer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//显示消息
void CDlgLockComputer::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	//更新控件
	if ( bShow ) UpdateControls();
}

//销毁消息
void CDlgLockComputer::OnClose()
{
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//释放资源
	if(m_pIClientSocket==NULL)
		return;
	m_pIClientSocket->CloseSocket();

	m_enOperateStatus = enOperateStatus_NULL;

	CDialog::OnClose();
}

//鼠标信息
void CDlgLockComputer::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	OnLMouseDownEvent(point);
}

//鼠标信息
void CDlgLockComputer::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
	OnLMouseUpEvent(point);
}

//鼠标信息
void CDlgLockComputer::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
	OnMouseMoveEvent(point);
}
////////////////////////////////////////////////////////////////////////////////////