#include "Og2dSceneNodeFactory.h"

namespace Og2d
{
	String SceneNodeFactory::TypeName = "DefaultSceneNodeFactory";
	
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	SceneNodeFactory::SceneNodeFactory(const String& szName)
		: m_szName(szName)
	{

	}

	/**
	 *
	 * \return 
	 */
	SceneNodeFactory::~SceneNodeFactory()
	{

	}

	/**
	 *
	 * \param szName 
	 * \param vPos 
	 * \param cSize 
	 * \return 
	 */
	SceneNode*	SceneNodeFactory::create(const String& szName, const Vector2D& vPos)
	{
		return new SceneNode(szName, vPos);
	}

	/**
	 *
	 * \param szName 
	 */
	void		SceneNodeFactory::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	String		SceneNodeFactory::getName() const
	{
		return m_szName;
	}
}