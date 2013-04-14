#pragma once

class CBankerDialog : public CDialog
{
	DECLARE_DYNAMIC(CBankerDialog)

public:
	CBankerDialog(CWnd* pParent = NULL); 
	virtual ~CBankerDialog();

	enum { IDD = IDD_DIALOG_BANKER };

	virtual void SetText(LPCTSTR lpszText);
	virtual void SetType(bool bType);
protected:
	bool		 m_bType;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
