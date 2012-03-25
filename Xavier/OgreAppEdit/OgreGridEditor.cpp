#include "OgreAppEditPrerequisites.h"
#include "OgreGridEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param fWidth 
	 * \param fSize 
	 * \param fDepth 
	 * \return 
	 */
	GridEditor::GridEditor(SceneManager* pSceneManager, Real fWidth, Real fSize, Real fDepth)
		: m_pSceneManager(pSceneManager), m_pGridNode(NULL), m_fDepth(fDepth), m_fSize(fSize), m_fWidth(fWidth)
	{
		setTypeName(EDIT_GRIDEDIROR);

		MeshManager::getSingletonPtr()->createPlane("XavierGridMesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Ogre::Vector3::UNIT_Y, 0), fWidth * fSize, fDepth * fSize, 1, 1, false, 1, fWidth, fDepth, Ogre::Vector3::UNIT_Z);
		//show();
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	GridEditor::~GridEditor(void)
	{
	}

	/**
	 *
	 */
	void		GridEditor::show()
	{
		if (m_pGridNode != NULL || m_pSceneManager == NULL)
			return;
		
		Entity* ent = m_pSceneManager->createEntity("XavierGirdEntity", "XavierGridMesh");
		ent->setMaterialName("XavierGird/Grid");
		ent->setCastShadows(false);
		
		m_pGridNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
		m_pGridNode->attachObject(ent);
	}

	/**
	 *
	 */
	void		GridEditor::hide()
	{
		if( m_pGridNode )
		{
			Ogre::Entity *entity = static_cast<Ogre::Entity*>(m_pGridNode->getAttachedObject(0));
			m_pGridNode->getParentSceneNode()->removeAndDestroyChild( m_pGridNode->getName() );
			m_pSceneManager->destroyEntity( entity );

			m_pGridNode = NULL;
		}
	}

	/**
	 *
	 * \return 
	 */
	GridEditorFactory::GridEditorFactory()
	{
		setTypeName(FACTORY_GRID);
	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*	GridEditorFactory::create(const SBaseCreateParam* pm)
	{
		SGridCreateParam* cm = (SGridCreateParam*)(pm);

		/*
		* 获取场景管理器
		*/
		SceneManager* pMgr = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
		assert(pMgr != NULL);

		return new GridEditor(pMgr, cm->fWidth, cm->fSize, cm->fDepth);
	}
}
