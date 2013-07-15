// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "myfile\videoclient.h"
#include "afxwin.h"


// CClientDlg �Ի���
class CClientDlg : public CDialog
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	CVideoClient m_VideoClient;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonLogin();
	CComboBox m_ComboBox_Server;
	CComboBox m_ComboBox_Room;
	CComboBox m_ComboBox_Desk;
	CEdit m_Edit_Port;
	CStatic m_Static_Pic1;
	CStatic m_Static_Pic2;
	CStatic m_Static_Pic3;
	CStatic m_Static_Pic4;
	CStatic m_Static_Pic5;
	CStatic m_Static_Pic6;
	CStatic m_Static_Pic7;
	CStatic m_Static_Pic8;
	CStatic m_Static_Pic9;
	CStatic m_Static_Pic10;
	afx_msg void OnBnClickedButtonDisconnect();
	CComboBox m_ComboBox_Pos;
};
