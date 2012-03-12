#ifndef _____OgreFunctorPointerSlot_h_
#define _____OgreFunctorPointerSlot_h_

#include "OgreSlotFunctorBase.h"

// Start of Ogre namespace section
namespace Ogre
{
/*!
\brief
    Slot template class that creates a functor that calls back via a functor
    object pointer.
*/
template<typename T>
class FunctorPointerSlot : public SlotFunctorBase
{
public:
    FunctorPointerSlot(T* functor) :
        d_functor(functor)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return (*d_functor)(args);
    }

private:
    T* d_functor;
};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIFunctorPointerSlot_h_
