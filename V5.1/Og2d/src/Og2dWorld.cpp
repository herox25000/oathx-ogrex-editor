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
		: m_szName(szName), m_pNeedUpdateScene(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	World::~World()
	{
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
	 * \param szCreateFactoryName 
	 * \param szName 
	 * \return 
	 */
	Scene*	World::createScene(const String& szCreateFactoryName, const String& szName, 
		const Vector2D& vPos, const Size& cSize)
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
				Scene* pScene = pFactory->createScene(szName, vPos, cSize);
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
			// update current scene
			m_pNeedUpdateScene->update(fElapsed);
		}
	}
}