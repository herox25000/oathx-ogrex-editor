
// OgreSandBoxView.cpp : COgreSandBoxView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COgreSandBoxView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COgreSandBoxView ����/����

COgreSandBoxView::COgreSandBoxView()
{
	// TODO: �ڴ˴���ӹ������

}

COgreSandBoxView::~COgreSandBoxView()
{
}

BOOL COgreSandBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COgreSandBoxView ����

void COgreSandBoxView::OnDraw(CDC* /*pDC*/)
{
	COgreSandBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// COgreSandBoxView ��ӡ


void COgreSandBoxView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL COgreSandBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COgreSandBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COgreSandBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// COgreSandBoxView ���

#ifdef _DEBUG
void COgreSandBoxView::AssertValid() const
{
	CView::AssertValid();
}

void COgreSandBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COgreSandBoxDoc* COgreSandBoxView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COgreSandBoxDoc)));
	return (COgreSandBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// COgreSandBoxView ��Ϣ�������
