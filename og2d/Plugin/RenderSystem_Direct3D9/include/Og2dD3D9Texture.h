#ifndef _____Og2dD3D9Texture_H
#define _____Og2dD3D9Texture_H

#include "Og2dTexture.h"

namespace Og2d
{
	class D3D9RenderSystem;

	/**
	* \ingroup : RenderSystem_Direct3D9
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : D3D9 文理支持
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_D3D9_Export_API D3D9Texture : public Texture
	{
	public:
		/**
		 *
		 * \param pRenderSystem 
		 * \param name 
		 * \return 
		 */
		D3D9Texture(D3D9RenderSystem* pRenderSystem);

		/**
		 *
		 * \return 
		 */
		virtual ~D3D9Texture();
		
		/** 创建纹理
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	bool				createFromFile(const String& szName);
		
		/**
		 *
		 * \return 
		 */
		virtual	Size				getOriginalSize() const;

		/**
		 *
		 * \return 
		 */
		virtual	Size				getSize() const;

		/**
		 *
		 * \return 
		 */
		virtual IDirect3DTexture9*	getD3DTexture() const;

	protected:
		D3D9RenderSystem*			m_pRenderSystem;
		String						m_szFilePath;
		IDirect3DTexture9*			m_pTexture;
		
	};
}

#endif