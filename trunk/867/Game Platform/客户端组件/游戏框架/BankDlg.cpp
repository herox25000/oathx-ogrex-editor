#include "stdafx.h"
#include "resource.h"
#include "BankDlg.h"

//////////////////////////////////////////////////////////////////////////
CFrameDlgBank::CFrameDlgBank() : CSkinPngDialog(IDD_DLG_BANK)
{
	m_strGameGold.Empty();
	m_strBankGold.Empty();
	m_BankType=0;
	m_pIClientKernel = NULL;
}

CFrameDlgBank::~CFrameDlgBank()
{

}

void CFrameDlgBank::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_GOLD,		m_strGameGold);
	DDX_Text(pDX, IDC_STATIC_BANKGOLD,		m_strBankGold);
	DDX_Control(pDX, IDC_BT_OK,	m_btOK);
	DDX_Control(pDX, IDC_BT_ALL,m_btAll);
}

BEGIN_MESSAGE_MAP(CFrameDlgBank, CSkinPngDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_ALL, OnButtonAll)
	ON_BN_CLICKED(IDC_BT_OK, OnButtonOK)
END_MESSAGE_MAP()


BOOL CFrameDlgBank::PreTranslateMessage(MSG* pMsg)
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
BOOL CFrameDlgBank::OnInitDialog()
{
	__super::OnInitDialog();
	SetWindowText(TEXT("银行"));
	UpdateView();
	SetTimer(UPDATE_TIMER,3*1000,NULL);
	return TRUE; 
}

void CFrameDlgBank::OnTimer(UINT_PTR nIDEvent)
{
	__super::OnTimer(nIDEvent);
	if (nIDEvent == UPDATE_TIMER)
	{
		UpdateView();
	}
}

//销毁消息
void CFrameDlgBank::OnClose()
{
	__super::OnClose();
}

void CFrameDlgBank:: OnCancel()
{
	__super::OnCancel();
}
//显示消息
int CFrameDlgBank::ShowMessageBox(LPCTSTR pszMessage)
{				
	int nResult = ShowInformationEx(pszMessage,0,MB_ICONQUESTION,TEXT("银行"));
	return nResult;
}

__int64 CFrameDlgBank::GetDlgItemInt64(UINT uID)
{
	CString buffer;
	GetDlgItemText(uID, buffer);
	buffer.Remove(',');
	return _atoi64(buffer.GetBuffer());
};

CString CFrameDlgBank::GetString(__int64 nNumber)
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

void CFrameDlgBank::OnButtonOK()
{
	// 游戏中不能存钱
	if(m_BankType == 1)
	{
		ShowMessageBox("游戏中不能存钱！！");
		return;
	}

	__int64 Imoney = GetDlgItemInt64(IDC_EDIT_GOLD);
	if ( Imoney<=0 )
	{
		ShowMessageBox("需要取的金额必须大于零！");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT_BANKPW,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("请输入银行密码！");
		GetDlgItem(IDC_EDIT_BANKPW)->SetWindowText("");
		GetDlgItem(IDC_EDIT_BANKPW)->SetFocus();
		return;
	}

	//密码验证
	TCHAR szTempPassword[PASS_LEN]=TEXT("");
	CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
	CMD5Encrypt::EncryptData(szTempPassword,szPassword);

	CMD_TOOLBOX_BankTask BankTask;
	memset(&BankTask, 0, sizeof(CMD_TOOLBOX_BankTask));
	BankTask.lMoneyNumber=Imoney;
	BankTask.lBankTask=BANKTASK_WITHDRAW;
	CopyMemory(BankTask.szPassword,szPassword,sizeof(BankTask.szPassword));
	m_pIClientKernel->SendSocketData(MDM_TOOLBOX, SUB_TOOLBOX_BANKOPERATING, &BankTask, sizeof(BankTask));

}

void CFrameDlgBank::OnButtonAll()
{
	//存钱
	if(m_BankType==1)
	{	
		SetDlgItemText(IDC_EDIT_GOLD,m_strGameGold);
	}
	else if(m_BankType==2) //取钱
	{
		SetDlgItemText(IDC_EDIT_GOLD,m_strBankGold);
	}
	UpdateData(FALSE);
}


void CFrameDlgBank::UpdateView()
{
	if(m_pIClientKernel == NULL)
		return;
	tagUserData* Medata = m_pIClientKernel->GetMeUserInfo();
	if(Medata == NULL)
		return;
	m_strGameGold = GetString(Medata->lScore);
	m_strBankGold = GetString(Medata->lInsureScore);
	UpdateData(FALSE);
}