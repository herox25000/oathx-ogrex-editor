#pragma once


// CServerControl 对话框

class CServerControl : public CDialog
{
	DECLARE_DYNAMIC(CServerControl)

public:
	CServerControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerControl();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERVERCONFIG };

	virtual BOOL OnInitDialog();
public:
	void LoadServerConfig();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedOk();
};
