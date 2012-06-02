#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "Xavier.h"
#include "MainFrm.h"
#include "OgreSSSDK.h"


using namespace Ogre;

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES,		OnProperties)
	ON_COMMAND(ID_NEWCREATE,		OnNewCreated)
	ON_COMMAND(ID_OPEN_WITH,		OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE,	OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT,			OnEditCut)
	ON_COMMAND(ID_EDIT_COPY,		OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR,		OnEditClear)
	ON_MESSAGE(WM_CREATE_FNISHED,	&CFileView::OnCreateFnished)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/** View 窗口创建
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_wFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		return -1;
	}

	// 加载视图图像
	m_FileViewImages.Create(IDB_FILE_VIEW, 
		16,
		0,
		RGB(255, 0, 255));
	m_wFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
	
	// 创建工具栏
	m_wToolBar.Create(this,
		AFX_DEFAULT_TOOLBAR_STYLE, 
		IDR_EXPLORER);
	m_wToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE);
	
	// 选择窗口风格
	OnChangeVisualStyle();

	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC |CBRS_BORDER_TOP | 
		CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wToolBar.SetOwner(this);
	m_wToolBar.SetRouteCommandsViaFrame(FALSE);
	
	/*
	* 创建服务工厂对话框
	*/
	if (!m_wServerFactoryDlg.Create(IDD_DIALOG_SERVER))
		return -1;

	// 调整布局
	AdjustLayout();

	return 0;
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	CFileView::OnCreateFnished(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		CString sPath = pMainFrame->GetPath();
		CString sName = pMainFrame->GetName();
		
		/*
		*	插入文件视图跟项目
		*/
		HTREEITEM hRoot = m_wFileView.InsertItem(_T(sName.GetBuffer()), 0, 0);
		m_wFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
		
		// 获取系统实例
		System* pSystem = System::getSingletonPtr();
		
		/*
		* 遍历所有创建的编辑工具
		*/
		int iCount = pSystem->getServerCount();
		for (int i=0; i<iCount; i++)
		{
			Server* pServer = pSystem->getServer(i);
			if (pServer)
				m_wFileView.InsertItem(_T(pServer->getTypeName().c_str()), 0, 0, hRoot);
		}

		m_wFileView.Expand(hRoot, TVE_EXPAND);
	}

	/*
	* 通知主窗口初始化完毕
	*/
	::SendMessage(pMainFrame->GetActiveView()->m_hWnd, WM_CREATE_FNISHED, NULL, NULL);

	return 0;
}

/**
 *
 * \param args 
 * \return 
 */
bool	CFileView::OnXMLSerializeCreated(const Ogre::EventArgs& args)
{
	// 发送创建完成消息到渲染窗口
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		::SendMessage(pMainFrame->GetActiveView()->m_hWnd, WM_CREATE_FNISHED, NULL, NULL);
	}
	
	return true;
}

/** VIEW 窗口尺寸改变
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

/** 有键菜单
 *
 * \param pWnd 
 * \param point 
 */
void	CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
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

/** 布局调整
 *
 */
void	CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, 
		rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	m_wFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, 
		rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

/**
 *
 */
void	CFileView::OnProperties()
{
	AfxMessageBox(_T("属性...."));
}

/**
 *
 */
void	CFileView::OnNewCreated()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		CRect rcMain;
		pMainFrame->GetClientRect(&rcMain);

		CRect rcDlg;
		m_wServerFactoryDlg.GetClientRect(&rcDlg);

		m_wServerFactoryDlg.SetWindowPos(&wndTop, rcMain.Width() / 2 - rcDlg.Width() / 2,
			rcMain.Height() / 2 - rcDlg.Height() / 2, 0, 0, SWP_NOSIZE);
		
		/*
		* 更新可用的工厂
		*/
		m_wServerFactoryDlg.UpdateFactory();

		m_wServerFactoryDlg.ShowWindow(SW_SHOW);
	}
}

/**
 *
 */
void	CFileView::OnFileOpenWith()
{
	
}

/**
 *
 */
void	CFileView::OnDummyCompile()
{
	
}

/**
 *
 */
void	CFileView::OnEditCut()
{
	
}

/**
 *
 */
void	CFileView::OnEditCopy()
{
	
}

/**
 *
 */
void	CFileView::OnEditClear()
{
	
}

/**
 *
 */
void	CFileView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

/**
 *
 * \param pOldWnd 
 */
void	CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wFileView.SetFocus();
}

/**
 *
 */
void	CFileView::OnChangeVisualStyle()
{
	m_wToolBar.CleanUpLockedImages();
	m_wToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定 */);

	m_FileViewImages.DeleteImageList();

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

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


