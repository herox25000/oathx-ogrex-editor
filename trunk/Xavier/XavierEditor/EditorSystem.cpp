#include "stdafx.h"
#include "EditorSystem.h"
#include "EditorPlugin.h"
#include "EditorPluginFactoryManager.h"
#include "EditorPluginManager.h"
#include "OgreGlobalEventSet.h"

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

		rsys->setConfigOption( "VSync", "No" );
		rsys->setConfigOption( "Full Screen", "No" );
		rsys->setConfigOption("FSAA", "2");
		m_pRoot->setRenderSystem( rsys );
		
		// create render window
		m_pRoot->initialise(bAutoCreateWindow);

		new GlobalEventSet();
		new EditorPluginFactoryManager();
		new EditorPluginManager("Xavier.world");

		return true;
	}

	/**
	 *
	 */
	void		EditorSystem::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 */
	void		EditorSystem::clearUp()
	{
		delete EditorPluginFactoryManager::getSingletonPtr();
		delete EditorPluginManager::getSingletonPtr();
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
}