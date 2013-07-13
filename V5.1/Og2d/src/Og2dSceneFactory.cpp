#include "Og2dSceneFactory.h"

namespace Og2d
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	SceneFactory::SceneFactory(const String& typeName)
		: m_typeName(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	SceneFactory::~SceneFactory()
	{

	}

	/**
	 *
	 * \param typeName 
	 */
	void		SceneFactory::setTypeName(const String& typeName)
	{
		m_typeName = typeName;
	}

	/**
	 *
	 * \return 
	 */
	String		SceneFactory::getTypeName() const
	{
		return m_typeName;
	}

	/**
	 *
	 * \return 
	 */
	Scene*		SceneFactory::createScene(const String& szName, const Rect& rcBound)
	{
		return new Scene(szName, rcBound);
	}
}