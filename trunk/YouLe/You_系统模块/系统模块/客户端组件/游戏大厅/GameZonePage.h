#pragma once

#include "GamePage.h"
#include "TabPage.h"

//////////////////////////////////////////////////////////////////////////
// 游戏专区页面
//////////////////////////////////////////////////////////////////////////
class CGameZonePage : public CTabPage
{
public:
	// 构造函数
	CGameZonePage();
	// 析构函数
	virtual ~CGameZonePage();

	// 创建专区
	virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pParent);
	// 显示状态
	virtual void		ShowWindow(int nCmdShow);
	// 背景刷新
	virtual	void		EraseBkgnd(CDC* pDC);
protected:
	// 项目窗口
	CGamePage			m_GamePage;
	// 页面按钮
	CGdipButton			m_GameBnts[4];
};