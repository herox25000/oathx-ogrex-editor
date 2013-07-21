#pragma once

#include "GameItemWnd.h"

class CGamePage : public CWnd
{
	DECLARE_DYNAMIC(CGamePage)
public:
	CGamePage();
	virtual ~CGamePage();
	
protected:
	GameItemList		m_GameList;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
};


