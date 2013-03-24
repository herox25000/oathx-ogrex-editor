#include "Stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"
#include "CMD_ToolBox.h"
#include "Encrypt.h"
#include "GlobalFrame.h"
#include ".\gameclientdlg.h"

////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientDlg, CBitmapDialog)
	ON_BN_CLICKED(IDC_MODIFY_LOGIN_PASSWORD,OnModifyLoginPassword)
	ON_BN_CLICKED(IDC_MODIFY_BANK_PASSWORD,OnModifyBankPassword)
	ON_BN_CLICKED(IDC_MODIFY_NICKNAME,OnModifyNickname)
	ON_BN_CLICKED(IDC_BANK_QUERY,OnBankQuery)
	ON_BN_CLICKED(IDC_DEPOSIT,OnBankDeposit)
	ON_BN_CLICKED(IDC_WITHDRAW,OnBankWithdraw)
	ON_BN_CLICKED(IDC_TRANSFER_MONEY,OnTransferMoney)
	ON_BN_CLICKED(IDC_QUERY_TRANSFER_LOG,OnQueryTransferLog)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedCloseButton)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT19, OnEnChangeUserID)
END_MESSAGE_MAP()

CString GetString(__int64 nNumber)
{
	CString strTemp;
	strTemp.Format("%I64d", nNumber);
	int nIndex = strTemp.GetLength()-3;
	while(nIndex>0)
	{
		if(nIndex==1&&nNumber<0)
		{
			break;
		}
		strTemp.Insert(nIndex, ',');
		nIndex-=3;
	}
	return strTemp;
}

//���캯��
CGameClientDlg::CGameClientDlg() : CBitmapDialog(IDD_GAME_FRAME)
{
}

//��������
CGameClientDlg::~CGameClientDlg()
{
}
//������ַ
WORD CGameClientDlg::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
{
	//��������
	WORD wMacSize=0;
	HINSTANCE hInstance=NULL;
	typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

	try
	{
		//���� DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) throw TEXT("���� NetApi32.dll ʧ��");

		//��ȡ����
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) throw TEXT("�޷��ҵ� NetBios ����");

		//��������
		NCB Ncb;
		LANA_ENUM LanaEnum;
		ZeroMemory(&Ncb,sizeof(Ncb));
		ZeroMemory(&LanaEnum,sizeof(LanaEnum));

		//ö������
		Ncb.ncb_command=NCBENUM;
		Ncb.ncb_length=sizeof(LanaEnum);
		Ncb.ncb_buffer=(BYTE *)&LanaEnum;
		if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("ö������ʧ��");
		if (LanaEnum.length==0) throw TEXT("�Ҳ����κ�����");

		//��ȡ��ַ
		tagAstatInfo Adapter;
		for (BYTE i=0;i<LanaEnum.length;i++)
		{
			//��������
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("��������ʧ��");

			//��ȡ״̬
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("��ȡ����״̬ʧ��");

			//��ȡ��ַ
			if (wMacSize<wBufferSize)
			{
				//������ַ
				WORD wCopySize=__min((wBufferSize-wMacSize),sizeof(BYTE)*6);
				CopyMemory(cbMacBuffer,Adapter.AdapterStatus.adapter_address,wCopySize);

				//����ж�
				wMacSize+=wCopySize;
				if (wMacSize==wBufferSize) break;
			}
		}

		//�ͷ���Դ
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}

		return wMacSize;
	}
	catch (...) 
	{ 
		//�ͷ���Դ
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}
	}

	return wMacSize;
}


//��ȡ����
void CGameClientDlg::GetClientSerial(tagClientSerial & ClientSerial)
{
	//��ȡ�汾
	OSVERSIONINFO OSVerInfo;
	OSVerInfo.dwOSVersionInfoSize=sizeof(OSVerInfo);
	GetVersionEx(&OSVerInfo);
	ClientSerial.dwSystemVer=MAKELONG(OSVerInfo.dwMajorVersion,OSVerInfo.dwMinorVersion);

	//������ʶ
	ZeroMemory(ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));
	WORD wMacSize=GetMACAddress((BYTE *)ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));

	//Ӳ�̱�ʶ
	WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
	LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
	for (WORD i=wIndex;i<CountArray(ClientSerial.dwComputerID);i++)
	{
		ASSERT(CountArray(pszHardDisk)>(i-wIndex));
		GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,&ClientSerial.dwComputerID[i],NULL,NULL,0,NULL);
	}

	return;
}

BOOL CGameClientDlg::IsValidPassword(CString str)
{
	if ( str.IsEmpty() )
		return FALSE;

	for (int i=0; i<str.GetLength(); i++)
	{
		TCHAR szChar=str[i];
	}
	return TRUE;
}

__int64 CGameClientDlg::GetDlgItemInt64(UINT uID)
{
	TCHAR szText[256];
	GetDlgItemText(uID, szText, sizeof(szText));
	return _atoi64(szText);
};

void CGameClientDlg::SetDlgItemInt64(UINT uID, __int64 value)
{
	TCHAR szText[256];
	_snprintf(szText, sizeof(szText), "%I64d", value);
	SetDlgItemText(uID, szText);
};

void CGameClientDlg::Msg(LPCTSTR lpszText)
{
	AfxMessageBox(TEXT(lpszText));
	//ShowInformationEx(TEXT(lpszText),0 ,MB_ICONINFORMATION,TEXT("������Ϣ")) ;
}

void CGameClientDlg::ShowWaitWindow()
{
	m_TipDialog.CenterWindow();
	m_TipDialog.ShowWindow(1);
	m_TipDialog.SetDlgItemText(IDC_MSG, TEXT("���ڵȴ���������Ӧ......"));
}

void CGameClientDlg::OnModifyLoginPassword()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strP1;
	CString strP2;
	CString strP3;

	GetDlgItemText(IDC_EDIT1, strP1);
	GetDlgItemText(IDC_EDIT2, strP2);
	GetDlgItemText(IDC_EDIT3, strP3);

	strP1.Trim();
	strP2.Trim();
	strP3.Trim();

	if (strP1.IsEmpty() || strP2.IsEmpty() || strP3.IsEmpty())
	{
		Msg("��½���벻��Ϊ��");
		return;
	}

	if (strP2!=strP3)
	{
		Msg("���������벻һ��");
		return;
	}

	CMD_Modify_Login_Password cmd;
	memset(&cmd, 0, sizeof(CMD_Modify_Login_Password));

	//��������
	CMD5Encrypt::EncryptData(strP1, cmd.szOLDPassword);
	CMD5Encrypt::EncryptData(strP2, cmd.szNEWPassword);

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_MODIFY_LOGIN_PASSWORD, &cmd, sizeof(CMD_Modify_Login_Password));

	GetDlgItem(IDC_MODIFY_LOGIN_PASSWORD)->EnableWindow(0);
	ShowWaitWindow();

	SetDlgItemText(IDC_EDIT1, 0);
	SetDlgItemText(IDC_EDIT2, 0);
	SetDlgItemText(IDC_EDIT3, 0);
}

void CGameClientDlg::OnModifyBankPassword()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strP1;
	CString strP2;
	CString strP3;

	GetDlgItemText(IDC_EDIT4, strP1);
	GetDlgItemText(IDC_EDIT5, strP2);
	GetDlgItemText(IDC_EDIT6, strP3);

	strP1.Trim();
	strP2.Trim();
	strP3.Trim();

	if (strP1.IsEmpty() || strP2.IsEmpty() || strP3.IsEmpty())
	{
		Msg("�������벻��Ϊ��");
		return;
	}

	if (strP2!=strP3)
	{
		Msg("�������������벻һ��");
		return;
	}

	CMD_Modify_Bank_Password cmd;
	memset(&cmd, 0, sizeof(CMD_Modify_Bank_Password));

	CMD5Encrypt::EncryptData(strP1, cmd.szOLDPassword);
	CMD5Encrypt::EncryptData(strP2, cmd.szNEWPassword);

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_MODIFY_BANK_PASSWORD, &cmd, sizeof(CMD_Modify_Bank_Password));

	GetDlgItem(IDC_MODIFY_BANK_PASSWORD)->EnableWindow(0);
	ShowWaitWindow();

	SetDlgItemText(IDC_EDIT4, 0);
	SetDlgItemText(IDC_EDIT5, 0);
	SetDlgItemText(IDC_EDIT6, 0);
}

void CGameClientDlg::OnModifyNickname()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strNickname;
	GetDlgItemText(IDC_EDIT7, strNickname);
	strNickname.Trim();
	if (strNickname.IsEmpty())
	{
		Msg("�ǳƲ���Ϊ��");
		return;
	}

	CMD_Modify_Nickname cmd;
	memset(&cmd, 0, sizeof(CMD_Modify_Nickname));
	GetDlgItemText(IDC_EDIT7, cmd.szNickname, sizeof(cmd.szNickname));
	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_MODIFY_NICKNAME, &cmd, sizeof(CMD_Modify_Nickname));
	
	GetDlgItem(IDC_MODIFY_NICKNAME)->EnableWindow(1);
	ShowWaitWindow();

	SetDlgItemText(IDC_EDIT7, 0);
}

void CGameClientDlg::OnBankQuery()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strPassword;
	GetDlgItemText(IDC_EDIT8, strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		Msg("�������벻��Ϊ��");
		return;
	}

	CMD_GF_BankTask cmd;
	memset(&cmd, 0, sizeof(CMD_GF_BankTask));

	cmd.lBankTask=BANKTASK_QUERY;
	cmd.lMoneyNumber=0;
	CMD5Encrypt::EncryptData(strPassword, cmd.szPassword);

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_BANK, &cmd, sizeof(CMD_GF_BankTask));

	GetDlgItem(IDC_DEPOSIT)->EnableWindow(0);
	GetDlgItem(IDC_WITHDRAW)->EnableWindow(0);
	GetDlgItem(IDC_BANK_QUERY)->EnableWindow(0);
	ShowWaitWindow();
}

void CGameClientDlg::OnBankDeposit()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strPassword;
	GetDlgItemText(IDC_EDIT8, strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		Msg("�������벻��Ϊ��");
		return;
	}

	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT9);
	if ( sfMoeny<=0 )
	{
		Msg("���Ľ����������");
		return;
	}

	CMD_GF_BankTask cmd;
	memset(&cmd, 0, sizeof(CMD_GF_BankTask));

	cmd.lBankTask=BANKTASK_DEPOSIT;
	cmd.lMoneyNumber=GetDlgItemInt64(IDC_EDIT9);
	CMD5Encrypt::EncryptData(strPassword, cmd.szPassword);

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_BANK, &cmd, sizeof(CMD_GF_BankTask));
	
	GetDlgItem(IDC_DEPOSIT)->EnableWindow(0);
	GetDlgItem(IDC_WITHDRAW)->EnableWindow(0);
	GetDlgItem(IDC_BANK_QUERY)->EnableWindow(0);

	ShowWaitWindow();

	SetDlgItemText(IDC_EDIT9, 0);
}

void CGameClientDlg::OnBankWithdraw()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strPassword;
	GetDlgItemText(IDC_EDIT8, strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		Msg("�������벻��Ϊ��");
		return;
	}

	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT10);
	if ( sfMoeny<=0 )
	{
		Msg("ȡ��Ľ����������");
		return;
	}

	CMD_GF_BankTask cmd;
	memset(&cmd, 0, sizeof(CMD_GF_BankTask));

	cmd.lBankTask=BANKTASK_WITHDRAW;
	cmd.lMoneyNumber=GetDlgItemInt64(IDC_EDIT10);
	CMD5Encrypt::EncryptData(strPassword, cmd.szPassword);

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_BANK, &cmd, sizeof(CMD_GF_BankTask));

	GetDlgItem(IDC_DEPOSIT)->EnableWindow(0);
	GetDlgItem(IDC_WITHDRAW)->EnableWindow(0);
	GetDlgItem(IDC_BANK_QUERY)->EnableWindow(0);
	ShowWaitWindow();
	SetDlgItemText(IDC_EDIT10, 0);
}

void CGameClientDlg::OnTransferMoney()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);

	CString strUser;
	GetDlgItemText(IDC_EDIT17, strUser);
	strUser.Trim();
	if (strUser.IsEmpty())
	{
		Msg("�Է����˺Ų���Ϊ��");
		return;
	}

	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT18);
	if ( sfMoeny<=0 )
	{
		Msg("ת�˵Ľ����������");
		return;
	}

	DWORD dwUserID=GetDlgItemInt(IDC_EDIT19);
	if ( dwUserID==0 )
	{
		Msg("������д�û���ID��");
		return;
	}

	TCHAR szText[256];
	_snprintf(szText, sizeof(szText), "���ٴ�ȷ������ת�˲������Ƿ�������ȷ:\n\n\n�˻�����        %s\n��          %s��",
		strUser, GetString(sfMoeny));

	if ( MessageBox(szText, "������",MB_YESNO|MB_ICONINFORMATION)==IDNO)
		return;

	CMD_Transfer_Money cmd;
	memset(&cmd, 0, sizeof(CMD_Transfer_Money));
	cmd.dwUserID=dwUserID;
	cmd.sfMoneyNumber=sfMoeny;
	GetDlgItemText(IDC_EDIT17, cmd.szAccount, sizeof(cmd.szAccount));

	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_TRANSFER_MONEY, &cmd, sizeof(CMD_Transfer_Money));
	ShowWaitWindow();

	SetDlgItemText(IDC_EDIT17, 0);
	SetDlgItemText(IDC_EDIT18, 0);
	SetDlgItemText(IDC_EDIT19, 0);
}

void CGameClientDlg::OnQueryTransferLog()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);
	m_ClientSocket->SendData(MDM_GF_GAME, SUB_C_QUERY_TRANSFER_LOG, 0, 0);
	m_TransDialog.DestroyWindow();
	m_TransDialog.Create(CTransDialog::IDD, this);
	ShowWaitWindow();
}

//�ؼ���
void CGameClientDlg::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON2, m_CloseButton);
}

void __stdcall RunCommand( const char* command, const char* param, LPARAM lParam)
{
	CGameClientDlg* pDlg=(CGameClientDlg*)lParam;

	if ( _stricmp(command, "ip")==0 )
	{
		pDlg->m_strIP=param;
	}
	if ( _stricmp(command, "port")==0 )
	{
		pDlg->m_strPort=param;
	}
	if ( _stricmp(command, "uid")==0 )
	{
		pDlg->m_strUID=param;
	}
	if ( _stricmp(command, "ver")==0 )
	{
		pDlg->m_strPlazaVersion=param;
	}
	if ( _stricmp(command, "pwd")==0 )
	{
		pDlg->m_strPasword=param;
	}
}

BOOL CGameClientDlg::OnInitDialog()
{
	__super::OnInitDialog();
	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//�������
	if (m_ClientSocket.CreateInstance()==false)
		throw TEXT("��Ϸ����ں�ģ�����ʧ��");

	//��ʼ���ں�
	IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
	try 
	{
		IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
		if (m_ClientSocket.CreateInstance()==false) 
		{
			throw TEXT("�����������ʧ��");
		}
		if (m_ClientSocket->SetTCPSocketSink(pIUnknownEx)==false) 
		{
			throw TEXT("��������ص��ӿ�����ʧ��");
		}
	}
	catch (...)
	{
		Msg(TEXT("�����������ʧ�ܣ�������������Ϸ������"));
		EndDialog(IDOK);
		return FALSE;
	}

	SetBitmap(IDB_DlgBackground);
	
	m_CloseButton.SetBitmaps(IDB_BITMAP_CLOSE, RGB(0, 0, 0));
	m_CloseButton.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_CloseButton.DrawTransparent(TRUE);

	CWinApp *p=AfxGetApp();
	LPCTSTR lpszCmdLine=AfxGetApp()->m_lpCmdLine;

	ParseCommandLine(lpszCmdLine, RunCommand, (LPARAM)this);

	DWORD dwServerAddr=strtoul(m_strIP, 0, 16);
	WORD  wServerPort=(WORD)strtoul(m_strPort, 0, 10);

	m_ClientSocket->Connect( dwServerAddr, wServerPort);

	m_TipDialog.Create(IDD_CONNECTING, this);
	m_TipDialog.ModifyStyleEx(0, WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME);
	
	RECT rect;
	m_TipDialog.GetWindowRect(&rect);
	m_TipDialog.SetWindowPos(NULL,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_FRAMECHANGED);
	m_TipDialog.ShowWindow(SW_SHOW);

	return TRUE;
}

void CGameClientDlg::OnOK()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);

	CDialog::OnOK();
}

void CGameClientDlg::OnCancel()
{
	ASSERT(m_ClientSocket.GetInterface()!=NULL);
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);

	CDialog::OnCancel();
}

void CGameClientDlg::UpdateUserData(tagUserData* pUserData)
{
	m_strAccount=pUserData->szName;
	this->SetDlgItemText(IDC_EDIT11, pUserData->szName);
	this->SetDlgItemText(IDC_EDIT12, pUserData->szName);
	this->SetDlgItemText(IDC_EDIT13, GetString(pUserData->lScore));
}


void * __cdecl CGameClientDlg::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//���͵�¼��
bool CGameClientDlg::SendLogonPacket()
{
	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKET];
	//��¼���ݰ�
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=strtol(m_strUID, 0, 10);
	pLogonByUserID->dwPlazaVersion=strtoul(m_strPlazaVersion,0,16);
	lstrcpyn(pLogonByUserID->szPassWord, m_strPasword, sizeof(pLogonByUserID->szPassWord));

	//�������к�
	tagClientSerial ClientSerial;
	GetClientSerial(ClientSerial);
	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());
	return true;
}

bool CGameClientDlg::SendUserRulePacket()
{
	m_TipDialog.SetDlgItemText(IDC_MSG, TEXT("���ڴ������......"));

	//�������ݰ�
	//�������ݰ�
	CMD_GR_UserRule UserRule;
	memset(&UserRule, 0, sizeof(CMD_GR_UserRule));
	UserRule.bLimitWin=false;
	UserRule.bLimitFlee=false;
	UserRule.wWinRate=0;
	UserRule.wFleeRate=0;
	UserRule.lMaxScore=0;
	UserRule.lLessScore	=0;
	UserRule.bLimitScore=false;
	UserRule.bPassword=false;
	UserRule.bCheckSameIP=false;

	//�������ݰ�
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_RULE,&UserRule,sizeof(UserRule));
	return true;
}

bool CGameClientDlg::SendSitDownPacket()
{
	m_TipDialog.SetDlgItemText(IDC_MSG, TEXT("����������λ......"));
	//�������ݰ�
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=0;
	UserSitReq.wChairID=1;
	//�������ݰ�
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);
	//��ȡ����
	CMD_GF_Info Info;
	ZeroMemory(&Info,sizeof(Info));
	Info.bAllowLookon=true;
	m_ClientSocket->SendData(MDM_GF_FRAME,SUB_GF_INFO,&Info,sizeof(Info));

	return true;
}

//��¼�ɹ�����
bool CGameClientDlg::OnLogonSuccess()
{
	m_TipDialog.ShowWindow(0);
	return true;
}




//����������Ϣ
bool __cdecl CGameClientDlg::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if ( nErrorCode!=0 )
	{
		m_TipDialog.ShowWindow(0);
		CString str;
		str.Format("���ӷ���ʧ�ܣ�����ID��%d",nErrorCode);
		Msg(str);
		EndDialog(IDOK);
		return true;
	}

	SendLogonPacket();
	m_TipDialog.SetDlgItemText(IDC_MSG, TEXT("������֤�û���¼��Ϣ..."));
	return true;
}


//�����ȡ��Ϣ
bool __cdecl CGameClientDlg::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
		return OnSocketMainLogon(Command,pBuffer,wDataSize);
	case MDM_GR_USER:			//�û���Ϣ
		return OnSocketMainUser(Command,pBuffer,wDataSize);
	case MDM_GR_INFO:			//������Ϣ
		return OnSocketMainInfo(Command,pBuffer,wDataSize);
	case MDM_GR_STATUS://״̬��Ϣ
		return OnSocketMainStatus(Command,pBuffer,wDataSize);
	case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
		return OnSocketMainSystem(Command,pBuffer,wDataSize);
	case MDM_GR_SERVER_INFO:	//������Ϣ
		return OnSocketServerInfo(Command,pBuffer,wDataSize);
	case MDM_GF_GAME:			//��Ϸ��Ϣ
		return OnSocketMainGame(Command,pBuffer,wDataSize);
	case MDM_GF_FRAME:			//�����Ϣ
		return OnSocketMainFrame(Command,pBuffer,wDataSize);
	default:
		return true;
	}
	return true;
}

//����ر���Ϣ
bool __cdecl CGameClientDlg::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	if(m_TipDialog.GetSafeHwnd())
		m_TipDialog.ShowWindow(0);
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		if ((cbShutReason==SHUT_REASON_REMOTE)||(cbShutReason==SHUT_REASON_TIME_OUT))
		{
			Msg(TEXT("�����������⣬���Ѿ���������Ͽ����ӣ�����������"));
			EndDialog(IDOK);
		}
		else
		{
			Msg(TEXT("�����������ݰ�����ʧ�ܣ������ж���"));
			EndDialog(IDOK);
		}
	}

	return true;
}

//��¼��Ϣ
bool CGameClientDlg::OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//��¼�ɹ�
		{
			SendSitDownPacket();
			return true;
		}
	case SUB_GR_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			m_TipDialog.ShowWindow(0);
			m_ClientSocket->CloseSocket();
			

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				Msg(pLogonError->szErrorDescribe);
				EndDialog(IDOK);
			}
			return true;
		}
	case SUB_GR_LOGON_FINISH:		//��¼���
		{
			SendUserRulePacket();
			return true;
		}
	}

	return true;
}


//������Ϣ
bool CGameClientDlg::OnSocketMainFrame(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GF_MODIFY_LOGIN_PWD:
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GF_Modify_Login_Pwd));
			if (wDataSize!=sizeof(CMD_GF_Modify_Login_Pwd)) return false;
			//��������
			CMD_GF_Modify_Login_Pwd * pCmd=(CMD_GF_Modify_Login_Pwd *)pBuffer;

			m_TipDialog.ShowWindow(0);
			GetDlgItem(IDC_MODIFY_LOGIN_PASSWORD)->EnableWindow(1);

			if (pCmd->lErrorCode==0)
				Msg("�޸ĵ�½����ɹ�,�´ε�¼ʱ���������� ^_^");
			else
				Msg(pCmd->szErrorDescribe);

			return true;
		}
	case SUB_GF_MODIFY_BANK_PWD:
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GF_Modify_Bank_Pwd));
			if (wDataSize!=sizeof(CMD_GF_Modify_Bank_Pwd)) return false;
			//��������
			CMD_GF_Modify_Bank_Pwd * pCmd=(CMD_GF_Modify_Bank_Pwd *)pBuffer;

			m_TipDialog.ShowWindow(0);
			GetDlgItem(IDC_MODIFY_BANK_PASSWORD)->EnableWindow(1);

			if (pCmd->lErrorCode==0)
				Msg("�޸���������ɹ� ^_^");
			else
				Msg(pCmd->szErrorDescribe);

			return true;
		}
	case SUB_GF_MODIFY_NICKNAME:	//�����Ϣ
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GF_Modify_Nickname));
			if (wDataSize!=sizeof(CMD_GF_Modify_Nickname)) return false;
			//��������
			CMD_GF_Modify_Nickname * pCmd=(CMD_GF_Modify_Nickname *)pBuffer;

			m_TipDialog.ShowWindow(0);
			GetDlgItem(IDC_MODIFY_NICKNAME)->EnableWindow(1);
			GetDlgItem(IDC_EDIT7)->SetWindowText(0);
			GetDlgItem(IDC_EDIT7)->SetFocus();

			if ( pCmd->lErrorCode==0 )
			{
				SetDlgItemText(IDC_EDIT12, pCmd->szNickname );
				Msg("�޸��ǳƳɹ�^_^");
			}
			else
			{
				Msg(pCmd->szErrorDescribe);
			}

			return true;
		}
	case SUB_GF_BANK:	//�����Ϣ
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GF_BankTask_Out));
			if (wDataSize!=sizeof(CMD_GF_BankTask_Out)) return false;
			//��������
			CMD_GF_BankTask_Out * pCmd=(CMD_GF_BankTask_Out *)pBuffer;

			SetDlgItemText(IDC_EDIT13, GetString(pCmd->lNewScore) );
			SetDlgItemText(IDC_EDIT14, GetString(pCmd->lMoneyInBank) );

			m_TipDialog.ShowWindow(0);
			GetDlgItem(IDC_DEPOSIT)->EnableWindow(1);
			GetDlgItem(IDC_WITHDRAW)->EnableWindow(1);
			GetDlgItem(IDC_BANK_QUERY)->EnableWindow(1);
			GetDlgItem(IDC_EDIT9)->SetFocus();

			if (pCmd->lErrorCode!=0)
				Msg(pCmd->szErrorDescribe);
			else
				Msg("���в����ɹ� ^_^");

			return true;
		}
	case SUB_GF_TRANSFER_MONEY:
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GF_Transfer_Money));
			if (wDataSize!=sizeof(CMD_GF_Transfer_Money)) return false;
			//��������
			CMD_GF_Transfer_Money * pCmd=(CMD_GF_Transfer_Money *)pBuffer;

			m_TipDialog.ShowWindow(0);

			if (pCmd->lErrorCode==0)
			{
				SetDlgItemText(IDC_EDIT13, GetString(pCmd->sfLeftMoney) );

				TCHAR szText[256];
				_snprintf(szText, sizeof(szText), "ת�˲����ɹ�: ת��%s����˰��%s�������Ŀڴ����%s��", 
					GetString(pCmd->sfMoneyNumber), GetString(pCmd->sfTax), GetString(pCmd->sfLeftMoney));
				Msg(szText);
			}
			else
			{
				Msg(pCmd->szErrorDescribe);
			}
			return true;
		}
	case SUB_GF_TRANSFER_LOG:
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GF_Transfer_Log_Out));
			if (wDataSize!=sizeof(CMD_GF_Transfer_Log_Out)) return false;
			CMD_GF_Transfer_Log_Out * pCmd=(CMD_GF_Transfer_Log_Out *)pBuffer;

			m_TipDialog.ShowWindow(0);
			m_TransDialog.CenterWindow();
			m_TransDialog.ShowWindow(1);
			return true;
		}
	case SUB_GF_TRANSFER_LOG_ITEM:
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GF_Transfer_Log_Item));
			if (wDataSize!=sizeof(CMD_GF_Transfer_Log_Item)) return false;

			CMD_GF_Transfer_Log_Item * pCmd=(CMD_GF_Transfer_Log_Item *)pBuffer;

			ULONG uMyID=strtoul(m_strUID, 0, 10);


			int insertpos=m_TransDialog.m_List1.GetItemCount();
			m_TransDialog.m_List1.InsertItem(insertpos, pCmd->szOutAccount);
			m_TransDialog.m_List1.SetItemText(insertpos, 1, pCmd->szInAccount);

			TCHAR szText[256];
			_snprintf(szText, sizeof(szText), "%I64d", pCmd->sfMoney);
			m_TransDialog.m_List1.SetItemText(insertpos, 2, szText);

			_snprintf(szText, sizeof(szText), "%04ld/%02ld/%02ld  %02ld:%02ld:%02ld", 
				pCmd->TransTime.wYear,
				pCmd->TransTime.wMonth,
				pCmd->TransTime.wDay,
				pCmd->TransTime.wHour,
				pCmd->TransTime.wMinute,
				pCmd->TransTime.wSecond );	

			m_TransDialog.m_List1.SetItemText(insertpos, 3, szText);

			return true;
		}
	case SUB_GF_MESSAGE:
		{
			//Ч�����
			CMD_GF_Message * pMessage=(CMD_GF_Message *)pBuffer;
			ASSERT(wDataSize>(sizeof(CMD_GF_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GF_Message)-sizeof(pMessage->szContent))) return false;

			//��Ϣ����
			WORD wHeadSize=sizeof(CMD_GF_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;

			if ( pMessage->wMessageType&SMT_EJECT )
				Msg(pMessage->szContent);

			return true;
		}
	}
	return true;
}



//��¼��Ϣ
bool CGameClientDlg::OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//ϵͳ��Ϣ
		{
			//Ч�����
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pBuffer;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//��Ϣ����
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;

			//�ر�����
			bool bIntermet=false;
			if (pMessage->wMessageType&SMT_INTERMIT_LINE) bIntermet=true;
			else
			{
				if (pMessage->wMessageType&SMT_CLOSE_ROOM) bIntermet=true;
			}

			if ( bIntermet==true ) 
			{
				m_TipDialog.ShowWindow(0);
				ASSERT(m_ClientSocket.GetInterface()!=NULL);
				m_ClientSocket->CloseSocket();
			}

			//��ʾ��Ϣ
			if ( pMessage->wMessageType&SMT_EJECT )
				Msg(pMessage->szContent);

			return true;
		}
	}

	return true;
}

//��¼��Ϣ
bool CGameClientDlg::OnSocketMainGame(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	return true;
}

//��¼��Ϣ
bool CGameClientDlg::OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	return true;
}

//�û���Ϣ
bool CGameClientDlg::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);

	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//�û�����
		{
			return OnSocketSubUserCome(Command,pBuffer,wDataSize);
		}
	case SUB_GR_USER_STATUS:		//�û�״̬
		{
			return OnSocketSubStatus(Command,pBuffer,wDataSize);
		}
	case SUB_GR_USER_SCORE:			//�û�����
		{
			return OnSocketSubScore(Command,pBuffer,wDataSize);
		}
	case SUB_GR_SIT_FAILED:			//����ʧ��
		{
			return OnSocketSubSitFailed(Command,pBuffer,wDataSize);
		}
	}

	return true;
}

//�û���Ϣ
bool CGameClientDlg::OnSocketServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SERVER_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_ONLINE_COUNT_INFO:			//�û�����
		{
			return true;
		}
	default:
		return true;
	}
	return true;
}

//״̬��Ϣ
bool CGameClientDlg::OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_STATUS);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_TABLE_INFO:		//������Ϣ
		{
			//��������
			CMD_GR_TableInfo * pTableInfo=(CMD_GR_TableInfo *)pBuffer;
			const WORD wHeadSize=sizeof(CMD_GR_TableInfo)-sizeof(pTableInfo->TableStatus);

			return true;
		}
	case SUB_GR_TABLE_STATUS:	//����״̬
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_GR_TableStatus));
			if (wDataSize<sizeof(CMD_GR_TableStatus)) return false;

			return true;
		}
	}

	return true;
}

//�û�����
bool CGameClientDlg::OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;
	
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pBuffer;
	if ( pUserInfoHead->dwUserID!=strtoul(m_strUID, 0, 10))
		return true;

	//��ȡ������Ϣ
	tagUserData UserData;
	memset(&UserData,0,sizeof(UserData));

	//��ȡ��Ϣ
	UserData.dwUserID=pUserInfoHead->dwUserID;
	UserData.wTableID=pUserInfoHead->wTableID;
	UserData.wChairID=pUserInfoHead->wChairID;
	UserData.cbUserStatus=pUserInfoHead->cbUserStatus;
	UserData.dwUserRight=pUserInfoHead->dwUserRight;
	UserData.dwMasterRight=pUserInfoHead->dwMasterRight;
	UserData.wFaceID=pUserInfoHead->wFaceID;
	UserData.cbGender=pUserInfoHead->cbGender;
	UserData.cbMemberOrder=pUserInfoHead->cbMemberOrder;
	UserData.cbMasterOrder=pUserInfoHead->cbMasterOrder;
	UserData.dwGroupID=pUserInfoHead->dwGroupID;
	UserData.lScore=pUserInfoHead->UserScoreInfo.lScore;
	UserData.lWinCount=pUserInfoHead->UserScoreInfo.lWinCount;
	UserData.lLostCount=pUserInfoHead->UserScoreInfo.lLostCount;
	UserData.lDrawCount=pUserInfoHead->UserScoreInfo.lDrawCount;
	UserData.lFleeCount=pUserInfoHead->UserScoreInfo.lFleeCount;
	UserData.lExperience=pUserInfoHead->UserScoreInfo.lExperience;

	//��ȡ��չ��Ϣ
	void * pDataBuffer=NULL;
	tagDataDescribe DataDescribe;
	CRecvPacketHelper RecvPacket(pUserInfoHead+1,wDataSize-sizeof(tagUserInfoHead));
	while (true)
	{
		pDataBuffer=RecvPacket.GetData(DataDescribe);
		if (DataDescribe.wDataDescribe==DTP_NULL) break;
		switch (DataDescribe.wDataDescribe)
		{
		case DTP_USER_ACCOUNTS:		//�û��ʻ�
			{
				ASSERT(pDataBuffer!=NULL);
				ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szName));
				if (DataDescribe.wDataSize<=sizeof(UserData.szName))
				{
					CopyMemory(&UserData.szName,pDataBuffer,DataDescribe.wDataSize);
					UserData.szName[CountArray(UserData.szName)-1]=0;
				}
				break;
			}
		//case DTP_USER_NICKNAME:		//�û��ʻ�
		//	{
		//		ASSERT(pDataBuffer!=NULL);
		//		ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szNickname));
		//		if (DataDescribe.wDataSize<=sizeof(UserData.szNickname))
		//		{
		//			CopyMemory(&UserData.szNickname,pDataBuffer,DataDescribe.wDataSize);
		//			UserData.szNickname[CountArray(UserData.szNickname)-1]=0;
		//		}
		//		break;
		//	}
		case DTP_UNDER_WRITE:		//����ǩ��
			{
				ASSERT(pDataBuffer!=NULL);
				ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite));
				if (DataDescribe.wDataSize<=sizeof(UserData.szUnderWrite))
				{
					CopyMemory(&UserData.szUnderWrite,pDataBuffer,DataDescribe.wDataSize);
					UserData.szUnderWrite[CountArray(UserData.szUnderWrite)-1]=0;
				}
				break;
			}
		}
	}

	UpdateUserData(&UserData);

	//SendSitDownPacket();

	return true;
}

bool CGameClientDlg::OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_SIT_FAILED);

	//��Ϣ����
	CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pBuffer;

	Msg( pSitFailed->szFailedDescribe);
	EndDialog(IDOK);

	return true;
}

//�û�����
bool CGameClientDlg::OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;

	//��������
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pBuffer;

	return true;
}

//�û�״̬
bool CGameClientDlg::OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_STATUS);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserStatus));
	if (wDataSize<sizeof(CMD_GR_UserStatus)) return false;

	//��������
	CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pBuffer;

	m_TipDialog.ShowWindow(0);

	return true;
}

void CGameClientDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

// �û�ID�ı�
void CGameClientDlg::OnEnChangeUserID()
{
	
}
