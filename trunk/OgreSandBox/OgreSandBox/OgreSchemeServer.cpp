#include "stdafx.h"
#include "OgreSchemeServer.h"

namespace Ogre
{
	const String	SchemeServer::EventNamespace			= "Scheme";
	const String	SchemeServer::ServerTypeName			= "ServerType/Scheme";

	/**
	 *
	 * \param nID 
	 * \param szName 
	 * \return 
	 */
	SchemeServer::SchemeServer(const uint32 nID, const String& szName)
		: Server(nID, szName)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	SchemeServer::~SchemeServer()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool		SchemeServer::configure(const SSAdp& ssadp)
	{
		return true;
	}
}