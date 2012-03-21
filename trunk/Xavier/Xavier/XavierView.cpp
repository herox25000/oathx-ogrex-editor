#include "stdafx.h"
#include "Xavier.h"
#include "XavierDoc.h"
#include "XavierView.h"
#include "OgreEditor.h"

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
	ON_WM_ERASEBKGND()
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
	
	// 创建渲染窗口
	AppEdit::getSingletonPtr()->createRenderWindow(m_hWnd, 800, 600, false);

	// 设置渲染时钟
	SetTimer(IDT_RENDERTIME, 100, NULL);

	return 0;
}

/**
 *
 */
void	CXavierView::OnDestroy()
{
	CView::OnDestroy();
	
	// 销毁渲染时钟
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

	ViewPortEditor* pViewEditor = static_cast<ViewPortEditor*>(
		AppEdit::getSingletonPtr()->getEditor(EDIT_VIEWPORT)
		);
	if (pViewEditor != NULL)
	{
		pViewEditor->windowMovedOrResized();
	}
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
		{			
			AppEdit::getSingletonPtr()->update();
			Sleep(1);
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}


/**
 *
 * \param pDC
 */
void	CXavierView::OnDraw(CDC* pDC)
{
	CXavierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

/**
 *
 * \param pDC 
 * \return 
 */
BOOL	CXavierView::OnEraseBkgnd(CDC* pDC)
{
	return CView::OnEraseBkgnd(pDC);
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
	// 默认准备
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


// CXavierView 诊断

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



