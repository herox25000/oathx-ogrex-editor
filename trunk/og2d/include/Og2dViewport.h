#ifndef _____Og2dViewport_H
#define _____Og2dViewport_H

#include "Og2dMath.h"

namespace Og2d
{
	class RenderSystem;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-11
	*
	* \Author  : lp
	*
	* \Desc    : 场景视口
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Viewport
	{
	public:
		/** 构造函数
		 *
		 * \param rcView 
		 * \return 
		 */
		Viewport(RenderSystem* pRenderSystem, const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual ~Viewport();

		/**
		 *
		 * \return 
		 */
		virtual Vector2D		getPosition() const;

		/**
		 *
		 * \param vPos 
		 */
		virtual	void			setPosition(const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual	Rect			getArea();
		
		/**
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
	protected:
		RenderSystem*			m_pRenderSystem;
		Vector2D				m_vPos;
		Size					m_bbSize;
	};
}

#endif