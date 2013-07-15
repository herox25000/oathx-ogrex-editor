// AutoUpdateDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SkinProgressCtrl.h"
#include "SkinButton.h"
#include "SkinStatic.h"

// CAutoUpdateDlg dialog
class CAutoUpdateDlg : public CDialog, public IDownloadSink
{
// Implementation
protected:
	HICON					m_hIcon;				//ͼ����
	CString					m_strCurrentFile;		//��ǰ�ļ�
	CSkinProgressCtrl		m_Progress1;			//���ȿؼ�
	CSkinProgressCtrl		m_Progress2;			//���ȿؼ�
	CSkinStatic				m_StatusText;			//״̬�ı�
	CSkinStatic				m_CountText;
	CSkinButton				m_btCancel;				//������ť

public:
	CDownloadMgr			m_DownloadMgr;			//���ع���
	CString					m_strCurrentDir;		//��ǰĿ¼
	ULONG					m_ulCurentLenght;		//��ǰ����
	ULONG					m_ulTotalLength;		//�������

public:
	CDC*					m_pMemDC;
	CBitmap*				m_pOldBitmap;
	CBitmap*				m_pBitmapMem;
	CBitmap					m_bmBack;

	//��׼����
public:
	CAutoUpdateDlg(CWnd* pParent = NULL);
	virtual ~CAutoUpdateDlg();

	//���غ���
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	//�ӿں���
public:
	virtual void OnStatusCallback(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCTSTR pszStatusText);

protected:
	BOOL CheckVersionUpdate(CString& strUpdateURL);
	void BuildBkDC();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg LRESULT OnTransaprentBk( WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
