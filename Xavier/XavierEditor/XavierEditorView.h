#pragma once

enum {
	EDIT_VIEW_INVALID,
	EDIT_VIEW_EDIT,
	EDIT_VIEW_DEMO,
};

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-15
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CXavierEditorView : public CView
{
protected:
	/**
	 *
	 * \return 
	 */
	CXavierEditorView();

	DECLARE_DYNCREATE(CXavierEditorView)

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CXavierEditorView();

	BOOL				m_bRMouseDown;
	CPoint				m_cRigthDwon;
public:
	/**
	 *
	 * \return 
	 */
	CXavierEditorDoc*	GetDocument() const;

public:
	/**
	 *
	 * \param pDC 
	 */
	virtual void		OnDraw(CDC* pDC);

	/**
	 *
	 * \param cs 
	 * \return 
	 */
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
protected:
	/**
	 *
	 * \param pInfo 
	 * \return 
	 */
	virtual BOOL		OnPreparePrinting(CPrintInfo* pInfo);

	/**
	 *
	 * \param pDC 
	 * \param pInfo 
	 */
	virtual void		OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);

	/**
	 *
	 * \param pDC 
	 * \param pInfo 
	 */
	virtual void		OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

#ifdef _DEBUG
	/**
	 *
	 */
	virtual void		AssertValid() const;

	/**
	 *
	 * \param dc 
	 */
	virtual void		Dump(CDumpContext& dc) const;
#endif

protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 */
	afx_msg void		OnFilePrintPreview();

	/**
	 *
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT		OnWizardFnished(WPARAM wParam, LPARAM lParam);
public:
	/**
	 *
	 * \param nIDEvent 
	 */
	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
protected:
	int					m_nState;
public:
	/**
	 *
	 */
	afx_msg void		OnDestroy();

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void		OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 * \param pDC 
	 * \return 
	 */
	afx_msg BOOL		OnEraseBkgnd(CDC* pDC);

	/**
	 *
	 * \param nFlags 
	 * \param zDelta 
	 * \param pt 
	 * \return 
	 */
	afx_msg BOOL		OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnLButtonDown(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnLButtonUp(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnRButtonDown(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnMouseMove(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnRButtonUp(UINT nFlags, CPoint point);
	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 */
	afx_msg void		OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 */
	afx_msg void		OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG 
inline CXavierEditorDoc* CXavierEditorView::GetDocument() const
   { return reinterpret_cast<CXavierEditorDoc*>(m_pDocument); }
#endif

