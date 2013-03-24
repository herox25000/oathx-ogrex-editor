#pragma once


// CTransDialog 对话框

class CTransDialog : public CDialog
{
	DECLARE_DYNAMIC(CTransDialog)

public:
	CTransDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransDialog();
	CListCtrl	m_List1;

// 对话框数据
	enum { IDD = IDD_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
