#pragma once

#include "Stdafx.h"

// CDlgDismissGame dialog

class CDlgDismissGame : public CSkinDialog
{
	//��������
protected:
	WORD							m_wDismissTable;					//�߳���ʾ

	//���Ʊ���
protected:
	CSkinButton						m_btOK;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

public:
	CDlgDismissGame(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDismissGame();

// Dialog Data
	enum { IDD = IDD_DLG_DISMISSGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_DYNAMIC(CDlgDismissGame)
	DECLARE_MESSAGE_MAP()

public:
	WORD GetDismissTableNum(){return m_wDismissTable;}
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
