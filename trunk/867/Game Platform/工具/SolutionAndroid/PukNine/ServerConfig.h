#pragma once


// CServerConfig �Ի���

class CServerConfig : public CDialog
{
	DECLARE_DYNAMIC(CServerConfig)

public:
	CServerConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERVERCONFIG };

	virtual BOOL OnInitDialog();
public:
	void LoadServerConfig();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
