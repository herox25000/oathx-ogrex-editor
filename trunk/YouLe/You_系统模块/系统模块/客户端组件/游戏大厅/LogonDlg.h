#pragma once

class CLogonDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);
	virtual ~CLogonDlg();

	enum { IDD = IDD_LOGON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};
