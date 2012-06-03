#include "stdafx.h"
#include "Xavier.h"
#include "DecalView.h"

IMPLEMENT_DYNAMIC(CDecalView, CDockablePane)

/**
 *
 * \return 
 */
CDecalView::CDecalView()
{

}

/**
 *
 * \return 
 */
CDecalView::~CDecalView()
{
}


BEGIN_MESSAGE_MAP(CDecalView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


/**
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

	// ¥¥Ω® ”Õº:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_wImageView.Create(dwViewStyle, rectDummy, this, 5))
	{
		return -1;
	}

	return 0;
}

/**
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

/**
 *
 */
void	CDecalView::AdjustLayout()
{
	if (GetSafeHwnd() != NULL)
	{
		CRect rcView;
		GetClientRect(rcView);

		m_wImageView.SetWindowPos(NULL, rcView.left + 1, rcView.top + 1,
			rcView.Width() - 2, rcView.Height() - 2,
			SWP_NOACTIVATE | SWP_NOZORDER
			);
	}
}

/**
 *
 */
void	CDecalView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wImageView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

