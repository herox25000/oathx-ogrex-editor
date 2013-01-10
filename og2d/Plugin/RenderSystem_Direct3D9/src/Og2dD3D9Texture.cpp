#include "Og2dD3D9Prerequisites.h"
#include "Og2dD3D9RenderSystem.h"
#include "Og2dException.h"
#include "Og2dD3D9Texture.h"

namespace Og2d
{
	/**
	 *
	 * \param pRenderSystem 
	 * \param name 
	 * \return 
	 */
	D3D9Texture::D3D9Texture(D3D9RenderSystem* pRenderSystem)
		: m_pRenderSystem(pRenderSystem), m_pTexture(0)
	{

	}

	/**
	 *
	 * \return 
	 */
	D3D9Texture::~D3D9Texture()
	{
		SAFE_RELEASE(m_pTexture);
	}
	
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	bool				D3D9Texture::createFromFile(const String& szName)
	{
		if (szName.empty())
			return 0;

		if (SUCCEEDED(D3DXCreateTextureFromFile(m_pRenderSystem->getD3DDevice(),
			szName.c_str(), &m_pTexture)))
		{
			m_szFilePath = szName;

			return true;
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Size				D3D9Texture::getOriginalSize() const
	{
		D3DXIMAGE_INFO d3dImage;
		ZeroMemory(&d3dImage, sizeof(D3DXIMAGE_INFO));
		
		// define return value
		Size cSize;

		// get image info
		if (SUCCEEDED(D3DXGetImageInfoFromFile(m_szFilePath.c_str(), &d3dImage)))
		{
			cSize.w = d3dImage.Width;
			cSize.h = d3dImage.Height;
		}
		
		// if get image info failed, then return default size(0,0)
		return cSize;
	}

	/**
	 *
	 * \return 
	 */
	Size				D3D9Texture::getSize() const
	{	
		// define return value
		Size cSize;

		// if the texture no null
		if (m_pTexture == NULL)
			return cSize;

		D3DSURFACE_DESC dc;
		ZeroMemory(&dc, sizeof(D3DSURFACE_DESC));

		// get texture describe info
		m_pTexture->GetLevelDesc(0, &dc);
		
		cSize.w = dc.Width;
		cSize.h = dc.Height;
		
		return cSize;
	}

	/**
	 *
	 * \return 
	 */
	IDirect3DTexture9*	D3D9Texture::getD3DTexture() const
	{
		return m_pTexture;
	}
}