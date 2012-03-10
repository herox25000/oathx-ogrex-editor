#pragma once

#include "OgreEditToolPrerequisites.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditModule
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
	class OgreEditTool_Export_API EditPlugin
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EditPlugin(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditPlugin(void);

		/**
		 *
		 * \param sName 
		 */
		virtual void				setName(const String& sName);

		/**
		 *
		 * \return 
		 */
		virtual String				getName() const;

	protected:
		String						m_sName; // ²å¼þÃû
	};
}
