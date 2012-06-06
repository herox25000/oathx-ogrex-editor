#include "stdafx.h"
#include "Xavier.h"
#include "DecalView.h"


CDecalView::CDecalView()
{
}

CDecalView::~CDecalView()
{
}

BEGIN_MESSAGE_MAP(CDecalView, CDockablePane)
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
int		CDecalView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wDecaView.Create(CSize(128,128), WS_CHILD|WS_VISIBLE, rectDummy, this, 4))
	{
		return -1;
	}

	m_wDecaView.Load("./media/texture/terrain", "*.*");
	
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
void	CDecalView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


/** 布局调整
 *
 */
void	CDecalView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wDecaView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, 
		rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}


/**
 *
 */
void	CDecalView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wDecaView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

/**
 *
 * \param pOldWnd 
 */
void	CDecalView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wDecaView.SetFocus();
}
