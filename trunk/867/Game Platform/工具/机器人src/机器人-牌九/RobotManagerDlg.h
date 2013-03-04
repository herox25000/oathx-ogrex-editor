// RobotManagerDlg.h : ͷ�ļ�
//

#pragma once

#include "�ƾ�/CPaiJiu.h"
#include "afxcmn.h"
#include "KernelEngineHead.h"

#include <map>

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

	void	ChangeRobot();
	void	Login();
	void	Logout();
	//�����ؼ�
public:
	struct CGame
	{
		CGame(CGameBase *pGame, int nTimes)
		{
			_pGame=pGame;
			_nTimes=nTimes;
		}
		CGameBase	*_pGame;
		int			_nTimes;
	};
	typedef std::vector<CGameBase*> CGameVec;
	typedef std::map<DWORD, CGame> CGameMap;
	CGameVec						m_BaVec;
	IUnknownEx						*m_pIUnknownEx;			 
//	CEventServiceHelper				m_EventService;						//�¼�����
	CTimerEngine					m_TimerEngine;						//��ʱ��
	//CRichEditCtrl					m_RichEditCtrl;
	CGameMap						m_BaMap;

	CString							m_strIP;
	UINT							m_nPort;
	CString							m_strPsw;
	int								m_nGroupID;
	int								m_nStartID;
	int								m_nEndID;

	CRichEditTrace					m_RichEditTrace;					//�¼���¼

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedClean();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedEndServer();
	afx_msg void OnBnClickedButton2();
};
