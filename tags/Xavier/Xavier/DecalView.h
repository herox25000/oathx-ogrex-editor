#pragma once

#include "ViewTree.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-03
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CDecalView : public CDockablePane
{
	DECLARE_DYNAMIC(CDecalView)

public:
	/**
	 *
	 * \return 
	 */
	CDecalView();

	/**
	 *
	 * \return 
	 */
	virtual ~CDecalView();
	
	CViewTree				m_wImageView;
protected:
	DECLARE_MESSAGE_MAP()
	
	/**
	 *
	 * \return 
	 */
	virtual void			AdjustLayout();
public:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void			OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 */
	afx_msg void			OnPaint();
};


