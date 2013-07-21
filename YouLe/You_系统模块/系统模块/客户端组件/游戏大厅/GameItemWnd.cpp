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
END_MESSAGE_MAP()

// 创建游戏项
BOOL CGameItemWnd::Create(UINT nID, INT nDestX, INT nDestY,
						  CWnd* pParent, HINSTANCE hInstance, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName)
{
	m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, 
		lpszBackResourceName);
	m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance,
		lpszBillResouceName);

	CRect rect;
	rect.SetRect(nDestX, nDestY,
		nDestX + m_PngBack.GetWidth(), nDestY + m_PngBack.GetHeight());

	return CWnd::Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rect, pParent, nID);
}

// 状态控制
BOOL CGameItemWnd::EnableWindow(BOOL bEnable)
{
	m_Regular.ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	m_JoinBtn.ShowWindow(bEnable ? SW_SHOW : SW_HIDE);

	return CWnd::EnableWindow(bEnable);
}

// 设置背景
void CGameItemWnd::SetBackImage(HINSTANCE hInstance, LPCTSTR lpszBackResouceName)
{
	m_PngBack.DestroyImage();
	m_PngBack.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBackResouceName);
}

// 设置广告
void CGameItemWnd::SetBillImage(HINSTANCE hInstance, LPCTSTR lpszBillResouceName)
{
	m_PngBill.DestroyImage();
	m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, lpszBillResouceName);
}

// 背景刷新
BOOL CGameItemWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);

	BOOL bEnabled = IsWindowEnabled();
	if (!bEnabled)
	{
		// draw enable background
		m_PngBack.DrawImage(pDevC, 0, 0);
	}
	else
	{
		// drwo normal stat image
		m_PngBill.DrawImage(pDevC, 0, 0);
	}

	m_Regular.SetBkGnd(pDevC);
	m_JoinBtn.SetBkGnd(pDevC);

	return TRUE;
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
	m_JoinBtn.CreateButton(this,
		TEXT("GAMEITEM_JOIN"), _T("PNG"), 60, 105, 0, 4);
	
	return 0;
}

