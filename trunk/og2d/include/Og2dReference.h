#ifndef _____Og2dReference_H
#define _____Og2dReference_H

#include "Og2dTypes.h"

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
	* \Desc    : 引用对象基类
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Reference
	{
	public:
		/**
		 *
		 * \return 
		 */
		Reference();

		/**
		 *
		 * \return 
		 */
		virtual ~Reference();

		/**
		 *
		 * \return 
		 */
		virtual	void	grab();

		/**
		 *
		 * \return 
		 */
		virtual	int		getReferenceCount() const;

		/**
		 *
		 * \return 
		 */
		virtual	void	drop();

	protected:
		int				m_nReferenceCount;
	};

#ifndef dropAndNULL
#define dropAndNULL(p) {if (p) p->drop(); p=NULL;}
#endif
}

#endif