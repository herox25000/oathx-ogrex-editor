#pragma once

#include "UnitListBox.h"

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-05-26
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CUnitView : public CDockablePane
{
	DECLARE_DYNAMIC(CUnitView)

public:
	enum {
		ID_UNIT	= 20, 
	};

	/**
	 *
	 * \return 
	 */
	CUnitView();
	/**
	 *
	 * \return 
	 */
	virtual ~CUnitView();

	/**
	 *
	 */
	void						AdjustLayout();
protected:
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
protected:
	DECLARE_MESSAGE_MAP()

protected:
	CTabCtrl					m_TabCtrl;
	CUnitListBox				m_UnitModule;
};


