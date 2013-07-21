#include "Stdafx.h"
#include "TabGamePage.h"

CTabGamePage::CTabGamePage()
{

}

CTabGamePage::~CTabGamePage()
{
	for (int i=0; i<m_GameItemList.GetCount(); i++)
	{
		delete m_GameItemList[i];
	}
}

BOOL	CTabGamePage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	CEmptyPage::Create(nID, rect, pParent);

	CPoint cPos = m_rect.TopLeft();
	for (int nRow=0; nRow<3; nRow++)
	{
		for (int nCol=0; nCol<3; nCol++)
		{
			CGameItemWnd* pItem = new CGameItemWnd();
			pItem->Create(1, cPos.x + nCol * 176, cPos.y + nRow * 140, pParent, NULL, TEXT("GAMEITEM_BACK"), TEXT("GAMEITEM_BILL"));
			pItem->ShowWindow(SW_HIDE);
			m_GameItemList.Add(pItem);
		}
	}
	
	return TRUE;
}

void	CTabGamePage::ShowWindow(int nCmd)
{
	for (int i=0; i<m_GameItemList.GetCount(); i++)
	{
		m_GameItemList[i]->ShowWindow(nCmd);
	}
}