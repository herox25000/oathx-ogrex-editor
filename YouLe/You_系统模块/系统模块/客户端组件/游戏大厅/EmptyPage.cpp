#include "Stdafx.h"
#include "EmptyPage.h"

CEmptyPage::CEmptyPage() : m_nID(0), m_pWnd(NULL)
{
	m_rect.SetRect(0, 0, 0, 0);
}

CEmptyPage::~CEmptyPage()
{

}

INT		CEmptyPage::GetID() const
{
	return m_nID;
}

void	CEmptyPage::SetID(const INT nID)
{
	m_nID = nID;
}

BOOL	CEmptyPage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	m_nID	= nID;
	m_rect	= rect;
	m_pWnd	= pParent;

	return TRUE;
}