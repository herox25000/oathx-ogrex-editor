#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "Editor.h"
#include "Serialize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView
CFileView::CFileView()
{
}

//////////////////////////////////////////////////////////////////////////
CFileView::~CFileView()
{
}

//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_MENU_TERRAIN, &CFileView::OnMenuTerrain)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序
int			CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wFileView.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 
		rectDummy, this, 4))
	{
		return -1;
	}

	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wToolBar.SetOwner(this);
	m_wToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	if (!m_dTerrain.Create(IDD_DIALOG_TR, this))
	{
		return FALSE;
	}

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
	HTREEITEM hItem = m_wFileView.GetSelectedItem();
	if (hItem != NULL)
	{
		CString text = m_wFileView.GetItemText(hItem);
		
		TiXmlDocument* pDoc = Serialize::GetSingleton().GetDocument();
		if (pDoc != NULL)
		{
			TiXmlElement* root = pDoc->RootElement();
			ASSERT(root != NULL);
	
			TiXmlElement* terr = root->FirstChildElement(STR_TERRAIN);
			while(terr != NULL)
			{
				CString sName = terr->Attribute(STR_NAME);
				if (sName == text)
				{
					root->RemoveChild(terr);
					
					CString sLog = "1> 删除地形项目 " + sName;
					BDLogMessage(sLog);

					if (Serialize::GetSingleton().Save())
						UpdateSolution();
					
					break;
				}
		
				terr = terr->NextSiblingElement();
			}
		}
	}
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

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : IDB_MENU_IMAGES_24;

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

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

//////////////////////////////////////////////////////////////////////////
BOOL		CFileView::CreateSolution(CString sPath, CString sName)
{
	HTREEITEM hRoot = m_wFileView.InsertItem("解决方案", 10, 10);

	CString sLog = "1> 创建解决方案 " + Serialize::GetSingleton().GetPathName();		
	BDLogMessage(sLog);

	m_wFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	m_wFileView.Expand(hRoot, TVE_EXPAND);
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL		CFileView::OpenSolution(CString sPathName)
{
	BOOL bResult = Serialize::GetSingleton().Open(sPathName);
	if (bResult)
	{
		HTREEITEM hRoot = m_wFileView.InsertItem(
			"解决方案", 
			10, 
			10);

		CString sLog = "1> 打开解决方案 " + sPathName;		
		BDLogMessage(sLog);

		m_wFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
		m_wFileView.Expand(hRoot, TVE_EXPAND);

		UpdateSolution();
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void		CFileView::UpdateSolution()
{
	m_wFileView.DeleteAllItems();

	TiXmlDocument* pDoc = Serialize::GetSingleton().GetDocument();
	if (pDoc == NULL)
		return;

	HTREEITEM hRoot = m_wFileView.InsertItem(
		"解决方案", 
		10, 
		10);
	
	TiXmlElement* root = pDoc->RootElement();
	if (root == NULL)
		return;

	TiXmlElement* child = root->FirstChildElement(STR_TERRAIN);
	while( child != NULL)
	{
		HTREEITEM hRoot = m_wFileView.GetRootItem();
		if (hRoot != NULL)
		{
			CString sName = child->Attribute(STR_NAME);
			m_wFileView.InsertItem(sName, 1, 1, hRoot);

			CString sLog = "1> 添加地形项目 " + sName;		
			BDLogMessage(sLog);
		}

		m_wFileView.Expand(hRoot, TVE_EXPAND);

		child = child->NextSiblingElement();
	}
}

//////////////////////////////////////////////////////////////////////////
void	CFileView::OnMenuTerrain()
{
	CRect rcMain;
	AfxGetMainWnd()->GetClientRect(rcMain);

	CRect rcNull;
	m_dTerrain.GetClientRect(rcNull);

	int x = rcMain.Width() / 2 - rcNull.Width() / 2;
	int y = rcMain.Height()/ 2 - rcNull.Height()/ 2;

	m_dTerrain.SetWindowPos(&wndTop, x, y, 0, 0, SWP_NOSIZE);
	m_dTerrain.ShowWindow(SW_SHOW);
}
