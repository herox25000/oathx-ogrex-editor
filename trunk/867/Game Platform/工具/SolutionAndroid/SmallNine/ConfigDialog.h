#pragma once

class CConfigDialog : public CDialog
{
	DECLARE_DYNAMIC(CConfigDialog)

public:
	CConfigDialog(CWnd* pParent = NULL); 
	virtual ~CConfigDialog();

	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};
