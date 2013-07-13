#include "Og2dSceneFactory.h"

namespace Og2d
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	SceneFactory::SceneFactory(int nType)
		: m_nType(nType)
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
	 * \return 
	 */
	int			SceneFactory::getType() const
	{
		return m_nType;
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