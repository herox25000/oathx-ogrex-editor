#pragma once

/**
* \ingroup : Barcelona
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-06-22
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CBarcelonaView : public CView
{
protected:
	/**
	 *
	 * \return 
	 */
	CBarcelonaView();
	DECLARE_DYNCREATE(CBarcelonaView)

public:
	enum {
		IDT_RENDERTIME	= 0xFFFFFFFF
	};

	/**
	 *
	 * \return 
	 */
	CBarcelonaDoc*		GetDocument() const;

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

public:
	virtual ~CBarcelonaView();
#ifdef _DEBUG
	virtual void		AssertValid() const;
	virtual void		Dump(CDumpContext& dc) const;
#endif

protected:
	/**
	 *
	 */
	afx_msg void		OnFilePrintPreview();

	/**
	 *
	 * \param nFlags 
	 * \param point 
	 */
	afx_msg void		OnRButtonUp(UINT nFlags, CPoint point);

	/**
	 *
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nIDEvent 
	 */
	afx_msg void		OnTimer(UINT_PTR nIDEvent);

	/**
	 *
	 */
	afx_msg void		OnDestroy();
};

#ifndef _DEBUG
inline CBarcelonaDoc* CBarcelonaView::GetDocument() const
   { return reinterpret_cast<CBarcelonaDoc*>(m_pDocument); }
#endif

