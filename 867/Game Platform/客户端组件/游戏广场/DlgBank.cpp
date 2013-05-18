#include "stdafx.h"
#include "resource.h"
#include "DlgBank.h"
#include "GameFrame.h"
#include "GlobalUnits.h"
#include "Zip.h"

//////////////////////////////////////////////////////////////////////////
CDlgBank::CDlgBank() : CSkinPngDialog(IDD_BANK_DIALOG)
{
	m_wOpt = OPT_SAVE; 
	m_pMeUserData = NULL;
	m_strGameGold.Empty();
	m_strBankGold.Empty();
}

CDlgBank::~CDlgBank()
{
}

void CDlgBank::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAMEGOLD,		m_strGameGold);
	DDX_Text(pDX, IDC_BANKGOLD,		m_strBankGold);
	DDX_Control(pDX, IDC_TAB_BANK,		m_TabBank);
	DDX_Control(pDX, IDC_BACNK_BTNOK,	m_btOK);
	DDX_Control(pDX, IDC_BANK_BTNALL,	m_btAll);
}

BEGIN_MESSAGE_MAP(CDlgBank, CSkinPngDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BANK, OnTcnSelchange)
	ON_BN_CLICKED(IDC_BACNK_BTNOK, OnButtonOK)
	ON_BN_CLICKED(IDC_BANK_BTNALL, OnButtonAll)
	ON_EN_CHANGE(IDC_EDIT1, OnEnUserIDChange)
END_MESSAGE_MAP()

BOOL CDlgBank::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN) 
	{
		if(pMsg->wParam == VK_RETURN)
		{
			OnButtonOK();
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

//初始化函数
BOOL CDlgBank::OnInitDialog()
{
	__super::OnInitDialog();
	SetWindowText("银行");
	m_TabBank.SetItemSize(CSize(100,25));
	//加入标签
	m_TabBank.InsertItem(BANK_DLG_SAVE,TEXT("存钱"));
	m_TabBank.InsertItem(BANK_DLG_GET,TEXT("取钱"));
	m_TabBank.InsertItem(BANK_DLG_PTN,TEXT("赠送"));
	m_TabBank.SetCurSel(BANK_DLG_SAVE);
	OnTcnSelchange(NULL, NULL);
	return FALSE; 
}

//绘画消息
VOID CDlgBank::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//获取位置
	CRect rcTabControl;
	m_TabBank.GetWindowRect(&rcTabControl);

	//转换位置
	ScreenToClient(&rcTabControl);

	//绘画线条
	INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	pDC->FillSolidRect(nLBorder,rcTabControl.bottom-1L,nWidth-nLBorder-nRBorder,1,RGB(145,168,183));


	//构造提示
	TCHAR szString[128]=TEXT("");
	_sntprintf(szString,CountArray(szString),TEXT("温馨提示：请妥善保管密码，警防盗号！"));
	//温馨提示
	pDC->SetTextColor(RGB(50,50,50));
	pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));

	return;
}

//销毁消息
void CDlgBank::OnClose()
{
	__super::OnClose();
}

void CDlgBank:: OnCancel()
{
	__super::OnCancel();
	if(m_BankSocketHelper.GetInterface()!=NULL)
		m_BankSocketHelper->CloseSocket();
}
//显示消息
int CDlgBank::ShowMessageBox(LPCTSTR pszMessage)
{				
	int nResult = ShowInformationEx(pszMessage,0,MB_ICONQUESTION,TEXT("银行"));
	return nResult;
}
__int64 CDlgBank::GetDlgItemInt64(UINT uID)
{
	CString buffer;
	GetDlgItemText(uID, buffer);
	buffer.Remove(',');
	return _atoi64(buffer.GetBuffer());
};

void CDlgBank::SetDlgItemInt64(UINT uID, __int64 value)
{
	TCHAR szText[256];
	_snprintf(szText, sizeof(szText), "%I64d", value);
	SetDlgItemText(uID, szText);
};

CString CDlgBank::GetString(__int64 nNumber)
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

//更新用户的分数
void CDlgBank::UpdataUserScore(__int64 Score,__int64 BankScore)
{
	m_strGameGold = GetString(Score);
	m_strBankGold = GetString(BankScore);
}

//设置socket指针
bool CDlgBank::SetClientSocket(ITCPSocket* Socket)
{
	if(Socket == NULL)
		return false;
	m_BankSocket=Socket;
	return true;
}

//socket 连接
bool __cdecl CDlgBank::ConnectToServer()
{
	//创建组件
	if (m_BankSocketHelper.GetInterface()==NULL)
	{
		//初始化内核
		IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
		try 
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_BankSocketHelper.CreateInstance()==false) 
			{
				throw TEXT("网络组件创建失败");
			}
			if (m_BankSocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("网络组件回调接口设置失败");
			}
		}
		catch (...)
		{
			ShowMessageBox(TEXT("抱歉，此功能暂时不能使用！EORR:2"));
			return false;
		}
	}

	m_BankSocket=m_BankSocketHelper.GetInterface();

	DWORD dwBankIP = g_GlobalUnits.m_ServerListManager.m_dwToolServerAddr;
	WORD wBankPort = g_GlobalUnits.m_ServerListManager.m_wToolServerPort;
	if (dwBankIP!=0 && wBankPort!=0)
	{
		m_BankSocket->Connect( dwBankIP, wBankPort);
	}
	else
	{
		ShowMessageBox("抱歉，此功能暂时不能使用！EORR:3");
		return false;
	}	
	return true;
}

//接口查询
void * __cdecl CDlgBank::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}


//连接事件
bool __cdecl CDlgBank::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//错误处理
	if (nErrorCode!=0)
	{
		ShowMessageBox("抱歉，连接服务器失败，此功能暂时不能使用！");
		return false;
	}

	SendLogonPacket();
	return true;
}
//关闭事件
bool __cdecl CDlgBank::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	return true;
}

//读取事件
bool __cdecl CDlgBank::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//登录消息
		return OnSocketMainLogon(Command,pData,wDataSize);
	case MDM_GR_USER:
		return OnSocketMainUser(Command,pData,wDataSize);
	case MDM_TOOLBOX:				
		return OnSocketToolBox(Command,pData,wDataSize);
	case MDM_GR_SYSTEM:
		return OnSystemMessage(Command,pData,wDataSize);
	}
	return true;
}

//发送登录包
void CDlgBank::SendLogonPacket()
{
	//获取信息
	BYTE cbBuffer[SOCKET_PACKET];
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//登录数据包
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=GlobalUserData.dwUserID;
	pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
	lstrcpyn(pLogonByUserID->szPassWord,GlobalUserData.szPassWord,sizeof(pLogonByUserID->szPassWord));
	//机器序列号
	tagClientSerial ClientSerial;
	g_GlobalUnits.GetClientSerial(ClientSerial);
	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_BankSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());
}

//登录消息
bool CDlgBank::OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//登录成功
		{
			return true;
		}
	case SUB_GR_LOGON_ERROR:		//登录失败
		{
			//效验参数
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;
			//关闭连接
			m_BankSocket->CloseSocket();
			ShowMessageBox("抱歉，此功能暂时不能使用！");
			return true;
		}
	case SUB_GR_LOGON_FINISH:		//登录完成
		{
			return true;
		}
	}

	return true;
}

//系统消息
bool CDlgBank::OnSystemMessage(CMD_Command Command,void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//系统消息
		{
			//效验参数
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pData;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//消息处理
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;
			if (pMessage->wMessageType&SMT_EJECT)
				ShowMessageBox(pMessage->szContent);
			return true;
		}
	}
	return true;
}

//用户消息
bool CDlgBank::OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//用户进入
		{
			return OnSocketSubUserCome(Command, pData, wDataSize);
		}
	case SUB_GR_USER_SCORE:			//用户分数
		{
			return OnSocketSubScore(Command,pData,wDataSize);
		}
	case SUB_GR_FLASHUSERINFO:
		{
			//效验参数
			ASSERT(Command.wMainCmdID==MDM_GR_USER);
			ASSERT(Command.wSubCmdID==SUB_GR_FLASHUSERINFO);
			//效验参数
			ASSERT(wDataSize==sizeof(CMD_GR_FlashUserInfo));
			if (wDataSize!=sizeof(CMD_GR_FlashUserInfo))
				return false;
			//处理数据
			CMD_GR_FlashUserInfo* pUserInfo = (CMD_GR_FlashUserInfo*)pData;
			if(pUserInfo->dwUserID == g_GlobalUnits.GetGolbalUserData().dwUserID)
			{
				m_strGameGold = GetString(pUserInfo->lScore);
				m_strBankGold = GetString(pUserInfo->lInsureScore);
				UpdateData(FALSE);
			}
		}
	}
	return true;
}


//用户进入
bool CDlgBank::OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pData;
	if (pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID)
	{
		m_strGameGold = GetString(pUserInfoHead->UserScoreInfo.lScore);
		m_strBankGold = GetString(pUserInfoHead->UserScoreInfo.lInsureScore);
		UpdateData(FALSE);
	}
	return true;

}
//用户分数
bool CDlgBank::OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;
	//处理数据
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pData;
	if(pUserScore->dwUserID == g_GlobalUnits.GetGolbalUserData().dwUserID)
	{
		m_strGameGold = GetString(pUserScore->UserScore.lScore);
		m_strBankGold = GetString(pUserScore->UserScore.lInsureScore);
		UpdateData(FALSE);
	}
	return true;
}

//框架消息
bool CDlgBank::OnSocketToolBox(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_TOOLBOX);
	switch(Command.wSubCmdID)
	{
	case SUB_TOOLBOX_QUERYUSERNAME:  //查询用户名返回
		return OnQueryUserName(pData,wDataSize);
	case SUB_TOOLBOX_TRANSFERMONEY: //转账
		return OnTransferMoney(pData,wDataSize);
	}

	return true;
}

//查询用户名
bool CDlgBank::OnQueryUserName(void * pData, WORD wDataSize)
{
	ASSERT(wDataSize>=sizeof(CMD_TOOLBOX_QueryUserName_Ret));
	if (wDataSize<sizeof(CMD_TOOLBOX_QueryUserName_Ret))
		return false;
	CMD_TOOLBOX_QueryUserName_Ret* QRet = (CMD_TOOLBOX_QueryUserName_Ret*)pData;
	if(QRet->lErrorCode == 0)
	{
		SetDlgItemText(IDC_EDIT2,QRet->UserNmae);
	}
	else
	{
		ShowMessageBox(QRet->szErrorDescribe);
	}
	return true;
}

//转账完成处理
bool CDlgBank::OnTransferMoney(void * pData, WORD wDataSize)
{
	ASSERT(wDataSize>=sizeof(CMD_TOOLBOX_TransferMoney_Ret));
	if (wDataSize<sizeof(CMD_TOOLBOX_TransferMoney_Ret))
		return false;
	CMD_TOOLBOX_TransferMoney_Ret *pTransRet = (CMD_TOOLBOX_TransferMoney_Ret*)pData;

	if (pTransRet->lErrorCode==0)
	{
		TCHAR szText[256];
		_snprintf(szText, sizeof(szText), "转账操作成功: 转账%s金币，税收%s金币", 
			GetString(pTransRet->sfMoneyNumber), GetString(pTransRet->sfTax), GetString(pTransRet->sfLeftMoney));
		ShowMessageBox(szText);
	}
	else
	{
		ShowMessageBox(pTransRet->szErrorDescribe);
	}

	return true;
}


//类型改变
void CDlgBank::OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabBank.GetCurSel())
	{
	case BANK_DLG_SAVE:
		{
			m_TabBank.SetCurSel(BANK_DLG_SAVE);
			SetDlgItemText(IDC_BANK_TEXT,TEXT("存入数目："));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("银行密码："));
			GetDlgItem(IDC_BANK_BTNALL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
			SetOptType(OPT_SAVE);
		}
		break;
	case BANK_DLG_GET:
		{
			m_TabBank.SetCurSel(BANK_DLG_GET);
			SetDlgItemText(IDC_BANK_TEXT,TEXT("取出数目："));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("银行密码："));
			GetDlgItem(IDC_BANK_BTNALL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
			SetOptType(OPT_GET);
		}
		break;
	case BANK_DLG_PTN:
		{
			m_TabBank.SetCurSel(BANK_DLG_PTN);
			SetDlgItemText(IDC_BANK_PLYNAME,TEXT("赠送玩家ID："));
			SetDlgItemText(IDC_BANK_TEXT,TEXT("赠送数目："));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("银行密码："));
			GetDlgItem(IDC_BANK_BTNALL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
			SetOptType(OPT_PTN);
		}
		break;
	}
}

// 设置操作类型
WORD CDlgBank::GetOptType() const
{
	return m_wOpt;
}

// 获取操作类型
void CDlgBank::SetOptType(WORD wType)
{
	m_wOpt = wType;
}

// 确定操作
void CDlgBank::OnButtonOK()
{
	switch (m_TabBank.GetCurSel())
	{
	case BANK_DLG_SAVE:
		SaveGoldOk();
		break;
	case BANK_DLG_GET:
		GetGoldOk();
		break;
	case BANK_DLG_PTN:
		PtnGoldOK();
		break;
	}
}

// 全部
void CDlgBank::OnButtonAll()
{
	if(m_TabBank.GetCurSel() == BANK_DLG_SAVE)
		SetDlgItemText(IDC_EDIT3,m_strGameGold);
	else
		SetDlgItemText(IDC_EDIT3,m_strBankGold);
	UpdateData(FALSE);
}

// 用户ID输入改变
void CDlgBank::OnEnUserIDChange()
{
	CString	buffer;
	GetDlgItemText(IDC_EDIT1, buffer);

	if (buffer.GetLength() >= 6)
	{
		DWORD dwUserID = atol(buffer.GetBuffer());
		if(dwUserID == g_GlobalUnits.GetGolbalUserData().dwGameID)
		{
			ShowMessageBox("不能给着自己转账！");
			return;
		}
		CMD_TOOLBOX_QueryUserName Query;
		Query.lGameID = dwUserID;
		m_BankSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_QUERYUSERNAME, &Query,sizeof(Query));
		return;
	}
}

//存钱确定
void CDlgBank::SaveGoldOk()
{
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("需要取的金额必须大于零！");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("请输入银行密码！");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	//密码验证
	TCHAR szTempPassword[PASS_LEN]=TEXT("");
	CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
	CMD5Encrypt::EncryptData(szTempPassword,szPassword);

	CMD_TOOLBOX_BankTask BankTask;
	memset(&BankTask, 0, sizeof(CMD_TOOLBOX_BankTask));
	BankTask.lMoneyNumber=sfMoeny;
	BankTask.lBankTask=BANKTASK_DEPOSIT;
	CopyMemory(BankTask.szPassword,szPassword,sizeof(BankTask.szPassword));
	m_BankSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &BankTask, sizeof(BankTask));
}
//取钱确定
void CDlgBank::GetGoldOk()
{
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("需要取的金额必须大于零！");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("请输入银行密码！");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	//密码验证
	TCHAR szTempPassword[PASS_LEN]=TEXT("");
	CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
	CMD5Encrypt::EncryptData(szTempPassword,szPassword);

	CMD_TOOLBOX_BankTask BankTask;
	memset(&BankTask, 0, sizeof(CMD_TOOLBOX_BankTask));
	BankTask.lMoneyNumber=sfMoeny;
	BankTask.lBankTask=BANKTASK_WITHDRAW;
	CopyMemory(BankTask.szPassword,szPassword,sizeof(BankTask.szPassword));
	m_BankSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &BankTask, sizeof(BankTask));
}
//转账确定
void CDlgBank::PtnGoldOK()
{
	DWORD dwGameID=GetDlgItemInt(IDC_EDIT1);
	if ( dwGameID==0 )
	{
		ShowMessageBox("必须填入对方的游戏ID");
		return;
	}
	if(dwGameID == g_GlobalUnits.GetGolbalUserData().dwGameID)
	{
		ShowMessageBox("不能给着自己转账！");
		return;
	}
	CString strUserName;
	GetDlgItemText(IDC_EDIT2, strUserName);
	strUserName.Trim();
	if (strUserName.IsEmpty())
	{
		ShowMessageBox("对方的账号不能为空！");
		return;
	}
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("转账的金额必须大于零！");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("请输入银行密码！");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	TCHAR szText[256];
	_snprintf(szText, sizeof(szText), "请再次确认您的转账操作，是否输入正确:\
		\n\n\n转入游戏ID： %d\n转入账户名： %s\n      金额： %s金币",
		dwGameID,strUserName, GetString(sfMoeny));
	if (IDYES == ShowInformationEx(szText,0,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1,TEXT("银行")))
	{
		//密码验证
		TCHAR szTempPassword[PASS_LEN]=TEXT("");
		CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
		CMD5Encrypt::EncryptData(szTempPassword,szPassword);

		CMD_TOOLBOX_TransferMoney cmd;
		memset(&cmd, 0, sizeof(CMD_TOOLBOX_TransferMoney));
		cmd.sfMoneyNumber=sfMoeny;
		cmd.dwGameID=dwGameID;
		CopyMemory(cmd.szAccount,strUserName,sizeof(cmd.szAccount));
		CopyMemory(cmd.szPassword,szPassword,sizeof(cmd.szPassword));
		m_BankSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_TRANSFERMONEY, &cmd, sizeof(cmd));
	}
}
