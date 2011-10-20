#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class CEditorView : public CView
{
protected:
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

	BOOL			m_bFirst;
public:
	CEditorDoc*		GetDocument() const;
public:
	virtual void	OnDraw(CDC* pDC);
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL	OnPreparePrinting(CPrintInfo* pInfo);
	virtual void	OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void	OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void	OnFilePrintPreview();
	afx_msg void	OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnDestroy();
};

#ifndef _DEBUG  // EditorView.cpp 中的调试版本
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

