#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "OgreEditor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_32771, &CFileView::OnCreateTerrainGroup)
	ON_COMMAND(ID_32772, &CFileView::OnCreateTerrainPage)
END_MESSAGE_MAP()


/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;
	}

	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();



	return 0;
}

/**
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

/**
 *
 */
void CFileView::UpdateTreeItem()
{
	EditorPlugin* pRootPlugin = EditorPluginManager::getSingletonPtr()->getRootPlugin();
	if (pRootPlugin)
	{
		m_wndFileView.DeleteAllItems();
		AddTreeItem(pRootPlugin, NULL);
	}
}

/**
 *
 * \param pPlugin 
 * \param hParent 
 * \return 
 */
BOOL CFileView::AddTreeItem(Ogre::EditorPlugin* pPlugin, HTREEITEM hParent)
{
	if (pPlugin == NULL)
		return FALSE;
	
	int nImage		= hParent ? 1 : 0;
	HTREEITEM hItem = m_wndFileView.InsertItem(pPlugin->getName().c_str(), nImage, nImage, hParent);

	HashMapEditorPluginIter hashPlugin = pPlugin->getPluginIter();
	while ( hashPlugin.hasMoreElements() )
	{
		EditorPlugin* pNext = hashPlugin.getNext();
		if (pNext)
		{
			AddTreeItem(pNext, hItem);
		}
	}

	m_wndFileView.Expand(hItem, TVE_EXPAND);
	
	return TRUE;
}

/**
 *
 * \param pWnd 
 * \param point 
 */
void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
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

/**
 *
 */
void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

/**
 *
 */
void CFileView::OnProperties()
{

}

/**
 *
 */
void CFileView::OnFileOpen()
{
	
}

/**
 *
 */
void CFileView::OnFileOpenWith()
{
	
}

/**
 *
 */
void CFileView::OnDummyCompile()
{
	
}

/**
 *
 */
void CFileView::OnEditCut()
{
	
}

/**
 *
 */
void CFileView::OnEditCopy()
{
	
}

/**
 *
 */
void CFileView::OnEditClear()
{
	
}

/**
 *
 */
void CFileView::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

/**
 *
 * \param pOldWnd 
 */
void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

/**
 *
 */
void	CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ���� */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

/**
 *
 */
void	CFileView::OnCreateTerrainGroup()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	if (pWndTree)
	{
		// get current select tiem
		HTREEITEM hSelectItem = pWndTree->GetSelectedItem();
		if (hSelectItem)
		{
			// get current select item the name
			CString name = pWndTree->GetItemText(hSelectItem);
			if (CPN::EDITOR_SCENE_MANAGER != name.GetBuffer())
				return;
		
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
			if (pMainFrame)
			{
				pMainFrame->ShowTerrainDialog();
			}
		}
	}
}

/**
 *
 */
void CFileView::OnCreateTerrainPage()
{
	//EditorPluginFactory* pPageFactory	= EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_TERRAINPAGE);
	//if (pPageFactory)
	//{
	//	STerrainPageEditorAdp adp;
	//	adp.nLayerCount					= 1;
	//	adp.tpl.fLayerWorldSize[0]		= 20.0f;
	//	adp.tpl.layerDiffuseTexture[0]	= "dirt_grayrocky_diffusespecular.dds";
	//	adp.tpl.layerNormalTexture[0]	= "dirt_grayrocky_normalheight.dds";
	//	adp.nMinBatchSize				= 33;
	//	adp.nMaxBatchSize				= 65;
	//	adp.nPageX						= 0;
	//	adp.nPageY						= 0;
	//	adp.vPos						= Vector3::ZERO;
	//	adp.bAtOnceLoad					= true;

	//	char szPluginName[MAX_PATH];
	//	sprintf_s(szPluginName, "%dx%d", adp.nPageX, adp.nPageY);
	//	adp.pluginName					= szPluginName;

	//	pPageFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(CPN::EDITOR_TERRAIN_GROUP));
	//}

	UpdateTreeItem();
}
