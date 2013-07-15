// UpdateBuilderDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CUpdateBuilderDlg dialog
class CUpdateBuilderDlg : public CDialog
{
	// Implementation
protected:
	HICON		m_hIcon;
	CListCtrl	m_FileListCtrl;

// Construction
public:
	CUpdateBuilderDlg(CWnd* pParent = NULL);

// Dialog Data
	enum { IDD = IDD_UPGRADEBUILDER_DIALOG };

protected:
	//��ؼ�
	virtual void DoDataExchange(CDataExchange* pDX);
	//��ʼ��
	virtual BOOL OnInitDialog();

	//���ֺ���
protected:
	//�ļ��ߴ�
	ULONG GetFileSize(LPCTSTR pszFileName);
	//�Ƿ����
	BOOL FindExist(LPCTSTR pszFileName);
	//������Ŀ
	BOOL SaveToXml(LPCTSTR pszFilePath);
	//�ļ��汾
	CString GetFileVersion(LPCTSTR pszFileName);
	//�����ļ�
	BOOL InsertFileItem(LPCTSTR pszFileName);
	//�����ļ�
	BOOL UpdateFileItem(int nItem);

	//��Ϣ����
protected:
	//������Ϣ
	afx_msg void OnPaint();
	//��ѯͼ��
	afx_msg HCURSOR OnQueryDragIcon();
	//�ļ��Ϸ�
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//װ���ļ�
	afx_msg void OnBnClickedLoadFiles();
	//�Ƴ��ļ�
	afx_msg void OnBnClickedRemoveFile();
	//������Ŀ
	afx_msg void OnBnClickedSaveItem();
	//װ����Ŀ
	afx_msg void OnBnClickedLoadItem();
	//������Ŀ
	afx_msg void OnBnClickedUpdateItem();
	
	DECLARE_MESSAGE_MAP()
};
