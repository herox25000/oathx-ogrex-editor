
#pragma once

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
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CViewTree : public CTreeCtrl
{
public:
	/**
	 *
	 * \return 
	 */
	CViewTree();

protected:
	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \param pResult 
	 * \return 
	 */
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
