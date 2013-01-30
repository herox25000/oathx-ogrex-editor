#include "OgreSystemStdAfx.h"
#include "OgrePropertySet.h"
#include "OgreServer.h"

namespace Ogre
{
	/**
	 *
	 * \param nID 
	 * \param name 
	 * \return 
	 */
	Server::Server(const String& name)
		: m_nRefCount(1), m_Name(name), m_pParent(NULL)
	{
			
	}

	/**
	 *
	 * \return 
	 */
	Server::~Server()
	{
		destroyAllServer();
	}

	/**
	 *
	 * \param name 
	 */
	void			Server::setName(const String& name)
	{
		m_Name = name;
	}

	/**
	 *
	 * \return 
	 */
	const String&	Server::getName() const
	{
		return m_Name;
	}

	/**
	 *
	 */
	void			Server::grab()
	{
		++ m_nRefCount;
	}

	/**
	 *
	 * \return 
	 */
	int				Server::getRefCount() const
	{
		return m_nRefCount;
	}

	/**
	 *
	 */
	void			Server::drop()
	{
		if ((--m_nRefCount) == 0)
		{
			delete this;
		}
	}

	/**
	 *
	 * \param pParent 
	 */
	void			Server::setParent(Server* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 *
	 * \return 
	 */
	Server*			Server::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \param pServer 
	 * \return 
	 */
	bool			Server::registerServer(Server* pServer)
	{
		if (m_Name == pServer->getName())
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL, 
				"Can not add your own : " + pServer->getName());

			return 0;
		}

		HashMapServer::iterator it = m_HashMapServer.find(pServer->getName());
		if ( it == m_HashMapServer.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				m_Name + "->Register new server : " + pServer->getName());

			Server* pParent = pServer->getParent();
			if (pParent)
				pServer->unregisterServer(pServer, 0);

			pServer->setParent(this);

			m_HashMapServer.insert(
				HashMapServer::value_type(pServer->getName(), pServer)
				);

			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL, 
				"This server has been exist : " + pServer->getName());	
		}

		return 0;	
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Server*			Server::getServer(const String& name)
	{
		HashMapServer::iterator it = m_HashMapServer.find(name);
		if ( it != m_HashMapServer.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Server*			Server::findServer(const String& name)
	{
		if (m_Name == name)
			return this;

		Server* pServer = getServer(name);
		if (pServer == NULL)
		{
			HashMapServer::iterator it = m_HashMapServer.begin();
			while( it != m_HashMapServer.end() )
			{
				pServer = it->second->findServer(name);
				if (pServer)
					break;
			}
		}

		return pServer;
	}

	/**
	 *
	 * \param pServer 
	 * \param bDestroy 
	 */
	void			Server::unregisterServer(Server* pServer, bool bDestroy)
	{
		HashMapServer::iterator it = m_HashMapServer.find(pServer->getName());
		if ( it != m_HashMapServer.end() )
		{
			pServer->setParent(NULL);

			if (bDestroy)
			{
				LogManager::getSingleton().logMessage(LML_NORMAL, 
					"Deleted this plugin tool :  " + pServer->getName());

				it->second->drop();
			}

			m_HashMapServer.erase(it);
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL, 
				"This plugin tool can not be found :  " + pServer->getName());
		}
	}

	/**
	 *
	 */
	void			Server::destroyAllServer()
	{
		HashMapServer::iterator it = m_HashMapServer.begin();
		while( it != m_HashMapServer.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Deleted this server :  " + it->second->getName());

			it->second->drop(); it = m_HashMapServer.erase(it);
		}
	}
}