#include "Og2dWorld.h"
#include "Og2dException.h"
#include "Og2dSystem.h"
#include "Og2dLogManager.h"
#include "Og2dScene.h"
#include "Og2dSceneFactory.h"

namespace Og2d
{
	template<>	World*	Singleton<World>::mpSingleton = 0;
	/**
	 *
	 * \return 
	 */
	World&		World::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	World*		World::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}

	/**
	 *
	 * \param cSize 
	 * \return 
	 */
	World::World(const String& szName) 
		: m_szName(szName), m_pNeedUpdateScene(NULL), m_pViewport(NULL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	World::~World()
	{
		destroyAllViewprot();
		destroyAllScene();
	}

	/**
	 *
	 * \param szName 
	 */
	void	World::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	String	World::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param name 
	 * \param vPos 
	 * \return 
	 */
	Viewport*	World::createViewport(const String& name, const Vector2D& vPos)
	{
		ViewportTab::iterator it = m_MapViewport.find(name);
		if ( it == m_MapViewport.end() )
		{
			// create viewport
			Viewport* pViewport = new Viewport(
				System::getSingletonPtr()->getRenderSystem(), vPos);
			if (pViewport)
			{
				// if current viewport is null then set it
				if (m_pViewport == NULL)
					m_pViewport = pViewport;

				m_MapViewport.insert(ViewportTab::value_type(name, pViewport));
				return pViewport;
			}
		}

		return NULL;
	}
	
	/**
	 *
	 * \param name 
	 */
	void	World::destroyViewport(const String& name)
	{
		ViewportTab::iterator it = m_MapViewport.find(name);
		if ( it != m_MapViewport.end() )
		{
			SAFE_DELETE(it->second); m_MapViewport.erase(it);
		}
	}

	/**
	 *
	 * \return 
	 */
	Viewport* World::getViewport() const
	{
		return m_pViewport;
	}

	/**
	 *
	 */
	void	World::destroyAllViewprot()
	{
		ViewportTab::iterator it = m_MapViewport.begin();
		while ( it != m_MapViewport.end() )
		{
			SAFE_DELETE(it->second); it = m_MapViewport.erase(it);
		}
	}

	/**
	 *
	 * \param szCreateFactoryName 
	 * \param szName 
	 * \return 
	 */
	Scene*	World::createScene(const String& szCreateFactoryName, const String& szName, 
		const Vector2D& vOrigin, const Size& cSize, const Rect& rcView)
	{
		SceneMapTab::iterator it = m_MapSceneTab.find(szName);
		if ( it == m_MapSceneTab.end() )
		{
			// get scene factory
			SceneFactory* pFactory = System::getSingleton().getSceneFactory(
				szCreateFactoryName
				);
			if (pFactory)
			{
				// crate scene object
				Scene* pScene = pFactory->createScene(szName, vOrigin, cSize, rcView);
				if (pScene)
				{
					// if current need updat scene is null 
					// set this scene to current need scene
					if (!getNeedUpdateScene())
						setNeedUpdateScene(pScene);

					// inser to map table
					m_MapSceneTab.insert(SceneMapTab::value_type(szName, pScene));
					return pScene;
				}
			}
			else
			{
				// can't found scene factory
				tryException(EC_ITEM_NOT_FOUND, "can't found scene factory " + szCreateFactoryName,
					"World::createScene");
			}
		}

		return NULL;
	}
	
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Scene*	World::getScene(const String& szName)
	{
		SceneMapTab::iterator it = m_MapSceneTab.find(szName);
		if ( it != m_MapSceneTab.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \param pScene 
	 */
	void	World::destroyScene(Scene* pScene)
	{
		destroyScene(pScene->getName());
	}

	/**
	 *
	 * \param szName 
	 */
	void	World::destroyScene(const String& szName)
	{
		SceneMapTab::iterator it = m_MapSceneTab.find(szName);
		if ( it != m_MapSceneTab.end() )
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL, 
				"destroy scene " + szName);

			// destroy scene object
			SAFE_DELETE(it->second); m_MapSceneTab.erase(it);
		}
	}

	/**
	 *
	 */
	void	World::destroyAllScene()
	{
		SceneMapTab::iterator it = m_MapSceneTab.begin();
		while (it != m_MapSceneTab.end())
		{
			// out log
			LogManager::getSingleton().logMessage(INFO_NORMAL, 
				"destroy scene " + it->second->getName());

			SAFE_DELETE(it->second); it = m_MapSceneTab.erase(it);
		}

		setNeedUpdateScene(NULL);
	}

	/**
	 *
	 * \param pScene 
	 */
	void	World::setNeedUpdateScene(Scene* pScene)
	{
		if (m_pNeedUpdateScene != pScene)
			m_pNeedUpdateScene = pScene;
	}

	/**
	 *
	 * \return 
	 */
	Scene*	World::getNeedUpdateScene() const
	{
		return m_pNeedUpdateScene;
	}

	/**
	 *
	 * \param fElapsed 
	 */
	void	World::update(float fElapsed)
	{
		if (m_pNeedUpdateScene)
		{
			// update view
			if (m_pViewport)
			{
				m_pViewport->update(fElapsed);
			}

			// update current scene
			m_pNeedUpdateScene->update(fElapsed);
		}
	}
}