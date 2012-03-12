#pragma once

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
	
public:
	/**
	 *
	 * \return 
	 */
	CXavierDoc*					GetDocument() const;

	/** ≥ı ºªØ‰÷»æ¥∞ø⁄
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

