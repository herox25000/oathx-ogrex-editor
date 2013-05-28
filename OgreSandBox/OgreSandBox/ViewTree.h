#pragma once

class CViewTree : public CTreeCtrl
{
public:
	CViewTree();

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
};
