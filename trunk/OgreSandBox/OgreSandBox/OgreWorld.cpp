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
		const SWorldAdp& adp = static_cast<const SWorldAdp&>(ssadp);
		return true;
	}

}