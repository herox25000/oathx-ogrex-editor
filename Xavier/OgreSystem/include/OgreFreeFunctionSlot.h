#ifndef _OgreFreeFunctionSlot_h_
#define _OgreFreeFunctionSlot_h_

#include "OgreSlotFunctorBase.h"

// Start of Ogre namespace section
namespace Ogre
{
	/*!
	\brief
		Slot functor class that calls back via a free function pointer.
	*/
	class FreeFunctionSlot : public SlotFunctorBase
	{
	public:
		//! Slot function type.
		typedef bool (SlotFunction)(const EventArgs&);

		FreeFunctionSlot(SlotFunction* func) :
			d_function(func)
		{}

		virtual bool operator()(const EventArgs& args)
		{
			return d_function(args);
		}

	private:
		SlotFunction* d_function;
	};


} // End of  Ogre namespace section

#endif  // end of guard _CEGUIFreeFunctionSlot_h_
