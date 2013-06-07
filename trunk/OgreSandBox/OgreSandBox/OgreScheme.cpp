#include "stdafx.h"
#include "OgreScheme.h"

namespace Ogre
{
	const String	Scheme::EventNamespace			= "Scheme";
	const String	Scheme::ServerTypeName			= "ServerType/Scheme";

	/**
	 *
	 * \param nID 
	 * \param szName 
	 * \return 
	 */
	Scheme::Scheme(const uint32 nID, const String& szName)
		: Server(nID, szName)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	Scheme::~Scheme()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool		Scheme::configure(const SSAdp& ssadp)
	{
		const SSchemeAdp& adp = static_cast<const SSchemeAdp&>(ssadp);

		if (Unity::createDirectory(adp.szPathName))
		{
					
		}

		return true;
	}
}