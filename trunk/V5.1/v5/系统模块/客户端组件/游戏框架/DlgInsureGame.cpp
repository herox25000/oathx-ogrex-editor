// DlgBank.cpp : implementation file
//

#include "stdafx.h"
#include "DlgInsureGame.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

//������
//class CGameClientView;
#define IDC_OK				500
#define IDC_CANCEL			501
#define	IDC_FRESH			502

//////////////////////////////////////////////////////////////////////////

//��ʱ��I D
#define IDI_CHARMVALUE_UPDATE_VIEW		1								//���½���
#define TIME_CHARMVALUE_UPDATE_VIEW		200								//���½���

//////////////////////////////////////////////////////////////////////////

//ת���ַ���
void MakeString(CString &strNum,SCORE lNumber)
{
	CString strTempNum;
	strTempNum.Format(_T("%I64d"), (lNumber>0?lNumber:-lNumber));

	int nLength = strTempNum.GetLength();
	for (int i = 0; i < int((nLength-1)/3); i++)
		strTempNum.Insert(nLength - 3*(i+1), _T(","));
	strNum.Format(_T("%s%s"), (lNumber<0?_T("-"):_T("")), strTempNum);
}

//ת������
void MakeStringToNum(CString str,SCORE &Num)
{
	CString strNumber = str;
	strNumber.Remove(',');
	strNumber.Trim();

#ifndef _UNICODE
	_snscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#else
	_snwscanf(strNumber.GetBuffer(),strNumber.GetLength(),_TEXT("%I64d"),&Num);
#endif
	strNumber.ReleaseBuffer();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDlgInsureGame, CSkinDialog)
CDlgInsureGame::CDlgInsureGame(CWnd* pParent /*=NULL*/)
	: CSkinDialog(IDD_BANK_STORAGE, pParent)
{
	m_wRevenueTake=0;
	m_wRevenueTransfer=0;
	m_lInCount=0;
	m_lGameGold=0;
	m_lStorageGold=0;
	m_pMeUserData=NULL;
	m_pIClientKernel=NULL;
	m_bBankStorage=true;
	m_blCanStore=false;
	m_blCanGetOnlyFree=false;
	m_ImageFrame.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANK_FRAME"));	
	m_ImageNumber.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("BANKNUM"));
}

CDlgInsureGame::~CDlgInsureGame()
{
}

void CDlgInsureGame::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_USER_PASSWORD, m_Edit);
	DDX_Control(pDX, IDC_STATIC_PASS, m_Static);
}


BEGIN_MESSAGE_MAP(CDlgInsureGame, CSkinDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()	
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FRESH,OnBnClickedFresh)
	ON_BN_CLICKED(IDC_OK,OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL,OnCancelEvent)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnBnClickedCheck)
	ON_EN_CHANGE(IDC_IN_COUNT, OnEnChangeInCount)
	ON_MESSAGE(WM_CREADED,OnCreateEd)

END_MESSAGE_MAP()

//��ѡ
void CDlgInsureGame::OnBnClickedCheck()
{
	if(IsButtonSelected(IDC_CHECK_ALL))
	{
		if(m_pMeUserData!=NULL)
		{
			//������Ϣ
			m_lInCount=(m_bBankStorage)?m_lGameGold:m_lStorageGold;

			//������ʾ
			CString strlGameGold;
			MakeString(strlGameGold,m_lInCount);
			SetDlgItemText(IDC_IN_COUNT,strlGameGold);
		}
	}
	else
	{
		//������ʾ
		SetDlgItemText(IDC_IN_COUNT,_TEXT(""));
		GetDlgItem(IDC_IN_COUNT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(0,-1);
	}
}

//�滭����
VOID CDlgInsureGame::DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos)
{
	//ת������
	TCHAR szControl[128]=TEXT("");
	CString cs;

	//ת����ʽ
	MakeString(cs,lScore);
	_sntprintf(szControl,CountArray(szControl),TEXT("%s"),cs);

	//��������
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//�滭�ж�
	if (nScoreLength>0L)
	{
		//��ȡ��С
		CSize SizeNumber;
		SizeNumber.SetSize(m_ImageNumber.GetWidth()/12L,m_ImageNumber.GetHeight());

		//�滭����
		for (INT i=0;i<nScoreLength;i++)
		{
			//�滭����
			if (szControl[i]==TEXT(','))
			{
				m_ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//�滭���
			if (szControl[i]==TEXT('.'))
			{
				m_ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//�滭����
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				m_ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//����λ��
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}

//ˢ�°�ť
void CDlgInsureGame::OnBnClickedFresh()
{
	//��������
	CMD_GR_C_QueryInsureInfoRequest QueryInsureInfo;
	QueryInsureInfo.cbActivityGame=TRUE;

	//��������
	SendSocketData(MDM_GR_INSURE,SUB_GR_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));
}

//��ȡ��ť
void CDlgInsureGame::OnBnClickedOk()
{	
	//����ת��
	CString strInCount;
	GetDlgItem(IDC_IN_COUNT)->GetWindowText(strInCount);
	MakeStringToNum(strInCount, m_lInCount);

	//������֤
	if (false==m_bBankStorage && (m_lInCount <= 0 || m_lInCount > m_lStorageGold ))
	{
		//������Ϣ
		CString strMessage;
		if(m_lStorageGold>0)strMessage.Format(TEXT("���������Ϸ��ֵ������1��%I64d֮��"), m_lStorageGold);
		else strMessage.Format(TEXT("��Ĵ洢��Ϸ����ĿΪ0,���ܽ�����ȡ����!"));

		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(strMessage,MB_ICONERROR,30);

		GetDlgItem(IDC_IN_COUNT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(0,-1);
		GetDlgItem(IDC_USER_PASSWORD)->SetWindowText(_TEXT(""));
		return;
	}

	//������֤
	if (true==m_bBankStorage && (m_lInCount <= 0 || m_lInCount > m_lGameGold ))
	{
		//������Ϣ
		CString strMessage;
		if(m_lGameGold>0)strMessage.Format(TEXT("���������Ϸ��ֵ������1��%I64d֮��"),m_lGameGold );
		else strMessage.Format(TEXT("��ĵ�ǰ��Ϸ����ĿΪ0,���ܽ��д洢����!"));

		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(strMessage,MB_ICONERROR,30);

		GetDlgItem(IDC_IN_COUNT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(0,-1);
		GetDlgItem(IDC_USER_PASSWORD)->SetWindowText(_TEXT(""));
		return;
	}

	//������֤
	TCHAR szPassword[LEN_PASSWORD]=TEXT("");
	GetDlgItemText(IDC_USER_PASSWORD,szPassword,CountArray(szPassword));
	if (szPassword[0]==0&&m_blUsingPassWord)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���벻��Ϊ�գ��������������룡"),MB_ICONERROR,30);

		GetDlgItem(IDC_USER_PASSWORD)->SetWindowText(_TEXT(""));
		GetDlgItem(IDC_USER_PASSWORD)->SetFocus();
		return;
	}

	//�������
	if(m_blUsingPassWord)
	{
		TCHAR szTempPassword[LEN_PASSWORD]=TEXT("");
		CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
		CWHEncrypt::MD5Encrypt(szTempPassword,szPassword);

	}

	//ȡ��
	if (false==m_bBankStorage)
	{
		//��������
		CMD_GR_C_TakeScoreRequest TakeScoreRequest;
		ZeroMemory(&TakeScoreRequest,sizeof(TakeScoreRequest));
		TakeScoreRequest.cbActivityGame=TRUE;
		TakeScoreRequest.lTakeScore=m_lInCount;
		CopyMemory(TakeScoreRequest.szInsurePass, szPassword, sizeof(TakeScoreRequest.szInsurePass));

		//��������
		SendSocketData(MDM_GR_INSURE,SUB_GR_TAKE_SCORE_REQUEST,&TakeScoreRequest,sizeof(TakeScoreRequest));
	}
	else
	{
		//״̬�ж�
		if (US_PLAYING==m_pMeUserData->GetUserStatus())
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("�������Ϸ���ٴ�"),MB_ICONERROR,30);
			return;	
		}

		//��������
		CMD_GR_C_SaveScoreRequest SaveScoreRequest;
		SaveScoreRequest.cbActivityGame=TRUE;
		SaveScoreRequest.lSaveScore=m_lInCount;

		//��������
		SendSocketData(MDM_GR_INSURE,SUB_GR_SAVE_SCORE_REQUEST,&SaveScoreRequest,sizeof(SaveScoreRequest));
	}

	//�������
	GetDlgItem(IDC_USER_PASSWORD)->SetWindowText(_TEXT(""));

	return;
}

//��ʼ������
BOOL CDlgInsureGame::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	UpdateData(FALSE);
	SetWindowText(TEXT("���չ�"));
	SetBankerActionType(true);	

	//��ʱ����
	SetTimer(IDI_CHARMVALUE_UPDATE_VIEW,TIME_CHARMVALUE_UPDATE_VIEW,NULL);

	return TRUE;
}

//�滭����
VOID CDlgInsureGame::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{	
	m_ImageFrame.DrawImage(pDC,30,55);
	DrawNumberString(pDC,m_lGameGold,200,78);
	DrawNumberString(pDC,m_lStorageGold,200,104);
	CRect rcScore(120,80,200,95);
	pDC->DrawText(TEXT("��ǰ��Ϸ�ң�"),rcScore,DT_END_ELLIPSIS | DT_CENTER | DT_WORDBREAK);
	CRect rcBank(120,105,200,120);
	pDC->DrawText(TEXT("���չ���Ϸ�ң�"),rcBank,DT_END_ELLIPSIS | DT_CENTER | DT_WORDBREAK);
	CRect rect(0,315,nWidth,nHeight);
	CString strInfo;
	strInfo.Format(TEXT("��ܰ��ʾ��������Ϸ���������ѣ�ȡ�����۳�%ld���������"), m_wRevenueTake);
	pDC->DrawText(strInfo,rect,DT_END_ELLIPSIS | DT_CENTER | DT_WORDBREAK);
}

//���½���
void CDlgInsureGame::UpdateView()
{
	//��ȡ����
	CString strinCount;
	GetDlgItemText(IDC_IN_COUNT,strinCount);
	SCORE OutNum = 0;
	MakeStringToNum(strinCount,OutNum);

	//��������
	if(m_OrInCount!= OutNum)
	{
		m_OrInCount = OutNum;
		if(OutNum!=0)
		{
			MakeString(strinCount,OutNum);
			SetDlgItemText(IDC_IN_COUNT,strinCount);
			((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(strinCount.GetLength(),strinCount.GetLength(),TRUE); 
		}

		//������֤
		if (false==m_bBankStorage && (OutNum < 0 || OutNum > m_lStorageGold ))
		{
			return;
		}

		//������֤
		if (true==m_bBankStorage && (OutNum < 0 || OutNum > m_lGameGold ))
		{
			return;
		}
	}

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}

//�����Ϣ
void CDlgInsureGame::OnLButtonDown(UINT nFlags, CPoint point)
{
	CSkinDialog::OnLButtonDown(nFlags, point);
}

//�����Ϣ
void CDlgInsureGame::OnMouseMove(UINT nFlags, CPoint point)
{
	CSkinDialog::OnMouseMove(nFlags, point);
}

//������Ϣ
BOOL CDlgInsureGame::PreTranslateMessage(MSG* pMsg)
{
	//������ĸ
	if(GetFocus()==GetDlgItem(IDC_IN_COUNT)&& pMsg->message==WM_CHAR)
	{
		BYTE bMesValue = (BYTE)(pMsg->wParam);
		BYTE bTemp = bMesValue-'0';
		if((bTemp<0 || bTemp>9) && bMesValue!=VK_BACK) return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}

//ʱ����Ϣ
void CDlgInsureGame::OnTimer(UINT nIDEvent)
{
	//ʱ����Ϣ
	switch(nIDEvent)
	{
	case IDI_CHARMVALUE_UPDATE_VIEW:		//���½���
		{
			//���½���
			UpdateView();
			return;
		}
	}
	__super::OnTimer(nIDEvent);
}

//������Ϣ
void CDlgInsureGame::OnEnChangeInCount()
{
	//״̬Ч��
	if(!m_pMeUserData) return;

	//��ȡ����
	CString strCount;
	GetDlgItem(IDC_IN_COUNT)->GetWindowText(strCount);

	//ȥ��ǰ���0
	CString strLeft = strCount.Left(1);
	if(strLeft.Find('0') != -1)
	{
		strCount = strCount.Right(strCount.GetLength() - 1);
		SetDlgItemText(IDC_IN_COUNT,strCount);
	}

	//������Ϣ
	SCORE lInCount=(m_bBankStorage)?m_lGameGold:m_lStorageGold;
	MakeStringToNum(strCount, m_lInCount);
	if((m_lInCount > lInCount || m_lInCount < 0L))
	{
		m_lInCount = lInCount;
		CString strlGameGold;
		MakeString(strlGameGold,m_lInCount);
		SetDlgItemText(IDC_IN_COUNT,strlGameGold);
	}

	return ;
}

//�Ƿ�ѡ��
bool CDlgInsureGame::IsButtonSelected(UINT uButtonID)
{
	return ((CButton *)GetDlgItem(uButtonID))->GetCheck()==BST_CHECKED;
}

//������Ϣ
int CDlgInsureGame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;
	CRect rect(0, 0, 0, 0);	
	m_btOK.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rect,this,IDC_OK);	
	m_btCancel.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rect,this,IDC_CANCEL);
	m_btFresh.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rect,this,IDC_FRESH);
	m_btOK.SetWindowPos(NULL,110,240,94,32,SWP_NOSIZE);
	m_btCancel.SetWindowPos(NULL,285,240,94,32,SWP_NOSIZE);
	m_btFresh.SetWindowPos(NULL,390,66,64,64,SWP_NOSIZE);
	
	return 0;
}

//������Ϣ
afx_msg LRESULT  CDlgInsureGame::OnCreateEd(WPARAM wparam,LPARAM lparam)
{
	return 1;
}

//ѡ�а�ť
void CDlgInsureGame::SetButtonSelected(UINT uButtonID, bool bSelected)
{
	CButton * pButton=(CButton *)GetDlgItem(uButtonID);
	if (bSelected) pButton->SetCheck(BST_CHECKED);
	else pButton->SetCheck(BST_UNCHECKED);
	return;
}

//������Ϣ
void CDlgInsureGame::SetSendInfo(IClientKernel *pClientKernel,IClientUserItem const*pMeUserData)
{
	//����Ч��
	ASSERT(pClientKernel!=NULL);
	if(pClientKernel==NULL) return;

	//������Ϣ
	m_pIClientKernel = pClientKernel;
	m_pMeUserData=const_cast<IClientUserItem *>(pMeUserData);

	//������Ϣ
	OnBnClickedFresh();

	return;
}

//����λ��
void CDlgInsureGame::SetPostPoint(CPoint Point)
{
	CRect Rect;
	GetWindowRect(&Rect);
	SetWindowPos(NULL,Point.x,Point.y-Rect.bottom+Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,/*SWP_NOMOVE|*/SWP_NOZORDER);
}

//������Ϣ
void CDlgInsureGame::SendSocketData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	//����Ч��
	ASSERT(m_pIClientKernel!=NULL);

	//������Ϣ
	if(m_pIClientKernel) m_pIClientKernel->SendSocketData(wMainCmdID, wSubCmdID, pBuffer, wDataSize);

	return ;
}

//��ʾ����
void CDlgInsureGame::ShowItem()
{
	//���ÿؼ�
	HINSTANCE hInstance = GetModuleHandle(GAME_FRAME_DLL_NAME);	
	m_btFresh.SetButtonImage(IDB_BT_FRESH,hInstance,false,false);
	m_btFresh.EnableWindow(TRUE);
	if(m_bBankStorage)
	{
		GetDlgItem(IDC_IN_COUNT)->EnableWindow(TRUE);
	    GetDlgItem(IDC_USER_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_USER_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PASS)->ShowWindow(SW_HIDE);
		m_btOK.SetButtonImage(IDB_SAVEGOLD, hInstance, false,false);
		m_btCancel.SetButtonImage(IDB_CLOSE,hInstance,false,false);
		m_btOK.EnableWindow(m_blCanStore);
		m_btCancel.EnableWindow(TRUE);
	}
	else
	{
		BOOL bShow = TRUE;
		if(m_blCanGetOnlyFree && m_pMeUserData->GetUserStatus() == US_PLAYING) bShow = FALSE;
		GetDlgItem(IDC_IN_COUNT)->EnableWindow(TRUE);
		GetDlgItem(IDC_USER_PASSWORD)->EnableWindow(TRUE);
		GetDlgItem(IDC_USER_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PASS)->ShowWindow(SW_SHOW);
		m_btOK.SetButtonImage(IDB_GETGOLD, hInstance, false,false);
		m_btCancel.SetButtonImage(IDB_CLOSE,hInstance,false,false);
		m_btOK.EnableWindow(bShow);
		m_btCancel.EnableWindow(TRUE);
	}

}

//��������
void CDlgInsureGame::SetBankerActionType(bool bStorage) 
{
	//���ñ���
	m_bBankStorage = bStorage;
	m_lInCount = 0;
	GetDlgItem(IDC_IN_COUNT)->SetWindowText(TEXT(""));
	((CButton*)GetDlgItem(IDC_CHECK_ALL))->SetCheck(0);

	//���ñ���
	if (m_bBankStorage)
	{
		m_blUsingPassWord = false;
	}
	else
	{
		m_blUsingPassWord = true;
	}

	//��ʾ�����
	if(m_blUsingPassWord)
	{
		GetDlgItem(IDC_USER_PASSWORD)->EnableWindow(m_blCanStore);
	}

	//��ʾ�ؼ�
	ShowItem();
}

//�ر�
void CDlgInsureGame::OnCancelEvent()
{
	DestroyWindow();
}

//ȡ��
void CDlgInsureGame::OnCancel()
{
	DestroyWindow();
}

//�س�
void CDlgInsureGame::OnOK()
{
	OnBnClickedOk();
}
