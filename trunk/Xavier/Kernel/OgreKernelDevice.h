#ifndef _____OgreKernel_H
#define _____OgreKernel_H

#include "IKernelDevice.h"
#include "Ogre.h"

namespace kernel
{
	/**
	* \ingroup : Kernel
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Kernel_Export_API OgreKernelDevice : public IKernelDevice
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		OgreKernelDevice(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~OgreKernelDevice(void);

		/**
		 *
		 * \param sName 
		 * \return 
		 */
		virtual bool			create(const String& sName);

	protected:
		Ogre::Root*				m_pRoot;
	};
}

#endif
