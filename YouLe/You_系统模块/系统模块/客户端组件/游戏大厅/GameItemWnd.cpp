#include "stdafx.h"
#include "GamePlaza.h"
#include "GameItemWnd.h"

IMPLEMENT_DYNAMIC(CGameItemWnd, CWnd)
CGameItemWnd::CGameItemWnd()
{
}

CGameItemWnd::~CGameItemWnd()
{
}

BEGIN_MESSAGE_MAP(CGameItemWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CGameItemWnd::Create(UINT nID, INT nDestX, INT nDestY,
						  CWnd* pParent, HINSTANCE hResource, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName)
{
	m_PngBack.LoadImage(hResource == NULL ? AfxGetInstanceHandle() : hResource, 
		lpszBackResourceName);
	m_PngBill.LoadImage(hResource == NULL ? AfxGetInstanceHandle() : hResource,
		lpszBillResouceName);

	CRect rect;
	rect.SetRect(nDestX, nDestY,
		nDestX + m_PngBack.GetWidth(), nDestY + m_PngBack.GetHeight());

	return CWnd::Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rect, pParent, nID);
}

BOOL CGameItemWnd::OnEraseBkgnd(CDC* pDC)
{
	return CWnd::OnEraseBkgnd(pDC);
}

int CGameItemWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// creat window rgn
	CRect rect;
	GetClientRect(&rect);

	CRgn rgn;
	rgn.CreateRoundRectRgn(rect.left+1, rect.top+1, rect.right-1, rect.bottom-1, 5, 5);
	SetWindowRgn(rgn, TRUE);

	// create regular button.
	m_Regular.CreateButton(this, 
		TEXT("GAMEITEM_REGULAR"), _T("PNG"), 7, 105, 0, 4);
	
	// create join button
	m_Join.CreateButton(this, TEXT("GAMEITEM_JOIN"), _T("PNG"), 60, 105, 0, 4);
	
	return 0;
}

void CGameItemWnd::OnPaint()
{
	CMemDC pMemDC(GetDC());

	BOOL bEnabled = IsWindowEnabled();
	if (!bEnabled)
	{
		// draw enable background
		m_PngBack.DrawImage(pMemDC, 0, 0);
	}
	else
	{
		// drwo normal stat image
		m_PngBill.DrawImage(pMemDC, 0, 0);
	}

	return CWnd::OnPaint();
}

