#include "stdafx.h"
#include "XavierEditor.h"
#include "XavierEditorDoc.h"
#include "XavierEditorView.h"
#include "GraphDC.h"
#include "OgreSystem.h"
#include "MainFrm.h"
#include "EditorTool.h"
#include "EditorToolWorld.h"
#include "EditorToolManager.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CXavierEditorView, CView)

BEGIN_MESSAGE_MAP(CXavierEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXavierEditorView::OnFilePrintPreview)
	ON_MESSAGE(WM_WIZARD_FNISHED,			&CXavierEditorView::OnWizardFnished)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// 渲染定时器
#define OGRE_RENDER_TIMER	9527

/**
 *
 * \return 
 */
CXavierEditorView::CXavierEditorView() 
: m_nState(EDIT_VIEW_INVALID), m_bRMouseDown(FALSE)
{

}

/**
 *
 * \return 
 */
CXavierEditorView::~CXavierEditorView()
{
}

/**
 *
 * \param cs 
 * \return 
 */
BOOL	CXavierEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/**
 *
 * \param pDC
 */
void	CXavierEditorView::OnDraw(CDC* /*pDC*/)
{
	CXavierEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

/**
 *
 */
void	CXavierEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

/**
 *
 * \param pInfo 
 * \return 
 */
BOOL	CXavierEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

/**
 *
 * \param pDC
 * \param pInfo
 */
void	CXavierEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{

}

/**
 *
 * \param pDC 
 * \param pInfo 
 */
void	CXavierEditorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{

}

/**
 *
 * \param pWnd 
 * \param point 
 */
void	CXavierEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
/**
 *
 */
void	CXavierEditorView::AssertValid() const
{
	CView::AssertValid();
}

/**
 *
 * \param dc 
 */
void	CXavierEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/**
 *
 * \return 
 */
CXavierEditorDoc* CXavierEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXavierEditorDoc)));
	return (CXavierEditorDoc*)m_pDocument;
}
#endif

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CXavierEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建渲染窗口
	System::getSingletonPtr()->createRenderWindow("EditorView", m_hWnd, 800, 600, 0);
	// 设置渲染定器
	SetTimer(OGRE_RENDER_TIMER, 16, NULL);

	return 0;
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	CXavierEditorView::OnWizardFnished(WPARAM wParam, LPARAM lParam)
{
	m_nState = EDIT_VIEW_EDIT;

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame)
	{
		pMainFrame->UpdateFileView();
	}

	return 0;
}

/**
 *
 * \param nIDEvent 
 */
void	CXavierEditorView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
	case OGRE_RENDER_TIMER:
		{
			System::getSingletonPtr()->update();
		}
		break;
	}
	CView::OnTimer(nIDEvent);
}

/**
 *
 */
void	CXavierEditorView::OnDestroy()
{
	KillTimer(OGRE_RENDER_TIMER);

	CView::OnDestroy();
}

/**
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CXavierEditorView::OnSize(UINT nType, int cx, int cy)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnSize(cx, cy);
	}

	CView::OnSize(nType, cx, cy);
}

/**
 *
 * \param pDC 
 * \return 
 */
BOOL	CXavierEditorView::OnEraseBkgnd(CDC* pDC)
{
	CRect rcView;
	GetClientRect(&rcView);

	CGraphDC dc(GetDC());
	dc.FillRect(&rcView, 
		&CBrush(RGB(0,0,0)));

	return TRUE;
}

/**
 *
 * \param nFlags 
 * \param zDelta 
 * \param pt 
 * \return 
 */
BOOL	CXavierEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnMouseWheel(zDelta * 2, Vector2(pt.x, pt.y));
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnLButtonDown(Vector2(point.x, point.y));
	}

	CView::OnLButtonDown(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnLButtonUp(Vector2(point.x, point.y));
	}

	CView::OnLButtonUp(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnRButtonDown(Vector2(point.x, point.y));
	}

	CView::OnRButtonDown(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void CXavierEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnRButtonUp(Vector2(point.x, point.y));
	}

	CView::OnRButtonUp(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	EditorTool* pSelectTool = EditorToolManager::getSingletonPtr()->getSelectEditorTool();
	if (pSelectTool)
		pSelectTool->OnMouseMove(Vector2(point.x, point.y));

	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnMouseMove(Vector2(point.x, point.y));
	}

	CView::OnMouseMove(nFlags, point);
}


/**
 *
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void	CXavierEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnKeyDown(nChar, nRepCnt, nFlags);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

/**
 *
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void	CXavierEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	EditorTool* pWorld = EditorToolManager::getSingletonPtr()->getEditorTool(EDITOR_TOOL_WORLD_NAME);
	if (pWorld)
	{
		pWorld->OnKeyUp(nChar, nRepCnt, nFlags);
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
