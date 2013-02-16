#pragma once


/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-15
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class COgreEditorView : public CView
{
protected:
	COgreEditorView();
	DECLARE_DYNCREATE(COgreEditorView)

	// 当前渲染状态
	int				m_nRenderState;
public:
	enum {
		EDIT_VIEW_INVALID,
		EDIT_VIEW_EDIT,
		EDIT_VIEW_DEMO,
	};

	COgreEditorDoc* GetDocument() const;

public:
	virtual void	OnDraw(CDC* pDC);
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL	OnPreparePrinting(CPrintInfo* pInfo);
	virtual void	OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void	OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~COgreEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/** 向导创建完成
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT	OnWizardFnished(WPARAM wParam, LPARAM lParam);

protected:
	afx_msg void	OnFilePrintPreview();
	afx_msg void	OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnDestroy();
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG
inline COgreEditorDoc* COgreEditorView::GetDocument() const
   { return reinterpret_cast<COgreEditorDoc*>(m_pDocument); }
#endif

