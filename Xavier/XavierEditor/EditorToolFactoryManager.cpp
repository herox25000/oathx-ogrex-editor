#include "StdAfx.h"
#include "EditorTool.h"
#include "EditorToolFactoryManager.h"
#include "EditorToolSceneManager.h"

namespace Ogre
{
	template<>	EditorToolFactoryManager*	Singleton<EditorToolFactoryManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorToolFactoryManager&		EditorToolFactoryManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorToolFactoryManager*		EditorToolFactoryManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	static const String EditorToolFactoryName[] = 
	{
		"EditorTool/SceneManager",
		"EditorTool/Terrain"
	};
	/**
	 *
	 * \param void 
	 * \return 
	 */
	EditorToolFactoryManager::EditorToolFactoryManager(void)
	{
		registerEditorToolFactory(new EditorToolSceneManagerFactory(EditorToolFactoryName[EDITOR_WORLD]));
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	EditorToolFactoryManager::~EditorToolFactoryManager(void)
	{
		HashMapEditorToolFactory::iterator it = m_HashMapEditorToolFactory.begin();
		while ( it != m_HashMapEditorToolFactory.end() )
		{
			delete it->second; it = m_HashMapEditorToolFactory.erase(it);
		}
	}
	
	/**
	 *
	 * \param pFactory 
	 */
	void				EditorToolFactoryManager::registerEditorToolFactory(EditorToolFactory* pFactory)
	{
		HashMapEditorToolFactory::iterator it = m_HashMapEditorToolFactory.find(pFactory->getName());
		if ( it == m_HashMapEditorToolFactory.end() )
		{
			m_HashMapEditorToolFactory.insert(
				HashMapEditorToolFactory::value_type(pFactory->getName(), pFactory)
				);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolFactory*	EditorToolFactoryManager::getEditorToolFactory(const String& name)
	{
		HashMapEditorToolFactory::iterator it = m_HashMapEditorToolFactory.find(name);
		if ( it != m_HashMapEditorToolFactory.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param nID 
	 * \return 
	 */
	EditorToolFactory*	EditorToolFactoryManager::getEditorToolFactory(const int nID)
	{
		HashMapEditorToolFactory::iterator it = m_HashMapEditorToolFactory.find(EditorToolFactoryName[nID]);
		if ( it != m_HashMapEditorToolFactory.end() )
		{
			return it->second;
		}

		return NULL;		
	}

	/**
	 *
	 * \param pFactory 
	 */
	void				EditorToolFactoryManager::unregisterEditorToolFactory(EditorToolFactory* pFactory)
	{
		HashMapEditorToolFactory::iterator it = m_HashMapEditorToolFactory.find(pFactory->getName());
		if ( it != m_HashMapEditorToolFactory.end() )
		{
			delete it->second; m_HashMapEditorToolFactory.erase(it);
		}
	}
}
