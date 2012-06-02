#ifndef _____OgreMemberFunctionSlot_h_
#define _____OgreMemberFunctionSlot_h_

#include "OgreSlotFunctorBase.h"

namespace Ogre
{
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
	template<typename T> class MemberFunctionSlot : public SlotFunctorBase
	{
	public:
		typedef bool(T::*MemberFunctionType)(const EventArgs&);

		/**
		 *
		 * \param func 
		 * \param obj 
		 * \return 
		 */
		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			m_count(func),
			m_object(obj)
		{}

		/**
		 *
		 * \return 
		 */
		virtual bool operator()(const EventArgs& args)
		{
			return (m_object->*m_count)(args);
		}

	private:
		MemberFunctionType	m_count;
		T*					m_object;
	};

}

#endif
