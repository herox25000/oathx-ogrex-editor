// RobotManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "DB.h"
// CRobotManagerDlg �Ի���
class CRobotManagerDlg : public CDialog
{
// ����
public:
	CRobotManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROBOTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	CDB		m_DB;

	DWORD	m_dwRecordCount;

	CString m_strServer;
	CString m_strDbName;
	CString m_strDbUser;
	CString m_strUserPW;

	typedef void(CRobotManagerDlg::*vPFun)();
	vPFun	FunModifyPsw;
	vPFun   FunModifyName;

	vPFun	FunModifyPswTemp;
	vPFun   FunModifyNameTemp;

	void    KeyError();
	void    ModifyPsw();
	void    ModifyName();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonFace();
	afx_msg void OnBnClickedButtonSex();
	afx_msg void OnBnClickedButtonName();
	afx_msg void OnBnClickedButtonPws();
	afx_msg void OnDestroy();
};
