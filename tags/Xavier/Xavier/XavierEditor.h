#pragma once

#include "OgreString.h"

namespace Ogre
{
	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-06-03
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierEditor(const String& typeName);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierEditor();		
		/**
		 *
		 * \return 
		 */
		virtual	const String&	getTypeName() const;
	protected:
		String					m_typeName;
	};
}
