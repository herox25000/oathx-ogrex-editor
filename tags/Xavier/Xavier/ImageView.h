#pragma once

#include "ImageListBox.h"

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
class CImageView : public CImageListBox
{
	DECLARE_DYNAMIC(CImageView)

public:
	/**
	 *
	 * \return 
	 */
	CImageView();

	/**
	 *
	 * \return 
	 */
	virtual ~CImageView();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	 *
	 */
	afx_msg void OnPaint();
};


