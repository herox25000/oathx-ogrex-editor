#pragma once


// CTransDialog �Ի���

class CTransDialog : public CSkinDialogEx
{
	DECLARE_DYNAMIC(CTransDialog)

public:
	CTransDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTransDialog();
	CListCtrl	m_List1;

// �Ի�������
	enum { IDD = IDD_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
