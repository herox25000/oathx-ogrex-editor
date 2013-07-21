#pragma once

class CGamePlazaDlg : public CDialog
{
public:
	CGamePlazaDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_GAMEPLAZA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV Ö§³Ö

protected:
	HICON					m_hIcon;

	virtual BOOL			OnInitDialog();

	afx_msg void			OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
};
