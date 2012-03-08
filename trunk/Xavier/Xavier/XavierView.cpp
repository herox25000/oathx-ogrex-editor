
// XavierView.cpp : CXavierView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXavierView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CXavierView ����/����

CXavierView::CXavierView()
{
	// TODO: �ڴ˴���ӹ������

}

CXavierView::~CXavierView()
{
}

BOOL CXavierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CXavierView ����

void CXavierView::OnDraw(CDC* /*pDC*/)
{
	CXavierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CXavierView ��ӡ


void CXavierView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CXavierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CXavierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CXavierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CXavierView ���

#ifdef _DEBUG
void CXavierView::AssertValid() const
{
	CView::AssertValid();
}

void CXavierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXavierDoc* CXavierView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXavierDoc)));
	return (CXavierDoc*)m_pDocument;
}
#endif //_DEBUG


// CXavierView ��Ϣ�������
