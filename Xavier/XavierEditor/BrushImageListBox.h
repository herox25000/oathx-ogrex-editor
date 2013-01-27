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
class CBrushImageListBox : public CImageListBox
{
	DECLARE_DYNAMIC(CBrushImageListBox)

public:
	/**
	 *
	 * \return 
	 */
	CBrushImageListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CBrushImageListBox();
	
protected:
	DECLARE_MESSAGE_MAP()

	CString			m_oldBrushName;
public:
	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


