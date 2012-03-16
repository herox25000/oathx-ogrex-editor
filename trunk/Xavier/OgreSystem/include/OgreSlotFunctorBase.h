#ifndef _____OgreSlotFunctorBase_h_
#define _____OgreSlotFunctorBase_h_

namespace Ogre
{
	// forward refs
	class EventArgs;

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
	class SlotFunctorBase
	{
	public:
		/**
		 *
		 * \return 
		 */
		virtual ~SlotFunctorBase() {};

		/**
		 *
		 * \return 
		 */
		virtual bool operator()(const EventArgs& args) = 0;
	};
}

#endif
