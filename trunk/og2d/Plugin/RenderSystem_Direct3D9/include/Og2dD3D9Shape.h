#ifndef _____Og2dD3D9Shape_H
#define _____Og2dD3D9Shape_H

#include "Og2dShape.h"

namespace Og2d
{
	class D3D9RenderSystem;

	// 定义使用动态顶点缓冲区
#ifndef USE_DYNAMIC_VERTEXBUFFER
#	define USE_DYNAMIC_VERTEXBUFFER		0
#endif

	/**
	* \ingroup : RenderSystem_Direct3D9
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-28
	*
	* \Author  : lp
	*
	* \Desc    : D3D9 实现
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_D3D9_Export_API D3D9Shape : public Shape
	{
	public:
		/**
		 *
		 * \param nLength 
		 * \return 
		 */
		D3D9Shape(D3D9RenderSystem* pSystem, int nLength);

		/**
		 *
		 * \return 
		 */
		virtual ~D3D9Shape();
		
		/**
		 *
		 * \return 
		 */
		virtual	SVertex2D*			lock();

		/**
		 *
		 * \param nStage 
		 * \param pTexture 
		 */
		virtual	void				setTexture(int nStage, Texture* pTexture);

		/**
		 *
		 */
		virtual	void				draw();

		/**
		 *
		 */
		virtual	void				unlock();

	protected:
		D3D9RenderSystem*			m_pRenderSystem;
		SVertex2D*					m_pVertex;
#if USE_DYNAMIC_VERTEXBUFFER == 0
		IDirect3DVertexBuffer9*		m_pVB;
#endif
	};
}

#endif