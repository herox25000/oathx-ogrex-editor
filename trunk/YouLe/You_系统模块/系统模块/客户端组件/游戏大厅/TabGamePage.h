#pragma once

#include "EmptyPage.h"
#include "GameItemWnd.h"

class CTabGamePage : public CEmptyPage
{
public:
	CTabGamePage();
	virtual ~CTabGamePage();

	virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pParent);
	virtual void		ShowWindow(int nCmd);
protected:
	GameItemList		m_GameItemList;
};
