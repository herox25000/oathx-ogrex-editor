#pragma once

#include "afxcmn.h"
#include "ConfigDialog.h"
#include "OxAndroid.h"
#include "AndroidManager.h"
#include "BankerDialog.h"

class OxDlg : public CDialog
{

public:
	OxDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SMALLNINE_DIALOG };

public:
	void					SaveScore(INT64 nScore);
	void					GetScore(INT64 nScore);
protected:
	HICON					m_hIcon;
	CListCtrl				m_ListView;
	CRichEditTrace			m_AndroidLog;
	CConfigDialog			m_ConfigDlg;
	double					m_fLostTime;
	int						m_nSelectItem;
	CBankerDialog			m_BankerDialog;

	O2::AndroidManager*		m_pManager;
	O2::OxFactory*			m_pFactory;
protected:
	virtual BOOL			OnInitDialog();
	virtual void			DoDataExchange(CDataExchange* pDX);	
	virtual	BOOL			OnUpdateListView();
	virtual DWORD			GetUserID();
protected:
	afx_msg void			OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void			OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void			OnBnClickedConfig();
	afx_msg void			OnBnClickedOk();
	afx_msg void			OnTimer(UINT nIDEvent);
	afx_msg void			OnBnClickedCancel();
	afx_msg void			OnDestroy();
	afx_msg void			OnBnClickedUpdate();
	afx_msg void			OnNMRclickListUserView(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void			OnOffline();
	afx_msg void			OnParticulars();
	afx_msg void			OnSaveScore();
	afx_msg void			OnGetScore();
};
