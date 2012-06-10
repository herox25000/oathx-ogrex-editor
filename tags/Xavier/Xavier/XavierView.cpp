#include "stdafx.h"
#include "Xavier.h"
#include "MainFrm.h"
#include "XavierDoc.h"
#include "XavierView.h"
#include "XavierAppEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CXavierView, CView)

BEGIN_MESSAGE_MAP(CXavierView, CView)
	ON_COMMAND(ID_FILE_PRINT,				&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,		&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,		&CXavierView::OnFilePrintPreview)
	ON_MESSAGE(WM_CREATE_FNISHED,			&CXavierView::OnCreateFnished)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

using namespace Ogre;

/**
 *
 * \return 
 */
CXavierView::CXavierView() : m_dwState(ST_VIEW_WELCOME), m_bLMouseDown(FALSE), m_bRMouseDown(FALSE), m_pFrameContext(NULL),m_pDecalCursor(NULL)
{
	m_pEditorManager = NULL;
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
	
	// ������Ⱦ����
	System::getSingleton().createApplicationWindow("Xavier Game Editor Window", m_hWnd, 800, 600, false);
	
	// ������Ⱦ����
	m_pFrameContext = new XavierFrameContext();
	if (m_pFrameContext)
	{
		Root::getSingleton().addFrameListener(m_pFrameContext);	
	}

	// �����༭��
	m_pEditorManager = new XavierEditorManager();
	m_pEditorManager->load("./config/editor.xml");

	// ������Ⱦʱ��
	SetTimer(IDT_RENDERTIME, 100, NULL);

	return 0;
}

/**
 *
 */
void	CXavierView::OnDestroy()
{
	CView::OnDestroy();
	
	if (m_pFrameContext)
	{
		Root::getSingleton().removeFrameListener(m_pFrameContext);
		SAFE_DELETE(m_pFrameContext);
	}

	SAFE_DELETE(m_pDecalCursor);
	SAFE_DELETE(m_pEditorManager);

	// ������Ⱦʱ��
	KillTimer(IDT_RENDERTIME);
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	CXavierView::OnCreateFnished(WPARAM wParam, LPARAM lParam)
{
	//TKLogEvent("������������Ⱦ...", LML_NORMAL);
	// ��������
	m_dwState = ST_VIEW_UPDATE;

	// to do:

	//WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
	//	System::getSingleton().getServer(SERVER_WORLDSPACE)
	//	);
	//if (pWorldServer)
	//{
	//	TerrainGroupServer* pTerrainServer = static_cast<TerrainGroupServer*>(
	//		System::getSingleton().getServer(SERVER_TERRAIN_GROUP)
	//		);

	//	m_pDecalCursor = new XavierDecalCursor(pWorldServer, pTerrainServer);
	//	m_pDecalCursor->setDecalCursor(0, 0, 1);
	//}

	//BaseGridServer* pGridServer = static_cast<BaseGridServer*>(
	//	System::getSingleton().getServer(SERVER_BASEGRID)
	//	);
	//if (pGridServer)
	//{
	//	pGridServer->hide();
	//}

	return 0;
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

	XavierViewportEditor* pSdkViewport = static_cast<XavierViewportEditor*>(
		XavierEditorManager::getSingleton().getTool(SERVER_SDKVIEWPORT)
		);
	if (pSdkViewport != NULL)
	{
		pSdkViewport->windowMovedOrResized();
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
			if (m_dwState == ST_VIEW_UPDATE)
				XavierEditorManager::getSingletonPtr()->update();
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

	if (m_dwState == ST_VIEW_WELCOME)
	{
		CRect rcView;
		GetClientRect(&rcView);

		CGraphDC dc(GetDC());
		dc.FillRect(&rcView, &CBrush(RGB(0,0,0)));
		dc.SetTextColor(RGB(255,0,0));
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText("Welcome to Xavier Game Editor", strlen("Welcome to Xavier Game Editor"), &rcView, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}
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
	// Ĭ��׼��
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
 * \param pWnd 
 * \param point 
 */
void	CXavierView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CXavierView ���

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


/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLMouseDown = TRUE;

	CView::OnLButtonDown(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLMouseDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRMouseDown = TRUE;
	m_cLMouseDown = point;
	CView::OnRButtonDown(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRMouseDown = FALSE;

	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnMouseMove(UINT nFlags, CPoint point)
{
	XavierCameraEditor* pCameraEditor = static_cast<XavierCameraEditor*>(
		XavierEditorManager::getSingleton().getTool(SERVER_SDKCAMERA)
		);
	if (pCameraEditor)
	{
		if (m_bRMouseDown)
		{
			CPoint cRel = point - m_cLMouseDown;
			pCameraEditor->OnMouseMove(Vector2(cRel.x, cRel.y));

			m_cLMouseDown = point;			
		}
	}

	/*CameraServer* pSdkCamera = static_cast<CameraServer*>(
		System::getSingleton().getServer(SERVER_SDKCAMERA)
		);
	if (pSdkCamera != NULL)
	{
		if (m_bRMouseDown)
		{
			CPoint cRel = point - m_cLMouseDown;
			pSdkCamera->injectMouseMove(cRel.x, cRel.y);

			m_cLMouseDown = point;
		}
		else
		{

			CRect rc;
			GetClientRect(&rc);

			TerrainGroupServer* pTerrainServer = static_cast<TerrainGroupServer*>(
				System::getSingleton().getServer(SERVER_TERRAIN_GROUP)
				);
			if (pTerrainServer)
			{
				Camera* pCamera = pSdkCamera->getCamera();
				if (pCamera)
				{
					float fScreenX = (float)point.x / (float)(rc.Width());
					float fScreenY = (float)point.y / (float)(rc.Height());
					
					m_pDecalCursor->invalid(pCamera, fScreenX, fScreenY);
				}
			}
		}
	}*/

	CView::OnMouseMove(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param zDelta 
 * \param pt 
 * \return 
 */
BOOL CXavierView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	XavierCameraEditor* pCameraEditor = static_cast<XavierCameraEditor*>(
		XavierEditorManager::getSingleton().getTool(SERVER_SDKCAMERA)
		);
	if (pCameraEditor)
	{
		pCameraEditor->OnMouseWheel(zDelta*5, Vector2(pt.x, pt.y));
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

/**
 *
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void CXavierView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch( nChar )
	{
	case VK_OEM_PLUS:
		{
			if (m_pDecalCursor)
			{
				float fRadius = XavierDecalCursor::getSingleton().getRadius();
				fRadius += 1.0f;
				m_pDecalCursor->setRadius(fRadius);
			}
		}
		
		break;
	case VK_OEM_MINUS:
		{
			if (m_pDecalCursor)
			{
				float fRadius = XavierDecalCursor::getSingleton().getRadius();
				fRadius -= 1.0f;
				m_pDecalCursor->setRadius(fRadius);
			}
		}
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

/**
 *
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void CXavierView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}