#pragma once

#include "RobotManager.h"
#include "RobotTimer.h"
#include "SmallnineMachine.h"
#include "afxwin.h"
#include "afxcmn.h"

enum
{
	IDT_TIMER_UPDATE		= 1,
	IDT_TIMER_RECONNECT		= 2
};

class CSmallNineDlg : public CDialog
{
public:
	CSmallNineDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SMALLNINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	double				m_fElapsed;
	double				m_fLostTime;
	double				m_fCrateTime;
	CString				m_ipAddress;
	WORD				m_wPort;
	CString				m_md5;
	DWORD				m_dwStartID;
	DWORD				m_dwEndID;
	SBankerConfig		m_AppConfig;
protected:
	HICON				m_hIcon;
	CRichEditTrace		m_RichEditTrace;

protected:
	virtual BOOL		OnInitDialog();
	afx_msg void		OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void		OnTimer(UINT nIDEvent);
	afx_msg void		OnBnClickedOk();
	afx_msg void		OnBnClickedCancel();
	
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit17();
};
