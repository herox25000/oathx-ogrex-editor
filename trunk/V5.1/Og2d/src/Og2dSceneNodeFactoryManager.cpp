#include "Og2dSceneNodeFactoryManager.h"
#include "Og2dLogManager.h"

namespace Og2d
{
	template<>	SceneNodeFactoryManager*	Singleton<SceneNodeFactoryManager>::mpSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	SceneNodeFactoryManager*	SceneNodeFactoryManager::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}

	/**
	 *
	 * \return 
	 */
	SceneNodeFactoryManager&	SceneNodeFactoryManager::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	SceneNodeFactoryManager::SceneNodeFactoryManager()
	{
		registerSceneNodeFactory( new SceneNodeFactory(SceneNodeFactory::TypeName) );
	}

	/**
	 *
	 * \return 
	 */
	SceneNodeFactoryManager::~SceneNodeFactoryManager()
	{
		SceneNodeFactoryRegister::iterator it = m_SceneNodeFactoryRegister.begin();
		while ( it != m_SceneNodeFactoryRegister.end() )
		{
			LogManager::getSingleton().logMessage(INFO_NORMAL, 
				"register scene node factory " + it->second->getName()
				);

			SAFE_DELETE(it->second); it = m_SceneNodeFactoryRegister.erase(it);
		}
	}

	/**
	 *
	 * \param pFactory 
	 * \return 
	 */
	bool			SceneNodeFactoryManager::registerSceneNodeFactory(SceneNodeFactory* pFactory)
	{
		SceneNodeFactoryRegister::iterator it = m_SceneNodeFactoryRegister.find(pFactory->getName());
		if ( it == m_SceneNodeFactoryRegister.end() )
		{
			m_SceneNodeFactoryRegister.insert(
				SceneNodeFactoryRegister::value_type(pFactory->getName(), pFactory)
				);

			LogManager::getSingleton().logMessage(INFO_NORMAL, 
				"register scene node factory " + pFactory->getName()
				);
			return true;
		}

		return 0;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	SceneNodeFactory*	SceneNodeFactoryManager::getSceneNodeFactory(const String& name)
	{
		SceneNodeFactoryRegister::iterator it = m_SceneNodeFactoryRegister.find(name);
		if ( it != m_SceneNodeFactoryRegister.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void				SceneNodeFactoryManager::unregisterSceneNodeFactory(SceneNodeFactory* pFactory)
	{
		SceneNodeFactoryRegister::iterator it = m_SceneNodeFactoryRegister.find(pFactory->getName());
		if ( it != m_SceneNodeFactoryRegister.end() )
		{
			LogManager::getSingleton().logMessage(INFO_NORMAL, 
				"register scene node factory " + it->second->getName()
				);

			SAFE_DELETE(it->second); m_SceneNodeFactoryRegister.erase(it);
		}

	}
}