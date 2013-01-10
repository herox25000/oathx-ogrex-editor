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
		m_BouingBox += vPos;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	RenderTarget::getPosition() const
	{
		return m_BouingBox.getUpper();
	}

	/**
	 *
	 * \param vPos 
	 */
	void		RenderTarget::setRelativelyPosition(const Vector2D& vPos)
	{
		m_vRelativelyPosition = vPos;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	RenderTarget::getRelativelyPosition() const
	{
		return m_vRelativelyPosition;
	}

	/**
	 *
	 * \param rcBoundingBox 
	 */
	void		RenderTarget::setBoundingBox(const Rect& rcBoundingBox)
	{
		m_BouingBox = rcBoundingBox;
	}

	/**
	 *
	 * \return 
	 */
	Rect		RenderTarget::getBoundingBox() const
	{
		return m_BouingBox;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	RenderTarget::getCenter() const
	{
		return m_BouingBox.getCenter();
	}
}