#include "stdafx.h"
#include "OgreScheme.h"
#include "OgreWorldServer.h"
#include "OgreSystem.h"

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

	// plugin export
	typedef void (*DLLPluginStart)(void);
	typedef void (*DLLPluginStop)(void);

	/**
	 *
	 * \return 
	 */
	System::System()
		: m_pRoot(NULL), m_pWindow(NULL), m_pGlobalEventSet(NULL), m_pScheme(NULL)
	{
		m_pGlobalEventSet = new GlobalEventSet();
	}

	/**
	 *
	 * \return 
	 */
	System::~System()
	{
		if (m_pGlobalEventSet)
		{
			delete m_pGlobalEventSet;
			m_pGlobalEventSet = NULL;
		}

		clearUp();
	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	bool			System::createSystem(const String& pluginFileName, const String& resourceFileName,
		bool bAutoCreateWindow)
	{
		// constructor ogre root object
		m_pRoot = new Root(pluginFileName);
		
		// load ogre resource config file
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

				// add ogre resource group
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}

		/*
		 *	create render system, default direct3d9.0c device
		 */
		Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
		while(pRend != m_pRoot->getAvailableRenderers().end())
		{
			Ogre::String rName = (*pRend)->getName();
			if (rName == "Direct3D9 Rendering Subsystem")
				break;

			pRend++;
		}

		Ogre::RenderSystem *rsys = *pRend;

		rsys->setConfigOption("VSync",			"Yes" );
		rsys->setConfigOption("Full Screen",	"No" );
		rsys->setConfigOption("FSAA",			"2");

		// set render system
		m_pRoot->setRenderSystem( rsys );
		
		// register server factory
		registerServerFactory(new TemplateServerFactory<Scheme>());
		registerServerFactory(new TemplateServerFactory<WorldServer>());
		
		// create render window
		m_pWindow = m_pRoot->initialise(bAutoCreateWindow);
		if (m_pWindow)
		{
			try{
				std::fstream plg;
#ifdef _DEBUG
				plg.open("SandBoxPlugin_d.win32");
#else
				plg.open("SandBoxPlugin.win32");
#endif
				if (plg.is_open())
				{
					char szName[1024];

					// read plugin config file, load plugin
					while(!plg.eof())
					{	
						plg.getline(szName, 1024, '\n');
						if (strlen(szName))
						{
							loadPlugin(szName);
						}
					}
					
					// initiallse all plugin
					for (size_t i=0; i<m_vPluginRegister.size(); i++)
					{
						m_vPluginRegister[i]->initialise();
					}
				}
			}
			catch(Exception& e)
			{
				LogManager::getSingleton().logMessage(LML_CRITICAL, e.getFullDescription());
			}
		}

		return true;
	}

	/**
	 *
	 */
	void			System::go()
	{
		// draw frame
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void			System::clearUp()
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.begin();
		while( it != m_HashMapServerFactory.end() )
		{
			TKLogEvent("Unregister server factory: " + it->second->getTypeName());

			delete it->second; it = m_HashMapServerFactory.erase(it);
		}

		// destroy scheme
		destroyScheme();

		// destory all sand box plugin
		destoryAllPlugin();

		// destroy root object
		if (m_pRoot != NULL)
		{
			delete m_pRoot;
			m_pRoot = NULL;
		}
	}

	/**
	 *
	 * \param szName 
	 * \param adp 
	 * \return 
	 */
	bool			System::createScheme(const String& szName, const SSchemeAdp& adp)
	{
		ServerFactory* pFactory = getServerFactory(Scheme::ServerTypeName);
		if (pFactory)
		{
			if (m_pScheme != NULL)
			{
				delete m_pScheme;
				m_pScheme = NULL;
			}
			
			m_pScheme = static_cast<Scheme*>(pFactory->createServer(0, szName, adp, NULL));
			if (m_pScheme)
			{
				TKLogEvent("create scheme : " + szName);
				return true;
			}
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Scheme*			System::getScheme() const
	{
		return m_pScheme;
	}

	/**
	 *
	 */
	void			System::destroyScheme()
	{
		if (m_pScheme)
		{
			delete m_pScheme;
			m_pScheme = NULL;
		}
	}

	/**
	 *
	 * \param name 
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 * \return 
	 */
	bool			System::createWindow(const String& name, HWND hWnd, int w, int h,
		bool bFullScreen)
	{
		// save win32 window hande
		NameValuePairList pm;
		pm["externalWindowHandle"] = StringConverter::toString((size_t)(hWnd));

		/*
		* create render window
		*/
		m_pWindow	= Root::getSingletonPtr()->createRenderWindow(name,
			w, h, bFullScreen, &pm);
		if (m_pWindow == NULL)
			return 0;
	
		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		/*
		* initialise all default resource
		*/
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();	

		return true;
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	System::getWindow() const
	{
		return m_pWindow;
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
			m_vDynlibRegister.push_back(pLib);

			DLLPluginStart call = (DLLPluginStart)pLib->getSymbol("dllStartPlugin");

			if (!call)
				OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStartPlugin in library " + name,
				"System::loadPlugin");

			call();
		}
	}

	/**
	 *
	 * \param name 
	 */
	void			System::unloadPlugin(const String& name)
	{
		for (DynlibRegister::iterator it=m_vDynlibRegister.begin();
			it!=m_vDynlibRegister.end(); it++)
		{
			if ( (*it)->getName() == name)
			{
				DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
				if (!call)
					OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStopPlugin in library " + name,
					"System::unloadPlugin");

				call();

				DynLibManager::getSingleton().unload(*it); m_vDynlibRegister.erase(it);

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
			PluginRegister::iterator it = 
				std::find(m_vPluginRegister.begin(), m_vPluginRegister.end(), pPlugin);
			if (it != m_vPluginRegister.end())
			{
				LogManager::getSingleton().logMessage("Installing plugin: " + pPlugin->getName());
				m_vPluginRegister.push_back(pPlugin);

				// install resource
				pPlugin->install();

				LogManager::getSingleton().logMessage("Plugin successfully installed");
			}
		}	
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			System::uninstallPlugin(Plugin* pPlugin)
	{
		if (pPlugin)
		{
			LogManager::getSingleton().logMessage("Uninstalling plugin: " + pPlugin->getName());
			PluginRegister::iterator it = 
				std::find(m_vPluginRegister.begin(), m_vPluginRegister.end(), pPlugin);
			if (it != m_vPluginRegister.end())
			{
				// close plugin resource
				pPlugin->uninstall(); m_vPluginRegister.erase(it);
			}

			LogManager::getSingleton().logMessage("Plugin successfully uninstalled");
		}
	}

	/**
	 *
	 */
	void			System::destoryAllPlugin()
	{
		// initiallse all plugin
		for (size_t i=0; i<m_vPluginRegister.size(); i++)
		{
			m_vPluginRegister[i]->shutdown();
		}

		// stop all dynlib
		for (DynlibRegister::reverse_iterator it = m_vDynlibRegister.rbegin(); 
			it != m_vDynlibRegister.rend(); ++it)
		{
			DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
			
			call();

			DynLibManager::getSingleton().unload(*it);
		}
	}

	/**
	 *
	 * \param pServerFactory 
	 */
	void			System::registerServerFactory(ServerFactory* pServerFactory)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(pServerFactory->getTypeName());
		if ( it == m_HashMapServerFactory.end() )
		{
			TKLogEvent("Register server factory: " + pServerFactory->getTypeName());

			m_HashMapServerFactory.insert(
				HashMapServerFactory::value_type(pServerFactory->getTypeName(), pServerFactory)
				);
		}
	}

	/**
	 *
	 * \param tyepName 
	 * \return 
	 */
	ServerFactory*	System::getServerFactory(const String& tyepName)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(tyepName);
		if ( it != m_HashMapServerFactory.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param pServerFactory 
	 */
	void			System::unregisterServerFactory(ServerFactory* pServerFactory)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(pServerFactory->getTypeName());
		if ( it != m_HashMapServerFactory.end() )
		{
			TKLogEvent("Unregister server factory: " + pServerFactory->getTypeName());

			delete it->second; it = m_HashMapServerFactory.erase(it);
		}
	}
}