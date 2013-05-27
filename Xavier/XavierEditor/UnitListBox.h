#pragma once

#include "ImageListBox.h"

/**
* \ingroup : asss
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-06
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CUnitListBox : public CImageListBox
{
	DECLARE_DYNAMIC(CUnitListBox)

public:
	/**
	 *
	 * \return 
	 */
	CUnitListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CUnitListBox();
	
	/**
	 *
	 * \param lpszFilePath 
	 * \return 
	 */
	BOOL			Load(LPCTSTR lpszPath, LPCTSTR lpszFilter);
protected:
	DECLARE_MESSAGE_MAP()
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
protected:
	CImageList*		m_pDragImage;
	BOOL			m_bDragging;
	CString			m_szFileName;
};


