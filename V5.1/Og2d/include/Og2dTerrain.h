#ifndef _____Og2dTerrain_H
#define _____Og2dTerrain_H

#include "Og2dRenderTarget.h"
#include "Og2dTexture.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-10
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012-2013 lp All rights reserved.
	*/
	class Og2d_Export_API Terrain : public RenderTarget
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		Terrain(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~Terrain();
	};
}

#endif