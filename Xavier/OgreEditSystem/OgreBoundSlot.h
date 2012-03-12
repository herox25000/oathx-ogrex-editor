#ifndef _____OgreBoundSlot_h_
#define _____OgreBoundSlot_h_

#include "OgreSubscriberSlot.h"

// Start of Ogre namespace section
namespace Ogre
{
class Event;
/*!
\brief
    Class that tracks a SubscriberSlot, its group, and the Event to which it was
    subscribed.  This is effectively what gets returned from the calls to the
    Event::subscribe members, though BoundSlot is always wrapped in a
    reference counted pointer.  When a BoundSlot is deleted, the connection is
    unsubscribed and the SubscriberSlot is deleted.
*/
class Ogre_EditSystem_Export_API BoundSlot
{
public:
    typedef unsigned int Group;

    /*!
    \brief
        Constructor.

    \param group
        The subscriber group this slot is attached to.

    \param subscriber
        The actual slot object that is controlling this connection binding.

    \param event
        The Event object to which the subscribed slot is attached.
    */
    BoundSlot(Group group, const SubscriberSlot& subscriber, Event& event);

    /*!
    \brief
        Copy constructor.
    */
    BoundSlot(const BoundSlot& other);

    /*!
    \brief
        Destructor
    */
    ~BoundSlot();

    /*!
    \brief
        Returns whether the slot which this object is tracking is still
        internally connected to the signal / event mechanism.

    \return
        - true to indicate that the slot is still connected.
        - false to indicate that the slot has been disconnected.
    */
    bool connected() const;

    /*!
    \brief
        Disconnects the slot.  Once disconnected, the slot will no longer be
        called when the associated signal / event fires.  There is no way to
        re-connect a slot once it has been disconnected, a new subscription to
        the signal / event is required.

    \return
        Nothing.
    */
    void disconnect();

    /*!
    \brief
        Equality operator

    \param other
        The BoundSlot to compare against.

    \return
        - true if the BoundSlot objects represent the same connection.
        - false if the BoundSlot objects represent different connections.
    */
    bool operator==(const BoundSlot& other) const;

    /*!
    \brief
        Non-equality operator

    \param other
        The BoundSlot to compare against.

    \return
        - true if the BoundSlot objects represent different connections.
        - false if the BoundSlot objects represent the same connection.
    */
    bool operator!=(const BoundSlot& other) const;

private:
    friend class Event;
    // no assignment.
    BoundSlot& operator=(const BoundSlot& other);
    Group d_group;                  //! The group the slot subscription used.
    SubscriberSlot* d_subscriber;   //! The actual slot object.
    Event* d_event;                 //! The event to which the slot was attached
};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIBoundSlot_h_
