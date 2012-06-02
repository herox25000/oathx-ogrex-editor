#ifndef _OgreFunctorCopySlot_h_
#define _OgreFunctorCopySlot_h_

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
	template<typename T> class FunctorCopySlot : public SlotFunctorBase
	{
	public:
		/**
		 *
		 * \param functor 
		 * \return 
		 */
		FunctorCopySlot(const T& functor) :
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
		T			m_functor;
	};
}

#endif
