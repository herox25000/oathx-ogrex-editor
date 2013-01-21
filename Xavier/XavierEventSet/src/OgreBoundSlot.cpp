#include "OgreEventSetStdAfx.h"
#include "OgreBoundSlot.h"
#include "OgreEvent.h"

namespace Ogre
{
	/**
	 *
	 * \param group 
	 * \param subscriber 
	 * \param event 
	 * \return 
	 */
	BoundSlot::BoundSlot(Group group, const SubscriberSlot& subscriber, Event& event) :
		m_group(group),
		m_subscriber(new SubscriberSlot(subscriber)),
		m_event(&event)
	{}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	BoundSlot::BoundSlot(const BoundSlot& other) :
		m_group(other.m_group),
		m_subscriber(other.m_subscriber),
		m_event(other.m_event)
	{
	}


	/**
	 *
	 * \return 
	 */
	BoundSlot::~BoundSlot()
	{
		disconnect();
		delete m_subscriber;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	BoundSlot&	BoundSlot::operator=(const BoundSlot& other)
	{
		m_group      = other.m_group;
		m_subscriber = other.m_subscriber;
		m_event      = other.m_event;

		return *this;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	bool		BoundSlot::operator==(const BoundSlot& other) const
	{
		return m_subscriber == other.m_subscriber;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	bool		BoundSlot::operator!=(const BoundSlot& other) const
	{
		return !(*this == other);
	}


	/**
	 *
	 * \return 
	 */
	bool		BoundSlot::connected() const
	{
		return (m_subscriber != 0) && m_subscriber->connected();
	}


	/**
	 *
	 */
	void		BoundSlot::disconnect()
	{
		// cleanup the bound subscriber functor
		if (connected())
			m_subscriber->cleanup();

		// remove the owning Event's reference to us
		if (m_event)
		{
			// get the event to erase the subscriber functor.
			m_event->unsubscribe(*this);
			m_event = 0;
		}

	}

} // End of  Ogre namespace section

