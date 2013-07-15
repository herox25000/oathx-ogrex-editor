// AiToolDlg.h : ͷ�ļ�
//

#pragma once
#include "GameInterface.h"
#include "define.h"
#include "afxwin.h"

// CAiToolDlg �Ի���
class CAiToolDlg : public CDialog
{
// ����
public:
	CAiToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AITOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	HANDLE			m_hTimerThreadHandle;		//�߳̾��
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
