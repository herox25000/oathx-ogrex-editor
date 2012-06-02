#include "OgreEventSetPrerequisites.h"
#include "OgreGlobalEventSet.h"
#include "OgreLogManager.h"

namespace Ogre
{
	template<> GlobalEventSet* Singleton<GlobalEventSet>::msSingleton	= 0;

	/**
	 *
	 * \return 
	 */
	GlobalEventSet&		GlobalEventSet::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	GlobalEventSet*		GlobalEventSet::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	GlobalEventSet::GlobalEventSet()
	{

	}

	/**
	 *
	 * \return 
	 */
	GlobalEventSet::~GlobalEventSet()
	{

	}

	/**
	 *
	 * \param name 
	 * \param args 
	 * \param eventNamespace 
	 */
	void GlobalEventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
	{
        fireEvent_impl(eventNamespace + "/" + name, args);
	}

}
