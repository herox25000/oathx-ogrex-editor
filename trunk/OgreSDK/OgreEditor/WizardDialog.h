#pragma once

#include "Resource.h"

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-15
*
* \Author  : lp
*
* \Desc    : 向导对话框
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CWizardDialog : public CDialog
{
	DECLARE_DYNAMIC(CWizardDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CWizardDialog(CWnd* pParent = NULL);
	/**
	 *
	 * \return 
	 */
	virtual ~CWizardDialog();

	enum { IDD = IDD_DIALOG_WIZARD };

protected:
	CString			m_Path;
	CString			m_Name;
	/**
	 *
	 * \param pDX 
	 */
	virtual void	DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 * \return 
	 */
	virtual BOOL	OnInitDialog();

	/**
	 *
	 */
	afx_msg void	OnBnClickedButtonPath();

	/**
	 *
	 */
	afx_msg void	OnBnClickedOk();

	/**
	 *
	 */
	afx_msg void	OnBnClickedCancel();
};
