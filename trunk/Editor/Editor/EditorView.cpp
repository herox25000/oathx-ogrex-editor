#include "stdafx.h"
#include "Editor.h"
#include "EditorDoc.h"
#include "EditorView.h"

#ifndef OGRE_RENDER_TIMER
#define OGRE_RENDER_TIMER 0
#endif

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

using namespace Ogre;

CEditorView::CEditorView() :
m_pRoot(NULL), 
m_pCamera(NULL), 
m_pSceneManager(NULL), 
m_pWindow(NULL), 
m_bFirst(FALSE),
m_pViewport(NULL),
m_pEditorLogListener(NULL)
{
	m_pRoot = Ogre::Root::getSingletonPtr();
	ASSERT(m_pRoot != NULL);
}

CEditorView::~CEditorView()
{	

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
	 *	������Ⱦϵͳ
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
	 *	������Ⱦ����
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
	* ��������������
	*/
	
	m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "editorSceneInstance");
	if (m_pSceneManager != NULL)
	{
		m_pCamera = m_pSceneManager->createCamera("editor");
		// ���ó�ʼλ��
		m_pCamera->setPosition(
			Ogre::Vector3(0,0,500)
			);
		m_pCamera->lookAt(
			Ogre::Vector3(0,0,-300)
			);
		m_pCamera->setNearClipDistance(5);

		// �����ӿ�
		m_pViewport = m_pWindow->addViewport(m_pCamera);
		if (m_pViewport != NULL && m_pCamera != NULL)
		{
			m_pViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

			m_pCamera->setAspectRatio(
				Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight())
				);
		}

		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// ��װ��Դ��
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	
	return TRUE;
}

void		CEditorView::Update()
{
	m_pRoot->renderOneFrame();
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
#endif

int			CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pEditorLogListener = new OgreEditorLogListener();
	Ogre::LogManager::getSingleton().getDefaultLog()->addListener(m_pEditorLogListener);

	SetTimer(OGRE_RENDER_TIMER, 10, NULL);

	return 0;
}

void		CEditorView::OnDestroy()
{
	CView::OnDestroy();

	Ogre::LogManager::getSingleton().getDefaultLog()->removeListener(m_pEditorLogListener);
	if (m_pEditorLogListener != NULL)
		delete m_pEditorLogListener;
	
	m_pEditorLogListener = NULL;
	
	// delete ogre render timer
	KillTimer(OGRE_RENDER_TIMER);
}


void		CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	Update();

	CView::OnTimer(nIDEvent);
}

void		CEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
}

void		CEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
}

void		CEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
}

void		CEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void		CEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_pWindow != NULL && m_pViewport != NULL)
	{
		CRect rcView;
		GetClientRect(&rcView);
	
		m_pWindow->windowMovedOrResized();
		m_pCamera->setAspectRatio(Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight()));
	}
}
