#pragma once

#include "resource.h"
#include "afxwin.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class CTerrainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainDialog)

public:
	CTerrainDialog(CWnd* pParent = NULL);
	virtual ~CTerrainDialog();

	enum { IDD = IDD_DIALOG_TR};

	CComboBox		m_wTrBox;
protected:
	virtual void	DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL	OnInitDialog();
	
	afx_msg void	OnBnClickedOk();
	afx_msg void	OnBnClickedCancel();
};
