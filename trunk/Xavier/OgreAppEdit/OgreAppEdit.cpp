#include "OgreAppEditPrerequisites.h"
#include "OgreAppEdit.h"
#include "OgreEditorPlugin.h"
#include "OgreDynLib.h"
#include "OgreDynLibManager.h"
#include "OgreGlobalEventSet.h"
#include "OgreRenderWindowEditor.h"
#include "OgreSceneManagerEditor.h"
#include "OgreCameraEditor.h"
#include "OgreViewPortEditor.h"
#include "OgreGridEditor.h"
#include "OgreXMLSerializeEditor.h"


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
		:m_pRoot(NULL), m_pRenderWindow(NULL)
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
		 *	������Ⱦϵͳ
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
		
		// ����������
		m_pRoot->initialise(false);

		// ע������༭����
		registerEditorFactory(new RenderWindowEditorFactory());
		registerEditorFactory(new SceneManagerEditorFactory());
		registerEditorFactory(new CameraEditorFactory());
		registerEditorFactory(new ViewPortEditorFactory());
		registerEditorFactory(new XMLSerializeEditorFactory());
		registerEditorFactory(new GridEditorFactory());
		
		//
		new GlobalEventSet();
	
		return true;
	}

	/**
	 *
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScree 
	 */
	void		AppEdit::createRenderWindow(HWND hWnd, int w, int h, bool bFullScreen)
	{
		NameValuePairList pm;
		pm[KER_HANDLE_WINDOW] = StringConverter::toString((size_t)(hWnd));
		m_pRenderWindow	= Root::getSingletonPtr()->createRenderWindow(XAVIER_WINDOW_NAME, w,
			h, bFullScreen, &pm);
		assert(m_pRenderWindow != NULL);

		TextureManager::getSingleton().setDefaultNumMipmaps(5);
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	AppEdit::getRenderWindow() const
	{
		return m_pRenderWindow;
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
			StringEditorFactory::iterator it = m_Factory.find(pFactory->getTypeName());
			if ( it == m_Factory.end() )
			{
				m_Factory.insert(StringEditorFactory::value_type(pFactory->getTypeName(), pFactory));
				return true;
			}
			else
			{
				TKLogEvent("�Ѽ��� �༭����:" + pFactory->getTypeName() + " �Ѵ���", LML_TRIVIAL);
			}
		}

		return 0;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void		AppEdit::unregisterEditorFactory(BaseEditorFactory* pFactory)
	{
		if (pFactory != NULL)
		{
			StringEditorFactory::iterator it = m_Factory.find(pFactory->getTypeName());
			if ( it != m_Factory.end() )
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("��ж�� �༭����:" + pFactory->getTypeName(), LML_TRIVIAL);
#endif
				delete it->second; m_Factory.erase(it);
			}
		}
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	BaseEditorFactory*	AppEdit::getEditorFactory(const String& typeName)
	{
		StringEditorFactory::iterator it = m_Factory.find(typeName);
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
			for (VEditor::iterator it=m_vEditor.begin(); 
				it!=m_vEditor.end(); it++)
			{
				if ((*it)->getTypeName() == pEditor->getTypeName())
				{
#ifdef _OUTPUT_LOG
					TKLogEvent("�ظ����� �༭�� " + pEditor->getTypeName(), LML_TRIVIAL);
#endif
					return 0;
				}
			}

#ifdef _OUTPUT_LOG
			TKLogEvent("�Ѽ��� �༭�� " + pEditor->getTypeName(), LML_NORMAL);
#endif
			m_vEditor.push_back(pEditor);
			
			return true;
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
		for (size_t i=0; i<m_vEditor.size(); i++)
		{
			if (m_vEditor[i]->getTypeName() == typeName)
				return m_vEditor[i];
		}

		return NULL;
	}

	/**
	 *
	 * \param pEditor 
	 */
	void		AppEdit::delEditor(BaseEditor* pEditor)
	{
		if (pEditor != NULL)
		{
			for (VEditor::iterator it=m_vEditor.begin(); 
				it!=m_vEditor.end(); it++)
			{
				if ((*it)->getTypeName() == pEditor->getTypeName())
				{
#ifdef _OUTPUT_LOG
					TKLogEvent("��ж�� �༭�� " + pEditor->getTypeName(), LML_NORMAL);
#endif
					delete (*it); it = m_vEditor.erase(it); 
					
					break;
				}
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	int			AppEdit::getEditorCount()
	{
		return m_vEditor.size();
	}

	/**
	 *
	 * \param index 
	 * \return 
	 */
	BaseEditor*	AppEdit::getEditor(int index)
	{
		return m_vEditor[index];
	}

	/**
	 *
	 * \param typeName 
	 */
	void		AppEdit::delEditor(const String& typeName)
	{
		delEditor(getEditor(typeName));
	}

	/**
	 * ����ɾ��
	 */
	void		AppEdit::clearEditor()
	{
		while(m_vEditor.size())
		{
			BaseEditor* pEditor = m_vEditor.back();
			if (pEditor == NULL)
				break;
#ifdef _OUTPUT_LOG
			TKLogEvent("��ж�� �༭�� " + pEditor->getTypeName(), LML_NORMAL);
#endif
			delete pEditor; m_vEditor.pop_back();		
		}
	}

	/**
	 *
	 * \param name 
	 */
	void		AppEdit::loadPlugin(const String& name)
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
	void		AppEdit::unloadPlugin(const String& name)
	{
		for (VDynLib::iterator it=m_vDynlib.begin();
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
	void		AppEdit::installPlugin(EditorPlugin* pPlugin)
	{
		if (pPlugin != NULL)
		{
			LogManager::getSingleton().logMessage("Installing plugin: " + pPlugin->getName());

			m_vPlugin.push_back(pPlugin);
			
			// ��װ���
			pPlugin->install();
			// ��ʼ��
			pPlugin->initialise();

			LogManager::getSingleton().logMessage("Plugin successfully installed");
		}
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void		AppEdit::uninstallPlugin(EditorPlugin* pPlugin)
	{
		LogManager::getSingleton().logMessage("Uninstalling plugin: " + pPlugin->getName());
		VEditorPlugin::iterator it = 
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
	void		AppEdit::clearPlugin()
	{
		for (VDynLib::reverse_iterator it = m_vDynlib.rbegin(); 
			it != m_vDynlib.rend(); ++it)
		{
			DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");

			call();

			DynLibManager::getSingleton().unload(*it);

		}
		m_vDynlib.clear();

		for (VEditorPlugin::reverse_iterator it = m_vPlugin.rbegin();
			it != m_vPlugin.rend(); ++it)
		{
			(*it)->uninstall();
		}

		m_vPlugin.clear();
	}

	/** destroy ogre edit system
	 *
	 */
	void		AppEdit::destroySystem()
	{
		clearPlugin();
		clearEditor();
		
		StringEditorFactory::iterator itFactory = m_Factory.begin();
		while( itFactory != m_Factory.end() )
		{	
			delete itFactory->second; itFactory = m_Factory.erase(itFactory);
		}

		delete GlobalEventSet::getSingletonPtr();

		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}
}
