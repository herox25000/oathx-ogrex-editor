#include "stdafx.h"
#include "OgreWorld.h"

namespace Ogre
{
	/**
	 *
	 * \param nID 
	 * \return 
	 */
	World::World(const uint32 nID, const String& szName)
		: Server(nID, szName), m_pSceneManager(NULL), m_pSceneQuery(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	World::~World()
	{
		
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool			World::configure(const SSAdp& ssadp)
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

}