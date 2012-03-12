#include "OgreEditSystemPrerequisites.h"
#include "OgreGlobalEventSet.h"
#include "OgreLogManager.h"


// Start of Ogre namespace section
namespace Ogre
{
	/*************************************************************************
		Static Data Definitions
	*************************************************************************/
	// singleton instance pointer
	template<> GlobalEventSet* Singleton<GlobalEventSet>::msSingleton	= 0;
	GlobalEventSet&		GlobalEventSet::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	GlobalEventSet*		GlobalEventSet::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/*************************************************************************
		GlobalEventSet constructor.
	*************************************************************************/
	GlobalEventSet::GlobalEventSet()
	{

	}

	/*************************************************************************
		GlobalEventSet destructor.
	*************************************************************************/
	GlobalEventSet::~GlobalEventSet()
	{

	}

	/*************************************************************************
		Overridden fireEvent which always succeeds.
	*************************************************************************/
	void GlobalEventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
	{
        fireEvent_impl(eventNamespace + "/" + name, args);
	}

} // End of  Ogre namespace section
