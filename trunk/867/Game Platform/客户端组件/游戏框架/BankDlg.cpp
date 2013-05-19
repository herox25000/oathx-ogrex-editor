#include "stdafx.h"
#include "resource.h"
#include "BankDlg.h"

//////////////////////////////////////////////////////////////////////////
CFrameDlgBank::CFrameDlgBank() : CSkinPngDialog(IDD_DLG_BANK)
{
	m_lGameGold = 0;
	m_lBankGold = 0;
	m_BankType=0;
	m_pIClientKernel = NULL;
	m_bInitInfo = false;
}

CFrameDlgBank::~CFrameDlgBank()
{

}

void CFrameDlgBank::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
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
	SetTimer(UPDATE_TIMER,2*1000,NULL);
	return TRUE; 
}

void CFrameDlgBank::OnTimer(UINT_PTR nIDEvent)
{
	__super::OnTimer(nIDEvent);
	if (nIDEvent == UPDATE_TIMER)
	{
		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}
}

//绘画消息
VOID CFrameDlgBank::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//图片绘制指标
	int Dex = 5;
	int Dey = 50;
	//背景
	CPngImage ImageBankBK;
	ImageBankBK.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_BK"));
	Dex = (nWidth-ImageBankBK.GetWidth())/2L;
	ImageBankBK.DrawImage(pDC,Dex,Dey);
	//框架
	CPngImage ImageBankFrame;
	ImageBankFrame.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_FRAME"));
	Dex = (nWidth-ImageBankFrame.GetWidth())/2L;
	ImageBankFrame.DrawImage(pDC,Dex,Dey);

	if(m_bInitInfo)
	{
		tagUserData* Medata = m_pIClientKernel->GetMeUserInfo();
		if(Medata != NULL)
		{
			//数字
			DrawNumberString(pDC,Medata->lScore,Dex+55,Dey+13);
			DrawNumberString(pDC,Medata->lInsureScore,Dex+55,Dey+37);
		}
	}

	//构造提示
	TCHAR szString[128]=TEXT("");
	_sntprintf(szString,CountArray(szString),TEXT("温馨提示：请妥善保管密码，警防盗号！"));
	//温馨提示
	pDC->SetTextColor(RGB(50,50,50));
	pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));

	return;
}

//绘画数字
VOID CFrameDlgBank::DrawNumberString(CDC * pDC, __int64 lScore, INT nXPos, INT nYPos)
{
	//转换逗号
	TCHAR szControl[128]=TEXT("");
	SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

	//变量定义
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//绘画判断
	if (nScoreLength>0L)
	{
		//加载资源
		CPngImage ImageNumber;
		ImageNumber.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_SCORE"));

		//获取大小
		CSize SizeNumber;
		SizeNumber.SetSize(ImageNumber.GetWidth()/12L,ImageNumber.GetHeight());

		//绘画数字
		for (INT i=0;i<nScoreLength;i++)
		{
			//绘画逗号
			if (szControl[i]==TEXT(','))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//绘画点号
			if (szControl[i]==TEXT('.'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//绘画数字
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//设置位置
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}


//转换字符
VOID CFrameDlgBank::SwitchScoreFormat(__int64 lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//转换数值
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//变量定义
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//转换字符
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//拷贝字符
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//插入逗号
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//结束字符
	pszBuffer[wTargetIndex++]=0;

	return;
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
	tagUserData* Medata = m_pIClientKernel->GetMeUserInfo();
	if(Medata == NULL)
		return;
	////存钱
	//if(m_BankType==1)
	//{	
	//	SetDlgItemText(IDC_EDIT_GOLD,GetString(m_lGameGold));
	//}
	//else if(m_BankType==2) //取钱
	//{
		SetDlgItemText(IDC_EDIT_GOLD,GetString(Medata->lInsureScore));
	//}
	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}


void CFrameDlgBank::UpdateView()
{
	m_bInitInfo = true;
	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}