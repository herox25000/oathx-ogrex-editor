
#pragma once

#include "ViewTree.h"

class CMeshToolBar : public CMFCToolBar
{
	virtual void			OnUpdateCmdUI(CFrameWnd* pTarget,
		BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL			AllowShowOnList() const 
	{
		return FALSE; 
	}
};

class CMeshView : public CDockablePane
{
public:
	CMeshView();
	virtual ~CMeshView();

	virtual BOOL			PreTranslateMessage(MSG* pMsg);
	virtual void			AdjustLayout();
	virtual void			OnChangeVisualStyle();

protected:
	CMeshToolBar			m_wToolBar;
	CViewTree				m_wViewTree;
	CImageList				m_wImage;
	UINT					m_nCurrSort;

protected:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnSize(UINT nType, int cx, int cy);
	afx_msg void			OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void			OnMeshAddMemberFunction();
	afx_msg void			OnMeshAddMemberVariable();
	afx_msg void			OnMeshDefinition();
	afx_msg void			OnMeshProperties();
	afx_msg void			OnNewFolder();
	afx_msg void			OnPaint();
	afx_msg void			OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT			OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void			OnSort(UINT id);
	afx_msg void			OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

