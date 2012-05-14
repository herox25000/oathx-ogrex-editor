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
* \@date   : 2012-05-14
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CServerFactoryDialog : public CDialog
{
	DECLARE_DYNAMIC(CServerFactoryDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CServerFactoryDialog(CWnd* pParent = NULL);

	/**
	 *
	 * \return 
	 */
	virtual ~CServerFactoryDialog();

	enum { IDD = IDD_DIALOG_SERVER };

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	/**
	 *
	 */
	afx_msg void	OnLbnDblclkListServerFactoryItem();

public:
	/**
	 *
	 * \return 
	 */
	virtual BOOL	OnInitDialog();

	/**
	 *
	 */
	virtual void	UpdateFactory();

public:
	CCheckListBox	m_wFactoryBox;
	
};
