#include "stdafx.h"
#include "Xavier.h"
#include "TerrainToolView.h"

IMPLEMENT_DYNAMIC(CTerrainToolView, CDockablePane)

/**
 *
 * \return 
 */
CTerrainToolView::CTerrainToolView()
{

}

/**
 *
 * \return 
 */
CTerrainToolView::~CTerrainToolView()
{
}


BEGIN_MESSAGE_MAP(CTerrainToolView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


/** View 窗口创建
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CTerrainToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_TabCtrl.Create(dwViewStyle, rectDummy, this, 14))
	{
		return -1;
	}
	
	// 调整布局
	AdjustLayout();

	return 0;
}

/** VIEW 窗口尺寸改变
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CTerrainToolView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


/** 布局调整
 *
 */
void	CTerrainToolView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_TabCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, 
		rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}


/**
 *
 */
void	CTerrainToolView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_TabCtrl.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

/**
 *
 * \param pOldWnd 
 */
void	CTerrainToolView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_TabCtrl.SetFocus();
}


