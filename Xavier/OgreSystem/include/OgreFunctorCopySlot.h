#ifndef _OgreFunctorCopySlot_h_
#define _OgreFunctorCopySlot_h_

#include "OgreSlotFunctorBase.h"

// Start of Ogre namespace section
namespace Ogre
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a copy of a
		functor object.
	*/
	template<typename T>
	class FunctorCopySlot : public SlotFunctorBase
	{
	public:
		FunctorCopySlot(const T& functor) :
			d_functor(functor)
		{}

		virtual bool operator()(const EventArgs& args)
		{
			return d_functor(args);
		}

	private:
		T d_functor;
	};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIFunctorCopySlot_h_
