
#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
public:
	CFileView();

	void				AdjustLayout();
	void				OnChangeVisualStyle();

protected:

	CViewTree			m_wFileView;
	CImageList			m_FileViewImages;
	CFileViewToolBar	m_wToolBar;

public:
	virtual ~CFileView();

protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void		OnProperties();
	afx_msg void		OnFileOpen();
	afx_msg void		OnFileOpenWith();
	afx_msg void		OnDummyCompile();
	afx_msg void		OnEditCut();
	afx_msg void		OnEditCopy();
	afx_msg void		OnEditClear();
	afx_msg void		OnPaint();
	afx_msg void		OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

