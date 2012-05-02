#ifndef _____OgreSubscriberSlot_h_
#define _____OgreSubscriberSlot_h_

#include "OgreFreeFunctionSlot.h"
#include "OgreFunctorCopySlot.h"
#include "OgreFunctorReferenceSlot.h"
#include "OgreFunctorPointerSlot.h"
#include "OgreMemberFunctionSlot.h"
#include "OgreFunctorReferenceBinder.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditSystem
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
	class Ogre_System_Export_API SubscriberSlot
	{
	public:
	
		/**
		 *
		 * \return 
		 */
		SubscriberSlot();

		/**
		 *
		 * \param func 
		 * \return 
		 */
		SubscriberSlot(FreeFunctionSlot::SlotFunction* func);

		/**
		 *
		 * \return 
		 */
		~SubscriberSlot();

		/**
		 *
		 * \return 
		 */
		bool	operator()(const EventArgs& args) const
		{
			return (*m_functor_impl)(args);
		}

		/**
		 *
		 * \return 
		 */
		bool	connected() const
		{
			return m_functor_impl != 0;
		}

		/**
		 *
		 */
		void	cleanup();

		// templatised constructors
		/*!
		\brief
			Creates a SubscriberSlot that is bound to a member function.
		*/
		template<typename T>
		SubscriberSlot(bool (T::*function)(const EventArgs&), T* obj) :
			m_functor_impl(new MemberFunctionSlot<T>(function, obj))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a functor object reference.
		*/
		template<typename T>
		SubscriberSlot(const FunctorReferenceBinder<T>& binder) :
			m_functor_impl(new FunctorReferenceSlot<T>(binder.d_functor))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a copy of a functor object.
		*/
		template<typename T>
		SubscriberSlot(const T& functor) :
			m_functor_impl(new FunctorCopySlot<T>(functor))
		{}

		/*!
		\brief
			Creates a SubscriberSlot that is bound to a functor pointer.
		*/
		template<typename T>
		SubscriberSlot(T* functor) :
			m_functor_impl(new FunctorPointerSlot<T>(functor))
		{}

	private:
		//! Points to the internal functor object to which we are bound
		SlotFunctorBase* m_functor_impl;
	};

}

#endif
