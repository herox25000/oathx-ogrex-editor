#include "Og2dViewport.h"
#include "Og2dRenderSystem.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param pRenderSystem 
	 * \return 
	 */
	Viewport::Viewport(RenderSystem* pRenderSystem, const Vector2D& vPos)
		: m_pRenderSystem(pRenderSystem), m_vPos(vPos)
	{
		m_bbSize = m_pRenderSystem->getBackBufferSize();
	}

	/**
	 *
	 * \return 
	 */
	Viewport::~Viewport()
	{

	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Viewport::getPosition() const
	{
		return m_vPos;
	}

	/**
	 *
	 * \param vPos 
	 */
	void		Viewport::setPosition(const Vector2D& vPos)
	{
		m_vPos = vPos;
	}

	/**
	 *
	 * \return 
	 */
	Rect		Viewport::getArea()
	{
		return Rect(m_vPos.x, m_vPos.y, m_vPos.x + m_bbSize.w, m_vPos.y + m_bbSize.h);
	}
	
	/**
	 *
	 * \param fElapsed 
	 */
	void		Viewport::update(float fElapsed)
	{
		if (m_pRenderSystem)
		{
			const Size& bbSize = m_pRenderSystem->getBackBufferSize();
			m_pRenderSystem->setMatrix2D(
				m_vPos.x, 
				m_vPos.y, 
				bbSize.w, 
				bbSize.h);
		}
	}
}