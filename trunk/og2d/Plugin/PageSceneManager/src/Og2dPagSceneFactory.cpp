#include "Og2dPageScenePrerequisites.h"
#include "Og2dPagSceneFactory.h"
#include "Og2dPageScene.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	PageSceneFactory::PageSceneFactory(const String& typeName)
		: SceneFactory(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	PageSceneFactory::~PageSceneFactory()
	{

	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Scene*	PageSceneFactory::createScene(const String& szName, const Vector2D& vOrigin,
		const Size& cSize, const Rect& rcView)
	{
		return new PageScene(szName, vOrigin, cSize, rcView);
	}
}