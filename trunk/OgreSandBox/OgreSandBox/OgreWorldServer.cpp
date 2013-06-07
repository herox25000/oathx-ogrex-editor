#include "stdafx.h"
#include "OgreWorldServer.h"

namespace Ogre
{
	/**
	 *
	 * \param nID 
	 * \return 
	 */
	WorldServer::WorldServer(const uint32 nID, const String& szName)
		: Server(nID, szName), m_pSceneManager(NULL), m_pSceneQuery(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	WorldServer::~WorldServer()
	{
		
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool			WorldServer::configure(const SSAdp& ssadp)
	{
		// convert to world param
		const SWorldAdp& adp = static_cast<const SWorldAdp&>(ssadp);

		// create ogre scene manager
		m_pSceneManager = Root::getSingletonPtr()->createSceneManager(adp.typeMask);
		if (m_pSceneManager == NULL)
			return 0;

		// create scene query
		m_pSceneQuery	= m_pSceneManager->createRayQuery(Ray());
		if (m_pSceneQuery == NULL)
		{
			TKLogEvent("Can't create ogre scene query error" ,
				LML_CRITICAL);
		}
		
		return Server::configure(ssadp);
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	WorldServer::getSceneManager() const
	{
		return m_pSceneManager;
	}

	/**
	 *
	 * \return 
	 */
	RaySceneQuery*	WorldServer::getRaySceneQuery() const
	{
		return m_pSceneQuery;
	}

}