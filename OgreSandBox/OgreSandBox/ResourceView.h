#pragma once

#include "ViewTree.h"

class CResourceViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, 
		BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const 
	{
		return FALSE; 
	}
};

class CResourceView : public CDockablePane
{
public:
	CResourceView();
	virtual ~CResourceView();

	void					AdjustLayout();
	void					OnChangeVisualStyle();

protected:
	CResourceViewToolBar	m_wToolBar;
	CViewTree				m_wTreeView;
	CImageList				m_TreeViewImage;
	UINT					m_nCurrSort;

public:
	virtual BOOL			PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnSize(UINT nType, int cx, int cy);
	afx_msg void			OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void			OnClassAddMemberFunction();
	afx_msg void			OnClassAddMemberVariable();
	afx_msg void			OnClassDefinition();
	afx_msg void			OnClassProperties();
	afx_msg void			OnNewFolder();
	afx_msg void			OnPaint();
	afx_msg void			OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT			OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void			OnSort(UINT id);
	afx_msg void			OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

