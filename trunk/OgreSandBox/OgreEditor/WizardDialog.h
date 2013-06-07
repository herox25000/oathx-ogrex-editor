#pragma once

#include "resource.h"

class CWizardDialog : public CDialog
{
	DECLARE_DYNAMIC(CWizardDialog)

public:
	CWizardDialog(CWnd* pParent = NULL); 
	virtual ~CWizardDialog();

	enum { IDD = IDD_DIALOG_WIZARD };

protected:
	CString			m_szPath;
	CString			m_szName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnBnClickedButtonBrowse();
	afx_msg void	OnBnClickedOk();
	afx_msg void	OnBnClickedCancel();
};
