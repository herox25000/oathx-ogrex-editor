#include "stdafx.h"
#include "OgreSandBox.h"
#include "OgreSandBoxDoc.h"
#include "OgreSandBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COgreSandBoxView, CView)

BEGIN_MESSAGE_MAP(COgreSandBoxView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COgreSandBoxView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

COgreSandBoxView::COgreSandBoxView()
{

}

COgreSandBoxView::~COgreSandBoxView()
{
}

BOOL COgreSandBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void COgreSandBoxView::OnDraw(CDC* /*pDC*/)
{
	COgreSandBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

void COgreSandBoxView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL COgreSandBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void COgreSandBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void COgreSandBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void COgreSandBoxView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COgreSandBoxView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void COgreSandBoxView::AssertValid() const
{
	CView::AssertValid();
}

void COgreSandBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COgreSandBoxDoc* COgreSandBoxView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COgreSandBoxDoc)));
	return (COgreSandBoxDoc*)m_pDocument;
}
#endif

BOOL COgreSandBoxView::OnEraseBkgnd(CDC* pDC)
{
	CRect rcView;
	GetClientRect(&rcView);

	CGraphDC dc(GetDC());
	dc.FillRect(&rcView, 
		&CBrush(RGB(0,0,0)));

	return CView::OnEraseBkgnd(pDC);
}
