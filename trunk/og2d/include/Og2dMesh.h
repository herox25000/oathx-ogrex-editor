#ifndef _____Og2dMesh_H
#define _____Og2dMesh_H

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
	* \date    : 2013-01-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Mesh : public RenderTarget
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		Mesh(const String& name, int nVertexCount);

		/**
		 *
		 * \return 
		 */
		virtual ~Mesh();

		/**
		 *
		 * \return 
		 */
		virtual	ulong			getVertexCount() const;
	protected:
		ulong					m_nVertexCount;
	};
}

#endif