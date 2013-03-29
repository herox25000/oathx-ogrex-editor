#pragma once
#include "afxcmn.h"


class CRobotDialog : public CDialog
{
	DECLARE_DYNAMIC(CRobotDialog)

public:
	CRobotDialog(CWnd* pParent = NULL);
	virtual ~CRobotDialog();

	enum { IDD = IDD_DIALOG_ROBOT };
	DWORD			m_dwGameID;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
};
