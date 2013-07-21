#pragma once

#include "GameItemWnd.h"

class CGamePage : public CWnd
{
	DECLARE_DYNAMIC(CGamePage)
public:
	CGamePage();
	virtual ~CGamePage();
	
	// 创建游戏页
	virtual BOOL			Create(INT nRow, INT nCol, 
		HINSTANCE hInstance, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// 添加游戏项
	virtual	CGameItemWnd*	AddGameItem(INT nID, INT nDestX,
		INT nDestY, HINSTANCE hInstance, LPCTSTR lpszBackResouce, LPCTSTR lpszBillResource, BOOL bEnabled);

	// 获取游戏项
	virtual CGameItemWnd*	GetGameItem(int nIndex);

	// 销毁全部项
	virtual	void			DestroyAll();
protected:
	GameItemList			m_GameList;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL			OnEraseBkgnd(CDC* pDC);
};


