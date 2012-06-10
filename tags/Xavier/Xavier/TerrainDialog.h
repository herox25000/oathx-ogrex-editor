#pragma once

#include "resource.h"


/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-10
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CTerrainDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerrainDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CTerrainDialog(CWnd* pParent = NULL);   // 标准构造函数

	/**
	 *
	 * \return 
	 */
	virtual ~CTerrainDialog();

	enum { IDD = IDD_TERRAIN_DLG };

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

	/**
	 *
	 */
	afx_msg void OnBnClickedCancel();

	/**
	 *
	 * \return 
	 */
	virtual BOOL OnInitDialog();
};
