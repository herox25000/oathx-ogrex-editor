#include "stdafx.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"
#include "EditorGizmo.h"

namespace Ogre
{
	template<>	Grizmo*	Singleton<Grizmo>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	Grizmo&	Grizmo::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	Grizmo*	Grizmo::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	Grizmo::Grizmo(SceneManager* pSceneManager, const String& szMeshFile, const Vector3& vPos, const Vector3& vScale)
		: m_pSceneManager(pSceneManager), m_pNode(NULL), m_pEntity(NULL)
	{
		configure(szMeshFile, vPos, vScale);
	}

	/**
	 *
	 * \return 
	 */
	Grizmo::~Grizmo()
	{
		if (m_pEntity)
			m_pEntity->detachFromParent();

		m_pSceneManager->destroyEntity(m_pEntity);

		if (m_pNode)
			m_pSceneManager->destroySceneNode(m_pNode);	
	}

	/**
	 *
	 * \param pParent 
	 */
	void		Grizmo::show(SceneNode* pParent)
	{
		if (pParent)
		{
			m_pNode->setVisible(true);
			pParent->addChild(m_pNode);
		}
	}

	/**
	 *
	 * \param pParent 
	 */
	void		Grizmo::hide(SceneNode* pParent)
	{
		if (pParent)
		{
			m_pNode->setVisible(0);
			pParent->removeChild(m_pNode);
		}		
	}

	/**
	 *
	 * \param szFileName 
	 * \param vPos 
	 * \param vScale 
	 * \return 
	 */
	bool		Grizmo::configure(const String& szFileName, 
		const Vector3& vPos, const Vector3& vScale)
	{
		m_pEntity = m_pSceneManager->createEntity(szFileName);
		if (m_pEntity == NULL)
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't find module file + " + szFileName);
		}

		m_pNode = m_pSceneManager->createSceneNode();
		if (m_pNode)
		{
			m_pNode->setScale(vScale);
			m_pNode->attachObject(m_pEntity);
		}

		return true;
	}
}