#include "stdafx.h"
#include "GamePlaza.h"
#include "GamePage.h"

IMPLEMENT_DYNAMIC(CGamePage, CWnd)
CGamePage::CGamePage()
{
}

CGamePage::~CGamePage()
{
	DestroyAll();
}

BEGIN_MESSAGE_MAP(CGamePage, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL	CGamePage::Create(INT nRow, INT nCol, HINSTANCE hInstance, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL bResult = CWnd::Create(NULL, NULL, WS_CHILD|WS_VISIBLE, rect, pParentWnd, nID);
	ASSERT(bResult == TRUE);

	CRect client;
	GetClientRect(&client);

	for (int cy=0; cy<nRow; cy++)
	{
		for (int cx=0; cx<nCol; cx++)
		{
			AddGameItem(cy * nRow + cx, client.left + cx * 176, client.top + cy * 140, hInstance, 
				TEXT("GAMEITEM_BACK"), TEXT("GAMEITEM_BILL"), TRUE);
		}
	}
	
	return bResult;
}

CGameItemWnd*	CGamePage::AddGameItem(INT nID, INT nDestX, INT nDestY, 
									   HINSTANCE hInstance, LPCTSTR lpszBackResouce, LPCTSTR lpszBillResource, BOOL bEnabled)
{
	CGameItemWnd* pItem = new CGameItemWnd();
	ASSERT(pItem != NULL);
	
	BOOL bResult = pItem->Create(nID, nDestX, nDestY, this, hInstance, lpszBackResouce, lpszBillResource);
	if (!bResult)
	{
		delete pItem;
		return NULL;
	}

	pItem->EnableWindow(bEnabled); m_GameList.Add(pItem);

	return pItem;
}

CGameItemWnd*	CGamePage::GetGameItem(int nIndex)
{
	ASSERT(nIndex >= 0 && nIndex < m_GameList.GetCount());
	return m_GameList[nIndex];
}

void			CGamePage::DestroyAll()
{
	for (int i=0; i<m_GameList.GetCount(); i++)
	{
		delete m_GameList[i]; m_GameList[i] = NULL;
	}
}


int				CGamePage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	CRgn rgn;
	rgn.CreateRoundRectRgn(rect.left+1, rect.top+1, rect.right-1, rect.bottom-1, 5, 5);
	SetWindowRgn(rgn, TRUE);

	return 0;
}

BOOL			CGamePage::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CMemDC dc(pDC, &rect);
	dc.FillRect(&rect, &CBrush(RGB(0, 76, 149)));

	return TRUE;
}
