// ServerConfigDlg.h : 头文件
//

#pragma once

#include "ServerTab.h"


// CServerConfigDlg 对话框
class CServerConfigDlg : public CDialog
{
// 构造
public:
	CServerConfigDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVERCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	enum
	{
		CFG_SMALLNINE,
		CFG_PUKNINE,
		CFG_30MINI,
	};
// 实现
protected:
	HICON m_hIcon;
	CServerTab	m_Tab;
	// 生成的消息映射函数
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
