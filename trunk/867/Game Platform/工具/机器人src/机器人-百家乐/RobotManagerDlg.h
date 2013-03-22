// RobotManagerDlg.h : 头文件
//

#pragma once

#include "百家乐/CBaccarat.h"
#include "afxcmn.h"
#include "KernelEngineHead.h"

#include <map>

// CRobotManagerDlg 对话框
class CRobotManagerDlg : public CDialog
{
// 构造
public:
	CRobotManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROBOTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void	ChangeRobot();
	void	Login();
	void	Logout();
	BOOL	Find(DWORD dwID);
	//其他控件
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
	typedef std::vector<CBaccarat*> CGameVec;
	typedef std::map<DWORD, CGame> CGameMap;
	CGameVec						m_BaVec;
	IUnknownEx						*m_pIUnknownEx;			 
//	CEventServiceHelper				m_EventService;						//事件服务
	CTimerEngine					m_TimerEngine;						//定时器
	//CRichEditCtrl					m_RichEditCtrl;
	CGameMap						m_BaMap;

	CString							m_strIP;
	UINT							m_nPort;
	CString							m_strPsw;
	int								m_nGroupID;
	int								m_nStartID;
	int								m_nEndID;

	int								m_nRoomMaxRobot;

	CRichEditTrace					m_RichEditTrace;					//事件记录

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
