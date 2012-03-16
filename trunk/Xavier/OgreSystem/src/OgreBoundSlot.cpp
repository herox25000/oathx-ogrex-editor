#include "OgreSystemPrerequisites.h"
#include "OgreBoundSlot.h"
#include "OgreEvent.h"

// Start of Ogre namespace section
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
		d_group(group),
		d_subscriber(new SubscriberSlot(subscriber)),
		d_event(&event)
	{}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	BoundSlot::BoundSlot(const BoundSlot& other) :
		d_group(other.d_group),
		d_subscriber(other.d_subscriber),
		d_event(other.d_event)
	{
	}


	/**
	 *
	 * \return 
	 */
	BoundSlot::~BoundSlot()
	{
		disconnect();
		delete d_subscriber;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	BoundSlot& BoundSlot::operator=(const BoundSlot& other)
	{
		d_group      = other.d_group;
		d_subscriber = other.d_subscriber;
		d_event      = other.d_event;

		return *this;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	bool BoundSlot::operator==(const BoundSlot& other) const
	{
		return d_subscriber == other.d_subscriber;
	}


	/**
	 *
	 * \param other 
	 * \return 
	 */
	bool BoundSlot::operator!=(const BoundSlot& other) const
	{
		return !(*this == other);
	}


	/**
	 *
	 * \return 
	 */
	bool BoundSlot::connected() const
	{
		return (d_subscriber != 0) && d_subscriber->connected();
	}


	/**
	 *
	 */
	void BoundSlot::disconnect()
	{
		// cleanup the bound subscriber functor
		if (connected())
			d_subscriber->cleanup();

		// remove the owning Event's reference to us
		if (d_event)
		{
			// get the event to erase the subscriber functor.
			d_event->unsubscribe(*this);
			d_event = 0;
		}

	}

} // End of  Ogre namespace section

