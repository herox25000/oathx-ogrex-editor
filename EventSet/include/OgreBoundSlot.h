#ifndef _____OgreBoundSlot_h_
#define _____OgreBoundSlot_h_

#include "OgreSubscriberSlot.h"

namespace Ogre
{
	class Event;

	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-16
	*
	* \Author  : CEGUI
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API BoundSlot
	{
	public:
		typedef unsigned int Group;

		/**
		 *
		 * \param group 
		 * \param subscriber 
		 * \param event 
		 * \return 
		 */
		BoundSlot(Group group, const SubscriberSlot& subscriber, Event& event);

		/**
		 *
		 * \param other 
		 * \return 
		 */
		BoundSlot(const BoundSlot& other);

		/**
		 *
		 * \return 
		 */
		~BoundSlot();

		/**
		 *
		 * \return 
		 */
		bool connected() const;

		/**
		 *
		 */
		void disconnect();

		/**
		 *
		 * \param other 
		 * \return 
		 */
		bool	operator==(const BoundSlot& other) const;

		/**
		 *
		 * \param other 
		 * \return 
		 */
		bool	operator!=(const BoundSlot& other) const;

	private:
		friend class Event;

		/**
		 *
		 * \param other 
		 * \return 
		 */
		BoundSlot& operator=(const BoundSlot& other);

		Group			m_group;                //! The group the slot subscription used.
		SubscriberSlot* m_subscriber;			//! The actual slot object.
		Event*			m_event;                //! The event to which the slot was attached
	};
}

#endif
