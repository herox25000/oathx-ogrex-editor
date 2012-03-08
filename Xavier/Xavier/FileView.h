#pragma once

#include "ViewTree.h"

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
class CFileViewToolBar : public CMFCToolBar
{
	/**
	 *
	 * \param pTarget
	 * \param bDisableIfNoHndler 
	 */
	virtual void			OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	/**
	 *
	 * \return 
	 */
	virtual BOOL			AllowShowOnList() const
	{
		return FALSE; 
	}
};

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
class CFileView : public CDockablePane
{
public:
	/**
	 *
	 * \return 
	 */
	CFileView();

	/**
	 *
	 */
	void					AdjustLayout();

	/**
	 *
	 */
	void					OnChangeVisualStyle();

protected:

	CViewTree				m_wndFileView;
	CImageList				m_FileViewImages;
	CFileViewToolBar		m_wndToolBar;

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CFileView();

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
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void			OnContextMenu(CWnd* pWnd, CPoint point);

	/**
	 *
	 */
	afx_msg void			OnProperties();

	/**
	 *
	 */
	afx_msg void			OnFileOpen();

	/**
	 *
	 */
	afx_msg void			OnFileOpenWith();

	/**
	 *
	 */
	afx_msg void			OnDummyCompile();

	/**
	 *
	 */
	afx_msg void			OnEditCut();

	/**
	 *
	 */
	afx_msg void			OnEditCopy();

	/**
	 *
	 */
	afx_msg void			OnEditClear();

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

