#include "Og2dPageScenePrerequisites.h"
#include "Og2dPageScene.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param szName 
	 * \param vOrigin 
	 * \param cSize 
	 * \param rcView 
	 * \return 
	 */
	PageScene::PageScene(const String& szName, const Vector2D& vOrigin, const Size& cSize,
		const Rect& rcView)
		: Scene(szName, vOrigin, cSize, rcView)
	{

	}

	/**
	 *
	 * \return 
	 */
	PageScene::~PageScene()
	{

	}

	/**
	 *
	 * \param fElapsed 
	 */
	void	PageScene::update(float fElapsed)
	{
		for (MapSceneNodeTab::iterator it=m_MapSceneNodeTab.begin();
			it!=m_MapSceneNodeTab.end(); it++)
		{
			it->second->update(fElapsed);
		}
	}
}