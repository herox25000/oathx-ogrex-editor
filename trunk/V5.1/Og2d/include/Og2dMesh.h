#ifndef _____Og2dMesh_H
#define _____Og2dMesh_H

#include "Og2dVertex.h"

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
	class Og2d_Export_API Mesh
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		Mesh(int nVertsPerRow, int nVertsPerCol, int nSpaceing);

		/**
		 *
		 * \return 
		 */
		virtual ~Mesh();
	protected:
		int					m_nVertsPerRow;
		int					m_nVertsPerCol;
		int					m_nSpaceing;
	};
}

#endif