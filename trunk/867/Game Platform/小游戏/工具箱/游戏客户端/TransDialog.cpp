// TransDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "TransDialog.h"

// CTransDialog 对话框

IMPLEMENT_DYNAMIC(CTransDialog, CDialog)
CTransDialog::CTransDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransDialog::IDD, pParent)
{
}

CTransDialog::~CTransDialog()
{
}

void CTransDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}

BEGIN_MESSAGE_MAP(CTransDialog, CDialog)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CTransDialog 消息处理程序
void CTransDialog::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
}

void CTransDialog::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (m_List1.m_hWnd)
		m_List1.MoveWindow(15, 15, cx-30, cy-30);
}

BOOL CTransDialog::OnInitDialog()
{
	__super::OnInitDialog();

	m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT|
		LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP);

	m_List1.InsertColumn(0, "转出用户名", LVCFMT_LEFT, 160);
	m_List1.InsertColumn(1, "转入用户名", LVCFMT_LEFT, 160);
	m_List1.InsertColumn(2, "转账金额", LVCFMT_LEFT, 130);
	m_List1.InsertColumn(3, "日期时间", LVCFMT_LEFT, 190);

	return TRUE;
}
