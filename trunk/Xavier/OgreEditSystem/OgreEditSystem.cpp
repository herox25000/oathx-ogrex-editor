#include "OgreEditSystemPrerequisites.h"
#include "OgreEditSystem.h"
#include "OgreRenderWindowEditor.h"
#include "OgreSceneManagerEditor.h"
#include "OgreCameraEditor.h"
#include "OgreViewPortEditor.h"

namespace Ogre
{
	template<>	EditSystem*	Singleton<EditSystem>::msSingleton = NULL;
	EditSystem&		EditSystem::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	EditSystem*		EditSystem::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	EditSystem::EditSystem(void)
		:m_pRoot(NULL)
	{
		
	}

	/**	
	 *
	 * \param void 
	 * \return 
	 */
	EditSystem::~EditSystem(void)
	{
	}

	/** create ogre editor system
	 *
	 * \param sPluginConfigFileName 
	 * \param sResourceConfigFileName 
	 * \return 
	 */
	bool		EditSystem::createSystem(const String& pluginFileName, const String& resourceFileName)
	{
		m_pRoot = new Root(pluginFileName);
		assert(m_pRoot != NULL);

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
		m_pRoot->setRenderSystem( rsys );
		
		// 不创建窗口
		m_pRoot->initialise(false);

		// 注册基本编辑工具
		registerEditorFactory(new RenderWindowEditorFactory());
		registerEditorFactory(new SceneManagerEditorFactory());
		registerEditorFactory(new CameraEditorFactory());
		registerEditorFactory(new ViewPortEditorFactory());

		return true;
	}

	/**
	 *
	 */
	void		EditSystem::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 * \param pFactory 
	 * \return 
	 */
	bool		EditSystem::registerEditorFactory(BaseEditorFactory* pFactory)
	{
		if (pFactory != NULL)
		{
			StrEditorFactory::iterator it = m_Factory.find(pFactory->getTypeName());
			if ( it == m_Factory.end() )
			{
				m_Factory.insert(StrEditorFactory::value_type(pFactory->getTypeName(), pFactory));
				return true;
			}
		}

		return 0;
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	BaseEditorFactory*	EditSystem::getEditorFactory(const String& typeName)
	{
		StrEditorFactory::iterator it = m_Factory.find(typeName);
		if ( it != m_Factory.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param pEditor 
	 * \return 
	 */
	bool		EditSystem::addEditor(BaseEditor* pEditor)
	{
		if (pEditor != NULL)
		{
			StrEditor::iterator it = m_Editor.find(pEditor->getTypeName());
			if ( it == m_Editor.end() )
			{
				m_Editor.insert(StrEditor::value_type(pEditor->getTypeName(), pEditor));
				return true;
			}
		}

		return 0;
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	BaseEditor*	EditSystem::getEditor(const String& typeName)
	{
		StrEditor::iterator it = m_Editor.find(typeName);
		if ( it != m_Editor.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param pEditor 
	 */
	void		EditSystem::delEditor(BaseEditor* pEditor)
	{
		StrEditor::iterator it = m_Editor.find(pEditor->getTypeName());
		if ( it != m_Editor.end() )
		{
			delete it->second; it = m_Editor.erase(it);
		}
	}

	/** destroy ogre edit system
	 *
	 */
	void		EditSystem::destroySystem()
	{
		StrEditor::iterator itEitor = m_Editor.begin();
		while( itEitor != m_Editor.end() )
		{
			delete itEitor->second; itEitor = m_Editor.erase(itEitor);
		}

		StrEditorFactory::iterator itFactory = m_Factory.begin();
		while( itFactory != m_Factory.end() )
		{	
			delete itFactory->second; itFactory = m_Factory.erase(itFactory);
		}

		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}
}
