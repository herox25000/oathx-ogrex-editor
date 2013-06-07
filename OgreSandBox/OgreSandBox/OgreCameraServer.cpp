#include "stdafx.h"
#include "OgreCameraServer.h"

namespace Ogre
{
	/**
	 *
	 * \param nID 
	 * \param szName 
	 * \return 
	 */
	CameraServer::CameraServer(uint32 nID, const String& szName)
		: Server(nID, szName)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	CameraServer::~CameraServer()
	{

	}
}