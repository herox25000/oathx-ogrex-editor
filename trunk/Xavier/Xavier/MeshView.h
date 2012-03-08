
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
class CMeshToolBar : public CMFCToolBar
{
	/**
	 *
	 * \param pTarget 
	 * \param bDisableIfNoHndler 
	 */
	virtual void			OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
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
class CMeshView : public CDockablePane
{
public:
	/**
	 *
	 * \return 
	 */
	CMeshView();

	/**
	 *
	 * \return 
	 */
	virtual ~CMeshView();

	/**
	 *
	 */
	void					AdjustLayout();

	/**
	 *
	 */
	void					OnChangeVisualStyle();

protected:
	CMeshToolBar			m_wndToolBar;
	CViewTree				m_wndClassView;
	CImageList				m_ClassViewImages;
	UINT					m_nCurrSort;

public:
	/**
	 *
	 * \param pMsg 
	 * \return 
	 */
	virtual BOOL			PreTranslateMessage(MSG* pMsg);

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
	afx_msg void			OnMeshAddMemberFunction();

	/**
	 *
	 */
	afx_msg void			OnMeshAddMemberVariable();

	/**
	 *
	 */
	afx_msg void			OnMeshDefinition();

	/**
	 *
	 */
	afx_msg void			OnMeshProperties();

	/**
	 *
	 */
	afx_msg void			OnNewFolder();

	/**
	 *
	 */
	afx_msg void			OnPaint();

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void			OnSetFocus(CWnd* pOldWnd);

	/**
	 *
	 * \param WPARAM 
	 * \param LPARAM 
	 * \return 
	 */
	afx_msg LRESULT			OnChangeActiveTab(WPARAM, LPARAM);

	/**
	 *
	 * \param id 
	 */
	afx_msg void			OnSort(UINT id);

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void			OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

