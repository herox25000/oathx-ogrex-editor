#include "StdAfx.h"
#include "Resource.h"
#include "DlgBuyProperty.h"
#include "GamePropertyItem.h"

//////////////////////////////////////////////////////////////////////////////////

//��̬����
CDlgBuyProperty * CDlgBuyProperty::m_pDlgBuyProperty=NULL;				//����ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgBuyProperty, CSkinDialog)
	ON_EN_CHANGE(IDC_PROPERTY_COUNT, OnEnChangePropertyCount)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgBuyProperty::CDlgBuyProperty() : CSkinDialog(IDD_DLG_PROPERTY)
{
	//���ñ���
	m_lCanBuyCount=0;

	//���ñ���
	m_pGamePropertyItem=NULL;
	m_pIGamePropertySink=NULL;

	//���ö���
	ASSERT(m_pDlgBuyProperty==NULL);
	if (m_pDlgBuyProperty==NULL) m_pDlgBuyProperty=this;

	return;
}

//��������
CDlgBuyProperty::~CDlgBuyProperty()
{
	//���ö���
	ASSERT(m_pDlgBuyProperty==this);
	if (m_pDlgBuyProperty==this) m_pDlgBuyProperty=NULL;

	return;
}

//�ؼ���
VOID CDlgBuyProperty::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);

	//�༭�ؼ�
	DDX_Control(pDX, IDC_NICK_NAME, m_edNickName);
	DDX_Control(pDX, IDC_PROPERTY_COUNT, m_edPropertyCount);
}

//��Ϣ����
BOOL CDlgBuyProperty::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��������
BOOL CDlgBuyProperty::OnInitDialog()
{
	__super::OnInitDialog();

	//����״̬
	UpdateCtrlStatus();

	//��������
	m_edNickName.LimitText(LEN_NICKNAME-1);

	//֧����ʽ
	((CButton *)GetDlgItem(IDC_PAY_BY_INSURE))->SetCheck(BST_CHECKED);

	return FALSE;
}

//ȷ������
VOID CDlgBuyProperty::OnOK()
{
	//��ȡ��Ϣ
	CString strNickName;
	GetDlgItemText(IDC_NICK_NAME,strNickName);
	strNickName.TrimLeft();strNickName.TrimRight();

	//��ȡ��Ŀ
	UINT wItemCount=GetDlgItemInt(IDC_PROPERTY_COUNT);

	//�ǳ��ж�
	if (strNickName.IsEmpty()==true)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�û��ǳƲ���ȷ������������"),MB_ICONERROR);

		//���ý���
		m_edNickName.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (wItemCount==0 || wItemCount > m_lCanBuyCount)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("������Ŀ����ȷ������������"),MB_ICONERROR);

		//���ý���
		m_edPropertyCount.SetFocus();

		return;
	}

	//��ȡ��Ϣ
	ASSERT(m_pGamePropertyItem->GetPropertyAttrib()!=NULL);
	tagPropertyAttrib * pPropertyAttrib=m_pGamePropertyItem->GetPropertyAttrib();

	//��ǰ���
	ASSERT(m_pIGamePropertySink!=NULL);
	TCHAR szMessage[128]=TEXT("");
	if(m_pIGamePropertySink->OnEventBuyPropertyPrep(strNickName,pPropertyAttrib->wIndex,szMessage)==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szMessage,MB_ICONERROR);

		return;
	}

	//�¼�֪ͨ	
	if (m_pIGamePropertySink->OnEventBuyProperty(strNickName,wItemCount,pPropertyAttrib->wIndex)==true)
	{
		//�رմ���
		DestroyWindow();
	}

	return;
}

//ȡ����Ϣ
VOID CDlgBuyProperty::OnCancel()
{
	//�رմ���
	DestroyWindow();

	return;
}

//�滭��Ϣ
VOID CDlgBuyProperty::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//���λ��
	INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
	INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
	INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;

	//������Դ
	CPngImage ImagePropertyFrame;
	ImagePropertyFrame.LoadImage(GetModuleHandle(GAME_PROPERTY_DLL_NAME),TEXT("PROPERTY_FRAME"));

	//��ȡ��С
	CSize SizePropertyFrame;
	SizePropertyFrame.SetSize(ImagePropertyFrame.GetWidth(),ImagePropertyFrame.GetHeight());

	//�滭���
	INT nXItemPos=nLBorder+10;
	INT nYItemPos=nTBorder+10;
	ImagePropertyFrame.DrawImage(pDC,nXItemPos-(SizePropertyFrame.cx-PROPERTY_SYMBOL_CX)/2,nYItemPos-(SizePropertyFrame.cy-PROPERTY_SYMBOL_CY)/2);

	//�滭ͼ��
	if (m_pGamePropertyItem!=NULL)
	{
		//��ȡ��Դ
		tagPropertyImage PropertyImage;
		m_pGamePropertyItem->GetImageInfo(PropertyImage);

		//�滭ͼ��
		CPngImage ImageSymbol;
		ImageSymbol.LoadImage(PropertyImage.hResInstance,PropertyImage.pszSymbolID);
		ImageSymbol.DrawImage(pDC,nXItemPos,nYItemPos,PROPERTY_SYMBOL_CX,PROPERTY_SYMBOL_CY,0,0,ImageSymbol.GetWidth(),ImageSymbol.GetHeight());
	}

	return;
}

//����״̬
VOID CDlgBuyProperty::UpdateCtrlStatus()
{
	//Ч�����
	ASSERT(m_pGamePropertyItem!=NULL);
	ASSERT(m_pIGamePropertySink!=NULL);

	//��������
	m_edPropertyCount.SetLimitText(12);

	//��ȡ����
	tagPropertyInfo * pPropertyInfo=m_pGamePropertyItem->GetPropertyInfo();
	tagPropertyAttrib * pPropertyAttrib=m_pGamePropertyItem->GetPropertyAttrib();

	//���ñ�ǩ
	if(pPropertyAttrib->wPropertyType==PT_TYPE_PROPERTY)
	{		
		SetDlgItemText(IDC_STATIC_NAME,TEXT("��������"));
		SetDlgItemText(IDC_STATIC_PRICE,TEXT("���߼۸�"));
	}
	else
	{
		SetDlgItemText(IDC_STATIC_NAME,TEXT("��������"));
		SetDlgItemText(IDC_STATIC_PRICE,TEXT("����۸�"));
	}

	//���߼۸�
	TCHAR szPropertyGold[64]=TEXT("");
	_sntprintf(szPropertyGold,CountArray(szPropertyGold),TEXT("%I64d ��Ϸ��/%s ����Ա�ۿۣ�%ld%%��"),pPropertyInfo->lPropertyGold,pPropertyAttrib->szMeasuringunit,pPropertyInfo->wDiscount);

	//���ñ���
	SetWindowText(pPropertyAttrib->szPropertyName);

	//���߼۸�
	SetDlgItemText(IDC_PROPERTY_GOLD,szPropertyGold);

	//���ߵ�λ
	SetDlgItemText(IDC_STATIC_COUNT,pPropertyAttrib->szMeasuringunit);

	//��������
	SetDlgItemText(IDC_PROPERTY_NAME,pPropertyAttrib->szPropertyName);
	SetDlgItemText(IDC_PROPERTY_DESCRIBE,pPropertyAttrib->szRegulationsInfo);

	//������Ŀ
	if(m_pIGamePropertySink!=NULL)	
	{
		IClientUserItem * pClientUserItem = m_pIGamePropertySink->OnQueryClientUserItem();
		if(pClientUserItem!=NULL)
		{
			//����۸�
			DOUBLE lPrice=(DOUBLE)pPropertyInfo->lPropertyGold;
			if(pClientUserItem->GetMemberOrder()>0) lPrice=lPrice*pPropertyInfo->wDiscount/100;

			//������Ŀ
			TCHAR szBuyCountInfo[32]=TEXT("");
			if(pClientUserItem!=NULL) m_lCanBuyCount=__max((LONGLONG)(pClientUserItem->GetUserInsure()/lPrice),0);	
			_sntprintf(szBuyCountInfo,CountArray(szBuyCountInfo),TEXT("��������ܹ��� %I64d %s��"),m_lCanBuyCount,pPropertyAttrib->szMeasuringunit);
			SetDlgItemText(IDC_MAX_BUYCOUNT,szBuyCountInfo);	

			//��������
			UINT  wItemCount = GetDlgItemInt(IDC_PROPERTY_COUNT);
			
			//��Ŀ�ж�
			if(wItemCount>m_lCanBuyCount) 
			{
				//��Ŀ����
				SetDlgItemInt(IDC_PROPERTY_COUNT,(UINT)m_lCanBuyCount);

				//�������
				((CEdit *)GetDlgItem(IDC_PROPERTY_COUNT))->SetSel(-1);
			}
		}
	}

	return;
}

//��ʾ����
VOID CDlgBuyProperty::ShowBuyPropertyWnd(CGamePropertyItem * pGamePropertyItem, IGamePropertySink * pIGamePropertySink)
{
	//Ч�����
	ASSERT(pGamePropertyItem!=NULL);
	ASSERT(pIGamePropertySink!=NULL);

	//��������
	CDlgBuyProperty * pDlgBuyProperty=m_pDlgBuyProperty;

	//��������
	if (pDlgBuyProperty==NULL)
	{
		try
		{
			pDlgBuyProperty=new CDlgBuyProperty;
		}
		catch (...)
		{
			ASSERT(FALSE);
		}
	}

	//���ñ���
	pDlgBuyProperty->m_pGamePropertyItem=pGamePropertyItem;
	pDlgBuyProperty->m_pIGamePropertySink=pIGamePropertySink;

	//��������
	if (pDlgBuyProperty->m_hWnd==NULL)
	{
		AfxSetResourceHandle(GetModuleHandle(GAME_PROPERTY_DLL_NAME));
		pDlgBuyProperty->Create(IDD_DLG_PROPERTY,AfxGetMainWnd());
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}
	else
	{
		//����״̬
		pDlgBuyProperty->UpdateCtrlStatus();
	}

	//��ʾ����
	pDlgBuyProperty->ShowWindow(SW_SHOW);

	//�����
	pDlgBuyProperty->SetActiveWindow();
	pDlgBuyProperty->SetForegroundWindow();

	return;
}

//�ı��¼�
VOID CDlgBuyProperty::OnEventPerformCommand(WORD wCommandID,VOID * pCmdData)
{
	//�����ж�
	if(m_pDlgBuyProperty==NULL || m_pDlgBuyProperty->m_hWnd==NULL) return;

	//�ֱ���
	if(wCommandID==CMD_CLOSE_WND)
	{
		//�رմ���
		m_pDlgBuyProperty->DestroyWindow();
	}
	else if(wCommandID==CMD_USER_CHANGE)
	{
		//��ȡ����
		IClientUserItem * pIClintUserItem=(IClientUserItem *)pCmdData;

		//�����ж�
		if(pIClintUserItem==NULL) return;

		//�޸��ǳ�
		m_pDlgBuyProperty->SetDlgItemText(IDC_NICK_NAME,pIClintUserItem->GetNickName());
	}
}

//�ı��¼�
void CDlgBuyProperty::OnEnChangePropertyCount()
{
	//��������
	DWORD dwSelPos=((CEdit *)GetDlgItem(IDC_PROPERTY_COUNT))->GetSel();
	CString strCount;
	GetDlgItem(IDC_PROPERTY_COUNT)->GetWindowText(strCount);
	
	//ȥ��ǰ���0
	CString strLeft = strCount.Left(1);
	if(strLeft.Find('0') != -1)
	{
		strCount = strCount.Right(strCount.GetLength() - 1);
		SetDlgItemText(IDC_PROPERTY_COUNT,strCount);
	}

	UINT wItemCount = GetDlgItemInt(IDC_PROPERTY_COUNT);

	//��Ŀ�ж�
	if(wItemCount>m_lCanBuyCount) 
		SetDlgItemInt(IDC_PROPERTY_COUNT,(UINT)m_lCanBuyCount);
	
	//���ù��	 
	((CEdit *)GetDlgItem(IDC_PROPERTY_COUNT))->SetSel(dwSelPos);
	
	return;
}

//////////////////////////////////////////////////////////////////////////////////
