#include "Og2dScene.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Scene::Scene(const String& szName, const Vector2D& vOrigin, const Size& cSize, 
		const Rect& rcView)
		: m_szName(szName), m_vOrigin(vOrigin), m_rcBouingBox(Vector2D(0, 0), cSize)
	{
	
	}

	/**
	 *
	 * \return 
	 */
	Scene::~Scene()
	{
		// 销毁所有的场景节点
		destroyAllSceneNode();
	}

	/**
	 *
	 * \param szName 
	 */
	void		Scene::setName(const String& szName)
	{
		m_szName = szName;
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
	Vector2D	Scene::getOrigin() const
	{
		return m_vOrigin;
	}

	/**
	 *
	 * \param vOrigin 
	 */
	void		Scene::setOrigin(const Vector2D& vOrigin)
	{
		m_vOrigin = vOrigin;
	}

	/**
	 *
	 * \return 
	 */
	Size		Scene::getSize() const
	{
		return m_rcBouingBox.getSize();
	}

	/**
	 *
	 * \param cSize 
	 */
	void		Scene::setSize(const Size& cSize)
	{
		m_rcBouingBox += cSize;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Scene::getCenter() const
	{
		return m_rcBouingBox.getCenter();
	}

	/**
	 *
	 * \return 
	 */
	Rect		Scene::getBoundingBox() const
	{
		return m_rcBouingBox;
	}


	/**
	 *
	 * \param szName 
	 * \param rcBoundingBox 
	 * \return 
	 */
	SceneNode*	Scene::createSceneNode(const String& szName, const Rect& rcBoundingBox)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
		if ( it == m_MapSceneNodeTab.end() )
		{
			// 创建新场景节点
			SceneNode* pSceneNode = new SceneNode(szName,
				rcBoundingBox, NULL);
			if (pSceneNode)
			{
				// 插入场景节点
				m_MapSceneNodeTab.insert(MapSceneNodeTab::value_type(szName,
					pSceneNode));

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
	SceneNode*	Scene::getSceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
		if ( it != m_MapSceneNodeTab.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param szName 
	 */
	void		Scene::destroySceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
		if ( it != m_MapSceneNodeTab.end() )
		{
			SAFE_DELETE( it->second ); m_MapSceneNodeTab.erase(it);
		}
	}

	/**
	 *
	 * \param pSceneNode 
	 */
	void		Scene::destroySceneNode(SceneNode* pSceneNode)
	{
		destroySceneNode(pSceneNode->getName());
	}

	/**
	 *
	 */
	void		Scene::destroyAllSceneNode()
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.begin();
		while( it != m_MapSceneNodeTab.end() )
		{
			SAFE_DELETE(it->second); it = m_MapSceneNodeTab.erase(it);
		}
	}

	/**
	 *
	 * \param fElapsed 
	 */
	void		Scene::update(float fElapsed)
	{
		for (MapSceneNodeTab::iterator it=m_MapSceneNodeTab.begin();
			it!=m_MapSceneNodeTab.end(); it++)
		{
			it->second->update(fElapsed);
		}
	}
}