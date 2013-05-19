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
	m_lGameGold=0;
	m_lBankGold=0;
	m_bInitInfo=false;
}

CDlgBank::~CDlgBank()
{
}

void CDlgBank::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
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

//��ʼ������
BOOL CDlgBank::OnInitDialog()
{
	__super::OnInitDialog();
	SetWindowText("����");
	m_TabBank.SetItemSize(CSize(100,25));
	//�����ǩ
	m_TabBank.InsertItem(BANK_DLG_SAVE,TEXT("��Ǯ"));
	m_TabBank.InsertItem(BANK_DLG_GET,TEXT("ȡǮ"));
	m_TabBank.InsertItem(BANK_DLG_PTN,TEXT("����"));
	m_TabBank.SetCurSel(BANK_DLG_SAVE);
	OnTcnSelchange(NULL, NULL);

	return FALSE; 
}

//�滭��Ϣ
VOID CDlgBank::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//��ȡλ��
	CRect rcTabControl;
	m_TabBank.GetWindowRect(&rcTabControl);
	//ת��λ��
	ScreenToClient(&rcTabControl);

	//�滭����
	INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	pDC->FillSolidRect(nLBorder,rcTabControl.bottom-1L,nWidth-nLBorder-nRBorder,1,RGB(145,168,183));

	//ͼƬ����ָ��
	int Dex = 5;
	int Dey = 80;
	//����
	CPngImage ImageBankBK;
	ImageBankBK.LoadImage(AfxGetInstanceHandle(),TEXT("PLAZA_BANK_BK"));
	Dex = (nWidth-ImageBankBK.GetWidth())/2L;
	ImageBankBK.DrawImage(pDC,Dex,Dey);
	//���
	CPngImage ImageBankFrame;
	ImageBankFrame.LoadImage(AfxGetInstanceHandle(),TEXT("PLAZA_BANK_FRAME"));
	Dex = (nWidth-ImageBankFrame.GetWidth())/2L;
	ImageBankFrame.DrawImage(pDC,Dex,Dey);

	if(m_bInitInfo)
	{
		//����
		DrawNumberString(pDC,m_lGameGold,Dex+55,Dey+13);
		DrawNumberString(pDC,m_lBankGold,Dex+55,Dey+37);
	}

	//������ʾ
	TCHAR szString[128]=TEXT("");
	_sntprintf(szString,CountArray(szString),TEXT("��ܰ��ʾ�������Ʊ������룬�������ţ�"));
	//��ܰ��ʾ
	pDC->SetTextColor(RGB(50,50,50));
	pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));

	return;
}

//�滭����
VOID CDlgBank::DrawNumberString(CDC * pDC, __int64 lScore, INT nXPos, INT nYPos)
{
	//ת������
	TCHAR szControl[128]=TEXT("");
	SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

	//��������
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//�滭�ж�
	if (nScoreLength>0L)
	{
		//������Դ
		CPngImage ImageNumber;
		ImageNumber.LoadImage(AfxGetInstanceHandle(),TEXT("PLAZA_BANK_SCORE"));

		//��ȡ��С
		CSize SizeNumber;
		SizeNumber.SetSize(ImageNumber.GetWidth()/12L,ImageNumber.GetHeight());

		//�滭����
		for (INT i=0;i<nScoreLength;i++)
		{
			//�滭����
			if (szControl[i]==TEXT(','))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//�滭���
			if (szControl[i]==TEXT('.'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//�滭����
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//����λ��
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}


//ת���ַ�
VOID CDlgBank::SwitchScoreFormat(__int64 lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}


//������Ϣ
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
//��ʾ��Ϣ
int CDlgBank::ShowMessageBox(LPCTSTR pszMessage)
{				
	int nResult = ShowInformationEx(pszMessage,0,MB_ICONQUESTION,TEXT("����"));
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

//�����û��ķ���
void CDlgBank::UpdataUserScore(__int64 Score,__int64 BankScore)
{
	m_lGameGold = Score;
	m_lBankGold = BankScore;
	m_bInitInfo = true;
	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}

//����socketָ��
bool CDlgBank::SetClientSocket(ITCPSocket* Socket)
{
	if(Socket == NULL)
		return false;
	m_BankSocket=Socket;
	return true;
}

//socket ����
bool __cdecl CDlgBank::ConnectToServer()
{
	//�������
	if (m_BankSocketHelper.GetInterface()==NULL)
	{
		//��ʼ���ں�
		IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
		try 
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_BankSocketHelper.CreateInstance()==false) 
			{
				throw TEXT("�����������ʧ��");
			}
			if (m_BankSocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("��������ص��ӿ�����ʧ��");
			}
		}
		catch (...)
		{
			ShowMessageBox(TEXT("��Ǹ���˹�����ʱ����ʹ�ã�EORR:2"));
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
		ShowMessageBox("��Ǹ���˹�����ʱ����ʹ�ã�EORR:3");
		return false;
	}	
	return true;
}

//�ӿڲ�ѯ
void * __cdecl CDlgBank::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}


//�����¼�
bool __cdecl CDlgBank::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//������
	if (nErrorCode!=0)
	{
		ShowMessageBox("��Ǹ�����ӷ�����ʧ�ܣ��˹�����ʱ����ʹ�ã�");
		return false;
	}

	SendLogonPacket();
	return true;
}
//�ر��¼�
bool __cdecl CDlgBank::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	return true;
}

//��ȡ�¼�
bool __cdecl CDlgBank::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
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

//���͵�¼��
void CDlgBank::SendLogonPacket()
{
	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKET];
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//��¼���ݰ�
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=GlobalUserData.dwUserID;
	pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
	lstrcpyn(pLogonByUserID->szPassWord,GlobalUserData.szPassWord,sizeof(pLogonByUserID->szPassWord));
	//�������к�
	tagClientSerial ClientSerial;
	g_GlobalUnits.GetClientSerial(ClientSerial);
	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_BankSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());
}

//��¼��Ϣ
bool CDlgBank::OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//��¼�ɹ�
		{
			return true;
		}
	case SUB_GR_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;
			//�ر�����
			m_BankSocket->CloseSocket();
			ShowMessageBox("��Ǹ���˹�����ʱ����ʹ�ã�");
			return true;
		}
	case SUB_GR_LOGON_FINISH:		//��¼���
		{
			return true;
		}
	}

	return true;
}

//ϵͳ��Ϣ
bool CDlgBank::OnSystemMessage(CMD_Command Command,void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//ϵͳ��Ϣ
		{
			//Ч�����
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pData;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//��Ϣ����
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

//�û���Ϣ
bool CDlgBank::OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//�û�����
		{
			return OnSocketSubUserCome(Command, pData, wDataSize);
		}
	case SUB_GR_USER_SCORE:			//�û�����
		{
			return OnSocketSubScore(Command,pData,wDataSize);
		}
	case SUB_GR_FLASHUSERINFO:
		{
			//Ч�����
			ASSERT(Command.wMainCmdID==MDM_GR_USER);
			ASSERT(Command.wSubCmdID==SUB_GR_FLASHUSERINFO);
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_GR_FlashUserInfo));
			if (wDataSize!=sizeof(CMD_GR_FlashUserInfo))
				return false;
			//��������
			CMD_GR_FlashUserInfo* pUserInfo = (CMD_GR_FlashUserInfo*)pData;
			if(pUserInfo->dwUserID == g_GlobalUnits.GetGolbalUserData().dwUserID)
			{
				m_lGameGold = pUserInfo->lScore;
				m_lBankGold = pUserInfo->lInsureScore;
				m_bInitInfo = true;
				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
			}
		}
	}
	return true;
}


//�û�����
bool CDlgBank::OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pData;
	if (pUserInfoHead->dwUserID==g_GlobalUnits.GetGolbalUserData().dwUserID)
	{
		m_lGameGold = pUserInfoHead->UserScoreInfo.lScore;
		m_lBankGold = pUserInfoHead->UserScoreInfo.lInsureScore;
		m_bInitInfo = true;
		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}
	return true;

}
//�û�����
bool CDlgBank::OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;
	//��������
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pData;
	if(pUserScore->dwUserID == g_GlobalUnits.GetGolbalUserData().dwUserID)
	{
		m_lGameGold = pUserScore->UserScore.lScore;
		m_lBankGold = pUserScore->UserScore.lInsureScore;
		m_bInitInfo = true;
		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}
	return true;
}

//�����Ϣ
bool CDlgBank::OnSocketToolBox(CMD_Command Command, void * pData, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_TOOLBOX);
	switch(Command.wSubCmdID)
	{
	case SUB_TOOLBOX_QUERYUSERNAME:  //��ѯ�û�������
		return OnQueryUserName(pData,wDataSize);
	case SUB_TOOLBOX_TRANSFERMONEY: //ת��
		return OnTransferMoney(pData,wDataSize);
	}

	return true;
}

//��ѯ�û���
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

//ת����ɴ���
bool CDlgBank::OnTransferMoney(void * pData, WORD wDataSize)
{
	ASSERT(wDataSize>=sizeof(CMD_TOOLBOX_TransferMoney_Ret));
	if (wDataSize<sizeof(CMD_TOOLBOX_TransferMoney_Ret))
		return false;
	CMD_TOOLBOX_TransferMoney_Ret *pTransRet = (CMD_TOOLBOX_TransferMoney_Ret*)pData;

	if (pTransRet->lErrorCode==0)
	{
		TCHAR szText[256];
		_snprintf(szText, sizeof(szText), "ת�˲����ɹ�: ת��%s��ң�˰��%s���", 
			GetString(pTransRet->sfMoneyNumber), GetString(pTransRet->sfTax), GetString(pTransRet->sfLeftMoney));
		ShowMessageBox(szText);
	}
	else
	{
		ShowMessageBox(pTransRet->szErrorDescribe);
	}

	return true;
}


//���͸ı�
void CDlgBank::OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabBank.GetCurSel())
	{
	case BANK_DLG_SAVE:
		{
			m_TabBank.SetCurSel(BANK_DLG_SAVE);
			SetDlgItemText(IDC_BANK_TEXT,TEXT("������Ŀ��"));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("�������룺"));
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
			SetDlgItemText(IDC_BANK_TEXT,TEXT("ȡ����Ŀ��"));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("�������룺"));
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
			SetDlgItemText(IDC_BANK_PLYNAME,TEXT("�������ID��"));
			SetDlgItemText(IDC_BANK_TEXT,TEXT("������Ŀ��"));
			SetDlgItemText(IDC_BANKPW_TEXT,TEXT("�������룺"));
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

// ���ò�������
WORD CDlgBank::GetOptType() const
{
	return m_wOpt;
}

// ��ȡ��������
void CDlgBank::SetOptType(WORD wType)
{
	m_wOpt = wType;
}

// ȷ������
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

// ȫ��
void CDlgBank::OnButtonAll()
{
	if(m_TabBank.GetCurSel() == BANK_DLG_SAVE)
		SetDlgItemText(IDC_EDIT3,GetString(m_lGameGold));
	else
		SetDlgItemText(IDC_EDIT3,GetString(m_lBankGold));
	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}

// �û�ID����ı�
void CDlgBank::OnEnUserIDChange()
{
	CString	buffer;
	GetDlgItemText(IDC_EDIT1, buffer);

	if (buffer.GetLength() >= 6)
	{
		DWORD dwUserID = atol(buffer.GetBuffer());
		if(dwUserID == g_GlobalUnits.GetGolbalUserData().dwGameID)
		{
			ShowMessageBox("���ܸ����Լ�ת�ˣ�");
			return;
		}
		CMD_TOOLBOX_QueryUserName Query;
		Query.lGameID = dwUserID;
		m_BankSocket->SendData(MDM_TOOLBOX, SUB_TOOLBOX_QUERYUSERNAME, &Query,sizeof(Query));
		return;
	}
}

//��Ǯȷ��
void CDlgBank::SaveGoldOk()
{
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("��Ҫȡ�Ľ���������㣡");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("�������������룡");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	//������֤
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
//ȡǮȷ��
void CDlgBank::GetGoldOk()
{
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("��Ҫȡ�Ľ���������㣡");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("�������������룡");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	//������֤
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
//ת��ȷ��
void CDlgBank::PtnGoldOK()
{
	DWORD dwGameID=GetDlgItemInt(IDC_EDIT1);
	if ( dwGameID==0 )
	{
		ShowMessageBox("��������Է�����ϷID");
		return;
	}
	if(dwGameID == g_GlobalUnits.GetGolbalUserData().dwGameID)
	{
		ShowMessageBox("���ܸ����Լ�ת�ˣ�");
		return;
	}
	CString strUserName;
	GetDlgItemText(IDC_EDIT2, strUserName);
	strUserName.Trim();
	if (strUserName.IsEmpty())
	{
		ShowMessageBox("�Է����˺Ų���Ϊ�գ�");
		return;
	}
	__int64 sfMoeny=GetDlgItemInt64(IDC_EDIT3);
	if ( sfMoeny<=0 )
	{
		ShowMessageBox("ת�˵Ľ���������㣡");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT4,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("�������������룡");
		GetDlgItem(IDC_EDIT4)->SetWindowText("");
		GetDlgItem(IDC_EDIT4)->SetFocus();
		return;
	}

	TCHAR szText[256];
	_snprintf(szText, sizeof(szText), "���ٴ�ȷ������ת�˲������Ƿ�������ȷ:\
		\n\n\nת����ϷID�� %d\nת���˻����� %s\n      �� %s���",
		dwGameID,strUserName, GetString(sfMoeny));
	if (IDYES == ShowInformationEx(szText,0,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1,TEXT("����")))
	{
		//������֤
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
