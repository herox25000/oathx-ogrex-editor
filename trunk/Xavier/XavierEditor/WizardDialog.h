#pragma once

#include "Resource.h"

class CWizardDialog : public CDialog
{
	DECLARE_DYNAMIC(CWizardDialog)

public:
	CWizardDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWizardDialog();

	enum { IDD = IDD_DIALOG_WIZARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
