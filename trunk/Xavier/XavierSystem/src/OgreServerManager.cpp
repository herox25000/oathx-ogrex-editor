#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerManager.h"

namespace Ogre
{
	template<>	ServerManager*	Singleton<ServerManager>::msSingleton = NULL;

	/**
	 *
	 * \return 
	 */
	ServerManager&	ServerManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	ServerManager*	ServerManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \param rootName 
	 * \return 
	 */
	ServerManager::ServerManager(const String& rootName)
		: m_pRootServer(NULL)
	{
		m_pRootServer = new Server(rootName);
	}

	/**
	 *
	 * \return 
	 */
	ServerManager::~ServerManager()
	{
		if (m_pRootServer)
		{
			m_pRootServer->drop();
		}
	}

	/**
	 *
	 * \return 
	 */
	Server*		ServerManager::getRootServer() const
	{
		return m_pRootServer;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Server*		ServerManager::getServer(const String& name)
	{
		if ( m_pRootServer->getName() == name)
			return m_pRootServer;

		return m_pRootServer->findServer(name);
	}
}