#include "OgreSystemPrerequisites.h"
#include "OgreEventSet.h"
#include "OgreGlobalEventSet.h"
#include "OgreLogManager.h"

// Start of Ogre namespace section
namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	EventSet::EventSet() :
		m_muted(false)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	EventSet::~EventSet(void)
	{
		removeAllEvents();
	}

	/**
	 *
	 * \param name 
	 */
	void EventSet::addEvent(const String& name)
	{
		if (isEventPresent(name))
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"Already Exists Event : " + name);
			return;
			//OGRE_EXCEPT(AlreadyExistsException("An event named '" + name + "' already exists in the EventSet."));
		}

		m_events[name] = new Event(name);
	}

	/**
	 *
	 * \param name 
	 */
	void EventSet::removeEvent(const String& name)
	{
		EventMap::iterator pos = m_events.find(name);

		if (pos != m_events.end())
		{
			delete pos->second;
			m_events.erase(pos);
		}

	}

	/**
	 *
	 * \param void 
	 */
	void EventSet::removeAllEvents(void)
	{
		EventMap::iterator pos = m_events.begin();
		EventMap::iterator end = m_events.end()	;

		for (; pos != end; ++pos)
		{
			delete pos->second;
		}

		m_events.clear();
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	bool EventSet::isEventPresent(const String& name)
	{
		return (m_events.find(name) != m_events.end());
	}

	/**
	 *
	 * \param name 
	 * \param subscriber 
	 * \return 
	 */
	Event::Connection EventSet::subscribeEvent(const String& name, Event::Subscriber subscriber)
	{
		// do subscription & return connection
		LogManager::getSingleton().logMessage(LML_NORMAL, "subscribe Event : " + name);
		return getEventObject(name, true)->subscribe(subscriber);
	}

	/**
	 *
	 * \param name 
	 * \param group 
	 * \param subscriber 
	 * \return 
	 */
	Event::Connection EventSet::subscribeEvent(const String& name, Event::Group group, Event::Subscriber subscriber)
	{
		LogManager::getSingleton().logMessage(LML_NORMAL, "subscribe Event : " + name);
		// do subscription with group & return connection
		return getEventObject(name, true)->subscribe(group, subscriber);
	}

	/**
	 *
	 * \param name 
	 * \param args 
	 * \param eventNamespace 
	 */
	void EventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
	{
		// handle global events
		GlobalEventSet::getSingleton().fireEvent(name, args, eventNamespace);
		// handle local event
		fireEvent_impl(name, args);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	bool EventSet::isMuted(void) const
	{
		return m_muted;
	}

	/**
	 *
	 * \param setting 
	 */
	void EventSet::setMutedState(bool setting)
	{
		m_muted = setting;
	}


	/**
	 *
	 * \param name 
	 * \param autoAdd 
	 * \return 
	 */
	Event* EventSet::getEventObject(const String& name, bool autoAdd)
	{
		EventMap::iterator pos = m_events.find(name);

		// if event did not exist, add it and then find it.
		if (pos == m_events.end())
		{
			if (autoAdd)
			{
				addEvent(name);
				return m_events.find(name)->second;
			}
			else
			{
				return 0;
			}
		}

		return pos->second;
	}

	/**
	 *
	 * \param name 
	 * \param args 
	 */
	void EventSet::fireEvent_impl(const String& name, EventArgs& args)
	{
		// find event object
		Event* ev = getEventObject(name);

		// fire the event if present and set is not muted
		if ((ev != 0) && !m_muted)
			(*ev)(args);
	}
} // End of  Ogre namespace section
