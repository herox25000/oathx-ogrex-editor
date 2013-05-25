#pragma once

#include "DefaultResourceListBox.h"

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-24
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CResourceView : public CDockablePane
{
	DECLARE_DYNAMIC(CResourceView)

public:
	enum {
		ID_TAB_RESOUCEVIEW	= 14,
		ID_TAB_DEFAULT		= 15,
	};

	/**
	 *
	 * \return 
	 */
	CResourceView();

	/**
	 *
	 * \return 
	 */
	virtual ~CResourceView();

	/**
	 *
	 */
	void						AdjustLayout();
protected:
	CTabCtrl					m_TabCtrl;
	CDefaultResourceListBox		m_DefaultResourceListBox;
protected:
	DECLARE_MESSAGE_MAP()

	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int					OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void				OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 */
	afx_msg void				OnPaint();

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void				OnSetFocus(CWnd* pOldWnd);

	/**
	 *
	 * \param pNMHDR 
	 * \param pResult 
	 */
	afx_msg void				OnTabPageSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
};


