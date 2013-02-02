#include "OgreSystemStdAfx.h"
#include "OgreSystem.h"
#include "OgreGlobalEventSet.h"
#include "OgreServer.h"
#include "OgreServerManager.h"
#include "OgreServerFactory.h"
#include "OgreServerFactoryManager.h"

namespace Ogre
{
	template<>	System*	Singleton<System>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	System&		System::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	System*		System::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	System::System()
		: m_pRoot(NULL), m_pRenderWindow(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	System::~System()
	{

	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	bool		System::createSystem(const String& pluginFileName, const String& resourceFileName,
		bool bAutoCreateWindow)
	{
		m_pRoot = new Root(pluginFileName);
		
		Ogre::ConfigFile cf;
		cf.load(resourceFileName);

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
		 *	create and select render system
		 */
		Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
		while(pRend != m_pRoot->getAvailableRenderers().end())
		{
			Ogre::String rName = (*pRend)->getName();
#ifdef _WIN32
			if (rName == "OpenGL Rendering Subsystem")
				break;
#else
			if (rName == "Direct3D9 Rendering Subsystem")
				break;
#endif
			pRend++;
		}
		Ogre::RenderSystem *rsys = *pRend;

#ifdef _WIN32
		rsys->setConfigOption( "Colour Depth", "32" );
		rsys->setConfigOption( "Full Screen", "No" );
		rsys->setConfigOption( "VSync", "No" );
		rsys->setConfigOption( "Video Mode", "800 x 600" );
		rsys->setConfigOption( "Display Frequency", "60" );
#else
		rsys->setConfigOption( "VSync", "No" );
		rsys->setConfigOption( "Full Screen", "No" );
#endif
		rsys->setConfigOption("FSAA", "2");
		// set render system
		m_pRoot->setRenderSystem( rsys );
		
		// create render window
		m_pRoot->initialise(bAutoCreateWindow);

		new GlobalEventSet();
		new ServerManager("Xavier");
		new ServerFactoryManager();

		return true;
	}

	/**
	 *
	 */
	void		System::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void		System::clearUp()
	{
		delete ServerManager::getSingletonPtr();
		delete ServerFactoryManager::getSingletonPtr();
		delete GlobalEventSet::getSingletonPtr();

		if (m_pRoot != NULL)
		{
			delete m_pRoot;
			m_pRoot = NULL;
		}
	}

	/**
	 *
	 * \param name 
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 */
	bool			System::createRenderWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen)
	{
		NameValuePairList pm;
		pm["externalWindowHandle"] = StringConverter::toString((size_t)(hWnd));

		/*
		* 创建渲染窗口
		*/
		m_pRenderWindow	= Root::getSingletonPtr()->createRenderWindow(name,
			w, h, bFullScreen, &pm);
		if (m_pRenderWindow == NULL)
			return 0;
	
		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		/*
		* 初始化默认资源组
		*/
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		return true;
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	System::getRenderWindow() const
	{
		return m_pRenderWindow;
	}
}