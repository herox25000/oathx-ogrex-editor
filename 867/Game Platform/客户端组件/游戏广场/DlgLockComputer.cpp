#include "stdafx.h"
#include"resource.h"
#include "DlgLockComputer.h"
#include "GameFrame.h"
#include "GlobalUnits.h"
#include "Zip.h"



////////////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CDlgLockComputer, CSkinPngDialog)
	ON_BN_CLICKED(IDOK,OnBnClickedOK) 
	ON_WM_CLOSE()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLockComputer::CDlgLockComputer(CWnd* pParent): CSkinPngDialog(IDD_LOCKCOMPUTER, pParent)//, CSkinWndObject(this)
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
	//设置标题
	SetWindowText(TEXT("绑定机器设置"));

	((CComboBox *)(GetDlgItem(IDC_LogonPws)))->LimitText(NAME_LEN-1);
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//更新控件
	UpdateControls();

	return TRUE;  
}

//绘画函数
void CDlgLockComputer::OnPaint()
{
	CPaintDC dc(this);
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
	m_btOk.SetWindowText((GlobalUserData.cbMoorMachine== 0 )?TEXT("绑定本机"):TEXT("解除绑定"));
	//更新界面
	InvalidateRect(NULL);
}


//销毁消息
void CDlgLockComputer::OnClose()
{
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//释放资源
	if(m_pIClientSocket!=NULL)
		m_pIClientSocket->CloseSocket();

	m_enOperateStatus = enOperateStatus_NULL;

	__super::OnClose();
}

void CDlgLockComputer::OnCancel()
{
	__super::OnCancel();
}



////////////////////////////////////////////////////////////////////////////////////