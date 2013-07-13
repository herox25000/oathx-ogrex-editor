#include "Og2dScene.h"
#include "Og2dException.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Scene::Scene(const String& szName, const Rect& rcBound)
		: m_szName(szName), m_rcBound(rcBound), m_bActive(true)
	{
	
	}

	/**
	 *
	 * \return 
	 */
	Scene::~Scene()
	{
		destroyAllSceneNode();
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
	Rect		Scene::getBoundingBox() const
	{
		return m_rcBound;
	}

	/**
	 *
	 * \return 
	 */
	void		Scene::setActive(bool bActive)
	{
		m_bActive = bActive;
	}

	/**
	 *
	 * \return 
	 */
	bool		Scene::getActive() const
	{
		return m_bActive;
	}

	/**
	 *
	 * \return 
	 */	
	SceneNode*	Scene::createSceneNode(const String& szNodeFactoryName, const String& szName, const Rect& rcBound)
	{
		SceneNodeFactory* pFactory = SceneNodeFactoryManager::getSingleton().getSceneNodeFactory(szNodeFactoryName);
		if (pFactory != NULL)
		{
			MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
			if ( it == m_MapSceneNodeTab.end() )
			{
				// create this scene node
				SceneNode* pNode = pFactory->create(szName, rcBound);
				if (pNode)
				{
					m_MapSceneNodeTab.insert(MapSceneNodeTab::value_type(szName, pNode));
					return pNode;
				}
			}
		}
		
		return NULL;
	}

	/**
	 *
	 * \return 
	 */	
	SceneNode*	Scene::getSceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
		if ( it != m_MapSceneNodeTab.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \return 
	 */	
	void		Scene::destroySceneNode(const String& szName)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.find(szName);
		if ( it != m_MapSceneNodeTab.end() )
		{
			SAFE_DELETE(it->second); it = m_MapSceneNodeTab.erase(it);
		}
	}

	/**
	 *
	 * \return 
	 */	
	void		Scene::destroySceneNode(SceneNode* pSceneNode)
	{
		destroySceneNode(pSceneNode->getName());
	}

	/**
	 *
	 * \return 
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
	 * \return 
	 */	
	void		Scene::update(float fElapsed)
	{
		MapSceneNodeTab::iterator it = m_MapSceneNodeTab.begin();
		while( it != m_MapSceneNodeTab.end() )
		{
			it->second->update(fElapsed); it ++;
		}
	}
}