#include "stdafx.h"
#include "AppMain.h"

namespace Ogre
{
	template<> AppMain*	Singleton<AppMain>::ms_Singleton = NULL;
	AppMain&	AppMain::getSingleton()
	{
		assert(ms_Singleton != NULL); return (*ms_Singleton);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	AppMain::AppMain(void)
		:m_pRoot(NULL),m_pWnd(NULL),m_pSceneMgr(NULL),m_pCamera(NULL)
	{
		m_pRoot = new Root();
	}

	//////////////////////////////////////////////////////////////////////////
	AppMain::~AppMain(void)
	{
		if (m_pRoot != NULL)
		{
			delete m_pRoot;
			m_pRoot = NULL;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupResource()
	{
		ConfigFile cf;
		cf.load("resources.cfg");

		ConfigFile::SectionIterator seci = cf.getSectionIterator();

		String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;

			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupRenderSystem(const String& sName)
	{
		Ogre::RenderSystemList::iterator pRend = m_pRoot->getAvailableRenderers()->begin();
		while(pRend != m_pRoot->getAvailableRenderers()->end())
		{
			Ogre::String rName = (*pRend)->getName();
			if (rName == sName)
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
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupRenderWindow(HWND hWnd, int w, int h)
	{
		m_pRoot->initialise(false);

		NameValuePairList miscParams;
		miscParams["externalWindowHandle"] = StringConverter::toString((long)hWnd);
		m_pWnd = m_pRoot->createRenderWindow("OgreRenderWindow", 
			w,
			h,
			false,
			&miscParams
			);
		assert(m_pWnd != NULL);
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupSceneManager()
	{
		m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupCamera()
	{
		m_pCamera = m_pSceneMgr->createCamera("AppMain");
		m_pCamera->setPosition(Vector3(0,0,500));
		m_pCamera->lookAt(Vector3(0,0,-300));
		m_pCamera->setNearClipDistance(5);
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupViewport()
	{
		Viewport* vp = m_pWnd->addViewport(m_pCamera);
		vp->setBackgroundColour(ColourValue(0,0,0));

		m_pCamera->setAspectRatio(
			Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::setupAllResourceGroups()
	{
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void			AppMain::createMainApp(bool bAutoWnd/* =true */, HWND hWnd/* =NULL */, int w/* =0 */, int h/* =0 */)
	{
		setupResource();

		if (bAutoWnd)
		{
			m_pRoot->initialise(true);
		}
		else
		{
			setupRenderSystem("OpenGL Rendering Subsystem");
			setupRenderWindow(hWnd, w, h);
		}

		setupSceneManager();
		setupCamera();
		setupViewport();

		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		setupAllResourceGroups();
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::update()
	{
		m_pRoot->_fireFrameStarted();
		m_pWnd->update();
		m_pRoot->_fireFrameEnded();

	}
}
