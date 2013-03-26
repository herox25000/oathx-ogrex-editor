#include "stdafx.h"
#include "resource.h"
#include "DlgBank.h"
#include ".\dlgbank.h"

//��ɫ����
#define SELECT_COLOR		RGB(37,56,220)						//ѡ����ɫ
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTabCtrlBank, CTabCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CTabCtrlBank::CTabCtrlBank()
{

}

//��������
CTabCtrlBank::~CTabCtrlBank()
{
}

//�ػ���Ϣ
void CTabCtrlBank::OnPaint()
{
	//��������
	CPaintDC dc(this);
	CSkinWndAttribute * pSkinAttribute=CSkinDialog::GetSkinAttribute();

	//�滭����
	CRect ClipRect,ClientRect;
	dc.GetClipBox(&ClipRect);
	dc.FillSolidRect(&ClipRect,pSkinAttribute->m_crBackGround);

	//���� DC
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(pSkinAttribute->GetDefaultFont());

	//�滭�߿�
	GetClientRect(&ClientRect);
	ClientRect.top+=18;
	dc.Draw3dRect(&ClientRect,pSkinAttribute->m_crInsideBorder,pSkinAttribute->m_crInsideBorder);

	//��ȡ��Ϣ
	TCITEM ItemInfo;
	TCHAR szBuffer[100];
	memset(&ItemInfo,0,sizeof(ItemInfo));
	ItemInfo.mask=TCIF_TEXT|TCIF_IMAGE;
	ItemInfo.pszText=szBuffer;
	ItemInfo.cchTextMax=sizeof(szBuffer);

	//�滭��ť
	CRect rcItem;
	int iCursel=GetCurSel();
	CPen LinePen(PS_SOLID,1,pSkinAttribute->m_crInsideBorder);
	CPen * pOldPen=dc.SelectObject(&LinePen);
	for (int i=0;i<GetItemCount();i++)
	{
		GetItem(i,&ItemInfo);
		GetItemRect(i,&rcItem);
		dc.FillSolidRect(&rcItem,pSkinAttribute->m_crBackGround);
		dc.MoveTo(rcItem.left,rcItem.bottom-1);
		dc.LineTo(rcItem.left,rcItem.top+2);
		dc.LineTo(rcItem.left+2,rcItem.top);
		dc.LineTo(rcItem.right-2,rcItem.top);
		dc.LineTo(rcItem.right,rcItem.top+2);
		dc.LineTo(rcItem.right,rcItem.bottom-1);

		if (iCursel!=i)
		{
			rcItem.top+=2;
			dc.MoveTo(rcItem.left,rcItem.bottom-1);
			dc.LineTo(rcItem.right,rcItem.bottom-1);
			dc.SetTextColor(pSkinAttribute->m_crControlTXColor);
			DrawText(dc,szBuffer,lstrlen(szBuffer),&rcItem,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
		}
		else 
		{
			rcItem.top+=3;
			dc.SetTextColor(SELECT_COLOR);
			DrawText(dc,szBuffer,lstrlen(szBuffer),&rcItem,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
		}
	}

	//������Դ
	dc.SelectObject(pOldPen);
	LinePen.DeleteObject();
}


//////////////////////////////////////////////////////////////////////////
#define BANK_DLG_SAVE	0
#define BANK_DLG_GET	1
#define BANK_DLG_PTN	2

//////////////////////////////////////////////////////////////////////////
DlgBank::DlgBank() : CSkinDialogEx(IDD_BANK_DIALOG)
{
	m_wOpt = OPT_SAVE;
}

DlgBank::~DlgBank()
{
}

void DlgBank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB_BANK,		m_TabBank);
	DDX_Control(pDX, IDC_BACNK_BTNOK,	m_btOK);
	DDX_Control(pDX, IDC_BANK_BTNALL,	m_btAll);
}

BEGIN_MESSAGE_MAP(DlgBank, CSkinDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BANK, OnTcnSelchange)
	ON_BN_CLICKED(IDC_BACNK_BTNOK, OnButtonOK)
	ON_BN_CLICKED(IDC_BANK_BTNALL, OnButtonAll)
	ON_EN_CHANGE(IDC_BANK_PLYNAME, OnEnUserIDChange)
END_MESSAGE_MAP()

//��ʼ������
BOOL DlgBank::OnInitDialog()
{
	__super::OnInitDialog();

	//�����ǩ
	m_TabBank.InsertItem(BANK_DLG_SAVE,TEXT("��Ǯ"));
	m_TabBank.InsertItem(BANK_DLG_GET,TEXT("ȡǮ"));
	m_TabBank.InsertItem(BANK_DLG_PTN,TEXT("����"));
	m_TabBank.SetCurSel(BANK_DLG_SAVE);
	OnTcnSelchange(NULL, NULL);
	return TRUE; 
}

//���͸ı�
void DlgBank::OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabBank.GetCurSel())
	{
	case BANK_DLG_SAVE:
		{
			m_TabBank.SetCurSel(BANK_DLG_SAVE);

			SetDlgItemText(IDC_BANK_TEXT,TEXT("������Ŀ��"));

			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

			SetOptType(OPT_SAVE);
		}
		break;
	case BANK_DLG_GET:
		{
			m_TabBank.SetCurSel(BANK_DLG_GET);

			SetDlgItemText(IDC_BANK_TEXT,TEXT("ȡ����Ŀ��"));

			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

			SetOptType(OPT_GET);
		}
		break;
	case BANK_DLG_PTN:
		{
			m_TabBank.SetCurSel(BANK_DLG_PTN);

			SetDlgItemText(IDC_BANK_TEXT,TEXT("������Ŀ��"));

			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	
			SetOptType(OPT_PTN);
		}
		break;
	}
}

// ���ò�������
WORD DlgBank::GetOptType() const
{
	return m_wOpt;
}

// ��ȡ��������
void DlgBank::SetOptType(WORD wType)
{
	m_wOpt = wType;
}

// ȷ������
void DlgBank::OnButtonOK()
{
	AfxMessageBox("ȷ��");
}

// ȫ��
void DlgBank::OnButtonAll()
{

}

// �û�ID����ı�
void DlgBank::OnEnUserIDChange()
{
	CString	buffer;
	GetDlgItemText(IDC_BANK_PLYNAME, buffer);

	if (buffer.GetLength() >= 6)
	{
		DWORD dwUserID = atol(buffer.GetBuffer());
	}
}
