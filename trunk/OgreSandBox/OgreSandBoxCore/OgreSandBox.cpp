#include "stdafx.h"
#include "OgreSandBox.h"

namespace Ogre
{
	template<>	SandBox*	Singleton<SandBox>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	SandBox&		SandBox::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	SandBox*		SandBox::getSingletonPtr()
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
	SandBox::SandBox()
		: m_pRoot(NULL), m_pWindow(NULL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	SandBox::~SandBox()
	{

	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	bool			SandBox::createSandBox(const String& pluginFileName, const String& resourceFileName,
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
		m_pRoot->setRenderSystem( rsys );
		
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
	void			SandBox::go()
	{
		// draw frame
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void			SandBox::clearUp()
	{
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
	 * \param name 
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 * \return 
	 */
	bool			SandBox::createWindow(const String& name, HWND hWnd, int w, int h,
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
	RenderWindow*	SandBox::getWindow() const
	{
		return m_pWindow;
	}

	/**
	 *
	 * \param name 
	 */
	void			SandBox::loadPlugin(const String& name)
	{
		DynLib* pLib = DynLibManager::getSingleton().load(name);
		if (pLib != NULL)
		{
			m_vDynlibRegister.push_back(pLib);

			DLLPluginStart call = (DLLPluginStart)pLib->getSymbol("dllStartPlugin");

			if (!call)
				OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStartPlugin in library " + name,
				"SandBox::loadPlugin");

			call();
		}
	}

	/**
	 *
	 * \param name 
	 */
	void			SandBox::unloadPlugin(const String& name)
	{
		for (DynlibRegister::iterator it=m_vDynlibRegister.begin();
			it!=m_vDynlibRegister.end(); it++)
		{
			if ( (*it)->getName() == name)
			{
				DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
				if (!call)
					OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStopPlugin in library " + name,
					"SandBox::unloadPlugin");

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
	void			SandBox::installPlugin(Plugin* pPlugin)
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
	void			SandBox::uninstallPlugin(Plugin* pPlugin)
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
	void			SandBox::destoryAllPlugin()
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
}