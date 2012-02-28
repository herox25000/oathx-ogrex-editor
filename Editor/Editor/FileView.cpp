#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "Editor.h"

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES,		OnProperties)
	ON_COMMAND(ID_OPEN,				OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH,		OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE,	OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT,			OnEditCut)
	ON_COMMAND(ID_EDIT_COPY,		OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR,		OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
CFileView::CFileView()
{
}

//////////////////////////////////////////////////////////////////////////
CFileView::~CFileView()
{
}

//////////////////////////////////////////////////////////////////////////
int			CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wFileView.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS, 
		rectDummy, this, 4))
	{
		return -1;
	}

	if (m_vImage.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255)))
	{
		m_wFileView.SetImageList(&m_vImage, TVSIL_NORMAL);
	}

	if (m_wToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER))
	{
		m_wToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE);
		OnChangeVisualStyle();

		DWORD dwToolBar = m_wToolBar.GetPaneStyle();
		dwToolBar = dwToolBar | CBRS_TOOLTIPS | CBRS_FLYBY;
		m_wToolBar.SetPaneStyle(dwToolBar);

		dwToolBar = m_wToolBar.GetPaneStyle();
		m_wToolBar.SetPaneStyle(dwToolBar & ~(CBRS_GRIPPER | 
			CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

		m_wToolBar.SetOwner(this);
		m_wToolBar.SetRouteCommandsViaFrame(FALSE);
	}

	AdjustLayout();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wFileView;
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
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnProperties()
{
	AfxMessageBox(_T("属性...."));
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnFileOpen()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnFileOpenWith()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnDummyCompile()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnEditCut()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnEditCopy()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnEditClear()
{
	
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wFileView.SetFocus();
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::OnChangeVisualStyle()
{
	m_wToolBar.CleanUpLockedImages();
	m_wToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定 */);

	m_vImage.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

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

	m_vImage.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_vImage.Add(&bmp, RGB(255, 0, 255));

	m_wFileView.SetImageList(&m_vImage, TVSIL_NORMAL);
}


