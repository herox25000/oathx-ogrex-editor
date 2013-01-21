#include "OgreSystemStdAfx.h"
#include "OgreWorld.h"

namespace Ogre
{

	template<>	World*	Singleton<World>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	World&		World::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	World*		World::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	World::World()
	{

	}

	/**
	 *
	 * \return 
	 */
	World::~World()
	{
		
	}
}