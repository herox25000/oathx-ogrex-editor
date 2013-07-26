#include "Stdafx.h"
#include "GameZonePage.h"

#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WINDOWX			176
#define GTP_WINDOWY			140
#define GTP_ITEMCOL			3
#define GTP_ITEMROW			3

// 构造函数
CGameZonePage::CGameZonePage()
{

}

// 析构函数
CGameZonePage::~CGameZonePage()
{

}

// 创建游戏页面
BOOL CGameZonePage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	BOOL bResult = CTabPage::Create(nID, rect, pParent);
	ASSERT(bResult == TRUE);
	
	INT nLeft	= rect.left + GTP_OFFSETX;
	int nTop	= rect.top + GTP_OFFSETY;

	m_GamePage.Create(GTP_ITEMCOL, GTP_ITEMROW, NULL, 
		CRect(nLeft, nTop, nLeft + GTP_WINDOWX * GTP_ITEMCOL, nTop + GTP_WINDOWY * GTP_ITEMROW), pParent, 0);

	// 创建页面按钮
	const TCHAR* chBtnImageResouceName[] = {
		TEXT("GAMETAB_GAME"),
		TEXT("GAMETAB_CARD"),
		TEXT("GAMETAB_MAHJ"),
		TEXT("GAMETAB_LEIS")
	};

	const INT idList[] = {
		IDB_GAMETAB_GAME, IDB_GAMETAB_CARD, IDB_GAMETAB_MAHJ, IDB_GAMETAB_LEIS
	};
	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].CreateButton(pParent, 
			chBtnImageResouceName[i], _T("PNG"), rect.left + i * 100, rect.top, idList[i], 3);
	}

	return bResult;
}

// 背景刷新
void CGameZonePage::EraseBkgnd(CDC* pDC)
{
	ASSERT(pDC != NULL);

	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].SetBkGnd(pDC);
	}
}

// 显示状态
void CGameZonePage::ShowWindow(int nCmdShow)
{
	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].ShowWindow(nCmdShow);
	}

	m_GamePage.ShowWindow(nCmdShow);
}

void CGameZonePage::EnableWindow(INT iBtton, BOOL bEnabled)
{
	m_GameBnts[iBtton].EnableWindow(bEnabled);
}
