#include "stdafx.h"
#include "MainFrm.h"
#include "UnitView.h"
#include "Resource.h"
#include "Editor.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class CUnitViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CUnitView;
	DECLARE_SERIAL(CUnitViewMenuButton)
public:
	CUnitViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, 
		const CRect& rect, 
		CMFCToolBarImages* pImages, 
		BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, 
		BOOL bHighlight = FALSE, 
		BOOL bDrawBorder = TRUE, 
		BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz,bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CUnitViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////
CUnitView::CUnitView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

//////////////////////////////////////////////////////////////////////////
CUnitView::~CUnitView()
{
}

BEGIN_MESSAGE_MAP(CUnitView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
int			CUnitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wTreeView.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		rectDummy, this, 2))
	{
		return -1; 
	}

	m_wToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wToolBar.SetOwner(this);
	m_wToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);
	m_wToolBar.ReplaceButton(ID_SORT_MENU, 
		CUnitViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CUnitViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CUnitViewMenuButton, m_wToolBar.GetButton(0));
	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wTreeView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wTreeView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

//////////////////////////////////////////////////////////////////////////
BOOL		CUnitView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CUnitViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CUnitViewMenuButton, m_wToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wToolBar.Invalidate();
		m_wToolBar.UpdateWindow();
	}
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("添加成员函数..."));
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnClassAddMemberVariable()
{

}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnClassDefinition()
{

}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnClassProperties()
{

}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnNewFolder()
{

}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wTreeView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wTreeView.SetFocus();
}

//////////////////////////////////////////////////////////////////////////
void		CUnitView::OnChangeVisualStyle()
{
	m_UnitViewImage.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_UnitViewImage.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_UnitViewImage.Add(&bmp, RGB(255, 0, 0));

	m_wTreeView.SetImageList(&m_UnitViewImage, TVSIL_NORMAL);

	m_wToolBar.CleanUpLockedImages();
	m_wToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}
