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
	* \Desc    : �༭����
	*
	* \bug     : 
	*
	*/
	class OgreEditTool_Export_API EditPluginFactroy
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EditPluginFactroy(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditPluginFactroy(void);

		/** ���ò����
		 *
		 * \param sName 
		 */
		virtual void				setName(const String& sName);

		/** ��ȡ�����
		 *
		 * \return 
		 */
		virtual String				getName() const;

	protected:
		String						m_sName;
	};
}
