#pragma once

#include "ImageListBox.h"

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
class CDefaultResourceListBox : public CImageListBox
{
	DECLARE_DYNAMIC(CDefaultResourceListBox)

public:
	/**
	 *
	 * \return 
	 */
	CDefaultResourceListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CDefaultResourceListBox();
	
protected:
	DECLARE_MESSAGE_MAP()

	CString			m_oldDecalName;
	CImageList*		m_pDragImage;
	int				m_nDragItem;
	BOOL			m_bDragging;
	HTREEITEM		m_hDropItem;
public:
	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
};


