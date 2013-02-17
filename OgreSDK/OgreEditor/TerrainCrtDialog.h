#pragma once

#include "resource.h"
#include "afxwin.h"

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-17
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CTerrainCrtDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerrainCrtDialog)

public:
	CTerrainCrtDialog(CWnd* pParent = NULL);
	virtual ~CTerrainCrtDialog();

	enum { IDD = IDD_DIALOG_CRTTERRAIN };

	virtual BOOL	OnInitDialog();
protected:
	virtual void	DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnBnClickedOk();
	afx_msg void	OnBnClickedCancel();
	
	CComboBox		m_TerrainSize;
};
