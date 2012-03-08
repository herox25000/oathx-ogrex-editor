
// XavierView.cpp : CXavierView 类的实现
//

#include "stdafx.h"
#include "Xavier.h"

#include "XavierDoc.h"
#include "XavierView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXavierView

IMPLEMENT_DYNCREATE(CXavierView, CView)

BEGIN_MESSAGE_MAP(CXavierView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXavierView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CXavierView 构造/析构

CXavierView::CXavierView()
{
	// TODO: 在此处添加构造代码

}

CXavierView::~CXavierView()
{
}

BOOL CXavierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CXavierView 绘制

void CXavierView::OnDraw(CDC* /*pDC*/)
{
	CXavierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CXavierView 打印


void CXavierView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CXavierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CXavierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CXavierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CXavierView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CXavierView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CXavierView 诊断

#ifdef _DEBUG
void CXavierView::AssertValid() const
{
	CView::AssertValid();
}

void CXavierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXavierDoc* CXavierView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXavierDoc)));
	return (CXavierDoc*)m_pDocument;
}
#endif //_DEBUG


// CXavierView 消息处理程序
