#pragma once

#include "afxcmn.h"

class CSmallNineDlg : public CDialog
{

public:
	CSmallNineDlg(CWnd* pParent = NULL);


	enum { IDD = IDD_SMALLNINE_DIALOG };

protected:
	virtual void	DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	virtual BOOL	OnInitDialog();
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl		m_AndroidListView;
	CRichEditTrace	m_AndroidLog;
};
