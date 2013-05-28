#ifndef _____OgreEventArgs_h_
#define _____OgreEventArgs_h_

namespace Ogre
{
	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : CEGUI
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_SandBox_Export_API EventArgs
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EventArgs(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EventArgs(void);

		//! handlers should increment this if they handled the event.
		uint	handled;
	};

}

#endif
