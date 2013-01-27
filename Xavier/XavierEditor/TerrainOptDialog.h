#pragma once

#include "resource.h"

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-27
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CTerrainOptDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerrainOptDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CTerrainOptDialog(CWnd* pParent = NULL);
	/**
	 *
	 * \return 
	 */
	virtual ~CTerrainOptDialog();

	enum { IDD = IDD_TERRAIN_OPTDIALOG };

protected:
	virtual void	DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 */
	afx_msg void	OnBnClickedRadioSplat();

	/**
	 *
	 */
	afx_msg void	OnBnClickedRadioDeform();
};
