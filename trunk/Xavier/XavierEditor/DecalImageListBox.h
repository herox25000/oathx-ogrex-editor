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
class CDecalImageListBox : public CImageListBox
{
	DECLARE_DYNAMIC(CDecalImageListBox)

public:
	/**
	 *
	 * \return 
	 */
	CDecalImageListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CDecalImageListBox();
	
protected:
	DECLARE_MESSAGE_MAP()

	CString			m_oldDecalName;
public:
	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


