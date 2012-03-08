#pragma once

class CXavierView : public CView
{
protected:
	CXavierView();
	DECLARE_DYNCREATE(CXavierView)

public:
	CXavierDoc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CXavierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CXavierDoc* CXavierView::GetDocument() const
   { return reinterpret_cast<CXavierDoc*>(m_pDocument); }
#endif

