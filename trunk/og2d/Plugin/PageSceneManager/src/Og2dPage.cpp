#include "Og2dPageScenePrerequisites.h"
#include "Og2dSceneNode.h"
#include "Og2dPage.h"

namespace Og2d
{
	/**
	 *
	 * \param vPos 
	 * \param cSize 
	 * \return 
	 */
	Page::Page(const String& szName, const Rect& rcBoundingBox)
		: SceneNode(szName, rcBoundingBox, NULL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	Page::~Page()
	{

	}

	/**
	 *
	 * \param fElapsed 
	 */
	void	Page::update(float fElapsed)
	{
		SceneNode::update(fElapsed);
	}
}