#include "stdafx.h"
#include "GamePlaza.h"
#include "GamePage.h"

IMPLEMENT_DYNAMIC(CGamePage, CWnd)
CGamePage::CGamePage()
{
}

CGamePage::~CGamePage()
{
}


BEGIN_MESSAGE_MAP(CGamePage, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CGamePage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			CGameItemWnd* pItemWnd = new CGameItemWnd();
			if (pItemWnd)
			{
				pItemWnd->Create(0, rect.left + i * 176, rect.top + j * 140, this, NULL, TEXT("GAMEITEM_BACK"), TEXT("GAMEITEM_BILL"));
			}
		}
	}

	return 0;
}
