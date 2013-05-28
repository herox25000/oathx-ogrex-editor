
// OgreSandBoxView.cpp : COgreSandBoxView 类的实现
//

#include "stdafx.h"
#include "OgreSandBox.h"

#include "OgreSandBoxDoc.h"
#include "OgreSandBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COgreSandBoxView

IMPLEMENT_DYNCREATE(COgreSandBoxView, CView)

BEGIN_MESSAGE_MAP(COgreSandBoxView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COgreSandBoxView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COgreSandBoxView 构造/析构

COgreSandBoxView::COgreSandBoxView()
{
	// TODO: 在此处添加构造代码

}

COgreSandBoxView::~COgreSandBoxView()
{
}

BOOL COgreSandBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COgreSandBoxView 绘制

void COgreSandBoxView::OnDraw(CDC* /*pDC*/)
{
	COgreSandBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// COgreSandBoxView 打印


void COgreSandBoxView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL COgreSandBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COgreSandBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COgreSandBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COgreSandBoxView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COgreSandBoxView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// COgreSandBoxView 诊断

#ifdef _DEBUG
void COgreSandBoxView::AssertValid() const
{
	CView::AssertValid();
}

void COgreSandBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COgreSandBoxDoc* COgreSandBoxView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COgreSandBoxDoc)));
	return (COgreSandBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// COgreSandBoxView 消息处理程序
