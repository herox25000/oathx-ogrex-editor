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

//���캯��
CDlgLockComputer::CDlgLockComputer(CWnd* pParent): CSkinPngDialog(IDD_LOCKCOMPUTER, pParent)//, CSkinWndObject(this)
{
	//���ñ���
	m_pIClientSocket = NULL;
	m_enOperateStatus=enOperateStatus_NULL;
	m_szLogonPws[0]=0;
}

//�鹹����
CDlgLockComputer::~CDlgLockComputer()
{
	//�ͷ���Դ
	if (m_brBkground.m_hObject != NULL ) m_brBkground.DeleteObject();
}

//��������
void CDlgLockComputer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
}

//��ʼ����
BOOL CDlgLockComputer::OnInitDialog()
{
	__super::OnInitDialog();
	//���ñ���
	SetWindowText(TEXT("�󶨻�������"));

	((CComboBox *)(GetDlgItem(IDC_LogonPws)))->LimitText(NAME_LEN-1);
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//���¿ؼ�
	UpdateControls();

	return TRUE;  
}

//�滭����
void CDlgLockComputer::OnPaint()
{
	CPaintDC dc(this);
}

//ȷ��
void CDlgLockComputer::OnBnClickedOK()
{
	CString strBuffer;
	GetDlgItemText(IDC_LogonPws,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.IsEmpty())
	{
		ShowMessage("���������¼����");
		return;
	}
	lstrcpyn(m_szLogonPws,strBuffer,CountArray(m_szLogonPws));

	//����״̬
	m_enOperateStatus = enOperateStatus_Upload;
	//��������
	if ( ConnectServer() == false )
	{
		//����״̬
		m_enOperateStatus = enOperateStatus_NULL;
		return;
	}

	//���¿ؼ�
	UpdateControls();
	//���½���
	InvalidateRect(NULL);
}

//��ʾ��Ϣ
void CDlgLockComputer::ShowMessage(TCHAR *pMessage)
{
	ShowInformationEx(pMessage,0,MB_ICONQUESTION,TEXT("����"));

	return;
}

//��������
bool CDlgLockComputer::ConnectServer()
{
	if ( m_pIClientSocket != NULL && m_pIClientSocket->GetSocketStatus() == SOCKET_STATUS_CONNECT )//?GetSocketStatus
	{
		SendData();
		return true;
	}

	//��ȡ����
	CGameFrame *pGameFrame = (CGameFrame *)AfxGetMainWnd() ;
	CPlazaViewItem * pPlazaViewItem = &(pGameFrame->m_DlgGamePlaza) ;
	if ( m_pIClientSocket == NULL )
	{

		//�Ϸ��ж�
		if ( pPlazaViewItem->m_ClientSocket.GetInterface() == NULL ) 
		{
			ShowMessage(TEXT("���������û�д����������µ�¼��"));
			return false;
		}

		//���ñ���
		m_pIClientSocket = (ITCPSocket*)pPlazaViewItem->m_ClientSocket.GetInterface();
	}

	//��ַ����
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

	//���ӷ�����
	try
	{
		//���ӷ�����
		m_pIClientSocket->CloseSocket();
		if (m_pIClientSocket->Connect(pszServerIP,PORT_LOGON_SERVER)!=ERROR_SUCCESS)
		{
			throw TEXT("���������Ӵ��󣬿��������ϵͳ��û�гɹ����������磡");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessage((TCHAR*)pszError);
		return false;
	}

	return true;
}

//��������
bool CDlgLockComputer::SendData()
{
	//״̬�ж�
	ASSERT(m_enOperateStatus != enOperateStatus_NULL);
	if ( m_enOperateStatus == enOperateStatus_NULL ) return false;

	if ( m_pIClientSocket == NULL || m_pIClientSocket->GetSocketStatus() != SOCKET_STATUS_CONNECT )
		return false;

	if ( m_enOperateStatus == enOperateStatus_Upload )
	{
		//��������
		TCHAR szPassword[33];
		BYTE cbBuffer[SOCKET_PACKET];
		CMD5Encrypt::EncryptData(m_szLogonPws,szPassword);

		tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
		CMD_GP_LockComputer * plock=(CMD_GP_LockComputer *)cbBuffer;
		memset(plock,0,sizeof(CMD_GP_LockComputer));
		plock->lUserID=GlobalUserData.dwUserID;
		CopyMemory(plock->szPassWord,szPassword,sizeof(plock->szPassWord));
		//�������к�
		tagClientSerial ClientSerial;
		g_GlobalUnits.GetClientSerial(ClientSerial);
		//�������ݰ�
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LockComputer),sizeof(cbBuffer)-sizeof(CMD_GP_LockComputer));
		Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
		m_pIClientSocket->SendData(MDM_GP_USER,SUB_GP_LOCKCOMPUTER,cbBuffer,sizeof(CMD_GP_LockComputer)+Packet.GetDataSize());
	
	}
	//����״̬
	m_enOperateStatus = enOperateStatus_NULL ;
	return true;
}

//���¿ؼ�
void CDlgLockComputer::UpdateControls()
{
	tagGlobalUserData &GlobalUserData = g_GlobalUnits.GetGolbalUserData();
	m_btOk.SetWindowText((GlobalUserData.cbMoorMachine== 0 )?TEXT("�󶨱���"):TEXT("�����"));
	//���½���
	InvalidateRect(NULL);
}


//������Ϣ
void CDlgLockComputer::OnClose()
{
	SetDlgItemText(IDC_LogonPws,TEXT(""));
	//�ͷ���Դ
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