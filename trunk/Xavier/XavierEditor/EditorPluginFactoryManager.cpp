#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorPluginFactoryManager.h"
#include "EditorSceneManager.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
#include "EditorTerrainPage.h"

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
		"Factory/EditorTerrain",
		"Factory/EditorTerrainPage",
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
		registerEditorPluginFactory(
			new EditorTerrrainFactory(EditorPluginFoctoryName[EPF_TERRAIN])
			);
		registerEditorPluginFactory(
			new EditorTerrainPageFactory(EditorPluginFoctoryName[EPF_TERRAINPAGE])
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
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Deleted this plugin factory :  " + it->second->getName());

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
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Register editor plugin factory : " + pFactory->getName());

			m_HashMapEditorPluginFactory.insert(
				HashMapEditorPluginFactory::value_type(pFactory->getName(), pFactory)
				);
			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin factory has been exist : " + pFactory->getName());	
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
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin factory can not be found :  " + factoryName);
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
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Deleted this plugin factory :  " + factoryName);

			delete it->second; m_HashMapEditorPluginFactory.erase(it);
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin factory can not be found :  " + factoryName);
		}	
	}
}