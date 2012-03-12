#ifndef _____OgreSlotFunctorBase_h_
#define _____OgreSlotFunctorBase_h_

namespace Ogre
{

// forward refs
class EventArgs;

/*!
\brief
    Defines abstract interface which will be used when constructing various
    functor objects that bind slots to signals (or in Ogre terms, handlers to
    events).
*/
class SlotFunctorBase
{
public:
    virtual ~SlotFunctorBase() {};
    virtual bool operator()(const EventArgs& args) = 0;
};


} // End of  Ogre namespace section

#endif  // end of guard _CEGUISlotFunctorBase_h_
