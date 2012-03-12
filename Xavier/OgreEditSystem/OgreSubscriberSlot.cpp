#include "OgreEditSystemPrerequisites.h"
#include "OgreSubscriberSlot.h"

// Start of Ogre namespace section
namespace Ogre
{

SubscriberSlot::SubscriberSlot(FreeFunctionSlot::SlotFunction* func) :
    d_functor_impl(new FreeFunctionSlot(func))
{
}


SubscriberSlot::SubscriberSlot() :
    d_functor_impl(0)
{
}


SubscriberSlot::~SubscriberSlot()
{
}

void SubscriberSlot::cleanup()
{
    delete d_functor_impl;
    d_functor_impl = 0;
}

} // End of  Ogre namespace section

