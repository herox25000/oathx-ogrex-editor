#ifndef _OgreFreeFunctionSlot_h_
#define _OgreFreeFunctionSlot_h_

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
	class FreeFunctionSlot : public SlotFunctorBase
	{
	public:
		typedef bool (SlotFunction)(const EventArgs&);

		/**
		 *
		 * \param func 
		 * \return 
		 */
		FreeFunctionSlot(SlotFunction* func) :
			m_count(func)
		{}

		/**
		 *
		 * \return 
		 */
		virtual bool operator()(const EventArgs& args)
		{
			return m_count(args);
		}

	private:
		SlotFunction* m_count;
	};
}

#endif
