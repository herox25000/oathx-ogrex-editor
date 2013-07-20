#pragma once

#include "GamePlazaDlg.h"

class CPlatformFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

	CGamePlazaDlg*		m_pGamePlazaDlg;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


