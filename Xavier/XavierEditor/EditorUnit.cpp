#include "stdafx.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
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
		: EditorPlugin(pluginName), m_pNode(NULL), m_pEntity(NULL), m_pSceneManager(NULL), m_pAxis(NULL), m_bLDown(0), m_nRot(0)
	{
		// 获取场景插件
		EditorSceneManager* pSceneMgrEditor = static_cast<EditorSceneManager*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME)
			);
		if (!pSceneMgrEditor)
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't find plugin + " + EDITOR_SCENEPLUGIN_NAME);
		}

		// 保存场景管理
		m_pSceneManager = pSceneMgrEditor->getSceneManager();
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
	bool			EditorUnit::OnSetFocus()
	{
		if (m_pNode)
		{
			m_pNode->showBoundingBox(true);
		}

		return true;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnLoseFocus()
	{
		if (m_pNode)
		{
			m_pNode->showBoundingBox(0);
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
		m_bLDown = true;
		return true;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnMouseMove(const Vector2& vPos)
	{
		if (!m_bLDown)
			return true;

		EditorViewport* pViewportEditor = static_cast<EditorViewport*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT)
			);
		if (pViewportEditor)
		{
			EditorTerrain* pTerrain = static_cast<EditorTerrain*>(
				EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
				);
			if (pTerrain)
			{
				TerrainGroup* pGroup = pTerrain->getTerrainGroup();
				if (pGroup)
				{
					Ray ray;
					if (pViewportEditor->getMouseRay(vPos, ray))
					{
						TerrainGroup::RayResult rayResult = pGroup->rayIntersects(ray);
						if (rayResult.hit)
						{
							m_pNode->setPosition(rayResult.position);
						}
					}
				}
			}
		}

		return true;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorUnit::OnLButtonUp(const Vector2& vPos)
	{
		m_bLDown = false;

		return true;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorUnit::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		switch (nChar)
		{
		case 'W':
			{
				Vector3 vPos = m_pNode->getPosition();
				vPos.y ++;
				m_pNode->setPosition(vPos);
			}
			break;
		case 'S':
			{
				Vector3 vPos = m_pNode->getPosition();
				vPos.y --;
				m_pNode->setPosition(vPos);
			}
			break;
		case 'A':
			{
				Vector3 vPos = m_pNode->getPosition();
				vPos.x --;
				m_pNode->setPosition(vPos);
			}
			break;
		case 'D':
			{
				Vector3 vPos = m_pNode->getPosition();
				vPos.x ++;
				m_pNode->setPosition(vPos);
			}
			break;
		case 'Q':
			{
				Quaternion rot = m_pNode->getOrientation();
				m_nRot ++;
				rot.FromAngleAxis(Degree(m_nRot), Vector3::UNIT_Y);
				m_pNode->setOrientation(rot);
			}
			break;
		case 'E':
			{
				Quaternion rot = m_pNode->getOrientation();
				m_nRot --;
				rot.FromAngleAxis(Degree(m_nRot), Vector3::UNIT_Y);
				m_pNode->setOrientation(rot);
			}
			break;
		case VK_OEM_PLUS:
			{
				Vector3 vScale = m_pNode->getScale();
				vScale += 0.01;
				m_pNode->setScale(vScale);
			}
			break;
		case VK_OEM_MINUS:
			{
				Vector3 vScale = m_pNode->getScale();
				vScale -= 0.01;
				m_pNode->setScale(vScale);
			}
			break;

		}

		return true;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorUnit::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return true;
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