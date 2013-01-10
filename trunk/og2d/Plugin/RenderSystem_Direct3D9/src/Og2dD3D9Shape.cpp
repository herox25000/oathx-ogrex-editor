#include "Og2dD3D9Prerequisites.h"
#include "Og2dD3D9Shape.h"
#include "Og2dD3D9Texture.h"
#include "Og2dD3D9RenderSystem.h"
#include "Og2dException.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param nLength 
	 * \return 
	 */
	D3D9Shape::D3D9Shape(D3D9RenderSystem* pSystem, int nLength)
		: Shape(nLength),m_pRenderSystem(pSystem),m_pVertex(NULL)
	{
#if USE_DYNAMIC_VERTEXBUFFER == 0
		m_pVB = NULL;
		/*
		* create vertex buffer
		*/
		if (FAILED(pSystem->getD3DDevice()->CreateVertexBuffer(nLength*SVERTEX2DSIZE,
			0, SVERTEX2DFVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		{
			tryException(EC_CREATE_FAILED, "can't create shape vertex",
				"D3D9Shape::D3D9Shape()");			
		}
#else
		m_pVertex = new SVertex2D[nLength];
#endif
	}

	/**
	 *
	 * \return 
	 */
	D3D9Shape::~D3D9Shape()
	{
#if USE_DYNAMIC_VERTEXBUFFER == 0
		SAFE_RELEASE(m_pVB);
#else
		delete [] m_pVertex;	
#endif
	}

	/**
	 *
	 * \return 
	 */
	SVertex2D*	D3D9Shape::lock()
	{
#if USE_DYNAMIC_VERTEXBUFFER == 0
		if (SUCCEEDED(m_pVB->Lock(0, m_nLength * SVERTEX2DSIZE, (void**)&m_pVertex, 0)))
			return m_pVertex;

		return NULL;
#else
		return m_pVertex;
#endif
	}

	/**
	 *
	 * \param nStage 
	 * \param pTexture 
	 */
	void		D3D9Shape::setTexture(int nStage, Texture* pTexture)
	{
		IDirect3DDevice9* pDevice = m_pRenderSystem->getD3DDevice();
		if (pDevice)
		{
			/* get d3d texture
			*/
			D3D9Texture* pD3DTexture = static_cast<D3D9Texture*>(
				pTexture
				);
			// set device texture
			pDevice->SetTexture(nStage,
				pD3DTexture ? pD3DTexture->getD3DTexture() : NULL);
		}
	}

	/**
	 *
	 */
	void		D3D9Shape::draw()
	{
#if USE_DYNAMIC_VERTEXBUFFER == 0
		IDirect3DDevice9* pDevice = m_pRenderSystem->getD3DDevice();
		if (pDevice)
		{
			pDevice->SetStreamSource(0, m_pVB, 0, SVERTEX2DSIZE);
			pDevice->SetFVF(SVERTEX2DFVF);
			pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nLength / 2);
		}
#else
		IDirect3DDevice9* pDevice = m_pRenderSystem->getD3DDevice();
		if (pDevice)
		{
			pDevice->SetFVF(SVERTEX2DFVF);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_pVertex, SVERTEX2DSIZE);
		}
#endif
	}

	/**
	 *
	 */
	void		D3D9Shape::unlock()
	{
#if USE_DYNAMIC_VERTEXBUFFER == 0
		m_pVB->Unlock();
#endif
	}
}