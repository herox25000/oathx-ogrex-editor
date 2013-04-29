#include "Stdafx.h"
#include "resource.h"
#include "CharmValueExchange.h"
#include ".\charmvalueexchange.h"

//////////////////////////////////////////////////////////////////////////

//��ʱ��I D
#define IDI_CHARMVALUE_UPDATE_VIEW		1								//���½���
#define TIME_CHARMVALUE_UPDATE_VIEW		500								//���½���

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCharmValueExchange, CSkinPngDialog)
	ON_WM_TIMER()	
	ON_EN_CHANGE(IDC_EXCHANGE_CHARM_VALUE, OnEnChangeExchangeCharmValue)
	ON_BN_CLICKED(IDC_BT_EXCHANGE, OnBnClickedBtExchange)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CCharmValueExchange::CCharmValueExchange(CWnd* pParent):CSkinPngDialog(IDD_CHARM_VALUE_EXCHANGE, pParent)
{
	m_lExchangeCharmValue=0;
	m_lLoveliness=0;
	m_lBankGoldValue=0;
	m_pIClientKernel=NULL;
	m_pClientSocket=NULL;
	m_pMeUserData = NULL;
}

//��������
CCharmValueExchange::~CCharmValueExchange()
{
}

//�ؼ���
void CCharmValueExchange::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_EXCHANGE, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Text(pDX, IDC_EXCHANGE_VALUE, m_strExChangeValue);
	DDX_Text(pDX, IDC_CHARM_VALUE, m_lLoveliness);
	DDX_Text(pDX, IDC_GOLD_VALUE, m_lBankGoldValue);
}

//ȷ����Ϣ
void CCharmValueExchange::OnBnClickedBtExchange()
{
	ShowInformation("�˹�����ʱû���ţ�",10,MB_ICONINFORMATION);
	return;
	//������֤
	if(m_pMeUserData->lLoveliness==0)
	{
		CString strMessage;
		strMessage.Format(TEXT("��������ֵΪ0,���ܽ��жһ�����!"));
		ShowInformationEx(strMessage,0 ,MB_ICONINFORMATION,TEXT("ϵͳ��Ϣ")) ;

		__super::OnOK();
		return;
	}
	else if ( m_lExchangeCharmValue <= 0 || m_lExchangeCharmValue > DWORD(m_pMeUserData->lLoveliness))
	{
		CString strMessage;
		strMessage.Format(TEXT("�����������ֵ������1��%ld֮��"), m_pMeUserData->lLoveliness);
		ShowInformationEx(strMessage,0 ,MB_ICONINFORMATION,TEXT("ϵͳ��Ϣ")) ;

		GetDlgItem(IDC_EXCHANGE_CHARM_VALUE)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EXCHANGE_CHARM_VALUE))->SetSel(0,-1);
		return;
	}

	//������Ϣ
	CMD_GF_ExchangeCharm ExchangeCharmValue;
	ZeroMemory(&ExchangeCharmValue, sizeof(ExchangeCharmValue));
	ExchangeCharmValue.cbSendLocation=(m_pIClientKernel!=NULL)?LOCATION_GAME_ROOM:LOCATION_PLAZA_ROOM;
	ExchangeCharmValue.lLoveliness = m_lExchangeCharmValue ;
	ExchangeCharmValue.lGoldValue = m_lExchangeCharmValue * CHARM_EXCHANGE_RATE;

	SendData(MDM_GF_PRESENT, SUB_GF_EXCHANGE_CHARM, &ExchangeCharmValue, sizeof(ExchangeCharmValue));

	return;
}

//��ʼ������
BOOL CCharmValueExchange::OnInitDialog()
{
	__super::OnInitDialog();

	UpdateData(FALSE);
	SetWindowText(TEXT("�����һ�"));
	//������ֵ
	CString strValue;
	strValue.Format(TEXT("%ld"),m_lExchangeCharmValue);
	GetDlgItem(IDC_EXCHANGE_CHARM_VALUE)->SetWindowText(strValue);
	GetDlgItem(IDC_EXCHANGE_CHARM_VALUE)->SetFocus();
	//��ʱ����
	SetTimer(IDI_CHARMVALUE_UPDATE_VIEW,TIME_CHARMVALUE_UPDATE_VIEW,NULL);

	return TRUE;
}

//���½���
void CCharmValueExchange::UpdateView()
{
	UpdateData(TRUE);
	//�һ���Ϣ
	if(m_pMeUserData!=NULL)
	{
		m_lBankGoldValue = m_pMeUserData->lInsureScore;
		m_lLoveliness = ((m_pMeUserData->lLoveliness<0)?0:m_pMeUserData->lLoveliness);
	}
	//������Ϣ
	m_strExChangeValue.Format(TEXT("ת�����ʣ�1���� = %d��Ϸ��"), CHARM_EXCHANGE_RATE);
	UpdateData(FALSE);
}

//������Ϣ
BOOL CCharmValueExchange::PreTranslateMessage(MSG* pMsg)
{
	//������ĸ
	if(GetFocus()==GetDlgItem(IDC_EXCHANGE_CHARM_VALUE) && pMsg->message==WM_CHAR)
	{
		BYTE bMesValue = (BYTE)(pMsg->wParam);
		BYTE bTemp = bMesValue-'0';
		if((bTemp<0 || bTemp>9) && bMesValue!=VK_BACK) return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//ʱ����Ϣ
void CCharmValueExchange::OnTimer(UINT nIDEvent)
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
void CCharmValueExchange::OnEnChangeExchangeCharmValue()
{
	if(m_pMeUserData==NULL)return ;

	CString strCount;
	GetDlgItem(IDC_EXCHANGE_CHARM_VALUE)->GetWindowText(strCount);
	m_lExchangeCharmValue=_tstol(strCount);

	return ;
}

//������Ϣ
void CCharmValueExchange::SetSendInfo(IClientKernel *pClientKernel,ITCPSocket *pClientSocket,tagUserData *pUserData)
{
	ASSERT(pUserData!=NULL);
	ASSERT((pClientKernel==NULL && pClientSocket!=NULL)||(pClientKernel!=NULL && pClientSocket==NULL));

	//������Ϣ
	m_pIClientKernel = pClientKernel;
	m_pClientSocket= pClientSocket;
	m_pMeUserData = pUserData;
	m_lExchangeCharmValue = m_pMeUserData->lLoveliness;

	return;
}

//������Ϣ
void CCharmValueExchange::SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	ASSERT((m_pIClientKernel==NULL && m_pClientSocket!=NULL)||(m_pIClientKernel!=NULL && m_pClientSocket==NULL));

	//������Ϣ
	if(m_pClientSocket!=NULL)m_pClientSocket->SendData(wMainCmdID, wSubCmdID, pBuffer, wDataSize);
	else m_pIClientKernel->SendSocketData(wMainCmdID, wSubCmdID, pBuffer, wDataSize);

	return ;
}

//////////////////////////////////////////////////////////////////////////

//�һ�����
extern "C" PROPERTY_MODULE_CLASS VOID __cdecl ShowCharmValueExchangeDlg(IClientKernel *pIClientKernel,ITCPSocket *pClientSocket,tagUserData *pUserData)
{
	//�һ�����
	CCharmValueExchange CharmValueExchangeDlg;

	//������Ϣ
	CharmValueExchangeDlg.SetSendInfo(pIClientKernel,pClientSocket,pUserData);
	CharmValueExchangeDlg.DoModal();

	return ;
}

//////////////////////////////////////////////////////////////////////////
