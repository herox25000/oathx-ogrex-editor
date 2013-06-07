#include "stdafx.h"
#include "OgreScheme.h"
#include "OgreWorldServer.h"
#include "OgreSystem.h"

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

		// create scheme dir
		if (!Unity::createDirectory(adp.szPathName))
			return 0;

		// create world server
		ServerFactory* pFactory = System::getSingleton().getServerFactory(WorldServer::ServerTypeName);
		if (pFactory)
		{
			SWorldAdp adp;
			adp.clrAmbientLight	= ColourValue::Black;
			adp.typeMask		= 2;

			pFactory->createServer(ID_DEFWORLD, "World", adp, this);
		}			
		
		return true;
	}
}