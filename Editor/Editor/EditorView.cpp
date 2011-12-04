#include "stdafx.h"
#include "Editor.h"

#include "EditorDoc.h"
#include "EditorView.h"

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

using namespace Ogre;

CEditorView::CEditorView()
:m_pRoot(NULL), m_pCamera(NULL), m_pSceneManager(NULL), m_pWindow(NULL), m_bFirst(FALSE)
{
#ifdef _DEBUG
	m_pRoot = new Ogre::Root("plugins_d.cfg");
	ASSERT(m_pRoot != NULL);
#else
	m_pRoot = new Ogre::Root("plugins.cfg");
	ASSERT(m_pRoot != NULL);
#endif
}

CEditorView::~CEditorView()
{
	if (m_pRoot != NULL)
		delete m_pRoot;

	m_pRoot = NULL;
}

BOOL		CEditorView::InitOgreEngine()
{
	CRect rcView;
	GetClientRect(&rcView);

#ifdef _DEBUG
	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");
#else
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");
#endif

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	/*
	 *	创建渲染系统
	 */
	Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
	while(pRend != m_pRoot->getAvailableRenderers().end())
	{
		Ogre::String rName = (*pRend)->getName();
		if (rName == "OpenGL Rendering Subsystem")
			break;

		pRend++;
	}
	Ogre::RenderSystem *rsys = *pRend;

	rsys->setConfigOption("Colour Depth", "32" );
	rsys->setConfigOption( "Full Screen", "No" );
	rsys->setConfigOption( "VSync", "No" );
	rsys->setConfigOption( "Video Mode", "800 x 600" );
	rsys->setConfigOption( "Display Frequency", "60" );

	m_pRoot->setRenderSystem( rsys );

	/*
	 *	创建渲染窗口
	 */
	m_pRoot->initialise(false);

	Ogre::NameValuePairList miscParams;
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((long)m_hWnd);
	m_pWindow = m_pRoot->createRenderWindow("OgreRenderWindow", 
		rcView.Width(),
		rcView.Height(),
		false,
		&miscParams
		);
	ASSERT(m_pWindow != NULL);

	/*
	* 创建场景管理器
	*/
	
	m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "editorSceneInstance");
	if (m_pSceneManager != NULL)
	{
		m_pCamera = m_pSceneManager->createCamera("editor");
		// 设置初始位置
		m_pCamera->setPosition(
			Ogre::Vector3(0,0,500)
			);
		m_pCamera->lookAt(
			Ogre::Vector3(0,0,-300)
			);
		m_pCamera->setNearClipDistance(5);

		// 设置视口
		Viewport* vp = m_pWindow->addViewport(m_pCamera);
		if (vp != NULL && m_pCamera != NULL)
		{
			vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

			m_pCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())
				);
		}

		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// 安装资源组
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	
	return TRUE;
}

void		CEditorView::Update()
{
	m_pRoot->_fireFrameStarted();
	m_pWindow->update();
	m_pRoot->_fireFrameEnded();
}

BOOL		CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void		CEditorView::OnDraw(CDC* /*pDC*/)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_bFirst)
	{
		InitOgreEngine();
		m_bFirst = TRUE;
	}
}

void		CEditorView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL		CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void		CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void		CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void		CEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void		CEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void		CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void		CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG

int			CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 10, NULL);
	return 0;
}

void		CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	Update();

	CView::OnTimer(nIDEvent);
}
