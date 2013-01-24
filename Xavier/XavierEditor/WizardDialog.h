#pragma once

#include "Resource.h"

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-24
*
* \Author  : lp
*
* \Desc    :
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
	CWizardDialog(CWnd* pParent = NULL);   // 标准构造函数
	/**
	 *
	 * \return 
	 */
	virtual ~CWizardDialog();

	enum { IDD = IDD_DIALOG_WIZARD };

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 */
	afx_msg void OnBnClickedOk();
};
