#include "GuardiolaDllExport.h"
#include "Singleton.h"
#include "PyEvtSet.h"
#include "Server.h"
#include "System.h"

namespace Barcelona
{
	template<>	System*	Singleton<System>::msSingleton = 0;

	/** 获取系统单实例对象引用
	 *
	 * \return 
	 */
	System&		System::getSingleton()
	{
		assert(msSingleton != 0); return (*msSingleton);
	}

	/** 获取系统单实例对象指针
	 *
	 * \return 
	 */
	System*		System::getSingletonPtr()
	{
		assert(msSingleton != 0); return msSingleton;
	}

	/** 构造函数
	 *
	 * \param void 
	 * \return 
	 */
	System::System(void) : m_pRoot(NULL), m_pRenderWindow(NULL)
	{
	}

	/** 带参数的构造函数，直接构造系统对象
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	System::System(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName,
		bool bAutoCreateWindow) : m_pRoot(NULL), m_pRenderWindow(NULL)
	{
		create(pluginFileName, resourceFileName, bAutoCreateWindow);
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	System::~System(void)
	{
		destroy();
	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \return 
	 */
	bool				System::create(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName, bool bAutoCreateWindow)
	{
		m_pRoot = new Ogre::Root(pluginFileName);
		
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
		
		// 注册内部服务工厂
		registerServerFactory(new ServerFactory());

		// 事件发送器
		new Ogre::GlobalEventSet();

		return true;
	}

	/** 创建应用程序
	 *
	 * \param name 
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 * \return 
	 */
	void				System::createApplication(const Ogre::String& name, HWND hWnd,
		int w, int h, bool bFullScreen)
	{
		Ogre::NameValuePairList pm;
		pm["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(hWnd));

		/*
		* 创建渲染窗口
		*/
		m_pRenderWindow	= Ogre::Root::getSingletonPtr()->createRenderWindow(name,
			w, h, bFullScreen, &pm);

		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

		/*
		* 初始化默认资源组
		*/
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
		// 清理工厂和服务
		clearServerFactory();
		clearServer();
		
		// 删除事件发送器
		delete Ogre::GlobalEventSet::getSingletonPtr();

		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
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
#ifdef _DEBUG_LOG
			TKLogEvent("register server factory " + pFactory->getTypeName(), Ogre::LML_NORMAL);
#endif
			m_hashFactory.insert(HashServerFactory::value_type(pFactory->getTypeName(), pFactory));
		}
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ServerFactory*		System::getServerFactory(const Ogre::String& typeName)
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
#ifdef _DEBUG_LOG
			TKLogEvent("unregister server factory " + pFactory->getTypeName(), Ogre::LML_NORMAL);
#endif
			delete it->second; m_hashFactory.erase(it);
		}
	}

	/**
	 *
	 * \param typeName 
	 */
	void				System::unregisterServerFactory(const Ogre::String& typeName)
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
#ifdef _DEBUG_LOG
			TKLogEvent("unregister server factory " + it->second->getTypeName(), Ogre::LML_NORMAL);
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
#ifdef _DEBUG_LOG
				TKLogEvent("add server [" + pServer->getTypeName() + "]", Ogre::LML_NORMAL);
#endif
				m_vServer.push_back(pServer);

				return true;
			}
			else
			{
#ifdef _DEBUG_LOG
				TKLogEvent("error " + pServer->getTypeName() + "isexit", Ogre::LML_CRITICAL);
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
	Server*			System::getServer(const Ogre::String& typeName)
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
#ifdef _DEBUG_LOG
			TKLogEvent("delete server [" + pServer->getTypeName() + "]", Ogre::LML_NORMAL);
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
#ifdef _DEBUG_LOG
			TKLogEvent("delete server [" + pServer->getTypeName() + "] ", Ogre::LML_NORMAL);
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
