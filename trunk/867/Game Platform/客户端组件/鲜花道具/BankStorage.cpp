#include "Stdafx.h"
#include "resource.h"
#include "BankStorage.h"
#include ".\bankstorage.h"

//////////////////////////////////////////////////////////////////////////

//��ʱ��I D
#define IDI_CHARMVALUE_UPDATE_VIEW		1								//���½���
#define TIME_CHARMVALUE_UPDATE_VIEW		200								//���½���

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CBankStorage, CSkinDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()	
	ON_BN_CLICKED(IDOK,OnBnClickedOk)
	ON_EN_CHANGE(IDC_IN_COUNT, OnEnChangeInCount)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CBankStorage::CBankStorage(CWnd* pParent):CSkinDialogEx(IDD_BANK_STORAGE, pParent)
{
	m_lInCount=0;
	m_lGameGold=0;
	m_lStorageGold=0;
	m_pMeUserData=NULL;
	m_pIClientKernel=NULL;
	m_pClientSocket=NULL;
}

//��������
CBankStorage::~CBankStorage()
{
}

//�ؼ���
void CBankStorage::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Text(pDX, IDC_GAME_GOLD, m_lGameGold);
	DDX_Text(pDX, IDC_STORAGE_GOLD, m_lStorageGold);
}

//��ȡ��ť
void CBankStorage::OnBnClickedOk()
{
	//������֤
	if (IsButtonSelected(IDC_DRAWOUT) && (m_lInCount <= 0 || m_lInCount > m_lStorageGold ))
	{
		CString strMessage;
		if(m_lStorageGold>0)strMessage.Format(TEXT("���������Ϸ��ֵ������1��%ld֮��"), m_lStorageGold);
		else strMessage.Format(TEXT("��Ĵ洢��Ϸ����ĿΪ0,���ܽ�����ȡ����!"));
		ShowInformationEx(strMessage,0 ,MB_ICONINFORMATION,TEXT("ϵͳ��Ϣ")) ;

		GetDlgItem(IDC_IN_COUNT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(0,-1);
		return;
	}

	//������֤
	if (IsButtonSelected(IDC_STORAGE) && (m_lInCount <= 0 || m_lInCount > m_lGameGold ))
	{
		CString strMessage;
		if(m_lGameGold>0)strMessage.Format(TEXT("���������Ϸ��ֵ������1��%ld֮��"),m_lGameGold );
		else strMessage.Format(TEXT("��ĵ�ǰ��Ϸ����ĿΪ0,���ܽ��д洢����!"));
		ShowInformationEx(strMessage,0 ,MB_ICONINFORMATION,TEXT("ϵͳ��Ϣ")) ;

		GetDlgItem(IDC_IN_COUNT)->SetFocus();
		((CEdit*)GetDlgItem(IDC_IN_COUNT))->SetSel(0,-1);
		return;
	}

	//������֤
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_USER_PASSWORD,szPassword,CountArray(szPassword));
	if (szPassword[0]==0)
	{
		ShowInformationEx(TEXT("���벻��Ϊ�գ��������������룡"),0 ,MB_ICONINFORMATION,TEXT("ϵͳ��Ϣ")) ;
		GetDlgItem(IDC_USER_PASSWORD)->SetWindowText("");
		GetDlgItem(IDC_USER_PASSWORD)->SetFocus();
		return;
	}
	TCHAR szTempPassword[PASS_LEN]=TEXT("");
	CopyMemory(szTempPassword,szPassword,sizeof(szTempPassword));
	CMD5Encrypt::EncryptData(szTempPassword,szPassword);

	if (IsButtonSelected(IDC_DRAWOUT))
	{
		//������Ϣ
		CMD_GF_BankGet BankGetGold;
		ZeroMemory(&BankGetGold, sizeof(BankGetGold));
		BankGetGold.lGetValue = m_lInCount;
		CopyMemory(BankGetGold.szPassword,szPassword,sizeof(BankGetGold.szPassword));

		SendData(MDM_GF_BANK, SUB_GF_BANK_GET, &BankGetGold, sizeof(BankGetGold));
	}
	else
	{
		//������Ϣ
		CMD_GF_BankStorage BankStorage;
		ZeroMemory(&BankStorage, sizeof(BankStorage));
		BankStorage.lStorageValue = m_lInCount;
		CopyMemory(BankStorage.szPassword,szPassword,sizeof(BankStorage.szPassword));

		SendData(MDM_GF_BANK, SUB_GF_BANK_STORAGE, &BankStorage, sizeof(BankStorage));
	}

	return;
}

//��ʼ������
BOOL CBankStorage::OnInitDialog()
{
	CSkinDialogEx::OnInitDialog();

	UpdateData(FALSE);

	SetWindowText(TEXT("����"));

	//������ֵ
	SetButtonSelected(IDC_STORAGE,true);

	//��ʱ����
	SetTimer(IDI_CHARMVALUE_UPDATE_VIEW,TIME_CHARMVALUE_UPDATE_VIEW,NULL);

	return TRUE;
}

//���½���
void CBankStorage::UpdateView()
{
	UpdateData(TRUE);

	if(m_pMeUserData==NULL)return;

	//������Ϣ
	m_lGameGold=((m_pMeUserData->lGameGold<0)?0:m_pMeUserData->lGameGold);
	m_lStorageGold=m_pMeUserData->lInsureScore;

	UpdateData(FALSE);
}

//�����Ϣ
void CBankStorage::OnLButtonDown(UINT nFlags, CPoint point)
{
	CSkinDialogEx::OnLButtonDown(nFlags, point);
}

//�����Ϣ
void CBankStorage::OnMouseMove(UINT nFlags, CPoint point)
{
	CSkinDialogEx::OnMouseMove(nFlags, point);
}

//������Ϣ
BOOL CBankStorage::PreTranslateMessage(MSG* pMsg)
{
	//������ĸ
	if(GetFocus()==GetDlgItem(IDC_IN_COUNT)&& pMsg->message==WM_CHAR)
	{
		BYTE bMesValue = (BYTE)(pMsg->wParam);
		BYTE bTemp = bMesValue-'0';
		if((bTemp<0 || bTemp>9) && bMesValue!=VK_BACK) return TRUE;
	}

	////���˻س�
	//if(pMsg->message==WM_KEYDOWN)
	//{
	//	BYTE bMesValue = (BYTE)(pMsg->wParam);
	//	if(bMesValue==VK_RETURN) return TRUE;
	//}

	return __super::PreTranslateMessage(pMsg);
}

//ʱ����Ϣ
void CBankStorage::OnTimer(UINT nIDEvent)
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
void CBankStorage::OnEnChangeInCount()
{
	CString strCount;
	GetDlgItem(IDC_IN_COUNT)->GetWindowText(strCount);
	m_lInCount=_tstol(strCount);

	return ;
}

//�Ƿ�ѡ��
bool CBankStorage::IsButtonSelected(UINT uButtonID)
{
	return ((CButton *)GetDlgItem(uButtonID))->GetCheck()==BST_CHECKED;
}

//ѡ�а�ť
void CBankStorage::SetButtonSelected(UINT uButtonID, bool bSelected)
{
	CButton * pButton=(CButton *)GetDlgItem(uButtonID);
	if (bSelected) pButton->SetCheck(BST_CHECKED);
	else pButton->SetCheck(BST_UNCHECKED);
	return;
}

//������Ϣ
void CBankStorage::SetSendInfo(IClientKernel *pClientKernel,ITCPSocket *pClientSocket,tagUserData *pMeUserData)
{
	ASSERT((pClientKernel==NULL && pClientSocket!=NULL)||(pClientKernel!=NULL && pClientSocket==NULL));

	//������Ϣ
	m_pIClientKernel = pClientKernel;
	m_pClientSocket= pClientSocket;
	m_pMeUserData= pMeUserData;

	return;
}

//������Ϣ
void CBankStorage::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	ASSERT((m_pIClientKernel==NULL && m_pClientSocket!=NULL)||(m_pIClientKernel!=NULL && m_pClientSocket==NULL));

	//������Ϣ
	if(m_pClientSocket!=NULL)m_pClientSocket->SendData(wMainCmdID, wSubCmdID, pBuffer, wDataSize);
	else m_pIClientKernel->SendSocketData(wMainCmdID, wSubCmdID, pBuffer, wDataSize);

	return ;
}
//////////////////////////////////////////////////////////////////////////

//�һ�����
extern "C" PROPERTY_MODULE_CLASS VOID __cdecl ShowBankStorageDlg(IClientKernel *pIClientKernel,ITCPSocket *pClientSocket,tagUserData *pMeUserData)
{
	//�һ�����
	CBankStorage BankStorageDlg;

	//������Ϣ
	BankStorageDlg.SetSendInfo(pIClientKernel,pClientSocket,pMeUserData);
	BankStorageDlg.DoModal();

	return ;
}

//////////////////////////////////////////////////////////////////////////

