#include "Og2dScene.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Scene::Scene(const String& szName, const Vector2D& vPos, const Size& cSize)
		: m_vPos(vPos), m_szName(szName), m_cSize(cSize)
	{
	
	}

	/**
	 *
	 * \return 
	 */
	Scene::~Scene()
	{

	}

	/**
	 *
	 * \param name 
	 */
	void		Scene::setName(const String& name)
	{
		m_szName = name;
	}

	/**
	 *
	 * \return 
	 */
	String		Scene::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \return 
	 */
	Size		Scene::getSize() const
	{
		return m_cSize;
	}

	/**
	 *
	 * \param cSize 
	 */
	void		Scene::setSize(const Size& cSize)
	{
		m_cSize = cSize;
	}

	/**
	 *
	 * \return 
	 */
	Rect		Scene::getArea() const
	{
		return Rect(m_vPos, m_cSize);
	}
}