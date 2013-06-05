#include "stdafx.h"
#include "OgreEditor.h"
#include "OgreEditorDoc.h"
#include "OgreEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


CEditorView::CEditorView()
{

}

CEditorView::~CEditorView()
{
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CEditorView::OnDraw(CDC* /*pDC*/)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

void CEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif

BOOL CEditorView::OnEraseBkgnd(CDC* pDC)
{
	CRect rcView;
	GetClientRect(&rcView);

	CGraphDC dc(GetDC());
	dc.FillRect(&rcView, 
		&CBrush(RGB(0,0,0)));

	dc.SetTextColor(RGB(100,255,0));
	dc.SetBkMode(TRANSPARENT);

	CRect rcText;
	rcText.left		= rcView.Width() / 2 - 500;
	rcText.right	= rcView.Width() / 2 + 500;
	rcText.top		= rcView.Height() / 2 - 100;
	rcText.bottom	= rcView.Height() / 2 + 100;

	CFont cFont;
	cFont.CreatePointFont(200, "»ªÎÄÐÐ¿¬");
	dc.SelectObject(&cFont);
	CString welcome("Welcome to Xanvier Game Editor\nversion 0.0.0.1\n<ogre 1.8.1>\nCopyright (c) 2013-2014 lp All rights reserved.");
	dc.DrawText(welcome, welcome.GetLength(), 
		&rcText, DT_CENTER|DT_VCENTER);

	return CView::OnEraseBkgnd(pDC);
}
