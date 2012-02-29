
#include "stdafx.h"
#include "MainFrm.h"
#include "MeshView.h"
#include "Resource.h"
#include "Editor.h"

/**
* \ingroup : Editor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-02-29
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CMeshViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CMeshView;

	DECLARE_SERIAL(CMeshViewMenuButton)
public:
	/**
	 *
	 * \param hMenu 
	 * \return 
	 */
	CMeshViewMenuButton(HMENU hMenu = NULL)
		: CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{

	}

	/**
	 *
	 * \param pDC 
	 * \param rect 
	 * \param pImages 
	 * \param bHorz 
	 * \param bCustomizeMode 
	 * \param bHighlight 
	 * \param bDrawBorder 
	 * \param bGrayDisabledButtons 
	 */
	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages,
		BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CMeshViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////
CMeshView::CMeshView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CMeshView::~CMeshView()
{
}

BEGIN_MESSAGE_MAP(CMeshView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION,			OnMeshAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE,			OnMeshAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION,						OnMeshDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES,						OnMeshProperties)
	ON_COMMAND(ID_NEW_FOLDER,							OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

int		CMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wViewTree.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建类视图\n");
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

	m_wToolBar.ReplaceButton(ID_SORT_MENU, CMeshViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CMeshViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CMeshViewMenuButton, m_wToolBar.GetButton(0));

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
void		CMeshView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wViewTree;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
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
void		CMeshView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb,
		SWP_NOACTIVATE | SWP_NOZORDER);

	m_wViewTree.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, 
		rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, 
		SWP_NOACTIVATE | SWP_NOZORDER);
}

//////////////////////////////////////////////////////////////////////////
BOOL		CMeshView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CMeshViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CMeshViewMenuButton, m_wToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wToolBar.Invalidate();
		m_wToolBar.UpdateWindow();
	}
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnMeshAddMemberFunction()
{
	AfxMessageBox(_T("添加成员函数..."));
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnMeshAddMemberVariable()
{
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnMeshDefinition()
{
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnMeshProperties()
{
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnNewFolder()
{
	AfxMessageBox(_T("新建文件夹..."));
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wViewTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wViewTree.SetFocus();
}

//////////////////////////////////////////////////////////////////////////
void		CMeshView::OnChangeVisualStyle()
{
	m_wImage.DeleteImageList();

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

	m_wImage.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_wImage.Add(&bmp, RGB(255, 0, 0));

	m_wViewTree.SetImageList(&m_wImage, TVSIL_NORMAL);

	m_wToolBar.CleanUpLockedImages();
	m_wToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}
