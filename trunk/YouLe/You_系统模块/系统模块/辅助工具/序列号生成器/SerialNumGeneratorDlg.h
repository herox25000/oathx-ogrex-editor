// SerialNumGeneratorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSerialNumGeneratorDlg �Ի���
class CSerialNumGeneratorDlg : public CDialog
{
// ����
public:
	CSerialNumGeneratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERIALNUMGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_xEdit;
};
