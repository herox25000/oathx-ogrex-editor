// DeskMagicDlg.h : ͷ�ļ�
//

#pragma once


// CDeskMagicDlg �Ի���
class CDeskMagicDlg : public CDialog
{
// ����
public:
	CDeskMagicDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESKMAGIC_DIALOG };

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
	BOOL LoadFileDat(LPCTSTR szFile);
	BOOL SaveFileDat(LPCTSTR szFile);
	BOOL LoadFileIni(LPCTSTR szFile);
	BOOL SaveFileIni(LPCTSTR szFile);
	BOOL ParseRect(TCHAR* szRect, RECT& rcRect);
	BOOL ParsePoint(TCHAR* szPoint, POINT& ptPoint);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
