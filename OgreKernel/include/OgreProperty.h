#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#include "OgreKernelPrerequisites.h"

namespace Ogre
{
	/**
	* \ingroup : OgreKernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-10
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API Property
	{
		typedef map<String, String>	StringValue;
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		Property(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~Property(void);
	};
}

#endif
