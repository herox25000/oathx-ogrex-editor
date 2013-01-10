#ifndef _____Og2dResource_H
#define _____Og2dResource_H

#include "Og2dReference.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-29
	*
	* \Author  : lp
	*
	* \Desc    : 资源基类
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Resource : public Reference
	{
	public:
		/**
		 *
		 * \return 
		 */
		Resource();

		/**
		 *
		 * \param name 
		 * \return 
		 */
		Resource(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~Resource();

		/**
		 *
		 * \return 
		 */
		virtual	const String&	getName() const;
		
		/**
		 *
		 * \param name 
		 */
		virtual	void			setName(const String& name);
	protected:
		String					m_szName;
	};
}

#endif