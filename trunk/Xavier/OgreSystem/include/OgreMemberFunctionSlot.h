#ifndef _____OgreMemberFunctionSlot_h_
#define _____OgreMemberFunctionSlot_h_

#include "OgreSlotFunctorBase.h"

// Start of Ogre namespace section
namespace Ogre
{
	/*!
	\brief
		Slot template class that creates a functor that calls back via a class
		member function.
	*/
	template<typename T>
	class MemberFunctionSlot : public SlotFunctorBase
	{
	public:
		//! Member function slot type.
		typedef bool(T::*MemberFunctionType)(const EventArgs&);

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj)
		{}

		virtual bool operator()(const EventArgs& args)
		{
			return (d_object->*d_function)(args);
		}

	private:
		MemberFunctionType d_function;
		T* d_object;
	};

} // End of  Ogre namespace section

#endif  // end of guard _CEGUIMemberFunctionSlot_h_
