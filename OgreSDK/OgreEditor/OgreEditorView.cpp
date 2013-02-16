#include "stdafx.h"
#include "GraphDC.h"
#include "MainFrm.h"
#include "OgreEditor.h"
#include "OgreEditorDoc.h"
#include "OgreEditorView.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COgreEditorView, CView)

BEGIN_MESSAGE_MAP(COgreEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COgreEditorView::OnFilePrintPreview)
	ON_MESSAGE(WM_WIZARD_FNISHED, &COgreEditorView::OnWizardFnished)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
COgreEditorView::COgreEditorView() 
{
	m_nRenderState = EDIT_VIEW_INVALID;
}

/**
 *
 * \return 
 */
COgreEditorView::~COgreEditorView()
{
}

/**
 *
 * \param cs 
 * \return 
 */
BOOL COgreEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/**
 *
 * \param pDC
 */
void COgreEditorView::OnDraw(CDC* /*pDC*/)
{
	COgreEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

/**
 *
 */
void COgreEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

/**
 *
 * \param pInfo 
 * \return 
 */
BOOL COgreEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

/**
 *
 * \param pDC
 * \param pInfo
 */
void COgreEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

/**
 *
 * \param pDC
 * \param pInfo
 */
void COgreEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

/**
 *
 * \param nFlags 
 * \param point 
 */
void COgreEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

/**
 *
 * \param pWnd 
 * \param point 
 */
void COgreEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void COgreEditorView::AssertValid() const
{
	CView::AssertValid();
}

void COgreEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COgreEditorDoc* COgreEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COgreEditorDoc)));
	return (COgreEditorDoc*)m_pDocument;
}
#endif

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int		COgreEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	try{
		if (!EditorSystem::getSingletonPtr()->createRenderWindow(OGRE_RENDER_WINDOW, m_hWnd, 800, 600, 0))
		{
			OGRE_EXCEPT(Exception::ERR_RT_ASSERTION_FAILED, "Can't create ogre render window",
				"COgreEditorView::OnCreate");
		}

		SetTimer(IDT_RENDER_TIMER, 16, NULL);
	}
	catch(Exception& e)
	{
		AfxMessageBox(e.getFullDescription().c_str());
	}

	return 0;
}

/**
 *
 */
void	COgreEditorView::OnDestroy()
{
	CView::OnDestroy();
	
	KillTimer(IDT_RENDER_TIMER);
}


/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	COgreEditorView::OnWizardFnished(WPARAM wParam, LPARAM lParam)
{
	// change current render state
	m_nRenderState = EDIT_VIEW_EDIT;

	// reset the file tree
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame)
	{
		pMainFrame->ResetFileTree();
	}

	return 0;
}

/**
 *
 * \param nIDEvent 
 */
void	COgreEditorView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
	case IDT_RENDER_TIMER:
		{
			if (m_nRenderState != EDIT_VIEW_INVALID)
			{
				EditorSystem::getSingletonPtr()->drawFrame();
			}
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}

/**
 *
 * \param pDC 
 * \return 
 */
BOOL	COgreEditorView::OnEraseBkgnd(CDC* pDC)
{
	CRect rcView;
	GetClientRect(&rcView);

	CGraphDC dc(GetDC());
	dc.FillRect(&rcView, 
		&CBrush(RGB(0,0,0)));

	return CView::OnEraseBkgnd(pDC);
}
