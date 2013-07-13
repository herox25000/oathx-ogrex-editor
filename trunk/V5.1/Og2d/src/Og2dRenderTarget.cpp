#include "Og2dRenderTarget.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	RenderTarget::RenderTarget(const String& szName)
		: m_szName(szName), m_fScale(1.0f), m_bVisible(true)
	{

	}

	/**
	 *
	 * \return 
	 */
	RenderTarget::~RenderTarget()
	{

	}

	/**
	 *
	 * \param szName 
	 */
	void		RenderTarget::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	String		RenderTarget::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param fScale 
	 */
	void		RenderTarget::setScale(float fScale)
	{
		m_fScale = fScale;
	}

	/**
	 *
	 * \return 
	 */
	float		RenderTarget::getScale() const
	{
		return m_fScale;
	}

	/**
	 *
	 * \param bVisible 
	 */
	void		RenderTarget::setVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}

	/**
	 *
	 * \return 
	 */
	bool		RenderTarget::isVisible() const
	{
		return m_bVisible;
	}

	/**
	 *
	 * \param vPos 
	 */
	void		RenderTarget::setPosition(const Vector2D& vPos)
	{
		Size cSize = getSize();
		m_rcArea.setRect(vPos.x, vPos.y, cSize.w, cSize.h);
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	RenderTarget::getPosition() const
	{
		return m_rcArea.getUpper();
	}

	/**
	 *
	 * \param cSize 
	 */
	void		RenderTarget::setSize(const Size& cSize)
	{
		Vector2D vPos = getPosition();
		m_rcArea.setRect(vPos.x, vPos.y, cSize.w, cSize.h);
	}

	/**
	 *
	 * \return 
	 */
	Size		RenderTarget::getSize() const
	{
		return m_rcArea.getSize();
	}

	/**
	 *
	 * \param rcArea 
	 */
	void		RenderTarget::setArea(const Rect& rcArea)
	{
		m_rcArea = rcArea;
	}

	/**
	 *
	 * \return 
	 */
	Rect		RenderTarget::getArea() const
	{
		return m_rcArea;
	}
}