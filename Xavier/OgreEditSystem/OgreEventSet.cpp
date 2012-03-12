#include "OgreEditSystemPrerequisites.h"
#include "OgreEventSet.h"
#include "OgreGlobalEventSet.h"

// Start of Ogre namespace section
namespace Ogre
{
/*************************************************************************
	Constructor
*************************************************************************/
EventSet::EventSet() :
	d_muted(false)
{
}


/*************************************************************************
	Destructor
*************************************************************************/
EventSet::~EventSet(void)
{
	removeAllEvents();
}


/*************************************************************************
	Add a new event to the EventSet
*************************************************************************/
void EventSet::addEvent(const String& name)
{
	if (isEventPresent(name))
	{
		//CEGUI_THROW(AlreadyExistsException("An event named '" + name + "' already exists in the EventSet."));
	}

	d_events[name] = new Event(name);
}


/*************************************************************************
	Remove an event from the EventSet
*************************************************************************/
void EventSet::removeEvent(const String& name)
{
	EventMap::iterator pos = d_events.find(name);

	if (pos != d_events.end())
	{
		delete pos->second;
		d_events.erase(pos);
	}

}


/*************************************************************************
	Remove all events from the EventSet
*************************************************************************/
void EventSet::removeAllEvents(void)
{
	EventMap::iterator pos = d_events.begin();
	EventMap::iterator end = d_events.end()	;

	for (; pos != end; ++pos)
	{
		delete pos->second;
	}

	d_events.clear();
}


/*************************************************************************
	Check to see if an event is available
*************************************************************************/
bool EventSet::isEventPresent(const String& name)
{
	return (d_events.find(name) != d_events.end());
}


/*************************************************************************
	Subscribe to a scripted event (no group)
*************************************************************************/
//Event::Connection EventSet::subscribeScriptedEvent(const String& name, const String& subscriber_name)
//{
//	//return subscribeEvent(name, Event::Subscriber(ScriptFunctor(subscriber_name)));
//	ScriptModule* sm = System::getSingletonPtr()->getScriptingModule();
//	if (!sm)
//	{
//	   CEGUI_THROW(InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available"));
//	}
//	return sm->subscribeEvent(this, name, subscriber_name);
//}


/*************************************************************************
	Subscribe to a scripted event
*************************************************************************/
//Event::Connection EventSet::subscribeScriptedEvent(const String& name, Event::Group group, const String& subscriber_name)
//{
//        //return subscribeEvent(name, group, Event::Subscriber(ScriptFunctor(subscriber_name)));
//        ScriptModule* sm = System::getSingletonPtr()->getScriptingModule();
//	if (!sm)
//	{
//	   CEGUI_THROW(InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available"));
//	}
//	return sm->subscribeEvent(this, name, group, subscriber_name);
//}


/*************************************************************************
	Subscribe to an event (no group)
*************************************************************************/
Event::Connection EventSet::subscribeEvent(const String& name, Event::Subscriber subscriber)
{
    // do subscription & return connection
    return getEventObject(name, true)->subscribe(subscriber);
}


/*************************************************************************
	Subscribe to an event group
*************************************************************************/
Event::Connection EventSet::subscribeEvent(const String& name, Event::Group group, Event::Subscriber subscriber)
{
    // do subscription with group & return connection
    return getEventObject(name, true)->subscribe(group, subscriber);
}

/*************************************************************************
	Fire / Trigger an event
*************************************************************************/
void EventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
{
    // handle global events
    GlobalEventSet::getSingleton().fireEvent(name, args, eventNamespace);
    // handle local event
    fireEvent_impl(name, args);
}


/*************************************************************************
	Return whether the EventSet is muted or not.	
*************************************************************************/
bool EventSet::isMuted(void) const
{
	return d_muted;
}


/*************************************************************************
	Set the mute state for this EventSet.	
*************************************************************************/
void EventSet::setMutedState(bool setting)
{
	d_muted = setting;
}


/*************************************************************************
    Return the named Event object, optionally adding it to the set
    if needed
*************************************************************************/
Event* EventSet::getEventObject(const String& name, bool autoAdd)
{
    EventMap::iterator pos = d_events.find(name);

    // if event did not exist, add it and then find it.
    if (pos == d_events.end())
    {
        if (autoAdd)
        {
            addEvent(name);
            return d_events.find(name)->second;
        }
        else
        {
            return 0;
        }
    }

    return pos->second;
}


/*************************************************************************

*************************************************************************/
void EventSet::fireEvent_impl(const String& name, EventArgs& args)
{
    // find event object
    Event* ev = getEventObject(name);

    // fire the event if present and set is not muted
    if ((ev != 0) && !d_muted)
        (*ev)(args);
}



} // End of  Ogre namespace section
