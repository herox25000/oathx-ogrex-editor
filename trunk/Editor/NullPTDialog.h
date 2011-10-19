#pragma once

#include "resource.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class CNullPTDialog : public CDialog
{
	DECLARE_DYNAMIC(CNullPTDialog)

public:
	CNullPTDialog(CWnd* pParent = NULL);
	virtual ~CNullPTDialog();

	enum { IDD = IDD_NULL_PT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLL();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
