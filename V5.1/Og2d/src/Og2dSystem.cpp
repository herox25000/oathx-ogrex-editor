#include "Og2dSystem.h"
#include "Og2dDebug.h"
#include "Og2dLogManager.h"
#include "Og2dDynlibManager.h"
#include "Og2dInputManager.h"
#include "Og2dPlugin.h"
#include "Og2dRenderSystem.h"
#include "Og2dSceneFactory.h"
#include "Og2dSceneNodeFactoryManager.h"
#include "Og2dException.h"

namespace Og2d
{
	template<>	System*	Singleton<System>::mpSingleton = 0;
	/**
	 *
	 * \return 
	 */
	System&		System::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	System*		System::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}

	// 插件启动接口
	typedef void (*DLLPluginStart)(void);
	// 插件关闭接口
	typedef void (*DLLPluginStop)(void);

	/**
	 *
	 * \return 
	 */
	System::System() : m_pRenderSystem(NULL), m_pWorld(NULL)
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
	 * \param szPlginFile 
	 * \param szLogFile 
	 * \return 
	 */
	bool			System::startup(const String& szPlginFile, const String& szLogFile, 
		const StringValue& Value)
	{
		// construct dynlib manager object
		new DynlibManager();
		// construct log manager
		new LogManager(szLogFile, true);
		// construct
		new InputManager();
		// scene node
		new SceneNodeFactoryManager();

		// read plugin config file
		std::fstream stream;
		stream.open(szPlginFile.c_str());
		
		if (stream.is_open())
		{
			char szTmp[512];
			while (!stream.eof())
			{
				// get config line, plugin name
				stream.getline(szTmp, 512, '\n');
				if (szTmp[0] != '\n' && szTmp[0] != '\0')
				{
					// load a plugin
					loadPlugin(szTmp);
				}
			}
		}
		else
		{
			tryException(EC_FILE_NOT_FOUND, "Can't found file" + szPlginFile,
				"System::startup");
		}
	
		// render sytem value params
		bool bScreen	=	0;
		int	 w			=	800;
		int	 h			=   600;
		bool bVsvy		=	true;

		// String Converter bool
		StringValue::const_iterator it_bool = Value.find("FULLSCREEN");
		if ( it_bool != Value.end() )
			bScreen = StringUtil::ToBOOL(it_bool->second);

		// String Converter w
		StringValue::const_iterator it_w	= Value.find("W");
		if ( it_w != Value.end() )
			w = StringUtil::ToUINT(it_w->second);

		// String Converter h
		StringValue::const_iterator it_h	= Value.find("H");
		if ( it_w != Value.end() )
			h = StringUtil::ToUINT(it_h->second);

		// String Converter h
		StringValue::const_iterator it_vsvy = Value.find("VSVY");
		if ( it_vsvy != Value.end() )
			bVsvy = StringUtil::ToBOOL(it_vsvy->second);

		// if current platform is WIN32 then set default render sytem (Direct3D9 Render System)
#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32
		for (MapRenderSystem::iterator it = m_vRenderSystem.begin();
			it!=m_vRenderSystem.end(); it++)
		{
			// if find Direct3D9 Render System
			if (it->second->getTypeName() == "Direct3D9 Render System")
			{
				// define win32 window handle
				HWND hWnd		=	NULL;
				
				// String Converter HWND
				StringValue::const_iterator it_hwnd = Value.find("HWND");
				if ( it_hwnd != Value.end() )
					hWnd = (HWND)(StringUtil::ToUINT(it_hwnd->second));

				/*
				*  create Direct3D9 Render System griaphics device
				*/
				if (it->second->createGriaphicsDevice(hWnd, bScreen, 
					Size(w, h), bVsvy))
				{
					// apply d3d9 render system
					setRenderSystem(it->second);
				}
			}
		}
#endif
		return true;
	}

	/**
	 *
	 */
	void			System::shutdown()
	{
		clearSceneFactory();
		destroyWorld();
		// clear all plugin
		clearPlugin();

		// delete singleton pointer
		DynlibManager* pDynlibMgr = DynlibManager::getSingletonPtr();
		SAFE_DELETE(pDynlibMgr);

		// delete input manager
		InputManager* pInputManager = InputManager::getSingletonPtr();
		SAFE_DELETE(pInputManager);

		// delete scene node manager
		SceneNodeFactoryManager* pSceneNodeFactoryManager = SceneNodeFactoryManager::getSingletonPtr();
		SAFE_DELETE(pSceneNodeFactoryManager);

		// delete log manager
		LogManager* pLogMgr = LogManager::getSingletonPtr();
		SAFE_DELETE(pLogMgr);
	}

	/** add a new render sytem object to manager
	 *
	 * \param pRenderSystem 
	 */
	void			System::addRenderSystem(RenderSystem* pRenderSystem)
	{
		MapRenderSystem::iterator it = m_vRenderSystem.find(pRenderSystem->getTypeName());
		if ( it == m_vRenderSystem.end() )
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"add render sytem : " + pRenderSystem->getTypeName());
			
			// insert to manager
			m_vRenderSystem.insert(MapRenderSystem::value_type(
				pRenderSystem->getTypeName(), pRenderSystem)
				);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	RenderSystem*	System::getRenderSystem(const String& name)
	{
		MapRenderSystem::iterator it = m_vRenderSystem.find(name);
		if ( it != m_vRenderSystem.end() )
			return it->second;
	
		return NULL;
	}


	/**
	 *
	 * \param pRenderSystem 
	 */
	void			System::removeRenderSystem(RenderSystem* pRenderSystem)
	{
		MapRenderSystem::iterator it = m_vRenderSystem.find(pRenderSystem->getTypeName());
		if ( it != m_vRenderSystem.end() )
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"remove render sytem : " + pRenderSystem->getTypeName());

			// delete render system
			SAFE_DELETE(it->second); m_vRenderSystem.erase(it);
		}
	}

	/**
	 *
	 * \param pRenderSystem 
	 */
	void			System::setRenderSystem(RenderSystem* pRenderSystem)
	{
		if (pRenderSystem)
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"select render sytem : " + pRenderSystem->getTypeName());

			m_pRenderSystem = pRenderSystem;

		}
	}

	/**
	 *
	 * \return 
	 */
	RenderSystem*	System::getRenderSystem() const
	{
		return m_pRenderSystem;
	}

	/**
	 *
	 */
	bool			System::run(float fElapsed)
	{
		// if no current rendersystem object then return
		if (!m_pRenderSystem)
			return 0;
		
		// begin render
		m_pRenderSystem->beginScene();
		
		if (m_pWorld)
			m_pWorld->update(fElapsed);

		// end render
		m_pRenderSystem->endScene();
		
		return true;
	}

	/** add scene factory
	 *
	 * \param pFactory 
	 * \return 
	 */
	void			System::addSceneFactory(SceneFactory* pFactory)
	{
		MapSceneFactory::iterator it = m_vSceneFactory.find(pFactory->getTypeName());
		if ( it == m_vSceneFactory.end() )
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"add scene factory : " + pFactory->getTypeName());

			// insert scene factory to map
			m_vSceneFactory.insert(
				MapSceneFactory::value_type(pFactory->getTypeName(),
				pFactory));
		}
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	SceneFactory*	System::getSceneFactory(const String& szName)
	{
		MapSceneFactory::iterator it = m_vSceneFactory.find(szName);
		if ( it != m_vSceneFactory.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void			System::removeFactory(SceneFactory* pFactory)
	{
		MapSceneFactory::iterator it = m_vSceneFactory.find(pFactory->getTypeName());
		if ( it != m_vSceneFactory.end() )
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"remove scene factory : " + pFactory->getTypeName());

			SAFE_DELETE(it->second); m_vSceneFactory.erase(it);
		}
	}

	/**
	 *
	 */
	void			System::clearSceneFactory()
	{
		MapSceneFactory::iterator it = m_vSceneFactory.begin();
		while ( it != m_vSceneFactory.end() )
		{
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"remove scene factory : " + it->second->getTypeName());

			delete it->second; it != m_vSceneFactory.erase(it);
		}
	}

	/**
	 *
	 * \param szName 
	 * \param vOrigin 
	 * \return 
	 */
	World*			System::createWorld(const String& szName, const Vector2D& vPos, WorldMask mask)
	{
		try
		{
			if (m_pWorld)
			{
				tryException(EC_RT_ASSERTION_FAILED, "Can't create world", 
				"System::createWorld")
			}
			else
			{
				// create world object
				m_pWorld = new World(szName);
			}
		}
		catch (Exception& e)
		{
			LogManager::getSingleton().logMessage(INFO_WARNING,
				e.getFullDescription());
		}

		return m_pWorld;
	}

	/**
	 *
	 */
	void			System::destroyWorld()
	{
		SAFE_DELETE(m_pWorld);
	}

	/**
	 *
	 * \param name 
	 */
	void			System::loadPlugin(const String& name)
	{
		DynLib* pLib = DynlibManager::getSingleton().load(name);
		if (pLib != NULL)
		{
			// save object
			m_vDynlib.push_back(pLib);
			
			// get plugin export function, the export function name must be dllStartPlugin
			DLLPluginStart call = (DLLPluginStart)pLib->getSymbol("dllStartPlugin");

			// execption
			if (!call)
				tryException(EC_ITEM_NOT_FOUND, "Cannot find symbol dllStartPlugin in library " + name,
				"System::loadPlugin");

			// execture dllStartPlugin
			call();

			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"load plugin  : " + name);
		}
	}

	/** unload plugin
	 *
	 * \param name 
	 */
	void			System::unloadPlugin(const String& name)
	{
		// find plugin
		for (VectorDynlib::iterator it=m_vDynlib.begin();
			it!=m_vDynlib.end(); it++)
		{
			if ( (*it)->getName() == name)
			{
				// get plugin export function, the function name is "dllStopPlugin"
				DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");
				if (!call)
					tryException(EC_ITEM_NOT_FOUND, "Cannot find symbol dllStopPlugin in library " + name,
					"System::unloadPlugin");

				// execute export function
				call();

				LogManager::getSingleton().logMessage(INFO_NORMAL,
					"unload plugin  : " + name);

				// unload plugin dynlib
				DynlibManager::getSingleton().unload(*it); m_vDynlib.erase(it);

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
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"install plugin : " + pPlugin->getTypeName());

			// install plugin, save plugin to vector
			pPlugin->install(); m_vPlugin.push_back(pPlugin);
		}	
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			System::uninstallPlugin(Plugin* pPlugin)
	{
		VectorPlugin::iterator it = 
			std::find(m_vPlugin.begin(), m_vPlugin.end(), pPlugin);
		if (it != m_vPlugin.end())
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"uninstall plugin : " + pPlugin->getTypeName());

			pPlugin->uninstall(); m_vPlugin.erase(it);
		}
	}

	/**
	 *
	 */
	void			System::clearPlugin()
	{
		// clera all plugin dynlib object
		for (VectorDynlib::reverse_iterator it = m_vDynlib.rbegin(); 
			it != m_vDynlib.rend(); ++it)
		{
			DLLPluginStop call = (DLLPluginStop)(*it)->getSymbol("dllStopPlugin");

			call();

			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL,
				"unload dynlib : " + (*it)->getName());

			DynlibManager::getSingleton().unload(*it);
		}
		m_vDynlib.clear();
	}
}