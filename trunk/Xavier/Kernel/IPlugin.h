#ifndef _____IPlugin_H
#define _____IPlugin_H

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
	class Kernel_Export_API IPlugin : public IUnknown
	{
	public:
		/**
		 *
		 * \return 
		 */
		virtual ~IPlugin() {}
	};
}

#endif