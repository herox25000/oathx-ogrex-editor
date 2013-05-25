#include "stdafx.h"
#include "XavierEditor.h"
#include "UnitView.h"

IMPLEMENT_DYNAMIC(CUnitView, CDockablePane)

/**
 *
 * \return 
 */
CUnitView::CUnitView()
{

}

/**
 *
 * \return 
 */
CUnitView::~CUnitView()
{
}


BEGIN_MESSAGE_MAP(CUnitView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


/** View 窗口创建
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CUnitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_TabCtrl.Create(dwViewStyle, rectDummy, this, ID_UNIT))
	{
		return -1;
	}

	HGDIOBJ hFont = GetStockObject(DEFAULT_GUI_FONT); 
	CFont   font; 
	font.Attach(hFont);
	m_TabCtrl.SetFont(&font);

	BOOL bNameValid = FALSE;

	CString strTabModule;
	bNameValid = strTabModule.LoadString(IDS_TAB_MODULE);
	ASSERT(bNameValid);
	m_TabCtrl.InsertItem(0, strTabModule);

	// 地形画刷图片
	if (!m_UnitModule.Create(CSize(64,64), WS_CHILD|WS_VISIBLE,
		rectDummy, &m_TabCtrl, ID_UNIT))
	{
		return -1;
	}

	// 加载地形画刷图片
	m_UnitModule.Load(".\\media\\models", "*.mesh");
	m_UnitModule.ShowWindow(SW_SHOW);

	m_TabCtrl.SetCurSel(0);

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
void	CUnitView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


/** 布局调整
 *
 */
void	CUnitView::AdjustLayout()
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
	m_UnitModule.SetWindowPos(NULL, rcTab.left + 1, rcTab.top, rcTab.Width() + 1, rcTab.Height()-23, 
		SWP_NOACTIVATE | SWP_NOZORDER);
}


/**
 *
 */
void	CUnitView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_TabCtrl.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));

	CRect rectModule;
	m_UnitModule.GetWindowRect(rectModule);
	ScreenToClient(rectModule);

	rectModule.InflateRect(1,1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


