#include "stdafx.h"
#include "Barcelona.h"
#include "BarcelonaDoc.h"
#include "BarcelonaView.h"
#include "Guardiola.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBarcelonaView, CView)

BEGIN_MESSAGE_MAP(CBarcelonaView, CView)
	ON_COMMAND(ID_FILE_PRINT,			&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,	&CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,	&CBarcelonaView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
CBarcelonaView::CBarcelonaView()
{

}

/**
 *
 * \return 
 */
CBarcelonaView::~CBarcelonaView()
{
}

/**
 *
 * \param cs 
 * \return 
 */
BOOL	CBarcelonaView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

/**
 *
 * \param pDC
 */
void	CBarcelonaView::OnDraw(CDC* pDC)
{
	CBarcelonaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rcView;
	GetClientRect(&rcView);

	CGraphDC dc(GetDC());
	dc.FillRect(&rcView, &CBrush(RGB(0,0,0)));
	dc.SetTextColor(RGB(255,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText("Welcome to Xavier Game Editor", strlen("Welcome to Xavier Game Editor"),
		&rcView, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}

/**
 *
 */
void	CBarcelonaView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

/**
 *
 * \param pInfo 
 * \return 
 */
BOOL	CBarcelonaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

/**
 *
 * \param pDC
 * \param pInfo
 */
void	CBarcelonaView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{

}

/**
 *
 * \param pDC
 * \param pInfo
 */
void	CBarcelonaView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void	CBarcelonaView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

/**
 *
 * \param pWnd 
 * \param point 
 */
void	CBarcelonaView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
/**
 *
 */
void	CBarcelonaView::AssertValid() const
{
	CView::AssertValid();
}

/**
 *
 * \param dc 
 */
void CBarcelonaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/**
 *
 * \return 
 */
CBarcelonaDoc* CBarcelonaView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBarcelonaDoc)));
	return (CBarcelonaDoc*)m_pDocument;
}
#endif

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int CBarcelonaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建渲染窗口
	Barcelona::System::getSingleton().createApplication("Xavier Game Editor Window",
		m_hWnd, 800, 600, false);

	// 设置渲染时钟
	SetTimer(IDT_RENDERTIME, 100, NULL);

	return 0;
}

/**
 *
 * \param nIDEvent 
 */
void CBarcelonaView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
	case IDT_RENDERTIME:
		Barcelona::System::getSingletonPtr()->update();
		break;
	}

	CView::OnTimer(nIDEvent);
}

/**
 *
 */
void CBarcelonaView::OnDestroy()
{
	CView::OnDestroy();
	
	// 销毁渲染时钟
	KillTimer(IDT_RENDERTIME);
}
