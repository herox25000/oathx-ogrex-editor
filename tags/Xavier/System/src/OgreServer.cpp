#include "OgreSystemPrerequisites.h"
#include "OgreServer.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	Server::Server(const String& typeName) : m_typeName(typeName)
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
	 * \return 
	 */
	String			Server::getTypeName() const
	{
		return m_typeName;
	}

	/**
	 *
	 * \param typeName 
	 */
	void			Server::setTypeName(const String& typeName)
	{
		m_typeName = typeName;
	}

	/**
	 *
	 * \return 
	 */
	bool			Server::load()
	{
		return 0;
	}

	/**
	 *
	 */
	void			Server::unload()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	const String	ServerFactory::FactoryTypeName = "System/BaseServerFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ServerFactory::ServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	ServerFactory::~ServerFactory()
	{

	}
}
