#include "stdafx.h"
#include "OgreEditor.h"
#include "ResourceView.h"

IMPLEMENT_DYNAMIC(CResourceView, CDockablePane)

CResourceView::CResourceView()
{

}

CResourceView::~CResourceView()
{
}


BEGIN_MESSAGE_MAP(CResourceView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_NOTIFY(TCN_SELCHANGE, ID_TAB_RESOUCEVIEW, OnTabPageSelChanged)
END_MESSAGE_MAP()

/** View 窗口创建
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CResourceView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_TabCtrl.Create(dwViewStyle, rectDummy, this, ID_TAB_RESOUCEVIEW))
	{
		return -1;
	}

	HGDIOBJ hFont = GetStockObject(DEFAULT_GUI_FONT); 
	CFont   font; 
	font.Attach(hFont);
	m_TabCtrl.SetFont(&font);

	BOOL bNameValid = FALSE;

	// load default resource tab page name
	CString strDefaultResource;
	bNameValid = strDefaultResource.LoadString(IDS_DEFAULT_RESOURCE);
	ASSERT(bNameValid);
	m_TabCtrl.InsertItem(0, strDefaultResource);

	// create default tab page
	if (!m_DefaultResourceListBox.Create(CSize(64,64), WS_CHILD|WS_VISIBLE,
		rectDummy, &m_TabCtrl, ID_TAB_DEFAULT))
	{
		return -1;
	}
	// load default resource
	m_DefaultResourceListBox.Load("D:\\sdk\\trunk\\OgreSDK\\Debug\\media\\terrain\\brush", "*.*");
	m_DefaultResourceListBox.ShowWindow(SW_SHOW);
	
	// set default page
	m_TabCtrl.SetCurSel(0);

	AdjustLayout();

	return 0;
}

/** VIEW 窗口尺寸改变
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CResourceView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


/** 布局调整
 *
 */
void	CResourceView::AdjustLayout()
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
	m_DefaultResourceListBox.SetWindowPos(NULL, rcTab.left + 1, rcTab.top, rcTab.Width() + 1, rcTab.Height()-23, 
		SWP_NOACTIVATE | SWP_NOZORDER);	
}

/**
 *
 */
void	CResourceView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_TabCtrl.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));

	CRect rectDefault;
	m_DefaultResourceListBox.GetWindowRect(rectDefault);
	ScreenToClient(rectDefault);

	rectDefault.InflateRect(1,1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

/**
 *
 * \param pOldWnd 
 */
void	CResourceView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_TabCtrl.SetFocus();
}

/**
 *
 * \param pNMHDR 
 * \param pResult 
 */
void	CResourceView::OnTabPageSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	switch(m_TabCtrl.GetCurSel())
	{
	case 0:
		{
			m_DefaultResourceListBox.ShowWindow(SW_SHOW);
		}
		break;
	}
}

