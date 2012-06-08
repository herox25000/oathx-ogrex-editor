#pragma once

#include "ImageView.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-03-08
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
public:
	/**
	 *
	 * \return 
	 */
	CDecalView();

	/**
	 *
	 */
	void					AdjustLayout();

protected:
	CImageListBox			m_wDecaView;

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CDecalView();

	/**
	 *
	 * \return 
	 */
	virtual	CString			GetHotItemText();
protected:
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

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void			OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};
