#include "stdafx.h"
#include "Xavier.h"
#include "XavierDoc.h"
#include "XavierView.h"
#include "XavierFrameContext.h"
#include "OgreSdk.h"

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
END_MESSAGE_MAP()

using namespace Ogre;

/**
 *
 * \return 
 */
CXavierView::CXavierView() : m_dwState(ST_VIEW_WELCOME), m_bLMouseDown(FALSE), m_pFrameContext(NULL)
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
	
	// ������Ⱦ����
	System::getSingleton().createApplicationWindow("Xavier Game Editor Window", m_hWnd, 800, 600, false);
	
	// �����Ⱦ����
	m_pFrameContext = new XavierFrameContext();
	if (m_pFrameContext)
	{
		Root::getSingleton().addFrameListener(m_pFrameContext);	
	}

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
		delete m_pFrameContext;
	}

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

	ViewportServer* pSdkViewport = static_cast<ViewportServer*>(
		System::getSingleton().getServer(SERVER_SDKVIEWPORT)
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
				System::getSingletonPtr()->update();
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
	m_cLMouseDown = point;

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
	CView::OnRButtonDown(nFlags, point);
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
 * \param nFlags 
 * \param point 
 */
void	CXavierView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLMouseDown)
	{
		CPoint cRel = point - m_cLMouseDown;
		
		CameraServer* pSdkCamera = static_cast<CameraServer*>(
			System::getSingleton().getServer(SERVER_SDKCAMERA)
			);
		if (pSdkCamera != NULL)
		{
			m_cLMouseDown = point;
			pSdkCamera->injectMouseMove(cRel.x, cRel.y);
		}
	}

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
	CameraServer* pSdkCamera = static_cast<CameraServer*>(
		System::getSingleton().getServer(SERVER_SDKCAMERA)
		);
	if (pSdkCamera != NULL)
	{
		pSdkCamera->injectMouseWheel(zDelta);
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
