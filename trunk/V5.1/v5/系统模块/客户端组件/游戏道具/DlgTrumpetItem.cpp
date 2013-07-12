#include "Stdafx.h"
#include "resource.h"
#include "DlgTrumpetItem.h"
#include "GamePropertyManager.h"

//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgTrumpetItem, CSkinDialog)
	ON_BN_CLICKED(IDC_EXPRESSION, OnBnClickedExpression)
	ON_BN_CLICKED(IDC_COLOR_SET, OnBnClickedColorSet)
	ON_BN_CLICKED(IDC_RADIO_TRUMPET, OnBnClickedTrumpet)
	ON_BN_CLICKED(IDC_RADIO_TYPHON, OnBnClickedTyphon)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////

//���캯��
CDlgTrumpetItem::CDlgTrumpetItem() : CSkinDialog(IDD_DLG_TRUMPET)
{
	//���ñ���
	m_crChatTX = RGB(0,0,0);
	m_wRadioSelected=0;
   
	//�ӿڱ���
	m_pGameTrumpetSink=NULL;
	m_pIClientUserItem=NULL;

	//�ؼ�����
	m_pExpressionControl=NULL;
}

//��������
CDlgTrumpetItem::~CDlgTrumpetItem()
{
	//���ٴ���
	if(m_pExpressionControl && IsWindow(m_pExpressionControl->m_hWnd)) m_pExpressionControl->DestroyWindow();

	//ɾ������
	SafeDelete(m_pExpressionControl);
}

//�ؼ���
void CDlgTrumpetItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EXPRESSION, m_btExpression);
	DDX_Control(pDX, IDC_COLOR_SET, m_btColorSet);
	DDX_Control(pDX, IDC_InputChat, m_InputChat);
	DDX_Control(pDX, IDC_EXPRESSION, m_btExpression);
	DDX_Control(pDX, IDC_COLOR_SET, m_btColorSet);

	DDX_Text(pDX, IDC_InputChat, m_strInuptChat);
	DDV_MaxChars(pDX, m_strInuptChat, TRUMPET_MAX_CHAR);
	DDX_Text(pDX, IDC_PROPERTY_INFO, m_strPropertyInfo);

	return;
}

//��������
void  CDlgTrumpetItem::UpdateControlSurface()
{
	//�����ж�
	if(m_pIClientUserItem==NULL) return;

	//���߹���
	CGamePropertyManager * pGamePropertyManager = CGamePropertyManager::GetInstance();

	//��ʽ�ַ�
	CString strTitle ;
	if(((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->GetCheck()==BST_CHECKED)
	{
		//��ȡ����
		CGamePropertyItem * pPropertyItem = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TRUMPET); 
		if(pPropertyItem==NULL) return;
		tagPropertyInfo * pPropertyInfo = pPropertyItem->GetPropertyInfo();

		//����۸�
		DOUBLE lPrice=(DOUBLE)pPropertyInfo->lPropertyGold;
		if(m_pIClientUserItem->GetMemberOrder()>0) lPrice=lPrice*pPropertyInfo->wDiscount/100;

		//������Ŀ
		TCHAR szBuyCountInfo[32]=TEXT("");
		DWORD dwCanBuyCount= __max((DWORD)(m_pIClientUserItem->GetUserInsure()/lPrice),0);	

		//��������
		strTitle.Format(TEXT("���ܹ����С������ĿΪ[ %d ] ��"), dwCanBuyCount);       
	}
	else
	{
		//��ȡ����
		CGamePropertyItem * pPropertyItem = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TYPHON); 
		if(pPropertyItem==NULL) return;
		tagPropertyInfo * pPropertyInfo = pPropertyItem->GetPropertyInfo();

		//����۸�
		DOUBLE lPrice=(DOUBLE)pPropertyInfo->lPropertyGold;
		if(m_pIClientUserItem->GetMemberOrder()>0) lPrice=lPrice*pPropertyInfo->wDiscount/100;

		//������Ŀ
		TCHAR szBuyCountInfo[32]=TEXT("");
		DWORD dwCanBuyCount= __max((DWORD)(m_pIClientUserItem->GetUserInsure()/lPrice),0);	

		//��������
		strTitle.Format(TEXT("���ܹ���Ĵ�������ĿΪ[ %d ] ��"), dwCanBuyCount);		
	}

	//���ñ���
	SetWindowText(strTitle);
}

//��ȡ����
void CDlgTrumpetItem::GetTrumpetContent(LPTSTR pszTrumpetContent)
{
	//�����ж�
	if(pszTrumpetContent==NULL) return;

	//��������
	CopyMemory(pszTrumpetContent,m_strInuptChat,sizeof(TCHAR)*TRUMPET_MAX_CHAR);
}

//��ʼ���
BOOL CDlgTrumpetItem::OnInitDialog()
{
	CSkinDialog::OnInitDialog();	

	//������Դ
	m_btExpression.SetButtonImage(IDB_BT_EXPRESSION,GetModuleHandle(GAME_PROPERTY_DLL_NAME),true,false);
	m_btColorSet.SetButtonImage(IDB_BT_COLOR_SET,GetModuleHandle(GAME_PROPERTY_DLL_NAME),true,false);

	//��������
	m_InputChat.LimitText(TRUMPET_MAX_CHAR);
	
	//Ĭ������
	//((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->SetCheck(TRUE);
	//OnBnClickedTrumpet();	

	//���½���
	//UpdateControlSurface();

	return TRUE;
}


//��ɫ��ť
void CDlgTrumpetItem::OnBnClickedColorSet()
{
	//������ɫ
	CColorDialog ColorDialog(m_crChatTX,CC_FULLOPEN);
	
	if (ColorDialog.DoModal()==IDOK)
	{
		m_crChatTX=ColorDialog.GetColor();

		//���ý���
		m_InputChat.SetFocus();
	}

	return;
}

//���鰴ť
void CDlgTrumpetItem::OnBnClickedExpression()
{
	//�����ؼ�
	if (m_pExpressionControl==NULL)
	{
		m_pExpressionControl = new CExpressionControl;
	}

	//�ƶ�����
	CRect rcButton;
	m_btExpression.GetWindowRect(&rcButton);

	//��ʾ����
	m_pExpressionControl->ShowExpression(this,rcButton.left,rcButton.top,this);
	m_pExpressionControl->SetFocus();

	return;
}

//���Ȱ�ť
void CDlgTrumpetItem::OnBnClickedTrumpet()
{
	//���߹���
	CGamePropertyManager * pGamePropertyManager = CGamePropertyManager::GetInstance();

	//��ȡ����
	CGamePropertyItem * pPropertyItem = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TRUMPET); 
	if(pPropertyItem==NULL) return;
	tagPropertyInfo * pPropertyInfo = pPropertyItem->GetPropertyInfo();

	m_strPropertyInfo.Format(TEXT("С����%I64d��Ϸ��һ����ÿ����Ϣ���ó���%d���ַ�����Ϣ���ڷ����ڵ������������Ŀ�ķ�ʽ��ʾ��"),	pPropertyInfo->lPropertyGold,TRUMPET_MAX_CHAR);	

	//��������
	UpdateData(FALSE);

	//���¿ؼ�
	UpdateControlSurface();
}

//���Ȱ�ť
void CDlgTrumpetItem::OnBnClickedTyphon()
{
	//���߹���
	CGamePropertyManager * pGamePropertyManager = CGamePropertyManager::GetInstance();

	//��ȡ����
	CGamePropertyItem * pPropertyItem = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TYPHON); 
	if(pPropertyItem==NULL) return;
	tagPropertyInfo * pPropertyInfo = pPropertyItem->GetPropertyInfo();

	m_strPropertyInfo.Format(TEXT("������%I64d��Ϸ��һ����ÿ����Ϣ���ó���%d���ַ�����Ϣ���ڷ����ڵ������������Ŀ�ķ�ʽ��ʾ��"),	pPropertyInfo->lPropertyGold,TRUMPET_MAX_CHAR);

	//��������
	UpdateData(FALSE);

	//���¿ؼ�
	UpdateControlSurface();
}

//ѡ���¼�
VOID CDlgTrumpetItem::OnExpressionSelect(CExpression * pExpression, tagExpressionInfo * pExpressionInfo)
{
	if (pExpressionInfo!=NULL)
	{
		CString strChatMsg;
		m_InputChat.GetWindowText(strChatMsg);
		strChatMsg+="/";
		strChatMsg+=pExpressionInfo->szExpression[1];
		m_InputChat.SetWindowText(strChatMsg);
		m_InputChat.SetFocus();
		m_InputChat.SetSel(strChatMsg.GetLength(),strChatMsg.GetLength());
	}
}

//���ýӿ�
bool CDlgTrumpetItem::SetGameTrumpetSink(IUnknownEx * pIUnknownEx)
{
	//���ýӿ�
	if (pIUnknownEx!=NULL)
	{
		//��ѯ�ӿ�
		ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IGamePropertyUseSink)!=NULL);
		m_pGameTrumpetSink=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IGamePropertyUseSink);

		//�ɹ��ж�
		if (m_pGameTrumpetSink==NULL) return false;
	}
	else m_pGameTrumpetSink=NULL;

	return true;
}

//��ʾ����
void CDlgTrumpetItem::ShowTrumpetWindow(CWnd * pParentWnd,IClientUserItem  * pIClientUserItem)
{
	//Ч��״̬
	ASSERT(pIClientUserItem!=NULL);
	if (pIClientUserItem==NULL) return;

	//״̬�ж�
	if(m_hWnd!=NULL && IsWindowVisible()==TRUE) return;

	//��鴰��
	if(m_hWnd==NULL) 
	{
		//���ýӿ�
		m_pIClientUserItem = pIClientUserItem;

		//��������
		AfxSetResourceHandle(GetModuleHandle(GAME_PROPERTY_DLL_NAME));
		Create(IDD_DLG_TRUMPET,pParentWnd);
		AfxSetResourceHandle(GetModuleHandle(NULL));		
	}

	//��ȡλ��
	CRect rcParentRect(0,0,0,0);
	pParentWnd->GetWindowRect(&rcParentRect);
	
	//��ȡ����
	CRect rcWindowRect(0,0,0,0);
	GetWindowRect(&rcWindowRect);

	//����λ��
	INT nXPos = rcParentRect.left+(rcParentRect.Width()-rcWindowRect.Width())/2;
	INT nYPos = rcParentRect.top+(rcParentRect.Height()-rcWindowRect.Height())/2;
	SetWindowPos(&CWnd::wndTopMost,nXPos,nYPos,rcWindowRect.Width(),rcWindowRect.Height(),SWP_SHOWWINDOW|SWP_NOZORDER);

	//��������
	CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();
	CGamePropertyItem * pGamePropertyTrumpet = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TRUMPET);
	CGamePropertyItem * pGamePropertyTyphon  = pGamePropertyManager->GetPropertyItem(PROPERTY_ID_TYPHON);

	//Ĭ������
	if(pGamePropertyTrumpet!=NULL && pGamePropertyTyphon==NULL)
	{
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->EnableWindow();
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->EnableWindow(FALSE);
		OnBnClickedTrumpet();
	}

	//Ĭ������
	if(pGamePropertyTrumpet==NULL && pGamePropertyTyphon!=NULL)
	{
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->EnableWindow();
		OnBnClickedTyphon();
	}

	//Ĭ������
	if(pGamePropertyTrumpet!=NULL && pGamePropertyTyphon!=NULL)
	{
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->EnableWindow();
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_TYPHON))->EnableWindow();
		OnBnClickedTrumpet();
	}

	//���ñ���
	m_strInuptChat=TEXT("");
	UpdateData(FALSE);

	//���½���
	UpdateControlSurface();
}

//ȷ����Ϣ
void CDlgTrumpetItem::OnBnClickedOk()
{
	//��ȡ����
	WORD wPropertyIndex = ((CButton*)GetDlgItem(IDC_RADIO_TRUMPET))->GetCheck()==BST_CHECKED?PROPERTY_ID_TRUMPET:PROPERTY_ID_TYPHON;

	//��ȡ��Ϣ
	m_InputChat.GetWindowText(m_strInuptChat);
	if ( m_strInuptChat.IsEmpty() )
	{
		CInformation Information2(this);
		Information2.ShowMessageBox(TEXT("�������ݲ���Ϊ�գ�"),MB_ICONWARNING);
		return ;
	}

	if ( TRUMPET_MAX_CHAR < m_strInuptChat.GetLength() )
	{ 
		CString strMsg;
		strMsg.Format(TEXT("�����������Ϊ%d���ַ���"), TRUMPET_MAX_CHAR);

		CInformation Information2(this);
		Information2.ShowMessageBox(TEXT("�����������Ϊ%d���ַ���"),TRUMPET_MAX_CHAR,MB_ICONWARNING);
		return ;
	}	

	//�ص��ӿ�
	if(m_pGameTrumpetSink!=NULL)  m_pGameTrumpetSink->OnEventUseProperty(wPropertyIndex);

	OnOK();
}

//�ؼ���ɫ
HBRUSH CDlgTrumpetItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CSkinDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if ( nCtlColor == CTLCOLOR_EDIT )
	{
		pDC->SetTextColor(m_crChatTX);
	}
	return hbr;
}


//�滭����
void CDlgTrumpetItem::OnPaint()
{
	CPaintDC dc(this); 

	//�滭�߿�
	CRect rcWindowRect(0,0,0,0);
	m_InputChat.GetWindowRect(&rcWindowRect);

	//��������
	ScreenToClient(&rcWindowRect);
	rcWindowRect.InflateRect(1,1,1,1);

	//���Ʊ߿�
	dc.MoveTo(rcWindowRect.left,rcWindowRect.top);
	dc.LineTo(rcWindowRect.right,rcWindowRect.top);
	dc.MoveTo(rcWindowRect.right,rcWindowRect.top);
	dc.LineTo(rcWindowRect.right,rcWindowRect.bottom);
	dc.MoveTo(rcWindowRect.right,rcWindowRect.bottom);
	dc.LineTo(rcWindowRect.left,rcWindowRect.bottom);
	dc.MoveTo(rcWindowRect.left,rcWindowRect.bottom);
	dc.LineTo(rcWindowRect.left,rcWindowRect.top);

	return;
}

//////////////////////////////////////////////////////////////////////

