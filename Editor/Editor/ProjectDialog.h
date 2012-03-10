#pragma once

#include "Resource.h"
#include "afxwin.h"

/**
* \ingroup : Editor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2011-12-14
*
* \Author  : lp
*
* \Desc    : 编辑器项目对话框
*
* \bug     : 
*
*/
class CProjectDialog : public CDialog
{
	DECLARE_DYNAMIC(CProjectDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CProjectDialog(CWnd* pParent = NULL);

	/**
	 *
	 * \return 
	 */
	virtual ~CProjectDialog();

	enum { IDD = IDD_DIALOG_TERRAIN };

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void	DoDataExchange(CDataExchange* pDX);

	/**
	 *
	 * \return 
	 */
	virtual BOOL	OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 */
	afx_msg void	OnBnClickedOk();

	/**
	 *
	 */
	afx_msg void	OnBnClickedCancel();

	/**
	 *
	 */
	afx_msg void	OnBnClickedSelectItemDire();

protected:
	CComboBox		m_SceneTypeBox;
	
};
