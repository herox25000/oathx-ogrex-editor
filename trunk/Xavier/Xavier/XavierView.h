#pragma once

#include "ETBrush.h"

enum{
	ST_VIEW_WELCOME,
	ST_VIEW_UPDATE
};

class XavierFrameContext;

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
class CXavierView : public CView
{
protected:
	/**
	 *
	 * \return 
	 */
	CXavierView();
	DECLARE_DYNCREATE(CXavierView)
	
protected:
	BOOL						m_bWelcome;
	DWORD						m_dwState;
	BOOL						m_bLMouseDown;
	BOOL						m_bRMouseDown;
	CPoint						m_cLMouseDown;
	CPoint						m_cLMouseLost;

protected:
	ET::Brush					m_brush;

protected:
	XavierFrameContext*			m_pFrameContext;
public:
	/**
	 *
	 * \return 
	 */
	CXavierDoc*					GetDocument() const;

	/** ��ʼ����Ⱦ����
	 *
	 * \return 
	 */
	BOOL						Initialize();
	
public:
	/**
	 *
	 * \param pDC 
	 */
	virtual void				OnDraw(CDC* pDC);

	/**
	 *
	 * \param cs 
	 * \return 
	 */
	virtual BOOL				PreCreateWindow(CREATESTRUCT& cs);
protected:
	/**
	 *
	 * \param pInfo 
	 * \return 
	 */
	virtual BOOL				OnPreparePrinting(CPrintInfo* pInfo);

	/**
	 *
	 * \param pDC 
	 * \param pInfo 
	 */
	virtual void				OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);

	/**
	 *
	 * \param pDC 
	 * \param pInfo 
	 */
	virtual void				OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CXavierView();

#ifdef _DEBUG
	/**
	 *
	 */
	virtual void				AssertValid() const;

	/**
	 *
	 * \param dc 
	 */
	virtual void				Dump(CDumpContext& dc) const;
#endif

protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int					OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 */
	afx_msg void				OnDestroy();

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT				OnCreateFnished(WPARAM wParam, LPARAM lParam);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void				OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 * \param nIDEvent 
	 */
	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void				OnLButtonUp(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void				OnRButtonDown(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);

	/**
	 *
	 * \param nFlags 
	 * \param zDelta 
	 * \param pt 
	 * \return 
	 */
	afx_msg BOOL				OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	/**
	 *
	 * \param pDC 
	 * \return 
	 */
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);

	/**
	 *
	 */
	afx_msg void				OnFilePrintPreview();

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void				OnRButtonUp(UINT nFlags, CPoint point);

	/**
	 *
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void				OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG
inline CXavierDoc* CXavierView::GetDocument() const
   { return reinterpret_cast<CXavierDoc*>(m_pDocument); }
#endif

