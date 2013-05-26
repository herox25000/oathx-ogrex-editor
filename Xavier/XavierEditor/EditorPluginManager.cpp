#include "stdafx.h"
#include "EditorSceneManager.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
#include "EditorPluginManager.h"

namespace Ogre
{
	static const uint QUERYFLAG_MOVABLE = 1;

	template<>	EditorPluginManager*	Singleton<EditorPluginManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorPluginManager&	EditorPluginManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginManager*	EditorPluginManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \param rootName 
	 * \return 
	 */
	EditorPluginManager::EditorPluginManager(const String& rootName)
		: m_pRootEditor(NULL), m_pSelectEdtior(NULL)
	{
		m_pRootEditor = new EditorPlugin(rootName);
		if (m_pRootEditor)
		{
			TKLogEvent("Init root plugin : " + rootName, LML_NORMAL);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginManager::~EditorPluginManager()
	{
		delete m_pRootEditor;
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getRootPlugin() const
	{
		return m_pRootEditor;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::findPlugin(const String& name)
	{
		if (name == m_pRootEditor->getName())
			return m_pRootEditor;

		return m_pRootEditor->findPlugin(name);
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			EditorPluginManager::setSelectPlugin(EditorPlugin* pPlugin)
	{
		// 丢失焦点
		if (m_pSelectEdtior != pPlugin)
		{
			if (m_pSelectEdtior != NULL)
				m_pSelectEdtior->OnLoseFocus();

			m_pSelectEdtior = pPlugin;

			// 获取焦点
			if (m_pSelectEdtior)
				m_pSelectEdtior->OnSetFocus();
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getSelectPlugin() const
	{
		return m_pSelectEdtior;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getPlugin(const Vector2& vPos)
	{
		EditorSceneManager* pSceneEditor = static_cast<EditorSceneManager*>(
			m_pRootEditor->findPlugin(EDITOR_SCENEPLUGIN_NAME)
			);
		if (pSceneEditor)
		{
			EditorViewport*	pViewportEditor = static_cast<EditorViewport*>(findPlugin(EDITOR_VIEWPORT));
			if (pViewportEditor)
			{
				RaySceneQuery* pRaySceneQuery = pSceneEditor->getRaySceneQuery();
				if (pRaySceneQuery)
				{
					Ray ray;
					if (!pViewportEditor->getMouseRay(vPos, ray))
						return NULL;

					pRaySceneQuery->setRay(ray);
					pRaySceneQuery->setQueryMask(QUERYFLAG_MOVABLE);
					pRaySceneQuery->setSortByDistance(true);

					RaySceneQueryResult& result = pRaySceneQuery->execute(); 
					for (RaySceneQueryResult::iterator it=result.begin();
						it!=result.end(); it++)
					{
						if (it->movable != NULL)
						{
							String name = it->movable->getName();
							if (!name.empty())
								return m_pRootEditor->findPlugin(it->movable->getName());
						}
					}
				}
			}
		}

		return NULL;
	}
}