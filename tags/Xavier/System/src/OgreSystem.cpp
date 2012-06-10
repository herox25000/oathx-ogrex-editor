#include "OgreSystemPrerequisites.h"
#include "OgreDynLibManager.h"
#include "OgrePlugin.h"
#include "OgreDynLib.h"
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

	// 插件导出
	typedef void (*DLLPluginStart)(void);
	typedef void (*DLLPluginStop)(void);

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
	bool				System::create(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow)
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
	void				System::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void				System::destroy()
	{
		clearServerFactory();
		clearServer();
		clearPlugin();
		
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
	void				System::createApplicationWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen)
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
	RenderWindow*		System::getApplicationWindow() const
	{
		return m_pRenderWindow;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void				System::registerServerFactory(ServerFactory* pFactory)
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
	ServerFactory*		System::getServerFactory(const String& typeName)
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
	void				System::unregisterServerFactory(ServerFactory* pFactory)
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
	 * \param typeName 
	 */
	void				System::unregisterServerFactory(const String& typeName)
	{
		ServerFactory* pFactory = getServerFactory(typeName);
		if (pFactory)
			unregisterServerFactory(pFactory);
	}

	/**
	 *
	 * \return 
	 */
	ServerFactoryIter	System::getHashServerFactory()
	{
		return ServerFactoryIter(m_hashFactory.begin(), m_hashFactory.end());
	}

	/**
	 *
	 */
	void				System::clearServerFactory()
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
	bool				System::addServer(Server* pServer)
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
	 * \param idx 
	 * \return 
	 */
	Server*			System::getServer(int idx)
	{
		if (idx >= 0 && idx < getServerCount())
			return m_vServer[idx];

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
			TKLogEvent("del server" + pServer->getTypeName(), LML_NORMAL);
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

	/**
	 *
	 * \param name 
	 */
	void			System::loadPlugin(const String& name)
	{
		DynLib* pLib = DynLibManager::getSingleton().load(name);
		if (pLib != NULL)
		{
			m_vDynlib.push_back(pLib);

			DLLPluginStart call = (DLLPluginStart)pLib->getSymbol("dllStartPlugin");

			if (!call)
				OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStartPlugin in library " + name,
				"AppEdit::loadPlugin");

			call();
		}
	}

	/**
	 *
	 * \param name 
	 */
	void			System::unloadPlugin(const String& name)
	{
		for (VDynlib::iterator it=m_vDynlib.begin();
			it!=m_vDynlib.end(); it++)
		{
			if ( (*it)->getName() == name)
			{
				DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
				if (!call)
					OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStopPlugin in library " + name,
					"AppEdit::unloadPlugin");

				call();

				DynLibManager::getSingleton().unload(*it); m_vDynlib.erase(it);

				break;
			}
		}
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			System::installPlugin(Plugin* pPlugin)
	{
		if (pPlugin != NULL)
		{
			LogManager::getSingleton().logMessage("Installing plugin: " + pPlugin->getName());

			m_vPlugin.push_back(pPlugin);

			// 安装插件
			pPlugin->install();
			// 初始化
			pPlugin->initialise();

			LogManager::getSingleton().logMessage("Plugin successfully installed");
		}	
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			System::uninstallPlugin(Plugin* pPlugin)
	{
		LogManager::getSingleton().logMessage("Uninstalling plugin: " + pPlugin->getName());
		VPlugin::iterator it = 
			std::find(m_vPlugin.begin(), m_vPlugin.end(), pPlugin);
		if (it != m_vPlugin.end())
		{
			pPlugin->shutdown();
			pPlugin->uninstall(); m_vPlugin.erase(it);
		}

		LogManager::getSingleton().logMessage("Plugin successfully uninstalled");
	}

	/**
	 *
	 */
	void			System::clearPlugin()
	{
		for (VDynlib::reverse_iterator it = m_vDynlib.rbegin(); 
			it != m_vDynlib.rend(); ++it)
		{
			DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");

			call();

			DynLibManager::getSingleton().unload(*it);

		}
		m_vDynlib.clear();

		for (VPlugin::reverse_iterator it = m_vPlugin.rbegin();
			it != m_vPlugin.rend(); ++it)
		{
			(*it)->uninstall();
		}

		m_vPlugin.clear();
	}
}