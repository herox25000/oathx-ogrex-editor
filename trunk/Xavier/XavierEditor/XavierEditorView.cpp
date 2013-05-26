#include "stdafx.h"
#include "XavierEditor.h"
#include "XavierEditorDoc.h"
#include "XavierEditorView.h"
#include "GraphDC.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CXavierEditorView, CView)

BEGIN_MESSAGE_MAP(CXavierEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXavierEditorView::OnFilePrintPreview)
	ON_MESSAGE(WM_WIZARD_FNISHED, &CXavierEditorView::OnWizardFnished)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
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
	EditorSystem::getSingletonPtr()->createRenderWindow("EditorView", m_hWnd, 800, 600, 0);
	// 设置渲染定器
	SetTimer(OGRE_RENDER_TIMER, 16, NULL);

	::RegisterHotKey(m_hWnd, 0, MOD_CONTROL, 'Z');
	::RegisterHotKey(m_hWnd, 1, MOD_CONTROL, 'Y');
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
		pMainFrame->ResetFileViewTree();
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
			if (m_nState != EDIT_VIEW_INVALID)
			{
				EditorSystem::getSingletonPtr()->update();
			}
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
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CXavierEditorView::OnSize(UINT nType, int cx, int cy)
{
	EditorPlugin* pRootPlugin = EditorPluginManager::getSingletonPtr()->getRootPlugin();
	if (pRootPlugin)
	{
		pRootPlugin->OnSize(cx, cy);
	}

	CView::OnSize(nType, cx, cy);
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
	EditorPlugin* pRootPlugin = EditorPluginManager::getSingletonPtr()->getRootPlugin();
	if (pRootPlugin)
	{
		pRootPlugin->OnMouseWheel(zDelta, Vector2(pt.x, pt.y));
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
	EditorPluginManager* pManager = EditorPluginManager::getSingletonPtr();
	if (pManager)
	{
		Vector2 vPos(point.x, 
			point.y);

		EditorPlugin* pPlugin = pManager->getPlugin(vPos);
		if (pPlugin == NULL)
		{
			EditorPlugin* pTerrain = pManager->findPlugin(EDITOR_TERRAIN);
			if (pTerrain)
				pManager->setSelectPlugin(pTerrain);	
		}
		else
		{
			pManager->setSelectPlugin(pPlugin);
		}

		EditorPlugin* pSelect = pManager->getSelectPlugin();
		if (pSelect)
			pSelect->OnLButtonDown(vPos);
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
	EditorPlugin* pSelect = EditorPluginManager::getSingletonPtr()->getSelectPlugin();
	if (pSelect)
	{
		Vector2 vPos(point.x, 
			point.y);

		pSelect->OnLButtonUp(vPos);
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
	EditorPlugin* pCamera = EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT_CAMER);
	if (pCamera)
	{
		Vector2 vPos(point.x, 
			point.y);

		pCamera->OnRButtonDown(vPos);
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
	EditorPlugin* pCamera = EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT_CAMER);
	if (pCamera)
	{
		Vector2 vPos(point.x, 
			point.y);

		pCamera->OnRButtonUp(vPos);
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
	EditorPluginManager* pPluginManager = EditorPluginManager::getSingletonPtr();
	if (pPluginManager)
	{
		Vector2 vPos(point.x, 
			point.y);

		EditorPlugin* pSelectPlugin = pPluginManager->getSelectPlugin();
		if (pSelectPlugin)
		{
			pSelectPlugin->OnMouseMove(vPos);
		}
	
		EditorPlugin* pCamera = EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT_CAMER);
		if (pCamera)
		{
			pCamera->OnMouseMove(vPos);
		}
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
	EditorPluginManager* pPluginManager = EditorPluginManager::getSingletonPtr();
	if (pPluginManager)
	{
		EditorPlugin* pSelectPlugin = pPluginManager->getSelectPlugin();
		if (pSelectPlugin)
		{
			pSelectPlugin->OnKeyDown(nChar, nRepCnt, nFlags);
		}
		else
		{
			EditorPlugin* pCamera = EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT_CAMER);
			if (pCamera)
			{
				pCamera->OnKeyDown(nChar, nRepCnt, nFlags);
			}
		}
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
	EditorPluginManager* pPluginManager = EditorPluginManager::getSingletonPtr();
	if (pPluginManager)
	{
		EditorPlugin* pSelectPlugin = pPluginManager->getSelectPlugin();
		if (pSelectPlugin)
		{
			pSelectPlugin->OnKeyUp(nChar, nRepCnt, nFlags);
		}
		else
		{
			EditorPlugin* pCamera = EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT_CAMER);
			if (pCamera)
			{
				pCamera->OnKeyUp(nChar, nRepCnt, nFlags);
			}
		}
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LONG	CXavierEditorView::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	UINT fuModifiers	= (UINT) LOWORD(lParam);  // key-modifier flags    
	UINT uVirtKey		= (UINT) HIWORD(lParam);     // virtual-key code    

	if( MOD_CONTROL == fuModifiers && 'Z' == uVirtKey )  
	{  
		EditorActionManager::getSingleton().redo();
	}  
	else if( MOD_CONTROL == fuModifiers && 'Y' == uVirtKey )  
	{  
		EditorActionManager::getSingleton().undo();
	}

	return 0;
}
