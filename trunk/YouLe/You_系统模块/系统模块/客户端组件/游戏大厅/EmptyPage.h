#pragma once

class CEmptyPage
{
public:
	CEmptyPage();
	virtual ~CEmptyPage();

	virtual BOOL		Create(INT nID, const RECT& rect, CWnd* pParent);
	// get current page id
	virtual INT			GetID() const;
	// set current page id
	virtual void		SetID(const INT nID);
	
protected:
	INT					m_nID;
	CRect				m_rect;
	CWnd*				m_pWnd;
};