#include "stdafx.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"
#include "EditorUnit.h"

namespace Ogre
{
	static const int	QUERYFLAG_MOVABLE = 2;

	/**
	 *
	 * \param pluginName 
	 * \return 
	 */
	EditorUnit::EditorUnit(const String& pluginName, const String& szFileName, 
		const Vector3& vPos, const Vector3& vScale, float fDegree) 
		: EditorPlugin(pluginName), m_pNode(NULL), m_pEntity(NULL), m_pSceneManager(NULL), m_pViewporPlugin(NULL), m_pEditorSceneManager(NULL)
	{
		// 获取场景插件
		m_pEditorSceneManager = static_cast<EditorSceneManager*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME)
			);
		if (!m_pEditorSceneManager)
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't find plugin + " + EDITOR_SCENEPLUGIN_NAME);
		}

		// 获取视图编辑器
		m_pViewporPlugin = static_cast<EditorViewport*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT)
			);
		if (m_pViewporPlugin == NULL)
		{
			TKLogEvent("Can't find editor plugin : " + EDITOR_VIEWPORT,
				LML_CRITICAL);
		}

		// 保存场景管理
		m_pSceneManager = m_pEditorSceneManager->getSceneManager();
		if (m_pSceneManager)
		{
			configure(szFileName, vPos, vScale, fDegree);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorUnit::~EditorUnit()
	{

	}

	/**
	 *
	 * \param szFileName 
	 * \param vPos 
	 * \param vScale 
	 * \param fDegree 
	 * \return 
	 */
	bool			EditorUnit::configure(const String& szFileName, const Vector3& vPos, 
		const Vector3& vScale, float fDegree)
	{
		m_pEntity = m_pSceneManager->createEntity(szFileName);
		if (m_pEntity == NULL)
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't find unit file + " + szFileName);
			return 0;
		}

		String name = m_pEntity->getName();
		setName(name);

		Quaternion rot;
		rot.FromAngleAxis(Degree(fDegree), Vector3::UNIT_Y);

		m_pNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(vPos, rot);
		if (m_pNode)
		{
			m_pNode->setScale(vScale);
			m_pNode->attachObject(
				m_pEntity);
		}	
		
		return true;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnLButtonDown(const Vector2& vPos)
	{
		if (m_pViewporPlugin)
		{
			Ray ray;
			if (m_pViewporPlugin->getMouseRay(vPos, ray))
			{
				RaySceneQuery* pSceneQuery = m_pEditorSceneManager->getRaySceneQuery();
				if (pSceneQuery == NULL)
					return 0;
				
				pSceneQuery->setRay(ray);
				pSceneQuery->setQueryMask(QUERYFLAG_MOVABLE);
				pSceneQuery->setSortByDistance(true);

				// Execute query
				Ogre::RaySceneQueryResult& result		= pSceneQuery->execute();
				Ogre::RaySceneQueryResult::iterator itr = result.begin();

				for ( itr = result.begin(); itr != result.end(); itr++ ) 
				{ 
					if (itr->movable && itr->movable->isVisible()) 
					{ 
						String name = itr->movable->getName();
						if (name.empty())
						{

						}
					} 
				}
			}
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnMouseMove(const Vector2& vPos)
	{

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorUnitFactory::EditorUnitFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorUnitFactory::~EditorUnitFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*	EditorUnitFactory::createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent)
	{
		const SEditorUnitAdp& adp = static_cast<const SEditorUnitAdp&>(ssadp);
		
		EditorUnit* pUnit = new EditorUnit(ssadp.pluginName, 
			adp.szFileName, adp.vPos, adp.vScale, adp.fDegree);
		if (pUnit)
		{
			// 设置删除优先级
			pUnit->setPriority(PRIORITY_LOW);

			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Create editor plugin : " + adp.pluginName);

			if (pParent)
				pParent->registerPlugin(pUnit);

			return pUnit;
		}

		return NULL;
	}
}