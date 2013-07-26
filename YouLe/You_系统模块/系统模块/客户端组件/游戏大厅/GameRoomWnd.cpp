#include "stdafx.h"
#include "GamePlaza.h"
#include "GameRoomWnd.h"

IMPLEMENT_DYNAMIC(CGameRoomWnd, CWnd)
CGameRoomWnd::CGameRoomWnd()
{
	memset(&m_Info, 0, sizeof(SRoomInfo));
}

CGameRoomWnd::~CGameRoomWnd()
{
}

BEGIN_MESSAGE_MAP(CGameRoomWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL	CGameRoomWnd::Create(UINT nID, INT nDestX, INT nDestY, 
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

void	CGameRoomWnd::SetRoomInfo(SRoomInfo* pInfo)
{
	ASSERT(pInfo != NULL); 
	memcpy(&m_Info, pInfo, sizeof(SRoomInfo));
}

int		CGameRoomWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// creat window rgn
	CRect rect;
	GetClientRect(&rect);

	CRgn rgn;
	rgn.CreateRoundRectRgn(rect.left+1, rect.top+1, rect.right-1, rect.bottom-1, 15, 15);
	SetWindowRgn(rgn, TRUE);

	// create regular button.
	m_Join.CreateButton(this, 
		TEXT("GAMEROOM_JOIN"), _T("PNG"), 7, 105, 0, 4);

	return 0;
}

void	CGameRoomWnd::OnPaint()
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
