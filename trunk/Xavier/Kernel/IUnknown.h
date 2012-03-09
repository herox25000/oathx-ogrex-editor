#ifndef _____IUnknown_H
#define _____IUnknown_H

#pragma once

#include "IKernelTypes.h"

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
	class Kernel_Export_API IUnknown
	{
	public:
		/**
		 *
		 * \return 
		 */
		IUnknown() : m_countREF(1)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~IUnknown()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual	int			grab()
		{
			++m_countREF; return m_countREF;
		}

		/**
		 *
		 * \return 
		 */
		virtual int			drop()
		{
			if (--m_countREF <= 0)
			{
				delete this;
				return 0;
			}

			return m_countREF;
		}

	protected:
		int					m_countREF;
	};
}


#endif