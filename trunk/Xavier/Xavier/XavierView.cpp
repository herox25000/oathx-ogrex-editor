#include "stdafx.h"
#include "Xavier.h"
#include "XavierDoc.h"
#include "XavierView.h"
#include "OgreEditSystemPrerequisites.h"
#include "OgreBaseEditor.h"
#include "OgreRenderWindowEditor.h"
#include "OgreEditSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CXavierView, CView)

BEGIN_MESSAGE_MAP(CXavierView, CView)
	ON_COMMAND(ID_FILE_PRINT,				&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,		&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,		&CXavierView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

using namespace Ogre;

/**
 *
 * \return 
 */
CXavierView::CXavierView()
{

}

/**
 *
 * \return 
 */
CXavierView::~CXavierView()
{
}

/**
 *
 * \param cs 
 * \return 
 */
BOOL	CXavierView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CXavierView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	BaseEditorFactory* pFactory = EditSystem::getSingleton().getEditorFactory(FACTORY_RENDERWINDOW);
	if (pFactory != NULL)
	{
		SRenderWindowCreateParams pm;
		pm.hWnd			= m_hWnd;
		pm.nHeight		= 600;
		pm.nWidth		= 800;
		pm.bFullScreen	= false;

		EditSystem::getSingleton().addEditor(pFactory->create(&pm));
	}

	// ÉèÖÃäÖÈ¾Ê±ÖÓ
	SetTimer(IDT_RENDERTIME, 10, NULL);

	return 0;
}

/**
 *
 */
void	CXavierView::OnDestroy()
{
	CView::OnDestroy();
	
	// Ïú»ÙäÖÈ¾Ê±ÖÓ
	KillTimer(IDT_RENDERTIME);
}


/**
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CXavierView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect rcView;
	GetClientRect(&rcView);
}

/**
 *
 * \param nIDEvent 
 */
void	CXavierView::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case IDT_RENDERTIME:
		EditSystem::getSingletonPtr()->update();
		break;
	}

	CView::OnTimer(nIDEvent);
}


/**
 *
 * \param pDC
 */
void	CXavierView::OnDraw(CDC* /*pDC*/)
{
	CXavierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}

/**
 *
 */
void	CXavierView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

/**
 *
 * \param pInfo 
 * \return 
 */
BOOL	CXavierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ä¬ÈÏ×¼±¸
	return DoPreparePrinting(pInfo);
}

/**
 *
 * \param pDC
 * \param pInfo 
 */
void	CXavierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/**
 *
 * \param pDC
 * \param pInfo 
 */
void	CXavierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

/**
 *
 * \param pWnd 
 * \param point 
 */
void	CXavierView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CXavierView Õï¶Ï

#ifdef _DEBUG
/**
 *
 */
void	CXavierView::AssertValid() const
{
	CView::AssertValid();
}

/**
 *
 * \param dc 
 */
void CXavierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/**
 *
 * \return 
 */
CXavierDoc* CXavierView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXavierDoc)));
	return (CXavierDoc*)m_pDocument;
}
#endif //_DEBUG



