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
	ON_NOTIFY(TCN_SELCHANGE, ID_TERRAINTOOLVIEW, OnTabPageSelChanged)
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
	if (!m_TabCtrl.Create(dwViewStyle, rectDummy, this, ID_TERRAINTOOLVIEW))
	{
		return -1;
	}

	HGDIOBJ hFont = GetStockObject(DEFAULT_GUI_FONT); 
	CFont   font; 
	font.Attach(hFont);
	m_TabCtrl.SetFont(&font);

	BOOL bNameValid = FALSE;

	// 地形贴花页面
	CString strTabDecal;
	bNameValid = strTabDecal.LoadString(IDS_TAB_DECAL);
	ASSERT(bNameValid);
	m_TabCtrl.InsertItem(0, strTabDecal);
	
	// 地形贴花图片
	if (!m_ImageDecal.Create(CSize(128,128), WS_CHILD|WS_VISIBLE,
		rectDummy, &m_TabCtrl, ID_TERRAIN_DECAL))
	{
		return -1;
	}
	// 加载地形贴花图片
	m_ImageDecal.Load("./media/texture/terrain/decal", "*.*");

	// 地形刷页面
	CString strTabBrush;
	bNameValid = strTabBrush.LoadString(IDS_TAB_BRUSH);
	ASSERT(bNameValid);
	m_TabCtrl.InsertItem(1, strTabBrush);

	// 地形贴花图片
	if (!m_ImageBrush.Create(CSize(128,128), WS_CHILD|WS_VISIBLE,
		rectDummy, &m_TabCtrl, ID_TERRAIN_BRUSH))
	{
		return -1;
	}
	// 加载地形贴花图片
	m_ImageBrush.Load("./media/texture/terrain/brush", "*.*");
	m_ImageBrush.ShowWindow(SW_HIDE);

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

	CRect rcTab;
	m_TabCtrl.GetClientRect(rcTab);
	
	// 调整位置
	m_ImageDecal.SetWindowPos(NULL, rcTab.left + 1, rcTab.top, rcTab.Width() + 1, rcTab.Height()-23, 
		SWP_NOACTIVATE | SWP_NOZORDER);
	m_ImageBrush.SetWindowPos(NULL, rcTab.left + 1, rcTab.top, rcTab.Width() + 1, rcTab.Height()-23, 
		SWP_NOACTIVATE | SWP_NOZORDER);
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

	CRect rectBrush;
	m_ImageBrush.GetWindowRect(rectBrush);
	ScreenToClient(rectBrush);

	rectBrush.InflateRect(1,1);
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

/**
 *
 * \param pNMHDR 
 * \param pResult 
 */
void	CTerrainToolView::OnTabPageSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	switch(m_TabCtrl.GetCurSel())
	{
	case 0:
		{
			m_ImageDecal.ShowWindow(SW_SHOW);
			m_ImageBrush.ShowWindow(SW_HIDE);
		}
		break;
	case 1:
		{
			m_ImageDecal.ShowWindow(SW_HIDE);
			m_ImageBrush.ShowWindow(SW_SHOW);
		}
		break;
	}
	*pResult = 0;
}