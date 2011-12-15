#include "OgreExplorerManager.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	template<> ExplorerManager* Singleton<ExplorerManager>::msSingleton = 0;
	ExplorerManager&	ExplorerManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}
	
	//////////////////////////////////////////////////////////////////////////
	ExplorerManager*	ExplorerManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return (msSingleton);
	}
	
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	ExplorerManager::ExplorerManager(void)
	{
	}

	ExplorerManager::~ExplorerManager(void)
	{
	}
}
