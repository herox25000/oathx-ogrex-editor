#pragma once


// CLogonDlg �Ի���

class CLogonDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogonDlg();

// �Ի�������
	enum { IDD = IDD_LOGON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
