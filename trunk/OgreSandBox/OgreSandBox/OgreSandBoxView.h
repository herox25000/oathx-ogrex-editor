#pragma once


class COgreSandBoxView : public CView
{
protected:
	COgreSandBoxView();
	DECLARE_DYNCREATE(COgreSandBoxView)

public:
	COgreSandBoxDoc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~COgreSandBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // OgreSandBoxView.cpp 中的调试版本
inline COgreSandBoxDoc* COgreSandBoxView::GetDocument() const
   { return reinterpret_cast<COgreSandBoxDoc*>(m_pDocument); }
#endif

