// ServerConfigDlg.h : ͷ�ļ�
//

#pragma once

#include "ServerTab.h"


// CServerConfigDlg �Ի���
class CServerConfigDlg : public CDialog
{
// ����
public:
	CServerConfigDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVERCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	enum
	{
		CFG_SMALLNINE,
		CFG_PUKNINE,
		CFG_30MINI,
	};
// ʵ��
protected:
	HICON m_hIcon;
	CServerTab	m_Tab;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnSaveConfig();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSave();
};
