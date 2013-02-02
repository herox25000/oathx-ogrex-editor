#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerFactory.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ServerFactory::ServerFactory(const String& typeName)
		: m_TypeName(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	ServerFactory::~ServerFactory()
	{
		
	}

	/**
	 *
	 * \param typeName 
	 */
	void			ServerFactory::setTypeName(const String& typeName)
	{
		m_TypeName = typeName;
	}

	/**
	 *
	 * \return 
	 */
	const String&	ServerFactory::getTypeName() const
	{
		return m_TypeName;
	}
}