#include "stdafx.h"
#include "resource.h"
#include "DlgBank.h"
#include ".\dlgbank.h"

//颜色定义
#define SELECT_COLOR		RGB(37,56,220)						//选择颜色
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTabCtrlBank, CTabCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CTabCtrlBank::CTabCtrlBank()
{

}

//析够函数
CTabCtrlBank::~CTabCtrlBank()
{
}

//重画消息
void CTabCtrlBank::OnPaint()
{
	//变量定义
	CPaintDC dc(this);
	CSkinWndAttribute * pSkinAttribute=CSkinDialog::GetSkinAttribute();

	//绘画背景
	CRect ClipRect,ClientRect;
	dc.GetClipBox(&ClipRect);
	dc.FillSolidRect(&ClipRect,pSkinAttribute->m_crBackGround);

	//设置 DC
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(pSkinAttribute->GetDefaultFont());

	//绘画边框
	GetClientRect(&ClientRect);
	ClientRect.top+=18;
	dc.Draw3dRect(&ClientRect,pSkinAttribute->m_crInsideBorder,pSkinAttribute->m_crInsideBorder);

	//获取信息
	TCITEM ItemInfo;
	TCHAR szBuffer[100];
	memset(&ItemInfo,0,sizeof(ItemInfo));
	ItemInfo.mask=TCIF_TEXT|TCIF_IMAGE;
	ItemInfo.pszText=szBuffer;
	ItemInfo.cchTextMax=sizeof(szBuffer);

	//绘画按钮
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

	//清理资源
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

//初始化函数
BOOL DlgBank::OnInitDialog()
{
	__super::OnInitDialog();

	//加入标签
	m_TabBank.InsertItem(BANK_DLG_SAVE,TEXT("存钱"));
	m_TabBank.InsertItem(BANK_DLG_GET,TEXT("取钱"));
	m_TabBank.InsertItem(BANK_DLG_PTN,TEXT("赠送"));
	m_TabBank.SetCurSel(BANK_DLG_SAVE);
	OnTcnSelchange(NULL, NULL);
	return TRUE; 
}

//类型改变
void DlgBank::OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabBank.GetCurSel())
	{
	case BANK_DLG_SAVE:
		{
			m_TabBank.SetCurSel(BANK_DLG_SAVE);

			SetDlgItemText(IDC_BANK_TEXT,TEXT("存入数目："));

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

			SetDlgItemText(IDC_BANK_TEXT,TEXT("取出数目："));

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

			SetDlgItemText(IDC_BANK_TEXT,TEXT("赠送数目："));

			GetDlgItem(IDC_BANK_PLYNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BANK_PLYNICK)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	
			SetOptType(OPT_PTN);
		}
		break;
	}
}

// 设置操作类型
WORD DlgBank::GetOptType() const
{
	return m_wOpt;
}

// 获取操作类型
void DlgBank::SetOptType(WORD wType)
{
	m_wOpt = wType;
}

// 确定操作
void DlgBank::OnButtonOK()
{
	AfxMessageBox("确定");
}

// 全部
void DlgBank::OnButtonAll()
{

}

// 用户ID输入改变
void DlgBank::OnEnUserIDChange()
{
	CString	buffer;
	GetDlgItemText(IDC_BANK_PLYNAME, buffer);

	if (buffer.GetLength() >= 6)
	{
		DWORD dwUserID = atol(buffer.GetBuffer());
	}
}
