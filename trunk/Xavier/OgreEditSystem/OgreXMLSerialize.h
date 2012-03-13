#ifndef _____OgreXMLSerialize_H
#define _____OgreXMLSerialize_H

#include "OgreProperty.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-13
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API XMLSerialize : public PropertySet
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		XMLSerialize(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XMLSerialize(void);
	};
}

#endif
