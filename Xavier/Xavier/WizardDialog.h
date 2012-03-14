#pragma once

#include "resource.h"
#include "afxwin.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-03-11
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
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

	enum { IDD = IDD_DIALOG_NEW };

		/**
	 *
	 * \return 
	 */
	virtual CString		GetPath() const {return m_csPath;}

	/**
	 *
	 * \return 
	 */
	virtual CString		GetName() const {return m_csName;}
protected:
	CString				m_typeMask;

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void		DoDataExchange(CDataExchange* pDX);

	/**
	 *
	 * \return 
	 */
	virtual BOOL		OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 */
	afx_msg void		OnBnClickedOk();

	/**
	 *
	 */
	afx_msg void		OnBnClickedCancel();
	
	/**
	 *
	 */
	afx_msg void		OnCbnSelchangeComboScenemanager();

	/**
	 *
	 */
	afx_msg void		OnBnClickedButtonFinddir();

protected:
	CString				m_csName;
	CString				m_csPath;

	CComboBox			m_cbSceneTypeMask;
	
};
