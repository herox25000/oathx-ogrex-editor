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

//��ʼ������
BOOL CFrameDlgBank::OnInitDialog()
{
	__super::OnInitDialog();
	SetWindowText(TEXT("����"));
	UpdateView();
	SetTimer(UPDATE_TIMER,2*1000,NULL);
	return TRUE; 
}

void CFrameDlgBank::OnTimer(UINT_PTR nIDEvent)
{
	__super::OnTimer(nIDEvent);
	if (nIDEvent == UPDATE_TIMER)
	{
		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}
}

//�滭��Ϣ
VOID CFrameDlgBank::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//ͼƬ����ָ��
	int Dex = 5;
	int Dey = 50;
	//����
	CPngImage ImageBankBK;
	ImageBankBK.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_BK"));
	Dex = (nWidth-ImageBankBK.GetWidth())/2L;
	ImageBankBK.DrawImage(pDC,Dex,Dey);
	//���
	CPngImage ImageBankFrame;
	ImageBankFrame.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_FRAME"));
	Dex = (nWidth-ImageBankFrame.GetWidth())/2L;
	ImageBankFrame.DrawImage(pDC,Dex,Dey);

	if(m_bInitInfo)
	{
		tagUserData* Medata = m_pIClientKernel->GetMeUserInfo();
		if(Medata != NULL)
		{
			//����
			DrawNumberString(pDC,Medata->lScore,Dex+55,Dey+13);
			DrawNumberString(pDC,Medata->lInsureScore,Dex+55,Dey+37);
		}
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
VOID CFrameDlgBank::DrawNumberString(CDC * pDC, __int64 lScore, INT nXPos, INT nYPos)
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
		ImageNumber.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_SCORE"));

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
VOID CFrameDlgBank::SwitchScoreFormat(__int64 lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
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
void CFrameDlgBank::OnClose()
{
	__super::OnClose();
}

void CFrameDlgBank:: OnCancel()
{
	__super::OnCancel();
}
//��ʾ��Ϣ
int CFrameDlgBank::ShowMessageBox(LPCTSTR pszMessage)
{				
	int nResult = ShowInformationEx(pszMessage,0,MB_ICONQUESTION,TEXT("����"));
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
	// ��Ϸ�в��ܴ�Ǯ
	if(m_BankType == 1)
	{
		ShowMessageBox("��Ϸ�в��ܴ�Ǯ����");
		return;
	}

	__int64 Imoney = GetDlgItemInt64(IDC_EDIT_GOLD);
	if ( Imoney<=0 )
	{
		ShowMessageBox("��Ҫȡ�Ľ���������㣡");
		return;
	}
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_EDIT_BANKPW,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowMessageBox("�������������룡");
		GetDlgItem(IDC_EDIT_BANKPW)->SetWindowText("");
		GetDlgItem(IDC_EDIT_BANKPW)->SetFocus();
		return;
	}

	//������֤
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
	////��Ǯ
	//if(m_BankType==1)
	//{	
	//	SetDlgItemText(IDC_EDIT_GOLD,GetString(m_lGameGold));
	//}
	//else if(m_BankType==2) //ȡǮ
	//{
		SetDlgItemText(IDC_EDIT_GOLD,GetString(Medata->lInsureScore));
	//}
	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}


void CFrameDlgBank::UpdateView()
{
	m_bInitInfo = true;
	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}