#include "OgreSystemPrerequisites.h"
#include "OgreSubscriberSlot.h"

namespace Ogre
{

	/**
	 *
	 * \param func 
	 * \return 
	 */
	SubscriberSlot::SubscriberSlot(FreeFunctionSlot::SlotFunction* func) :
		m_functor_impl(new FreeFunctionSlot(func))
	{
	}


	/**
	 *
	 * \return 
	 */
	SubscriberSlot::SubscriberSlot() :
		m_functor_impl(0)
	{
	}


	/**
	 *
	 * \return 
	 */
	SubscriberSlot::~SubscriberSlot()
	{
	}

	/**
	 *
	 */
	void	SubscriberSlot::cleanup()
	{
		delete m_functor_impl;
		m_functor_impl = 0;
	}

}

