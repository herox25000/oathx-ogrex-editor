#include "Og2dRenderSystem.h"
#include "Og2dQuad.h"
#include "Og2dSystem.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param rect 
	 * \return 
	 */
	Quad::Quad(const String& szName, const Rect& rect) 
		: RenderTarget(szName), m_pShape(NULL),m_pTexture(0)
	{
		// get render system object
		RenderSystem* pRenderSystem = System::getSingleton().getRenderSystem();
		if (pRenderSystem)
		{
			// create shape object, 4 vertex
			m_pShape = pRenderSystem->createShape(4);
		}
		
		// set bounding box
		setBoundingBox(rect);

		// init default texture rect
		m_tUV[0] = 0.0f;
		m_tUV[1] = 0.0f;
		m_tUV[2] = 1.0f;
		m_tUV[3] = 1.0f;
	}

	/**
	 *
	 * \return 
	 */
	Quad::~Quad()
	{
		SAFE_DELETE(m_pShape);
	}

	/**
	 *
	 * \param fScale 
	 */
	void	Quad::setScale(float fScale)
	{
		if (!equals(m_fScale, fScale))
		{
			m_fScale	=	fScale;
			m_BouingBox *=	fScale;
		}
	}

	/**
	 *
	 * \param vclr 
	 */
	void	Quad::setColour(const SVertexClr4& vclr)
	{
		m_colour = vclr;
	}

	/**
	 *
	 * \param pTexture 
	 */
	void	Quad::setTexture(Texture* pTexture)
	{
		if (m_pTexture != pTexture)
		{
			// if the texture object is valid, drop it
			if (m_pTexture != NULL)
				m_pTexture->drop();
			
			// set't texture
			m_pTexture = pTexture;
			
			// if the texture object is valid, grab it
			if (m_pTexture != NULL)
				m_pTexture->grab();
		}
	}

	/**
	 *
	 * \param rect 
	 */
	bool	Quad::setTextureRect(const Rect& rect)
	{
		if (m_pTexture == NULL)
			return 0;
		
		// use new texture rect
		m_tRect = rect;

		// get texture memey size
		Size cSize = m_pTexture->getSize();
		
		// update uv coord
		m_tUV[0] = m_tRect[0] / cSize.w;
		m_tUV[1] = m_tRect[1] / cSize.h;
		m_tUV[2] = m_tRect[2] / cSize.w;
		m_tUV[3] = m_tRect[3] / cSize.h;

		return true;
	}
	
	/**
	 *
	 * \return 
	 */
	Rect	Quad::getTextureRect() const
	{
		return m_tRect;
	}

	/**
	 *
	 * \param fElapsed 
	 */
	bool	Quad::draw(float fElapsed)
	{
		// lock vertex buffer
		SVertex2D* pVertex = m_pShape->lock();
		if (!pVertex)
			return 0;
		
		// set vertex data
		pVertex[0] = SVertex2D(m_BouingBox[0],	m_BouingBox[1], 0.0f, 
			m_colour[0], m_tUV[0], m_tUV[1]);

		pVertex[1] = SVertex2D(m_BouingBox[2], m_BouingBox[1], 0.0f,
			m_colour[1], m_tUV[2], m_tUV[1]);

		pVertex[2] = SVertex2D(m_BouingBox[2], m_BouingBox[3], 0.0f,
			m_colour[2], m_tUV[2], m_tUV[3]);

		pVertex[3] = SVertex2D(m_BouingBox[0],	m_BouingBox[3], 0.0f,
			m_colour[3], m_tUV[0], m_tUV[3]);

		// unlock shape
		m_pShape->unlock();
		// bind texture to quad
		m_pShape->setTexture(0, m_pTexture);
		// requset draw the quad
		m_pShape->draw();

		return true;
	}
}