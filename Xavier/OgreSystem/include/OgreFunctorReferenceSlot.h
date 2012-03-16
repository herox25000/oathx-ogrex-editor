#ifndef _____OgreFunctorReferenceSlot_h_
#define _____OgreFunctorReferenceSlot_h_

#include "OgreSlotFunctorBase.h"

// Start of Ogre namespace section
namespace Ogre
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a functor
		object reference.
	*/
	template<typename T>
	class FunctorReferenceSlot : public SlotFunctorBase
	{
	public:
		FunctorReferenceSlot(T& functor) :
			d_functor(functor)
		{}

		virtual bool operator()(const EventArgs& args)
		{
			return d_functor(args);
		}

	private:
		T& d_functor;
	};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIFunctorReferenceSlot_h_
