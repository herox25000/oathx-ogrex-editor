#ifndef _____Og2dRenderBatch_H
#define _____Og2dRenderBatch_H

#include "Og2dRenderTarget.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-04
	*
	* \Author  : lp
	*
	* \Desc    : 渲染批次对象
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RenderBatch
	{
	public:
		/**
		 *
		 * \param szName 
		 * \param nBatch 
		 * \return 
		 */
		RenderBatch(const String& szName, int nBatch);

		/**
		 *
		 * \return 
		 */
		virtual ~RenderBatch();

		/**
		 *
		 * \param szName 
		 */
		virtual	void		setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual	String		getName() const;

		/**
		 *
		 * \param nBatch 
		 */
		virtual	void		setBatch(int nBatch);

		/**
		 *
		 * \return 
		 */
		virtual	int			getBatch() const;
	protected:
		String				m_szName;
		int					m_nBatch;
	};
}

#endif