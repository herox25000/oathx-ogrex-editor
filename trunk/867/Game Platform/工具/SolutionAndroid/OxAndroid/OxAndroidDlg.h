#pragma once
#include "Ox4.h"
#include "AndroidManager.h"

class COxAndroidDlg : public CDialog
{
public:
	COxAndroidDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_OXANDROID_DIALOG };

	protected:
	virtual void		DoDataExchange(CDataExchange* pDX);

protected:
	double				m_fElapsed;
	double				m_fLostTime;
	O2::Ox4Factory*		m_pOx4Factory;
	O2::AndroidManager*	m_pAndroidManager;
protected:
	HICON				m_hIcon;

	virtual BOOL		OnInitDialog();
	afx_msg void		OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void		OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual void OnCancel();
};
