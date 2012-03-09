#ifndef _____IKernelDevice_H
#define _____IKernelDevice_H

#pragma once

#include "IUnknown.h"

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
	class Kernel_Export_API IKernelDevice : public IUnknown
	{
	public:
		/**
		 *
		 * \return 
		 */
		virtual ~IKernelDevice() {}
	};

	extern "C"{

		Kernel_Export_API IKernelDevice* createKernelDevice(const String& sName);
	}
}

#endif