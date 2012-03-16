#include "OgreAppEditPrerequisites.h"
#include "OgreAppEdit.h"
#include "OgreRenderWindowEditor.h"
#include "OgreSceneManagerEditor.h"
#include "OgreCameraEditor.h"
#include "OgreViewPortEditor.h"

namespace Ogre
{
	template<>	AppEdit*	Singleton<AppEdit>::msSingleton = NULL;
	AppEdit&		AppEdit::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	AppEdit*		AppEdit::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	AppEdit::AppEdit(void)
		:m_pRoot(NULL)
	{
		
	}

	/**	
	 *
	 * \param void 
	 * \return 
	 */
	AppEdit::~AppEdit(void)
	{
	}

	/** create ogre editor system
	 *
	 * \param sPluginConfigFileName 
	 * \param sResourceConfigFileName 
	 * \return 
	 */
	bool		AppEdit::createSystem(const String& pluginFileName, const String& resourceFileName)
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
	void		AppEdit::update()
	{
		m_pRoot->renderOneFrame();
	}

	/**
	 *
	 * \param pFactory 
	 * \return 
	 */
	bool		AppEdit::registerEditorFactory(BaseEditorFactory* pFactory)
	{
		if (pFactory != NULL)
		{
			StrEditorFactory::iterator it = m_Factory.find(pFactory->getTypeName());
			if ( it == m_Factory.end() )
			{
				m_Factory.insert(StrEditorFactory::value_type(pFactory->getTypeName(), pFactory));
				return true;
			}
			else
			{
				TKLogEvent("编辑工厂:" + pFactory->getTypeName() + " 已存在", LML_TRIVIAL);
			}
		}

		return 0;
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	BaseEditorFactory*	AppEdit::getEditorFactory(const String& typeName)
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
	bool		AppEdit::addEditor(BaseEditor* pEditor)
	{
		if (pEditor != NULL)
		{
			StrEditor::iterator it = m_Editor.find(pEditor->getTypeName());
			if ( it == m_Editor.end() )
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("添加编辑器:" + pEditor->getTypeName() + " OK", LML_NORMAL);
#endif
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
	BaseEditor*	AppEdit::getEditor(const String& typeName)
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
	void		AppEdit::delEditor(BaseEditor* pEditor)
	{
		StrEditor::iterator it = m_Editor.find(pEditor->getTypeName());
		if ( it != m_Editor.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("删除编辑器:" + pEditor->getTypeName() + " OK", LML_NORMAL);
#endif
			delete it->second; it = m_Editor.erase(it);
		}
	}

	/** destroy ogre edit system
	 *
	 */
	void		AppEdit::destroySystem()
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
