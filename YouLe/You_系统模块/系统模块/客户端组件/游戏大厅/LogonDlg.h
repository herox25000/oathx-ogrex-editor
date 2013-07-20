#pragma once


// CLogonDlg 对话框

class CLogonDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogonDlg();

// 对话框数据
	enum { IDD = IDD_LOGON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
