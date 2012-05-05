#include "OgreSystemPrerequisites.h"
#include "OgreSystem.h"
#include "OgreGlobalEventSet.h"
#include "OgreServerWorldSpace.h"
#include "OgreServerCamera.h"
#include "OgreServerViewport.h"
#include "OgreServerBaseGrid.h"

namespace Ogre
{
	template<>	System*	Singleton<System>::msSingleton = NULL;
	System&		System::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	System*		System::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	System::System() : m_pRoot(NULL), m_pRenderWindow(NULL)
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
	 * \return 
	 */
	bool			System::create(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow)
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
		 *	创建渲染系统
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
		m_pRoot->setRenderSystem( rsys );
		
		// create render window
		m_pRoot->initialise(bAutoCreateWindow);
		
		// 注册世界服务工长
		registerServerFactory(new WorldSpaceServerFactory());
		registerServerFactory(new CameraServerFactory());
		registerServerFactory(new ViewportServerFactory());
		registerServerFactory(new BaseGridServerFactory());

		// 事件发送器
		new GlobalEventSet();

		return true;
	}

	/**
	 *
	 */
	void			System::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void			System::destroy()
	{
		clearServerFactory();
		clearServer();
		
		delete GlobalEventSet::getSingletonPtr();

		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}

	/**
	 *
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScree 
	 */
	void			System::createApplicationWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen)
	{
		NameValuePairList pm;
		pm[KEY_HANDLE_WINDOW] = StringConverter::toString((size_t)(hWnd));

		/*
		* 创建渲染窗口
		*/
		m_pRenderWindow	= Root::getSingletonPtr()->createRenderWindow(name,
			w, h, bFullScreen, &pm);

		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		/*
		* 初始化默认资源组
		*/
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	System::getApplicationWindow() const
	{
		return m_pRenderWindow;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void			System::registerServerFactory(ServerFactory* pFactory)
	{
		HashServerFactory::iterator it = m_hashFactory.find(pFactory->getTypeName());
		if ( it == m_hashFactory.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("register server factory " + pFactory->getTypeName(), LML_NORMAL);
#endif
			m_hashFactory.insert(HashServerFactory::value_type(pFactory->getTypeName(), pFactory));
		}
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ServerFactory*	System::getServerFactory(const String& typeName)
	{
		HashServerFactory::iterator it = m_hashFactory.find(typeName);
		if ( it != m_hashFactory.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void			System::unregisterServerFactory(ServerFactory* pFactory)
	{
		HashServerFactory::iterator it = m_hashFactory.find(pFactory->getTypeName());
		if ( it != m_hashFactory.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("unregister server factory " + pFactory->getTypeName(), LML_NORMAL);
#endif
			delete it->second; m_hashFactory.erase(it);
		}
	}

	/**
	 *
	 */
	void			System::clearServerFactory()
	{
		HashServerFactory::iterator it = m_hashFactory.begin();
		while( it != m_hashFactory.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("unregister server factory " + it->second->getTypeName(), LML_NORMAL);
#endif
			delete it->second; it = m_hashFactory.erase(it);
		}
	}

	/**
	 *
	 * \param pServer 
	 * \return 
	 */
	bool			System::addServer(Server* pServer)
	{
		if (pServer != NULL)
		{
			VServer::iterator it = std::find(m_vServer.begin(), m_vServer.end(), pServer);
			if ( it == m_vServer.end() )
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("add server " + pServer->getTypeName(), LML_NORMAL);
#endif
				m_vServer.push_back(pServer);

				return true;
			}
			else
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("error " + pServer->getTypeName() + "isexit", LML_CRITICAL);
#endif
			}
		}

		return 0;
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	Server*			System::getServer(const String& typeName)
	{
		for (VServer::iterator it=m_vServer.begin(); it!=m_vServer.end(); it++)
		{
			if ((*it)->getTypeName() == typeName)
				return (*it);
		}

		return NULL;
	}

	/**
	 *
	 * \param pServer 
	 */
	void			System::delServer(Server* pServer)
	{
		VServer::iterator it = std::find(m_vServer.begin(), m_vServer.end(), pServer);
		if ( it != m_vServer.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("delete server" + pServer->getTypeName(), LML_NORMAL);
#endif
			delete (*it); m_vServer.erase(it);
		}
	}

	/**
	 *
	 */
	void			System::clearServer()
	{
		while( m_vServer.size() )
		{
			Server* pServer = m_vServer.back();
#ifdef _OUTPUT_LOG
			TKLogEvent("add server" + pServer->getTypeName(), LML_NORMAL);
#endif
			delete pServer; m_vServer.pop_back();
		}
	}

	/**
	 *
	 * \return 
	 */
	int				System::getServerCount() const
	{
		return m_vServer.size();
	}
}