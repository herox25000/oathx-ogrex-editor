#pragma once

#include "GameItemWnd.h"

class CGamePage : public CWnd
{
	DECLARE_DYNAMIC(CGamePage)
public:
	CGamePage();
	virtual ~CGamePage();
	
	// ������Ϸҳ
	virtual BOOL			Create(INT nRow, INT nCol, 
		HINSTANCE hInstance, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// �����Ϸ��
	virtual	CGameItemWnd*	AddGameItem(INT nID, INT nDestX,
		INT nDestY, HINSTANCE hInstance, LPCTSTR lpszBackResouce, LPCTSTR lpszBillResource, BOOL bEnabled);

	// ��ȡ��Ϸ��
	virtual CGameItemWnd*	GetGameItem(int nIndex);

	// ����ȫ����
	virtual	void			DestroyAll();
protected:
	GameItemList			m_GameList;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL			OnEraseBkgnd(CDC* pDC);
};


