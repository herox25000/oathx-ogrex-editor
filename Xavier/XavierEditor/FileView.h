#pragma once

#include "ViewTree.h"

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-22
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CFileViewToolBar : public CMFCToolBar
{
	/**
	 *
	 * \param pTarget 
	 * \param bDisableIfNoHndler 
	 */
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	/**
	 *
	 * \return 
	 */
	virtual BOOL AllowShowOnList() const
	{ 
		return FALSE; 
	}
};

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-22
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CFileView : public CDockablePane
{
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:

	CViewTree			m_wndFileView;
	CImageList			m_FileViewImages;
	CFileViewToolBar	m_wndToolBar;

public:
	virtual ~CFileView();
	/**
	 *
	 */
	virtual	void		UpdateFileView();
protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	/**
	 *
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);
	/**
	 *
	 */
	afx_msg void		OnProperties();
	/**
	 *
	 */
	afx_msg void		OnFileOpen();
	/**
	 *
	 */
	afx_msg void		OnFileOpenWith();
	/**
	 *
	 */
	afx_msg void		OnDummyCompile();
	/**
	 *
	 */
	afx_msg void		OnEditCut();
	/**
	 *
	 */
	afx_msg void		OnEditCopy();
	/**
	 *
	 */
	afx_msg void		OnEditClear();
	/**
	 *
	 */
	afx_msg void		OnPaint();
	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void		OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

