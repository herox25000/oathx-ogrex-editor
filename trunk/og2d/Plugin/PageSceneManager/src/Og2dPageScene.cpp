#include "Og2dPageScenePrerequisites.h"
#include "Og2dPageScene.h"
#include "Og2dWorld.h"
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
	PageScene::PageScene(const String& szName, const Vector2D& vPos, const Size& cSize)
		: Scene(szName, vPos, cSize)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	PageScene::~PageScene()
	{
		destroyAllSceneNode();
	}

	/**
	 *
	 * \param szName 
	 * \param vPos 
	 * \return 
	 */
	SceneNode*	PageScene::createSceneNode(const String& szName, const Vector2D& vPos)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNode.find(szName);
		if ( it == m_MapSceneNode.end() )
		{
			SceneNode* pSceneNode = new SceneNode(szName, vPos);
			if (pSceneNode)
			{
				m_MapSceneNode.insert(
					MapSceneNodeTab::value_type(szName, pSceneNode)
					);
				return pSceneNode;
			}
		}

		return NULL;
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	SceneNode*	PageScene::getSceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNode.find(szName);
		if ( it != m_MapSceneNode.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param szName 
	 */
	void		PageScene::destroySceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNode.find(szName);
		if ( it != m_MapSceneNode.end() )
		{
			SAFE_DELETE(it->second); m_MapSceneNode.erase(it);
		}
	}

	/**
	 *
	 * \param pSceneNode 
	 */
	void		PageScene::destroySceneNode(SceneNode* pSceneNode)
	{
		destroySceneNode(pSceneNode->getName());
	}

	/**
	 *
	 */
	void		PageScene::destroyAllSceneNode()
	{
		MapSceneNodeTab::iterator it = m_MapSceneNode.begin();
		while( it != m_MapSceneNode.end() )
		{
			SAFE_DELETE( it->second ); it = m_MapSceneNode.erase(it);
		}
	}

	/**
	 *
	 * \param fElapsed 
	 */
	void		PageScene::update(float fElapsed)
	{
		// get viewport
		Viewport* pViewport = World::getSingletonPtr()->getViewport();
		Rect rcViewArea = pViewport->getArea();
		
		MapSceneNodeTab::iterator it = m_MapSceneNode.begin();
		while( it != m_MapSceneNode.end() )
		{
			Rect rcNodeArea(it->second->getPosition(), Size(640, 480));
			
			Vector2D vLeftUpper		= rcNodeArea.getUpper();
			Vector2D vLeftLower(rcNodeArea.left, rcNodeArea.bottom);
			
			Vector2D vRigthUpper	= rcNodeArea.getLower();
			Vector2D vRightLower(rcNodeArea.right, rcNodeArea.top);

			if (rcViewArea.ptInRect(vLeftUpper) ||
				rcViewArea.ptInRect(vLeftLower) ||
				rcViewArea.ptInRect(vRigthUpper) ||
				rcViewArea.ptInRect(vRightLower))
			{
				it->second->update(fElapsed);
			}
			
			it ++;
		}
	}
}