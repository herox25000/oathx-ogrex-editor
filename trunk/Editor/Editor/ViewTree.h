#pragma once

class CViewTree : public CTreeCtrl
{
public:
	CViewTree();
	virtual ~CViewTree();

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()
};
