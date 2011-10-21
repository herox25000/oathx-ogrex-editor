
// EditorView.cpp : CEditorView 类的实现
//

#include "stdafx.h"
#include "Editor.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "AppMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDT_UPDATE 100

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CEditorView::CEditorView()
:m_bFirst(TRUE)
{
	
}

//////////////////////////////////////////////////////////////////////////
CEditorView::~CEditorView()
{
}

//////////////////////////////////////////////////////////////////////////
BOOL		CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnDraw(CDC* /*pDC*/)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_bFirst)
	{
		CRect rcView;
		GetClientRect(rcView);

		Ogre::AppMain::getSingleton().createMainApp(0, m_hWnd, rcView.Width(), rcView.Height());
		Ogre::AppMain::getSingleton().update();
		
		m_bFirst = FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

//////////////////////////////////////////////////////////////////////////
BOOL		CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
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

//////////////////////////////////////////////////////////////////////////
CEditorDoc* CEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	Ogre::AppMain::getSingleton().update();

	CView::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
int			CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(IDT_UPDATE, 10, NULL);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
void		CEditorView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(IDT_UPDATE);
}
