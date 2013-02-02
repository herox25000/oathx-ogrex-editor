#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerFactory.h"
#include "OgreServerFactoryManager.h"
#include "OgreServerSceneManager.h"
#include "OgreServerCamera.h"
#include "OgreServerViewport.h"

namespace Ogre
{
	template<>	ServerFactoryManager*	Singleton<ServerFactoryManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	ServerFactoryManager&	ServerFactoryManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	ServerFactoryManager*	ServerFactoryManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	static const String		DefaultServerFactory[] = 
	{
		"Server/SceneManager",
		"Server/Camera",
		"Server/Viewport",
		"Server/TerrainGroup",
		"Server/Terrain",
	};

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \return 
	 */
	ServerFactoryManager::ServerFactoryManager()
	{
		registerServerFactory(
			new ServerSceneManagerFactory(DefaultServerFactory[SERVER_SCENEMANAGER])
			);
		registerServerFactory(
			new ServerCameraFactory(DefaultServerFactory[SERVER_CAMERA])
			);
	}

	/**
	 *
	 * \return 
	 */
	ServerFactoryManager::~ServerFactoryManager()
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.begin();
		while( it != m_HashMapServerFactory.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"unregister server factory : " + it->second->getTypeName());

			delete it->second; it = m_HashMapServerFactory.erase(it);
		}
	}

	/**
	 *
	 * \param typeName 
	 * \param pFactory 
	 * \return 
	 */
	bool			ServerFactoryManager::registerServerFactory(ServerFactory* pFactory)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(pFactory->getTypeName());
		if ( it == m_HashMapServerFactory.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Register server factory : " + pFactory->getTypeName());

			m_HashMapServerFactory.insert(
				HashMapServerFactory::value_type(pFactory->getTypeName(), pFactory)
				);

			return true;
		}
		else
		{			
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"This server factory exists : " + pFactory->getTypeName());
		}

		return 0;
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ServerFactory*	ServerFactoryManager::getServerFactory(const String& typeName)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(typeName);
		if ( it != m_HashMapServerFactory.end() )
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
	ServerFactory*	ServerFactoryManager::getServerFactory(int nID)
	{
		return getServerFactory(DefaultServerFactory[nID]);
	}

	/**
	 *
	 * \param pFactory 
	 */
	void			ServerFactoryManager::unregisterServerFactory(ServerFactory* pFactory)
	{
		HashMapServerFactory::iterator it = m_HashMapServerFactory.find(pFactory->getTypeName());
		if ( it != m_HashMapServerFactory.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"unregister server factory : " + pFactory->getTypeName());

			delete it->second; m_HashMapServerFactory.erase(it);
		}	
	}
}