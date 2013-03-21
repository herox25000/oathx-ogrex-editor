#pragma once

#include "RobotManager.h"
#include "RobotTimer.h"
#include "SmallnineMachine.h"
#include "afxwin.h"
#include "afxcmn.h"

enum
{
	IDT_TIMER_UPDATE	= 1,
	IDT_TIMER_CRATE		= 2
};

class CSmallNineDlg : public CDialog
{
public:
	CSmallNineDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SMALLNINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON				m_hIcon;
	double				m_fElapsed;
	double				m_fLostTime;
	double				m_fCrateTime;

	virtual BOOL		OnInitDialog();
	afx_msg void		OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
};
