#ifndef _____OgreFunctorReferenceSlot_h_
#define _____OgreFunctorReferenceSlot_h_

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
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	template<typename T> class FunctorReferenceSlot : public SlotFunctorBase
	{
	public:
		/**
		 *
		 * \param functor 
		 * \return 
		 */
		FunctorReferenceSlot(T& functor) :
			m_functor(functor)
		{}

		/**
		 *
		 * \return 
		 */
		virtual bool operator()(const EventArgs& args)
		{
			return m_functor(args);
		}

	private:
		T&		m_functor;
	};

}

#endif
