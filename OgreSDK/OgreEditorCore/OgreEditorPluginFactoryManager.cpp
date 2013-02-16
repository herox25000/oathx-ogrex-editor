#include "OgreEditorCoreStdAfx.h"
#include "OgreEditorPluginFactoryManager.h"

namespace Ogre
{
	template<>	EditorPluginFactoryManager*	Singleton<EditorPluginFactoryManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorPluginFactoryManager&	EditorPluginFactoryManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginFactoryManager*	EditorPluginFactoryManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	static const String		EditorPluginFoctoryName[]= {
		"Factory/EditorSceneManager",
		"Factory/EditorCamera",
		"Factory/EditorViewport",
		"Factory/EditorTerrainGroup",
	};

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \return 
	 */
	EditorPluginFactoryManager::EditorPluginFactoryManager()
	{
		registerEditorPluginFactory(
			new EditorSceneManagerFactory(EditorPluginFoctoryName[EPF_SCENEMANAGER])
			);
		registerEditorPluginFactory(
			new EditorCameraFactory(EditorPluginFoctoryName[EPF_CAMERA])
			);
		registerEditorPluginFactory(
			new EditorViewportFactory(EditorPluginFoctoryName[EPF_VIEWPORT])
			);
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginFactoryManager::~EditorPluginFactoryManager()
	{
		HashMapEditorPluginFactory::iterator it = m_HashMapEditorPluginFactory.begin();
		while ( it != m_HashMapEditorPluginFactory.end() )
		{
			LogManager::getSingleton().logMessage("Deleted this plugin factory :  " + it->second->getName(), 
				LML_NORMAL);

			delete it->second; it = m_HashMapEditorPluginFactory.erase(it);
		}
	}

	/**
	 *
	 * \param pFactory 
	 * \return 
	 */
	bool					EditorPluginFactoryManager::registerEditorPluginFactory(EditorPluginFactory* pFactory)
	{
		HashMapEditorPluginFactory::iterator it = m_HashMapEditorPluginFactory.find(pFactory->getName());
		if ( it == m_HashMapEditorPluginFactory.end() )
		{
			LogManager::getSingleton().logMessage("Register editor plugin factory : " + pFactory->getName(), 
				LML_NORMAL);

			m_HashMapEditorPluginFactory.insert(
				HashMapEditorPluginFactory::value_type(pFactory->getName(), pFactory)
				);
			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage("This plugin factory has been exist : " + pFactory->getName(), 
				LML_CRITICAL);	
		}

		return 0;
	}

	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorPluginFactory*	EditorPluginFactoryManager::getEditorPluginFactory(const String& factoryName)
	{
		HashMapEditorPluginFactory::iterator it = m_HashMapEditorPluginFactory.find(factoryName);
		if ( it != m_HashMapEditorPluginFactory.end() )
		{
			return it->second;	
		}
		else
		{
			LogManager::getSingleton().logMessage("This plugin factory can not be found :  " + factoryName,
				LML_CRITICAL);
		}

		return NULL;
	}

	/**
	 *
	 * \param nType 
	 * \return 
	 */
	EditorPluginFactory*	EditorPluginFactoryManager::getEditorPluginFactory(const int nType)
	{
		return getEditorPluginFactory(EditorPluginFoctoryName[nType]);
	}

	/**
	 *
	 * \param factoryName 
	 */
	void					EditorPluginFactoryManager::unregisterEditorPluginFactory(const String& factoryName)
	{
		HashMapEditorPluginFactory::iterator it = m_HashMapEditorPluginFactory.find(factoryName);
		if ( it != m_HashMapEditorPluginFactory.end() )
		{
			LogManager::getSingleton().logMessage("Deleted this plugin factory :  " + factoryName,
				LML_NORMAL);

			delete it->second; m_HashMapEditorPluginFactory.erase(it);
		}
		else
		{
			LogManager::getSingleton().logMessage("This plugin factory can not be found :  " + factoryName, 
				LML_CRITICAL);
		}	
	}
}