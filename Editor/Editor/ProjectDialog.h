#pragma once

#include "Resource.h"
#include "afxwin.h"

class CProjectDialog : public CDialog
{
	DECLARE_DYNAMIC(CProjectDialog)

public:
	CProjectDialog(CWnd* pParent = NULL);
	virtual ~CProjectDialog();

	enum { IDD = IDD_DIALOG_TERRAIN };

protected:
	virtual void	DoDataExchange(CDataExchange* pDX);
	virtual BOOL	OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnBnClickedOk();
	afx_msg void	OnBnClickedCancel();
	afx_msg void	OnBnClickedSelectItemDire();

	CComboBox		m_SceneTypeBox;
	
};
