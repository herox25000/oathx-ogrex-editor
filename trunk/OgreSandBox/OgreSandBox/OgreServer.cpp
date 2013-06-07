#include "stdafx.h"
#include "OgreServer.h"

namespace Ogre
{
	const String	Server::EventNamespace			= "Server";
	const String	Server::ServerTypeName			= "ServerType/Default";

	const String	Server::EventRegisterServer		= "RegisterServer";
	const String	Server::EventUnregisterServer	= "UnregisterServer";
	const String	Server::EventLoadProperty		= "LoadProperty";

	/**
	 *
	 * \param nID 
	 * \param szName 
	 * \return 
	 */
	Server::Server(const uint32 nID, const String& szName)
		: m_nID(nID), m_szName(szName), m_pParent(NULL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	Server::~Server()
	{

	}

	/**
	 *
	 * \param nID 
	 */
	void			Server::setID(const uint32 nID)
	{
		m_nID = nID;
	}

	/**
	 *
	 * \return 
	 */
	uint32			Server::getID() const
	{
		return m_nID;
	}

	/**
	 *
	 * \param szName 
	 */
	void			Server::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	const String&	Server::getName() const
	{
		return m_szName;
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
	 */
	void			Server::registerServer(Server* pServer)
	{
		ServerRegister::iterator it = m_ServerRegister.find(pServer->getID());
		if ( it != m_ServerRegister.end() )
		{
			// reset parent server
			Server* pParent = pServer->getParent();
			if (pParent)
				pParent->unregisterServer(pServer, 0);

			// set new parent server
			pServer->setParent(this);
			
			// insert server
			m_ServerRegister.insert(
				ServerRegister::value_type(pServer->getID(), pServer)
				);

			// send register server event
			RegServerEventArgs args(pServer);
			fireEvent(EventRegisterServer, args, 
				EventNamespace);

		}
	}

	/**
	 *
	 * \param nID 
	 * \return 
	 */
	Server*			Server::getServer(const uint32 nID)
	{
		if (m_nID == nID)
			return this;

		ServerRegister::iterator it = m_ServerRegister.begin();
		while( it != m_ServerRegister.end() )
		{
			Server* pServer = it->second->getServer(nID);
			if (pServer)
				return pServer;

			it ++;
		}

		return NULL;
	}

	/**
	 *
	 * \param pServer 
	 * \param bDestory/* 
	 */
	void			Server::unregisterServer(Server* pServer, bool bDestory/* =true */)
	{
		ServerRegister::iterator it = m_ServerRegister.find(pServer->getID());
		if ( it != m_ServerRegister.end() )
		{
			// send register server event
			RegServerEventArgs args(pServer);
			fireEvent(EventUnregisterServer, args, 
				EventNamespace);

			if (bDestory)
			{
				delete it->second;
			}

			m_ServerRegister.erase(it);
		}
	}

	/**
	 *
	 * \return 
	 */
	ServerIterator	Server::getServerIterator()
	{
		return ServerIterator(m_ServerRegister.begin(), m_ServerRegister.end());
	}
	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool			Server::configure(const SSAdp& ssadp)
	{
		// send register server event
		LoadPropertyEventArgs args(ssadp.szPropertyFilePath);
		fireEvent(EventLoadProperty, args, EventNamespace);

		return true;
	}
}
