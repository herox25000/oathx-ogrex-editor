#include "OgreEditorCoreStdAfx.h"
#include "OgreGlobalEventSet.h"
#include "OgreEditorSystem.h"
#include "OgreDynLibManager.h"
#include "OgrePlugin.h"
#include "OgreDynLib.h"

namespace Ogre
{
	template<>	EditorSystem*	Singleton<EditorSystem>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorSystem&		EditorSystem::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorSystem*		EditorSystem::getSingletonPtr()
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
	EditorSystem::EditorSystem()
		: m_pRoot(NULL), m_pRenderWindow(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorSystem::~EditorSystem()
	{

	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	bool		EditorSystem::createEditorSystem(const String& pluginFileName, const String& resourceFileName,
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
		 *	创建渲染系统
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

		rsys->setConfigOption( "VSync", "Yes" );
		rsys->setConfigOption( "Full Screen", "No" );
		rsys->setConfigOption("FSAA", "2");
		m_pRoot->setRenderSystem( rsys );
		
		// create render window
		m_pRoot->initialise(bAutoCreateWindow);

		new GlobalEventSet();
		new EditorPluginFactoryManager();
		new EditorPluginManager("Ogre.world");
		
		return true;
	}

	/**
	 *
	 */
	void		EditorSystem::drawFrame()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void		EditorSystem::clearUp()
	{
		delete EditorPluginManager::getSingletonPtr();
		delete EditorPluginFactoryManager::getSingletonPtr();
		delete GlobalEventSet::getSingletonPtr();

		clearPlugin();

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
	bool			EditorSystem::createRenderWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen)
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
	RenderWindow*	EditorSystem::getRenderWindow() const
	{
		return m_pRenderWindow;
	}

	/**
	 *
	 * \param name 
	 */
	void			EditorSystem::loadPlugin(const String& name)
	{
		DynLib* pLib = DynLibManager::getSingleton().load(name);
		if (pLib != NULL)
		{
			m_vDynlibRegister.push_back(pLib);

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
	void			EditorSystem::unloadPlugin(const String& name)
	{
		for (DynlibRegister::iterator it=m_vDynlibRegister.begin();
			it!=m_vDynlibRegister.end(); it++)
		{
			if ( (*it)->getName() == name)
			{
				DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
				if (!call)
					OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Cannot find symbol dllStopPlugin in library " + name,
					"AppEdit::unloadPlugin");

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
	void			EditorSystem::installPlugin(Plugin* pPlugin)
	{
		if (pPlugin != NULL)
		{
			LogManager::getSingleton().logMessage("Installing plugin: " + pPlugin->getName());

			m_vPluginRegister.push_back(pPlugin);

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
	void			EditorSystem::uninstallPlugin(Plugin* pPlugin)
	{
		LogManager::getSingleton().logMessage("Uninstalling plugin: " + pPlugin->getName());
		PluginRegister::iterator it = 
			std::find(m_vPluginRegister.begin(), m_vPluginRegister.end(), pPlugin);
		if (it != m_vPluginRegister.end())
		{
			pPlugin->shutdown();
			pPlugin->uninstall(); m_vPluginRegister.erase(it);
		}

		LogManager::getSingleton().logMessage("Plugin successfully uninstalled");
	}

	/**
	 *
	 */
	void			EditorSystem::clearPlugin()
	{
		for (DynlibRegister::reverse_iterator it = m_vDynlibRegister.rbegin(); 
			it != m_vDynlibRegister.rend(); ++it)
		{
			DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");

			call();

			DynLibManager::getSingleton().unload(*it);

		}
		m_vDynlibRegister.clear();

		for (PluginRegister::reverse_iterator it = m_vPluginRegister.rbegin();
			it != m_vPluginRegister.rend(); ++it)
		{
			(*it)->uninstall();
		}

		m_vPluginRegister.clear();
	}
}