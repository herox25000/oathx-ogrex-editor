#pragma once

#include "ConfigFile.h"

class CConfigDialog : public CDialog
{
	DECLARE_DYNAMIC(CConfigDialog)

public:
	CConfigDialog(CWnd* pParent = NULL); 
	virtual ~CConfigDialog();

	enum { IDD = IDD_DIALOG_CONFIG };

	virtual BOOL OnInitDialog();
	virtual void OnAplyConfig();
	virtual void OnLoadConfig();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLoadconfig();
	afx_msg void OnBnClickedSaveconfig();
};
