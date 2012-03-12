#ifndef _____OgreGlobalEventSet_h_
#define _____OgreGlobalEventSet_h_

#include "OgreEventSet.h"
#include "OgreSingleton.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif

// Start of Ogre namespace section
namespace Ogre
{
/*!
\brief
    The GlobalEventSet singleton allows you to subscribe to an event for all
    instances of a class.  The GlobalEventSet effectively supports "late binding"
    to events; which means you can subscribe to some event that does not actually
    exist (yet).
*/
class Ogre_EditSystem_Export_API GlobalEventSet : public EventSet, public Singleton<GlobalEventSet>
{
public:
	GlobalEventSet();
	~GlobalEventSet();


	/*!
	\brief
		Return singleton System object

	\return
		Singleton System object
	*/
	static	GlobalEventSet&	getSingleton(void);


	/*!
	\brief
		Return pointer to singleton System object

	\return
		Pointer to singleton System object
	*/
	static	GlobalEventSet*	getSingletonPtr(void);


	/*!
	\brief
		Fires the named event passing the given EventArgs object.

	\param name
		String object holding the name of the Event that is to be fired (triggered)

	\param args
		The EventArgs (or derived) object that is to be bassed to each subscriber of the Event.  Once all subscribers
		have been called the 'handled' field of the event is updated appropriately.
		
	\param eventNamespace
		String object describing the namespace prefix to use when firing the global event.

	\return
		Nothing.
	*/
	virtual void	fireEvent(const String& name, EventArgs& args, const String& eventNamespace = "");
};

} // End of  Ogre namespace section


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	// end of guard _CEGUIGlobalEventSet_h_
