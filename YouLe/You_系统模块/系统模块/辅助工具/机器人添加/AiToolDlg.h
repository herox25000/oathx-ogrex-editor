// AiToolDlg.h : 头文件
//

#pragma once
#include "GameInterface.h"
#include "define.h"
#include "afxwin.h"

// CAiToolDlg 对话框
class CAiToolDlg : public CDialog
{
// 构造
public:
	CAiToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AITOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	bool	ReSelManage();
	DECLARE_MESSAGE_MAP()
private:
	int				m_ConnectCount;
	DWORD			dwIP;
	WORD			wPort;
	DWORD			dwBeginID;
	int             mLogUserNum;
	int				m_OffLineUserNum;
	HANDLE			m_hTimerThreadHandle;		//线程句柄
	CGameLogic						m_GameLogic;	
	CGameInterface m_UserManage[USER_NUM];
public:
	afx_msg void OnBnClickedOk();
private:
	static unsigned __stdcall TimerThread(LPVOID pThreadData);
public:
	DWORD m_EditID;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int m_Table;
	int m_Chair;
	CComboBox m_List;
	int m_EditPort;
	int m_NumPlay;
	BOOL m_IsPlay;
	afx_msg void OnBnClickedButton3();
};
